// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MASTERNODEMAN_H
#define MASTERNODEMAN_H

#include "activemasternode.h"
#include "activemasternodeman.h"
#include "base58.h"
#include "key.h"
#include "main.h"
#include "masternode.h"
#include "net.h"
#include "sync.h"
#include "util.h"

#define MASTERNODES_DUMP_SECONDS (15 * 60)
#define MASTERNODES_DSEG_SECONDS (3 * 60 * 60)


class CMasternodeMan;
class CActiveMasternode;

extern CMasternodeMan mnodeman;
extern CActiveMasternodeMan amnodeman;

void DumpMasternodes();

/** Access to the MN database (mncache.dat)
 */
class CMasternodeDB
{
private:
    fs::path pathMN;
    std::string strMagicMessage;

public:
    enum ReadResult {
        Ok,
        FileError,
        HashReadError,
        IncorrectHash,
        IncorrectMagicMessage,
        IncorrectMagicNumber,
        IncorrectFormat
    };

    CMasternodeDB();
    bool Write(const CMasternodeMan& mnodemanToSave);
    ReadResult Read(CMasternodeMan& mnodemanToLoad, bool fDryRun = false);
};

class CMasternodeMan
{
private:
    // critical section to protect the inner data structures
    mutable RecursiveMutex cs;
    mutable RecursiveMutex cs_script;
    mutable RecursiveMutex cs_txin;
    mutable RecursiveMutex cs_pubkey;

    // critical section to protect the inner data structures specifically on messaging
    mutable RecursiveMutex cs_process_message;

    // vector to hold all MNs
    std::vector<CMasternode*> vMasternodes;
    // map MNs by CScript
    std::unordered_map<CScript, CMasternode*, CScriptCheapHasher> mapScriptMasternodes;
    // map MNs by CTxIn
    std::unordered_map<CTxIn, CMasternode*, CTxInCheapHasher> mapTxInMasternodes;
    // map MNs by CTxIn
    std::unordered_map<CPubKey, CMasternode*, CPubKeyCheapHasher> mapPubKeyMasternodes;
    // who's asked for the Masternode list and the last time
    std::map<CNetAddr, int64_t> mAskedUsForMasternodeList;
    // who we asked for the Masternode list and the last time
    std::map<CNetAddr, int64_t> mWeAskedForMasternodeList;
    // which Masternodes we've asked for
    std::map<COutPoint, int64_t> mWeAskedForMasternodeListEntry;

    // find an entry in the masternode list that is next to be paid (internally)
    CMasternode* GetNextMasternodeInQueueForPayment(
        int nBlockHeight, bool fFilterSigTime, 
        int& nCount, std::vector<CTxIn>& vecEligibleTxIns,
        bool fJustCount = false);

public:
    // Keep track of all broadcasts I've seen
    std::map<uint256, CMasternodeBroadcast> mapSeenMasternodeBroadcast;
    // Keep track of all pings I've seen
    std::map<uint256, CMasternodePing> mapSeenMasternodePing;

    // keep track of dsq count to prevent masternodes from gaming obfuscation queue
    // TODO: Remove this from serialization
    int64_t nDsqCount;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        LOCK(cs);
        uint64_t n = (uint64_t)vMasternodes.size();
        CCompactSize size(n);
        READWRITE(size);
        if(ser_action.ForRead()) { 
            vMasternodes.reserve(size);
            for(uint64_t i = 0; i < size; i++) {
                auto mn = new CMasternode();
                READWRITE(*mn);
                vMasternodes.push_back(mn);
                {
                    LOCK(cs_script);
                    mapScriptMasternodes[GetScriptForDestination(mn->pubKeyCollateralAddress.GetID())] = mn;
                }
                {
                    LOCK(cs_txin);
                    mapTxInMasternodes[mn->vin] = mn;
                }
                {
                    LOCK(cs_pubkey);
                    mapPubKeyMasternodes[mn->pubKeyMasternode] = mn;
                }
            }
        } else {
            for(auto mn : vMasternodes) {
                READWRITE(*mn);
            }
        }
        READWRITE(mAskedUsForMasternodeList);
        READWRITE(mWeAskedForMasternodeList);
        READWRITE(mWeAskedForMasternodeListEntry);
        READWRITE(nDsqCount);

        READWRITE(mapSeenMasternodeBroadcast);
        READWRITE(mapSeenMasternodePing);
    }

    CMasternodeMan();

    /// Add an entry
    bool Add(CMasternode& mn);

    /// Ask (source) node for mnb
    void AskForMN(CNode* pnode, const CTxIn& vin);

    /// Check all Masternodes
    void Check();

    /// Check all Masternodes and remove inactive
    void CheckAndRemove(bool forceExpiredRemoval = false);

    /// Clear Masternode vector
    void Clear();

    int CountEnabled();

    void CountNetworks(int& ipv4, int& ipv6, int& onion);

    void DsegUpdate(CNode* pnode);

    /// Find an entry
    CMasternode* Find(const CScript& payee);
    CMasternode* Find(const CTxIn& vin);
    CMasternode* Find(const CPubKey& pubKeyMasternode);
    CMasternode* Find(const CService &addr);

    // Find an entry in the masternode list that is next to be paid
    inline CMasternode* GetNextMasternodeInQueueForPayment(int nBlockHeight) {
        int nCount = 0;
        std::vector<CTxIn> vEligibleTxIns;
        return GetNextMasternodeInQueueForPayment(nBlockHeight, true, nCount, vEligibleTxIns);
    }

    inline int GetNextMasternodeInQueueCount(int nBlockHeight) {
        int nCount = 0;
        std::vector<CTxIn> vEligibleTxIns;
        GetNextMasternodeInQueueForPayment(nBlockHeight, true, nCount, vEligibleTxIns, true);
        return nCount;
    }

    inline std::pair<CMasternode*, std::vector<CTxIn>> GetNextMasternodeInQueueEligible(int nBlockHeight) {
        int nCount = 0;
        std::vector<CTxIn> vEligibleTxIns;
        auto mn = GetNextMasternodeInQueueForPayment(nBlockHeight, true, nCount, vEligibleTxIns);
        return std::pair<CMasternode*, std::vector<CTxIn>>(mn, vEligibleTxIns);
    }

    /// Get the current winner for this block
    CMasternode* GetCurrentMasterNode(int mod = 1, int64_t nBlockHeight = 0);

    std::vector<CMasternode> GetFullMasternodeVector()
    {
        Check();
        // copy everything to avoid iteration problems and multithreading
        std::vector<CMasternode> result;
        {
            LOCK(cs);

            for(auto mn : vMasternodes) { 
                result.push_back(*mn);
            }
        }

        return result;
    }

    std::vector<std::pair<int, CMasternode> > GetMasternodeRanks(int64_t nBlockHeight);
    int GetMasternodeRank(const CTxIn& vin, int64_t nBlockHeight);

    void ProcessMessage(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);

    /// Return the number of (unique) Masternodes
    int size() { return vMasternodes.size(); }

    /// Return the number of Masternodes older than (default) 8000 seconds
    int stable_size ();

    std::string ToString() const;

    void Remove(CTxIn vin);

    /// Update masternode list and maps using provided CMasternodeBroadcast
    void UpdateMasternodeList(CMasternodeBroadcast mnb);
};

void ThreadCheckMasternodes();

#endif

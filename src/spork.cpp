// Copyright (c) 2014-2016 The Dash developers
// Copyright (c) 2016-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "messagesigner.h"
#include "net.h"
#include "netmessagemaker.h"
#include "spork.h"
#include "sporkdb.h"
#include <iostream>

#define MAKE_SPORK_DEF(name, defaultValue) CSporkDef(name, defaultValue, #name)

std::vector<CSporkDef> sporkDefs = {
    MAKE_SPORK_DEF(SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT,      4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_14_MIN_PROTOCOL_ACCEPTED,              4070908800ULL), // OFF

    MAKE_SPORK_DEF(SPORK_101_SERVICES_ENFORCEMENT,              4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_102_FORCE_ENABLED_MASTERNODE ,         4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_103_PING_MESSAGE_SALT,                 0),             // OFF
    MAKE_SPORK_DEF(SPORK_104_MAX_BLOCK_TIME,                    4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_105_MAX_BLOCK_SIZE,                    4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_106_STAKING_SKIP_MN_SYNC,              4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_107_IGNORE_COLLATERAL_CONFIRMATIONS,   4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_108_FORCE_MASTERNODE_MIN_AGE,          0),             // ON
    MAKE_SPORK_DEF(SPORK_109_FORCE_ENABLED_VOTED_MASTERNODE,    4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_110_FORCE_ENABLED_MASTERNODE_PAYMENT,  4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_111_ALLOW_DUPLICATE_MN_IPS,            4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_112_MASTERNODE_LAST_PAID_V2,           4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_113_RECONSIDER_WINDOW_ENFORCEMENT,     4070908800ULL), // OFF

    MAKE_SPORK_DEF(SPORK_2_NOOP,                                4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_3_NOOP,                                4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_5_NOOP,                                4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_7_NOOP,                                4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_9_NOOP,                                4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_10_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_11_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_12_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_13_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_15_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_16_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_17_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_18_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_19_NOOP,                               4070908800ULL), // OFF
    MAKE_SPORK_DEF(SPORK_111_NOOP,                              4070908800ULL), // OFF
};

CSporkManager sporkManager;
std::map<uint256, CSporkMessage> mapSporks;

CSporkManager::CSporkManager()
{
    for (auto& sporkDef : sporkDefs) {
        sporkDefsById.emplace(sporkDef.sporkId, &sporkDef);
        sporkDefsByName.emplace(sporkDef.name, &sporkDef);
    }
}

void CSporkManager::Clear()
{
    strMasterPrivKey = "";
    mapSporksActive.clear();
}

// Kyanite: on startup load spork values from previous session if they exist in the sporkDB
void CSporkManager::LoadSporksFromDB()
{
    for (const auto& sporkDef : sporkDefs) {
        // attempt to read spork from sporkDB
        CSporkMessage spork;
        if (!pSporkDB->ReadSpork(sporkDef.sporkId, spork)) {
            LogPrintf("%s : no previous value for %s found in database\n", __func__, sporkDef.name);
            continue;
        }

        // add spork to memory
        mapSporks[spork.GetHash()] = spork;
        mapSporksActive[spork.nSporkID] = spork;
        std::time_t result = spork.nValue;
        // If SPORK Value is greater than 1,000,000 assume it's actually a Date and then convert to a more readable format
        std::string sporkName = sporkManager.GetSporkNameByID(spork.nSporkID);
        if (spork.nValue > 1000000) {
            char* res = std::ctime(&result);
            LogPrintf("%s : loaded spork %s with value %d : %s\n", __func__, sporkName.c_str(), spork.nValue,
                      ((res) ? res : "no time") );
        } else {
            LogPrintf("%s : loaded spork %s with value %d\n", __func__,
                      sporkName, spork.nValue);
        }
    }
}

void CSporkManager::ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv)
{
    if (fLiteMode) return; // disable all masternode related functionality

    if (strCommand == NetMsgType::SPORK) {
        CSporkMessage spork;
        vRecv >> spork;

        // Ignore spork messages about unknown/deleted sporks
        std::string strSpork = sporkManager.GetSporkNameByID(spork.nSporkID);
        if (strSpork == "Unknown") return;

        // Do not accept sporks signed way too far into the future
        if (spork.nTimeSigned > GetAdjustedTime() + 2 * 60 * 60) {
            LOCK(cs_main);
            LogPrintf("%s : ERROR: too far into the future\n", __func__);
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        if (Params().GetConsensus().NetworkUpgradeActive(chainActive.Tip()->nHeight, Consensus::UPGRADE_TIME_PROTOCOL_V2) &&
            spork.nMessVersion != MessageVersion::MESS_VER_HASH) {
            LogPrintf("%s : nMessVersion=%d not accepted anymore\n", __func__, spork.nMessVersion);
            return;
        }

        uint256 hash = spork.GetHash();
        std::string sporkName = sporkManager.GetSporkNameByID(spork.nSporkID);
        {
            LOCK(cs);
            if (mapSporksActive.count(spork.nSporkID)) {
                // spork is active
                if (mapSporksActive[spork.nSporkID].nTimeSigned > spork.nTimeSigned) {
                    // spork in memory has been signed more recently
                    LogPrintf("%s : spork %d (%s) in memory is more recent: %d >= %d\n", __func__,
                            spork.nSporkID, sporkName,
                            mapSporksActive[spork.nSporkID].nTimeSigned, spork.nTimeSigned);
                    return;
                } else if(mapSporksActive[spork.nSporkID].nTimeSigned == spork.nTimeSigned) {
                    // nothing to do
                    return;
                } else {
                    // update active spork
                    LogPrintf("%s : got updated spork %d (%s) with value %d (signed at %d) \n", __func__,
                            spork.nSporkID, sporkName, spork.nValue, spork.nTimeSigned);
                }
            } else {
                // spork is not active
                LogPrintf("%s : got new spork %d (%s) with value %d (signed at %d) \n", __func__,
                        spork.nSporkID, sporkName, spork.nValue, spork.nTimeSigned);
            }
        }

        const bool fRequireNew = spork.nTimeSigned >= Params().GetConsensus().nTime_EnforceNewSporkKey;
        bool fValidSig = spork.CheckSignature();
        if (!fValidSig && !fRequireNew) {
            // See if window is open that allows for old spork key to sign messages
            if (GetAdjustedTime() < Params().GetConsensus().nTime_RejectOldSporkKey) {
                CPubKey pubkeyold = spork.GetPublicKeyOld();
                fValidSig = spork.CheckSignature(pubkeyold);
            }
        }

        if (!fValidSig) {
            LOCK(cs_main);
            LogPrintf("%s : Invalid Signature\n", __func__);
            Misbehaving(pfrom->GetId(), 100);
            return;
        }

        {
            LOCK(cs);
            mapSporks[hash] = spork;
            mapSporksActive[spork.nSporkID] = spork;
        }
        spork.Relay();

        // Kyanite: add to spork database.
        pSporkDB->WriteSpork(spork.nSporkID, spork);
    }
    if (strCommand == NetMsgType::GETSPORKS) {
        LOCK(cs);
        std::map<SporkId, CSporkMessage>::iterator it = mapSporksActive.begin();

        while (it != mapSporksActive.end()) {
            g_connman->PushMessage(pfrom, CNetMsgMaker(pfrom->GetSendVersion()).Make(NetMsgType::SPORK, it->second));
            it++;
        }
    }
}

bool CSporkManager::UpdateSpork(SporkId nSporkID, int64_t nValue)
{
    CSporkMessage spork = CSporkMessage(nSporkID, nValue, GetTime());

    if(spork.Sign(strMasterPrivKey)){
        spork.Relay();
        LOCK(cs);
        mapSporks[spork.GetHash()] = spork;
        mapSporksActive[nSporkID] = spork;
        return true;
    }

    return false;
}

// grab the spork value, and see if it's off
bool CSporkManager::IsSporkActive(SporkId nSporkID)
{
    return GetSporkValue(nSporkID) < GetAdjustedTime();
}

// grab the value of the spork on the network, or the default
int64_t CSporkManager::GetSporkValue(SporkId nSporkID)
{
    LOCK(cs);

    if (mapSporksActive.count(nSporkID)) {
        return mapSporksActive[nSporkID].nValue;

    } else {
        auto it = sporkDefsById.find(nSporkID);
        if (it != sporkDefsById.end()) {
            return it->second->defaultValue;
        } else {
            LogPrintf("%s : Unknown Spork %d\n", __func__, nSporkID);
        }
    }

    return -1;
}

SporkId CSporkManager::GetSporkIDByName(std::string strName)
{
    auto it = sporkDefsByName.find(strName);
    if (it == sporkDefsByName.end()) {
        LogPrintf("%s : Unknown Spork name '%s'\n", __func__, strName);
        return SPORK_INVALID;
    }
    return it->second->sporkId;
}

std::string CSporkManager::GetSporkNameByID(SporkId nSporkID)
{
    auto it = sporkDefsById.find(nSporkID);
    if (it == sporkDefsById.end()) {
        LogPrintf("%s : Unknown Spork ID %d\n", __func__, nSporkID);
        return "Unknown";
    }
    return it->second->name;
}

bool CSporkManager::SetPrivKey(std::string strPrivKey)
{
    CSporkMessage spork;

    spork.Sign(strPrivKey);

    const bool fRequireNew = GetTime() >= Params().GetConsensus().nTime_EnforceNewSporkKey;
    bool fValidSig = spork.CheckSignature();
    if (!fValidSig && !fRequireNew) {
        // See if window is open that allows for old spork key to sign messages
        if (GetAdjustedTime() < Params().GetConsensus().nTime_RejectOldSporkKey) {
            CPubKey pubkeyold = spork.GetPublicKeyOld();
            fValidSig = spork.CheckSignature(pubkeyold);
        }
    }
    if (fValidSig) {
        LOCK(cs);
        // Test signing successful, proceed
        LogPrintf("%s : Successfully initialized as spork signer\n", __func__);
        strMasterPrivKey = strPrivKey;
        return true;
    }

    return false;
}

std::string CSporkManager::ToString() const
{
    LOCK(cs);
    return strprintf("Sporks: %llu", mapSporksActive.size());
}

uint256 CSporkMessage::GetSignatureHash() const
{
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << nMessVersion;
    ss << nSporkID;
    ss << nValue;
    ss << nTimeSigned;
    return ss.GetHash();
}

std::string CSporkMessage::GetStrMessage() const
{
    return std::to_string(nSporkID) +
            std::to_string(nValue) +
            std::to_string(nTimeSigned);
}

const CPubKey CSporkMessage::GetPublicKey(std::string& strErrorRet) const
{
    return CPubKey(ParseHex(Params().GetConsensus().strSporkPubKey));
}

const CPubKey CSporkMessage::GetPublicKeyOld() const
{
    return CPubKey(ParseHex(Params().GetConsensus().strSporkPubKeyOld));
}

void CSporkMessage::Relay()
{
    CInv inv(MSG_SPORK, GetHash());
    g_connman->RelayInv(inv);
}


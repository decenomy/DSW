// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "masternode.h"

#include "addrman.h"
#include "init.h"
#include "masternode-payments.h"
#include "masternode-sync.h"
#include "masternodeman.h"
#include "netbase.h"
#include "spork.h"
#include "sync.h"
#include "util.h"
#include "wallet/wallet.h"

// keep track of the scanning errors I've seen
std::map<uint256, int> mapSeenMasternodeScanningErrors;
// cache block hashes as we calculate them
std::map<int64_t, uint256> mapCacheBlockHashes;
// cache collaterals
std::vector<std::pair<int,CAmount>> vecCollaterals;

//Get the last hash that matches the modulus given. Processed in reverse order
bool GetBlockHash(uint256& hash, int nBlockHeight)
{
    const CBlockIndex* tipIndex = GetChainTip();
    if (!tipIndex || !tipIndex->nHeight) return false;

    if (nBlockHeight == 0)
        nBlockHeight = tipIndex->nHeight;

    if (mapCacheBlockHashes.count(nBlockHeight)) {
        hash = mapCacheBlockHashes[nBlockHeight];
        return true;
    }

    int nBlocksAgo = 0;
    if (nBlockHeight > 0) nBlocksAgo = (tipIndex->nHeight + 1) - nBlockHeight;
    if (nBlocksAgo < 0) return false;

    const CBlockIndex* BlockReading = tipIndex;
    int n = 0;
    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (n >= nBlocksAgo) {
            hash = BlockReading->GetBlockHash();
            mapCacheBlockHashes[nBlockHeight] = hash;
            return true;
        }
        n++;

        if (BlockReading->pprev == NULL) {
            assert(BlockReading);
            break;
        }
        BlockReading = BlockReading->pprev;
    }

    return false;
}

CMasternode::CMasternode() :
        CSignedMessage()
{
    LOCK(cs);
    vin = CTxIn();
    addr = CService();
    pubKeyCollateralAddress = CPubKey();
    pubKeyMasternode = CPubKey();
    activeState = MASTERNODE_ENABLED;
    sigTime = GetAdjustedTime();
    lastPing = CMasternodePing();
    unitTest = false;
    allowFreeTx = true;
    protocolVersion = PROTOCOL_VERSION;
    nLastDsq = 0;
    nScanningErrorCount = 0;
    nLastScanningErrorBlockHeight = 0;
    lastTimeChecked = 0;
}

CMasternode::CMasternode(const CMasternode& other) :
        CSignedMessage(other)
{
    LOCK(cs);
    vin = other.vin;
    addr = other.addr;
    pubKeyCollateralAddress = other.pubKeyCollateralAddress;
    pubKeyMasternode = other.pubKeyMasternode;
    activeState = other.activeState;
    sigTime = other.sigTime;
    lastPing = other.lastPing;
    unitTest = other.unitTest;
    allowFreeTx = other.allowFreeTx;
    protocolVersion = other.protocolVersion;
    nLastDsq = other.nLastDsq;
    nScanningErrorCount = other.nScanningErrorCount;
    nLastScanningErrorBlockHeight = other.nLastScanningErrorBlockHeight;
    lastTimeChecked = 0;
}

uint256 CMasternode::GetSignatureHash() const
{
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << nMessVersion;
    ss << addr;
    ss << sigTime;
    ss << pubKeyCollateralAddress;
    ss << pubKeyMasternode;
    ss << protocolVersion;
    return ss.GetHash();
}

std::string CMasternode::GetStrMessage() const
{
    return (addr.ToString() +
            std::to_string(sigTime) +
            pubKeyCollateralAddress.GetID().ToString() +
            pubKeyMasternode.GetID().ToString() +
            std::to_string(protocolVersion)
    );
}

//
// When a new masternode broadcast is sent, update our information
//
bool CMasternode::UpdateFromNewBroadcast(CMasternodeBroadcast& mnb)
{
    if (mnb.sigTime > sigTime) {
        pubKeyMasternode = mnb.pubKeyMasternode;
        pubKeyCollateralAddress = mnb.pubKeyCollateralAddress;
        sigTime = mnb.sigTime;
        vchSig = mnb.vchSig;
        protocolVersion = mnb.protocolVersion;
        addr = mnb.addr;
        lastTimeChecked = 0;
        int nDoS = 0;
        if (mnb.lastPing.IsNull() || (!mnb.lastPing.IsNull() && mnb.lastPing.CheckAndUpdate(nDoS, false))) {
            lastPing = mnb.lastPing;
            mnodeman.mapSeenMasternodePing.insert(std::make_pair(lastPing.GetHash(), lastPing));
        }
        return true;
    }
    return false;
}

//
// Deterministically calculate a given "score" for a Masternode depending on how close it's hash is to
// the proof of work for that block. The further away they are the better, the furthest will win the election
// and get paid this block
//
uint256 CMasternode::CalculateScore(int mod, int64_t nBlockHeight)
{
    {
        LOCK(cs_main);
        if (!chainActive.Tip()) return UINT256_ZERO;
    }

    uint256 hash;
    uint256 aux = vin.prevout.hash + vin.prevout.n;

    if (!GetBlockHash(hash, nBlockHeight)) {
        LogPrint(BCLog::MASTERNODE,"CalculateScore ERROR - nHeight %d - Returned 0\n", nBlockHeight);
        return UINT256_ZERO;
    }

    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << hash;
    uint256 hash2 = ss.GetHash();

    CHashWriter ss2(SER_GETHASH, PROTOCOL_VERSION);
    ss2 << hash;
    ss2 << aux;
    uint256 hash3 = ss2.GetHash();

    uint256 r = (hash3 > hash2 ? hash3 - hash2 : hash2 - hash3);

    return r;
}

void CMasternode::Check(bool forceCheck)
{
    if (ShutdownRequested()) return;

    // todo: add LOCK(cs) but be careful with the AcceptableInputs() below that requires cs_main.

    if (!forceCheck && (GetTime() - lastTimeChecked < MASTERNODE_CHECK_SECONDS)) return;
    lastTimeChecked = GetTime();


    //once spent, stop doing the checks
    if (activeState == MASTERNODE_VIN_SPENT) return;


    if (!IsPingedWithin(MASTERNODE_REMOVAL_SECONDS)) {
        activeState = MASTERNODE_REMOVE;
        return;
    }

    if (!IsPingedWithin(MASTERNODE_EXPIRATION_SECONDS)) {
        activeState = MASTERNODE_EXPIRED;
        return;
    }

    if(lastPing.sigTime - sigTime < MASTERNODE_MIN_MNP_SECONDS){
        activeState = MASTERNODE_PRE_ENABLED;
        return;
    }

    if (!unitTest) {
        CValidationState state;
        CMutableTransaction tx = CMutableTransaction();
        CScript dummyScript;
        dummyScript << ToByteVector(pubKeyCollateralAddress) << OP_CHECKSIG;
        CTxOut vout = CTxOut((CMasternode::GetMasternodeNodeCollateral(chainActive.Height()) - 0.01 * COIN), dummyScript);
        tx.vin.push_back(vin);
        tx.vout.push_back(vout);
        {
            TRY_LOCK(cs_main, lockMain);
            if (!lockMain) return;

            if (!AcceptableInputs(mempool, state, CTransaction(tx), false, NULL)) {
                activeState = MASTERNODE_VIN_SPENT;
                return;
            }
        }
    }

    activeState = MASTERNODE_ENABLED; // OK
}

int64_t CMasternode::SecondsSincePayment()
{
    CScript pubkeyScript;
    pubkeyScript = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    int64_t sec = (GetAdjustedTime() - GetLastPaid());
    int64_t month = 60 * 60 * 24 * 30;
    if (sec < month) return sec; //if it's less than 30 days, give seconds

    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << vin;
    ss << sigTime;
    uint256 hash = ss.GetHash();

    // return some deterministic value for unknown/unpaid but force it to be more than 30 days old
    return month + hash.GetCompact(false);
}

int64_t CMasternode::GetLastPaid()
{
    const CBlockIndex* BlockReading = GetChainTip();
    if (BlockReading == nullptr) return false;

    CScript mnpayee;
    mnpayee = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << vin;
    ss << sigTime;
    uint256 hash = ss.GetHash();

    // use a deterministic offset to break a tie -- 2.5 minutes
    int64_t nOffset = hash.GetCompact(false) % 150;

    int nMnCount = mnodeman.CountEnabled() * 1.25;
    int n = 0;
    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (n >= nMnCount) {
            return 0;
        }
        n++;

        if (masternodePayments.mapMasternodeBlocks.count(BlockReading->nHeight)) {
            /*
                Search for this payee, with at least 2 votes. This will aid in consensus allowing the network
                to converge on the same payees quickly, then keep the same schedule.
            */
            if (masternodePayments.mapMasternodeBlocks[BlockReading->nHeight].HasPayeeWithVotes(mnpayee, 2)) {
                return BlockReading->nTime + nOffset;
            }
        }

        if (BlockReading->pprev == NULL) {
            assert(BlockReading);
            break;
        }
        BlockReading = BlockReading->pprev;
    }

    return 0;
}

bool CMasternode::IsValidNetAddr()
{
    // TODO: regtest is fine with any addresses for now,
    // should probably be a bit smarter if one day we start to implement tests for this
    return Params().IsRegTestNet() ||
           (IsReachable(addr) && addr.IsRoutable());
}

bool CMasternode::IsInputAssociatedWithPubkey() const
{
    CScript payee;
    payee = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    CTransaction txVin;
    uint256 hash;
    if(GetTransaction(vin.prevout.hash, txVin, hash, true)) {
        for (CTxOut out : txVin.vout) {
            if (out.nValue == CMasternode::GetMasternodeNodeCollateral(chainActive.Height()) && out.scriptPubKey == payee) return true;
        }
    }

    return false;
}

CAmount CMasternode::GetMasternodeNodeCollateral(int nHeight) 
    if (nHeight < 50000 && nHeight >= 0) {
        return 10000 * COIN;
    }
    else if (nHeight <= 99999 && nHeight >= 50000) {
        return 15000 * COIN;
    }
    else if (nHeight <= 149999 && nHeight >= 100000) {
        return 20000 * COIN;
    }
    else if (nHeight <= 199999 && nHeight >= 150000) {
        return 25000 * COIN;
    }
    else if (nHeight <= 249999 && nHeight >= 200000) {
        return 30000 * COIN;
    }
    else if (nHeight <= 499999 && nHeight >= 250000) {
        return 40000 * COIN;
    }
    else if (nHeight >= 500000) {
        return 50000 * COIN;
    }

    return 0;

CAmount CMasternode::GetBlockValue(int nHeight)
{
    CAmount maxMoneyOut= Params().GetConsensus().nMaxMoneyOut;

    if(nMoneySupply >= maxMoneyOut) {
        return 0;
    }

    CAmount nSubsidy;

    if (nHeight == 0) {
        nSubsidy = 6000000 * COIN;
    }
    else if (nHeight < 20000 && nHeight > 0) {
        nSubsidy = 30 * COIN;
    }
    else if (nHeight <= 29999 && nHeight >= 20000) {
        nSubsidy = 40 * COIN;
    }
    else if (nHeight <= 39999 && nHeight >= 30000) {
        nSubsidy = 60 * COIN;
    }
    else if (nHeight <= 49999 && nHeight >= 40000) {
        nSubsidy = 80 * COIN;
    }
    else if (nHeight <= 59999 && nHeight >= 50000) {
        nSubsidy = 100 * COIN;
    }
    else if (nHeight <= 69999 && nHeight >= 60000) {
        nSubsidy = 120 * COIN;
    }
    else if (nHeight <= 79999 && nHeight >= 70000) {
        nSubsidy = 140 * COIN;
    }
    else if (nHeight <= 89999 && nHeight >= 80000) {
        nSubsidy = 160 * COIN;
    }
    else if (nHeight <= 99999 && nHeight >= 90000) {
        nSubsidy = 180 * COIN;
    }
    else if (nHeight <= 109999 && nHeight >= 100000) {
        nSubsidy = 200 * COIN;
    }
    else if (nHeight <= 119999 && nHeight >= 110000) {
        nSubsidy = 220 * COIN;
    }
    else if (nHeight <= 129999 && nHeight >= 120000) {
        nSubsidy = 240 * COIN;
    }
    else if (nHeight <= 139999 && nHeight >= 130000) {
        nSubsidy = 260 * COIN;
    }
    else if (nHeight <= 149999 && nHeight >= 140000) {
        nSubsidy = 250 * COIN;
    }
    else if (nHeight <= 159999 && nHeight >= 150000) {
        nSubsidy = 240 * COIN;
    }
    else if (nHeight <= 169999 && nHeight >= 160000) {
        nSubsidy = 230 * COIN;
    }
    else if (nHeight <= 179999 && nHeight >= 170000) {
        nSubsidy = 220 * COIN;
    }
    else if (nHeight <= 189999 && nHeight >= 180000) {
        nSubsidy = 210 * COIN;
    }
    else if (nHeight <= 199999 && nHeight >= 190000) {
        nSubsidy = 200 * COIN;
    }
    else if (nHeight <= 209999 && nHeight >= 200000) {
        nSubsidy = 190 * COIN;
    }
    else if (nHeight <= 219999 && nHeight >= 210000) {
        nSubsidy = 180 * COIN;
    }
    else if (nHeight <= 229999 && nHeight >= 220000) {
        nSubsidy = 170 * COIN;
    }
    else if (nHeight <= 239999 && nHeight >= 230000) {
        nSubsidy = 160 * COIN;
    }
    else if (nHeight <= 249999 && nHeight >= 240000) {
        nSubsidy = 150 * COIN;
    }
    else if (nHeight <= 259999 && nHeight >= 250000) {
        nSubsidy = 140 * COIN;
    }
    else if (nHeight <= 269999 && nHeight >= 260000) {
        nSubsidy = 130 * COIN;
    }
    else if (nHeight <= 279999 && nHeight >= 270000) {
        nSubsidy = 120 * COIN;
    }
    else if (nHeight <= 289999 && nHeight >= 280000) {
        nSubsidy = 110 * COIN;
    }
    else if (nHeight <= 299999 && nHeight >= 290000) {
        nSubsidy = 108 * COIN;
    }
    else if (nHeight <= 309999 && nHeight >= 300000) {
        nSubsidy = 106 * COIN;
    }
    else if (nHeight <= 319999 && nHeight >= 310000) {
        nSubsidy = 104 * COIN;
    }
    else if (nHeight <= 329999 && nHeight >= 320000) {
        nSubsidy = 102 * COIN;
    }
    else if (nHeight <= 339999 && nHeight >= 330000) {
        nSubsidy = 100 * COIN;
    }
    else if (nHeight <= 349999 && nHeight >= 340000) {
        nSubsidy = 98 * COIN;
    }
    else if (nHeight <= 359999 && nHeight >= 350000) {
        nSubsidy = 96 * COIN;
    }
    else if (nHeight <= 369999 && nHeight >= 360000) {
        nSubsidy = 94 * COIN;
    }
    else if (nHeight <= 379999 && nHeight >= 370000) {
        nSubsidy = 92 * COIN;
    }
    else if (nHeight <= 389999 && nHeight >= 380000) {
        nSubsidy = 90 * COIN;
    }
    else if (nHeight <= 399999 && nHeight >= 390000) {
        nSubsidy = 88 * COIN;
    }
    else if (nHeight <= 409999 && nHeight >= 400000) {
        nSubsidy = 86 * COIN;
    }
    else if (nHeight <= 419999 && nHeight >= 410000) {
        nSubsidy = 84 * COIN;
    }
    else if (nHeight <= 429999 && nHeight >= 420000) {
        nSubsidy = 82 * COIN;
    }
    else if (nHeight <= 439999 && nHeight >= 430000) {
        nSubsidy = 80 * COIN;
    }
    else if (nHeight <= 449999 && nHeight >= 440000) {
        nSubsidy = 78 * COIN;
    }
    else if (nHeight <= 459999 && nHeight >= 450000) {
        nSubsidy = 76 * COIN;
    }
    else if (nHeight <= 469999 && nHeight >= 460000) {
        nSubsidy = 74 * COIN;
    }
    else if (nHeight <= 479999 && nHeight >= 470000) {
        nSubsidy = 72 * COIN;
    }
    else if (nHeight <= 489999 && nHeight >= 480000) {
        nSubsidy = 70 * COIN;
    }
    else if (nHeight <= 499999 && nHeight >= 490000) {
        nSubsidy = 68 * COIN;
    }
    else {
        nSubsidy = 60 * COIN;
        if (nHeight >= 800888) {
           if (nHeight <= 870500-1 && nHeight >= 500000) {
                nSubsidy = 30 * COIN;
           } else if (nHeight <= 1000000-1 && nHeight >= 870500) {
                nSubsidy = 15 * COIN;
           } else if (nHeight <= 1200000-1 && nHeight >= 1000000) {
                nSubsidy = 8 * COIN;
           } else {
                nSubsidy = 4 * COIN;
           }
        }
    }
    return nSubsidy;
}

CAmount CMasternode::GetMasternodePayment(int nHeight)
{
    if(nHeight <= 5000) return 0;

    return CMasternode::GetBlockValue(nHeight) * 90 / 100;
}

void CMasternode::InitMasternodeCollateralList() {
    CAmount prev = -1; 
    for(int i = 0; i < 9999999; i++) {
        CAmount c = GetMasternodeNodeCollateral(i);
        if(prev != c) {
            LogPrint(BCLog::MASTERNODE, "%s: Found collateral %d at block %d\n", __func__, c / COIN, i); 
            prev = c;
            vecCollaterals.push_back(std::make_pair(i, c));
        }
    }
}

std::pair<int, CAmount> CMasternode::GetNextMasternodeCollateral(int nHeight) {
    for(auto p : vecCollaterals) {
        if(p.first > nHeight) {
            return std::make_pair(p.first - nHeight, p.second);
        }
    }
    return std::make_pair(-1, -1);
}

CMasternodeBroadcast::CMasternodeBroadcast() :
        CMasternode()
{ }

CMasternodeBroadcast::CMasternodeBroadcast(CService newAddr, CTxIn newVin, CPubKey pubKeyCollateralAddressNew, CPubKey pubKeyMasternodeNew, int protocolVersionIn) :
        CMasternode()
{
    vin = newVin;
    addr = newAddr;
    pubKeyCollateralAddress = pubKeyCollateralAddressNew;
    pubKeyMasternode = pubKeyMasternodeNew;
    protocolVersion = protocolVersionIn;
}

CMasternodeBroadcast::CMasternodeBroadcast(const CMasternode& mn) :
        CMasternode(mn)
{ }

bool CMasternodeBroadcast::Create(std::string strService, std::string strKeyMasternode, std::string strTxHash, std::string strOutputIndex, std::string& strErrorRet, CMasternodeBroadcast& mnbRet, bool fOffline)
{
    CTxIn txin;
    CPubKey pubKeyCollateralAddressNew;
    CKey keyCollateralAddressNew;
    CPubKey pubKeyMasternodeNew;
    CKey keyMasternodeNew;

    //need correct blocks to send ping
    if (!fOffline && !masternodeSync.IsBlockchainSynced()) {
        strErrorRet = "Sync in progress. Must wait until sync is complete to start Masternode";
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        return false;
    }

    if (!CMessageSigner::GetKeysFromSecret(strKeyMasternode, keyMasternodeNew, pubKeyMasternodeNew)) {
        strErrorRet = strprintf("Invalid masternode key %s", strKeyMasternode);
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        return false;
    }

    std::string strError;
    if (!pwalletMain->GetMasternodeVinAndKeys(txin, pubKeyCollateralAddressNew, keyCollateralAddressNew, strTxHash, strOutputIndex, strError)) {
        strErrorRet = strError; // GetMasternodeVinAndKeys logs this error. Only returned for GUI error notification.
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strprintf("Could not allocate txin %s:%s for masternode %s", strTxHash, strOutputIndex, strService));
        return false;
    }

    int nPort;
    int nDefaultPort = Params().GetDefaultPort();
    std::string strHost;
    SplitHostPort(strService, nPort, strHost);
    if (nPort == 0) nPort = nDefaultPort;
    CService _service(LookupNumeric(strHost.c_str(), nPort));

    // The service needs the correct default port to work properly
    if (!CheckDefaultPort(_service, strErrorRet, "CMasternodeBroadcast::Create"))
        return false;

    return Create(txin, _service, keyCollateralAddressNew, pubKeyCollateralAddressNew, keyMasternodeNew, pubKeyMasternodeNew, strErrorRet, mnbRet);
}

bool CMasternodeBroadcast::Create(CTxIn txin, CService service, CKey keyCollateralAddressNew, CPubKey pubKeyCollateralAddressNew, CKey keyMasternodeNew, CPubKey pubKeyMasternodeNew, std::string& strErrorRet, CMasternodeBroadcast& mnbRet)
{
    // wait for reindex and/or import to finish
    if (fImporting || fReindex) return false;

    LogPrint(BCLog::MASTERNODE, "CMasternodeBroadcast::Create -- pubKeyCollateralAddressNew = %s, pubKeyMasternodeNew.GetID() = %s\n",
             EncodeDestination(pubKeyCollateralAddressNew.GetID()),
        pubKeyMasternodeNew.GetID().ToString());

    CMasternodePing mnp(txin);
    if (!mnp.Sign(keyMasternodeNew, pubKeyMasternodeNew)) {
        strErrorRet = strprintf("Failed to sign ping, masternode=%s", txin.prevout.hash.ToString());
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        mnbRet = CMasternodeBroadcast();
        return false;
    }

    mnbRet = CMasternodeBroadcast(service, txin, pubKeyCollateralAddressNew, pubKeyMasternodeNew, PROTOCOL_VERSION);

    if (!mnbRet.IsValidNetAddr()) {
        strErrorRet = strprintf("Invalid IP address %s, masternode=%s", mnbRet.addr.ToStringIP (), txin.prevout.hash.ToString());
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        mnbRet = CMasternodeBroadcast();
        return false;
    }

    mnbRet.lastPing = mnp;
    if (!mnbRet.Sign(keyCollateralAddressNew, pubKeyCollateralAddressNew)) {
        strErrorRet = strprintf("Failed to sign broadcast, masternode=%s", txin.prevout.hash.ToString());
        LogPrint(BCLog::MASTERNODE,"CMasternodeBroadcast::Create -- %s\n", strErrorRet);
        mnbRet = CMasternodeBroadcast();
        return false;
    }

    return true;
}

bool CMasternodeBroadcast::Sign(const CKey& key, const CPubKey& pubKey)
{
    sigTime = GetAdjustedTime();

    std::string strError = "";
    std::string strMessage;

    if(Params().GetConsensus().NetworkUpgradeActive(chainActive.Height(), Consensus::UPGRADE_STAKE_MODIFIER_V2)) {
        nMessVersion = MessageVersion::MESS_VER_HASH;
        strMessage = GetSignatureHash().GetHex();

        if (!CMessageSigner::SignMessage(strMessage, vchSig, key)) {
            return error("%s : SignMessage() (nMessVersion=%d) failed", __func__, nMessVersion);
        }

        if (!CMessageSigner::VerifyMessage(pubKey, vchSig, strMessage, strError)) {
            return error("%s : VerifyMessage() (nMessVersion=%d) failed, error: %s\n",
                    __func__, nMessVersion, strError);
        }

        return true;
    } else {
        nMessVersion = MessageVersion::MESS_VER_STRMESS;
        strMessage = GetOldStrMessage();

        CHashWriter ss(SER_GETHASH, 0);
        ss << strMessageMagic;
        ss << strMessage;

        if (!key.SignCompact(ss.GetHash(), vchSig)) {
            return error("%s : VerifyMessage() (nMessVersion=%d) failed, error: Signing failed.\n",
                    __func__, nMessVersion);
        }

        return true;
    }
}

bool CMasternodeBroadcast::Sign(const std::string strSignKey)
{
    CKey key;
    CPubKey pubkey;

    if (!CMessageSigner::GetKeysFromSecret(strSignKey, key, pubkey)) {
        return error("%s : Invalid strSignKey", __func__);
    }

    return Sign(key, pubkey);
}

std::string CMasternodeBroadcast::GetOldStrMessage() const
{
    std::string strMessage;

    std::string vchPubKey(pubKeyCollateralAddress.begin(), pubKeyCollateralAddress.end());
    std::string vchPubKey2(pubKeyMasternode.begin(), pubKeyMasternode.end());
    strMessage = addr.ToString() + std::to_string(sigTime) + vchPubKey + vchPubKey2 + std::to_string(protocolVersion);

    return strMessage;
}

bool CMasternodeBroadcast::CheckSignature() const
{
    std::string strError = "";
    std::string strMessage = (nMessVersion == MessageVersion::MESS_VER_HASH ?
                                  GetSignatureHash().GetHex() :
                                  GetStrMessage());
    std::string oldStrMessage = (nMessVersion == MessageVersion::MESS_VER_HASH ?
                                     GetSignatureHash().GetHex() :
                                     GetOldStrMessage());

    if (!CMessageSigner::VerifyMessage(pubKeyCollateralAddress, vchSig, oldStrMessage, strError) &&
        !CMessageSigner::VerifyMessage(pubKeyCollateralAddress, vchSig, strMessage, strError))
        return error("%s : VerifyMessage (nMessVersion=%d) failed: %s", __func__, nMessVersion, strError);

    return true;
}

bool CMasternodeBroadcast::CheckDefaultPort(CService service, std::string& strErrorRet, const std::string& strContext)
{
    int nDefaultPort = Params().GetDefaultPort();

    if (service.GetPort() != nDefaultPort) {
        strErrorRet = strprintf("Invalid port %u for masternode %s, only %d is supported on %s-net.",
            service.GetPort(), service.ToString(), nDefaultPort, Params().NetworkIDString());
        LogPrint(BCLog::MASTERNODE, "%s - %s\n", strContext, strErrorRet);
        return false;
    }

    return true;
}

bool CMasternodeBroadcast::CheckAndUpdate(int& nDos)
{
    // make sure signature isn't in the future (past is OK)
    if (sigTime > GetAdjustedTime() + 60 * 60) {
        LogPrint(BCLog::MASTERNODE, "mnb - Signature rejected, too far into the future %s\n", vin.prevout.ToStringShort());
        nDos = 1;
        return false;
    }

    // incorrect ping or its sigTime
    if(lastPing.IsNull() || !lastPing.CheckAndUpdate(nDos, false, true))
    return false;

    if (protocolVersion < ActiveProtocol()) {
        LogPrint(BCLog::MASTERNODE, "mnb - ignoring outdated Masternode %s protocol version %d\n", vin.prevout.ToStringShort(), protocolVersion);
        return false;
    }

    CScript pubkeyScript;
    pubkeyScript = GetScriptForDestination(pubKeyCollateralAddress.GetID());

    if (pubkeyScript.size() != 25) {
        LogPrint(BCLog::MASTERNODE,"mnb - pubkey the wrong size\n");
        nDos = 100;
        return false;
    }

    CScript pubkeyScript2;
    pubkeyScript2 = GetScriptForDestination(pubKeyMasternode.GetID());

    if (pubkeyScript2.size() != 25) {
        LogPrint(BCLog::MASTERNODE,"mnb - pubkey2 the wrong size\n");
        nDos = 100;
        return false;
    }

    if (!vin.scriptSig.empty()) {
        LogPrint(BCLog::MASTERNODE, "mnb - Ignore Not Empty ScriptSig %s\n", vin.prevout.ToStringShort());
        return false;
    }

    std::string strError = "";
    if (!CheckSignature())
    {
        // masternodes older than this proto version use old strMessage format for mnannounce
        nDos = protocolVersion <= MIN_PEER_MNANNOUNCE ? 0 : 100;
        return error("%s : Got bad Masternode address signature", __func__);
    }

    if(addr.GetPort() != Params().GetDefaultPort()) {
        return error(
            "%s : Invalid port %u for masternode %s, only %d is supported on %s-net.", 
            __func__, addr.GetPort(), addr.ToString(), Params().GetDefaultPort(), 
            Params().NetworkIDString());
    }

    //search existing Masternode list, this is where we update existing Masternodes with new mnb broadcasts
    CMasternode* pmn = mnodeman.Find(vin);

    // no such masternode, nothing to update
    if (pmn == NULL) return true;

    // this broadcast is older or equal than the one that we already have - it's bad and should never happen
    // unless someone is doing something fishy
    // (mapSeenMasternodeBroadcast in CMasternodeMan::ProcessMessage should filter legit duplicates)
    if(pmn->sigTime >= sigTime) {
        return error("%s : Bad sigTime %d for Masternode %20s %105s (existing broadcast is at %d)",
                      __func__, sigTime, addr.ToString(), vin.ToString(), pmn->sigTime);
    }

    // masternode is not enabled yet/already, nothing to update
    if (!pmn->IsEnabled()) return true;

    // mn.pubkey = pubkey, IsVinAssociatedWithPubkey is validated once below,
    //   after that they just need to match
    if (pmn->pubKeyCollateralAddress == pubKeyCollateralAddress && !pmn->IsBroadcastedWithin(MASTERNODE_MIN_MNB_SECONDS)) {
        //take the newest entry
        LogPrint(BCLog::MASTERNODE, "mnb - Got updated entry for %s\n", vin.prevout.ToStringShort());
        if (pmn->UpdateFromNewBroadcast((*this))) {
            pmn->Check();
            if (pmn->IsEnabled()) Relay();
        }
        masternodeSync.AddedMasternodeList(GetHash());
    }

    return true;
}

bool CMasternodeBroadcast::CheckInputsAndAdd(int& nDoS)
{
    // we are a masternode with the same vin (i.e. already activated) and this mnb is ours (matches our Masternode privkey)
    // so nothing to do here for us
    if (fMasterNode && activeMasternode.vin != nullopt &&
            vin.prevout == activeMasternode.vin->prevout && pubKeyMasternode == activeMasternode.pubKeyMasternode)
        return true;

    // incorrect ping or its sigTime
    if(lastPing.IsNull() || !lastPing.CheckAndUpdate(nDoS, false, true)) return false;

    // search existing Masternode list
    CMasternode* pmn = mnodeman.Find(vin);

    if (pmn != NULL) {
        // nothing to do here if we already know about this masternode and it's enabled
        if (pmn->IsEnabled()) return true;
        // if it's not enabled, remove old MN first and continue
        else
            mnodeman.Remove(pmn->vin);
    }

    CValidationState state;
    CMutableTransaction tx = CMutableTransaction();
    CScript dummyScript;
    dummyScript << ToByteVector(pubKeyCollateralAddress) << OP_CHECKSIG;
    CTxOut vout = CTxOut((CMasternode::GetMasternodeNodeCollateral(chainActive.Height()) - 0.01 * COIN), dummyScript);
    tx.vin.push_back(vin);
    tx.vout.push_back(vout);

    int nChainHeight = 0;
    {
        TRY_LOCK(cs_main, lockMain);
        if (!lockMain) {
            // not mnb fault, let it to be checked again later
            mnodeman.mapSeenMasternodeBroadcast.erase(GetHash());
            masternodeSync.mapSeenSyncMNB.erase(GetHash());
            return false;
        }

        if (!AcceptableInputs(mempool, state, CTransaction(tx), false, NULL)) {
            //set nDos
            state.IsInvalid(nDoS);
            return false;
        }

        nChainHeight = chainActive.Height();
    }

    LogPrint(BCLog::MASTERNODE, "mnb - Accepted Masternode entry\n");

    if (pcoinsTip->GetCoinDepthAtHeight(vin.prevout, nChainHeight) < MASTERNODE_MIN_CONFIRMATIONS) {
        LogPrint(BCLog::MASTERNODE,"mnb - Input must have at least %d confirmations\n", MASTERNODE_MIN_CONFIRMATIONS);
        // maybe we miss few blocks, let this mnb to be checked again later
        mnodeman.mapSeenMasternodeBroadcast.erase(GetHash());
        masternodeSync.mapSeenSyncMNB.erase(GetHash());
        return false;
    }

    // verify that sig time is legit in past
    // should be at least not earlier than block when 1000 __DSW__ tx got MASTERNODE_MIN_CONFIRMATIONS
    uint256 hashBlock = UINT256_ZERO;
    CTransaction tx2;
    GetTransaction(vin.prevout.hash, tx2, hashBlock, true);
    BlockMap::iterator mi = mapBlockIndex.find(hashBlock);
    if (mi != mapBlockIndex.end() && (*mi).second) {
        CBlockIndex* pMNIndex = (*mi).second;                                                        // block for 1000 __DSW__ tx -> 1 confirmation
        CBlockIndex* pConfIndex = chainActive[pMNIndex->nHeight + MASTERNODE_MIN_CONFIRMATIONS - 1]; // block where tx got MASTERNODE_MIN_CONFIRMATIONS
        if (pConfIndex->GetBlockTime() > sigTime) {
            LogPrint(BCLog::MASTERNODE,"mnb - Bad sigTime %d for Masternode %s (%i conf block is at %d)\n",
                sigTime, vin.prevout.hash.ToString(), MASTERNODE_MIN_CONFIRMATIONS, pConfIndex->GetBlockTime());
            return false;
        }
    }

    LogPrint(BCLog::MASTERNODE, "mnb - Got NEW Masternode entry - %s - %lli \n", vin.prevout.ToStringShort(), sigTime);
    CMasternode mn(*this);
    mnodeman.Add(mn);

    // if it matches our Masternode privkey, then we've been remotely activated
    if (pubKeyMasternode == activeMasternode.pubKeyMasternode && protocolVersion == PROTOCOL_VERSION) {
        activeMasternode.EnableHotColdMasterNode(vin, addr);
    }

    bool isLocal = (addr.IsRFC1918() || addr.IsLocal()) && !Params().IsRegTestNet();

    if (!isLocal) Relay();

    return true;
}

void CMasternodeBroadcast::Relay()
{
    CInv inv(MSG_MASTERNODE_ANNOUNCE, GetHash());
    g_connman->RelayInv(inv);
}

uint256 CMasternodeBroadcast::GetHash() const
{
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << sigTime;
    ss << pubKeyCollateralAddress;
    return ss.GetHash();
}

CMasternodePing::CMasternodePing() :
        CSignedMessage(),
        vin(),
        blockHash(),
        sigTime(GetAdjustedTime())
{ }

CMasternodePing::CMasternodePing(CTxIn& newVin) :
        CSignedMessage(),
        vin(newVin),
        sigTime(GetAdjustedTime())
{
    int nHeight;
    {
        LOCK(cs_main);
        nHeight = chainActive.Height();
        if (nHeight > 12)
            blockHash = chainActive[nHeight - 12]->GetBlockHash();
    }
}

uint256 CMasternodePing::GetHash() const
{
    int64_t salt = sporkManager.GetSporkValue(SPORK_103_PING_MESSAGE_SALT);
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << vin;
    if (nMessVersion == MessageVersion::MESS_VER_HASH) ss << blockHash;
    ss << sigTime;
    if (salt > 0) ss << salt;
    return ss.GetHash();
}

std::string CMasternodePing::GetStrMessage() const
{
    int64_t salt = sporkManager.GetSporkValue(SPORK_103_PING_MESSAGE_SALT);

    if(salt == 0) {
        return vin.ToString() + blockHash.ToString() + std::to_string(sigTime);
    } else {
        return vin.ToString() + blockHash.ToString() + std::to_string(sigTime) + std::to_string(salt);
    }
}

bool CMasternodePing::CheckAndUpdate(int& nDos, bool fRequireEnabled, bool fCheckSigTimeOnly)
{
    if (sigTime > GetAdjustedTime() + 60 * 60) {
        LogPrint(BCLog::MNPING, "%s: Signature rejected, too far into the future %s\n", __func__, vin.prevout.ToStringShort());
        nDos = 1;
        return false;
    }

    if (sigTime <= GetAdjustedTime() - 60 * 60) {
        LogPrint(BCLog::MNPING, "%s: Signature rejected, too far into the past %s - %d %d \n", __func__, vin.prevout.ToStringShort(), sigTime, GetAdjustedTime());
        nDos = 1;
        return false;
    }

    // see if we have this Masternode
    CMasternode* pmn = mnodeman.Find(vin);
    const bool isMasternodeFound = (pmn != nullptr);
    const bool isSignatureValid = (isMasternodeFound && CheckSignature(pmn->pubKeyMasternode));

    if(fCheckSigTimeOnly) {
        if (isMasternodeFound && !isSignatureValid) {
            nDos = 33;
            return false;
        }
        return true;
    }

    LogPrint(BCLog::MNPING, "%s: New Ping - %s - %s - %lli\n", __func__, GetHash().ToString(), blockHash.ToString(), sigTime);

    if (isMasternodeFound && pmn->protocolVersion >= ActiveProtocol()) {
        if (fRequireEnabled && !pmn->IsEnabled()) return false;

        // update only if there is no known ping for this masternode or
        // last ping was more then MASTERNODE_MIN_MNP_SECONDS-60 ago comparing to this one
        if (!pmn->IsPingedWithin(MASTERNODE_MIN_MNP_SECONDS - 60, sigTime)) {
            if (!isSignatureValid) {
                nDos = 33;
                return false;
            }

            // Check if the ping block hash exists in disk
            BlockMap::iterator mi = mapBlockIndex.find(blockHash);
            if (mi == mapBlockIndex.end() || !(*mi).second) {
                LogPrint(BCLog::MNPING, "%s: ping block not in disk. Masternode %s block hash %s\n", __func__, vin.prevout.ToStringShort(), blockHash.ToString());
                return false;
            }

            // Verify ping block hash in main chain and in the [ tip > x > tip - 24 ] range.
            {
                LOCK(cs_main);
                if (!chainActive.Contains((*mi).second) || (chainActive.Height() - (*mi).second->nHeight > 24)) {
                    LogPrint(BCLog::MNPING,"%s: Masternode %s block hash %s is too old or has an invalid block hash\n",
                            __func__, vin.prevout.hash.ToString(), blockHash.ToString());
                    // Do nothing here (no Masternode update, no mnping relay)
                    // Let this node to be visible but fail to accept mnping
                    return false;
                }
            }

            pmn->lastPing = *this;

            //mnodeman.mapSeenMasternodeBroadcast.lastPing is probably outdated, so we'll update it
            CMasternodeBroadcast mnb(*pmn);
            uint256 hash = mnb.GetHash();
            if (mnodeman.mapSeenMasternodeBroadcast.count(hash)) {
                mnodeman.mapSeenMasternodeBroadcast[hash].lastPing = *this;
            }

            pmn->Check(true);
            if (!pmn->IsEnabled()) return false;

            LogPrint(BCLog::MNPING, "%s: Masternode ping accepted, vin: %s\n", __func__, vin.prevout.ToStringShort());

            Relay();
            return true;
        }
        LogPrint(BCLog::MNPING, "%s: Masternode ping arrived too early, vin: %s\n", __func__, vin.prevout.ToStringShort());
        //nDos = 1; //disable, this is happening frequently and causing banned peers
        return false;
    }
    LogPrint(BCLog::MNPING, "%s: Couldn't find compatible Masternode entry, vin: %s\n", __func__, vin.prevout.ToStringShort());

    return false;
}

void CMasternodePing::Relay()
{
    CInv inv(MSG_MASTERNODE_PING, GetHash());
    g_connman->RelayInv(inv);
}

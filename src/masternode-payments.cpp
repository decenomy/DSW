// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "masternode-payments.h"
#include "addrman.h"
#include "chainparams.h"
#include "fs.h"
#include "masternode-sync.h"
#include "masternodeman.h"
#include "netmessagemaker.h"
#include "spork.h"
#include "sync.h"
#include "util.h"
#include "utilmoneystr.h"
#include "core_io.h"


/** Object for who's going to get paid on which blocks */
CMasternodePayments masternodePayments;

uint64_t reconsiderWindowMin    = 0;
uint64_t reconsiderWindowTime   = 0;

RecursiveMutex cs_vecPayments;
RecursiveMutex cs_mapMasternodeBlocks;
RecursiveMutex cs_mapMasternodePayeeVotes;

//
// CMasternodePaymentDB
//

CMasternodePaymentDB::CMasternodePaymentDB()
{
    pathDB = GetDataDir() / "mnpayments.dat";
    strMagicMessage = "MasternodePayments";
}

bool CMasternodePaymentDB::Write(const CMasternodePayments& objToSave)
{
    int64_t nStart = GetTimeMillis();

    // serialize, checksum data up to that point, then append checksum
    CDataStream ssObj(SER_DISK, CLIENT_VERSION);
    ssObj << strMagicMessage;                   // masternode cache file specific magic message
    ssObj << FLATDATA(Params().MessageStart()); // network specific magic number
    ssObj << objToSave;
    uint256 hash = Hash(ssObj.begin(), ssObj.end());
    ssObj << hash;

    // open output file, and associate with CAutoFile
    FILE* file = fsbridge::fopen(pathDB, "wb");
    CAutoFile fileout(file, SER_DISK, CLIENT_VERSION);
    if (fileout.IsNull())
        return error("%s : Failed to open file %s", __func__, pathDB.string());

    // Write and commit header, data
    try {
        fileout << ssObj;
    } catch (const std::exception& e) {
        return error("%s : Serialize or I/O error - %s", __func__, e.what());
    }
    fileout.fclose();

    LogPrint(BCLog::MASTERNODE,"Written info to mnpayments.dat  %dms\n", GetTimeMillis() - nStart);

    return true;
}

CMasternodePaymentDB::ReadResult CMasternodePaymentDB::Read(CMasternodePayments& objToLoad, bool fDryRun)
{
    int64_t nStart = GetTimeMillis();
    // open input file, and associate with CAutoFile
    FILE* file = fsbridge::fopen(pathDB, "rb");
    CAutoFile filein(file, SER_DISK, CLIENT_VERSION);
    if (filein.IsNull()) {
        error("%s : Failed to open file %s", __func__, pathDB.string());
        return FileError;
    }

    // use file size to size memory buffer
    int fileSize = fs::file_size(pathDB);
    int dataSize = fileSize - sizeof(uint256);
    // Don't try to resize to a negative number if file is small
    if (dataSize < 0)
        dataSize = 0;
    std::vector<unsigned char> vchData;
    vchData.resize(dataSize);
    uint256 hashIn;

    // read data and checksum from file
    try {
        filein.read((char*)&vchData[0], dataSize);
        filein >> hashIn;
    } catch (const std::exception& e) {
        error("%s : Deserialize or I/O error - %s", __func__, e.what());
        return HashReadError;
    }
    filein.fclose();

    CDataStream ssObj(vchData, SER_DISK, CLIENT_VERSION);

    // verify stored checksum matches input data
    uint256 hashTmp = Hash(ssObj.begin(), ssObj.end());
    if (hashIn != hashTmp) {
        error("%s : Checksum mismatch, data corrupted", __func__);
        return IncorrectHash;
    }

    unsigned char pchMsgTmp[4];
    std::string strMagicMessageTmp;
    try {
        // de-serialize file header (masternode cache file specific magic message) and ..
        ssObj >> strMagicMessageTmp;

        // ... verify the message matches predefined one
        if (strMagicMessage != strMagicMessageTmp) {
            error("%s : Invalid masternode payement cache magic message", __func__);
            return IncorrectMagicMessage;
        }


        // de-serialize file header (network specific magic number) and ..
        ssObj >> FLATDATA(pchMsgTmp);

        // ... verify the network matches ours
        if (memcmp(pchMsgTmp, Params().MessageStart(), sizeof(pchMsgTmp))) {
            error("%s : Invalid network magic number", __func__);
            return IncorrectMagicNumber;
        }

        // de-serialize data into CMasternodePayments object
        ssObj >> objToLoad;
    } catch (const std::exception& e) {
        objToLoad.Clear();
        error("%s : Deserialize or I/O error - %s", __func__, e.what());
        return IncorrectFormat;
    }

    LogPrint(BCLog::MASTERNODE,"Loaded info from mnpayments.dat  %dms\n", GetTimeMillis() - nStart);
    LogPrint(BCLog::MASTERNODE,"  %s\n", objToLoad.ToString());
    if (!fDryRun) {
        LogPrint(BCLog::MASTERNODE,"Masternode payments manager - cleaning....\n");
        objToLoad.CleanPaymentList();
        LogPrint(BCLog::MASTERNODE,"Masternode payments manager - result:\n");
        LogPrint(BCLog::MASTERNODE,"  %s\n", objToLoad.ToString());
    }

    return Ok;
}

uint256 CMasternodePaymentWinner::GetHash() const
{
    CHashWriter ss(SER_GETHASH, PROTOCOL_VERSION);
    ss << std::vector<unsigned char>(payee.begin(), payee.end());
    ss << nBlockHeight;
    ss << vinMasternode.prevout;
    return ss.GetHash();
}

std::string CMasternodePaymentWinner::GetStrMessage() const
{
    if (Params().GetConsensus().NetworkUpgradeActive(chainActive.Tip()->nHeight, Consensus::UPGRADE_TIME_PROTOCOL_V2)) {
        return vinMasternode.prevout.ToStringShort() + std::to_string(nBlockHeight) + HexStr(payee);
    } else {
        return vinMasternode.prevout.ToStringShort() + std::to_string(nBlockHeight) + ScriptToAsmStr(payee);
    }
}

bool CMasternodePaymentWinner::IsValid(CNode* pnode, std::string& strError)
{
    CMasternode* pmn = mnodeman.Find(vinMasternode);

    if (!pmn) {
        strError = strprintf("Unknown Masternode %s", vinMasternode.prevout.ToStringShort());
        LogPrint(BCLog::MASTERNODE,"CMasternodePaymentWinner::IsValid - %s\n", strError);
        mnodeman.AskForMN(pnode, vinMasternode);
        return false;
    }

    if (sporkManager.IsSporkActive(SPORK_102_FORCE_ENABLED_MASTERNODE)) {
        if (pmn->Status() != "ENABLED") {
            strError = strprintf("Masternode is not in ENABLED state - Status(): %d", pmn->Status());
            LogPrint(BCLog::MASTERNODE, "CMasternodePaymentWinner::IsValid - Force masternode requirement to have ENABLED status instead of ACTIVE - %s\n", strError);
            return false;
        }
    }

    int n = mnodeman.GetMasternodeRank(vinMasternode, nBlockHeight - 100);

    if (n > MNPAYMENTS_SIGNATURES_TOTAL) {
        //It's common to have masternodes mistakenly think they are in the top 10
        // We don't want to print all of these messages, or punish them unless they're way off
        if (n > MNPAYMENTS_SIGNATURES_TOTAL * 2) {
            strError = strprintf("Masternode not in the top %d (%d)", MNPAYMENTS_SIGNATURES_TOTAL * 2, n);
            LogPrint(BCLog::MASTERNODE,"CMasternodePaymentWinner::IsValid - %s\n", strError);
            //if (masternodeSync.IsSynced()) Misbehaving(pnode->GetId(), 20);
        }
        return false;
    }

    return true;
}

void CMasternodePaymentWinner::Relay()
{
    CInv inv(MSG_MASTERNODE_WINNER, GetHash());
    g_connman->RelayInv(inv);
}

void DumpMasternodePayments()
{
    int64_t nStart = GetTimeMillis();

    CMasternodePaymentDB paymentdb;
    CMasternodePayments tempPayments;

    LogPrint(BCLog::MASTERNODE,"Verifying mnpayments.dat format...\n");
    CMasternodePaymentDB::ReadResult readResult = paymentdb.Read(tempPayments, true);
    // there was an error and it was not an error on file opening => do not proceed
    if (readResult == CMasternodePaymentDB::FileError)
        LogPrint(BCLog::MASTERNODE,"Missing budgets file - mnpayments.dat, will try to recreate\n");
    else if (readResult != CMasternodePaymentDB::Ok) {
        LogPrint(BCLog::MASTERNODE,"Error reading mnpayments.dat: ");
        if (readResult == CMasternodePaymentDB::IncorrectFormat)
            LogPrint(BCLog::MASTERNODE,"magic is ok but data has invalid format, will try to recreate\n");
        else {
            LogPrint(BCLog::MASTERNODE,"file format is unknown or invalid, please fix it manually\n");
            return;
        }
    }
    LogPrint(BCLog::MASTERNODE,"Writting info to mnpayments.dat...\n");
    paymentdb.Write(masternodePayments);

    LogPrint(BCLog::MASTERNODE,"Budget dump finished  %dms\n", GetTimeMillis() - nStart);
}

bool IsBlockValueValid(int nHeight, CAmount nExpectedValue, CAmount nMinted)
{
    // No superblock, regular check
    return nMinted <= nExpectedValue;
}

bool IsBlockPayeeValid(const CBlock& block, int nBlockHeight)
{
    if (!masternodeSync.IsSynced()) { //there is no budget data to use to check anything -- find the longest chain
        LogPrint(BCLog::MASTERNODE, "Client not synced, skipping block payee checks\n");
        return true;
    }

    const bool isPoSActive = Params().GetConsensus().NetworkUpgradeActive(nBlockHeight, Consensus::UPGRADE_POS);
    const CTransaction& txNew = (isPoSActive ? block.vtx[1] : block.vtx[0]);

    auto t = GetTime();

    if((t - reconsiderWindowTime) > HOUR_IN_SECONDS) {  // shift the reconsider window at each hour 
        reconsiderWindowMin = GetRand() % 10;           // choose randomly from minute 0 to minute 9
        reconsiderWindowTime = t;

        for (auto it = mapRejectedBlocks.cbegin(); it != mapRejectedBlocks.cend();) { // clean up old entries
            it = (GetTime() - (*it).second) > HOUR_IN_SECONDS ? mapRejectedBlocks.erase(it) : std::next(it);
        }
    }

    //check for masternode payee
    if (masternodePayments.IsTransactionValid(txNew, nBlockHeight))
        return true;
    LogPrint(BCLog::MASTERNODE,"Invalid mn payment detected %s\n", txNew.ToString().c_str());

    // fails if spork 8 is enabled and
    // spork 113 is disabled or current time is outside the reconsider window
    if (sporkManager.IsSporkActive(SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT)) {
        if (!sporkManager.IsSporkActive(SPORK_113_RECONSIDER_WINDOW_ENFORCEMENT)) 
        {
            return false;
        }

        if ((t / MINUTE_IN_SECONDS) % 10 != reconsiderWindowMin) 
        {
            return false;
        }

        LogPrint(BCLog::MASTERNODE,"Masternode payment enforcement reconsidered, accepting block\n");
        return true;
    }

    LogPrint(BCLog::MASTERNODE,"Masternode payment enforcement is disabled, accepting block\n");
    return true;
}


void FillBlockPayee(CMutableTransaction& txNew, const CBlockIndex* pindexPrev, bool fProofOfStake)
{
    masternodePayments.FillBlockPayee(txNew, pindexPrev, fProofOfStake);
}

std::string GetRequiredPaymentsString(int nBlockHeight)
{
    return masternodePayments.GetRequiredPaymentsString(nBlockHeight);
}

void CMasternodePayments::FillBlockPayee(CMutableTransaction& txNew, const CBlockIndex* pindexPrev, bool fProofOfStake)
{
    if (!pindexPrev) return;

    bool hasPayment = true;
    CScript payee;

    //spork
    if (!masternodePayments.GetBlockPayee(pindexPrev->nHeight + 1, payee)) {
        //no masternode detected
        CMasternode* winningNode = mnodeman.GetCurrentMasterNode(1);
        if (winningNode) {
            payee = GetScriptForDestination(winningNode->pubKeyCollateralAddress.GetID());
        } else {
            LogPrint(BCLog::MASTERNODE,"CreateNewBlock: Failed to detect masternode to pay\n");
            hasPayment = false;
        }
    }

    if (hasPayment) {
        CAmount masternodePayment = CMasternode::GetMasternodePayment(pindexPrev->nHeight + 1);
        if (fProofOfStake) {
            /**For Proof Of Stake vout[0] must be null
             * Stake reward can be split into many different outputs, so we must
             * use vout.size() to align with several different cases.
             * An additional output is appended as the masternode payment
             */
            unsigned int i = txNew.vout.size();
            txNew.vout.resize(i + 1);
            txNew.vout[i].scriptPubKey = payee;
            txNew.vout[i].nValue = masternodePayment;

            //subtract mn payment from the stake reward
            if (i == 2) {
                // Majority of cases; do it quick and move on
                txNew.vout[i - 1].nValue -= masternodePayment;
            } else if (i > 2) {
                // special case, stake is split between (i-1) outputs
                unsigned int outputs = i-1;
                CAmount mnPaymentSplit = masternodePayment / outputs;
                CAmount mnPaymentRemainder = masternodePayment - (mnPaymentSplit * outputs);
                for (unsigned int j=1; j<=outputs; j++) {
                    txNew.vout[j].nValue -= mnPaymentSplit;
                }
                // in case it's not an even division, take the last bit of dust from the last one
                txNew.vout[outputs].nValue -= mnPaymentRemainder;
            }
        } else {
            txNew.vout.resize(2);
            txNew.vout[1].scriptPubKey = payee;
            txNew.vout[1].nValue = masternodePayment;
            txNew.vout[0].nValue = CMasternode::GetBlockValue(pindexPrev->nHeight + 1) - masternodePayment;
        }

        CTxDestination address1;
        ExtractDestination(payee, address1);

        LogPrint(BCLog::MASTERNODE,"Masternode payment of %s to %s\n", FormatMoney(masternodePayment).c_str(), EncodeDestination(address1).c_str());
    }
}

void CMasternodePayments::ProcessMessageMasternodePayments(CNode* pfrom, std::string& strCommand, CDataStream& vRecv)
{
    if (sporkManager.IsSporkActive(SPORK_114_MN_PAYMENT_V2)) return; // voting is disabled

    if (!masternodeSync.IsBlockchainSynced()) return;

    if (fLiteMode) return; //disable all Masternode related functionality


    if (strCommand == NetMsgType::GETMNWINNERS) { //Masternode Payments Request Sync
        if (fLiteMode) return;   //disable all Masternode related functionality

        int nCountNeeded;
        vRecv >> nCountNeeded;

        if (Params().NetworkID() == CBaseChainParams::MAIN) {
            if (pfrom->HasFulfilledRequest(NetMsgType::GETMNWINNERS)) {
                LogPrintf("CMasternodePayments::ProcessMessageMasternodePayments() : mnget - peer already asked me for the list\n");
                return;
            }
        }

        pfrom->FulfilledRequest(NetMsgType::GETMNWINNERS);
        masternodePayments.Sync(pfrom, nCountNeeded);
        LogPrint(BCLog::MASTERNODE, "mnget - Sent Masternode winners to peer %i\n", pfrom->GetId());
    } else if (strCommand == NetMsgType::MNWINNER) { //Masternode Payments Declare Winner
        //this is required in litemodef
        CMasternodePaymentWinner winner;
        vRecv >> winner;

        if (pfrom->nVersion < ActiveProtocol()) return;

        int nHeight;
        {
            TRY_LOCK(cs_main, locked);
            if (!locked || chainActive.Tip() == NULL) return;
            nHeight = chainActive.Tip()->nHeight;
        }

        if (masternodePayments.mapMasternodePayeeVotes.count(winner.GetHash())) {
            LogPrint(BCLog::MASTERNODE, "mnw - Already seen - %s bestHeight %d\n", winner.GetHash().ToString().c_str(), nHeight);
            masternodeSync.AddedMasternodeWinner(winner.GetHash());
            return;
        }

        int nFirstBlock = nHeight - (mnodeman.CountEnabled() * 1.25);
        if (winner.nBlockHeight < nFirstBlock || winner.nBlockHeight > nHeight + 20) {
            LogPrint(BCLog::MASTERNODE, "mnw - winner out of range - FirstBlock %d Height %d bestHeight %d\n", nFirstBlock, winner.nBlockHeight, nHeight);
            return;
        }

        // reject old signature version
        if (Params().GetConsensus().NetworkUpgradeActive(chainActive.Tip()->nHeight, Consensus::UPGRADE_TIME_PROTOCOL_V2) &&
            winner.nMessVersion != MessageVersion::MESS_VER_HASH) {
            LogPrint(BCLog::MASTERNODE, "mnw - rejecting old message version %d\n", winner.nMessVersion);
            return;
        }

        std::string strError = "";
        if (!winner.IsValid(pfrom, strError)) {
            // if(strError != "") LogPrint(BCLog::MASTERNODE,"mnw - invalid message - %s\n", strError);
            return;
        }

        if (!masternodePayments.CanVote(winner.vinMasternode.prevout, winner.nBlockHeight)) {
            //  LogPrint(BCLog::MASTERNODE,"mnw - masternode already voted - %s\n", winner.vinMasternode.prevout.ToStringShort());
            return;
        }

        if (!winner.CheckSignature()) {
            if (masternodeSync.IsSynced()) {
                LogPrintf("CMasternodePayments::ProcessMessageMasternodePayments() : mnw - invalid signature\n");
                LOCK(cs_main);
                Misbehaving(pfrom->GetId(), 20);
            }
            // it could just be a non-synced masternode
            mnodeman.AskForMN(pfrom, winner.vinMasternode);
            return;
        }

        if (winner.nBlockHeight >= nHeight && 
            sporkManager.IsSporkActive(SPORK_109_FORCE_ENABLED_VOTED_MASTERNODE)
        ) {
            CMasternode* pmn = mnodeman.Find(winner.payee);
            if (!pmn) {
                LogPrint(BCLog::MASTERNODE, "mnw - winner payee is not a masternode");
                return;
            }
            if (!pmn->IsEnabled()) {
                LogPrint(BCLog::MASTERNODE, "mnw - winner payee is a masternode but is not ENABLED");
                return;
            }  
        }

        CTxDestination address1;
        ExtractDestination(winner.payee, address1);

        LogPrint(BCLog::MASTERNODE, "mnw - winning vote - Addr %s Height %d bestHeight %d - %s\n", EncodeDestination(address1), winner.nBlockHeight, nHeight, winner.vinMasternode.prevout.ToStringShort());

        if (masternodePayments.AddWinningMasternode(winner)) {
            winner.Relay();
            masternodeSync.AddedMasternodeWinner(winner.GetHash());
        }
    }
}

bool CMasternodePayments::GetBlockPayeeV1(int nBlockHeight, CScript& payee) 
{
    LogPrint(BCLog::MASTERNODE, "CMasternodePayments::GetBlockPayeeV1() nHeight %d. \n", nBlockHeight);

    LOCK(cs_mapMasternodeBlocks);

    if (mapMasternodeBlocks.count(nBlockHeight)) {
        return mapMasternodeBlocks[nBlockHeight].GetPayee(payee);
    }

    return false;
}

bool CMasternodePayments::GetBlockPayeeV2(int nBlockHeight, CScript& payee)
{
    LogPrint(BCLog::MASTERNODE, "%s : nHeight %d. \n", __func__, nBlockHeight);

    // pay to the oldest MN that still had no payment but its input is old enough and it was active long enough
    auto pmn = mnodeman.GetNextMasternodeInQueueForPayment(nBlockHeight);

    if (pmn) {
        LogPrint(BCLog::MASTERNODE,"%s : Found by GetNextMasternodeInQueueForPayment \n", __func__);

        payee = GetScriptForDestination(pmn->pubKeyCollateralAddress.GetID());

        CTxDestination address1;
        ExtractDestination(payee, address1);

        LogPrint(BCLog::MASTERNODE,"%s : Winner payee %s nHeight %d. \n", __func__, EncodeDestination(address1).c_str(), nBlockHeight);

        return true;
    } 

    LogPrint(BCLog::MASTERNODE,"%s : Failed to find masternode to pay\n", __func__);

    return false;
}

bool CMasternodePayments::GetBlockPayee(int nBlockHeight, CScript& payee)
{
    return
        !sporkManager.IsSporkActive(SPORK_114_MN_PAYMENT_V2) ?
        GetBlockPayeeV1(nBlockHeight, payee) :
        GetBlockPayeeV2(nBlockHeight, payee);
}

// Is this masternode scheduled to get paid soon?
// -- Only look ahead up to 8 blocks to allow for propagation of the latest 2 winners
bool CMasternodePayments::IsScheduled(CMasternode& mn, int nNotBlockHeight)
{
    if (sporkManager.IsSporkActive(SPORK_114_MN_PAYMENT_V2)) return false; // voting is disabled

    int nHeight;
    {
        TRY_LOCK(cs_main, locked);
        if (!locked || chainActive.Tip() == NULL) return false;
        nHeight = chainActive.Tip()->nHeight;
    }

    CScript mnpayee;
    mnpayee = GetScriptForDestination(mn.pubKeyCollateralAddress.GetID());

    CScript payee;
    for (int64_t h = nHeight; h <= nHeight + 8; h++) {
        if (h == nNotBlockHeight) continue;
        CMasternodeBlockPayees mnbp;
        {
            LOCK(cs_mapMasternodeBlocks);

            if (mapMasternodeBlocks.count(h)) {
                mnbp = mapMasternodeBlocks[h];
            }
        }
        if (mnbp.nBlockHeight > 0 && mnbp.GetPayee(payee)) {
            if (mnpayee == payee) {
                return true;
            }
        }
    }

    return false;
}

bool CMasternodePayments::AddWinningMasternode(CMasternodePaymentWinner& winnerIn)
{
    uint256 blockHash;
    if (!GetBlockHash(blockHash, winnerIn.nBlockHeight - 100)) {
        return false;
    }

    {
        LOCK(cs_mapMasternodePayeeVotes);

        if (mapMasternodePayeeVotes.count(winnerIn.GetHash())) {
            return false;
        }

        mapMasternodePayeeVotes[winnerIn.GetHash()] = winnerIn;
        }

    {
        LOCK(cs_mapMasternodeBlocks);

        if (!mapMasternodeBlocks.count(winnerIn.nBlockHeight)) {
            CMasternodeBlockPayees blockPayees(winnerIn.nBlockHeight);
            mapMasternodeBlocks[winnerIn.nBlockHeight] = blockPayees;
        }

        mapMasternodeBlocks[winnerIn.nBlockHeight].AddPayee(winnerIn.payee, 1);
    }

    return true;
}

bool CMasternodeBlockPayees::IsTransactionValidV1(const CTransaction& txNew, int nBlockHeight) 
{
    //require at least 6 signatures
    int nMaxSignatures = 0;
    for (CMasternodePayee& payee : vecPayments)
        if (payee.nVotes >= nMaxSignatures && payee.nVotes >= MNPAYMENTS_SIGNATURES_REQUIRED)
            nMaxSignatures = payee.nVotes;

    // if we don't have at least 6 signatures on a payee, approve whichever is the longest chain
    if (nMaxSignatures < MNPAYMENTS_SIGNATURES_REQUIRED) {
        return true;
    }

    std::string strPayeesPossible = "";
    CAmount requiredMasternodePayment = CMasternode::GetMasternodePayment(nBlockHeight);

    for (CMasternodePayee& payee : vecPayments) {
        bool found = false;
        for (CTxOut out : txNew.vout) {
            if (payee.scriptPubKey == out.scriptPubKey) {
                if(out.nValue == requiredMasternodePayment)
                    found = true;
                else
                    LogPrintf("%s : Masternode payment value (%s) different from required value (%s).\n",
                            __func__, FormatMoney(out.nValue).c_str(), FormatMoney(requiredMasternodePayment).c_str());
            }
        }

        if (payee.nVotes >= MNPAYMENTS_SIGNATURES_REQUIRED) {
            if (found) {
                
                CMasternode* pmn = mnodeman.Find(payee.scriptPubKey);

                bool result = false;
                if(sporkManager.IsSporkActive(SPORK_110_FORCE_ENABLED_MASTERNODE_PAYMENT)) {
                    result = pmn && pmn->IsEnabled(); // it is a existing masternode and it is enabled then it is OK
                } else {
                    result = true;
                }

                return result;
            }

            CTxDestination address1;
            ExtractDestination(payee.scriptPubKey, address1);

            if (strPayeesPossible != "")
                strPayeesPossible += ",";

            strPayeesPossible += EncodeDestination(address1);
        }
    }

    LogPrint(BCLog::MASTERNODE,"CMasternodePayments::IsTransactionValid - Missing required payment of %s to %s\n", FormatMoney(requiredMasternodePayment).c_str(), strPayeesPossible.c_str());
    
    return false;
}

bool CMasternodeBlockPayees::IsTransactionValidV2(const CTransaction& txNew, int nBlockHeight)
{
    // if there is no MNs, then there is no enough data to perform verification
    if (mnodeman.CountEnabled() == 0) {
        return true;
    }

    // if the masternode list is not synced, then there is no enough data to perform verification
    if (!masternodeSync.IsSynced()) {
        return true;
    }

    auto requiredMasternodePayment = CMasternode::GetMasternodePayment(nBlockHeight);
    auto found = false;
    CScript paidPayee;

    for (CTxOut out : txNew.vout) {
        if (out.nValue == requiredMasternodePayment) {
            found = true;
            paidPayee = out.scriptPubKey;
        }
    }

    if (found) {
        // fetch the paid masternode from our masternode list
        auto pmn = mnodeman.Find(paidPayee);

        // check if the masternode really exists and is enabled
        if (!pmn || !pmn->IsEnabled()) return false;

        // get the masternodes choosen on this decision
        auto eligible = mnodeman.GetNextMasternodeInQueueEligible(nBlockHeight);

        auto nmn = eligible.first;
        auto result = false;

        if (pmn->GetVin() == nmn->GetVin()) { // if they match, then the paid masternode is OK
            result = true;
        } else { // else, iterate on the eligible list and see if there is another possibility of a valid masternode to pay
            for (auto& txin : eligible.second) {
                if (pmn->GetVin() == txin) { 
                    result = true; // there is a plausible masternode to pay, therefore return true
                }
            }

            if(!result) {
                CTxDestination addr;
                ExtractDestination(paidPayee, addr);

                LogPrint(BCLog::MASTERNODE, "CMasternodePayments::IsTransactionValid - Paid masternode %s is not eligible\n", EncodeDestination(addr));
            }
        }

        return result;
    } else {
        LogPrint(BCLog::MASTERNODE, "CMasternodePayments::IsTransactionValid - Missing required payment of %s\n", FormatMoney(requiredMasternodePayment).c_str());

        return false;
    }

    return false;
}

bool CMasternodeBlockPayees::IsTransactionValid(const CTransaction& txNew, int nBlockHeight)
{
    return !sporkManager.IsSporkActive(SPORK_114_MN_PAYMENT_V2) ?
               IsTransactionValidV1(txNew, nBlockHeight) :
               IsTransactionValidV2(txNew, nBlockHeight);
}

std::string CMasternodeBlockPayees::GetRequiredPaymentsString()
{
    LOCK(cs_vecPayments);

    std::string ret = "Unknown";

    for (CMasternodePayee& payee : vecPayments) {
        CTxDestination address1;
        ExtractDestination(payee.scriptPubKey, address1);
        if (ret != "Unknown") {
            ret += ", ";
        }
        ret = EncodeDestination(address1) + ":" + std::to_string(payee.nVotes);
    }

    return ret;
}

std::string CMasternodePayments::GetRequiredPaymentsString(int nBlockHeight)
{
    LOCK(cs_mapMasternodeBlocks);

    if (mapMasternodeBlocks.count(nBlockHeight)) {
        return mapMasternodeBlocks[nBlockHeight].GetRequiredPaymentsString();
    }

    return "Unknown";
}

bool CMasternodePayments::IsTransactionValid(const CTransaction& txNew, int nBlockHeight)
{
    CMasternodeBlockPayees mnbp;

    {
        LOCK(cs_mapMasternodeBlocks);

        if (mapMasternodeBlocks.count(nBlockHeight)) {
            mnbp = mapMasternodeBlocks[nBlockHeight];
        }
    }

    if (mnbp.nBlockHeight > 0) {
        return mnbp.IsTransactionValid(txNew, nBlockHeight);
    }

    if (sporkManager.IsSporkActive(SPORK_112_MASTERNODE_LAST_PAID_V2)) { // if voting is disabled, try again
        return mnbp.IsTransactionValid(txNew, nBlockHeight);
    }

    return true;
}

void CMasternodePayments::CleanPaymentList()
{
    int nHeight;
    {
        TRY_LOCK(cs_main, locked);
        if (!locked || chainActive.Tip() == NULL) return;
        nHeight = chainActive.Tip()->nHeight;
    }

    LOCK2(cs_mapMasternodePayeeVotes, cs_mapMasternodeBlocks);

    //keep up to five cycles for historical sake
    int nLimit = std::max(int(mnodeman.size() * (sporkManager.IsSporkActive(SPORK_112_MASTERNODE_LAST_PAID_V2) ? 2 : 1.25)), 1000);

    std::map<uint256, CMasternodePaymentWinner>::iterator it = mapMasternodePayeeVotes.begin();
    while (it != mapMasternodePayeeVotes.end()) {
        CMasternodePaymentWinner winner = (*it).second;

        if (nHeight - winner.nBlockHeight > nLimit) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::CleanPaymentList - Removing old Masternode payment - block %d\n", winner.nBlockHeight);
            masternodeSync.mapSeenSyncMNW.erase((*it).first);
            mapMasternodePayeeVotes.erase(it++);
            mapMasternodeBlocks.erase(winner.nBlockHeight);
        } else {
            ++it;
        }
    }
}

void CMasternodePayments::ProcessBlock(int nBlockHeight)
{
    if (!fMasterNode) return;

    if (sporkManager.IsSporkActive(SPORK_114_MN_PAYMENT_V2)) return; // voting is disabled

    auto nHeight = nLastBlockHeight;

    for (auto& activeMasternode : amnodeman.GetActiveMasternodes()) {
        if (activeMasternode.vin == nullopt) {
            LogPrint(BCLog::MASTERNODE, "%s: Active Masternode not initialized.", __func__);
            continue;
        }

        //reference node - hybrid mode

        int n = mnodeman.GetMasternodeRank(*(activeMasternode.vin), nBlockHeight - 100);

        if (n == -1 || n == INT_MAX) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock - Unknown Masternode\n");
            continue;
        }

        if (n > MNPAYMENTS_SIGNATURES_TOTAL) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock - Masternode not in the top %d (%d)\n", MNPAYMENTS_SIGNATURES_TOTAL, n);
            continue;
        }

        if (nBlockHeight <= nLastBlockHeight) continue;

        CMasternodePaymentWinner newWinner(*(activeMasternode.vin));

        LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() Start nHeight %d - vin %s. \n", nBlockHeight, activeMasternode.vin->prevout.ToStringShort());

        // pay to the oldest MN that still had no payment but its input is old enough and it was active long enough
        CMasternode* pmn = mnodeman.GetNextMasternodeInQueueForPayment(nBlockHeight);

        if (pmn != NULL) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() Found by FindOldestNotInVec \n");

            newWinner.nBlockHeight = nBlockHeight;

            CScript payee = GetScriptForDestination(pmn->pubKeyCollateralAddress.GetID());
            newWinner.AddPayee(payee);

            CTxDestination address1;
            ExtractDestination(payee, address1);

            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() Winner payee %s nHeight %d. \n", EncodeDestination(address1).c_str(), newWinner.nBlockHeight);
        } else {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() Failed to find masternode to pay\n");
        }

        std::string errorMessage;
        CPubKey pubKeyMasternode;
        CKey keyMasternode;

        if (!CMessageSigner::GetKeysFromSecret(activeMasternode.strMasterNodePrivKey, keyMasternode, pubKeyMasternode)) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() - Error upon calling GetKeysFromSecret.\n");
            continue;
        }

        LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() - Signing Winner\n");
        if (newWinner.Sign(keyMasternode, pubKeyMasternode)) {
            LogPrint(BCLog::MASTERNODE, "CMasternodePayments::ProcessBlock() - AddWinningMasternode\n");

            if (AddWinningMasternode(newWinner)) {
                newWinner.Relay();
                nHeight = nBlockHeight;
            }
        }
    }

    nLastBlockHeight = nHeight;
}

void CMasternodePayments::Sync(CNode* node, int nCountNeeded)
{
    int nHeight;
    {
        TRY_LOCK(cs_main, locked);
        if (!locked || chainActive.Tip() == NULL) return;
        nHeight = chainActive.Tip()->nHeight;
    }

    LOCK(cs_mapMasternodePayeeVotes);

    int nCount = (mnodeman.CountEnabled() * 1.25);
    if (nCountNeeded > nCount) nCountNeeded = nCount;

    int nInvCount = 0;
    std::map<uint256, CMasternodePaymentWinner>::iterator it = mapMasternodePayeeVotes.begin();
    while (it != mapMasternodePayeeVotes.end()) {
        CMasternodePaymentWinner winner = (*it).second;
        if (winner.nBlockHeight >= nHeight - nCountNeeded && winner.nBlockHeight <= nHeight + 20) {
            node->PushInventory(CInv(MSG_MASTERNODE_WINNER, winner.GetHash()));
            nInvCount++;
        }
        ++it;
    }
    g_connman->PushMessage(node, CNetMsgMaker(node->GetSendVersion()).Make(NetMsgType::SYNCSTATUSCOUNT, MASTERNODE_SYNC_MNW, nInvCount));
}

std::string CMasternodePayments::ToString() const
{
    std::ostringstream info;

    info << "Votes: " << (int)mapMasternodePayeeVotes.size() << ", Blocks: " << (int)mapMasternodeBlocks.size();

    return info.str();
}

// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/ebf.h"
#include "ebf/jackpot/dice.h"
#include "ebf/jackpot/lottery.h"
#include "ebf/jackpot/roulette.h"
#include "ebf/sapphire/bond.h"
#include "ebf/system/hodl.h"
#include "ebf/system/masternode.h"
#include "ebf/system/spork.h"

void CEBFPlatform::CheckAndRun(const CBlock& block, CValidationState& state, CMutableTransaction& coinstake) {
    std::vector<CTxOut> vout;

    CSporkEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    CHodlEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    CMasternodeEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    CBondEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    CDiceEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    CLotteryEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;
    
    CRouletteEBF(block).CheckAndRun(state, vout);
    if(!state.IsValid()) return;

    // TODO Group similar CTxOut

    // TODO Add CTxOut to the transaction
}
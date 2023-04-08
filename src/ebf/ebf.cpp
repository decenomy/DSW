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

bool CEBFPlatform::Check(const std::vector<CTxOut>& vout, CValidationState& state) {
    // Check the EBFs inside the transaction
    for(auto& txout : vout) {
        auto& script = txout.scriptPubKey;

        if (script[0] == OP_RETURN &&
            script[1] == EBF_MESSAGE_FIRST_FRAGMENT &&
            script[2] == EBF_MESSAGE_SECOND_FRAGMENT
        ) {
            switch (script[3])
            {
            case DICE_CONTRACT:
                return CDiceEBFBet::CheckTxOut(txout, state);
            default:
                // accept unknown contracts
                break;
            }
        }
    }

    return true;
}

bool CEBFPlatform::AcceptToMemoryPoolWorker(CTxMemPool& pool, CValidationState &state, const CTransaction &tx) {
    LOCK(pool.cs);
    return Check(tx.vout, state);
}

bool CEBFPlatform::Run(const CBlock& block, CValidationState& state, CMutableTransaction& coinstake) {
    
    std::vector<CTxOut> vout;

    for(auto& tx : block.vtx) {
        if(!Check(tx.vout, state)) return false;
    }

    auto runSuccessful = 
        CSporkEBF(block).Run(state, vout) &&
        CHodlEBF(block).Run(state, vout) &&
        CMasternodeEBF(block).Run(state, vout) &&
        CBondEBF(block).Run(state, vout) &&
        CDiceEBF(block).Run(state, vout) &&
        CLotteryEBF(block).Run(state, vout) &&
        CRouletteEBF(block).Run(state, vout);

    if(!runSuccessful) return false;

    // TODO Group similar CTxOut

    // TODO Add CTxOut to the transaction

    return true;
}
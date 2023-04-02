// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/dice.h"

void CDiceEBF::ProcessBlock(CValidationState& state) {
    // Foreach bet made at 6 blocks ago
    //   Check if it won
    //   Perform Payouts
}

CScript CDiceEBF::GetBetScript(DiceBetType betType, CAmount amount) {
    return CScript() << 
        OP_RETURN <<                                // Bets are started with an OP_RETURN
        CScriptNum(EBF_MESSAGE_FIRST_FRAGMENT) <<   // and identified by two random magic numbers
        CScriptNum(EBF_MESSAGE_SECOND_FRAGMENT) <<  // ...
        CScriptNum(EbfContracts::DICE_CONTRACT) <<  // Defines the type of the contract
        CScriptNum(1) <<                            // Defines the version of the contract to run
        CScriptNum(betType) <<                      // Defines the method of the contract, in this case: a bet on a roll of two dices
        CScriptNum(amount);                         // Finally the amount being bet
}
// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/dice.h"

void CDiceEBF::ProcessBlock(CValidationState& state) {
    // Foreach bet made at 6 blocks ago
    //   Check if it won
    //   Perform Payouts
}

CScript CDiceEBF::GetBetScript(DiceBetType betType, CAmount amount, CKeyID payee) {
    return CScript() << 
        OP_RETURN <<                                // 1 byte   Bets are started with an OP_RETURN
        CScriptNum(EBF_MESSAGE_FIRST_FRAGMENT) <<   // 1 byte   and identified by two random magic numbers
        CScriptNum(EBF_MESSAGE_SECOND_FRAGMENT) <<  // 1 byte   ...
        CScriptNum(EbfContracts::DICE_CONTRACT) <<  // 1 byte   Defines the type of the contract
        CScriptNum(1) <<                            // 1 byte   Defines the version of the contract to run
        CScriptNum(betType) <<                      // 1 byte   Defines the method of the contract, in this case: a bet on a roll of two dices
        CScriptNum(amount) <<                       // 8 bytes  Defines the amount being bet
        ToByteVector(payee);                        // 20 bytes Finally define the key id of the address to be paid in case of a payout
}
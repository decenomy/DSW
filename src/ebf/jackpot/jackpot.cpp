// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/jackpot.h"
#include "chain.h"

uint256 CJackpotEBF::GetRandomSeed() {
    // V1 Get the entropy value directly from the stake modifier
    return CBlockIndex::CalculateStakeModifier(block);
}

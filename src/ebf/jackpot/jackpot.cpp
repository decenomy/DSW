// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/jackpot.h"

// Get seed from the stake modifier
uint256 GetRandomSeed(const CBlockHeader* pblockHeader) const
{
    if (!pblockHeader) throw std::runtime_error(strprintf("%s : ERROR: null pblockHeader", __func__));

    auto pBlockIndex = mapBlockIndex[pblockHeader->hashPrevBlock];

    if (!pBlockIndex) throw std::runtime_error(strprintf("%s : ERROR: null pBlockIndex", __func__));

    return pBlockIndex->GetStakeModifierV2();
}
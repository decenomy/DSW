// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_H
#define DECENOMY_EBF_H

#include "chain.h"

enum EbfPlatforms { // 0-31 (32 Slots)
    SYSTEM          = 0x00,
    SAPPHIRE        = 0x01,
    JACKPOT         = 0x02,
    MAX_PLATFORMS   = 0x1F,
};

enum EbfContracts { // 0-7 (8 Slots per platform in one byte, more are possible by using varint) 
    // System
    HODL_CONTRACT           = EbfPlatforms::SYSTEM      + (0x00 << 5),
    MASTERNODE_CONTRACT     = EbfPlatforms::SYSTEM      + (0x01 << 5),
    SPORK_CONTRACT          = EbfPlatforms::SYSTEM      + (0x02 << 5),

    // Sapphire
    BOND_CONTRACT           = EbfPlatforms::SAPPHIRE    + (0x00 << 5),
    
    // Jackpot
    DICE_CONTRACT           = EbfPlatforms::JACKPOT     + (0x00 << 5),
    ROULETTE_CONTRACT       = EbfPlatforms::JACKPOT     + (0x01 << 5),
    LOTTERY_CONTRACT        = EbfPlatforms::JACKPOT     + (0X02 << 5),
};

bool CheckEBFs(const CBlock& block);
void FillWithdrawalsAndPayouts(const CBlock& block, CMutableTransaction& txNew);

#endif // DECENOMY_EBF_H
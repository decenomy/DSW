// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_H
#define DECENOMY_EBF_H

enum EbfPlatforms { // 0-31 (32 Slots)
    BASE        = 0x00,
    SAPPHIRE    = 0x01,
    JACKPOT     = 0x02,
};

enum EbfType { // 0-7 (8 Slots for one byte, more are possible by using varint) 
    // System
    HODL_CONTRACT           = 0x00 << 5 + EbfPlatforms::BASE,
    MASTERNODE_CONTRACT     = 0x01 << 5 + EbfPlatforms::BASE,

    // Sapphire
    BOND_CONTRACT           = 0x00 << 5 + EbfPlatforms::SAPPHIRE,
    
    // Jackpot
    DICE_CONTRACT           = 0x00 << 5 + EbfPlatforms::JACKPOT,
    ROULETTE_CONTRACT       = 0x01 << 5 + EbfPlatforms::JACKPOT,
    LOTTERY_CONTRACT        = 0X02 << 5 + EbfPlatforms::JACKPOT,
};

#endif // DECENOMY_EBF_H
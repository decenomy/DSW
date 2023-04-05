// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_H
#define DECENOMY_EBF_H

#include "chain.h"
#include "consensus/validation.h"

#define EBF_MESSAGE_FIRST_FRAGMENT  0xE6
#define EBF_MESSAGE_SECOND_FRAGMENT 0x72

enum EBFPlatforms { // 0-31 (32 Slots)
    SYSTEM          = 0x00,
    SAPPHIRE        = 0x01,
    JACKPOT         = 0x02,
    MAX_PLATFORMS   = 0x1F,
};

enum EBFContracts { // 0-7 (8 Slots per platform in one byte, more are possible by using varint) 
    // System
    HODL_CONTRACT           = EBFPlatforms::SYSTEM      + (0x00 << 5),
    MASTERNODE_CONTRACT     = EBFPlatforms::SYSTEM      + (0x01 << 5),
    SPORK_CONTRACT          = EBFPlatforms::SYSTEM      + (0x02 << 5),

    // Sapphire
    BOND_CONTRACT           = EBFPlatforms::SAPPHIRE    + (0x00 << 5),
    
    // Jackpot
    DICE_CONTRACT           = EBFPlatforms::JACKPOT     + (0x00 << 5),
    ROULETTE_CONTRACT       = EBFPlatforms::JACKPOT     + (0x01 << 5),
    LOTTERY_CONTRACT        = EBFPlatforms::JACKPOT     + (0X02 << 5),
};

class CEBF {
protected:
    const CBlock& block;
public:
    CEBF(const CBlock& block) : block(block) {}
    virtual void CheckAndRun(const CValidationState& state, const std::vector<CTxOut>& vout) = 0;
};

class CEBFPlatform {
public:
    static void CheckAndRun(const CBlock& block, CValidationState& state, CMutableTransaction& coinstake);
};

#endif // DECENOMY_EBF_H
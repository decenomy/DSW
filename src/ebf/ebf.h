// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_H
#define DECENOMY_EBF_H

#include "chain.h"
#include "consensus/validation.h"
#include "txmempool.h"

#define EBF_MESSAGE_FIRST_FRAGMENT  0xE6
#define EBF_MESSAGE_SECOND_FRAGMENT 0x72

enum EBFPlatforms { // 0-31 (32 Slots)
    SYSTEM          = 0x00,
    SAPPHIRE        = 0x01,
    JACKPOT         = 0x02,
};

enum EBFContracts { // 0-7 (8 Slots per platform in one byte, more are possible by using varint) 
    // System
    HODL_CONTRACT           = EBFPlatforms::SYSTEM          + (0x00 << 5),
    MASTERNODE_CONTRACT     = EBFPlatforms::SYSTEM          + (0x01 << 5),
    SPORK_CONTRACT          = EBFPlatforms::SYSTEM          + (0x02 << 5),

    // Sapphire
    BOND_CONTRACT           = EBFPlatforms::SAPPHIRE        + (0x00 << 5),
    
    // Jackpot
    DICE_CONTRACT           = EBFPlatforms::JACKPOT         + (0x00 << 5),
    ROULETTE_CONTRACT       = EBFPlatforms::JACKPOT         + (0x01 << 5),
    LOTTERY_CONTRACT        = EBFPlatforms::JACKPOT         + (0X02 << 5),
};

class CEBFAction {
protected:
    CAmount amount = 0;
    uint8_t version = 0x01;
    EBFContracts contract;

    CEBFAction(CAmount amount, EBFContracts contract, uint8_t version = 0x01) : amount(amount), contract(contract), version(version) {}

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        uint8_t op                  = static_cast<uint8_t>(OP_RETURN);
        uint8_t firstFragment       = EBF_MESSAGE_FIRST_FRAGMENT;
        uint8_t secondFragment      = EBF_MESSAGE_SECOND_FRAGMENT;
        uint8_t contract            = static_cast<uint8_t>(this->contract);

        READWRITE(op);
        READWRITE(firstFragment);
        READWRITE(secondFragment);
        READWRITE(contract);
        if (ser_action.ForRead()) {
            this->contract = static_cast<EBFContracts>(contract);
        }
        READWRITE(version);
    }
};

class CEBF {
protected:
    const CBlock& block;
public:
    CEBF(const CBlock& block) : block(block) {}
    virtual bool Run(CValidationState& state, std::vector<CTxOut>& vout) = 0;
};

class CEBFPlatform {
public:
    static bool AcceptToMemoryPoolWorker(CTxMemPool& pool, CValidationState &state, const CTransaction &tx);
    static bool Check(const std::vector<CTxOut>& vout, CValidationState& state);
    static bool Run(const CBlock& block, CValidationState& state, CMutableTransaction& coinstake);
};

#endif // DECENOMY_EBF_H
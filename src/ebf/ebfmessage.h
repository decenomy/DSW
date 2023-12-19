// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_MESSAGE_H
#define DECENOMY_EBF_MESSAGE_H

#include "ebf.h"

class CEBFMessage {
protected:
    CAmount amount = 0;
    uint8_t version = 0x01;
    EBFContracts contract;

    CEBFMessage(CAmount amount, EBFContracts contract, uint8_t version = 0x01) : amount(amount), contract(contract), version(version) {}

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

#endif // DECENOMY_EBF_MESSAGE_H
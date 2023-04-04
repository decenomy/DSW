// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/dice.h"
#include "streams.h"

CDiceEBFBet::CDiceEBFBet(CScript script)
{
    if (script.size() != 34) {
        throw std::runtime_error(strprintf("%s : ERROR: script with invalid size", __func__));
    }

    if (script[0] != OP_RETURN ||
        script[1] != EBF_MESSAGE_FIRST_FRAGMENT ||
        script[2] != EBF_MESSAGE_SECOND_FRAGMENT ||
        script[3] != EbfContracts::DICE_CONTRACT ||
        script[4] != 0x01) {
        throw std::runtime_error(strprintf("%s : ERROR: bet with invalid header format", __func__));
    }

    if (script[5] < DiceBetType::OverSeven ||
        script[5] > DiceBetType::OddSum) {
        throw std::runtime_error(strprintf("%s : ERROR: bet with invalid bet type", __func__));
    }

    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    for(uint8_t byte : script) { ss << byte; }
    this->Unserialize(ss);
}

CScript CDiceEBFBet::ToScript()
{
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    this->Serialize(ss);
    auto script = CScript();
    for(uint8_t byte : ss) {
        script << static_cast<opcodetype>(byte);
    }
    return script;
}

void CDiceEBF::ProcessBlock(CValidationState& state)
{
    // Foreach bet made at 6 blocks ago
    //   Check if it won
    //      If yes => perform the payouts
}

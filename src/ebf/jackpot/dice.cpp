// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/jackpot/dice.h"
#include "main.h"
#include "streams.h"

bool CDiceEBFBet::CheckTxOut(const CTxOut& txout, CValidationState &state) {
    if (txout.nValue < DICE_EBF_MIN_AMOUNT) {
        return state.Invalid(false, REJECT_MALFORMED, "amount too low", strprintf("%s : ERROR: amount too low", __func__));
    }

    if (txout.nValue > DICE_EBF_MAX_AMOUNT) {
        return state.Invalid(false, REJECT_MALFORMED, "amount too high", strprintf("%s : ERROR: amount too high", __func__));
    }

    auto script = txout.scriptPubKey;

    if (script.size() != DICE_EBF_SCRIPT_SIZE) {
        return state.Invalid(false, REJECT_MALFORMED, "script with invalid size", strprintf("%s : ERROR: script with invalid size", __func__));
    }

    if (script[0] != OP_RETURN ||
        script[1] != EBF_MESSAGE_FIRST_FRAGMENT ||
        script[2] != EBF_MESSAGE_SECOND_FRAGMENT ||
        script[3] != DICE_CONTRACT ||
        script[4] != 0x01
    ) {
        return state.Invalid(false, REJECT_MALFORMED, "bet with invalid header format", strprintf("%s : ERROR: bet with invalid header format", __func__));
    }

    if (script[5] < DiceBetType::OverSeven ||
        script[5] > DiceBetType::OddSum
    ) {
        return state.Invalid(false, REJECT_MALFORMED, "bet with invalid bet type", strprintf("%s : ERROR: bet with invalid bet type", __func__));
    }

    return true;
}

CAmount CDiceEBFBet::CheckResults(DiceFace dice1, DiceFace dice2) {

    auto sum = static_cast<int>(dice1) + static_cast<int>(dice2);

    switch(betType) {
    case DiceBetType::OverSeven:
        return sum > 7 ? amount * 36 / 15 : 0;
    case DiceBetType::UnderSeven:
        return sum < 7 ? amount * 36 / 15 : 0;
    case DiceBetType::SumOfTwo:
        return sum == 2 ? amount * 36 / 1 : 0;
    case DiceBetType::SumOfThree:
        return sum == 3 ? amount * 36 / 2 : 0;
    case DiceBetType::SumOfFour:
        return sum == 4 ? amount * 36 / 3 : 0;
    case DiceBetType::SumOfFive:
        return sum == 5 ? amount * 36 / 4 : 0;
    case DiceBetType::SumOfSix:
        return sum == 6 ? amount * 36 / 5 : 0;
    case DiceBetType::SumOfSeven:
        return sum == 7 ? amount * 36 / 6 : 0;
    case DiceBetType::SumOfEight:
        return sum == 8 ? amount * 36 / 5 : 0;
    case DiceBetType::SumOfNine:
        return sum == 9 ? amount * 36 / 4 : 0;
    case DiceBetType::SumOfTen:
        return sum == 10 ? amount * 36 / 3 : 0;
    case DiceBetType::SumOfEleven:
        return sum == 11 ? amount * 36 / 2 : 0;
    case DiceBetType::SumOfTwelve:
        return sum == 12 ? amount * 36 / 1 : 0;
    case DiceBetType::SingleOne:
        return dice1 == DiceFace::One || dice2 == DiceFace::One ? amount * 36 / 11 : 0;
    case DiceBetType::SingleTwo:
        return dice1 == DiceFace::Two || dice2 == DiceFace::Two ? amount * 36 / 11 : 0;
    case DiceBetType::SingleThree:
        return dice1 == DiceFace::Three || dice2 == DiceFace::Three ? amount * 36 / 11 : 0;
    case DiceBetType::SingleFour:
        return dice1 == DiceFace::Four || dice2 == DiceFace::Four ? amount * 36 / 11 : 0;
    case DiceBetType::SingleFive:
        return dice1 == DiceFace::Five || dice2 == DiceFace::Five ? amount * 36 / 11 : 0;
    case DiceBetType::SingleSix:
        return dice1 == DiceFace::Six || dice2 == DiceFace::Six ? amount * 36 / 11 : 0;
    case DiceBetType::AnyDouble:
        return dice1 == dice2 ? amount * 36 / 6 : 0;
    case DiceBetType::DoubleOne:
        return dice1 == dice2 && dice1 == DiceFace::One ? amount * 36 / 1 : 0;
    case DiceBetType::DoubleTwo:
        return dice1 == dice2 && dice1 == DiceFace::Two ? amount * 36 / 1 : 0;
    case DiceBetType::DoubleThree:
        return dice1 == dice2 && dice1 == DiceFace::Three ? amount * 36 / 1 : 0;
    case DiceBetType::DoubleFour:
        return dice1 == dice2 && dice1 == DiceFace::Four ? amount * 36 / 1 : 0;
    case DiceBetType::DoubleFive:
        return dice1 == dice2 && dice1 == DiceFace::Five ? amount * 36 / 1 : 0;
    case DiceBetType::DoubleSix:
        return dice1 == dice2 && dice1 == DiceFace::Six ? amount * 36 / 1 : 0;
    case DiceBetType::EvenSum:
        return sum % 2 == 0 ? amount * 36 / 18 : 0;
    case DiceBetType::OddSum:
        return sum % 2 != 0 ? amount * 36 / 18 : 0;
    }

    return 0;
}

CScript CDiceEBFBet::GeneratePayoutScript() {
    return CScript() << OP_DUP << OP_HASH160 << ToByteVector(payee) << OP_EQUALVERIFY << OP_CHECKSIG;
}

CDiceEBFBet::CDiceEBFBet(DiceBetType betType, CAmount amount, CKeyID payee) : CEBFAction(amount, DICE_CONTRACT), betType(betType), payee(payee) {
    CValidationState state;
    if(!CheckTxOut(ToTxOut(), state)) {
        throw std::runtime_error(state.GetRejectReason());
    }
}

CDiceEBFBet::CDiceEBFBet(CTxOut& txout) : CEBFAction(txout.nValue, DICE_CONTRACT)
{
    CValidationState state;
    if(!CheckTxOut(txout, state)) {
        throw std::runtime_error(state.GetRejectReason());
    }

    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    for (uint8_t byte : txout.scriptPubKey) {
        ss << byte;
    }
    this->Unserialize(ss);
}

CTxOut CDiceEBFBet::ToTxOut()
{
    CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
    Serialize(ss);
    auto script = CScript();
    for (uint8_t byte : ss) {
        script << static_cast<opcodetype>(byte);
    }
    return CTxOut(amount, script);
}

bool CDiceEBF::Run(CValidationState& state, std::vector<CTxOut>& vout)
{
    // Walk backwards to the betting block index
    auto bettingBlockIndex = mapBlockIndex[block.hashPrevBlock];
    for (int i = 1; i < DICE_EBF_BLOCK_DELAY; i++) {
        bettingBlockIndex = mapBlockIndex[bettingBlockIndex->pprev->GetBlockHash()];
    }

    // Draw results
    auto seed = GetRandomSeed();

    auto left = seed >> 128;
    auto right = seed << 128 >> 128;

    auto dice1 = static_cast<DiceFace>((left - (left / 6)).Get32() + 1);
    auto dice2 = static_cast<DiceFace>((right - (right / 6)).Get32() + 1);

    // Fetch the betting block
    CBlock bettingBlock;
    if (bettingBlockIndex->nHeight <= chainActive.Height() && ReadBlockFromDisk(bettingBlock, bettingBlockIndex)) {
        for(auto& tx : bettingBlock.vtx) {
            for(auto& txout : tx.vout) {
                auto& script = txout.scriptPubKey;

                if (script[0] == OP_RETURN &&
                    script[1] == EBF_MESSAGE_FIRST_FRAGMENT &&
                    script[2] == EBF_MESSAGE_SECOND_FRAGMENT &&
                    script[3] == DICE_CONTRACT
                ) {
                    if(CDiceEBFBet::CheckTxOut(txout, state)) {
                        auto bet = CDiceEBFBet(txout);

                        auto result = bet.CheckResults(dice1, dice2);

                        if(result > 0) {
                            vout.push_back(CTxOut(result, bet.GeneratePayoutScript()));
                        }
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

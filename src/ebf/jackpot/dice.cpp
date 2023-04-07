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

bool CDiceEBF::Run(CValidationState& state, const std::vector<CTxOut>& vout)
{
    // Walk backwards to the betting block index
    auto bettingBlockIndex = mapBlockIndex[block.hashPrevBlock];
    for (int i = 1; i < DICE_EBF_BLOCK_DELAY; i++) {
        bettingBlockIndex = mapBlockIndex[bettingBlockIndex->pprev->GetBlockHash()];
    }

    // Fetch the betting block
    CBlock bettingBlock;
    if (bettingBlockIndex->nHeight <= chainActive.Height() && ReadBlockFromDisk(bettingBlock, bettingBlockIndex)) {
        auto seed = GetRandomSeed();

        auto left = seed >> 128;
        auto right = seed << 128 >> 128;

        auto dice1 = left - (left / 6);
        auto dice2 = right - (right / 6);

        // Foreach bet made at 6 blocks ago
        //   Check if it won
        //      If yes => perform the payouts
    }

    return true;
}

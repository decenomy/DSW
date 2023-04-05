// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_JACKPOT_LOTTERY_H
#define DECENOMY_EBF_JACKPOT_LOTTERY_H

#include "ebf/jackpot/jackpot.h"

class CLotteryEBF : public CJackpotEBF {
public:
    CLotteryEBF(const CBlock& block) : CJackpotEBF(block) {}
    void CheckAndRun(const CValidationState& state, const std::vector<CTxOut>& vout);
};

#endif // DECENOMY_EBF_JACKPOT_LOTTERY_H
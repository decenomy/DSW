// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_JACKPOT_ROULETTE_H
#define DECENOMY_EBF_JACKPOT_ROULETTE_H

#include "ebf/jackpot/jackpot.h"

class CRouletteEBF : public CJackpotEBF {
public:
    CRouletteEBF(const CBlock& block) : CJackpotEBF(block) {}
    bool Run(CValidationState& state, std::vector<CTxOut>& vout);
};

#endif // DECENOMY_EBF_JACKPOT_ROULETTE_H
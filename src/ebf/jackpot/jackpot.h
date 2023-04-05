// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_JACKPOT_H
#define DECENOMY_EBF_JACKPOT_H

#include "consensus/validation.h"
#include "ebf/ebf.h"
#include "primitives/block.h"

class CJackpotEBF : CEBF {
protected:
    uint256 GetRandomSeed(const CBlock& block);
public:
    CJackpotEBF(const CBlock& block) : CEBF(block) {}
};

#endif // DECENOMY_EBF_JACKPOT_H
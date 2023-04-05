// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_SYSTEM_SPORK_H
#define DECENOMY_EBF_SYSTEM_SPORK_H

#include "ebf/ebf.h"

class CSporkEBF : public CEBF {
public:
    CSporkEBF(const CBlock& block) : CEBF(block) {}
    void CheckAndRun(const CValidationState& state, const std::vector<CTxOut>& vout);
};

#endif // DECENOMY_EBF_SYSTEM_SPORK_H
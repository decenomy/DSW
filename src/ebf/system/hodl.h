// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_SYSTEM_HODL_H
#define DECENOMY_EBF_SYSTEM_HODL_H

#include "ebf/ebf.h"

class CHodlEBF : public CEBF {
public:
    CHodlEBF(const CBlock& block) : CEBF(block) {}
    bool Run(CValidationState& state, std::vector<CTxOut>& vout);
};

#endif // DECENOMY_EBF_SYSTEM_HODL_H
// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "consensus/validation.h"
#include "ebf/ebf.h"
#include "primitives/block.h"

class CJackpotEBF {
    public:
        virtual void ProcessBlock(CValidationState& state, const CBlock& block) = 0;
    protected:
        static uint256 GetRandomSeed(const CBlock& block);
};

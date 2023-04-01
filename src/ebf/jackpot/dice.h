// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/ebf.h"

enum Dice {
    One     = 1,
    Two     = 2,
    Three   = 3,
    Four    = 4,
    Five    = 5,
    Six     = 6,
}

class DiceDraw
{
    std::pair<Dice, Dice> result;
public:
    DiceDraw(const CBlockIndex* pindex);

    const std::pair<Dice, Dice> Result() const;
}
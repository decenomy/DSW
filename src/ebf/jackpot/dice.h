// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_JACKPOT_DICE_H
#define DECENOMY_EBF_JACKPOT_DICE_H

#include "ebf/jackpot/jackpot.h"
#include "script/script.h"

enum DiceFace {
    One     = 0x01,
    Two     = 0x02,
    Three   = 0x03,
    Four    = 0x04,
    Five    = 0x05,
    Six     = 0x06,
};

enum DiceBetType {
    OverSeven   = 0x00, // Sum = 2 to 6 
    UnderSeven  = 0x01, // Sum = 8 to 12
    SumOfTwo    = 0x02, // Sum = 2
    SumOfThree  = 0x03, // ...
    SumOfFour   = 0x04, // ...
    SumOfFive   = 0x05, // ...
    SumOfSix    = 0x06, // ...
    SumOfSeven  = 0x07, // ...
    SumOfEight  = 0x08, // ...
    SumOfNine   = 0x09, // ...
    SumOfTen    = 0x0A, // ...
    SumOfEleven = 0x0B, // ...
    SumOfTwelve = 0x0C, // Sum = 12
    SingleOne   = 0x0D, // One of the dices are 1
    SingleTwo   = 0x0E, // ...
    SingleThree = 0x0F, // ...
    SingleFour  = 0x10, // ...
    SingleFive  = 0x11, // ...
    SingleSix   = 0x12, // One of the dices are 6
    AnyDouble   = 0x13, // A double of any number 
    DoubleOne   = 0x14, // Double 1s
    DoubleTwo   = 0x15, // ...
    DoubleThree = 0x16, // ...
    DoubleFour  = 0x17, // ...
    DoubleFive  = 0x18, // ...
    DoubleSix   = 0x19, // Double 6s
    EvenSum     = 0x1A, // Even Sum 
    OddSum      = 0x1B, // Odd Sum
};

class CDiceEBF : public CJackpotEBF {
public:
    CDiceEBF(const CBlock& block) : CJackpotEBF(block) {}
    void ProcessBlock(CValidationState& state);

    static CScript GetBetScript(DiceBetType betType, CAmount amount, CKeyID payee);
};

#endif // DECENOMY_EBF_JACKPOT_DICE_H
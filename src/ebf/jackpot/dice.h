// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DECENOMY_EBF_JACKPOT_DICE_H
#define DECENOMY_EBF_JACKPOT_DICE_H

#include "ebf/jackpot/jackpot.h"

#define DICE_EBF_SCRIPT_SIZE    26
#define DICE_EBF_MIN_AMOUNT     COIN
#define DICE_EBF_MAX_AMOUNT     1000 * COIN
#define DICE_EBF_BLOCK_DELAY    6

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

class CDiceEBFBet : public CEBFAction {
private:
    DiceBetType betType; 
    CKeyID payee;
public:
    CDiceEBFBet(DiceBetType betType, CAmount amount, CKeyID payee);
    CDiceEBFBet(CTxOut& txout);

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        CEBFAction::SerializationOp(s, ser_action);

        uint8_t betType = static_cast<uint8_t>(this->betType);
        READWRITE(betType);
        if (ser_action.ForRead()) {
            this->betType = static_cast<DiceBetType>(betType);
        }

        READWRITE(payee);
    }
    
    CTxOut ToTxOut();

    static bool CheckTxOut(const CTxOut& txout, CValidationState &state);
    CAmount CheckResults(DiceFace dice1, DiceFace dice2);
    CScript GeneratePayoutScript();
};

class CDiceEBF : public CJackpotEBF {
public:
    CDiceEBF(const CBlock& block) : CJackpotEBF(block) {}
    bool Run(CValidationState& state, std::vector<CTxOut>& vout);
};

#endif // DECENOMY_EBF_JACKPOT_DICE_H
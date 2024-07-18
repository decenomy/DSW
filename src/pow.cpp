// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pow.h"

#include "chain.h"
#include "chainparams.h"
#include "main.h"
#include "primitives/block.h"
#include "uint256.h"
#include "util.h"

#include <math.h>

unsigned int GetNextWorkRequiredPOW(const CBlockIndex* pindexLast)
{
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();

    /* current difficulty formula, kyanite - DarkGravity v3, written by Evan Duffield - evan@dashpay.io */
    const CBlockIndex* BlockLastSolved = pindexLast;
    const CBlockIndex* BlockReading = pindexLast;
    int64_t nActualTimespan = 0;
    int64_t LastBlockTime = 0;
    int64_t PastBlocksMin = 24;
    int64_t PastBlocksMax = 24;
    int64_t CountBlocks = 0;
    uint256 PastDifficultyAverage;
    uint256 PastDifficultyAveragePrev;

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || BlockLastSolved->nHeight < PastBlocksMin) {
        return consensus.powLimit.GetCompact();
    }

    for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
        if (PastBlocksMax > 0 && i > PastBlocksMax) {
            break;
        }
        CountBlocks++;

        if (CountBlocks <= PastBlocksMin) {
            if (CountBlocks == 1) {
                PastDifficultyAverage.SetCompact(BlockReading->nBits);
            } else {
                PastDifficultyAverage = ((PastDifficultyAveragePrev * CountBlocks) + (uint256().SetCompact(BlockReading->nBits))) / (CountBlocks + 1);
            }
            PastDifficultyAveragePrev = PastDifficultyAverage;
        }

        if (LastBlockTime > 0) {
            int64_t Diff = (LastBlockTime - BlockReading->GetBlockTime());
            nActualTimespan += Diff;
        }
        LastBlockTime = BlockReading->GetBlockTime();

        if (BlockReading->pprev == NULL) {
            assert(BlockReading);
            break;
        }
        BlockReading = BlockReading->pprev;
    }

    uint256 bnNew(PastDifficultyAverage);

    int64_t _nTargetTimespan = CountBlocks * consensus.nTargetSpacing;

    if (nActualTimespan < _nTargetTimespan / 3)
        nActualTimespan = _nTargetTimespan / 3;
    if (nActualTimespan > _nTargetTimespan * 3)
        nActualTimespan = _nTargetTimespan * 3;

    // Retarget
    bnNew *= nActualTimespan;
    bnNew /= _nTargetTimespan;

    if (bnNew > consensus.powLimit) {
        bnNew = consensus.powLimit;
    }

    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredPOS(const CBlockIndex* pindexLast)
{
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();

    const auto nHeight = pindexLast->nHeight + 1;
    const auto fIsTimeProtocolV2 = consensus.IsTimeProtocolV2(nHeight);
    const auto nTargetTimespan = consensus.TargetTimespan(nHeight);

    int64_t nActualSpacing = 0;
    if (pindexLast->nHeight != 0)
        nActualSpacing = pindexLast->GetBlockTime() - pindexLast->pprev->GetBlockTime();
    if (nActualSpacing < 0)
        nActualSpacing = 1;
    if (fIsTimeProtocolV2 && nActualSpacing > consensus.nTargetSpacing * 10)
        nActualSpacing = consensus.nTargetSpacing * 10;

    // ppcoin: target change every block
    // ppcoin: retarget with exponential moving toward target spacing
    uint256 bnNew;
    bnNew.SetCompact(pindexLast->nBits);

    // On first block with V2 time protocol, reduce the difficulty by a factor 16
    if (fIsTimeProtocolV2 && !consensus.IsTimeProtocolV2(pindexLast->nHeight))
        bnNew <<= 4;

    int64_t nInterval = nTargetTimespan / consensus.nTargetSpacing;
    bnNew *= ((nInterval - 1) * consensus.nTargetSpacing + nActualSpacing + nActualSpacing);
    bnNew /= ((nInterval + 1) * consensus.nTargetSpacing);

    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    return bnNew.GetCompact();
}

// It is just used for logging, remove it later on
double GetDifficulty(uint32_t nBits)
{
    int nShift = (nBits >> 24) & 0xff;

    double dDiff = (double)0x0000ffff / (double)(nBits & 0x00ffffff);

    while (nShift < 29) {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29) {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;
}

unsigned int GetNextWorkRequiredPOSV2(const CBlockIndex* pIndexLast)
{
    // Retrieve the parameters and consensus rules
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();
    
    // Get the current block height
    const auto nPrevHeight = pIndexLast->nHeight;
    const auto nHeight = nPrevHeight + 1;
    
    // Define the target block spacing time
    const auto& nTargetSpacing = consensus.nTargetSpacing;

    // Determine the target timespan and maximum adjustment factor based on current height
    auto nTargetTimespan = consensus.TargetTimespan(nHeight);
    auto nMaximumAdjustmentFactor = consensus.nMaximumAdjustmentFactor;

    // Perform a long adjustment if the current height is a multiple of the target timespan
    if (nHeight % (nTargetTimespan / nTargetSpacing) == 0) {
        nTargetTimespan = consensus.nTargetLongTimespan;
        nMaximumAdjustmentFactor = consensus.nMaximumLongAdjustmentFactor;
    }

    std::cout << "============================================================" << std::endl;

    std::cout << "GetNextWorkRequiredPOSV2 consensus.nMaximumAdjustmentFactor: " << consensus.nMaximumAdjustmentFactor << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 consensus.nMaximumLongAdjustmentFactor: " << consensus.nMaximumLongAdjustmentFactor << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 consensus.nTargetTimespan: " << consensus.TargetTimespan(nHeight) << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 consensus.nTargetLongTimespan: " << consensus.nTargetLongTimespan << std::endl;

    // Adjust the target timespan for the early stages of the blockchain
    nTargetTimespan = std::min(nTargetTimespan, chainActive.Height() * nTargetSpacing);

    // Calculate the number of blocks in the adjustment period
    const auto nBlockspan = static_cast<int>(nTargetTimespan / nTargetSpacing);

    // Get the start and end blocks for the adjustment period
    const auto pStartBlock = chainActive[std::max(nPrevHeight - nBlockspan, 0)];
    const auto pEndBlock = pIndexLast;

    // Calculate the actual timespan between the start and end blocks
    int64_t nActualTimespan = pEndBlock->GetBlockTime() - pStartBlock->GetBlockTime();
    
    // Limit the adjustment step using the maximum adjustment factor
    const auto nMinTimespan = (nTargetTimespan * (100LL - nMaximumAdjustmentFactor)) / 100LL;
    const auto nMaxTimespan = (nTargetTimespan * (100LL + nMaximumAdjustmentFactor)) / 100LL;

    std::cout << "GetNextWorkRequiredPOSV2 nHeight: " << nHeight << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 nActualTimespan: " << nActualTimespan << std::endl;

    std::cout << "GetNextWorkRequiredPOSV2 nMinTimespan: " << nMinTimespan << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 nMaxTimespan: " << nMaxTimespan << std::endl;

    // Clamp the actual timespan to be within the min and max bounds
    if (nActualTimespan < nMinTimespan)
        nActualTimespan = nMinTimespan;
    if (nActualTimespan > nMaxTimespan)
        nActualTimespan = nMaxTimespan;

    std::cout << "GetNextWorkRequiredPOSV2 nBits: " << GetDifficulty(pIndexLast->nBits) << std::endl;

    std::cout << "GetNextWorkRequiredPOSV2 nActualTimespan: " << nActualTimespan << std::endl;
    std::cout << "GetNextWorkRequiredPOSV2 nTargetTimespan: " << nTargetTimespan << std::endl;

    // Retarget the difficulty based on the clamped actual timespan
    uint256 bnNew;
    bnNew.SetCompact(pIndexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    const CBlockIndex* BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - DAY_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV2 nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    std::cout << "GetNextWorkRequiredPOSV2 nBits: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredPOSV3(const CBlockIndex* pIndexLast)
{
    // Retrieve the parameters and consensus rules
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();
    
    // Get the current block height
    const auto nPrevHeight = pIndexLast->nHeight;
    const auto nHeight = nPrevHeight + 1;
    
    // Define the target block spacing time
    const auto& nTargetSpacing = consensus.nTargetSpacing;

    const int nBlocksPerHour = HOUR_IN_SECONDS / nTargetSpacing;
    const int nBlocksPerDay  = DAY_IN_SECONDS  / nTargetSpacing;
    const int nBlocksPerWeek = WEEK_IN_SECONDS / nTargetSpacing;

    std::cout << "============================================================" << std::endl;

    std::cout << "GetNextWorkRequiredPOSV3 consensus.nTargetSpacing: " << nTargetSpacing << std::endl;

    std::cout << "GetNextWorkRequiredPOSV3 nBits start: " << GetDifficulty(pIndexLast->nBits) << std::endl;
    
    const int64_t nAlpha = 2; // EMA Smoothing factor
    const int64_t nN = 20; // EMA period

    uint256 bnNew(0);
    
    if(pIndexLast->nHeight > nN) {
        
        const CBlockIndex* pIndexReading = pIndexLast;

        for (unsigned int i = 0;
            pIndexReading && pIndexReading->nHeight && i < nN;
            i++
        ) {
            uint256 currentValue;
            currentValue.SetCompact(pIndexReading->nBits);

            bnNew = ((currentValue * nAlpha) / (nN + 1)) + ((bnNew * (nN + 1 - nAlpha)) / (nN + 1));

            pIndexReading = pIndexReading->pprev;
        }

        std::cout << "GetNextWorkRequiredPOSV3 nBits EMA: " << GetDifficulty(bnNew.GetCompact()) << std::endl;
    } else {
        bnNew.SetCompact(pIndexLast->nBits);
    }

    // Retarget the difficulty based on a PID controller based function
    int64_t nActualSpacing = nHeight > 1 ? pIndexLast->GetBlockTime() - pIndexLast->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualSpacingError = nActualSpacing - nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV3 nActualSpacing: " << nActualSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV3 nActualSpacingError: " << nActualSpacingError << std::endl;
    
    int64_t nActualPreviousSpacing = nHeight > 2 ? pIndexLast->pprev->GetBlockTime() - pIndexLast->pprev->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualPreviousSpacingError = nActualPreviousSpacing - nTargetSpacing;
    
    std::cout << "GetNextWorkRequiredPOSV3 nActualPreviousSpacing: " << nActualPreviousSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV3 nActualPreviousSpacingError: " << nActualPreviousSpacingError << std::endl;
    
    int64_t nDiffErrorSpacing = nActualSpacingError - nActualPreviousSpacingError;
    std::cout << "GetNextWorkRequiredPOSV3 nDiffErrorSpacing: " << nDiffErrorSpacing << std::endl;

    int64_t nAccumulatedTargetSpacing = WEEK_IN_SECONDS;
    int64_t nAccumulatedSpacing = nHeight > nBlocksPerWeek ?
        pIndexLast->GetBlockTime() - chainActive[nPrevHeight - nBlocksPerWeek]->GetBlockTime() :
        nAccumulatedTargetSpacing;
    int64_t nAccumulatedTargetSpacingError = nAccumulatedSpacing - nAccumulatedTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV3 nAccumulatedSpacing: " << nAccumulatedSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV3 nAccumulatedTargetSpacingError: " << nAccumulatedTargetSpacingError << std::endl;

    int64_t nKp = 2 * nBlocksPerHour;
    int64_t nKd = 4 * nBlocksPerHour;
    int64_t nKi = 8 * nBlocksPerHour;

    std::cout << "GetNextWorkRequiredPOSV3 Kp factor: " << nKp << std::endl;
    std::cout << "GetNextWorkRequiredPOSV3 Kd factor: " << nKd << std::endl;
    std::cout << "GetNextWorkRequiredPOSV3 Ki factor: " << nKi << std::endl;

    // bnNew *= nActualSpacing + ((nKp - 1) * nTargetSpacing);
    // bnNew /= nKp * nTargetSpacing;

    if (nActualSpacingError > 0) {
        bnNew += (bnNew * nActualSpacingError) / (nKd * nTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nActualSpacingError) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV3 nBits Kp: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nDiffErrorSpacing > 0) {
        bnNew += (bnNew * nDiffErrorSpacing) / (nKd * nTargetSpacing);
    } else {
        bnNew -= (bnNew * -nDiffErrorSpacing) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV3 nBits Kd: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // bnNew *= nAccumulatedSpacing + ((nKi - 1) * nAccumulatedTargetSpacing);
    // bnNew /= nKi * nAccumulatedTargetSpacing;

    if (nAccumulatedTargetSpacingError > 0) {
        bnNew += (bnNew * nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV3 nBits Ki: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    std::cout << "GetNextWorkRequiredPOSV3 nBits return: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredPOSV4(const CBlockIndex* pIndexLast)
{
    // Retrieve the parameters and consensus rules
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();

    std::cout << "============================================================" << std::endl;
    
    // Get the current block height
    const auto nPrevHeight = pIndexLast->nHeight;
    const auto nHeight = nPrevHeight + 1;

    std::cout << "GetNextWorkRequiredPOSV4 nHeight: " << nHeight << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 nPrevHeight: " << nPrevHeight << std::endl;
    
    // Define the target block spacing time
    const auto& nTargetSpacing = consensus.nTargetSpacing;

    const int nBlocksPerHour = HOUR_IN_SECONDS / nTargetSpacing;
    const int nBlocksPerDay  = DAY_IN_SECONDS  / nTargetSpacing;
    const int nBlocksPerWeek = WEEK_IN_SECONDS / nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV4 consensus.nTargetSpacing: " << nTargetSpacing << std::endl;

    std::cout << "GetNextWorkRequiredPOSV4 nBits start: " << GetDifficulty(pIndexLast->nBits) << std::endl;
    
    const int64_t nN = 20; // EMA period

    uint256 bnNew;
    const CBlockIndex* pIndexReading = pIndexLast;

    for (unsigned int nCountBlocks = 1; 
         pIndexReading && pIndexReading->nHeight && nCountBlocks <= nN; 
         nCountBlocks++
    ) {
        uint256 bnCurrent = uint256().SetCompact(pIndexReading->nBits);
        if (nCountBlocks == 1) {
            bnNew = bnCurrent;
        } else {
            // NOTE: that's not really an average...
            bnNew = (bnNew * nCountBlocks + bnCurrent) / (nCountBlocks + 1);
        }

        pIndexReading = pIndexReading->pprev;
    }

    std::cout << "GetNextWorkRequiredPOSV4 nBits Smoothing: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Retarget the difficulty based on a PID controller based function
    int64_t nActualSpacing = nHeight > 1 ? pIndexLast->GetBlockTime() - pIndexLast->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualSpacingError = nActualSpacing - nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV4 nActualSpacing: " << nActualSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 nActualSpacingError: " << nActualSpacingError << std::endl;
    
    int64_t nActualPreviousSpacing = nHeight > 2 ? pIndexLast->pprev->GetBlockTime() - pIndexLast->pprev->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualPreviousSpacingError = nActualPreviousSpacing - nTargetSpacing;
    
    std::cout << "GetNextWorkRequiredPOSV4 nActualPreviousSpacing: " << nActualPreviousSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 nActualPreviousSpacingError: " << nActualPreviousSpacingError << std::endl;
    
    int64_t nDiffErrorSpacing = nActualSpacingError - nActualPreviousSpacingError;
    std::cout << "GetNextWorkRequiredPOSV4 nDiffErrorSpacing: " << nDiffErrorSpacing << std::endl;

    int64_t nAccumulatedTargetSpacing = WEEK_IN_SECONDS;
    int64_t nAccumulatedSpacing = nHeight > nBlocksPerWeek ?
        pIndexLast->GetBlockTime() - chainActive[nPrevHeight - nBlocksPerWeek]->GetBlockTime() :
        nAccumulatedTargetSpacing;
    int64_t nAccumulatedTargetSpacingError = nAccumulatedSpacing - nAccumulatedTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV4 nAccumulatedSpacing: " << nAccumulatedSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 nAccumulatedTargetSpacingError: " << nAccumulatedTargetSpacingError << std::endl;

    int64_t nKp = 2 * nBlocksPerHour;
    int64_t nKd = 4 * nBlocksPerHour;
    int64_t nKi = 8 * nBlocksPerHour;

    std::cout << "GetNextWorkRequiredPOSV4 Kp factor: " << nKp << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 Kd factor: " << nKd << std::endl;
    std::cout << "GetNextWorkRequiredPOSV4 Ki factor: " << nKi << std::endl;

    if (nActualSpacingError > 0) {
        bnNew += (bnNew * nActualSpacingError) / (nKd * nTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nActualSpacingError) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV4 nBits Kp: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nDiffErrorSpacing > 0) {
        bnNew += (bnNew * nDiffErrorSpacing) / (nKd * nTargetSpacing);
    } else {
        bnNew -= (bnNew * -nDiffErrorSpacing) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV4 nBits Kd: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nAccumulatedTargetSpacingError > 0) {
        bnNew += (bnNew * nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV4 nBits Ki: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    const CBlockIndex* BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - DAY_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV4 24h nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    std::cout << "GetNextWorkRequiredPOSV4 nBits return: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredPOSV5(const CBlockIndex* pIndexLast)
{
    // Retrieve the parameters and consensus rules
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();

    std::cout << "============================================================" << std::endl;
    
    // Get the current block height
    const auto nPrevHeight = pIndexLast->nHeight;
    const auto nHeight = nPrevHeight + 1;

    std::cout << "GetNextWorkRequiredPOSV5 nHeight: " << nHeight << std::endl;
    
    // Fetch the target block spacing time and timespan
    const auto& nTargetSpacing = consensus.nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV5 consensus.nTargetSpacing: " << nTargetSpacing << std::endl;
    
    // Retarget the difficulty based on a PID controller based function
    int64_t nActualSpacing = nHeight > 1 ? pIndexLast->GetBlockTime() - pIndexLast->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualSpacingError = nActualSpacing - nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV5 nActualSpacing: " << nActualSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV5 nActualSpacingError: " << nActualSpacingError << std::endl;
    
    int64_t nActualPreviousSpacing = nHeight > 2 ? pIndexLast->pprev->GetBlockTime() - pIndexLast->pprev->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualPreviousSpacingError = nActualPreviousSpacing - nTargetSpacing;
    
    std::cout << "GetNextWorkRequiredPOSV5 nActualPreviousSpacing: " << nActualPreviousSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV5 nActualPreviousSpacingError: " << nActualPreviousSpacingError << std::endl;
    
    int64_t nDiffErrorSpacing = nActualSpacingError - nActualPreviousSpacingError;
    std::cout << "GetNextWorkRequiredPOSV5 nDiffErrorSpacing: " << nDiffErrorSpacing << std::endl;

    const int nBlocksPerWeek = WEEK_IN_SECONDS / nTargetSpacing;

    int64_t nAccumulatedTargetSpacing = WEEK_IN_SECONDS;
    int64_t nAccumulatedSpacing = nHeight > nBlocksPerWeek ?
        pIndexLast->GetBlockTime() - chainActive[nPrevHeight - nBlocksPerWeek]->GetBlockTime() :
        nAccumulatedTargetSpacing;
    int64_t nAccumulatedTargetSpacingError = nAccumulatedSpacing - nAccumulatedTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV5 nAccumulatedSpacing: " << nAccumulatedSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV5 nAccumulatedTargetSpacingError: " << nAccumulatedTargetSpacingError << std::endl;

    const int nBlocksPerHour = HOUR_IN_SECONDS / nTargetSpacing;

    int64_t nKp = nBlocksPerHour / 2;   // 30 min
    int64_t nKd = nKp * 8;              // 240 min = 4h
    int64_t nKi = nKd * 8;              // 1920 min = 32h

    std::cout << "GetNextWorkRequiredPOSV5 Kp factor: " << nKp << std::endl;
    std::cout << "GetNextWorkRequiredPOSV5 Kd factor: " << nKd << std::endl;
    std::cout << "GetNextWorkRequiredPOSV5 Ki factor: " << nKi << std::endl;

    uint256 bnNew;
    bnNew.SetCompact(pIndexLast->nBits);

    std::cout << "GetNextWorkRequiredPOSV5 nBits start: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nActualSpacingError > 0) {
        bnNew += (bnNew * nActualSpacingError) / (nKd * nTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nActualSpacingError) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV5 nBits Kp: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    uint256 bnNew2;
    bnNew2.SetCompact(pIndexLast->nBits);

    bnNew2 *= nActualSpacing + ((nKd - 1) * nTargetSpacing);
    bnNew2 /= nKd * nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV5 nBits Kp v2: " << GetDifficulty(bnNew2.GetCompact()) << std::endl;

    if (nDiffErrorSpacing > 0) {
        bnNew += (bnNew * nDiffErrorSpacing) / (nKd * nTargetSpacing);
    } else {
        bnNew -= (bnNew * -nDiffErrorSpacing) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV5 nBits Kd: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nAccumulatedTargetSpacingError > 0) {
        bnNew += (bnNew * nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nAccumulatedTargetSpacingError) / (nKd * nAccumulatedTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV5 nBits Ki: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    const CBlockIndex* BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - DAY_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV5 24h nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - HOUR_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV5 1h nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    std::cout << "GetNextWorkRequiredPOSV5 nBits return: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequiredPOSV6(const CBlockIndex* pIndexLast)
{
    // Retrieve the parameters and consensus rules
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();

    std::cout << "============================================================" << std::endl;
    
    // Get the current block height
    const auto nPrevHeight = pIndexLast->nHeight;
    const auto nHeight = nPrevHeight + 1;

    std::cout << "GetNextWorkRequiredPOSV6 nHeight: " << nHeight << std::endl;
    
    // Fetch the target block spacing time and timespan
    const auto& nTargetSpacing = consensus.nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV6 consensus.nTargetSpacing: " << nTargetSpacing << std::endl;
    
    // Retarget the difficulty based on a PID controller based function
    int64_t nActualSpacing = nHeight > 1 ? pIndexLast->GetBlockTime() - pIndexLast->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualSpacingError = nActualSpacing - nTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV6 nActualSpacing: " << nActualSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV6 nActualSpacingError: " << nActualSpacingError << std::endl;
    
    int64_t nActualPreviousSpacing = nHeight > 2 ? pIndexLast->pprev->GetBlockTime() - pIndexLast->pprev->pprev->GetBlockTime() : nTargetSpacing;
    int64_t nActualPreviousSpacingError = nActualPreviousSpacing - nTargetSpacing;
    
    std::cout << "GetNextWorkRequiredPOSV6 nActualPreviousSpacing: " << nActualPreviousSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV6 nActualPreviousSpacingError: " << nActualPreviousSpacingError << std::endl;
    
    int64_t nDiffSpacingError = nActualSpacingError - nActualPreviousSpacingError;
    std::cout << "GetNextWorkRequiredPOSV6 nDiffSpacingError: " << nDiffSpacingError << std::endl;

    const int nBlocksPerWeek = WEEK_IN_SECONDS / nTargetSpacing;

    int64_t nAccumulatedTargetSpacing = WEEK_IN_SECONDS;
    int64_t nAccumulatedSpacing = nHeight > nBlocksPerWeek ?
        pIndexLast->GetBlockTime() - chainActive[nPrevHeight - nBlocksPerWeek]->GetBlockTime() :
        nAccumulatedTargetSpacing;
    int64_t nAccumulatedTargetSpacingError = nAccumulatedSpacing - nAccumulatedTargetSpacing;

    std::cout << "GetNextWorkRequiredPOSV6 nAccumulatedSpacing: " << nAccumulatedSpacing << std::endl;
    std::cout << "GetNextWorkRequiredPOSV6 nAccumulatedTargetSpacingError: " << nAccumulatedTargetSpacingError << std::endl;

    const int nBlocksPerHour = HOUR_IN_SECONDS / nTargetSpacing;

    int64_t nKp = nBlocksPerHour / 2;   // 30 min
    int64_t nKd = nKp * 8;              // 240 min = 4h
    int64_t nKi = nKd * 8;              // 1920 min = 32h

    std::cout << "GetNextWorkRequiredPOSV6 Kp factor: " << nKp << std::endl;
    std::cout << "GetNextWorkRequiredPOSV6 Kd factor: " << nKd << std::endl;
    std::cout << "GetNextWorkRequiredPOSV6 Ki factor: " << nKi << std::endl;

    uint256 bnNew;
    bnNew.SetCompact(pIndexLast->nBits);

    std::cout << "GetNextWorkRequiredPOSV6 nBits start: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nHeight == 1402101) {
        bnNew <<= 4; // just for testing purposes
        std::cout << "GetNextWorkRequiredPOSV6 nBits @1402101: " << GetDifficulty(bnNew.GetCompact()) << std::endl;
    }

    if (nActualSpacingError > 0) {
        bnNew += (bnNew * nActualSpacingError) / (nKp * nTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nActualSpacingError) / (nKp * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV6 nBits Kp: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nDiffSpacingError > 0) {
        bnNew += (bnNew * nDiffSpacingError) / (nKd * nTargetSpacing);
    } else {
        bnNew -= (bnNew * -nDiffSpacingError) / (nKd * nTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV6 nBits Kd: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    if (nAccumulatedTargetSpacingError > 0) {
        bnNew += (bnNew * nAccumulatedTargetSpacingError) / (nKi * nAccumulatedTargetSpacing);     
    } else {
        bnNew -= (bnNew * -nAccumulatedTargetSpacingError) / (nKi * nAccumulatedTargetSpacing);
    }

    std::cout << "GetNextWorkRequiredPOSV6 nBits Ki: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    const CBlockIndex* BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - DAY_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV6 24h nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    BlockReading = pIndexLast;

    for (unsigned int i = 0; BlockReading && BlockReading->nHeight > 0; i++) {
        if(BlockReading->nTime < (pIndexLast->nTime - HOUR_IN_SECONDS)) {
            std::cout << "GetNextWorkRequiredPOSV6 1h nBlocks: " << i << std::endl;
            break;
        }

        BlockReading = BlockReading->pprev;
    }

    std::cout << "GetNextWorkRequiredPOSV6 nBits return: " << GetDifficulty(bnNew.GetCompact()) << std::endl;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader* pblock)
{
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();
    const auto nHeight = pindexLast->nHeight + 1;

    if (params.IsRegTestNet()) return pindexLast->nBits;

    if (nHeight > 1402100) {
        return GetNextWorkRequiredPOSV6(pindexLast);
    }

    if (nHeight > 1397500) {
        GetNextWorkRequiredPOSV6(pindexLast);
        return GetNextWorkRequiredPOSV5(pindexLast);
    }

    if (nHeight > 1391100) {
        GetNextWorkRequiredPOSV5(pindexLast);
        return GetNextWorkRequiredPOSV4(pindexLast);
    }

    if (nHeight > 1391000) {
        GetNextWorkRequiredPOSV4(pindexLast);
        return GetNextWorkRequiredPOSV3(pindexLast);
    }

    if (consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_POS_V3)) {
        GetNextWorkRequiredPOSV3(pindexLast); // Just for comparison, remove it later on
        return GetNextWorkRequiredPOSV2(pindexLast);
    }

    if (consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_POS)) {
        return GetNextWorkRequiredPOS(pindexLast);
    }

    return GetNextWorkRequiredPOW(pindexLast);
}

bool CheckProofOfWork(uint256 hash, unsigned int nBits)
{
    bool fNegative;
    bool fOverflow;
    uint256 bnTarget;

    if (Params().IsRegTestNet()) return true;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check range
    if (fNegative || bnTarget.IsNull() || fOverflow || bnTarget > Params().GetConsensus().powLimit)
        return error("CheckProofOfWork() : nBits below minimum work");

    // Check proof of work matches claimed amount
    if (hash > bnTarget)
        return error("CheckProofOfWork() : hash doesn't match nBits");

    return true;
}

uint256 GetBlockProof(const CBlockIndex& block)
{
    uint256 bnTarget;
    bool fNegative;
    bool fOverflow;
    bnTarget.SetCompact(block.nBits, &fNegative, &fOverflow);
    if (fNegative || fOverflow || bnTarget.IsNull())
        return UINT256_ZERO;
    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a uint256. However, as 2**256 is at least as large
    // as bnTarget+1, it is equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1,
    // or ~bnTarget / (nTarget+1) + 1.
    return (~bnTarget / (bnTarget + 1)) + 1;
}

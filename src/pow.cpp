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
    if (nHeight % nTargetTimespan == 0) {
        nTargetTimespan = consensus.nTargetLongTimespan;
        nMaximumAdjustmentFactor = consensus.nMaximumLongAdjustmentFactor;
    }

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

    // Clamp the actual timespan to be within the min and max bounds
    if (nActualTimespan < nMinTimespan)
        nActualTimespan = nMinTimespan;
    if (nActualTimespan > nMaxTimespan)
        nActualTimespan = nMaxTimespan;

    // Retarget the difficulty based on the clamped actual timespan
    uint256 bnNew;
    bnNew.SetCompact(pIndexLast->nBits);
    bnNew *= nActualTimespan;
    bnNew /= nTargetTimespan;

    // Ensure the new difficulty does not exceed the minimum allowed by consensus
    if (bnNew > consensus.posLimit)
        bnNew = consensus.posLimit;

    // Return the new difficulty in compact format
    return bnNew.GetCompact();
}

unsigned int GetNextWorkRequired(const CBlockIndex* pindexLast, const CBlockHeader* pblock)
{
    const auto& params = Params();
    const auto& consensus = params.GetConsensus();
    const auto nHeight = pindexLast->nHeight + 1;

    if (params.IsRegTestNet()) return pindexLast->nBits;

    if (consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_POS_V3)) {
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

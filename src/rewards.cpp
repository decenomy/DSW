// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2024 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "fs.h"
#include "rewards.h"
#include "masternode.h"
#include "masternode-sync.h"
#include "sqlite3/sqlite3.h"
#include "timedata.h"

#include <unordered_map>

std::unordered_map<int, CAmount> mDynamicRewards;
sqlite3* db;

bool CRewards::Init()
{
    const auto& dbFile = GetDataDir() / "chainstate" / "rewards.db";

    // Create and/or open the database
    int rc = sqlite3_open(dbFile.c_str(), &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Create the rewards table
    const char* create_table_query = "CREATE TABLE IF NOT EXISTS rewards (height INT PRIMARY KEY, amount INTEGER)";
    rc = sqlite3_exec(db, create_table_query, NULL, NULL, NULL);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);

    return true;
}

bool CRewards::Shutdown()
{
    return false;
}

int CRewards::GetDynamicRewardsEpoch(int nHeight)
{
    auto& consensus = Params().GetConsensus();
    const auto nRewardAdjustmentInterval = consensus.nRewardAdjustmentInterval;
    return nHeight / nRewardAdjustmentInterval;
}

int CRewards::GetDynamicRewardsEpochHeight(int nHeight)
{
    auto& consensus = Params().GetConsensus();
    const auto nRewardAdjustmentInterval = consensus.nRewardAdjustmentInterval;
    return GetDynamicRewardsEpoch(nHeight) * nRewardAdjustmentInterval;
}

bool CRewards::IsDynamicRewardsEpochHeight(int nHeight)
{
    return GetDynamicRewardsEpochHeight(nHeight) == nHeight;
}

bool CRewards::ConnectBlock(CBlockIndex* pindex, CAmount nSubsidy, CCoinsViewCache& coins)
{
    auto& consensus = Params().GetConsensus();
    const auto nHeight = pindex->nHeight;

    if(consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_DYNAMIC_REWARDS)) 
    {
        if (IsDynamicRewardsEpochHeight(nHeight)) 
        {
            auto nBlocksPerDay = DAY_IN_SECONDS / consensus.nTargetSpacing;
            auto nBlocksPerWeek = WEEK_IN_SECONDS / consensus.nTargetSpacing;
            auto nBlocksPerMonth = MONTH_IN_SECONDS / consensus.nTargetSpacing;

            // get total money supply
            const auto nMoneySupply = pindex->nMoneySupply.get();

            // get the current masternode collateral, and the next week collateral
            auto nCollateralAmount = CMasternode::GetMasternodeNodeCollateral(nHeight);
            auto nNextWeekCollateralAmount = CMasternode::GetMasternodeNodeCollateral(nHeight + nBlocksPerWeek);

            // calculate the current circulating supply
            CAmount nCirculatingSupply = 0;
            std::unique_ptr<CCoinsViewCursor> pcursor(coins.Cursor());

            while (pcursor->Valid()) {
                COutPoint key;
                Coin coin;
                if (pcursor->GetKey(key) && pcursor->GetValue(coin)) {
                    // ----------- burn address scanning -----------
                    CTxDestination source;
                    if (ExtractDestination(coin.out.scriptPubKey, source)) {
                        const std::string addr = EncodeDestination(source);
                        if (consensus.mBurnAddresses.find(addr) != consensus.mBurnAddresses.end() &&
                            consensus.mBurnAddresses.at(addr) < nHeight
                        ) {
                            pcursor->Next(); // Skip
                            continue;
                        }
                    }

                    // ----------- masternode collaterals scanning ----------- 
                    if(coin.out.nValue == nCollateralAmount || 
                    coin.out.nValue == nNextWeekCollateralAmount
                    ) {
                        pcursor->Next(); // Skip
                        continue;
                    }

                    // ----------- UTXOs age related scanning -----------
                    auto nBlocksDiff = nHeight - coin.nHeight;

                    if(nBlocksDiff < 3 * nBlocksPerMonth) {                 // for less than 3 months fully account it
                        nCirculatingSupply += coin.out.nValue;
                    } else
                    if(nBlocksDiff < 6 * nBlocksPerMonth) {                 // for 3 to 6 months account it at 50%
                        nCirculatingSupply += coin.out.nValue * 50 / 100;
                    } else
                    if(nBlocksDiff < 9 * nBlocksPerMonth) {                 // for 6 to 9 months account it at 25%
                        nCirculatingSupply += coin.out.nValue * 25 / 100;
                    } else
                    if(nBlocksDiff < 12 * nBlocksPerMonth) {                // for 9 to 12 months account it at 10%
                        nCirculatingSupply += coin.out.nValue * 10 / 100;
                    }                                                       // do not account it when there is more than 1 year
                }

                pcursor->Next();
            }

            // calculate target emissions
            const auto nRewardAdjustmentInterval = consensus.nRewardAdjustmentInterval;
            const auto nTotalEmissionRate = sporkManager.GetSporkValue(SPORK_116_TOT_SPLY_TRGT_EMISSION);
            const auto nCirculatingEmissionRate = sporkManager.GetSporkValue(SPORK_117_CIRC_SPLY_TRGT_EMISSION);
            const auto nActualEmission = nSubsidy * nRewardAdjustmentInterval;
            const auto nSupplyTargetEmission = ((nMoneySupply / (365L * nBlocksPerDay)) / 1000000) * nTotalEmissionRate * nRewardAdjustmentInterval;
            const auto nCirculatingTargetEmission = ((nCirculatingSupply / (365L * nBlocksPerDay)) / 1000000) * nCirculatingEmissionRate * nRewardAdjustmentInterval;

            // calculate required delta values
            const auto delta = (nActualEmission - std::max(nSupplyTargetEmission, nCirculatingTargetEmission)) / nRewardAdjustmentInterval;

            CAmount deltaEffective;
            const auto ratio = (delta * 100) / nSubsidy;
            const auto dampedDelta = delta * ((-ratio / 10) + 10) / 100; 

            // adjust the reward for this epoch
            const auto nNewSubsidy = nSubsidy - dampedDelta;

            // save it
            std::cout << "Adjustment at height " << nHeight << ": " << nSubsidy << " => " << nNewSubsidy << std::endl; 
        }
    }

    return true;
}

bool CRewards::DisconnectBlock(CBlockIndex* pindex)
{
    auto& consensus = Params().GetConsensus();
    const auto nHeight = pindex->nHeight;
    
    if (consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_DYNAMIC_REWARDS) &&
        IsDynamicRewardsEpochHeight(nHeight)
    ) {
        auto it = mDynamicRewards.find(nHeight);
        if (it != mDynamicRewards.end()) {
            mDynamicRewards.erase(it); 
        }
    }

    return true;
}

CAmount CRewards::GetBlockValue(int nHeight)
{
    auto& consensus = Params().GetConsensus();

    CAmount nSubsidy;

    // ---- Insert reward table here ----
    if (nHeight > 1) nSubsidy = 800 * COIN;
    else
    if (nHeight > 0) nSubsidy = 600000000 * COIN;

    // ---- Insert reward table here ----

    if (masternodeSync.IsSynced() &&
        consensus.NetworkUpgradeActive(nHeight, Consensus::UPGRADE_DYNAMIC_REWARDS)
    ) {
        // if this is the block where calculations are made on ConnectBlock
        // return the reward value from the previous block
        if(IsDynamicRewardsEpochHeight(nHeight)) 
            return GetBlockValue(nHeight - 1);

        // find and return the dynamic reward
        const auto nEpochHeight = GetDynamicRewardsEpochHeight(nHeight);
        auto it = mDynamicRewards.find(nEpochHeight);
        if (it != mDynamicRewards.end()) {
            return std::min(nSubsidy, it->second);
        }
    }

    // fallback non-dynamic reward return
    return nSubsidy;
}
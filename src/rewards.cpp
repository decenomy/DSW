// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2024 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "rewards.h"
#include "masternode-sync.h"

CAmount CRewards::GetBlockValue(int nHeight)
{
    CAmount nSubsidy;

    // ---- Insert here the original rewards table ----
    nSubsidy = 800 * COIN;
    // ------------------------------------------------

    if(!IsInitialBlockDownload() && masternodeSync.IsSynced()) 
    {

    }

    return nSubsidy;
}
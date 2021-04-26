// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/scriptdb.h"
#include "wallet/db.h"
#include "base58.h"

static std::atomic<unsigned int> nWalletDBUpdateCounter;

//
// CScriptDB
//

bool CScriptDB::WriteContract(const std::string& hash, const std::string& contract)
{
	// Write contract to db
	return true;
}

void CScriptDB::IncrementUpdateCounter()
{
    nWalletDBUpdateCounter++;
}

unsigned int CScriptDB::GetUpdateCounter()
{
    return nWalletDBUpdateCounter;
}

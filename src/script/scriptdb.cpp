// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/scriptdb.h"
#include "script/script.h"
#include "dbwrapper.h"

bool CScriptDB::WriteContract(const std::vector<unsigned char>& name, CScriptContract& contract)
{
    // TODO: Maybe we should check script validity here before we write it to the database
    LogPrintf("Wrote script %s to database\n", (std::string&) name);
    uint256 hash = contract.GetConsensusScriptHash(contract, TYPE_X11KVS);
    return true; // Write(hash, contract.consensusScript);
}

bool CScriptDB::ReadContract(CScriptContract& contract)
{
    return true; // Read(contract.GetConsensusScriptHash(contract, TYPE_X11KVS), contract.consensusScript);
}

// TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if this it's needed
// bool CScriptDB::EraseContract(CScriptContract& contract)
// {
//     return Erase(contract.GetConsensusScriptHash(contract, TYPE_X11KVS));
// }

bool CScriptDB::ContractExists(CScriptContract& contract)
{
    uint256 hash = contract.GetConsensusScriptHash(contract, TYPE_X11KVS);
    return true; // Exists(hash);
}

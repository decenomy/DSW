// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/scriptdb.h"

bool CScriptDB::WriteContract(const uint256& contractHash, const CScriptContract& contract)
{
    // TODO: Maybe we should check script validity here before we write it to the database
    return true; // Write(contractHash, contract);
}

bool CScriptDB::ReadContract(const uint256& contractHash, CScriptContract& contract)
{
    return true; // Read(contractHash, contract);
}

// TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if this it's needed
// bool CScriptDB::EraseContract(const uint256& contractHash)
// {
//     return Erase(contractHash);
// }

bool CScriptDB::ContractExists(const uint256& contractHash)
{
    return true; // Exists(contractHash);
}

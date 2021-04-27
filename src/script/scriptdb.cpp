// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/scriptdb.h"
#include "fs.h"
#include "dbwrapper.h"



CScriptDB* scriptDB;

bool CScriptDB::WriteScript(const std::string& name, const uint256 hash, const CScript& contract)
{
	// TODO: Maybe we should check script validity here before we write it to the database
    LogPrintf("Wrote script %s to database\n", name);
    // return scriptDB->Write(hash, contract); // TODO: Gives error on compile (‘const class CScript’ has no member named ‘Serialize’). Should be fixed
	return true;
}

bool CScriptDB::ReadScript(const uint256 hash, const CScript& contract)
{
    // return scriptDB->Read(hash, contract); // TODO: Gives error on compile (‘const class CScript’ has no member named ‘Serialize’). Should be fixed
	return true;
}

// TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if this it's needed
bool CScriptDB::EraseScript(const uint256 hash)
{
    // return scriptDB->Erase(hash); // TODO: Gives error on compile (‘const class CScript’ has no member named ‘Serialize’). Should be fixed
	return true;
}

bool CScriptDB::ScriptExists(const uint256 hash)
{
    // return scriptDB->Exists(hash); // TODO: Gives error on compile (‘const class CScript’ has no member named ‘Serialize’). Should be fixed
	return true;
}

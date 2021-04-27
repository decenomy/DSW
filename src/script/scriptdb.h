// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SCRIPTDB_H
#define BITCOIN_SCRIPTDB_H

#include "fs.h"
#include "dbwrapper.h"
#include "spork.h"

class CScript;
class uint160;
class uint256;

/** Error statuses for the wallet database */
enum DBErrors {
    DB_LOAD_OK,
    DB_CORRUPT,
    DB_NONCRITICAL_ERROR,
    DB_TOO_NEW,
    DB_LOAD_FAIL,
    DB_NEED_REWRITE
};

/** Access to the script database */
class CScriptDB : public CDBWrapper
{
public:
	CScriptDB(size_t nCacheSize, bool fMemory, bool fWipe) : CDBWrapper(GetDataDir() / "scripts", nCacheSize, fMemory, fWipe)
	{
	}

	static bool WriteScript(const std::string& name, const uint256 hash, const CScript& contract);
	static bool ReadScript(const uint256 hash, const CScript& contract);
	static bool EraseScript(const uint256 hash);
	static bool ScriptExists(const uint256 hash);

	// TODO: Implement Serialize and Unserialize

private:
    CScriptDB(const CScriptDB&);
    void operator=(const CScriptDB&);
};

#endif // BITCOIN_SCRIPTDB_H

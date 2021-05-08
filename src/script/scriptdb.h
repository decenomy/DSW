// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SCRIPTDB_H
#define BITCOIN_SCRIPTDB_H

#include "dbwrapper.h"
#include "script/script.h"
#include "serialize.h"

class CScriptContract;
class CScript;
class CDBWrapper;

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
    CScriptContract contract;

    CScriptDB(size_t nCacheSize, bool fMemory, bool fWipe) : CDBWrapper(GetDataDir() / "scripts", nCacheSize, fMemory, fWipe) {};

    bool WriteContract(const std::vector<unsigned char>& name, CScriptContract& contract);
    bool ReadContract(CScriptContract& contract);
    // bool EraseContract(CScriptContract& contract); // TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if it's strictly needed
    bool ContractExists(CScriptContract& contract);

private:
    CScriptDB(const CScriptDB&);
    void operator=(const CScriptDB&);
};

#endif // BITCOIN_SCRIPTDB_H

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

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(contract);
    }

    void SetNull()
    {
        contract.SetNull();
    }

    bool IsNull() const
    {
        return contract.IsNull();
    }
    bool WriteContract(const uint256 contractHash, const CScriptContract contract);
    bool ReadContract(const uint256 contractHash, CScriptContract& contract);
    // bool EraseContract(CScriptContract& contract); // TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if it's strictly needed
    bool ContractExists(const uint256 contractHash, const CScriptContract& contract);

    bool UpdateContractStatus(uint256 contractHash, const bool status, CScriptContract& contract);

private:
    CScriptDB(const CScriptDB&);
    void operator=(const CScriptDB&);
};

#endif // BITCOIN_SCRIPTDB_H

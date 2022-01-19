// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_SCRIPTDB_H
#define BITCOIN_SCRIPTDB_H

#include "dbwrapper.h"
#include "script/script.h"

class CScriptContract;
class CDBWrapper;
class uint256;


/** Access to the script database */
class CScriptDB : public CDBWrapper
{
public:
    CScriptDB(size_t nCacheSize, bool fMemory, bool fWipe) : CDBWrapper(GetDataDir() / "scripts", nCacheSize, fMemory, fWipe) {};

private:
    CScriptDB(const CScriptDB&);
    void operator=(const CScriptDB&);

public:
    CScriptContract *contract;
    
    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(contract);
    }

    bool WriteContract(const uint256& contractHash, const CScriptContract& contract);
    bool ReadContract(const uint256& contractHash, CScriptContract& contract);
    // bool EraseContract(const uint256& contractHash); // TODO: Erasing Scripts from database can be dangerous so maybe it should just be marked as 'DISABLED' if it's strictly needed
    bool ContractExists(const uint256& contractHash);
};

#endif // BITCOIN_SCRIPTDB_H

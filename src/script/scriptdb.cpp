// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/scriptdb.h"
#include "base58.h"

static std::atomic<unsigned int> nWalletDBUpdateCounter;

//
// CScriptDB
//

bool CScriptDB::WriteName(const std::string& strAddress, const std::string& strName)
{
    nWalletDBUpdateCounter++;
    return Write(std::make_pair(std::string("name"), strAddress), strName);
}

bool CScriptDB::EraseName(const std::string& strAddress)
{
    // This should only be used for sending addresses, never for receiving addresses,
    // receiving addresses must always have an address book entry if they're not change return.
    nWalletDBUpdateCounter++;
    return Erase(std::make_pair(std::string("name"), strAddress));
}

bool CScriptDB::WriteMultiSig(const CScript& dest)
{
    nWalletDBUpdateCounter++;
    return Write(std::make_pair(std::string("multisig"), *(const CScriptBase*)(&dest)), '1');
}

bool CScriptDB::EraseMultiSig(const CScript& dest)
{
    nWalletDBUpdateCounter++;
    return Erase(std::make_pair(std::string("multisig"), *(const CScriptBase*)(&dest)));
}

bool CScriptDB::WriteMinVersion(int nVersion)
{
    return Write(std::string("minversion"), nVersion);
}

void CScriptDB::IncrementUpdateCounter()
{
    nWalletDBUpdateCounter++;
}

unsigned int CScriptDB::GetUpdateCounter()
{
    return nWalletDBUpdateCounter;
}

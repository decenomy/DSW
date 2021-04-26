// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/standard.h"

#include "pubkey.h"
#include "script/script.h"
#include "util.h"
#include "utilstrencodings.h"

typedef std::vector<unsigned char> valtype;

unsigned nMaxDatacarrierBytes = MAX_OP_RETURN_RELAY;

CScriptID::CScriptID(const CScript& in) : uint160(Hash160(in.begin(), in.end())) {}

const char* GetTxnOutputType(txnouttype t)
{
    switch (t)
    {
		case TX_NONSTANDARD: return "nonstandard";
		case TX_PUBKEY: return "pubkey";
		case TX_PUBKEYHASH: return "pubkeyhash";
		case TX_SCRIPTHASH: return "scripthash";
		case TX_MULTISIG: return "multisig";
		case TX_COLDSTAKE: return "coldstake";
		case TX_NULL_DATA: return "nulldata";
		case TX_ZEROCOINMINT: return "zerocoinmint";
    }
    return NULL;
}

static bool MatchPayToPubkey(const CScript& script, valtype& pubkey)
{
    if (script.size() == CPubKey::PUBLIC_KEY_SIZE + 2 && script[0] == CPubKey::PUBLIC_KEY_SIZE && script.back() == OP_CHECKSIG) {
        pubkey = valtype(script.begin() + 1, script.begin() + CPubKey::PUBLIC_KEY_SIZE + 1);
        return CPubKey::ValidSize(pubkey);
    }
    if (script.size() == CPubKey::COMPRESSED_PUBLIC_KEY_SIZE + 2 && script[0] == CPubKey::COMPRESSED_PUBLIC_KEY_SIZE && script.back() == OP_CHECKSIG) {
        pubkey = valtype(script.begin() + 1, script.begin() + CPubKey::COMPRESSED_PUBLIC_KEY_SIZE + 1);
        return CPubKey::ValidSize(pubkey);
    }
    return false;
}

static bool MatchPayToPubkeyHash(const CScript& script, valtype& pubkeyhash)
{
    if (script.size() == 25 && script[0] == OP_DUP && script[1] == OP_HASH160 && script[2] == 20 && script[23] == OP_EQUALVERIFY && script[24] == OP_CHECKSIG) {
        pubkeyhash = valtype(script.begin () + 3, script.begin() + 23);
        return true;
    }
    return false;
}

static bool MatchPayToColdStaking(const CScript& script, valtype& stakerPubKeyHash, valtype& ownerPubKeyHash)
{
    if (script.IsPayToColdStaking()) {
        stakerPubKeyHash = valtype(script.begin () + 6, script.begin() + 26);
        ownerPubKeyHash = valtype(script.begin () + 28, script.begin() + 48);
        return true;
    }
    return false;
}

/** Test for "small positive integer" script opcodes - OP_1 through OP_16. */
static constexpr bool IsSmallInteger(opcodetype opcode)
{
    return opcode >= OP_1 && opcode <= OP_16;
}

static bool MatchMultisig(const CScript& script, unsigned int& required, std::vector<valtype>& pubkeys)
{
    opcodetype opcode;
    valtype data;
    CScript::const_iterator it = script.begin();
    if (script.size() < 1 || script.back() != OP_CHECKMULTISIG) return false;

    if (!script.GetOp(it, opcode, data) || !IsSmallInteger(opcode)) return false;
    required = CScript::DecodeOP_N(opcode);
    while (script.GetOp(it, opcode, data) && CPubKey::ValidSize(data)) {
        pubkeys.emplace_back(std::move(data));
    }
    if (!IsSmallInteger(opcode)) return false;
    unsigned int keys = CScript::DecodeOP_N(opcode);
    if (pubkeys.size() != keys || keys < required) return false;
    return (it + 1 == script.end());
}

/**
 * Return public keys or hashes from scriptPubKey, for 'standard' transaction types.
 */
bool Solver(const CScript& scriptPubKey, txnouttype& typeRet, std::vector<std::vector<unsigned char> >& vSolutionsRet)
{
    vSolutionsRet.clear();

    // Shortcut for pay-to-script-hash, which are more constrained than the other types:
    // it is always OP_HASH160 20 [20 byte hash] OP_EQUAL
    if (scriptPubKey.IsPayToScriptHash())
    {
        typeRet = TX_SCRIPTHASH;
        std::vector<unsigned char> hashBytes(scriptPubKey.begin()+2, scriptPubKey.begin()+22);
        vSolutionsRet.push_back(hashBytes);
        return true;
    }

    // Zerocoin
    if (scriptPubKey.IsZerocoinMint()) {
        typeRet = TX_ZEROCOINMINT;
        if(scriptPubKey.size() > 150) return false;
        std::vector<unsigned char> hashBytes(scriptPubKey.begin()+2, scriptPubKey.end());
        vSolutionsRet.push_back(hashBytes);
        return true;
    }

    // Provably prunable, data-carrying output
    //
    // So long as script passes the IsUnspendable() test and all but the first
    // byte passes the IsPushOnly() test we don't care what exactly is in the
    // script.
    if (scriptPubKey.size() >= 1 && scriptPubKey[0] == OP_RETURN && scriptPubKey.IsPushOnly(scriptPubKey.begin()+1)) {
        typeRet = TX_NULL_DATA;
        return true;
    }

    std::vector<unsigned char> data;
    if (MatchPayToPubkey(scriptPubKey, data)) {
        typeRet = TX_PUBKEY;
        vSolutionsRet.push_back(std::move(data));
        return true;
    }

    if (MatchPayToPubkeyHash(scriptPubKey, data)) {
        typeRet = TX_PUBKEYHASH;
        vSolutionsRet.push_back(std::move(data));
        return true;
    }

    std::vector<unsigned char> data1;
    if (MatchPayToColdStaking(scriptPubKey, data, data1)) {
        typeRet = TX_COLDSTAKE;
        vSolutionsRet.push_back(std::move(data));
        vSolutionsRet.push_back(std::move(data1));
        return true;
    }

    unsigned int required;
    std::vector<std::vector<unsigned char>> keys;
    if (MatchMultisig(scriptPubKey, required, keys)) {
        typeRet = TX_MULTISIG;
        vSolutionsRet.push_back({static_cast<unsigned char>(required)}); // safe as required is in range 1..16
        vSolutionsRet.insert(vSolutionsRet.end(), keys.begin(), keys.end());
        vSolutionsRet.push_back({static_cast<unsigned char>(keys.size())}); // safe as size is in range 1..16
        return true;
    }

    vSolutionsRet.clear();
    typeRet = TX_NONSTANDARD;
    return false;
}

int ScriptSigArgsExpected(txnouttype t, const std::vector<std::vector<unsigned char> >& vSolutions)
{
    switch (t)
    {
    case TX_NONSTANDARD:
    case TX_NULL_DATA:
    case TX_ZEROCOINMINT:
        return -1;
    case TX_PUBKEY:
        return 1;
    case TX_PUBKEYHASH:
        return 2;
    case TX_COLDSTAKE:
        return 3;
    case TX_MULTISIG:
        if (vSolutions.size() < 1 || vSolutions[0].size() < 1)
            return -1;
        return vSolutions[0][0] + 1;
    case TX_SCRIPTHASH:
        return 1; // doesn't include args needed by the script
    }
    return -1;
}

bool ExtractDestination(const CScript& scriptPubKey, CTxDestination& addressRet, bool fColdStake)
{
    std::vector<valtype> vSolutions;
    txnouttype whichType;
    if (!Solver(scriptPubKey, whichType, vSolutions))
        return false;

    if (whichType == TX_PUBKEY) {
        CPubKey pubKey(vSolutions[0]);
        if (!pubKey.IsValid())
            return false;

        addressRet = pubKey.GetID();
        return true;

    } else if (whichType == TX_PUBKEYHASH) {
        addressRet = CKeyID(uint160(vSolutions[0]));
        return true;

    } else if (whichType == TX_SCRIPTHASH) {
        addressRet = CScriptID(uint160(vSolutions[0]));
        return true;
    } else if (whichType == TX_COLDSTAKE) {
        addressRet = CKeyID(uint160(vSolutions[!fColdStake]));
        return true;
    }
    // Multisig txns have more than one address...
    return false;
}

bool ExtractDestinations(const CScript& scriptPubKey, txnouttype& typeRet, std::vector<CTxDestination>& addressRet, int& nRequiredRet)
{
    addressRet.clear();
    typeRet = TX_NONSTANDARD;
    std::vector<valtype> vSolutions;
    if (!Solver(scriptPubKey, typeRet, vSolutions))
        return false;
    if (typeRet == TX_NULL_DATA){
        // This is data, not addresses
        return false;
    }

    if (typeRet == TX_MULTISIG)
    {
        nRequiredRet = vSolutions.front()[0];
        for (unsigned int i = 1; i < vSolutions.size()-1; i++)
        {
            CPubKey pubKey(vSolutions[i]);
            if (!pubKey.IsValid())
                continue;

            CTxDestination address = pubKey.GetID();
            addressRet.push_back(address);
        }

        if (addressRet.empty())
            return false;

    } else if (typeRet == TX_COLDSTAKE)
    {
        if (vSolutions.size() < 2)
            return false;
        nRequiredRet = 2;
        addressRet.push_back(CKeyID(uint160(vSolutions[0])));
        addressRet.push_back(CKeyID(uint160(vSolutions[1])));
        return true;

    } else
    {
        nRequiredRet = 1;
        CTxDestination address;
        if (!ExtractDestination(scriptPubKey, address))
           return false;
        addressRet.push_back(address);
    }

    return true;
}

namespace
{
class CScriptVisitor : public boost::static_visitor<bool>
{
private:
    CScript *script;
public:
    CScriptVisitor(CScript *scriptin) { script = scriptin; }

    bool operator()(const CNoDestination &dest) const {
        script->clear();
        return false;
    }

    bool operator()(const CKeyID &keyID) const {
        script->clear();
        *script << OP_DUP << OP_HASH160 << ToByteVector(keyID) << OP_EQUALVERIFY << OP_CHECKSIG;
        return true;
    }

    bool operator()(const CScriptID &scriptID) const {
        script->clear();
        *script << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
        return true;
    }
};
}

CScript GetScriptForDestination(const CTxDestination& dest)
{
    CScript script;

    boost::apply_visitor(CScriptVisitor(&script), dest);
    return script;
}

CScript GetScriptForRawPubKey(const CPubKey& pubKey)
{
    return CScript() << std::vector<unsigned char>(pubKey.begin(), pubKey.end()) << OP_CHECKSIG;
}

CScript GetScriptForStakeDelegation(const CKeyID& stakingKey, const CKeyID& spendingKey)
{
    CScript script;
    script << OP_DUP << OP_HASH160 << OP_ROT <<
            OP_IF << OP_CHECKCOLDSTAKEVERIFY << ToByteVector(stakingKey) <<
            OP_ELSE << ToByteVector(spendingKey) << OP_ENDIF <<
            OP_EQUALVERIFY << OP_CHECKSIG;
    return script;
}

CScript GetScriptForMultisig(int nRequired, const std::vector<CPubKey>& keys)
{
    CScript script;

    script << CScript::EncodeOP_N(nRequired);
    for (const CPubKey& key : keys)
        script << ToByteVector(key);
    script << CScript::EncodeOP_N(keys.size()) << OP_CHECKMULTISIG;
    return script;
}

/*
	Escrow
	If Alice and Bob jointly operate a business they may want to ensure that all funds are kept in 2-of-2 multisig transaction outputs that require the co-operation of both parties to spend. However, they recognise that in exceptional circumstances such as either party getting "hit by a bus" they need a backup plan to retrieve the funds. So they appoint their lawyer, Lenny, to act as a third-party.

	With a standard 2-of-3 CHECKMULTISIG at any time Lenny could conspire with either Alice or Bob to steal the funds illegitimately. Equally Lenny may prefer not to have immediate access to the funds to discourage bad actors from attempting to get the secret keys from him by force.

	However, with CHECKLOCKTIMEVERIFY the funds can be stored in scriptPubKeys of the form:

		IF
			<now + 3 months> CHECKLOCKTIMEVERIFY DROP
			<Lenny's pubkey> CHECKSIGVERIFY
			1
		ELSE
			2
		ENDIF
		<Alice's pubkey> <Bob's pubkey> 2 CHECKMULTISIG

	At any time the funds can be spent with the following scriptSig:
		0 <Alice's signature> <Bob's signature> 0
	
	After 3 months have passed Lenny and one of either Alice or Bob can spend the funds with the following scriptSig:
	    0 <Alice/Bob's signature> <Lenny's signature> 1

	https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki
*/
CScript GetScriptForEscrow(int lockUntil, const CPubKey user1PubKey, const CPubKey user2PubKey, const CPubKey escrowPubKey) // if lockUntil is less than 500M it is block height. Otherwise it's timestamp.
{
    CScript script;

    script << OP_IF;
	script << 	lockUntil << OP_CHECKLOCKTIMEVERIFY << OP_DROP;
	script << 	escrowPubKey << OP_CHECKSIGVERIFY;
	script << 	OP_1;
	script << OP_ELSE;
	script << 	OP_2;
	script << OP_ENDIF;
    script << user1PubKey << user2PubKey << OP_2 << OP_CHECKMULTISIG;

    return script;
}

/*
	Two-factor wallets
	Services like GreenAddress store bitcoins with 2-of-2 multisig scriptPubKey's such that one keypair is controlled by the user, and the other keypair is controlled by the service. To spend funds the user uses locally installed wallet software that generates one of the required signatures, and then uses a 2nd-factor authentication method to authorize the service to create the second SIGHASH_NONE signature that is locked until some time in the future and sends the user that signature for storage. If the user needs to spend their funds and the service is not available, they wait until the nLockTime expires.

	The problem is there exist numerous occasions the user will not have a valid signature for some or all of their transaction outputs. With CHECKLOCKTIMEVERIFY rather than creating refund signatures on demand scriptPubKeys of the following form are used instead:

		IF
			<service pubkey> CHECKSIGVERIFY
		ELSE
			<expiry time> CHECKLOCKTIMEVERIFY DROP
		ENDIF
		<user pubkey> CHECKSIG

	Now the user is always able to spend their funds without the co-operation of the service by waiting for the expiry time to be reached.

	https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki
*/
CScript GetScriptFor2FactorAuthentication(int lockUntil, const CPubKey servicePubKey, const CPubKey userPubKey) // if lockUntil is less than 500M it is block height. Otherwise it's timestamp.
{
    CScript script;

    script << OP_IF;
	script << 	servicePubKey << OP_CHECKSIGVERIFY;
	script << OP_ELSE;
	script << 	lockUntil << OP_CHECKLOCKTIMEVERIFY << OP_DROP;
	script << OP_ENDIF;
    script << userPubKey << OP_CHECKSIG;

    return script;
}

/*
	Trustless Payments for Publishing Data
	The PayPub protocol makes it possible to pay for information in a trustless way by first proving that an encrypted file contains the desired data, and secondly crafting scriptPubKeys used for payment such that spending them reveals the encryption keys to the data. However the existing implementation has a significant flaw: the publisher can delay the release of the keys indefinitely.

	This problem can be solved interactively with the refund transaction technique; with CHECKLOCKTIMEVERIFY the problem can be non-interactively solved using scriptPubKeys of the following form:

    IF
        HASH160 <Hash160(encryption key)> EQUALVERIFY
        <publisher pubkey> CHECKSIG
    ELSE
        <expiry time> CHECKLOCKTIMEVERIFY DROP
        <buyer pubkey> CHECKSIG
    ENDIF

	The buyer of the data is now making a secure offer with an expiry time. If the publisher fails to accept the offer before the expiry time is reached the buyer can cancel the offer by spending the output.

	https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki
*/
CScript GetScriptForTrustlessPaymentsForPublishingData(int lockUntil, const CPubKey publisherPubKey, const CPubKey buyerPubKey, const std::vector<unsigned char> encryptionKey) // if lockUntil is less than 500M it is block height. Otherwise it's timestamp.
{
    CScript script;

    script << OP_IF;
	script << 	OP_HASH160 << ToByteVector(Hash160(encryptionKey)) << OP_EQUALVERIFY; // TODO: ToByteVector(Hash160(encryptionKey)) need to be checked
	script << 	publisherPubKey << OP_CHECKSIG;
	script << OP_ELSE;
	script << 	lockUntil << OP_CHECKLOCKTIMEVERIFY << OP_DROP;
	script << 	buyerPubKey << OP_CHECKSIG;
	script << OP_ENDIF;

    return script;
}

/*
	Freezing Funds
	In addition to using cold storage, hardware wallets, and P2SH multisig outputs to control funds, now funds can be frozen in UTXOs directly on the blockchain. With the following scriptPubKey, nobody will be able to spend the encumbered output until the provided expiry time. This ability to freeze funds reliably may be useful in scenarios where reducing duress or confiscation risk is desired.

		<expiry time> CHECKLOCKTIMEVERIFY DROP DUP HASH160 <pubKeyHash> EQUALVERIFY CHECKSIG

	https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki
*/
CScript GetScriptForFreezingFunds(int lockUntil, const CPubKey pubKey) // if lockUntil is less than 500M it is block height. Otherwise it's timestamp.
{
    CScript script;

    script << lockUntil << OP_CHECKLOCKTIMEVERIFY << OP_DROP;
	script << OP_DUP << OP_HASH160 << ToByteVector(pubKey.GetID()) << OP_EQUALVERIFY << OP_CHECKSIG; // TODO: ToByteVector(pubKey.GetID()) need to be checked

    return script;
}

bool IsValidDestination(const CTxDestination& dest) {
    return dest.which() != 0;
}

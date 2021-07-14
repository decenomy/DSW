// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

#define DISABLED 0x7FFFFFFE;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "U.S. News & World Report Dec 20 2019 With His Absence, Trump signs $1.4 trillion bill to avoid government shutdown, raise minimum age for tobacco";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256S("00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"))
    (7413, uint256S("8ee36dd195197ed0e842104d4a1691ff2c587537b7d83259589c7a0d53e01e3b"))
    (14827, uint256S("225e2b978d86516b047a4700fb068927b3fe9758db425d49b92486943f526959"))
    (22241, uint256S("8f4bba8f4e39358abb8f309d0369e0d38819f508fc8582b360f41c94b819a860"))
    (29655, uint256S("c43e5ff111cd810544cbf9170d4fc5bc04ed41f1ac54945317170c3181245029"))
    (37069, uint256S("1b1bf969c73522e22089f0915fc8ed1cab8d10a315f302428c6309d1889856bb"))
    (44483, uint256S("d86f2999112b318774a3d513ce332efa6c8c9d7ded45fa5b6c0d1bd133eac512"))
    (51897, uint256S("4d78d855507d72f857884c1e16f4ef583d6534d7299d663504cafc4ce06220b5"))
    (59311, uint256S("b062a3fb86ebabc47314dd0a76de482b0ef6950b24a91d6c1b5d8acea7f931fe"))
    (66725, uint256S("d51466e749d17b39fcd0be144227048748f8c3664797e09e5f08538d21a8a535"))
    (74139, uint256S("242aa0f7e858bb0cdb64d739d6f5469297a75051d9c02903e543a95707276751"))
    (81553, uint256S("aac90fb604b590196bca069c73cb1cea45f00fc72aa2ad5172823b954ea865c4"))
    (88967, uint256S("0a7707c7a2d591ca07a3ef5048bbf82875165f09eab83f14bdb66ea587894694"))
    (96381, uint256S("24102b8bb60846fc9300721a324a8d64273aafb82590ea1901d41cd252305d7c"))
    (103795, uint256S("20e26c406471271e7e4d69740972ee3bc0cb0eeded8f3fe7e204cd12d3c946ae"))
    (111209, uint256S("f6fe595efb6902f95f011103505ac6960a01b78e77d1991250e8a722c020b468"))
    (118623, uint256S("7f07bf0922062f30fc4db490b91ea26afc300a1058aaa6f8ef89fb8cd00ff606"))
    (126037, uint256S("5079b670c9c152d45f53bb304fbe08e10ec1acc238906574f01dc668448ace1b"))
    (133451, uint256S("94ef8576db964b701ebdb4e1f88a7f4d21f7689e553e6951bf77c44c33aef4e4"))
    (140865, uint256S("de75bd21a0e5d1e56416f4c689a89656418d8eb84d67c8626a8454f3fb4c016a"))
    (148279, uint256S("0fc00cca14c173fe345685fb14cf927f1b70b68255ba5fc7027cccb5f41ccbed"))
    (155693, uint256S("e4c74a2c8eb29e00b0a88cec9cc09755e593fc14bf270a0d3793fadb3766ba6e"))
    (163107, uint256S("848f8c62f30aea89056486b43b2ff20946912de05474ebb9d8ac37e89a85ffe3"))
    (170521, uint256S("24b91e41c37242b19da53f41c448693fbd1263cd55ed6a0eb21a0336db7baf66"))
    (177935, uint256S("52fb7dcac020a4cce6bf8437d2559b987743c759e8a094eb0b2ce6c7c40e398e"))
    (185349, uint256S("ed05a9cf4bf08e87aeae30b39153adebd3e2c0d5a0603110bf348193132fc82a"))
    (192763, uint256S("d9cdb78ef9ca85ce7c055f6c2f56c8630cf9bc2d187c819a5c3243b738462888"))
    (200177, uint256S("68d5351851e89b938a128539d6db9c82d77a3ecd84f7fd43c44b4d7422c37c49"))
    (207591, uint256S("fd5604f51cca4091e6e3d7255f7b527699bf0de6074a1c6acfadd9ee143d2166"))
    (215005, uint256S("247288064c7cdc0916f95045e6e5e0400da13477ade21434bad3ba9af71bca64"))
    (222419, uint256S("1cd69a6db4ba5633a7c723d9c4f0653bf7bee0828be4c84250299e79cacda99d"))
    (229833, uint256S("d1f574f8ed4996007d8c305767b6efacc730532bd9b3c546eaa44ced7d95ae2b"))
    (237247, uint256S("968f2e14ca2b72543930cb2d39ba658b722426c606ce30ae8ce840783a13964f"))
    (244661, uint256S("4e728e5d186caa03be035382ddc3fb76908a57371cbfd66e89c4fcd81ecf35e7"))
    (252075, uint256S("b7baca45fecda5fc26b144fa8b07e0013b83a87ccafaa232a21a6e842e5f3f5a"))
    (259489, uint256S("1ba947214b772e5cab49b3671aebef822ca0d80f058aafa6a06e408aa61c2400"))
    (266903, uint256S("5bd5e2cd4405b475bfa450c7064824e430bd68266373608310039d34353fd0d7"))
    (274317, uint256S("875110ae3ced9040c97beb37c5377db21607cfe1a4e2b68f1dc0553f740452dc"))
    (281731, uint256S("ee38af13cb1f583f62f8d5068850aeab5e933874392b46087f13b29d9bfdbf6c"))
    (289145, uint256S("268b6ff07180ce14477b08825f86e71344ac102fefa3d0cfe2a098aab206c170"))
    (296559, uint256S("e06dec8eb24b07f75ff5933661c33b60d0bf0c23dbb40d65a3572e20f2165264"))
    (303973, uint256S("a5ac2e13edec0bd3f4eae11bd690e3fce461eb783d1e855f2a32d97badcfb22f"))
    (311387, uint256S("b5b92cee611be2739c4ef560e49f7a8ed4f22b43d153b1430d96ad78ea546e31"))
    (318801, uint256S("5175b376f11a407abdb4900df0b92285c16b92520e490e1ac85353daa4b802a2"))
    (326215, uint256S("a83e151fc1341d18173cc2e762faa494adfd352f54313572a539c4fd2f4387b8"))
    (333629, uint256S("d67be0f68de5be51de2d90a5bb332fd92c4111c195eda24149789b4ef3c07a8c"))
    (341043, uint256S("0b95affbeaac8cde4fdc32de363451ffe81c8865f3dd56a2a8faa24037b773a6"))
    (348457, uint256S("8741f7b82bf9ffc95c329e18992f1013007e401563467a8dc510e244dd27c68e"))
    (355871, uint256S("6a4b34ba78568d306fa18c512fcf4d33f63ddef22b3ad3071584c19846ae3282"))
    (363285, uint256S("81e83e1010275fd9d742c4962e34dccbcf17a55002fcf89fede35c4f5adaa7f3"))
    (370699, uint256S("57a6ae55c50692083970a0e264a5a307e24682539e9f311c3073cbc4e91f327b"))
    (378113, uint256S("f283ef41554fc3e4d2e0555311db3844d73f240d66f837b7fa920416a1a14201"))
    (385527, uint256S("b5b63f7ef469a6818dda3ca94ba02530aa2a095a9b94af93f580a933d2cc11a2"))
    (392941, uint256S("0ebfea756041858c03fbb6f374be54d04f54344be17eab3053b90d2c4f31cef3"))
    (400355, uint256S("cfc59955af2b3ad3bfa2ef97eee7b19448ec19b47ee72eb389b95e6e2b03fe07"))
    (407769, uint256S("a136f3fecb6fa01e990a16f2c5cad5379b55ffe556f220676af894b87f096b44"))
    (415183, uint256S("663606f3d5e294a41855ac98afa57c7098fb7614623710d34f80a4647cad47bb"))
    (422597, uint256S("612e54f4936e0d703838c69706a590e103bc4adf0ffbdfa2b2c48c3fe01a2eb5"))
    (430011, uint256S("0824a7717d73036abfed1fd66723ec26b6a95a07071131f5361ab012fcab9642"))
    (437425, uint256S("fe1a90deb140da622b8c3ba42a053d8fa5ba83a9189e29c97602d7cd229b8966"))
    (444839, uint256S("5f7e4f4009460af6c1d28b1349de0f286aee260b22ae15a68a1fb1cda4042202"))
    (452253, uint256S("b7f7ebe7c0f487695fe280ca69aa87a9f274a3c17f8162b65107f47cc5ec7651"))
    (459667, uint256S("82060f154bd46bd523a55aeec9b8a006d6600df81751507d782131a0d07de409"))
    (467081, uint256S("a5f42a916324e77e5a71f0493f2aad80fe3172ef323bf4cd35dc5c6bd37ac999"))
    (474495, uint256S("0b71ad6b4303d3645f37a6de38644e439b4c4a3c73d1906c1f8fd8b938568116"))
    (481909, uint256S("4031e3ce4d9d525c903d39ef020b4309479d6a4d25fc4f8cb65eed7f06460f4c"))
    (489323, uint256S("dd889df1592b3dc3ad473208b0cd02e8777c62223c09af6d3abf4b83f71eab8d"))
    (496737, uint256S("638af3364c5c1feb0bb1344fbfc34071dae5e8540a9056bd3b876be67bd48cff"))
    (504151, uint256S("dfb77662334b57619a4eb6766f114bbadfa5782a832e5583409d44c049bba1bf"))
    (511565, uint256S("3299393f159a5f473d94f11f89d3ba2721184574c81eb72b7e038fd04d585cea"))
    (518979, uint256S("fa708b00befcabf77789955f229d576f0402b27aa282feb8a885b654c4a44e50"))
    (526393, uint256S("4ff7fc7cb364640c45863abc35ce01f10eab9c4020a177fcc27243de434011e3"))
    (533807, uint256S("f5198683d14c7599a6ddb3284c37c1e84c1da0f508904820edae316d765b1fe3"))
    (541221, uint256S("5ff5911e26a429008859fa948a1c949c164914b3720eb22222b160366249d58f"))
    (548635, uint256S("deeb2fc8b7a9a0192ad1a7e572fa1044daf9d00b18ec53b97e34924c2496ee85"))
    (556049, uint256S("51c6200110dd851bf93b16d928a6b9bb8e45121c3b6df6428f3eb4d94d51157f"))
    (563463, uint256S("8607427d30668329ebe97cd59b35a28cd31dcea24e252ddfa15a5eaa8455cb41"))
    (570877, uint256S("e17cf3775070feda9405d96f7bb4ee9c23b8c7095eabfaec663bc9863313ac8c"))
    (578291, uint256S("ad37e089285eb4d7fb3ea0e43d2f3a62cf6a569b075aff58059ff7a66dfb16aa"))
    (585705, uint256S("c7d3b3462df10f2a87d4216ef1fc69ed64c32103d8af53e4d7a23ce116a8b713"))
    (593119, uint256S("5af146a7b3c9efc279ee0b0baa600af225cb40130fe26ee75db353a7199fb60a"))
    (600533, uint256S("538d3e646ad4bb4f0ea1b4a73551d161b2bb5838ffd5e7801c567dbe2dc7a3bb"))
    (607947, uint256S("76c96776e37e0528ce177b15aeb991979d40af4b1076f28123a801ec437650d8"))
    (615361, uint256S("577a04b8ecb81bee45d86ca68ac5d6e2ca6ebcf2799fb91e9c054456c485afe7"))
    (622775, uint256S("169d98a8a9f862fb36818ef0e623e4fe20af378b6dba67a7eeb9c6b3e613c961"))
    (630189, uint256S("4077553dbb2f80eefc4f4ee99d9bb57d9c4b9db98e8c0f72ed3854a95fec5e52"))
    (637603, uint256S("47d6459a3e323296207a554a9b657a3a162e7561ed36277914df4c6a7e978f2d"))
    (645017, uint256S("3b9b945d2c2d2509a6e8e259a4d398d27efdbfde251eb707d36e43f46d9cfc43"))
    (652431, uint256S("4669fb8d39b9cfe4a3d76658e7557fc5694792e018d354c9f9d9e05b7302817b"))
    (659845, uint256S("04397aecf8273ebf33fbdf829bf891d4671ca1df60a7b605c364db3e8d3f943c"))
    (667259, uint256S("a449dbc14e9c2e9c40ca041c75231388f1fa72cb99dd0c568e515945b63f772d"))
    (674673, uint256S("5db4e6483a9a2ec33dc234a267f7d33eff33dd0019d2035d5b1b015dcd77c4c0"))
    (682087, uint256S("377180f7437e4f840f9343d31dd87430b3fcaa4cc4c4abeb29009dfaefb19511"))
    (689501, uint256S("10fb6a01304ad70e9ba828275a81949ee95990e56b2414f89d45297b15e4e764"))
    (696915, uint256S("e75bd16826cbcb59dfe643ceb2faf5f7b485a08224a680a449f12d4284d4b513"))
    (704329, uint256S("0b640e85e3eb3a63e4421799a6d8cfd0bfa384fd856f93aca186c6d86143193e"))
    (711743, uint256S("8c5cf81efd576a16aa703609916caa4bf91bbd903f62e2d38d01086c044351a5"))
    (719157, uint256S("500524fe21e1a02ea934f93bace945b1d4b55370b41e5364a4ef312343210bb0"))
    (726571, uint256S("603a32f0a30899f44161937ff71d8f63b89930fad68c462ebbf246eb13703130"))
    (733985, uint256S("813cd62e63d38855972dc24b6ed98ca57d4edceb2b350792ec780023d1ace904"))
    (741399, uint256S("b73c90b90cfc9e18944919af274a337ff642be42fd9d0cdbf8b58c9b043fc230"))
    (741421, uint256S("80d473a15ccb8a1527347053e015707385ecaa93b9102d3fdf2321cc12c4599b"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1623960315, // * UNIX timestamp of last checkpoint block
    1940370,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1618037081,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1618038166,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1612360301; // 2021-02-03T13:51:41+00:00

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e0ffff0, 1, 0 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1576918337, 2012178, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // Around 84604500 coins will be produced until block 750k. Another ~915.4M coin for around 17.4 more years until year ~2040. Limit can be increased afterwards if needed. 
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 160;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "023a979aefef58890e1cae7934c5bed09a8dc8f70da29d884d84bf083eaac6d566";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint    = DISABLED;
        consensus.height_last_ZC_WrappedSerials     = DISABLED;
        consensus.height_start_InvalidUTXOsCheck    = DISABLED;
        consensus.height_start_ZC_InvalidSerials    = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck  = DISABLED;
        consensus.height_ZC_RecalcAccumulators      = DISABLED;
        
        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 2081097200;        // October 17, 2017 4:30:00 AM
        consensus.ZC_WrappedSerialsSupply = 0 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 320;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 330;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 320;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 350;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock              = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x12;
        pchMessageStart[3] = 0x19;
        nDefaultPort = __PORT_MAINNET__;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.aezora.com"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.aezora.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.aezora.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.aezora.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.aezora.com"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.aezora.com"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.aezora.com"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.aezora.com"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.aezora.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 24);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 198);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x43).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1618037081; // 

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e0ffff0, 1, 50 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1618037081, 3673827, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bc103d39f3620750bbf80d5cfdcffeeab5d97cbdac6b9f8ba3da04d8718"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // aezora starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // Around 84604500 coins will be produced until block 750k. Another ~915.4M coin for around 17.4 more years until year ~2040. Limit can be increased afterwards if needed. 
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 200;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint    = 1106090;
        consensus.height_last_ZC_WrappedSerials     = -1;
        consensus.height_start_InvalidUTXOsCheck    = 999999999;
        consensus.height_start_ZC_InvalidSerials    = 999999999;
        consensus.height_start_ZC_SerialRangeCheck  = 1;
        consensus.height_ZC_RecalcAccumulators      = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 301;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 401;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x57;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x33;
        pchMessageStart[3] = 0xff;
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet1", "testnet1.4444.tools"));
        vSeeds.push_back(CDNSSeedData("testnet2", "testnet2.4444.tools"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet aezora addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet aezora script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet aezora BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet aezora BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet aezora BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1618038166; // 

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 50 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1618038166, 302, 0x1fffffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x006656221e2e3eed8679ea44b0ad48121ceb26b38408aec372ac8bca1fa6f8cf"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 2;   // aezora starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 5;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // Around 84604500 coins will be produced until block 750k. Another ~915.4M coin for around 17.4 more years until year ~2040. Limit can be increased afterwards if needed.
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0;                 // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x57;
        nDefaultPort = __PORT_REGTEST__;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}

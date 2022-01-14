// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
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
    const char* pszTimestamp = "Another 50% daily gain for Dogecoin confirms 'alt season' as Bitcoin slumps, 05/05/2021, COINTELEGRAPH";
    const CScript genesisOutputScript = CScript() << ParseHex("0478505c5bc438e08c0c8de26a661bc5a4453378d0b149fbf17cb3e1499b1d3e552fe5faaa253673c5349b461bd964a2ee860c114e9d2b9fdb0328f37ed356ed54") << OP_CHECKSIG;
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
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (3545, uint256S("aecf2fd4dbc0daf045a3a4aeef801ce91079310a09259406ba2c6a2a1d9d1a5b"))
    (7091, uint256S("670f3d6821d9ca097899fc8b6eaecbca05e41a0ac66f243935d15a2a2fa69642"))
    (10637, uint256S("ad68b2b55a05422568655472cf959e883ecb5a0204367770a80cf6ead4f96a33"))
    (14183, uint256S("2a9b1fd7ce3715c4b6f0983ae2e522fde6d591f42c4c9db3668e0e9186a16f90"))
    (17729, uint256S("a8b4e61e42773b0cab50e12684b3c734a9db64959170167a6bcdda4db591e049"))
    (21275, uint256S("457bcfdc8fe0e61d58e2b698b8eb9bb6e79d965c54063bc561a836981e681e66"))
    (24821, uint256S("b4d0cfe25f492112c7d02b2c4ef423675d0de5396f9d3942a838a2cca904c116"))
    (28367, uint256S("b0da06de3382b9b171a0e671408a6f5da4e690b3519f071c847578cc661d8359"))
    (31913, uint256S("4e23c45ede724344285418343b16c37f8c868f701b312e92d3cc60206121677d"))
    (35459, uint256S("ba7f67dce7c92e2e60ee838ff9921754029222f220f1c61f021bf8457924f2e4"))
    (39005, uint256S("be4f22b5a8ad006061fe0d661c186700c56402de7c7ca304918a554fed82b1f1"))
    (42551, uint256S("d81d78b244dcd74e391c4f0ac6a1814b5aa3bc631b3cacf2d6f473e45fac831c"))
    (46097, uint256S("09f2b3ada8a9a39279d5d6885d34777252de1bccd01f9cab5a11a1d4e43c5692"))
    (49643, uint256S("21c925cf9d39afb9dc1a96c7d3591f1aecf26645166ef9114f71eb288696685d"))
    (53189, uint256S("91493c3a78c4b3bf2c4f7e2be906382972cda7dc95ff4c09f3290ac817e5260f"))
    (56735, uint256S("8584412991c362cf3b6563b65a5b198c83d2902ee52e391f55a8c887d5d8dc28"))
    (60281, uint256S("dd8863215b15b55b4661785395f6d32c509364bf230e7dd5974377c7b124c97d"))
    (63827, uint256S("784a5190fc1f1e9e5443589b40339983915819595c42e3aa727d37879f1c2612"))
    (67373, uint256S("e376035510f2bdde331d542eaf29b1c468995208ebaed039601a0e608c54bdc2"))
    (70919, uint256S("69e9231a3e40d2c7555648b090dd2514e04b9ec601f157c5369fda3c231210f8"))
    (74465, uint256S("b61bd1bcad2d231a2efb2b6219bd62e3510e27a561d98ccd4459675e009782c9"))
    (78011, uint256S("d88e89215e1af6ac61dddd90eec38f4cc586c144e5fd0ae13f800b8019e5d64a"))
    (81557, uint256S("e8dd7692206b1dc4e761d3d90bd8edd4c302d3619a88621e181811a331ebc37a"))
    (85103, uint256S("f3d93fa00d12515868acef41e6deb2d6a1711b1104e8bf4b71aabd4d8304f9dc"))
    (88649, uint256S("e2674533eba44204df3c672f32cf3a374c61df79ba6bd7ed24bbe843909fa22a"))
    (92195, uint256S("8db5be6f11b16de8a52ba4e5320001c8c33ec0175c4ccf0f12a6f775476a76f5"))
    (95741, uint256S("040df1373d0ccfe52d120afc321e03d646c23774f7240a094a6e2328e91d496c"))
    (99287, uint256S("ffc3230e21199b457c005bea3af7a34e9c20ccc0381efa4f581c71b6f8f9d590"))
    (102833, uint256S("d3f11e305f710ac714eb035f8165fd77f635e71ac32229d882a7a8d942e06744"))
    (106379, uint256S("a1b1320aa40b725d3abeefcee6724c4547c2f4e385bc8195c14468ab9aae7bea"))
    (109925, uint256S("86711369955bebe3ecbe4719d1399520efa1b2eeb19e3ebd1d2830dc600faea6"))
    (113471, uint256S("a875c3a749807a2cd9293b37849fb96d97975de3bd043c4305f1dee657b921bb"))
    (117017, uint256S("4fd8cbf28cc88f57a4d98214710468951b63cbc97afaf2f45f1fe5abe761c654"))
    (120563, uint256S("82b8d3dd9fb3f072df61a0b77051761029f8ae5fe9febfb58cf7513f2b16fa57"))
    (124109, uint256S("83712dc7aabacd68dec8de530a3bf4e0c7eab2f9660d7293600240348c186863"))
    (127655, uint256S("aded840c40366fb6a329a0f4932c499f56d18b9023e1af764e9b17b4789d8c48"))
    (131201, uint256S("03972fd1dfb5291bad32e67f8ba5ca585da00b70c09b56edcadb890f08e35c73"))
    (134747, uint256S("874a39b0d3529d4fcb5fc6467bb6b31a1f5dcc2e19cd63df08189d9156c18c5b"))
    (138293, uint256S("a6ec29181df20eddebe2bf2af623b557dc4225baf2b6476a041dafdf9c5e8f62"))
    (141839, uint256S("4a4354081125803c51b47a7ec1cb04a95cdf46dbbb601171b28569eb1c4a1a79"))
    (145385, uint256S("5de2b1f91358f39b522499ef5ca2f85cee9aaa540c750ae2b9b3c47a5cb12f47"))
    (148931, uint256S("0b1b69f7be582e838d0333816a013bad37a34170bb4920caed332a535b4440c1"))
    (152477, uint256S("ba2a9ad836cc6d60a535ded7f386eea60707dd33cb24e68fdfdff8edcd92a473"))
    (156023, uint256S("e919c1e6d3bab59cf2a4f162a001bbbd247e0d31c95831b8b39610b0674886c3"))
    (159569, uint256S("5cd896a15be3bb9d8ee2949d0f78d35b6623463f56b5096d5b1699401e9b76ee"))
    (163115, uint256S("c2948b380ff5456a26449dff4f93700d6f3303932fe794dc128f0d7aaa44f3b1"))
    (166661, uint256S("4008afac216df459e3a163510d87d6b912eb66b703166f3668122f8f4c90b5de"))
    (170207, uint256S("bc982a817f02699dc6d949f89ccd156ac9e7ab2081684239209e25ccbc421dc5"))
    (173753, uint256S("4f2823ab3bb27d106fad85fa304c3b0b6d64e33e3bf91bd4a4e3cfb8a23ad46d"))
    (177299, uint256S("256ab5e9ba10c73cd48ea07d05745677bb2cbe6abe0a5da3201b40f017c02b22"))
    (180845, uint256S("8d6e345c4a32a3bc474a1e4a25725047f89e61d4d46f1faae34146a9e4690a57"))
    (184391, uint256S("307003c41dfad411e21c11cf32ddfa4add3c69cbd5582dafd8709bd4b8e63635"))
    (187937, uint256S("566caed7a84c8c02aabce4e1a9629a1dd75cc7eb11f6222a31820c2d04e1d125"))
    (191483, uint256S("3965a01506adcfcad3c8e94a545cc4c5fc3a4a2328882be477feb72ed9945b79"))
    (195029, uint256S("05d2cf3ce3b4fdcfe7b6668da2bb93d212c2813ad811ccb93b0b5b61c18dbac8"))
    (198575, uint256S("871bf351accabf2d227defb1c10b689940ff4f6a0c1f7f8215f4a29bc1290440"))
    (202121, uint256S("2854051257f997cd0c96c5f3da18f6d2b6925d6c0689c9b056c182164bd8bee5"))
    (205667, uint256S("05b15e5de410d20997c661e47cd518eb9957b77a1bac998c1f97857d71f52b15"))
    (209213, uint256S("d82597b71cfcf65abebab5eac93b17532fd1558c89780cb2a435f7c291877343"))
    (212759, uint256S("32c400618f6ef8e4812848bef6663b884838b6ca6147d4d16db19a6eab764978"))
    (216305, uint256S("e870ec70481c07eac52b5d59df04204fc14c1ddd4df6bdb36dca21b78ef9e288"))
    (219851, uint256S("c91b35c2d8932682c4e60064ab05cda57c7d7ccea25f2c1c604d9533a7e13433"))
    (223397, uint256S("7abf417c23dcae3ea12746421a7fb20565a07e6fc792c35af2b4eef473c98196"))
    (226943, uint256S("da62331a30e32c6c07994a8b36eae3042b2ff82f1804fa0c44077a8b5476b2cc"))
    (230489, uint256S("8b3d0237cb0f69456c62114913bd78f7f251c32683f0faadd9b07e6842197ef3"))
    (234035, uint256S("90975e96495d9653b55d1ffcc26498cee197adfe59f8e14ac3a00a3eb69142c9"))
    (237581, uint256S("0dca52cca972f2a1749c2f1707e15f00223e06d688413f4fd28256f4d84cb7d2"))
    (241127, uint256S("10d669eec10e16ee013bb9c8ec2ffe51926f38b28daa98f9a04d2a0c95317dd1"))
    (244673, uint256S("4525791fd027d9fbd8edd9b82d90e09ae621308628715ec3696d893eefa6e6b8"))
    (248219, uint256S("06c10017e851177ecce3c85408e11947d7770447687dc48c1ea16882b643ba69"))
    (251765, uint256S("c3e7255bd2ca103d55f93f643a6f23df7c47b3faf32685d27c7ac551327b388a"))
    (255311, uint256S("add4d9b4e8a65179a5a658e503596d50ce59066bce47ed5a9ec2648407aeb4a6"))
    (258857, uint256S("1ee90e8fa3abfe9e288741d7c4f547c20b919aca44606ae46628c0a81732a25a"))
    (262403, uint256S("f9f62cc0e01979cc9ccb9a18a98d9f7c684f9c82f8a77af66338f4a9528a396e"))
    (265949, uint256S("91dedb484fb73e6c9785a943bce5ff1af2b4412f94370fd71cc18d0fd4b60a9f"))
    (269495, uint256S("e072fba8eb659533d4cc7918c5ae5ca23d33c963e818eee47a1b4e46fa34537c"))
    (273041, uint256S("4eab747e99db5a5af757c3de3d3c7d1f6efbbc7a5c5d4e96c5e5590cbd0b6c68"))
    (276587, uint256S("455240c804f0a44504c8a410526f1fadef9dddfdcdfe16be5052439a489a0fc7"))
    (280133, uint256S("13ef37fdec800fec7f5c47db29a9e926391033a10de90ceb38b6cff7fe6e762e"))
    (283679, uint256S("6fc944f81d7774b8f6e20b1d5d1be7e0ccebce961d727e9c6f2159140f395e4d"))
    (287225, uint256S("fa85ac39f2a4dacb3a0cfd1d7a34850f4b4dcb35371b3041b92a3ab8fe23df92"))
    (290771, uint256S("fcf43f2104458dece7b8341b4ddd971aafdef75d44442af0ecca1cd23971ba93"))
    (294317, uint256S("483b1c794f99a806bf870b7814310745a7392a88c59eb36b325b3fc8ee4800b6"))
    (297863, uint256S("2942bbd498bd161e1b3d0f957cebb284cdaed9d84a3278225e822081ef198f13"))
    (301409, uint256S("e6164e405ab9d0bcbefc45c8a305309b6d2faf1e512fc77e835f6543da37d000"))
    (304955, uint256S("4280fb65d5abb130586f3be534d5f9f0c7016b45cb3d9650dbd2153daa8de06d"))
    (308501, uint256S("04142976d0e9735e39c99fdf62aad9d0a243a7f01ae49d8b8fc4393828b997b3"))
    (312047, uint256S("6d5120a0df0549f3ca7312473d624e81bea24964409419b0af29975dcb3caf48"))
    (315593, uint256S("96aa157dafdc76bffb3d1fb5d6bd11761ea576ac72fb77eb18049e06bb4c68ec"))
    (319139, uint256S("431f9f7b7619a5dfa7b2fb0cbd783f97968a7ce8c9ae601c5aa41a1350a543b6"))
    (322685, uint256S("7fc8ad4d7b9e4fa53d43c2917bec9dafaeaf80758fb03e36d3bc36f2f934cebf"))
    (326231, uint256S("be23dd2b7b38bfe12d09d4b7a2d1d79504294c2577437c3b6f8641eb09dddd59"))
    (329777, uint256S("f3be04d2f5384608c280744d52e04e840d679a92fad9cf212dbe3ef16d8c3eb2"))
    (333323, uint256S("fe7b6008be17eb74a17742fe8173522d2b2a2e0833e6df14655e48e846931722"))
    (336869, uint256S("5e45935d8aa6e90ff73e32865fc32b769bf69a90d03a5c7accec164f0cbd12e8"))
    (340415, uint256S("e793ee9bd51d3fefc08cd2dff1e22db479151df7002032d4faa13d2d27e8bb09"))
    (343961, uint256S("dd626f708ab3673d0f36c8d81d910a69dc1cc68293ccbcbf36233ffb718a1a46"))
    (347507, uint256S("db53d68bc6e99d1067a79fd7730cc307fdef88fcd1324bd7e5d6dd2b79d14676"))
    (351053, uint256S("9b1b8b911db25e4997cbfd53a487725d7b66df619ea75afda1a47214170045a0")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1641820845, // * UNIX timestamp of last checkpoint block
    751615,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2836        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
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

        // uint32_t nGenesisTime = 1620224091; // Wed May 05 2021 14:14:51 GMT+0000
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

        genesis = CreateGenesisBlock(1620224091, 1077816, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"));
        assert(genesis.hashMerkleRoot == uint256S("0x5322195c37996cc752786ab95a76b328f2f8e03d3a9b5ffb465173613d4f97ab"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "0273914d51723890516e319ecf24d71749da673c76606941290a0db4842389d693";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "bXXXXXXXXXXXXXXXXXXXXXXXXXXXZEYRfd", 0 }
        };

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
        consensus.ZC_TimeStart = 1893456000;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 115000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("f4f586f27b0af2d9307015d45b7ff3ba72821ce54bf45110c0e034bda22a98cf");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c33e160f767be68f93c57e2c5af5d77e7d1c83bb82a345f6f2d4ea968a3f5d95");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("70ce131e9bc06cca48bcf8bd0f0f8efff93fe6e34ce9caaaad984c66616f7245");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("b13b0ac7e05c537438198d3e181c2e9796d0fbe9139e2ab3f33352fadd25dd35");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3e2e44e642974c48c9c2e1b6efd5fbb88b253decc6878a9ee64e7242abd5ed5c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("9ce29639f18a952d53bb4aaa2600279c1aef9bce52089b1c970da24be993ae3a");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 36552;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x49).convert_to_container<std::vector<unsigned char> >();

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

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
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
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint    = 999999999;
        consensus.height_last_ZC_WrappedSerials     = 999999999;
        consensus.height_start_InvalidUTXOsCheck    = 999999999;
        consensus.height_start_ZC_InvalidSerials    = 999999999;
        consensus.height_start_ZC_SerialRangeCheck  = 999999999;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet beacon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet beacon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet beacon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP44 coin type is '1' (All coin's testnet default)
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

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight       = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
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
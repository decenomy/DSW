// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

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
    const char* pszTimestamp = "Soverain's blockchain #init";
    const CScript genesisOutputScript = CScript() << ParseHex("04dbc25a9a48add73d7f65d1ff4ae6a1fc80d2089fcdc78dc8e5088c6d27df962f393a07cad6fc632f6b891f5c81f970bf282679c39e581f856d6a94c9f814cc68") << OP_CHECKSIG;
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
    (0, uint256S("000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"))
    (33493, uint256S("2ccb113a359ce6a93b81cb6fd257be3eb61ec64f650013748e3edab2a6b5665d"))
    (66987, uint256S("a911a84db76f0ffc2ab61c471eedc565d6f3273d48618ad85b509a4dcb284098"))
    (100481, uint256S("d1deaf8864d5b233b1596a044ce78b335ea88f28f25aa15a09c29e1cd3aad1cc"))
    (133975, uint256S("ba7cce7bbd9da0f4f6749beb258ef66adfbaec3c0dcebf6e711cd88b066dc0ff"))
    (167469, uint256S("44d4e323510b246c307cc79dac43c5341d7f9600fdb1ee8b68ea2f6cd6d1d7c8"))
    (200963, uint256S("8354628ea76be135b5d18a4722de2aa70b1959a9b1b57f7309aabdce316a5682"))
    (234457, uint256S("3a94bdaa95b74c584b1ecdaa1c06146dc8ee3b35d2cbf7ecc600016cd761372e"))
    (267951, uint256S("020b4810756828c242b49819c866e6955a60446a3d1910530f0cc147fb00a3eb"))
    (301445, uint256S("4275c691f8300bd93f7a1c7385d436afe5f70829a3ca212a9674fe3eb0a29c59"))
    (334939, uint256S("65b18c8c4b1951847c157ed2c3d6cb9c034c60f60fc7ba30098168005dc4f673"))
    (368433, uint256S("cb24b6f154cb33455f0586387636b3ef601695491bc16d6954fcce5ce22068ff"))
    (401927, uint256S("cede9be7dff94c35f48060e8e687a95a6052bfd781550c81c5ebb12c547f3073"))
    (435421, uint256S("3203c315ab05d1eb01418b9497cf3fbf3ffe11a9105ac3bc0dea07aab799eb00"))
    (468915, uint256S("4706c1bde0476090532086fdebe8ca7097d7896bdc653304573fb3c2460ef9ed"))
    (502409, uint256S("7daf3c226f76dbd97f052ab97526460d01b66d2c6fc3be4367077e5fee8d752c"))
    (535903, uint256S("7414521d6ce62bbd906b7ba7af2597fa00b6cdb86a73d4b0c864f4bdd3e4e032"))
    (569397, uint256S("a3cfd3ac726cefa65de1847a451824cbeac185352399046cc6333a45d2f94dce"))
    (602891, uint256S("602ac22d3352d0f8068897a8ea71c8b7e2b3168838646bf86341fd4e2756e7d9"))
    (636385, uint256S("587f336cf5df469b1643eb8f717ff9d63d490b8737b7908c80b5ab54b518d48a"))
    (669879, uint256S("3dac11c363d14873ccfa7fb970531c14738bfa6b01387edfac79fffad12de4f8"))
    (703373, uint256S("ce1cebe2cb4633f13fc53e5d19ef7a4547ac868e35e7db439e3b24df61b3f278"))
    (736867, uint256S("f477a962eb1a46da22ce08501d76a17db67ddc56651aa0789ce1da4cbda62c0f"))
    (770361, uint256S("49c93b6479f05492428bd80ab82063af99a2134a46daea2c43ecdc2b0474aeaf"))
    (803855, uint256S("c6a397118cb639ae026130f16aa72b72244383b25283f5a476bfe0dc3567d8f6"))
    (837349, uint256S("e4db6c80d520b57527c172dfacb91671708f451bf5302b160e20989df6f5e386"))
    (870843, uint256S("807df890be054a25ee222f9d4419871070d00ad27c6faf549ae8506f0137b63e"))
    (904337, uint256S("61a2e8c36dde419c1d9620565068b960de3e4655bd8662bfbbd2b666a96c81b4"))
    (937831, uint256S("75be45e0416eec9eb41adffc42ae6b2b0ec3e7e3fd1d67d6e92469da1f9e6cb9"))
    (971325, uint256S("a0fc3dc100aa4c1f9e7fce622363d64660b78f6b642699cda61bc98c3c37abc1"))
    (1004819, uint256S("7866405c905976891051ea190d24a8ed71fec8e63bb91255faf30c400cef0ce3"))
    (1038313, uint256S("5932ff65146cddcf1f823c34724f10bf8f74805e8e5a596716e5e3906168a752"))
    (1071807, uint256S("ee930810fafa6d483b252bfb15cc88c35bb2eaae7750370cece57283ee042660"))
    (1105301, uint256S("3c5a76b8b6a79bba182a5f4001883f0fc66076e1d939c5abf857c49a25b5c9b9"))
    (1138795, uint256S("9f0feeb806444ca733e313a0abd21f7cc44ea964aee645350fbe870d0a910d7d"))
    (1172289, uint256S("93e2e88580b67d0393543b004ae5ab22537e698d8330cf6e4cb6dc9b80b0ac28"))
    (1205783, uint256S("e4447f3cfcda32006e2bc381020e88f936fd32946961ef106e92bb7043075ce5"))
    (1239277, uint256S("f67380f1f324bed55314de26dc151291c38265f64c0c16a506e544e3162c72a8"))
    (1272771, uint256S("d4c04091ab550b2d27a2bd835da95d190ab2e2016602874b6771045785b72643"))
    (1306265, uint256S("e1f47958867f83eda4ae25ceb4e8b1bfb2848b0e02065ab0aeb06b443828b3cc"))
    (1339759, uint256S("948d8ef7e4b8f98f1dc8e6315183c7a0102063d56f796dcfc69177b7b6901ac7"))
    (1373253, uint256S("43f3926035a1a557e86874d46890c6ac361d5963607d29092e909533b6d51967"))
    (1406747, uint256S("427a7d35738e081016b0e7cc9e9ed5dc61d53097bbb92fac51cb33bba99473a8"))
    (1440241, uint256S("3a1012847937dd9511d19ecfdf9541a247fa5e12ec291ec083ac1ea83c272a3a"))
    (1473735, uint256S("f0234707215acc2b5993415721d70b6a60740a4654cab80bd6e72f4ce5017eeb"))
    (1507229, uint256S("245d463688d029d75e4146dc4863e8973ca299b1f079e17fe3f82f69012923ca"))
    (1540723, uint256S("92ef9f3641b714df3be1a8a00077c676ea3494225887e23858a852a9f524e4f0"))
    (1574217, uint256S("ed7228d7aa37dce21bbec2526fb7c808a32903b4d36375b6843ebd6cd3b4d554"))
    (1607711, uint256S("c3701823db11a8fd22589fd1ed7fc108fec39a65231dfc83d4050e20549e4070"))
    (1641205, uint256S("d0337394244916f49c8048db61bbbbd94d7e3d70861d252a9d9b821a049416cb"))
    (1674699, uint256S("d3ccac1beacb8a6187d3ff5f1ce879a55dd8b8b01d6d220bb5fc93f340b55e57"))
    (1708193, uint256S("45e8352541e6593c0bca9ff0b44ee610e4e5a907654297938d84628642933b54"))
    (1741687, uint256S("2d3bcfa5419ef05319260e4de101dfb4e3b95db5f9a84d3e8c0e59d504c23789"))
    (1775181, uint256S("c4bad524a54e55ae38f1e722e43912e23ec8aec68e8fc902868e2d69355c14f8"))
    (1808675, uint256S("51773ffbe10a005c56fc83b6e3ceb89ddd6f845235e37f75af7403bf00a0253f"))
    (1842169, uint256S("c72ecbd0bb0883cfa34a532301312ce1d6e3555aaab8d4bcc3c0ae18263b9eda"))
    (1875663, uint256S("27238642cd496e973c0ec3b21760b223626b26ddf5bd70e4aa90de5f0e4d4f2b"))
    (1909157, uint256S("8024dd2bd7da64b96664cd81826a3b1d9735e49f5b3f12dbc3ceabe94ad6cbf2"))
    (1942651, uint256S("0dc74393599243ecd1874dc68cea4f6cbc41e6cbba70a5d75c5af65420b5367e"))
    (1976145, uint256S("b5478fe3eacbafa4a8815fd709aeaff4851af895a1ff067865f2855a4966a151"))
    (2009639, uint256S("a443692ecca2836e79e8fff5843333466463ef84dc6e295fec65147a341c67da"))
    (2043133, uint256S("50d5bbd59f54f83c367449a5bbf4f163d89856c8d5f47b94c99cc2917311e409"))
    (2076627, uint256S("1d19cfcd0538e0fd90ff7fb08cd72ae6d2eda89c5c6a00a0e27f7a8f3379cf2c"))
    (2110121, uint256S("aa47cfcc1b46362e3fef64d3a7492ad54228fd892795c4556173a95753fef482"))
    (2143615, uint256S("53274cb4dd765159a1115521126fe3291da4bf885eb8833b7b5874f78f042db9"))
    (2177109, uint256S("4fe175b8e468b13d734f55ec485b6b70a26815946a399400cda4ddb972e946ad"))
    (2210603, uint256S("7c3ec421faf7830df5a9393216a982e7bb57c85c688b5f823b616c182232f854"))
    (2244097, uint256S("7f576580244f38cdec512b770a94652ea72be44631f9a91c4a2cf9037af261e6"))
    (2277591, uint256S("db2f91114f2f962002a0bd9e5f2c3ddeb0140d27e59db1d731e183281467130b"))
    (2311085, uint256S("7d877831e986ac6b1f7cf57df846807bff3d908ee23d073acdbee544047b3ccb"))
    (2344579, uint256S("d4f0449990263d44ad8e36ffdef32fbe6115fef8dc3e95d1a3d4314df2221a23"))
    (2378073, uint256S("c66d220d4f8be755cf7fe97f8413c363d7787b063fb7cb5a1a29ff3830b7ac46"))
    (2411567, uint256S("493feb4b2266396c3248f5edcd9e21ac1f246939babce1c37725f877e1c7c672"))
    (2445061, uint256S("ef1802c01d5e21943c232c450b78af12ce264c0e6639674c74696e0cffe3c4a4"))
    (2478555, uint256S("09fafee05b620af2bbbafc4ff7633809d99e7314be288900318d19397366e541"))
    (2512049, uint256S("039844f7938b2a58cd3d86657bbce30eb2e2305f2c4f8c022d7b065f404e59ab"))
    (2545543, uint256S("b868d085ed06a21361df053a61b3f9460f3961ab5777f3d03bbae1be958ef613"))
    (2579037, uint256S("e21b950c6f8a0a05ec16f61a8e05ff809d79196f6a12e67d6d3fda1dc7cfea7b"))
    (2612531, uint256S("4269f3465606d7995725cdef50c67c54685372ce0da546419dac2c5d4487c4ad"))
    (2646025, uint256S("747ba453a7dbd7c747e6f444f92c302a52b9539b3f337a3b6ef9a54ea78db31c"))
    (2679519, uint256S("107603d3c82c4c1d6f956e945882b0c40ff19043231856fd5e75891d14ff26b5"))
    (2713013, uint256S("3ebae9931e67283aa52193401dd9790b41b48864857720aefdc8038954ee492f"))
    (2746507, uint256S("0fc6b135b976641885d9bc29449cedaee2bd1acf737b99b177e2043c0fc57b3b"))
    (2780001, uint256S("f5eee5fb40b372fd4ed665f221f0e413f2a647936305410335a0f54ef0df0d17"))
    (2813495, uint256S("14df297c20b8ca19a3793c16d64c504a4f077b914db08bbeb495104a6213208e"))
    (2846989, uint256S("d4bdec58601d7f9f42171886502300894f7a27d5327f42c7b58354c1a71ce5d5"))
    (2880483, uint256S("4e35074dfbcd383091c0c6055c16aa70384cc4eac6b32097dde3a668c7267c9f"))
    (2913977, uint256S("8dc99acd505b9ec066703bcbe7b291063cbec226eb814f196636bcfdcd346ae7"))
    (2947471, uint256S("90fa08fd24798439a81a6e2d40dc69d75ee85377d5100226d7e753f9e081fbb0"))
    (2980965, uint256S("dac744ae2fb73074538ad45af2146bfa6bc7df7743e805dc8c926df422158298"))
    (3014459, uint256S("1d947cf0d9d3569a086d7c38945df7c7eaec284f2386a6759fae20e416376c62"))
    (3047953, uint256S("e4ef8dd96aacc921c8a70d186589eb04cef6cc034f361cb11d0432cbbd4fac4b"))
    (3081447, uint256S("5fd9e0968576e7493eca1bb3283d047a33f41963e0f6444750f3e18f20097107"))
    (3114941, uint256S("bf7e8a48fb5c8dabb99674f47cc91d06cf5293373a5be1a42bc4f60b9953ac69"))
    (3148435, uint256S("72fbb1f2bdd8ae2b21b4e9d7e112db462fedca8c6b6e3ff33b011244e8b47df4"))
    (3181929, uint256S("7b49b838462e804f51126c24f7f40b36081abad96de2ebabf4eb8db379472bc8"))
    (3215423, uint256S("7c91e86dc23671429883aeebcde1de1084b13092a0b46c08b959a0b9e6f75ff7"))
    (3248917, uint256S("a3b2f94a4d1ef72d1abf57bd1849062a22ce817429ecd50a9bd4f6daf013e91a"))
    (3282411, uint256S("c137d7c8b47107598f1174336401ee43305292438695a7c853298b2d9c73438b"))
    (3315905, uint256S("297377f50538805f05a1a6c00d6241ed4c2072c74538361f16fffe8494843332"))
    (3349399, uint256S("3b23cb0a8fefcc0c38c1c62eb8bdc2c0b66d291c0baf380aa4500f47b47ff516"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707829815, // * UNIX timestamp of last checkpoint block
    8449009,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1563924366, 694507, 0x1e0fffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x79b352ef6aa3a1994a4c3d711e2d460385b53cce065611049a9a3c55e49b53e1"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 120;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 3 * 60 * 60; // 3h
        consensus.nStakeMinDepth = 120;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 20 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 30;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03061929edbb05141eef4ce4c9fc5c944c0ee67aaebcca5defaced677769bcc871";
        consensus.strSporkPubKeyOld = "04c90538206b7c4921e1e96e93e83dcc39f4351b997fc57934f5beddf916563497b99a315a772b626e072c9a903209c85172cec7052a54739dc392e27cda0d581f";
        consensus.nTime_EnforceNewSporkKey = 1625615999;
        consensus.nTime_RejectOldSporkKey = 1625788799;

        // burn addresses
        consensus.mBurnAddresses = {
           { "SXXXXXXXXXXXXXXXXXXXXXXXXXXXXFdBi4", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 2024001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("7aeb48ba5038096a31dba0b0a274236297eaab809ef24fe48d58eec821ebbffa");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("24975d012582291480d6604d469acd18b09acd87068f9f1a8309338c708dcda9");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("ea1031ff14a7c59c7df9291d347cbf1c72bb1a9b4aafbf3c215314a14aaeaae7");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("cbf48bacc3e1c8d843fe43be3baf7732c7ac4282f57e171980a2b50d18fb141f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("99552707f5e6815ac9c4bdf764817c21cd72dd095f44a1268c373bec8cb1648a");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("a538111ace7e59b635beac76a113d3a99592215f5063fae161a67bc1176e137d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x45;
        nDefaultPort = 18976;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.suvcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4C).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 10;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 200;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  =uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 18980;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.suvcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet suvereno addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet suvereno script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet suvereno BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nCoinbaseMaturityV2 = 80;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTargetSpacingV2 = 60;
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

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight
            = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 18984;

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

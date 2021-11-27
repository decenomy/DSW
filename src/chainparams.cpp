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
    const char* pszTimestamp = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam felis.";
    const CScript genesisOutputScript = CScript() << ParseHex("04eddc90a654f0335fce2081f682ec2475b935afad5a217ffc9a324b04665054e8a42e14cfdce6a5d11fe0f8e1de9b0ff375905dc58025db46b49f7925d3ff290e") << OP_CHECKSIG;
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
    (0, uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"))
    (16996, uint256S("006976ad8b4d087c348d0ddfbc1f9cc8a05f925f7d6b405d3529290e65e44e58"))
    (33993, uint256S("556ef9c4c8068e52532a430da86a3de3ba29d71007bc18ab6f998af01c8a3db4"))
    (50990, uint256S("cffc3112f45a02b6d5bbd22d4a280bfcdd6f16b5c1c97580ca71c87c91010c15"))
    (67987, uint256S("0ba2a0ff3cb362d104df025fbcc8649eb8f8234e9c5a9ec0f88f731eb83ab6a5"))
    (84984, uint256S("13ac2ac2c4860ed5ef1cad6ce1aa00d7d1770fc71b35314d4f0decedcdd1123c"))
    (101981, uint256S("7b768559453c939c4cb23f56fa49c4b3214f5a0df36a3dd034ce5114fbdf38e5"))
    (118978, uint256S("bdb61c4b20a4d16dbd712b3927becd042914e64c3b421817548c7c2dd4f24e82"))
    (135975, uint256S("87a2e3453c7666a9c0350e2ad16b1d115e0c8de6c62d07c331b1fd77693146f0"))
    (152972, uint256S("f9043dabf1ac2e8696737a2dcf74d65c184eef16944a850f6c87fed319bedd91"))
    (169969, uint256S("e24e27883eedaec0efd75492753674e056a480fee8c6f733dec528116e1b3136"))
    (186966, uint256S("9cd73b0c0d54ab02720f90d4ec33a058779c9f6fd0f1872abf715be55618844f"))
    (203963, uint256S("45076f8d5248d566f92d1c0e1209245fd03881c1c9aaab4a2e898143bbb173ce"))
    (220960, uint256S("217cb2737f98339d7a65e2e214da79abecd29f5d7eb3f85d7e249957d0ce3f11"))
    (237957, uint256S("12e0e481bafe3f1b56c11d232d6365ec7976b31cc253bd15a0b9576a5d3fd0cd"))
    (254954, uint256S("d5015af62cdcf773c4835185050b5a587e212dc92811954cae83a1aa12a894eb"))
    (271951, uint256S("6bfed9f310c609804ee31672b192b8c7651392530aac5efca059cdbc509887ae"))
    (288948, uint256S("daf2e419e6a7489f7d9b2b5457872676abba286c90a4060962fe9fa8acacb41e"))
    (305945, uint256S("8a619ecf4b9f49374437a305c4ee244b5a9a7ee152790f00d0df363179337a17"))
    (322942, uint256S("7d1c6620955f4f5cc01bfbc1420e3ed74b4c92fd2a0e4c8845c04a0e1f97caa1"))
    (339939, uint256S("853112d4e802c149a78833d09ac270859e20f03ee61118222b92efd6bbf91a69"))
    (356936, uint256S("62599f098df6092a22c271d2dffda36fc0a8cecd1332dd21f0dbe655e0ad1dde"))
    (373933, uint256S("9fc39327399ad398103736177c4598c1dac708edda710be3e0387020ef505a2f"))
    (390930, uint256S("bcc4c2b32baabc3994538dad1c02b7cb4b0d29b79ba9011107ad9265b4da57bb"))
    (407927, uint256S("bc2255397046d49eb8dfbcd4eb9aa70540dbb86fb843e75508e65f0fd4c7b5c9"))
    (424924, uint256S("98079b0a353e74c7f3d9460308713cb74ddae04fc75cb38125a21349fbccace8"))
    (441921, uint256S("6dd52f6554b76b68c9e85c2bc65d185a7c46051cbb0139b425fe4a2a2b3196b7"))
    (458918, uint256S("4cf3cb9661436a4d8da4b0c3dfca4858c0ea6dc0a6e5a1542165aeb4e11db6f7"))
    (475915, uint256S("30bb8639ea0b3555bdf5b2a3fe4f64019a3af604c3bfb6f5e3b35c1cf130f343"))
    (492912, uint256S("a5392b02e4e38099b35bc361ffe9c0f5d42f92a75750a6ea5a9da359eef0f507"))
    (509909, uint256S("750babe166721ab60b8f2d1d811b631b17659513eec7161718fc6848f69165c3"))
    (526906, uint256S("2e2795693c0845da1c66a51fe6195d5fe7e413cd2f37ebbe63bc3a7d3cce0508"))
    (543903, uint256S("46e85b28d060128e585e97c6594774160de36566c52f9be524f5610e1a364ad7"))
    (560900, uint256S("df55403840627b7084cf436e9cdb29b685ad57b43955bd9582d344ad0908775c"))
    (577897, uint256S("4ffa3e17abd85f72a960368f26641229e3def1da305f44825bea264d5c963800"))
    (594894, uint256S("fefda83460069ddd6b06b462ec440e8a5f60d23b0f1d873883b0f407022bb310"))
    (611891, uint256S("6cbff2a38697381144aa9574bcbd732cfbb3d87ce02f46472591b72e8b552cc3"))
    (628888, uint256S("357434271f037fcf36bcbf8f23c08c93ae0c68c5c8e9d7e44ce38a0405470c41"))
    (645885, uint256S("fc8c2f8a974fa8aa8e5e3536fb3ccae10c0a71e4be83a39a2809afa9fce07334"))
    (662882, uint256S("724e5027251e43d7ed502abda634c87041b3aeef6703fb47ee99fcefde59d29d"))
    (679879, uint256S("b736d1ddc17e0481899df9d7fdff531e6a8b2cc82bbd182767d5931a7985f50e"))
    (696876, uint256S("e4948dcdeb586416473485c0300d08c4f02498fa0459a72eeda0739fa66cf45a"))
    (713873, uint256S("20036e43662e53fbeb6770df67cff2560b0f734c28bef14c447e60485e09cf5e"))
    (730870, uint256S("8d86f380fed894edfccef684c5ebe58d1c17cef4d0fff296d8fe20454e05c9f9"))
    (747867, uint256S("6a464cc2f2849698b49870ed60f471093f590cadaad81dad54e198a32e795613"))
    (764864, uint256S("b0ab1962890045c9299a277447464b5fe2c7233ff3a3b93e9bb11b5dac3737ee"))
    (781861, uint256S("634ee5c0c2dea72c3a1946bad3d5f6e8786d4c352f8a36eb9c7621b146643913"))
    (798858, uint256S("d062388eac8677c5c7ff39efe037dd7c201804d6761897f0f977320c93f61ede"))
    (815855, uint256S("54e3a7522179f7ae60c7c457dc59825d5ac71628e1b2dd8ca4edf3833b2b7615"))
    (832852, uint256S("45156acdf2251d85dc13257b53c6a5bb368358e803a9995918b41c7a47135fd7"))
    (849849, uint256S("b48a9a8eba2637805e9c6594bdb07d4c1cfc51fd704a9350a5228b8afe52db7f"))
    (866846, uint256S("0c61b7dcccb79ac18b8dd20d8f626614e87df0d0fbe71ba471d3cde2d4da8d02"))
    (883843, uint256S("12e5ce426ec16f246314cab37f075dbb004bc1e235b6b652e0a5fdc5e65186e1"))
    (900840, uint256S("f42aeb152a62aa41737212f0fe7af399aaa52def416bf45e239de863f01bf21e"))
    (917837, uint256S("f9c923d700726706b1942e5e018d4f490e2b62398b95fae824092dee3e1cf64a"))
    (934834, uint256S("f6cd83a2e0285480035068aa64223ea3ee579c43f82502c719274b3a2d0203ee"))
    (951831, uint256S("f394384b5e0a4393d9a7e77db86b5db74ecb3bf1d40a41acf77cba93b42a66b0"))
    (968828, uint256S("c49c381e56bf9655dcd1fc9de660096a3335ac9ed88bddd898420d40c4f1bf7c"))
    (985825, uint256S("2df0962a3994feabc53d2fa8e8a848e0330cc181c13461673dd640aa7bade0c7"))
    (1002822, uint256S("c3e13d3fc6394d2ba6cd18602eae4cce04e0ea828cc5818685ac5eb6d4504085"))
    (1019819, uint256S("36007567482d24bbe5054fbe7c4ce6f2ad441cb12a9d2bebdb55fc408f471be2"))
    (1036816, uint256S("11b188aeaafaa8f000a4d0047beed61d6ddb6c3f1e03c2b4b05941482b88b719"))
    (1053813, uint256S("a347b1beec28f7fc6700b17aed8d7b2258d65c5ed242c11b21b8ee1729d58845"))
    (1070810, uint256S("1ca6bdee69d38300bf72060ca1a28606b921743707a63615ae90c19928141c21"))
    (1087807, uint256S("eb81ebe4c43c2273d248f08386cdbd6e96c3755f7783297bf8d59b58aa76e913"))
    (1104804, uint256S("c440544d91b41915be2ae80fa429171343133d188346b0523e748ca816f8d112"))
    (1121801, uint256S("99b3b878f67cafa005bc1c2265e04d3319a0d0bbd02c94ebc2b9cfc86210b84d"))
    (1138798, uint256S("91dbf90f4bd071309ba87fb3bbff4d3d418cd969fcc9795eefefa42167207b50"))
    (1155795, uint256S("e7fcc800bd1d679417b3e3abf7402766f2d396eb72c108f0b4ee89f3446f4411"))
    (1172792, uint256S("8dfd0cd2f84f81d086330d2bcf3821a2c4fef01f3e9153a2a869cbaccee27815"))
    (1189789, uint256S("54b763cf178e3268905eea0b158d611683582eb451f2c1071618b8776a7eda74"))
    (1206786, uint256S("dcdd4ff8a5db6364cfbc0a8600fe41dea840e58954c4bc96b8a9dccc00b064b0"))
    (1223783, uint256S("f977e0ba03dd07111bf3f5a8ffc66046644fa9f1c5c116038d09b3774c30f018"))
    (1240780, uint256S("fb6330169d527ef38248de6b1de5be403b2c2141a1e14fe19be47b8d29f3c7e4"))
    (1257777, uint256S("464761935f98656ecfc9b52ae00992457f435f9823d4562f8334106e340fd098"))
    (1274774, uint256S("db3f21dd4519bc1bfaef45ce79731652fd8cda568baa4a8de0930b0e00030631"))
    (1291771, uint256S("ef676c790c72465ba43f82a075ee6aa46698171ad21ee117d8d6d255ed77a8a1"))
    (1308768, uint256S("f017c08221dd25d830510678ef0a8439be47c9cc5e13fb7a65dcda705d479729"))
    (1325765, uint256S("4e36f25bfa12fce0fbf0b12d81bf7117fe16df38c851d7dce0e67b00bf2669d5"))
    (1342762, uint256S("219953c49b4ed45acf45a5266230d143a226c700ad4eba18d46eddffff05ae5d"))
    (1359759, uint256S("4db906815052c5fb287b4c48e4ea7249c4d94fcadb9941bdce2bf0a3f86ca286"))
    (1376756, uint256S("88c391f52d420a7e843e35fe3d04baf473914b45a7248194761cb1d2b6c1fe5d"))
    (1393753, uint256S("c4a9d9ecb91b31cd3844f626bfbf5e2b2e8be9891acb883033cad8e7c5dd36c8"))
    (1410750, uint256S("67401fa7cbb356af85d39f604c11de8624c6722f6f069919960ab3e236a79330"))
    (1427798, uint256S("9f1266eea2df006c76b7d608be8b14a58309f0911f1f24bd64e439a09e9ca413"))
    (1445001, uint256S("ae4717d9455ff6dda508ef7a9257006d0bd5973595d0e94096404b1e77f946d7"))
    (1462184, uint256S("36205a5c9d42fc540ad460ad317520077aab734b9042bc6df70f3fac18db4e29"))
    (1479424, uint256S("c01dfd66a45d982807a63df75a930d3c22e4b5791476f431603f3534e20c78b7"))
    (1496609, uint256S("4fb92796c4c62c3a29a34d081fc05017640dc1be3da614dd5f071d98a0bddae2"))
    (1513703, uint256S("69ab77920e7ab7d015f652ecde6d2619f19df4145f0700f233633126ee35009f"))
    (1530777, uint256S("e7a789cc07b3d349f4b207dbcd8051560edea2a19c0894c8eb5d754d630332be"))
    (1547879, uint256S("b1bbb21c85d7882d12ac97b5fc94f69e57ed81e18701577ca532fa0c8578b695"))
    (1564998, uint256S("2d98dec08e5d52d2424ada197462ef7a0f7bc0e9c0f05d08e13535df60beed75"))
    (1582169, uint256S("51592cbf95ea175e8d6b9053943124b5f6faf6e11e9dc9f3fb5ba9ce260b59fe"))
    (1599316, uint256S("6c6029e34816ae6ba16546e75c8f3002fbe56f537675be64a058ed56831b27a2"))
    (1616498, uint256S("23a2a2374de0f7c84699e8a417b327bd887aab261d3ee51b3cae5bf177fd2fc9"))
    (1633749, uint256S("02ada189bf538d3fae997842eee741429e409e77ce7a3e4e8a011bf54699b269"))
    (1650940, uint256S("329f0003da181fe878333f9ad8ef1132b5cb354529ae2dd43212498d361c6302"))
    (1668160, uint256S("25788f8bd01d0abd7e54aa8861d44c5b80af5aa10180eb7a20f92bbb398cc2e1"))
    (1685367, uint256S("81035da28513e2890541001c15fed241fc5ca49360b86e52943df118a00511c3"))
 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1637264205, // * UNIX timestamp of last checkpoint block
    4495872,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"))
    (1016800, uint256S("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231"))
    (1106100, uint256S("c54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30")) //!< zc public spend activation height
    (1112700, uint256S("2ad8d507dbe3d3841b9f8a29c3878d570228e9361c3e057362d7915777bbc849"))
    (1347000, uint256S("30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882")); //!< First v7 block
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1575145155,
    2971390,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
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

        genesis = CreateGenesisBlock(1533728621, 936030, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"));
        assert(genesis.hashMerkleRoot == uint256S("baf314231c2c162bb4bd33665c67320df47e74812821b1ad78faec22c9795553"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 50;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 600;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        consensus.nMintHeight = 1700001;
        consensus.nMintValue = 8100000 * COIN;
        consensus.sMintAddress = "KDkx9d9GRYenjfGtuLSEkCzECH5zXHJbGW";

        // spork keys
        consensus.strSporkPubKey = "03458aea0319e726ffaa7e97b278d0c1d9bacbd983e4a3cec6506e7988380da53c";
        consensus.strSporkPubKeyOld = "0443b94e8f01b62c33c61a8b53b8d7a4d522dc6183fe04639538470930a4bf7f7bfc2453adcdd0e7e8a1a7208c651054bbb0dcbb723b2013f424fb9badbca39462";
        consensus.nTime_EnforceNewSporkKey = 1638316800; // Wed Dec 01 2021 00:00:00 GMT+0000
        consensus.nTime_RejectOldSporkKey  = 1638403200; // Thu Dec 02 2021 00:00:00 GMT+0000

        // burn addresses
        consensus.mBurnAddresses = {
           { "KJXXXXXXXXXXXXXXXXXXXXXXXXXXW2cAfW", 0 }
        };

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint    = 168624000;
        consensus.height_last_ZC_WrappedSerials     = 168622900;
        consensus.height_start_InvalidUTXOsCheck    = 90285;
        consensus.height_start_ZC_InvalidSerials    = 89173700;
        consensus.height_start_ZC_SerialRangeCheck  = 89540000;
        consensus.height_ZC_RecalcAccumulators      = 90800000;

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
        consensus.ZC_TimeStart = 2147407649;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 4131563 * COIN; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 751;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 615800;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1700101;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1100000;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1150000;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1700201;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1700301;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1a2340ca777d4c118bc4725e5326fa23e9072086728788ddb905ef9acde7d4a6");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("54136b30651f42501f26dab7859e8884860b5af7455a6707e0afdbd2957164f8");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("5dd0f62b4819eb575f886b02acd272e07de7d4ce8101688c15fe42d48200b2be");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("bd5886ac6694f69c9179f1ea48c458af0a8d56dd76c3347cb7742c5849b9f7ac");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0x95;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x52;
        nDefaultPort = 39697;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 201;
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
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("s1.birake.com", "seeder1.birake.com"));
        vSeeds.push_back(CDNSSeedData("s2.birake.com", "seeder2.birake.com"));
        vSeeds.push_back(CDNSSeedData("s3.birake.com", "seeder3.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet birake addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet birake script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet birake BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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
        nDefaultPort = 51476;

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

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
    const char* pszTimestamp = "Is Bitcoin a Good Investment: Analyst Predicts High Institutional Demand Post Covid-19";
    const CScript genesisOutputScript = CScript() << ParseHex("04b3fa9f648a6b1f477db94dc72db5df018b5539f081fa32258d6c7ba47a6b47b48187909c1fa62b2087d9e17e115fbfb20b042ff7c9c34f35c5d17f76c458e7f4") << OP_CHECKSIG;
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
    (0, uint256S("000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"))
    (6862, uint256S("4a7b611ad397341c4a74bfcd6e93006d77fc906e416597244b7265592e056801"))
    (13725, uint256S("48bbf6914014d784daca7dd3a6639a69a47d11c57f5a22fde30d49fc40ebdc19"))
    (20588, uint256S("ba36e5c8239c8b4cdbd87e4d85f5947b971579ad9152aa211479370524206316"))
    (27451, uint256S("8e437346cafe6b1a0228f9af01baf133356d205ec9fba2db4c0e2cbc68eb915b"))
    (34314, uint256S("e9d7da6246233bcc901b504957af1e9911bd0e0bb0e4c27fbf23007bb9eb8915"))
    (41177, uint256S("448af53281d2995e7409db6b351d8eaa9931b85fa97471a92ec8fa6e83be7e7f"))
    (48040, uint256S("8d4792e6a21d442fdcff207eddad58cb1e7cb3877b48b51e27f1bed29af3326a"))
    (54903, uint256S("8030d7b7ec946f5592c1eb856703221cf8aa7b1f730ce5fe16f7cab2ae5eefaa"))
    (61766, uint256S("25a8693dc169dabcfd63639423c7188fd31a58c34825871a779a405a4233656a"))
    (68629, uint256S("61bef6dd4d216c8586bbcc00bd050b27534f0c7520df15121529932e4f311bef"))
    (75492, uint256S("19d9125b07421e222617827f8ea0f8804badcf0a36bc7a1ef9bd959109738321"))
    (82355, uint256S("19437844c23b6d010010135396e2f3000d36cc8a400fdee96fdc76d1a2bb5bf0"))
    (89218, uint256S("3fe553c6129921530dd306971db501b606f49a5729ef858be9f28595cb364640"))
    (96081, uint256S("0c35a9c3a985144e7f60742ee6206e1ec335193bbcae474cf3b8eaa44cf52a1d"))
    (102944, uint256S("0125dc9b8a5dae9ab8ef732d7f1feca5a4795ac8c4b6234bb6d6389fabffc03f"))
    (109807, uint256S("4882b445cb1a45f43767ccd4b47c2a2adcd03b8ebb6c1f53f4795df10ffb6289"))
    (116670, uint256S("b61a1015843de234ad14c9294a3ae3e00c6cb4d98b1d5eb1724bfab5f0492e9f"))
    (123533, uint256S("67eea44551bc0f14ebafd4de49bd86d616d281d281e59f774a0d18b341381859"))
    (130396, uint256S("8bc962af746a7c818d0df68a090cca57d35c5f9937bb181eb3485850c44db3e9"))
    (137259, uint256S("0afbf7d8e1562515147b5e1830e37eda4045c11dcbc982833dabe0e68e5a43be"))
    (144122, uint256S("4d38a79eb9a82edf35f4ef71890cc112fb1b351eeee7b292af0f7c4ca83296c9"))
    (150985, uint256S("8468f03633968abec87faec83aa8d90b158fdd79c9505752d092daddb96c3b9a"))
    (157848, uint256S("839a6b8926329477a8c68170ff96058cb8316299c8298a44f7ae04b49841b8dd"))
    (164711, uint256S("2672d9ce5142fccf3894eb03e9cf5a93a4433cd4e884a2fd384dcae04923cee6"))
    (171574, uint256S("c6a7f676fedab9ce912edcda9e5c4c33c8b685c2cc069ff92f85097ed9964254"))
    (178437, uint256S("f08c5a52270093c7dfe02fffaf0cc9320be031bb584389566e6da7d25df90e62"))
    (185300, uint256S("3346c3844bed4be62008f135e39bbc0d0448d7e24ab8cd874ece0bc3b1f8144a"))
    (192163, uint256S("182270c4d7623414292af8b09d75cab20a2b93cbc1440854c3285e5749aabb53"))
    (199026, uint256S("247b1d8fdbef2a89a81ec37887dcbd2c8e570939ac859b7c149b69c2fb8fff84"))
    (205889, uint256S("7e8ea609a599e28b8faf30b175faf355bb32fb2face0c87edc5e17aa2fd314f0"))
    (212752, uint256S("6a19d96ad7474a85802b4bccbbef5d86b859d83114e2170bc50626c90f882b99"))
    (219615, uint256S("e51dc3af40977dbe84e66e163426289de26a9316668a01fda296c3bd81a1b997"))
    (226478, uint256S("10c3264275d290a591dc30d55f53f7c88d324ab2244c955c1707d179f8a34fd5"))
    (233341, uint256S("0a6ece541d2f0402254bde192e510cd2aa8ac81a76b148ae40585212ce87c6dc"))
    (240204, uint256S("e07669c0386b9fd9066edb870d3e7ef002dd7d895a22be431f0d59273995bd59"))
    (247067, uint256S("6db52ef885cf39ac085e1538ec308230ecdf09c2296182756e7ca7601bd08205"))
    (253930, uint256S("db8cc8c4bfe57b3c5063b158fd422333b5229a82cf3ac9b5ff10ffa60dce1f71"))
    (260793, uint256S("31db437a221fd393f0a56569ff08683ee1395e2385753928a55f6e13d607018f"))
    (267656, uint256S("96598edffa51b807fe64203c69b74d8d30fd8a0512dcbacb3b8799a43b686e5a"))
    (274519, uint256S("57a2713adb24497694279a2aaef4f352fcd50e1eb526cff07e7e721170d081c4"))
    (281382, uint256S("3d07733ddf8d1c8461d5ada1c2031b16f071dea4927b31f0355b3935f6266be2"))
    (288245, uint256S("1e355e8c91ef5a69d9eedd6862731893991176e60168da1a98d147907f532ae8"))
    (295108, uint256S("8bf584e00542b72a38f0158c94178e5cb6ce154d7ba040f943c68c35b5b9708d"))
    (301971, uint256S("310dc04f68032a57b2af04f5a5f4d7c64a66425609ab86e8a8b3ae0beceade4e"))
    (308834, uint256S("350480c62e1bc06377b4c8d9a4f4b92453889f28e9aad7a1cfc4b4573b412322"))
    (315697, uint256S("32b41bc9bdf1528e74ec18ee1d985e77691eadccd4cd6aed4550fbf69eb99c11"))
    (322560, uint256S("5065159afa14729500c33a7ca7b338fefedc99e2044e7f5bbe87dc16774b45bb"))
    (329423, uint256S("023978112ff61132cd9b53568f53bca4ebf312b76a601fecb9931fde2c9e6ec3"))
    (336286, uint256S("0dfad5a433c79e3807e968cafeac30ec1566229ed3cf19eed339a8012a8363b0"))
    (343149, uint256S("19513148050e8f04ed0710f29036282040d5bc9485305a330e6c759e2b7b41c9"))
    (350012, uint256S("55a0a63136220101fa5361cd7e29b975dddbad880a20a4756c049040e4e3f0d0"))
    (356875, uint256S("ed88461e0f2d545f8975b4195820fc08504cf32933c9def54ba4b535e4a52900"))
    (363738, uint256S("d3fa7091c78bf715be5ff37eaf3c05e3719ece263441536e152b5369036e2971"))
    (370601, uint256S("c6ad6c7603f41e894ce0dcd1251861738c989dc9474cb2544c9b397b5633c97b"))
    (377464, uint256S("3fc1526262862243f5e2d73b4d5fd175c36520ae20333d02e8e2e5a692ac796b"))
    (384327, uint256S("738f268e4346cf0b5042002496416646478b80f9c592e71cf5681dae6f1cd2ab"))
    (391190, uint256S("22c804b0a3df2c43701c34f470600d901f518adf50a3b05ad230d79cd2dde81a"))
    (398053, uint256S("d31b8ddb814aa798e01a8cc68e260a55f8dcc6d67c75ab22439af9503c8c0613"))
    (404916, uint256S("2f819532ba7d758baa11a2bb832b2c1c4f07f9bcabc8ec82f7a74db922c97c15"))
    (411779, uint256S("147a020fa61b09cc9a7d7e34d28ba4d278fd00e24f8a4d32cc08a2071007cfb0"))
    (418642, uint256S("c4d263f04addfae54c5f5fb7dac26548fd8438b5ba74f7b94ccd6fb255b4e90f"))
    (425505, uint256S("82cc1ca360c5f82e651ca7d3cae0cb2d9af5d96f771b6c2d1f6beab13e56ec34"))
    (432368, uint256S("655424b54f00cc4f78e610f0f4766d70f5c64b200287316362dbbb84ed2a1d65"))
    (439231, uint256S("3cebbadff15ab1bc3d2559b863842d8140b19a60c5297bedaa6f4567d0cefb93"))
    (446094, uint256S("a903a7be9c2ab26cb8c4a50e9d085a980d1035ae8cca1228cbd1c5d29c3d9c8e"))
    (452957, uint256S("0a742a222be52168446dc370a6c70e1f57248063e56117eef5198ec6ce20a9b8"))
    (459820, uint256S("8f25376c1ed87b57ac9fcaf0f61da7d750d622a09ffdeed1c9c9612e3baacaad"))
    (466683, uint256S("dd4650b4714e35f8c57b258c10a7d1bfb28093a5c072552a28f9bd5113a7427d"))
    (473546, uint256S("779695bc4c7eb7f011f204c55af85b36586ed367560716fc75eba054940c5c80"))
    (480409, uint256S("7d407cc32f676a56f8b56959dd719e22962b2f734c441ac293f28c828f551b89"))
    (487272, uint256S("d455fbca4ed5966e1a47ef357e787a1180a33a466df13688bbbc2b545d485c5c"))
    (494135, uint256S("a4bf9f63a340e99abc458a6775cc696fccaf9cc642fb81ab925e6335deafeefc"))
    (500998, uint256S("485d68d8d474de89997497200205f2b0fbf9396adaf9973693006e35e08cf94f"))
    (507861, uint256S("35a56c61fc473b031f25f46590fdbc62f648e49fd651ede6afadd2a51e95fc44"))
    (514724, uint256S("4190cb62d686e52a5e06dee28e1c2c3e65abe79f12978813df54b984ca19713c"))
    (521587, uint256S("b4b6e16b2c7df81ca632a7e1da79bb3added81dc36380ba5254ab164307f7a59"))
    (528450, uint256S("146695dabd67f3c679bf5d39eda2dd6c116dea6b9b974e8fa1418fce3162c291"))
    (535313, uint256S("eeb54de2b4ab8a7ecb677f30ff861dee9ac8a7c1bab39088973a28c574ecd297"))
    (542176, uint256S("73df3f6865e6e104e2890b632055e9263dce116c86413fc551b9fb8584a75c57"))
    (549039, uint256S("cb15e1afacbd5d57226a0e91dc712c8e7202b70cbba07a0413d8c24942e50c77"))
    (555902, uint256S("397f6d65ab1f4320aa1648097feaf4044888153d2bd80c99e94fbc077634d0e2"))
    (562765, uint256S("88c1e91c30c1a4fbb0110503159223cb0694c4a559ba3b4ead309b83ef2111d6"))
    (569628, uint256S("b851a83f1f0e1fdd2e5642b3d8557de62316fa1caa861ed9459435d29d22f91a"))
    (576491, uint256S("01ad03af2044d02775b22b9aaf496fc73933e0839e3808b3867d8ad73b2d4552"))
    (583354, uint256S("f06661f6302c0290250edcc5cb107ce7417aaa7eeefb91fc1d09e0b09c8f3570"))
    (590217, uint256S("4d3f157c716730001634a8ec67cc53b4556d777691acaa649e5b94704ab87b76"))
    (597080, uint256S("2dacd846d306955a9239c43ef4f1e6771f0571f069ecd6755ef6ba91ab92b1a7"))
    (603943, uint256S("6786ef34562d22ff8af8e502ce039f891730f3d7841c8fc4015a35f9df853803"))
    (610806, uint256S("933ddc5671e6fb9b3a481c97a404e73dc6b9245f164db6f372d423c48b8b70ea"))
    (617669, uint256S("088cd42e96d28e0607fdc5b2c7612e2ad863e29bb69f4980f9beb92771103b4a"))
    (624532, uint256S("58f2b8741722983a8cf6a1f5e6bafd27796017b07b7a8f671d4cfe3f46c169ec"))
    (631395, uint256S("ea7c2d03a425b150458ef8ddd708a89c8b19996c5a477085bf899823742acf59"))
    (638258, uint256S("72cb7cc520242f534c5a4497d694dad7a86d978834c2033f7d90c0f0ae2f7de0"))
    (645121, uint256S("e36a8efd3aa742f1e28dd270a2a622df8f0564bf32b9341de1d28a0c8d279ccc"))
    (651984, uint256S("a2e3338c8ff4925045e70952c156b082a37d10a6731bc46a9399910a1c4efdd7"))
    (658847, uint256S("b538b6597ef295aaf8826f6f6664c4afda538937c737b52c8f65f8b6a637e46b"))
    (665710, uint256S("60e2be1541c0d70451b534f21a0190d43dedc6a9a32df58b77b634bcfe4d6e3e"))
    (672573, uint256S("707a262fb0076b524059842007c0607e66db4d9f3e897ac71a8c5f248001b7c4"))
    (679436, uint256S("85101e2a1f63108ae681888cae4da83491faabe0ef72cf2e9eee76e8e77290e5"))
    (686299, uint256S("0c93e35004cf402d22a605c47939c11049f47350701d9cb7559f46b1a900b042"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686257145, // * UNIX timestamp of last checkpoint block
    1537077,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2858        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1587772800,
    0,
    2880};

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

        genesis = CreateGenesisBlock(1587772800, 548987, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"));
        assert(genesis.hashMerkleRoot == uint256S("0x24c4359abe6d653e1a86916a0326cfe84cf959fdc9cc60659d3c5901b3181df0"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "038da032fea63c7f54c820e600ce4f568a63a013570a76770ff71401871ce7c748";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "MbURNXXXXXXXXXXXXXXXXXXXXXXXTCG195", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1101;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1301;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1401;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1501;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1601;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1701;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("2e320a2062fec37665c7b1c33442a1aeedc887fef37a2ba208df8d136330448f");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("818dac1349e48c56c9beda5ef0015908a17ee35545febba405c5827496e981d1");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("d7777b62abf541e637ea76f2bfce77c3a878354174223bdb43d3776a7e567f31");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("00ed73543b2a555a7154421143399250e6044c93380caa9a8a722a28ad4da5d1");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("a297d00abf468b3eee50f0f80a347029691e9cd46f2a0a1f69bff8e1a099975a");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5165a4bd37eacd57e7c61e5a3c7264fe0a50787fb30b2e97cfde7258f7a74a28");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("594bbd3655b3a2d00f16820b8637ccfaa43c83100d7cac97886ff6350fd75030");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0b38649f5de753f137830a3c38a3785c0fd5f33439bd306240771861b8a0a34c");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x6c;
        pchMessageStart[1] = 0x79;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0x78;
        nDefaultPort = 22487;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed5",  "seed5.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed6",  "seed6.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed7",  "seed7.mobic.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.mobic.net"));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 51);
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x51).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
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
        nDefaultPort = 32487;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.__decenomy.net__", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet mobic addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet mobic script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet mobic BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
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

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
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
        nDefaultPort = 42487;

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

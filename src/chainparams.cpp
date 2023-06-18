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
    const char* pszTimestamp = "25/Apr/2019 The SapphireCoin Launched!";
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
    (0, uint256S("00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"))
    (21712, uint256S("630b3d784c4841c0dcdaa4655a43a844fbf1eb84aab67047f7a84571482f55f6"))
    (43425, uint256S("55ddbb04330928fbf14cfac211e7d0787113861c8959b476e0c81cc17ba8bec9"))
    (65138, uint256S("6d7e4f08153455c9c5f8bdab320620bf185068ecbb232e209c7a60dd13b18e7d"))
    (86851, uint256S("76a49d467cbfee7b10459fd67828eb053c819dc164f5912f701c06b4adee0497"))
    (108564, uint256S("2f9ef44b7a5ccefda2d93c0db6bf0da8fce60a84d5f66ac6e13111d73229bf87"))
    (130277, uint256S("7191b1ebcf060253e0ab57f90c6eb271d74529ee4ea6761197befda44f1f86bb"))
    (151990, uint256S("39936657295f14b7a2dcc225381cc749468c2116f9e87ad2a4015f6843042916"))
    (173703, uint256S("fae222b881bf250530a0a63ba80a88c7638f0aae5bf8831f49f636264dfb16a4"))
    (195416, uint256S("3d6610255a1503dfec531a1ebe27e2c05eb5b215e6c0c865ea965afca2fb9e59"))
    (217129, uint256S("b1737468501710f9ab71be67733becededfb19b5599aaa54874b1b091bba6c6d"))
    (238842, uint256S("a7b0be49a0fe911e51b3343b4961fc46d9a14cc9ab85adc7cb35acdef82f5016"))
    (260555, uint256S("ba80ebcb50b48559856454f46678388ea4bb72657fdeccee686df802d9844527"))
    (282268, uint256S("33fc1368d1ebcc77146b1d3b61e490dd6831676a3524635c9f53c51a86dccd63"))
    (303981, uint256S("6b8bdfd6ff1da73f84e04ba8272ab72b08404d29ca2e5ecd90ca36b9c27ee18f"))
    (325694, uint256S("3a9b872e9ddc68505db2d08c4cf6d502bfb822bc27c6197333022322f044478d"))
    (347407, uint256S("6f5de8a02e55527d96312463df4c9b7bd57cd8c486befbdecbef57e5de1f9649"))
    (369120, uint256S("7788898cec7c04b1819524f398704768b316c7ab3010cac6e3a911731609644a"))
    (390833, uint256S("0e32f101932465c26379f09133ea6286cb988ca48c211a2e85a038aaa43af828"))
    (412546, uint256S("bd885dea4aef284eef5c8dfa0925a5a030f8c4544e1474bb4a55edef540c02ce"))
    (434259, uint256S("718bde81e7cca152001ff4e892f1ab1bd9d3bf8a1f4d2eecd8ab37ba34c40cae"))
    (455972, uint256S("05718c082dda73412e995a80ae8809c7a38d65055ccb60c38b1cff4a89c8bd43"))
    (477685, uint256S("ab2104f53949bb08ca70d85bcfb04d5295d7f9449875ef354bdbf27e57f0bffc"))
    (499398, uint256S("a817c4e6498aecb5d3ee0e60360360d98a4197588c1849192879425c292ea17f"))
    (521111, uint256S("b5f209c68067ab64a81a120e59d459ba51d469eafa86df8168d3838f4a6a2183"))
    (542824, uint256S("02f793564f7bd5cd22937e5862d1d9e3e40684d98635721d54fe41cee4e1b523"))
    (564537, uint256S("a1978c4079e9c9ae25d6562046834084409436b9763516eab948aca423a947b7"))
    (586250, uint256S("207bdca86f02f36624cb099bd8d6499c9c5e085fc52c630ba5a6a55172d8a41c"))
    (607963, uint256S("2a29001b070372dbdcef93efeb7ca7059b420ed66c709153218c9847526a4e0a"))
    (629676, uint256S("ab5173a9f4502b6aeb7918b8722ce32755d18d28e0059523015facf5847e8ece"))
    (651389, uint256S("d8a98780f6134a1bfe8ce924987ab5b94d999cd60a92ebddbc74ecb4021ba5b2"))
    (673102, uint256S("8e0d28d133f79590d823aa02bdda4d07a33a97d9a6e3600136f845aaf5690e3e"))
    (694815, uint256S("2ae7af05b082962a3846c30c920521f00c92fc0a0b198d7db9c7edb9b6c1aa99"))
    (716528, uint256S("816dfd5df1d0e0d8bb708f15689aa557b708304477a921f23b3b9ad49f917470"))
    (738241, uint256S("b130f9a43cb6e1a7c96e157ab8010ed8fb6ef168872ae178a069db4ecd44fc15"))
    (759954, uint256S("f9f94ac1477a0ee34530020d1b09d5dd9012021f03a3311b77d256413e148f5d"))
    (781667, uint256S("d9a0161d28c19188fdafed6f88061755ea78ada3172f186188ac7f3d70a4867e"))
    (803380, uint256S("7a015cd22d25cf5a9b5eb089df548f2f46c5a915d2e7f3d321f19ad082a5fb0e"))
    (825093, uint256S("87e05a59b407b21d69765f39d3fe116364f877a35d9b126950ca67db42fb44bb"))
    (846806, uint256S("9e04e0fab1748325429177edbd6744bf46e6ace95875a3ed1c299b017ad720cd"))
    (868519, uint256S("edca62240629ffb7c0ce6bed2c660acb8de1eb63507fca1fe8cc63531ca6b7b2"))
    (890232, uint256S("eb57ccba19d9419adb9e2113fe150b3affc261c4c52d3fb9bf4d835631c33e93"))
    (911945, uint256S("997ed95150d5c57c89e107ff96e1cad05dece93dbec2e7a42c8fd39ab8bc974b"))
    (933658, uint256S("93d5e523c9addd4f116ae52d091beaedee6d2a094d7b480d3a73ddb9c33d8316"))
    (955371, uint256S("a49e59b5bd3934a7f91e9a5be213bcf4fd42ae941a125314045ed1faa3420d78"))
    (977084, uint256S("8fed4bcca5b9dff137d8bd4302df5e9e7913adbda4b175bf41377c6e46358a95"))
    (1000167, uint256S("87ff147390e1855158631ee657881fe1a05d91a6258946a0e3106040fa96af9f"))
    (1022726, uint256S("1e536f9a07fde9e2790e2a9602b0c3a168b5811c266802bd78b0fbc139d5b982"))
    (1045948, uint256S("4fd8b304cd5dfb591bbe074596bd0270bbff6aa4d236cd5c2d6f80d919a92556"))
    (1068561, uint256S("6cb78ae8586bbd0539809407066bfed8fd333d1333749f14366bc0b3b2545dae"))
    (1090952, uint256S("1220eaa6198ce6409011f9c312f909f0b830162dcc800e7ddc962ba59b9f70fa"))
    (1113206, uint256S("239266e05ba6a4ff8f1c4b9cb6bbc2605a8440681829c810be395d40ca76d2a0"))
    (1135637, uint256S("15cb2d2f3f6a3cc0e5b3b2e9d9c24e13839c22c050b6510937f59c5823814421"))
    (1158594, uint256S("a18a2068bc43bb75d4e486e419e0b0d73f1ac45e2051be1704c3ca92598a47b6"))
    (1180889, uint256S("73964ecc37ff505fee56ebc891645f9511d02860990741dfb20c16712ad978a7"))
    (1205016, uint256S("06314087a92103d1669274bbe7dea3e80f0077ddd96a2bcf2824d0ac4367f1c5"))
    (1227260, uint256S("b26e98a25f3a2f39e625670d73401988a01ee9cddd94d0a907983b330eae6e60"))
    (1249406, uint256S("2852d514919d7217b54df411893fde892a7d5806eb7d115d109261c1653d0a01"))
    (1271554, uint256S("822c7372f56d6fba3c721c65c80ea1a8672ac3da64ea355cafe3c819603c3cbb"))
    (1293740, uint256S("808c099d3ddf8b68987401f96a81f6a6cc5b30f42f06d5fadad0d57eeb0dc06b"))
    (1315947, uint256S("36b31f0d2b68b68f05b37b494f38eedf0019bf6d8b1a162f2ec7a283bc51aa9d"))
    (1338037, uint256S("6542b337e962a6d44f4d78a0b238afdd1c6d52ccc0de83e223207fc17be9c49e"))
    (1360076, uint256S("f598264a789976e16a7a238ab0afe9dd48ab84832f74773bf630152ea6c005b7"))
    (1382157, uint256S("5aaafce1444586d09772d3f353cfd4220e2e364f096727844c598a9a045f7720"))
    (1404498, uint256S("a0a0ce4a703aa237259e2f5729c6de3ad3a410c5c252646d2d2c4628692d0799"))
    (1426934, uint256S("f1654573b1e6be7a40b8561b0d65026838e2c9df17cef7ea1d0599cde3d203c6"))
    (1449288, uint256S("655c549834f173d488b8cca2af6fbb7be2127317a6d28340c405b6974244516f"))
    (1471547, uint256S("a2610615c33e00240fdc25be5a55394712aa1c972c357482264ce1966c1b2c8c"))
    (1493852, uint256S("7de7fc56d280929b2c408162f8ecc780d20c74f75b22ae810dfd546ffc195f51"))
    (1516289, uint256S("7dd921dddc4a4c75bbf2be3d913b73266191392adfa07fe26cbb5cecac0c0466"))
    (1538671, uint256S("56adc034480ab2a827e88b094f07904df6ee372edbc2a5e53a591f63dd7cb537"))
    (1561088, uint256S("8cb102e4ef27c24281a3bc89ece806f7e2240f0bf12d5ada72992bd140ca49bc"))
    (1583417, uint256S("84fe63fa688b0e3490c6fbf565b94c8dc1948f127443dbb97b5530696aa1d54d"))
    (1605971, uint256S("890999dd81242640d55a74b5646e78adefcb7e138041cb6018c814dfc1e78a80"))
    (1628345, uint256S("e738e7836c27db38f3c0e28299f21b9dabd61a3369cff40fc6eaa09eb34e7546"))
    (1651067, uint256S("26343258d6326cb25e1a06dd8611aacf9613c20ae2fd5847aba02796e93a7957"))
    (1673608, uint256S("c8b21ed33f67171da5e1acfcd520807a066c026646c89fd13b040759b4b3368e"))
    (1695912, uint256S("c2cfe3ab14918db6298ce93dd5fd4b882d3ebebe448f9abcc81a594eb6bddf1b"))
    (1718396, uint256S("941a343e4dee75925e7a3c0c3c4943cbeb5f1fcd52deaad9c5108517ea7dc95a"))
    (1740916, uint256S("20d30d4fc7a8878ac21b132f07e94a2cc7da2387dc24f4559042a76ef9593f75"))
    (1763186, uint256S("83a685ee109180d83c6eaca01a6eabbddefe7d3d154a83659ddd904dc5c2b58c"))
    (1784899, uint256S("2dd309fe34cb8f954aad3cf097a847448949486982cae1e3f5da18d810eb1277"))
    (1806612, uint256S("c2e17e765ca693227c351a2420649301280245c0d49c4aa2bf126e769ed6b9eb"))
    (1828325, uint256S("c7f3e041dbd8bea5df99ecc686e6abef5bae670292e85a22c62977c45fbf6ca1"))
    (1850038, uint256S("db67f1214d5021d8f107a1d8f08bd2ce6eb73ac75aecdf5f06a6d48091c855d9"))
    (1871751, uint256S("2b75fe33c1d5a22aec552424dba1bcc14f71ada14729a6407561719b4cb96fd1"))
    (1893464, uint256S("61941c68b00b0250d25bc71f40bcc4f29fe1b5b95f3c51d7f35bf2341c7a8b5e"))
    (1915177, uint256S("72865302d2b0e9b95716bad0ce022eda6f2b407e03f9f62574878542e23864e4"))
    (1936980, uint256S("e253812b5dae36e09b80ce56da2ab0a28a2ab6fe3063f592a82811c71d46c464"))
    (1958693, uint256S("4b0ef48a7e7e7b8e61aa400f9ad1aadcbd71100dd1ef55ee2c499da41a29dbae"))
    (1980406, uint256S("5e5744a0df99341725fde6c5f459ab92ce73b437edac4c7bbd8517de66581a12"))
    (2002119, uint256S("858735820907bead46f38109d8b6f5790f7047a649b17b348acf31a7b9a80d69"))
    (2023832, uint256S("511137ce40584bc06989f7e3d0fae9a8518d6acfa433e7d8ff0342856e375b97"))
    (2045545, uint256S("12de56037f6a5cfdc2c81ce17e8fd2b3fe93889e6925df3fa4d3e786d53a1d27"))
    (2067258, uint256S("e2d14af00598568e6e395bda33d422607625fdfa136242e169e5bff2cd379313"))
    (2088971, uint256S("933d8b6beb8e8c8ebb26528f9bdb0aef434762cf19e68994687f78ee8b54afaf"))
    (2110684, uint256S("4494be4048890e3a2801753682df0dcc976742c91e4390c74b1283272089e926"))
    (2132397, uint256S("72e2390c2f0c23532995cf7e27a196db9b3cca1b8e6a9a60b02b8b91e117d0f4"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685958480, // * UNIX timestamp of last checkpoint block
    14050728,   // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1605265870,
    0,
    100};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1605265870,
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

        genesis = CreateGenesisBlock(1556165178, 2894113, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

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
        consensus.nStakeMinDepth = 60;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "SXXXXXXXXXXXXXXXXXXXXXXXXXXXXFdBi4",      0 },
            { "Sd2xcwvvtRH8P8sLemSiPjadTfBd9myPbW", 586593 },
            { "ST74xpmzemL4ELiBpyDmirzgahujSUiYmM", 586593 },
            { "Sic7sZBNkijna4zNLSVgTBkfr2ebP6c9wk", 586593 },
            { "Sh8N9R2Li5Wm5B7g3xxfEotp9Vpp38baJM", 586593 },
            { "SVAjKY5p9NPSNwG7PLK3VzeXUdJjm2W7CY", 586593 },
            { "SQfMZVatpQR9b3KdKp992nxeEZNWkcz7d2", 586593 },
            { "SNAgLi7pfHD6BDAkQQ74ixtT4o59wkqP8Y", 586593 },
            { "SS6ZgTuvafGX98YqeHdu79wpGrR1KxuqMw", 586593 },
            { "SMoP6U7uazpLdqZ18GQFVNNuV77UTK16wh", 586593 },
            { "SjfZFjCv2PxNKQeDgW1RmsFjSpq5PngaZc", 586593 },
            { "SPop7eX3kMjwojy1k1EHAqBoodhbski4tR", 586593 },
            { "Sf3KBrFqmD3PBHrwTpdsFgUTctEz9mQn5Z", 586593 },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 905001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 905101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V1].nActivationHeight     = 574500;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 905201;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 905301;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 905401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 905501;
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].nActivationHeight          = 910001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1200001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("ef544e9c4181e103bdcaae6153aa90495f1f830a91368364c4b8b97a3782e579");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("c36a49839903e01bc2d6c44f20516fd5f3d816cf2d16cd30c488986668bdf269");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("2033cd79c94ef01e04c0b886944350af7af4ee2dcdf2bb2a8f417ea48dabecf3");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V1].hashActivationBlock     = uint256S("f0cf896ad6fd9bfc188853d5354ddec23972f9854023f92a7e3ba0886f3ef4d9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("502226d6ce3e3fd036452b59b0045ff478658b00a42fbf3434630cfe775d84ae");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("9002e71bbefb2a10d5208b7e8e0a2182d2b13a55585c595752454c65dc9cda02");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5b37c32d7c08cf98df958953dd4c32820f0609a4f4bed452fcb0811bec60500e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("f6326f790d1c0d01843913b301b56dc0d984e9d76e0949669cbeebda37336cf7");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("96dc6197a2d0cc2b9dfe5487b35f0d5b051d1dd958de19e00043897223c08ea4");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("92330b37f9e362b521a77ebe3fb4a1dfedb8d055770bfa601eb0420c4d81b3f3");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x3e;
        pchMessageStart[3] = 0x58;
        nDefaultPort = 45328;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back(CDNSSeedData("seeder", "seeder.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed1",  "seed1.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed2",  "seed2.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed3",  "seed3.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed4",  "seed4.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed5",  "seed5.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed6",  "seed6.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed7",  "seed7.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed8",  "seed8.sappcoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 25);
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x02)(0x2D)(0x25)(0x63).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x40).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added

        base58Prefixes[PUBKEY_ADDRESS_BIR]  = std::vector<unsigned char>(1, 45);
        base58Prefixes[SECRET_KEY_BIR]      = std::vector<unsigned char>(1, 179);
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

        genesis = CreateGenesisBlock(1556165178, 2894113, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // sapphire starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;

        consensus.nCoinbaseMaturity = 15;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.nTime_EnforceNewSporkKey = 1556165178;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1556165178;     //!> September 26, 2019 11:00:00 PM GMT

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 878611;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 878631;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x46;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x64;
        pchMessageStart[3] = 0x23;
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back(CDNSSeedData("tseeder", "tseeder.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed1",  "tseed1.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed2",  "tseed2.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed3",  "tseed3.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed4",  "tseed4.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed5",  "tseed5.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed6",  "tseed6.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed7",  "tseed7.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed8",  "tseed8.sappcoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet sapphire addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet sapphire script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet sapphire BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet sapphire BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet sapphire BIP44 coin type is '1' (All coin's testnet default)
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

        genesis = CreateGenesisBlock(1605314006, 18440, 0x1effffff, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000529df5fae941569b6466128042f5f036a8d1d380dd484a06e8a12fb275a3"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // sapphire starting difficulty is 1 / 2^12
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

        pchMessageStart[0] = 0xa7;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x72;
        pchMessageStart[3] = 0xa8;
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

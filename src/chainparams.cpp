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
    const char* pszTimestamp = "Its hard to be a diamond in a rhinestone world";
    const CScript genesisOutputScript = CScript() << ParseHex("04269d7e08ec3f33895e990cc9d0df716a860c1165f0c4108a9d5e0ce04dc93803606b1b30adcaa48d6fce12c676aad91a9117aca59f7f60f56a1369d6fb2e9729") << OP_CHECKSIG;
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
    (0, uint256S("00000e474f09929213ecad858b8c24002f8146cb459b98e5f665c27eea85f279"))
    (5228, uint256S("17742a8645ea5924668cb6e24cdf5b762e6b307aa80fe63f2eccd22fd3d81db8"))
    (10457, uint256S("e1fd4a4a27bde0d1503d4fa801333d3700fe28e567f056d384a9d9b8d5846a96"))
    (15686, uint256S("e273f1544e558db8f821a39d3e6818bfca998ec9923cdb3115417b7b11fd0cea"))
    (20915, uint256S("ce2932c78011154b89d26716906ef6a7f2a6a30c80478fe40e8d3240ebfdcb37"))
    (26144, uint256S("a03434d429054099bbac02ffa5ef99018190b2b784a4399e695c1ab0335f2287"))
    (31373, uint256S("cf7e0f636360c9b0aa4add59734d4a588d782e1dcecce612c1f9931311fb8e33"))
    (36602, uint256S("b268f705a2012787e0b20c6194fc8120db2a6b06b9fafbdff2c72451814fc70e"))
    (41831, uint256S("92e16cf271e2d2e96aab17e09776af523a26ab7de965cf523e1c21dede5873b7"))
    (47060, uint256S("220a1bd9b451dfb9e153713f0a8a105d7e66b81d1e5c0e65c2f6bf0d113927a0"))
    (52289, uint256S("d53052335ab84a2f8f97658ebb82771dd07c688f2d4b50e4e54f9455e30b0dc9"))
    (57518, uint256S("e0e77c6d65e6ab0d0a840920c8909fa424bc536484292923f05a2388e1feffc8"))
    (62747, uint256S("08c105294ab4a6920eaa730ca2edbce90e4e2e5ceebaeddc10e8e7b2a00ae4a6"))
    (67976, uint256S("4a63f8a95c07a685d98695e04b69abc8fa20a679f8a9d7a6319d54aa91da9542"))
    (73205, uint256S("8fa5edb5b313496846e33c4de3a123413a2a49af24e555c5ea4a5249efa2e7ee"))
    (78434, uint256S("b33feee4f7a0562b84e224c5c9b476523a7ba733fb74ff643fc78a12b95dd83e"))
    (83663, uint256S("291ee5d94537ae0bb899676ea1802d4d45a1fce2aa24f3a371378542fbb6fccb"))
    (88892, uint256S("8b9ba2f00320bf25b5140fa059ccbb409992f8e2c69d853b7eddbbc23b8fbe58"))
    (94121, uint256S("b4d02356def7ca25d61ca23bfcb205e12a4c28dda04256583a14dc256ea5482b"))
    (99350, uint256S("232c88716e9dc3490b584e316ace1f12aa187cf2739a617f1d39b62b35bbbd69"))
    (104579, uint256S("9dfa0abb0051ebd6ea0e9fade9bfed913f6f1b9125e0a198e70844f515601d29"))
    (109808, uint256S("411f66dc945eb76f9eca95f3fe49aa463d273d3ebef46d5a2404c833384c900d"))
    (115037, uint256S("224a7d8e189514c91e8a1a4f600ffe509925b704264ce35da5a17e258848cc12"))
    (120266, uint256S("2b6f948672fc8a163dc54e13786688af122c2bce1cacdcbac93e5ade16619659"))
    (125495, uint256S("6be4f80cbb571ac7c17751cc85009d2b935ab24a8c3f41990294f92c4e822a2a"))
    (130724, uint256S("af0548401f85f2fe6b007911b1215e7b822407e9780255f5f8992e22332db7f8"))
    (135953, uint256S("c6990ea728a57d56f3ad8806eca850c79ad5a4f3c4afa7c5c569f68056bdbe20"))
    (141182, uint256S("ee541afc16eeb051827019f841e264b180b3b99848910a5962a982ddf9ee58ee"))
    (146411, uint256S("20ebb57f47b2ea6aca4a4a65f085112b24bca6066003825600b8df54e44c8b8c"))
    (151640, uint256S("5d6fd6d52b992858719cb4902c1a06c3d6f0fd72f38ce6b6bf3f52f6f2bed4b3"))
    (156869, uint256S("98dcea3f89e518acb78df7be60841ba561b1af0cda9348d75888e69f4ee75bfb"))
    (162098, uint256S("749418d9216e011ce07ff231bce8caee16c78d7d413d856e5352be53fccb4c46"))
    (167327, uint256S("0e2357d23af86872f295a28386e7dc122f5428876f8f6914f814cefb4d660ef8"))
    (172556, uint256S("36a1058467d2b9837825c53286d4c35d3a06f34665c87a78ead4f5c8db3c211a"))
    (177785, uint256S("152818ae10e404134d5ef0b0057523b3fdc97644f783eada4e96404fff498ebc"))
    (183014, uint256S("32f6948ab9fde503dcfdd505351b4a19960c52a55ca3234a18a715566fd5cfaa"))
    (188243, uint256S("97ceae3f2291daf2de41cf6bdb941176ed9db9b332ed64ee4b756cb018c25b4c"))
    (193472, uint256S("70fe658790fedec321a26afb618580a3aa5613353905519d63046b8e2ec414e0"))
    (198701, uint256S("3c5c7cda2d80ec36643fce1bc729b1fb9100de446d3a5c5f5cd6e82da18635e5"))
    (203930, uint256S("73290c00f86e95ac24049cec6f1a34a009c1a0bb8d14f4e6aba2b1caab874831"))
    (209159, uint256S("42932a33be5b7863a6d77c8667220bf2059b965a38ac65c57accd0c9cf7fda25"))
    (214388, uint256S("f4cb73082c2c73b787d91fbbc496335b57540721b2cc675075ec223e658c181b"))
    (219617, uint256S("1204b1bb4357fbcdcad948e69e0b79473adb22edae15a7119271badfd45e23eb"))
    (224846, uint256S("0b1f8b0d378c699bf1ea379af70f62324b732e0e3c899b60cd1613d31dbce438"))
    (230075, uint256S("832e6d115c851d07c95372207c9d67cf543db81d96969cea1bba8d2b365287ce"))
    (235304, uint256S("a186f36eb249d81bb3ca11ebb8887192d025ad495de78c44889c0741a10c9049"))
    (240533, uint256S("a4f31fb1b31bb52630fda6b5e3ffc94a32a823d5fd1aae628e27096b1b1d8375"))
    (245762, uint256S("6e86b99f8c01bcaed4ac89b955dfb58a86af3d8f95a94614f027ecbf835f377a"))
    (250991, uint256S("c1a1986e05caef8dac4280334fcc0cb6fc27c073d97e04424e12d7d7a03f500e"))
    (256220, uint256S("07635b94a3bad1e5c3a9217f7836b47c580d245d065009be49ddb89c320d9789"))
    (261449, uint256S("f3809ba07d3bebc7d6fccd29113073e26261937a466ac8e7ec981c5a240e05e9"))
    (266678, uint256S("42f4681ec3925fc82a75696b85657a48dcde1877e11c0fe585e91c37578f3676"))
    (271907, uint256S("c0164e469a073b8199a09605acc617eca31a8510dc38aed2e6c74a07ada5c87e"))
    (277136, uint256S("b8e9875b366c2ccf56b676f517e45874adfae6be1ea2630e871591ada33c0498"))
    (282365, uint256S("39cacb24bdf472741bba97030ede540d768a0299dc844591b2a54fd34b05f483"))
    (287594, uint256S("1ef74d512afe3cd8fa36a6ba171af9f431154fbeba2812ff4fb254e75a3d877b"))
    (292823, uint256S("bdb0b62d040311781530e0b7f297425fad2693cdfc852167354a1884c7cfeabf"))
    (298052, uint256S("60c74e8f39c88721eccb43b19a3f5a25dfa31c5f0662167075939f57d6ec42f6"))
    (303281, uint256S("bc809ba8e052c816bb4a7885917bc0457b5064a31fc195ad8641b3dd0c347a77"))
    (308510, uint256S("220e9c654699c40ff2377f2c35651ebba8661dde19ca70d7d949708f542d171e"))
    (313739, uint256S("5e491b7d6b811a38cc44823fc79f96bccab1b04086fe310c56fa0fdae51ecc52"))
    (318968, uint256S("fbd09bd4a71e18ed69f07bbb46308b663084f1063c124842f9fc26840470a49d"))
    (324197, uint256S("6dd6053861359fa3c15f8b101c6240ff81013118db4f8855fc040b6d0c03bf90"))
    (329426, uint256S("f339802b760572829b4542172133f43c6c174d4d63510c7e9c97bfb81cbe5914"))
    (334655, uint256S("22f2a91c79e01371d22d0f38dd8c335243bbe4b109765870ba35ceb2f0a5d042"))
    (339884, uint256S("5673f81170ad774cac294c5b430f47ce0c5134595a8be8265a440b6029353a12"))
    (345113, uint256S("6b8fe8dbd4712ebbaf8ee0b65475bd59f50fb6b771520ac39df173afa243e88d"))
    (350342, uint256S("f13e5026ca938a21999e37ddf2790c4281d70d51337c1d040fe105ac6d665116"))
    (355571, uint256S("30e0bc65b48952fd95d0d3a46f03b04714ef2f7dc3807093dbdb2c3a511c65d0"))
    (360800, uint256S("1bce3b3a7b2176c83e7a37b6f19f91fc08c92c6db997ba4b2cb89011a259d301"))
    (366029, uint256S("f3408a577bc5883b128c212159b29fd6174e6d360893e51ba8cb5a3e0bf835eb"))
    (371258, uint256S("2c83a5e8b47fb20c1440967b6c702e366d3a0ce16b516486d2f17ce41fa608d2"))
    (376487, uint256S("a98635d117ff97bf99c281178145c5829509e7baf7473a50710452533c38588a"))
    (381716, uint256S("11bbeeb65d84b9ffea843af77bbd4bab074ea48d3b633745393fe9b85aa02b8d"))
    (386945, uint256S("437c389082f98b9afdd0618683388eaed6efda1b9b1dcfbe4f862ac3b36f54e3"))
    (392174, uint256S("a4c77e40b7d8b02a14152e3fd71d9eefd1252759eef562728cc2cb2f997b86c6"))
    (397403, uint256S("5bd8920c28be18e03e875bfa739fdddb7d510d5c2f3ead547d992710b9a34e93"))
    (402632, uint256S("8eeadbfd7cd4697e627447dbc77bdfe1da5bddca1f4b41ca588c28cafc284a3d"))
    (407861, uint256S("79437b519c018dce9f136ba5115905babff9027b21a4deb71f73aff1db655619"))
    (413090, uint256S("974868dc24c05f044ff6a75010c6cd2f0a10e67a37fd1959e87ff77050460aa1"))
    (418319, uint256S("194fd34a2eb5bf1694412386bb896c0feaf0ec0949604222372a9c34549fc770"))
    (423548, uint256S("237b323b0606114b06e6f42692cf35861eeb10d0d28151960acd39bd657ecb04"))
    (428777, uint256S("be20d4eb2c63372ae9eaaceb1a4bb15a2ed0e4cd101185798dc697f7bff9a15a"))
    (434006, uint256S("adef84b207cf27e39f8996f76bb9d5b57ddbb847394d5dd5c346a14e9e06f3b0"))
    (439235, uint256S("6e923acabce2f9f87bfba381e2753619ce32ad1d9cae2d2990b0eec3ebaf7623"))
    (444464, uint256S("39e450c942b3f06ad605620e442cf0dd43ef577cf44bb6c34fd878b8516f0419"))
    (449693, uint256S("7fb0d6f78fd1623fc0c75266d19c253df6a22a86e618a50c2153bad46cf9a79d"))
    (454922, uint256S("bab8cac70a9ec9926f064873aeedb9f3c3475c1434813985b28dca1995beefd1"))
    (460151, uint256S("526f614352177cab889f10036cfff1d4701dc47ac028901ce46bbccd43aaa92f"))
    (465384, uint256S("e8c8be02d99bdedec145767a4a6474fcf493e585600b794ff0510e77f628d2a9"))
    (470613, uint256S("1cfda816b9fd63ff72a82fabf8b9c0260f3632846e30eda4fd492b5812caaa77"))
    (475842, uint256S("bc9a75edda8c7b3f7d280b8b27186f27bd0c4661784840a5e3753f8ca2dbe151"))
    (481071, uint256S("93d629a9e91c6d4f39567d128d9be303563307499cb0fabf42ffc6935fab9588"))
    (486300, uint256S("bdb90b9b9247426852e9e380d3c4a4377f5d3bc70fe87c821d0f2cc185aab9a5"))
    (491529, uint256S("fa0feb09a643667a71ffa4d4db440368d3a7d197697f5b31be81ff77f720e992"))
    (496758, uint256S("a09a84ab876ab154be81c703edcb7bf2236c3116ef00e090d4d520b86b66a1e9"))
    (501987, uint256S("15ddb0b2cdfa3a615cfeaf4f5fc232c1445980959b9216b5ed9aa49a168d554e"))
    (507216, uint256S("322d62cded4f002399eec8c26087e61058ae32b066d21b22dcfba6d877f1d2cf"))
    (512445, uint256S("b07377a9173bab72e25a5939439c62f0ae646abab2cc85329aadc0d72f033dc7"))
    (517674, uint256S("e97c01e605aff45b7c85746ff09d154c435e2f77931098e0ca750744823e4782"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626298545, // * UNIX timestamp of last checkpoint block
    1570764,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    4239        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
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

        genesis = CreateGenesisBlock(1567042340, 1911933, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e474f09929213ecad858b8c24002f8146cb459b98e5f665c27eea85f279"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 15 * 150;
        consensus.nStakeMinDepth = 15;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40;
        consensus.nTargetTimespanV2 = 30;
        consensus.nTargetSpacing = 1 * 150;
        consensus.nTargetSpacingV2 = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "02d8e66d000dbe1c014cf7d0a1fe89fec297d78603cb5d0b1a17ec0e6809e9271d";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           //{ "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
        };

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint    = DISABLED;
        consensus.height_last_ZC_WrappedSerials     = DISABLED;
        consensus.height_start_InvalidUTXOsCheck    = DISABLED;
        consensus.height_start_ZC_InvalidSerials    = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck  = DISABLED;
        consensus.height_ZC_RecalcAccumulators      = DISABLED;

        // Zerocoin-related params
        consensus.ZC_Modulus = "c95577b6dce0049b0a20c779af38079355abadde1a1d80c353f6cb697a7ae5a087bad39caa5798478551d0f9d91e626771"
                "6506f32412de1d19d17588765eb9502b85c6a18abdb05791cfd8b734e960281193705eeece210920cc922b3af3ceb178bf12c22eb565d576"
                "7fbf19545639be8953c2c38ffad41f3371e4aac750ac2d7bd614b3faabb453081d5d88fdbb803657a980bc93707e4b14233a2358c97763bf"
                "28f7c933206071477e8b371f229bc9ce7d6ef0ed7163aa5dfe13bc15f7816348b328fa2c1e69d5c88f7b94cee7829d56d1842d77d7bb8692"
                "e9fc7b7db059836500de8d57eb43c345feb58671503b932829112941367996b03871300f25efb5";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1667974340;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 337700;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 337800;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 337900;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 338000;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 338100;
        consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].nActivationHeight        = 292001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 525001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 523001;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight      = 525001;   

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("d5d5436381a5aceff75bae332b4a35f3c24b52194a56518fecf0ad25b03c2a80");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("11374e214fdc781a3ea206ead6cf23291ec3abfda245d58b0e555bc8d9711854");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("154c490fdff3943de777c76cf00072cedc0d2306886570fa78a32b692df3f2c3");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("309bf804c3b8a94b48ef510f0fb932ee837708c42ffe5ee02a520f3daa10f899");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("641f2baba0202043bb559452d494eff8a1c5f3de1d8b8adc4f572b0a3b24f03b");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("c06e7c7d19a30a298ea59f69533d66f68b4f535a9d6ba957f6d738f6ec965281");
		consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].hashActivationBlock     = uint256S("f39105a85aec716241fc717add26b08cc2785748aa4c7cf3c0daec5d578565f6");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd9;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0x3d;
        nDefaultPort = 12341;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.dashdiamond.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30); // D
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83); // a
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 125);  // s
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x45).convert_to_container<std::vector<unsigned char> >();

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
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

        genesis = CreateGenesisBlock(1515616140, 79855, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // dashdiamond starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
		consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 150;
        consensus.nTargetTimespanV2 = 40 * 60;
        consensus.nTargetSpacing = 1 * 150;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
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
        consensus.ZC_TimeStart = 1524711188;        // Thu Apr 25 04:06:18 AM +00 2019
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
		consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight      = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
		consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
		consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x43;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 51434;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back(CDNSSeedData("dashdseeder.4444.tools", "dashdseeder.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd1.4444.tools", "dashd1.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd2.4444.tools", "dashd2.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd3.4444.tools", "dashd3.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd4.4444.tools", "dashd4.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd5.4444.tools", "dashd5.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd6.4444.tools", "dashd6.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd7.4444.tools", "dashd7.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd8.4444.tools", "dashd8.4444.tools", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet dashdiamond addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet dashdiamond script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet dashdiamond BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet dashdiamond BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet dashdiamond BIP44 coin type is '1' (All coin's testnet default)
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

        genesis = CreateGenesisBlock(1515524400, 732084, 0x1effffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000529df5fae941569b6466128042f5f036a8d1d380dd484a06e8a12fb275a3"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // dashdiamond starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;       // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 150;
        consensus.nTargetTimespanV2 = 40 * 60;
        consensus.nTargetSpacing = 1 * 150;
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
        consensus.height_last_ZC_AccumCheckpoint    = DISABLED; //310     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials     = DISABLED; //-1
        consensus.height_start_InvalidUTXOsCheck    = DISABLED; //999999999
        consensus.height_start_ZC_InvalidSerials    = DISABLED; //999999999
        consensus.height_start_ZC_SerialRangeCheck  = DISABLED; //300
        consensus.height_ZC_RecalcAccumulators      = DISABLED; //999999999

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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51436;

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

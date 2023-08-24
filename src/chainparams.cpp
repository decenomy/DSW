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
	// pszTimestamp = Headline: https://cointelegraph.com/news/another-defi-exit-scam-just-made-off-with-20m-in-investor-funds
    const char* pszTimestamp = "COINTELEGRAPH 10/Sep/2020 Another DeFi exit scam just made off with $20M in investor funds";
    const CScript genesisOutputScript = CScript() << ParseHex("0448790ec8f49697a1b0089fd998e932231ba4728c8c3edc2b50b65821e58b441117036ff66337ea5021baf94e29ea83117e885d67018654d0869bbe2eb1d74dd6") << OP_CHECKSIG;
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
    (0, uint256S("00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"))
    (10586, uint256S("2593146d756d02c59a02f8db67c7f266931c1dcf5f81d9987c41bd3b943e3443"))
    (21173, uint256S("f8d6341e2c774ab7db1284ca1f1eb2a57bfefc87c81c5bdd94a69b1351df734f"))
    (31760, uint256S("263f5cb659c3685635236387acbe7e81f9342472f726903d466df35ad9a26647"))
    (42347, uint256S("f1f052bd90f16bffa7cb0e4aa170737f18e2ce55e2c44de18d484f02acbbe481"))
    (52934, uint256S("a72cab3003e2b4955e60204e396a6d7777ecdeba95c3c7dded18c23a02587206"))
    (63521, uint256S("7e5619762b27c0499d8611749bf6cb07db538ec186d780a7b561c4bbc3d22f8b"))
    (74108, uint256S("3c37c3f5afcc81e24a2fb937af3af2e92e1c87f699414252f9d5daae567a4604"))
    (84695, uint256S("891ee042cdb98cfebb2921536eb82405b71a7f252e6edc5948446e7d87acd85f"))
    (95282, uint256S("8ee8d7d5c127099abfbb3bbe2b49cdd1d23ebd921b3a53accf11b86afc6e4643"))
    (105869, uint256S("e00429f853cf814f68ee9e4a2ec6e7a2383eb7a19b7e62024cb2ffbd18a2e33b"))
    (116456, uint256S("2fa079d972df10e50ca472e37d94e017441bb5eb3a8503a2e1099ca8cb94a7de"))
    (127043, uint256S("09fc826480ae8a84262b5796cbf78e561dace60a8ee78060ed742cf5f8914f71"))
    (137630, uint256S("7520670253d218ee3832b1938856c943c8889e4a320b298b9a0d78a8b2243cf4"))
    (148217, uint256S("540309c63274ffe2724b96dc845cbcb56cb187e8949ade67044fa6ab4df0f2ee"))
    (158804, uint256S("8d80fe36320d239230a19ec9d6f2d5ca462ca95f97985e13243f208089b0f9aa"))
    (169391, uint256S("9811a06d4d8dc3b3272695c1f14fc84af8efc0c2606a142c3984dddd754017ee"))
    (179978, uint256S("166191b66a2277caa7b9ad616e45d011cbee20851838f64891cdb1ca41f2b4e8"))
    (190565, uint256S("f6a55387ad9297646486a1e596f942037fbaae094c1bd25c8b6a817d253108ae"))
    (201152, uint256S("4dcdf4f6060a654743c2ebb9fffeda6039d2ed518ac9d639267787ea64204f3d"))
    (211739, uint256S("a72dce384debc5a6329cd72003040a70f805689163fb012cb2586654246e7b5a"))
    (222326, uint256S("e4f92003c89814dac7449e55f9ea63faa522aa4ca46cf42c5201d4a9bd819c1b"))
    (232913, uint256S("3fa47f3cb6556cece55eb451fda9f715501ccd54aa2d2d3f830448b0263111c8"))
    (243500, uint256S("61b811ef538e00ff987fff8141734f915cfae20f9e437c9136eefea9f66c7b38"))
    (254087, uint256S("a65475a18813d10e46086fea833cb74b23a0648f75dec97e5db2bee033a93a76"))
    (264674, uint256S("89e37aa277727d0fcc3587b077050c5b2954dec7d043a7d7967b80cb2dd96fb1"))
    (275261, uint256S("9c0710c82251b49e695c8eb5459099368d5115248a5b595f9f3dc67c06455c37"))
    (285848, uint256S("dde03308ecd6a5c5bd47ddc90a51e5160b733aaa851349610bb5613bc31944e6"))
    (296435, uint256S("ed19249ef2e20bba8610b6e2c29703fa8ce5340d8b887309c7efd0876c75f26b"))
    (307022, uint256S("12f309fdc511ea7e3fc442e44b2a4090a660eaa990b99cf0d7661ffa207791a4"))
    (317609, uint256S("63b89157199e04f0171ddf7c43f0fd0c6123f5bd4e44c883aad3b9f846dcd85b"))
    (328196, uint256S("26a8cdc0c8344967048903c5a833366706872626778c72fbdb2cd9fe6b351dda"))
    (338783, uint256S("68f4ce06d08823d839606c3f7a2ce3b8f14720b58bdd5d1a79829af5a1600516"))
    (349370, uint256S("4f5ece707a4d35ebca73ce755a3835e273d451d2f05fcecfdd657bc24cecb9d2"))
    (359957, uint256S("7b14cdc785265a935adf2acac5169d92ac4eab2f6ada87eda3d2aac3c9dc4c7a"))
    (370544, uint256S("c6ff59702b0369a408dd82f3c4f94b78e9f18e935b0f1a976102f416698668fa"))
    (381131, uint256S("eda66cba2c557b6a5262c24d0ffd012d8af864a20199824ef0ac6eaec052f25a"))
    (391718, uint256S("d64dd3586bf074a56e180e357feccaaf221952a429afda007db399584c4946aa"))
    (402305, uint256S("2cc5a02770a0aa41af1526cb87dc589bb2f9f6c1f61a12a40698da1198e1d7fa"))
    (412892, uint256S("f3a1b0f3c377b3b09832a68427d67dfc1301c3f987316802a8f74e7fee850456"))
    (423479, uint256S("7ee327a06c4ef8859c9c83d8d5ebb4056ce87a50aed0d3f9095770e6c4dcf5da"))
    (434066, uint256S("cb93f86697bd839ed7530aa99a286daa2060334801db77bc1afadfbf638b3c52"))
    (444653, uint256S("428d562af817aa58261fdd7e0f89a56ff159a0a8b4c048765065015028cf608e"))
    (455240, uint256S("c2ec2fe34b183f36c75ccfb2e4dd931138cc7e6867c334679c50594ffebde51b"))
    (465827, uint256S("ad078b4a5c0de670c4857018d962453989be75a65134110e2f05a55c8510ab77"))
    (476414, uint256S("e7658da96a7e974ff56b15baf473467b3e5f77ec2dd80b1333fb3c4a3e985fea"))
    (487001, uint256S("daf2a8af9f65d3878360be7d452d64856ce6f37c9aa4fbeb395d59ef880c706f"))
    (497588, uint256S("6677d9f438fd21d0a93619e5450d0f60388ea3c85e1544e658572903347641cc"))
    (508175, uint256S("18c618cc88f6475973d71edae52d20b27944a39f8c85ad20273e6353b99db2ac"))
    (518762, uint256S("27bd1592c2d9a498078b38efeccd318658f1beb098d91326a018338916a46db1"))
    (529349, uint256S("962c88098156806e1b07fde2633c0bdc4fdfe0b78e40f05ba25049e7d22a8de1"))
    (539936, uint256S("e542fb19c942d43e12f6b1a561c923c2e29603a120fcf2631fe637cc175c1f90"))
    (550523, uint256S("12a135252612647fde841badff20593351d115807ddac23ca44612c991bbdf8d"))
    (561110, uint256S("62b515d4cb9095091b8014da808c943f051c87ae870caa0aea8ddd895414c84b"))
    (571697, uint256S("1fa745b3fb88a5c8e179f040d273288f8ffc7d94fe50686c6bf0c15f7196c07e"))
    (582284, uint256S("a9551a71424cce848b24031bbff8be44cf5638db4a7ebcf361c0a6d729f764da"))
    (592871, uint256S("f506e171ebe5e0e1c6c841872933eb4976b7fa3c8f862ec716e03e4b6f8f525f"))
    (603458, uint256S("9c9c1079607932e74b0b2af0214917ea71fa43c2350863bdbeaac4757f781aa8"))
    (614045, uint256S("653120295d9882d96f67a48c960d990d5ad98a05d1bc6bb758e3185f1c93bd19"))
    (624632, uint256S("11ad92015f94e95265126e441ee1b8fbc8ab8718fe1eea62cc625fe6ba2e8561"))
    (635219, uint256S("ddc8c8f906ca00436ff9f51f05cdbba8120e9ff648e86cb33e000e07cef8790b"))
    (645806, uint256S("9d2504bbe996dd4b03af50a1ef9edecec97051954c3b02e466d4d32e3ab01a8b"))
    (656393, uint256S("7a8a76c8eb3d0be51279937a1aba7f49b24405c99e7bf56706ab61ff19b7b857"))
    (666980, uint256S("2ebce668f513bafe721f62cc5338cf8574f17458e553677eeae0f8b38e9b297c"))
    (677567, uint256S("c8351c9927a1423bdbfead9cdb1e464ba03c72da6f23c8f88d38105030292883"))
    (688154, uint256S("9740544c2c771b5a77ce55645855ebbd31e90edf7fcd019b856ebcdac4ba075d"))
    (698741, uint256S("52d58ab113d008fdac5b52dd9e57e64352aac5e8ba05a5f2953e1ac511648c5d"))
    (709328, uint256S("802c3d9e596d532dd53663da0fd96618101cdad06c789fbae169271436e3fee6"))
    (719915, uint256S("8a6c20d84530a1bd3ec32480537fa3a37fd26c9e2d140048f2c4185b2f52945f"))
    (730502, uint256S("e9341fe07a2a2d7159639371f6131e742640f24be4892e9351867a95b7e6d8ed"))
    (741089, uint256S("144da2f8894719cd9a6a809ae23a8fdea60dffef0d6441978894b8ac42dd1106"))
    (751676, uint256S("21606439edb6abeade85f0649ca0ebe4b74b2928ecc41bbf115b6163e0ddb531"))
    (762263, uint256S("a57b26f14ceb2e6a2a91bf3fedf1189379ee9451e9c6fafcabf21baa81c968ac"))
    (772850, uint256S("0d650f64280ef38528cc8b1391f90656b269d0365f3c439dc5e7adec429f1d2a"))
    (783437, uint256S("46e01e63d41f5f8b827614decd79d9045a0376c0bffa259e0ceacd0128bd2fd8"))
    (794024, uint256S("a7e7827e21e642278d0b3d85a5e77603bfdb0886995457906a0154473f2867a7"))
    (804611, uint256S("139994f6751ac8b89412d33678d310442f42abe3756eb504cfac01b70674efb4"))
    (815198, uint256S("cab98bbbdd9165cd64978bd11d0c805fcbc838507904523f8b4ecaebcd985bd1"))
    (825785, uint256S("fab9e3b27daacfb893e8404cb07c963723f55ec67d79f779b73d227cdcea876d"))
    (836372, uint256S("91f2124251bcc8be92ee4f8b26a2ed895db95d1ec2244f0e20de60b920583928"))
    (846959, uint256S("817b3b9e61725237e0265f1b8d1211ce75baaf0df14544d1a2e0b379b0decfa8"))
    (857546, uint256S("9559d79825310b92e3603c61233f4f1739e38c9e670f726cddc30fa3dedb3662"))
    (868133, uint256S("01b512a0652b36054a4085b89fefe5bb8687f5822b845aff86010731d089b261"))
    (878720, uint256S("303cbb65e08b97e6e0b10986b334cfd95d0a2a9eb9c3c2555e794147e06fa296"))
    (889307, uint256S("5031e527be2d98c6a68e4100060330624fa65b1fc06beb77b2235bd896bceb36"))
    (899894, uint256S("a9ff4976ae0f20c8bd384306f4bbab5c0353ed1949a336a7981a6a038e8bc044"))
    (910481, uint256S("ccf037d5349108c941440d8980eb1ae0a264568d544f68836f2772afe638f479"))
    (921068, uint256S("653f19a9d159dab2925f7be900b3f308af35a55aeb1a4ac73505614d84ffb613"))
    (931655, uint256S("8dfa3f86ed44ce7afeca3f8fda7978889c9c8e7ca8116d6998df37b30f73175f"))
    (942242, uint256S("be5dbb049193468af14bf7b11af8d7310ec96cf1148ac21edc3da44c0e5bf275"))
    (952829, uint256S("8fc0e9571f9dd58cb979af9780859c51e98de3dcded27437d6178031434d9314"))
    (963416, uint256S("390125e25b16e63323d8a74b062958008c2c99e7280a229eb9f9d90f255d8ab2"))
    (974003, uint256S("b1c3ff357c97c8c0502c47d8670403936b3d8debafb2de6a9c5c0bd9eb7e54a9"))
    (984590, uint256S("f84a25506e995f974ff32f1e1b9131190d44646978a4e8f98b2a581d438f9cc4"))
    (995177, uint256S("5e96926de911a23bbf4bc032891993dc19a631d161bec7e138185fb07512c49e"))
    (1005764, uint256S("291f12f1ddb2e8d27735fa1d49e1863887a43a2ac5a312056a15a47ab03936b4"))
    (1016351, uint256S("524c22daa21fb653dd765bd01264982384f96445f720e4b77ce1483e1658eb14"))
    (1026938, uint256S("d44cc2ac2e857cab9b55abb8ce7be9f49b0b2621982b4556c8be63f8f27bbc15"))
    (1037525, uint256S("570e92a6906c2100010a213816f3f55e4032d3818e15699bf72716a6e4ec3605"))
    (1048112, uint256S("886a68499863e2333bf1c8701f82ca3fa4a0fac5c96f49f51e3e760e4116ac64"))
    (1058699, uint256S("9f8feca036c2a415d6b34bfc2801f2d5f82ce366e4c736829a09df38c89a3502"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692835920, // * UNIX timestamp of last checkpoint block
    2267510,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint. 2000 for 10 minutes of bitcoin blockchain (1M block size). With 2M of block size and 1 minute of block time, this field should be around 4000 * 10 * 6 * 24 = 5760000
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x000000313693c8b25165dbdc8498b8c0084fa24ffea6a02765733700fbcf7467"))
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1599766365,
    0,
    2000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"))
;

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1625312841,
    0,
    2000};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         * Salute to old Kyanite code based on DASH code base.
         * Original chain launch was made on 10th of September, 2020 as the pszTimestamp headline.
         * Genesis block creation timestamp (1599766364) is reflecting that day.
         * Original chain consensus.hashGenesisBlock: 0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1
         * Original chain genesis.hashMerkleRoot: 0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71
         * We keep both consensus.hashGenesisBlock and genesis.hashMerkleRoot of the original chain in the new DSW code base.
         */
        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

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
        consensus.strSporkPubKey = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.strSporkPubKeyOld = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "KXBURNXXXXXXXXXXXXXXXXXXXXXXWJmF2X", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("a68286b8dd2d7730ab2025201b38020fa68592010ac3e4bcbeaf066b40533802");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6b369beb95e63b6dab9c5f52e26339aaf5bfdccce0bad968c21267464829c904");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("4278660ffb8d8d12cc070eea2f8390aa84132fef799675a865717e444d5722e1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("2123647f29f91a35aa429913db96e666d7de476f1fc109a8298bf6f291b36584");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("04721c90cd55aa14dbf5cf0b24de60311b37b2deb0e98004b01b2e90c4d3b031");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("8f7c1d65300983dbf2d99c70051d20470f0088275d6bca9a69fbb2b8597585b7");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0xf9;
        nDefaultPort = 7757;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.kyancoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 46); // K
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);  // 7 or X
        // Kyan BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Kyan BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x42).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1599766365; // 2021-02-03T13:51:41+00:00

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

        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1000M KYAN
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 10;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.strSporkPubKeyOld = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "kBURNXXXXXXXXXXXXXXXXXXXXXXXUwNvtS", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
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

        pchMessageStart[0] = 0x6a;
        pchMessageStart[1] = 0x9a;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x9f;
        nDefaultPort = 8757;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.kyancoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 107); // Testnet kyanite addresses start with 'k'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
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

        // uint32_t nGenesisTime = 1625312841; // 2021-02-03T13:51:41+00:00

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x207fffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x207fffff, 1, 1000 * COIN);
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

        genesis = CreateGenesisBlock(1625312841, 1, 0x207fffff, 1, 1000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"));
        assert(genesis.hashMerkleRoot == uint256S("0xa50c4f55f3df2d2ecf33f0248f631ca20935c49dccad9bf2107911d94c5ab0fe"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // kyanite starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1 billion KYAN
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
        consensus.strSporkPubKeyOld = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
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

        pchMessageStart[0] = 0xd6;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x9d;
        nDefaultPort = 9757;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140); // Regtest kyanite addresses start with 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Regtest kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        // Regtest kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.
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

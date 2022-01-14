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
    (7732, uint256S("7593882311894430869c2e213dbae760771869d6498440af665b039a4e44a3cc"))
    (15465, uint256S("8f736ed9bb886fe59f084ddbd0d9d089d854c4b7c062d6c63b848f420d809bc9"))
    (23198, uint256S("2830adc10f6bf75d08c1b2e8e9ea6a9cd81fb31020ef5bcb8af9fff7a525f3f4"))
    (30931, uint256S("18946fb797652972a0600e0db2c0d15344fd52bfedbf138d8775a7cf9a2460fb"))
    (38664, uint256S("46630076f86b55795668234e0201c9dd903c8b6e1116c6ea17db03958a112f46"))
    (46397, uint256S("7deb95db22dbea4a22dda2ce7071810b6b865423dcfe9d13cf41ae7478e3d937"))
    (54130, uint256S("334657474de3a4a55dc2c9ef9b0802f225c14864460dee9d65735680972237a5"))
    (61863, uint256S("d2d1a6cccdb71997aafb73929e1bc6f3682c16e018d7e14c65f5d2290fd7f44c"))
    (69596, uint256S("e5d5d62d7123cc79b6fb09110ce62ab48db13a857b0ee9cfe2ead6ec767c12a3"))
    (77329, uint256S("662c03329ffabecb93bc794bd7854c1176b258d3df484d5f38f2dd72c7d5707a"))
    (85062, uint256S("0862998c03da003ff30c3505d37e7f79940004c13accc713b7aaeed178cd2cc1"))
    (92795, uint256S("63cb4379273373c6abe09d2f21c193cb8dde65b3507039de7b5c0344aebaec42"))
    (100528, uint256S("33eb5609211cdb471b18a786234c97e14e76708cef7e3e1be88c33bacc684900"))
    (108261, uint256S("d21839b267e2201c7cc69c8eaaeb3f906ff8a8a4697324780eca1212e265594a"))
    (115994, uint256S("8698e85ba304abbc4c9fad56e22390673303f8a163c0b1999ed978a14faf1f39"))
    (123727, uint256S("144f1cb5720acfab0d728011cbd05bddcfde12afc7de04c4e2e8db64b5e7330f"))
    (131460, uint256S("ed70964fca95a976322c5778d17453da3a1d9546ccedd160e2bde90d9cc2db19"))
    (139193, uint256S("f8d1b9b260817fceec5c77ff5e50a4cf1ac6aa15d39cd6cb8a46f1f6160402de"))
    (146926, uint256S("0ef6a0f2f3234a0c883e928436530ff44dedfdcd7f171e0b8684d8ce91adcc33"))
    (154659, uint256S("68702e7f102f0eaaf1d048ef5bea0253bd0ecc37074dfaa6ba4380802acfcb7d"))
    (162392, uint256S("b49c05d02f32a96d4878cb6bc311846906cf71c88ae0536e773fc32eaf5ce10c"))
    (170125, uint256S("4a32a61c6fa997e359fa2555a9624f432ebdb44b47d4c29c3fd304de308a51b9"))
    (177858, uint256S("0b20fcf7e225345231ddd24ce3d165db9e645f2fa5f667298fade35aee3d73ed"))
    (185591, uint256S("1a02ae3cdb96444bea1daa21fd8d90bb7c404e3ae269ea97b219af0865efb54f"))
    (193324, uint256S("fec55a98f3ffe1a7482b4af7e75d820c7411ca142cf4cf025880f238bed2ec17"))
    (201057, uint256S("6099c1d73a50e5e6d674740eae9da8c5a7ecdfa44902f6322a6bad5a140c902b"))
    (208790, uint256S("1c75d495bf7c326570c03c4cc684eb9fd0ec37da9b84db533292f5d7e4e9f2a3"))
    (216523, uint256S("08c05d89883ff467b2022f1f3bd7ca19c72026343ce8ac48d6609278d7514251"))
    (224256, uint256S("6a741e85f18cbbb6d5595822a2ca6542f39c9ced100c7313daf4fee04b170859"))
    (231989, uint256S("c496642da6af280e90d12172b3991de63459c22f722a4ec3932524fd2e3802f7"))
    (239722, uint256S("0ba1764d41f35785b282026e14cccc90877666103079b0e9b2a0293257f0593d"))
    (247455, uint256S("07620ba7897444d064c778fc26056c9054c7e91812ec328d789893bd7ec2fb2c"))
    (255188, uint256S("e61f6b75da7a010c68f587827d8cd3feebc09ba0ccc1fbe0bc432de3f4a70ca3"))
    (262921, uint256S("cae39d74ce0650ad925ffffa3b57d8805dc12946fe356b1d804acd9e23451794"))
    (270654, uint256S("48c284319b4c8d23560d72c10bbc1d56c1a47fac64e2366bbd02e3c0c8ca09ef"))
    (278387, uint256S("14ae8ee5e762319237e7203d78489523a97dde1e20a0c49677bc75a708806639"))
    (286120, uint256S("b289fdd92a9935132f29c3c600225b00fc86bd2486b9dc8aec68da89f261883b"))
    (293853, uint256S("59f99015285ba6cbb9fc6b55f2a2dc5d0e94796a392d60243b79a93fc80e43fc"))
    (301586, uint256S("3b4006ae1540294b36798c30b3aa726fb9d6162ad9b4ca699a0e12f365f792e7"))
    (309319, uint256S("1b6f3fbf178ccb4fbe458f372f78134f276a5e87699676827ed4e8a3ddf66574"))
    (317052, uint256S("eda8f386c5be96c742184e9ff4ac1202d0a0f717022602310e59c31725a4ae1f"))
    (324785, uint256S("4b442f22fab8733f9cbb8f107041030a52daa9d31df7072e9b5a30aac2ad0424"))
    (332518, uint256S("284869c3b18f5e479c820a9cf1cd272990aee9cbe930329ccdadf8eff48ee5b8"))
    (340251, uint256S("3e6bc67038b0f88b3d9e3427c394f82e27e01cd6608cd7a68db112b6ac343bad"))
    (347984, uint256S("25686db0ca0da6023c16f79f35458ab4b171e50f98c48587bb342aa6f67d6149"))
    (355717, uint256S("69c6f5962b3a20516dabde3eae08ffe7fb682bd3a220ac453761a749de53aee6"))
    (363450, uint256S("ab7d3161f6e0be8db2721783058ffc45ca2dc481c0ac2e71890a07a7450ab19b"))
    (371183, uint256S("bfb370489b411115cd9e65747f96e6460f5b2844fd2efebc7a088afe25da7f51"))
    (378916, uint256S("0d92a2f183840324b8df214e654ed83204aa7f3e22235430b75edf6517d7f538"))
    (386649, uint256S("1eb7e91362163a4eddfd6919507469218fc86850cd700d6e0f25a875a6804253"))
    (394382, uint256S("8a8b887dcac1921e29affa6e15feba6c9124b0fae011b3db0fff5da826c05638"))
    (402115, uint256S("1f16c3bfed5ff3af56eb32cc0a9e775c103d3476a40d178250c511721e66754b"))
    (409848, uint256S("ceb4686f5568008e18541d26d47111ed54dca2eeee449a028f90f236e102a0c7"))
    (417581, uint256S("2d996d18b33aa9337e07fc7e7144440e3529785ad46b5784cd886d33e893f724"))
    (425314, uint256S("751a3a535a4ce97987faf687f1975f0ef10613abfe70590a1ceec20cb557f386"))
    (433047, uint256S("6fdb86ecc679156d4e245d4acfb1b6f07a5c60ef5ab45bd913c5ee4b62ace745"))
    (440780, uint256S("13aa575f0467228f9049ff693076dd4c3416a502d625631bf2a3c7ee8d555e3c"))
    (448513, uint256S("1e7a9b3b3eb8d13426c75358d47182bfb164963fc795bd30dd269f55924e74e5"))
    (456246, uint256S("6bb69758fa3644c154646525a7cf30f865a3a352331c3a7be6d8b603e8e2308a"))
    (463979, uint256S("006a9b2e15d245a9bb39b0aa3b80e44a8a54eb7b8f4476bafb068072ccad522b"))
    (471712, uint256S("74f88c4deea7554a45fe28bc9aa54d253e49efdfc3c154fb33dc313198098cf6"))
    (479445, uint256S("7d4a6f344e992ea19cb949f464f3ca0fa6d617eb03ed752344eaac09e9324404"))
    (487178, uint256S("79e0d68eb382a45b0e436afab5c20433890957b66174e998d3c29d1794327045"))
    (494911, uint256S("a9cc316189d6d4939e2f3686c8bc9fd68d36986b20f2b8416ee54e3ad88deb36"))
    (502644, uint256S("bf0cd159fd05c2482837f9f55c305272393fed4015799d328155e9c98d72cd58"))
    (510377, uint256S("5fc31c8aa3f89d26fee3732187b335e4cd4ec2ff88204cfb4b3126f3c4fdc553"))
    (518110, uint256S("99daabf576d5f376bd720632688d4f5d0aeff9a5e5f5a17b27a6e9573f07f995"))
    (525843, uint256S("4cb0ea7af2fb238c16fb6a41b152afb8f1244b32069befa14a76350911c51676"))
    (533576, uint256S("4e4d512fe4817a55c3383aa4610c2a4831d6d3e9dc636782325272a21cd92500"))
    (541309, uint256S("1d7214c5e20542c108e5bb1aef5271c8742c5ef0ea907650c8c88977fcd93cf2"))
    (549042, uint256S("fbe790f60cf4102a441172b48743051d1cef5a68d75db01669e229e8d38f3d06"))
    (556775, uint256S("a5ac226042f6e70e88c4f07d6dcadd74c82c52645bd01e552cb341125113f66b"))
    (564508, uint256S("61d27b2fa38e40b4fc325a7f9fb3770315e62c859ddb1a40710d558d1d9b362d"))
    (572241, uint256S("3517d50e1b6bd60c6054a757c292fc5c946cd0e08dcef33a7261690a642ed892"))
    (579974, uint256S("56122f91abe2b68d9a25e52ff3ee41d889fc9c56e8b457fccc30a7114aa2a41b"))
    (587707, uint256S("cba2156a3b45de490110e4ba9fba66004f0856e04e9ad6c52aa2c89a298ac713"))
    (595440, uint256S("f33edf7cc745e0b8c839c18e720e90454585d7784f2f36987b25ed321f21621c"))
    (603173, uint256S("0c5ddf52e096c84c43aba59c03669d3e04bed92aa387faf3902c268fed2dee65"))
    (610906, uint256S("6bd46bafe2e3cf9d7ab2a27c5e32f89217d6986b501ef2d728515a23bd1cc646"))
    (618639, uint256S("bfec8ed8c4f0667859c3279aa69adde13b5c44ecf467d6400091e442f358c88f"))
    (626372, uint256S("60e2299cdef3d14d06fdaf18348c1e18733ab357428b7a49402484a9dd2f9260"))
    (634105, uint256S("64cf293d4d01be70d0fd693e4ce58181f9433deae376d7ae08cb7f6dcaa40750"))
    (641838, uint256S("a1f8e8d5ea9a398dd26150be10f43f2bdfdcae5afbd6c8d154f600005cd846f1"))
    (649571, uint256S("ce1b6915e77dd15c32fdaa4c997e9435afdbfcffca68ea95b1ba3241915e500e"))
    (657304, uint256S("2bef88f2844111ae7fefae8a9aba1f56000c90c682e59f2628d9511780aa15bc"))
    (665037, uint256S("4c3675c9f42b91ff608a33d61a95f63db6a0566c3d87a64420ca1204afc57f93"))
    (672770, uint256S("5fec69612f77934f0aa3fb624bb166113e24e15cbf07adceb024c9ca96f83075"))
    (680503, uint256S("5445f002c1ed3756968b47b5d8bd00f7a63b71999fa1105b437e6e4a1c4637a9"))
    (688236, uint256S("c5ab7eca0bfef12630bb24b5d5b56c1311f39e363f2530930941074014b8724d"))
    (695969, uint256S("553a17d55a085240986271b591db00845a55a75bac75bb99b794d128255392c9"))
    (703702, uint256S("974e0203906d7f0aa7fb74247ad483f56a5f2ea4196fcf788dbc558007fc6c06"))
    (711435, uint256S("8844e3d2a3ba761016f87a4b00a3ef313db3817a8eef509f0a4946972f6dec77"))
    (719168, uint256S("0af43638656e9ccddcefce4cda085fe30734787485ea83a8dd6eab1e478aa8d7"))
    (726901, uint256S("ebb777d3a7be3aa56630b08d523e03b633406d5db5e8ffb69027e1fc7ecb799b"))
    (734634, uint256S("db7c9dce55b76abbb9e4a252f880700d22b2c7b3cbedf4d4407cdc4cd199abff"))
    (742367, uint256S("2d7dc9bcd85a88f50e73b2c657dbf9c467889d1ca9f84ecbaabb2d21ce8825b9"))
    (750100, uint256S("5aa96df88e09b2f02a93f46294c138e788dca321e32a27da58a25a01328f7e67"))
    (757833, uint256S("4de5e802affbdcfe3b6243ed99b4f555ae457f3042abe3fa062b13a4d1861d76"))
    (765566, uint256S("4b7f40fc6e4abfbabcddcd0bd9dbbbe9b046d02f24d849df370d553598242ae6"))
    (773299, uint256S("0375199823a77bcbf7c74d40f41c873a3403ab9e72bf5f7b9c9edc43252519b5"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1642018305, // * UNIX timestamp of last checkpoint block
    2263988,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2812        // * estimated number of transactions per day after checkpoint
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
           { "DBURNXXXXXXXXXXXXXXXXXXXXXXXYnc6B1", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("8686d0f1739d6dfc6eafcefb4c9ad1b56fc256a852d5087593631ccb0866b8f4");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("982267b09fbedbfad523c97f2c73a483dd070b11c00042a1fdb5586e3ab8848d");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("8686d0f1739d6dfc6eafcefb4c9ad1b56fc256a852d5087593631ccb0866b8f4");

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

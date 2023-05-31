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
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
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
    const char* pszTimestamp = "Bitcoin is now worth more than Visa and Mastercard combined, COINTELEGRAPH, 16/03/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("0459d0cd928dbe01d8ce77979ef8c87c1f6ed3ccefc64502ac599a38fde1e7424e8a9a7fe8660055332e693d84ee9702d3ff583e2445e201bff209b7b67b405447") << OP_CHECKSIG;
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
    (0, uint256S("000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"))
    (11328, uint256S("cc232ed8cbfca62be6f64bacd377fefa08390534e18356ea971edeb24d6df57e"))
    (22657, uint256S("630e163d7db554e90abe8e2e578937fba2f969a9d6f3c0ef68e989325e4f1a23"))
    (33986, uint256S("0d2aeefe44689722790866cf552fc770c9ea3baaddd9167fe92a6b11c4201709"))
    (45315, uint256S("c2d73f175d9ce53e03acf1d0c78d527e717b8ea70f6f61c16f30190236c580e4"))
    (56644, uint256S("fa2fc44f0538194087e23dd1ebaf76f3b9d407f8629f3410789ea981d2e30ce6"))
    (67973, uint256S("208ed671c2e621ffa8273e7936ed9d532950c5b9d7476fa4a5683a05949e82e7"))
    (79302, uint256S("320ced1c2f35c3fd76c7302077d79289dfaae4e10f27887e16774c9b263df41d"))
    (90631, uint256S("4c1b255d73455eeb37694be9e1c00662e0e1c70a4f3ad521519485bee9f6c359"))
    (101960, uint256S("d1ab1a0bf3f102d01bfcf0f46cdd866dd792e0aa5455982d01afc7810627de96"))
    (113289, uint256S("fa49c864ae9f30fb9477f9bb44f9e537228603aff82a54e4135e0e37a28aabcd"))
    (124618, uint256S("52ccc00642cee7e469048b19ca9a5295c45be9980fb61b95798f521cd3bd0851"))
    (135947, uint256S("db92fd1413406fc04865e2b37214973dd6de5101c0dad2fbfac9dd14e75e1210"))
    (147276, uint256S("b278e09189606a89ff7c47ca51b3015e0dc9a15e9ba04b7d8094e0eb26ee7ae4"))
    (158605, uint256S("cf438603e967800bb736be16eead53c306d5962caa6e90e03dcda0e36ba7bad5"))
    (169934, uint256S("e1b6f3552a5f17af0e6cbe165d57b4942d31f120fc5ff9fcc77029897ba0d875"))
    (181263, uint256S("f4103664f20c1fc18654bb8c64fe09c9f9451facc74de0aba448434932f1ca0e"))
    (192592, uint256S("8ae19c424eee3a290cd9535758f22a26541460a9b911dec8c4d0808165f50f17"))
    (203921, uint256S("ea90722d3111bea964c73c3d9c0c11fc13b72114f22bf2943b5d3c38a0771f02"))
    (215250, uint256S("53b71633e581b323274a67cffe5a4f41cd3318b4342133fb797e630d8310d5dc"))
    (226579, uint256S("4820b6a12546318d7dfc01fdcecd03527bc534b746255721b756e9439aee6958"))
    (237908, uint256S("bf5c4bb20338270cdd44daac5b065508d28199750f0d5f8ed434aa3ee1835b59"))
    (249237, uint256S("4b9e6729cfe1bafd9e2ceb58e7da7e26dede38f4b8bb1b150757682c5ac05274"))
    (260566, uint256S("1cb048ff6108a862540184ab7a736d53ffff9079c93acd34c6644ef8c26c42a2"))
    (271895, uint256S("bea7d9ff8676389a0df735dcef954af5b226a7030a62f7b822df7b0eb83e9348"))
    (283224, uint256S("46b0ea2f521e238e9d36cd429efe2e96c0fffd1b83b7fd3b0c87b5fb51b8eb12"))
    (294553, uint256S("dc869c31aeb966ea6afd16f19a6456ef778a5a7f57e6707a0ba6ec470420334d"))
    (305882, uint256S("2d0a1ac4cfeee50fb9c72ff65fe0b36a962c8e6b1c9b5e372a1d3c6bda08fa2d"))
    (317211, uint256S("b03d4ee098893564b6b1cf8b805a68e7c49444c1d6efe32d72d9b62f79d786f5"))
    (328540, uint256S("40c55d28a146c1c64611e3f57b96d4c6c6d37c630de0e1e69144cb67aab2d543"))
    (339869, uint256S("9c3637c37176d25847214a1d5fafc3d5ac42f4b586219ecca35fff141b0a41e0"))
    (351198, uint256S("7eb2545fc1ba9baef9897b98ffc11d93f160d115392cc1f371f2a05a3e72885f"))
    (362527, uint256S("eeab36bd4b3180dce5ed890497d36bc4fd92a72c486fa36cedd2c88c242d0cc7"))
    (373856, uint256S("e51357e97de659ac9cc400d42ad274c19a0a6e597ff24f542d22f481500b6bcc"))
    (385185, uint256S("0a92d2e333a6a728fa378ee267430339c440c5bf7f0107fd8e517e33efa815e9"))
    (396514, uint256S("4b1357328622b44d59c3f5b2b7319d85a3fa5a617a7c3c06b0dcc6e18e6f9057"))
    (407843, uint256S("f8c27a720f88ba6519980ada623cd9c5bb9ade168305454040b36ca3761db972"))
    (419172, uint256S("f1c29392cbf1ddb685b1d89b61c77dc0a830af991d65618ee222e0526a421ea4"))
    (430501, uint256S("a1a97e3e9d7b345c05c45e88c12eea5b35669396e2ce8b53af10ffa3146fef7b"))
    (441830, uint256S("859dc94103568ccdbe94a360a41d6575168e87e70b0a5e5b912e3d23e863c7dd"))
    (453159, uint256S("0cc6b5f7e7c33db9693fa4f8f05a8d2090e3f5c8842dc4dd19aebaea758690e9"))
    (464488, uint256S("c603161f8712bd60ec0981bbafca7cbffbe771e4d1ec120f967488a3c2fa2557"))
    (475817, uint256S("9d28d126aeb9c4f7baca92d684967ff078242705770906e59dc79e365f4b1ea5"))
    (487146, uint256S("c7116d009ed337cb38d5d40555a63f524d36882b703f3a6149c5dca4aae0b4cb"))
    (498475, uint256S("cd00b3760ce2dc52483cd0c442cb34274a3bf8e25d4a5e3bb215a73a39579bed"))
    (509804, uint256S("9c3081fb5cc0b9ca8b534129c98f1d5206850647d89e263f57f3af433fd204f6"))
    (521133, uint256S("14cfcc77958701f80e9b359f2f767ae8ae9cd38ebef4d2e18fcde6e11f775fa1"))
    (532462, uint256S("a65ab26324539023f30354367bad7fcab080f8dc9f0c4ef33d271de2803e11a2"))
    (543791, uint256S("93f34e9e30a1a765a06c1af15f656a3a50705c79b741b92a398e7ddd2956ad52"))
    (555120, uint256S("5be7386d36521b9863809b9727abdfc0c6afe16d7a3b0dabb85f2847ad769b33"))
    (566449, uint256S("65aa6fa6c5f457e07ad52f8a23958666206137ae70efc60b81b4807ffb8d7c02"))
    (577778, uint256S("02e8925ea780532cbe4b37bc9c1877473db7d45e8de9caaf21c3f3213fdfb347"))
    (589107, uint256S("0d84facab136554bb466097b920bdaa0f687b82a86c9a0415dcf333bb677ee3b"))
    (600436, uint256S("56843a168205874281ea549ea90b6cef0bc99dbef4eb2b6a76e174165a53c962"))
    (611765, uint256S("a7db2e2f810a5a0446c0f0604b2d09007b6aeeaec7a7c17c50011aba859bc1ad"))
    (623094, uint256S("0ad545720a71aa1312efb97a72e80cc60e001e876a3a0aca5408ef294b927fcc"))
    (634423, uint256S("91b6a9818d8084ccc97831c8df17e5f4b3d87e5d0cb1dd64d69acdea169f7318"))
    (645752, uint256S("53120eb8c3ed37b20f14ad554656ea82fab1862b8426bfec33d6e0ce37007aec"))
    (657081, uint256S("5e0ffb0dca434d22a74b8278993e19e8934603b6f28815d37b49e0e159f6b429"))
    (668410, uint256S("77258985465f78ef332fc328167d2c5dfed0e17ef14d0ed11b0f7f06a10d9def"))
    (679739, uint256S("bb3a2d37862a5906727896871878337c8cf364dd847c6a0a59553c9e0a5a837a"))
    (691068, uint256S("959e0fdcc47b9a7ba32990af62ff0b13795bc7ef9759416398444627c0568712"))
    (702397, uint256S("91da08dd8ee5bf8e688b2447d1f1adbd85d745a780d5a07ef1850e639851b78b"))
    (713726, uint256S("88d89d0ce89235188dbafecfea5f4611ddb6a737c8eae74ff638a09b5b83917b"))
    (725055, uint256S("12fa1830574ab1ad766b12c7b7fa96ef7fd13246e2508d1c3ee4928d098ebf2f"))
    (736384, uint256S("f1027011e2cbaed5cd5bda3496c643c948649caeb4942221e7ae9b0b372dd624"))
    (747713, uint256S("f89bb07cdb8ffeaac2bddc2c187a5514a6ac34376b65ec51d0ed5da7bba103f9"))
    (759042, uint256S("2916894dc9d2d2a3f16da9e59ab85391fc9724973921240355e660164910ae6c"))
    (770371, uint256S("829207d4b59e6b23260b4515d90a8fb8bd69924cb0f14f8555576798b384986d"))
    (781700, uint256S("d8a3a4fd689889adde637ab4a8e0338f1be8f4b92fb4288b4b7dd6bb88764974"))
    (793029, uint256S("f84fd650dbbaa7687f0703c782ecce3607a0aeb9f475983c0e6d9db7f2c91bd3"))
    (804358, uint256S("4e82c279e9a0cfb34defe2322aaf0c4c8ddafc317d43d86ba3d375c0edf6b2ca"))
    (815687, uint256S("950c354debc71a6bb59e9b19c9e492f507ebb68ff678474d247de0572fd78f51"))
    (827016, uint256S("0ce6ecbbbaa9bad7dea0c183f61d68b3e7865324db4ff67c3e652ee1a7e4c93d"))
    (838345, uint256S("8023082db1bb844b2e88640e9179082ddd7aaf4f64af9010cd2f961c9bcfb7b4"))
    (849674, uint256S("f5af2f8e9745152383d71fd753ca1c26053714a7d071e345e3a98489a09e69c1"))
    (861003, uint256S("dc80f87fe81a48c5c7e1be12f665b073bf2f424899ad3bef88b28bd58073ba93"))
    (872332, uint256S("2eac41a17b55b036683eb0a5171bf7d5a85bdb86ea2690f22a8e833d5e43a89c"))
    (883661, uint256S("8e8ea81c4ad92579f68cd395c82004fcd80d1efa08fd9bb539d0ed404ebab6b1"))
    (894990, uint256S("d1785f2d831765ed6095190e3a29cdc16e56956f0214d3879ef8743149f1b109"))
    (906319, uint256S("b34f66b27f7324d7ad26e70e47e54be621a68e24a71364e0fa85eaaa578b5834"))
    (917648, uint256S("532875cc1c0ec831a7067ec11d5c78adc85415e2cfb1c3533ffb325e66076499"))
    (928977, uint256S("2a1154af3f81d750e2d3441b15d8df6ed5f77bf4df684ca00e67b333c5cddb2f"))
    (940306, uint256S("ad48d00fc3e6299a9b966a9944fe02e7a68257d39c04503d1cd691a721a35ad5"))
    (951635, uint256S("f88d47fe5f9085b7ff62e7cb77b7227d8688085bb9b43a29b071b2915c025b73"))
    (962964, uint256S("4a6279136a6f3ab9aaa853a124f756eab57dd389fc3a96709c7842daa96604ec"))
    (974293, uint256S("d6cc78f1b2966059c4c916bfc0f6ee5558e89fab9ee10d94b19ba0e0df4c98cf"))
    (985622, uint256S("e1c0c8bd919476a1707e083944cefe2c5086292e57df94b57219049d580f2844"))
    (996951, uint256S("b5b57bea74b4c64d3374a131dfd9505a2872e1bb544c0cc229c361665f164615"))
    (1008280, uint256S("15eb86f5523214e6a76a0609a79cdd7cdaf57b23eea827c97724b0ff916006f4"))
    (1019609, uint256S("66e600a00f64e6401cbbbcb98c1725f39a39f590b284336f6987c9379b9f9f24"))
    (1030938, uint256S("51e0baa5ead25bb5f3e9e88e623d59fe0fd4fbe532a4ff734cad7f3a4d1fbbac"))
    (1042267, uint256S("3d1db902bb1cba4ca908903b4fac9124107b0ac6fe5d40ccd566b34b61f16939"))
    (1053596, uint256S("1b20ae035cb53d9b457233deee58cc72718328ad585e0ac6dc19d440212429f2"))
    (1064925, uint256S("5748c1091e7ee688aa14e9ac1fb296afbc55d781c532e647a3056a2e801e2e4a"))
    (1076254, uint256S("b2a03a8399b1544f421f14a60ae518303982944f988283889baf2cce6b0d5304"))
    (1087583, uint256S("d7add81a3e52717aa6d758e0183c4f01172b5c8ba64682744a15cc6d2b5bdedc"))
    (1098912, uint256S("d1d85f1df22353e335228f6dd89b341f572164a7aa9aabc0dfacac7e2b2b75ed"))
    (1110241, uint256S("f5396fcddd2479cfada6c4c8de8c75568e2a8840c26c7f21d6147ec6a4fa9ca9"))
    (1121570, uint256S("9d1f18fe0738180bdaedeb0f8ca7333819e2d459c5386ed4c211569f015c76ae"))
    (1132899, uint256S("2015848e9a9683a0a71afe8f6d090c002d1c2a6b04dcee3f9ec1e57b25d1029a"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685549520, // * UNIX timestamp of last checkpoint block
    2424052,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2832        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1533446237,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1533446237,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1615902863, 1765803, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit = ~UINT256_ZERO >> 20;
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "cBURNXXXXXXXXXXXXXXXXXXXXXXXT5p8pX", 0 },
            { "cBurnAddressXXXXXXXXXXXXXXXXVrq7yw", 0 },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 190001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 190001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("d2b726f6c67aa8f9444c918a9ee1a7a3f3e71b6d214d930ee1b486e1ccfc49f5");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("13eee22f4b637ad17bfa5836fb086d4a3985242e68f32d483138bfe9240c8a3e");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("5c592d9ced3bf780c0d9fac0a46a479e4b9b0bcf834d8f6faf93475aa286cf94");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("6ee546e646f1277c4d38944a83212b051531f745c4bfa54bac7633c38c47fe9f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0xe9;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 13333;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptoflow.eu"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87);  // c
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);  // f
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 102);     // i
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x44).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1615902864;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
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

        genesis = CreateGenesisBlock(1615902864, 42773, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c5ee0ad5d40f6b26125819d873afabc0c0d47034c97d7b1dd74511215bb"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 12; // cryptoflow starting difficulty
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
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

        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x16;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x15;
        nDefaultPort = 14333;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptoflow.eu", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptoflow addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptoflow script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptoflow BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP44 coin type is '1' (All coin's testnet default)
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
        // // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1615902865;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 0 * COIN);
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

        // // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1615902865, 506, 0x1fffffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000817f2ab1c84d7ae24a42b8cfe71f401f6c05bce5499b9550128e73606a238"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 2; // starting difficulty
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
        consensus.strSporkPubKey = "04ae5f52611fc9f3dcd3f2db88ad4a9b10ab218389cacd1ed07cc893af6ad2f3e6618090edb54038e5a26d2c6d04db4a6c901a8bf52a72fef484f478519fdf0b02";
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

        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0xa0;
        pchMessageStart[3] = 0x93;
        nDefaultPort = 15333;

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

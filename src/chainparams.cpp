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
    (11256, uint256S("8d433a470bd5d2600f291740fb682c0ee7f117d5c2122a240685d4cba960c3a6"))
    (22513, uint256S("9ccece9a91a6bf5c73bed65e44984b83936b9d5d5d3f1354abd4fa38107685a1"))
    (33770, uint256S("f685991a8b85b941ad0194886bceb1efbd50b18b9dbe445c0b4ee136dab7e1d5"))
    (45027, uint256S("bc4e0e08cee67ea2cc65f219f68bdcde42e2fe686c93fb9021a904dc3d19dddb"))
    (56284, uint256S("8428f67a860eaf3275961c404a146d54e7a8cafc0119630e1cfdf542f63c4c11"))
    (67541, uint256S("0be2f1c19520bc0aa95f87898ded6703f604bc35cfff1fcc07163ef9a58b0c59"))
    (78798, uint256S("fe55d63af7fdd62e75acb009285d9b3810ae18e2f17a8508870ed393974683e6"))
    (90055, uint256S("ee1c8ce93384bc50d8cf5028ef5d6ee991e2e066c4bbb56fc409103360897aa9"))
    (101312, uint256S("47893f44eaa9912e15c88799a66002fafa581bb36764216d596aa886fd1e7ab6"))
    (112569, uint256S("88704c99d6d9f23f708c3effb77b76367d1ac621225a92d63bc2596f452f2cfb"))
    (123826, uint256S("708080c6b0ccefc1aa7a4cf7073f7bf7f9ad57893b8961b10f2f51bb759ff4f8"))
    (135083, uint256S("4569f181bda0c379163dc905ed23ecc0cc0e651c3a33b64df96d598efdb0dfcc"))
    (146340, uint256S("cb6ce989faeb98a139e4536913132d4992d04a0d5f812b6a9f99cb8f0e588852"))
    (157597, uint256S("745b4cf5944acc95ac3e01039d1abe3f0edb05c9221c162f818905af2934c101"))
    (168854, uint256S("247cbfedb8a478af18450217dfbf8a3492321b9efabccea072a90ec705089380"))
    (180111, uint256S("0ec266824bde2e20e66f01be035f290316e8f079387fe7d68349889ce21c9d96"))
    (191368, uint256S("37fe5856f252af7472ff24206605ffbaafdb2c44d7e4ee872dc46cfd65af389f"))
    (202625, uint256S("efafc5d4a1be0f6ad3c90a8ce1228646d39a989dea6157fccfa84054abf8dea5"))
    (213882, uint256S("2194f39687b29c4250f44ced2b2baafbdc78b60287b59f8caffef7ee4635bfd7"))
    (225139, uint256S("e4fb8c601e1e507e82aef2efd765b0b51fcf8d7f17b044d1a37d0f2fa05cfd99"))
    (236396, uint256S("33fb3f05f1ecaa40d7a9217973fdce825443c36f6e933e1fb1ea7820adbaebd8"))
    (247653, uint256S("d47354b06f3ceb268c1b33abdbc8b8689611efe1a88e0aa75ee925b1de2f710c"))
    (258910, uint256S("7ddc2c6e6da13a1190655ae5c157a04d4686553709672b48d3ca96d407778ab3"))
    (270167, uint256S("c3cae474fd751fdb45bc2c34bb303962dd4012c5b5fe1c41337e6bc34abb07d6"))
    (281424, uint256S("c66145143ebfd5753338ded873460970f283fb0c76f3981e8679b03b5782a7e5"))
    (292681, uint256S("6f45d00724697fa60bdee13ce0707575ae1a27fe2a6fa4fcfac667d6efa966d8"))
    (303938, uint256S("f5b95fb2e17efbc9ebc3340b8adc36d4453ebfc50591bb7844afae319efe3a7b"))
    (315195, uint256S("ae9710abd3e5c284b162df77d781df5ce81b65149efc2eabf6a79bc179e00142"))
    (326452, uint256S("86a49d8333f943a2babc501f1102be3f13a822ed7415042a7e8089de50cb683a"))
    (337709, uint256S("898cd3e537d93a21d93daa53ec9e8dd2af2417a558201c0b7e6292173cdddc01"))
    (348966, uint256S("037ee41310432d3f9e378d5f5765ee260b105135631463edc750646a3e3423c5"))
    (360223, uint256S("a29473953ff83b4324d06ef1b7cc0528d86b8b67fe09bf0bd1434e990bdaf783"))
    (371480, uint256S("df8a533c2d57db74fa1cb0f45115cc9ba7468f1d4734ef8124349bd68ec6464e"))
    (382737, uint256S("6ee81149159a3f2fb7fa4d33d740c68fa74deb41ca806eae631eebae525cb476"))
    (393994, uint256S("38b0b990c3a9d74ee6c1bab7d2d78c9b1279efdf9cfd0a70705ed10f5cafd3ad"))
    (405251, uint256S("dedd9c96936cb746dd4205a0e117c465f35747eb58a6042aaea2b28ad3d55dcf"))
    (416508, uint256S("61b925b9b36b7f5b688a4c221e586c0a1dd27218aba355778d7812f72714ff73"))
    (427765, uint256S("ba0525a627b36995d3090f7435ce93c41396c5320ac341d64b26a681acf214ee"))
    (439022, uint256S("cddd00cc3a6984b66313fb7dfdf740b354a10f2f1b9f7696d3385d5e6cf1b6d2"))
    (450279, uint256S("6cc7862ed3899186c71b6232db5fc137891e69888c2d9e457539aab780664390"))
    (461536, uint256S("8eb3b65f9e6193affe3aca2d17b3394dfb226b97f8b19c4780b32757c3f09ae0"))
    (472793, uint256S("55f8e637e50edb322e7c9e4f8db1ea3483fad8e395bb7462a37c3a32073310c1"))
    (484050, uint256S("fe3d2cd865326847c80884260f4d1d3a166c4fae30ba4d6108453d8124a05d86"))
    (495307, uint256S("43cd58591d6d1cc01b8cb53e8efb65a5a1d622f471db3fac5f738c90cadcce76"))
    (506564, uint256S("6246c42baf8532151e1be3f9d5070508ddcf11703f9024fda55908d152b3171d"))
    (517821, uint256S("537864391c4102e45b894deaf1b9bc8f56bfdcb3566c7f687a83d9f22d227e4a"))
    (529078, uint256S("3ec7e0b338d7f887b137d5f45c52d244a86451c675cc35efa2fea270ac9a3f6b"))
    (540335, uint256S("fba99c263ed41decf89cd27ac3ab8114d79e7de0bf2df23f077227c97d4fbd2b"))
    (551592, uint256S("3888795dd964e74b8d6e41f55a5c1ddba78308effbc44e11c48dc4b4b1f0b43e"))
    (562849, uint256S("7482f0fcfe456d1d524a47d265bfe89accda873673eba4f6bd00d40ec2a2b077"))
    (574106, uint256S("569beaaf68a6590f77a1e4e9250316d46b863b3150eac2f67b717b176d2d2f70"))
    (585363, uint256S("4ebda51d8de8eb92b00f8ddf16ae2b54eb3a0e7b04572880db2f21db6b67860b"))
    (596620, uint256S("49771480aaaf1cae18258dd206c1fc84583a1353bbd6c55c6c23e09b4ab89828"))
    (607877, uint256S("9bbae3429feb2505c72b91006450514f72f9a66d9bc106679342a4d8cab12549"))
    (619134, uint256S("09046a4bc2c9816eb2e07850256ad1b14701fdcb561b3153d2e7777b5ab20b31"))
    (630391, uint256S("68f4dbe224d50bbe63e8ca754218580995175f2b602e9ce990bad8dd6ce8e76c"))
    (641648, uint256S("70969a85618b4a405b450ca64a6c2b2e3a0fb2381d05afa697977aca8eb4e768"))
    (652905, uint256S("804d32ff40a62d353cb0be5c8ea4582dd4fbcbd6a48e7fc61e0ffe7f225c7c26"))
    (664162, uint256S("b1190ec068972e3b5ab8b737d822d29fbf1e950652a570c700227fa7f6158795"))
    (675419, uint256S("c35319771d2848b35e001cef5f07d2567869360bb31758d60c20f7403dfd311f"))
    (686676, uint256S("527c3b4396f522fb87e505fe091f985d83053f13645c0f0608e265e188a09f35"))
    (697933, uint256S("6bb049d89d813539c2731ee20686fcae1cdfbaabeb03f4065cb436fe89720b02"))
    (709190, uint256S("392e782d7b171cb9574c482895462dfa5e223171db870d6703752549ead9cb40"))
    (720447, uint256S("74948e7006a0c31aa664d74bb82a50e4080540446c435b830e54d65194053ef2"))
    (731704, uint256S("bac17b72816314b14d55b3babaf2fc34d3094b35573d87ac93c0cdd2fe2bd34b"))
    (742961, uint256S("338cd65f59ecd7ceacf80b20da6920a388868bfa613435c9774d3d53f24c6e1e"))
    (754218, uint256S("c98fd3428c8b2edbcceaeba92b772b0054ff16ea9e96b72421b72e8a7f7b14d3"))
    (765475, uint256S("755a90adf6535cd934b4c16f7bc56082ea4742db35c538f5783b18b583b8fba3"))
    (776732, uint256S("9df16ca589d8a20b09dfd32771219e2ab6c7dfcb2023f4f8125d2c2c88daf755"))
    (787989, uint256S("f2a884472968e95befcfb6ff80584a8da533695bc8eb3db4af247802973c2777"))
    (799246, uint256S("e79a5dba74762aa1c7607e4f53cd9d55705627c1f305884bd4a4cc0d13599b8b"))
    (810503, uint256S("dd6f6e5ecdb326036be22d4a7364d95d4e38ab7bf28190b19634b780b2fd716f"))
    (821760, uint256S("0ac54a69bb4874aa4c4fb5f5d52f0cc0e53692fecd72937fdee3b10271d86e95"))
    (833017, uint256S("093b315726ca03792175e8fbbeae65703a7340de3037f8d4a23f92859dc33c3c"))
    (844274, uint256S("c802c5b6c6607bc59e4965a2110e2a0cbeeb8a8011d4163b6a81136edbabccb1"))
    (855531, uint256S("aee5578ed6224189c4274dcb2f77f37c2b9b5b067b8185bdb2aad9222c1f445d"))
    (866788, uint256S("1f9664fc6f9ab871b7539bdec1e25caca60e3bf81984630a2b64f74c50d77033"))
    (878045, uint256S("12b641425b112ebfa3e390f8861f67355ed00c6b8bf56a341c4b0739e3e65e0d"))
    (889302, uint256S("757b243da6b7935224da531e8d260b85139753b22b050a375de7d3b3d775e692"))
    (900559, uint256S("cf9e5b9aa7a01235e711b72d4796f8a9ed9e1058906df8a9cb9afe50c5f7a8a6"))
    (911816, uint256S("ea0d6389917e53bb9a912bdfa90db3c489744d0131e681fa49887a7b3a2798a8"))
    (923073, uint256S("a30b8fc22a24878aced10c9ad14a85acc62aad778061b5ebf4e80ffac3ffeb39"))
    (934330, uint256S("5008ac02c2310ff314272adfe7b947c7fece2d572c41dcb5f2037a187e070798"))
    (945587, uint256S("12fa2c8e84a7b407dce2b18798979b9bad9b7aee706b32cfcf2273252f78362e"))
    (956844, uint256S("5c30c6b0c1691e9a1ebe87445b1acca67a4cde7dc9ff256cd674125f3203de4e"))
    (968101, uint256S("a09b6ab1b12a3faa5c12068b5ba8bc22bd67559ef3a4e9caf7d4e8accf3873d2"))
    (979358, uint256S("94b4e7d4498bc2d2c23bcb0ce639bf96094655c5e1fc347ab7a2d7393f5f341a"))
    (990615, uint256S("a98e79218960157b2c3b7d6b1c1437f22a9a2f97abdec24614e95e6c65bf5261"))
    (1001872, uint256S("3056586966d285f9e69fc1358421e378c8a0fcc397cde6ad0e318ec173ba2ce7"))
    (1013129, uint256S("25ee768aafc53f68417950e8969ab9659f19a0bab2733d2aea6bb9187abee862"))
    (1024386, uint256S("d483ee2f531550bf48c4b94a9badccf6a62919a178cf139b44a110a10fcf3f08"))
    (1035643, uint256S("34cc511e04b67610024e5752308a088ee7540b3c22ef726f6e25961eecae122c"))
    (1046900, uint256S("6cc9b4984fe3f153d18ae36c4e0ff99689c88cfd9dc4f1e41070f53b0f2c1196"))
    (1058157, uint256S("5ddd3c7f5399a4379716bc733889916d54b0decf6178dd5b872c535d67a7616b"))
    (1069414, uint256S("e0ab09d287df4e3380466ac5258b8206458d1b090716c74d0160668a69d2873e"))
    (1080671, uint256S("36a8100f46cd4ec05aafa52f8d6c55626e7feca715491c4bec0d7e2cfe125017"))
    (1091928, uint256S("ffbbf495fb7e8da584ce503d4b2de3562ff6cae0b5fc9b4e4026ae37a8e6067b"))
    (1103185, uint256S("40255e92802d854289ff53c21b6f389aa3a217ff79f14fd11d96c0d97e0b1b67"))
    (1114442, uint256S("57b1dcc5a97242e2a381209d22917658616a392c84a10561614d5901ab5f9c4f"))
    (1125699, uint256S("74bd792a66cafeda9e943773b4e82d07e7079ac1e2df5cacf0e25fac0c7be973"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685106945, // * UNIX timestamp of last checkpoint block
    2408779,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

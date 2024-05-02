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
    (14982, uint256S("e501a1de6fe88913966edb87e9d1b4e2435ac85d6431d123666e84626bbaac85"))
    (29965, uint256S("965b41df0e3c91c0003aacfbca8916a03745c200ed3277cec8ef1e3f722b5027"))
    (44948, uint256S("2f00caa68de0a16938f11fab2d41e6b9292c1523764b5e5acab830417bcca26e"))
    (59931, uint256S("e804709f7b1d4866ac6525f8719d7434407945f741e8460c87e43ed24e8b07b6"))
    (74914, uint256S("6c67b42a008011e6bc2fe88d489ccb3e1ed29b9a7976ad7d382950c4c543879a"))
    (89897, uint256S("f57da4f8e7a7ac52ea7eae267ca4cfe4d6e2b00ee2cbefc2bfce45abf704ea44"))
    (104880, uint256S("1e4d17744adc877102eb777aaff7413a773e71f00cf0213583d10554cce47d29"))
    (119863, uint256S("b89cfd61bd014b87c608b7fd5a8b088f9c511bc684b34d6ceaa70cadd24d73bf"))
    (134846, uint256S("44fc835a9c28aeddf5c64a338e1fd465ca45b859c02d30b53d745c9b87c81fb2"))
    (149829, uint256S("381c78b29a987569731c72cd51968cf646383985df3911150d0e1f2414d5bb0f"))
    (164812, uint256S("27b9e38da91242e1684f7fa20fda677c142b4e4728a020779d1c2d3bfb5778f3"))
    (179795, uint256S("b401725f02bc0b026919b3c7f4c05d8d97cb85a4d042733f85e971e32666a116"))
    (194778, uint256S("57d53c7b053b8484e67d46674d1c45a94a0b10130a40cdce8c2ee696d9f404d6"))
    (209761, uint256S("871f36ec68cc4c686a29da9632877154369a9f06ad25a455e7169dc4bd059b60"))
    (224744, uint256S("f58e94277aac9355e4157e30ede3c87b177c5d83aaefc016756950fe5471bf31"))
    (239727, uint256S("2788304cafb8f70254695f0199886a80a8e908682ab51c544e84553a146e6177"))
    (254710, uint256S("70944f09d9487e994ecf8f88922938e1bcafb7e151dd15cfc3c70db7d63b08c0"))
    (269693, uint256S("b8431763d1f80d71cf598622950d30e3f7f173cfed72246810498a8d541cc75c"))
    (284676, uint256S("d636e44b930d7b2e1f1685c689b7a5b2702ec0630be32e30e957afd2dd40f562"))
    (299659, uint256S("4eac39d5ed91492b305b0ee6b7ea8d9b91599fe4140dc82393a683110905bdc1"))
    (314642, uint256S("20428f72c0726b19107818870addcaf2a3c1010d80d951585e9ef702720eb462"))
    (329625, uint256S("81aa3e310b1a2e1ac66c762b16e6cbf3bcd2ec33b49e49e52a91b88f03be1eb5"))
    (344608, uint256S("bb1ebf1314fdf3f6ac89c279bfb821a59c5e51b64481d7ff4d7909fb938ef5ff"))
    (359591, uint256S("52f7bc575e119ac58c129ca99dbfb236082447e0ecb5092251b41c51197909f1"))
    (374574, uint256S("3a6af9fbecfb5713c4573bea3be7bbd31b808edd39ab6c4f90e019a17ae5ec9f"))
    (389557, uint256S("bb4d008bb6712effbf3e0968eafbd324f942f46b9a36ddb9f686ea49f2153504"))
    (404540, uint256S("e09ef0e7f90b2c5b0879b200ec2a79dc8a77e27993e9b1656781b8dfdc0fb593"))
    (419523, uint256S("acaa4d251f5c18bd3f38b9cf69896e34022afee929d90878fa31aba39ea1621f"))
    (434506, uint256S("161ab9b0af73372b7cd0f1ed818f632f8d390b199c87693ad0b99e93ae9dc4ba"))
    (449489, uint256S("ddc90e2c9ad8506a8a01f34dfa7245075928cd5fcad92f6c1a4d6aa92ad5ab80"))
    (464472, uint256S("03401a146bd1768894f59e9efea9a05eb0c8be2db3a3134be23c35173d14d9f5"))
    (479455, uint256S("b75f670d8fed8742cb72420d17dcd0ca866bd4c0da17e927cdb16210577209b1"))
    (494438, uint256S("f02fb24f069687c7c69c557da4dbe50b09e7edafd407e68e1c47fdb477e6f654"))
    (509421, uint256S("1e4abc6d34620960328f2f88a25d7e49655ab8048a7d78db0c5956deb8f9bf98"))
    (524404, uint256S("1537c70d5f77cca82c5e65814bf7315b4bf3d6acaadb999d97aa9c9634f1648e"))
    (539387, uint256S("aab2d74f33f203518b6dfcef7b6bfb6c442ed9e2972d36e3bcc967ea86baf309"))
    (554370, uint256S("31f91c6711958e527ea45175c3012d2fdb4cea34fef5f6dc75b2ea1f5504cce1"))
    (569353, uint256S("2f84f2fb6f94b725cd48dd3804967d5b51c5252ff5a29108cf8194ef12c7b212"))
    (584336, uint256S("e5638cfe35785f95386d39582a50736b1617c05ff20b3caa30761583157ee5d1"))
    (599319, uint256S("e4dcc36e019f4bcaccc2766418907fb6591b7d63ce4090e6b02f06df93191896"))
    (614302, uint256S("1b7c5c387bf7ee1f78339d84046cbf416a36432d46b07cb09898ce6cc2bc995c"))
    (629285, uint256S("88f6f91e6863dc71166af8ce5dac9045c3cd0ec6878d288ad65fb8a4552149f0"))
    (644268, uint256S("60156955cb1de323db6c0411b49a7bd7371630a8190660b03f5f6e138c2efa89"))
    (659251, uint256S("cb4ade6201a8a5c015e2910d9a0994b3e9e7ba623de872b62cb18e8529899e31"))
    (674234, uint256S("3167b0130bbca1878c488b76f4adb31525550c2a4789f7b9829e3f8eeabad5f3"))
    (689217, uint256S("2bb190958b983577d55e702c92dd42a2bed02004a40a1efd24e18e7f6afea6e3"))
    (704200, uint256S("6454a8fbf94abfd4b9407f1f9cbfadf34f6be229e74a49c917e04a5ce50cf423"))
    (719183, uint256S("976504277d7a2946510054210193f4280a7e0abdd6a93425cd6a22a215aeb221"))
    (734166, uint256S("0656b7927ab2c1038ada978bcaf0959ac2a231d3ca3c3a1b5a79dec7e6a4f52e"))
    (749149, uint256S("3143f349c3fc5881c3e04c025d3662a8488203f52c7a1bc4e201e563abc81302"))
    (764132, uint256S("0f0cf24393381c0ea15b3fa3cb4c294152b22d0c3032bad3977b64f917987c36"))
    (779115, uint256S("182b001a0e6ff3a660d1c53a6c3ab122358852629961effad3a81080a7c75445"))
    (794098, uint256S("01523ce9d2c9d07de9e034e0efc1af1da5b89ec432906321c735fdbebec6e7ea"))
    (809081, uint256S("28ab4beaf49aea52648efa5aa5d5ea93f9c4669b2a64aaa3b37f2c94350eacdf"))
    (824064, uint256S("c9e671258e38690fc4472aecd0e1a72aaa426820c49a850587de11b68527ae9d"))
    (839047, uint256S("ab7d1f53c4b296c54973c698aaffba2b2be1e14e9b7fcb22f9a2946e6fbadd32"))
    (854030, uint256S("28334b0a421e048f724bf302291a631ee928b2026e41b9dddf7db0f7d7cd7811"))
    (869013, uint256S("1da98f7b17168942148e53d7fbb21fe39eedbf08cd36e11fb49767a0ff70b25f"))
    (883996, uint256S("ee048c451c66f761edb451a5e99c655282c244d51297643a0e665abf929fd1fb"))
    (898979, uint256S("26458f57dda710e7b586ad32209c3f5060a828d20d6bc51c9c75d9602baca4bb"))
    (913962, uint256S("52306b7bb9ee77d648370ffd3a3c5b4da6537a9992fb62fd5126d07edd2f8378"))
    (928945, uint256S("192f4bdc70df37d511184a4f4b967a517f17f82825c5123e51d539f46b93444a"))
    (943928, uint256S("1606f1a35caa9bf01849842b8e90de4e5de8adb0734ea8747b419cb28af5f409"))
    (958911, uint256S("0bb9b4db3b2105c9e1a60c9e8c1397266dfc03bf433fa8d2c974f6f0b57cd508"))
    (973894, uint256S("93e963a1693a3dc0583c2390329cf1317b27b6bd184593c49aa0358a86480bb3"))
    (988877, uint256S("a2c91597202d2e09dcd3e707301dd556b9137cda74d7254736f2457210ae5ff9"))
    (1003860, uint256S("9b132121ef0d5fe882ad70dd2dadf44b0ce86d3bad4059cfcf218a9956966f1f"))
    (1018843, uint256S("b0b9457660e02946929e18f82fc73198808a6ad7e37c95731fc0f7ea8a65e4b0"))
    (1033826, uint256S("821d07ef6d02cf67d7624ea8fd97a1c5ab8bcf4e56d212e16cb56581d579f019"))
    (1048809, uint256S("c756a60cd38e5e2c1576c06781128096adc86a0f0cff4608c210ba6b32e86d3a"))
    (1063792, uint256S("4c9a4c920dfe4964b72ddac21e03163ea291fcbe92146ccc679723ef07e6f262"))
    (1078775, uint256S("b79b4b414af49c25b02e73f7879ca10b03576f81aab397be71ea27e7f5a1ff68"))
    (1093758, uint256S("d17a6b7027494878a9f1c065666f857d84e3b83ffe99bd7e451f03878f6dc3bc"))
    (1108741, uint256S("e91657b97650ebbe150086a4596252e5bbd10c8df1038519f56a934c418fdfc2"))
    (1123724, uint256S("02d7bceb04b713336647ae8026a0697966cd17198cdb9fbf83a709f46575ef3e"))
    (1138707, uint256S("5af2e9a7a3702989be3dccfa44a78260e62387417f1832e324f4ee30b4a49a01"))
    (1153690, uint256S("d3b079d0ca827c1c34049e396504ea7979e477a660cefb725005a644e3921a14"))
    (1168673, uint256S("eee669fa098053bad152f575ef30762885d0d3e6f1ca7df81f157a43de8d37b9"))
    (1183656, uint256S("482104f0b4a1d2d95de00a0e09add049a6cf60230a7fb66f8601b75c26ae895c"))
    (1198639, uint256S("cf5f4e082acc30a96af095dffb77b8f6c891de3b3b4fd947d5f7a8a3dc354b66"))
    (1213622, uint256S("56690a91d659a426fec0bd7acd70fb88395a4556dc14b23ab131a2ac75e27d77"))
    (1228605, uint256S("f3bd8ec5324fe2a6c4688f89e93132b08a4f5a2630953a23e5bb699b3d066e25"))
    (1243588, uint256S("0f9cfd481e7b4abcae67d30757a0ddef3b7599ea2eeaea3a99ebfca1ba9a23fe"))
    (1258571, uint256S("f15755da69380c737242f0409935de78db290f63d348304f9fbf918b07abcce1"))
    (1273554, uint256S("12724b97d7fd98cff90a6f0437b36e62d3bdec2a858c099c8846a8877b502d70"))
    (1288537, uint256S("12cd087b1b4858d204d476a1d127c8038ae96f62f43035001d9c281bbbfe0fb6"))
    (1303520, uint256S("feeb25d189d074ed013883ecbf8c76d9b7e998f132291d8594be42c9a733f73b"))
    (1318503, uint256S("1df99c6711f567dae1b8d2eae14cc96bd454e41859f1254604dff71f728c96f6"))
    (1333486, uint256S("3e269ea4db258d709395aa9ab7f8cf9b723a46c012d28ed73c4d0d7b1a68353b"))
    (1348469, uint256S("6eaefca56485faf86916c75375e98f62080c6f2ef7ef5eb71d661f2a21fad633"))
    (1363452, uint256S("68baac477c90a50d7cf23487f4137939b0b240b8af7e5394dc7fb83f96ed38d0"))
    (1378435, uint256S("083ffada3b982fcb4d522e008ab382892574c2dcbb1836c4e1f1e0ad77863b4a"))
    (1393418, uint256S("fd1d81a332de239cd4cc6633161a891b1ccab4d429f91708ddd3c70092d1779e"))
    (1408401, uint256S("b6af69a451a58e9886ebbbbf91ada26198a58f11708663afc0b5a439020d6689"))
    (1423384, uint256S("17f2ba81e2a0b60d8a03bf7243cb15e3d85a8ee2f77e99cb490ab7f4408bb836"))
    (1438367, uint256S("ab8b49ed5651ac5c84695bc189d0f525cb6885a640504e2c6c5143b0dec2e7f0"))
    (1453350, uint256S("b6048fbddf777532737229911da6d4537e71ef9172bd99854d092909c5f9f78e"))
    (1468333, uint256S("f7e4b841e027ad2e4500fef9081fbe4663a36221224eb5fc72cf4e0ae04cd258"))
    (1483316, uint256S("042e96c8ad09e08102bc82d7d2441b7c35816e476dfa7a82143bec80d6eeb103"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707077535, // * UNIX timestamp of last checkpoint block
    3138948,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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
        consensus.nRewardAdjustmentInterval = 7 * 1440;

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
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("d2b726f6c67aa8f9444c918a9ee1a7a3f3e71b6d214d930ee1b486e1ccfc49f5");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("13eee22f4b637ad17bfa5836fb086d4a3985242e68f32d483138bfe9240c8a3e");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("5c592d9ced3bf780c0d9fac0a46a479e4b9b0bcf834d8f6faf93475aa286cf94");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("6ee546e646f1277c4d38944a83212b051531f745c4bfa54bac7633c38c47fe9f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

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
        consensus.nRewardAdjustmentInterval = 60;

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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 1941;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight           = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight       = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

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

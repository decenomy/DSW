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
    (12466, uint256S("673d76aec8655d9cf129c500022fcbee3a94e382247ba3be6f511c01fa1559fa"))
    (24933, uint256S("621402bca9f21ff4cc36861b94765145636845d997691fb00e5b09f45c039b88"))
    (37400, uint256S("0ff4a81edb78ea1359ca36c31c858e1dd63d2ad7a116ae093290bb21213a9ce9"))
    (49867, uint256S("5bc576d1d2a17642afcfec5433177455f55310f39aebd670f8819aa6cb22924c"))
    (62334, uint256S("4932e2a055318e77a41f0b10f9fc25524c8ea1f378b203bd0a43a12ca0b98259"))
    (74801, uint256S("8f305a2c963ec43ba0378076e5f313fe312ddb1b9afea67dc2f941f3fdbf5bd7"))
    (87268, uint256S("6e8fdad3ce04537ed636654a5ed01d9ec1a5534ceb4d1a91089e9cd297307778"))
    (99735, uint256S("5a5a241d98d40875739feb7a86084c9f7bdc5a1ca6e2aa116e705e8045fbee3e"))
    (112202, uint256S("a5e07446d45643f9e3479de92320e9d4a85d202d8ed985cedaf73a142423f7e9"))
    (124669, uint256S("c7373898b6a105588fa3d83cc2457b17b1ad9c4a2605d2785bd59c791751a604"))
    (137136, uint256S("c3a8d207300670aba0a1a8ac95ef4525b8ddbf8c2c06c0b9a776e6281ff04ac2"))
    (149603, uint256S("bdaa86cc9c4a018ec686dc7c9db1b2f5129eef5fd5e38bc1b4b47b80670a6a3b"))
    (162070, uint256S("2364335537340e544a961c31b60f0d8e8542b103cabc532b89e09ea91169f101"))
    (174537, uint256S("49cf8a6ac28b87482e6871f45a44d1bd93372e661ebff1564e2f1c584e89ddea"))
    (187004, uint256S("50cd238e590574b7bfb42e6dc96027418f5d2d68676d0e78942ccc04de937abd"))
    (199471, uint256S("c9f7132c90fc3080983d90c0eaaa4afdfa49ddbb637f3374d955dab186de73d0"))
    (211938, uint256S("cc32e1dac749b39e8121fe17a9f5cae964826a532f1b2f359f0fe6defdb80878"))
    (224405, uint256S("060a3a23db1adcdcad37003da5d653962f52ccc707fad7fa691ee8607307c8f4"))
    (236872, uint256S("225ae6ebbd63728f95702e6d6f2ef713fc087cd1b2f93f3e8abefbfb047c8035"))
    (249339, uint256S("c36841de1cf1a3c7c6ad218652f26d27802d2a4336835d05a2532b398ce1101f"))
    (261806, uint256S("c3258d1c0756c992f93c1b84aa76dfe364fc704c038fdef9fc0a3ba276b893f1"))
    (274273, uint256S("4441211c73f5a7f0d93997eefb850e009d160ff307633f5a08b0ec3f46b8493c"))
    (286740, uint256S("123f21b3b39a24bca99a38554a4ff536b3a8636895e349bd06043b6d3eb5685b"))
    (299207, uint256S("f25617152d091c3a976e09987250607d52b812d0adb6a962f63656a5dac87587"))
    (311674, uint256S("340d5c0191969d9ea2dd18588ce0375587f60fca8d2db4dbf83931275c36eaef"))
    (324141, uint256S("f02eefdfebbd6601705d9b28be59a5c7c6cc60523a4ec313cd4540fd2ffab06a"))
    (336608, uint256S("3efd7425d778aaf9dff7348098418e5d9763b8b1e932b88645c914d20273c485"))
    (349075, uint256S("5276d110783791d7f8aa8d569c112f6c487f49ebc85f09cd1bbe25a0c2ce4d6f"))
    (361542, uint256S("5b57fb0051bbafb37d1d33d6cfb349eb68e52423c31d634efc102fd1e1a26ae3"))
    (374009, uint256S("32ab635ac19e95787d2bfbfbb80625990265cb64da21e874e77027c102914fee"))
    (386476, uint256S("599e63c834bc93565b0c617046f5d6e25aa8864343f2888d5b691a9f1b351ec3"))
    (398943, uint256S("9d9f137aba0af3a4b07ebf1e428e56c28ac2928ebfc3cf51768f93fba3348bdd"))
    (411410, uint256S("76de159098d30e4175a47c08414bccc4aad86942ceefc8fad0a230d6c68594ff"))
    (423877, uint256S("f5d02602a09da5ffed2359c675e6021c2fdf62c0132c19d2ca39c16f21af82f0"))
    (436344, uint256S("289043d00b5b0af98e93d5651b55622433a3175cbbdfa9ec39f24600a7a0eee1"))
    (448811, uint256S("cb1b22af9a33cc1a5053446afce64f06c18c2db93f6e01d84e0f6532e8761f52"))
    (461278, uint256S("0c8c3ee7f46c2391b263eb8b2ef479818120a61a073f3580804c5be5504dac26"))
    (473745, uint256S("90c5807e145a3978a0bb565f7efa4b12c332fa3ce8d8459d249c4527007a1a39"))
    (486212, uint256S("7a589e6a26c5c01731fce552c9a99d9949d39d95bdac71bf4b6fa7c48d0d086a"))
    (498679, uint256S("adcb558bde95e0d20e9586d684ad81b0c7154781e4090528bb0142da3f80be3e"))
    (511146, uint256S("4584a6d70c367ea3afe945118db944a6db7466371cfaf5ac4855c804a90ffc15"))
    (523613, uint256S("69e2b18ed92ababf68a32a41834676bf92eed0b26c2e2f337c577f0df922b3d7"))
    (536080, uint256S("3e77ee4aece581287fc3fd4929008a2184b18895c823c1f9dea945ba3f19c21a"))
    (548547, uint256S("51e8d460dee188a192666925c24b625adff54c56eae6f38df3c0ca8666414392"))
    (561014, uint256S("1000b2b70446aa42045dbb9af6fd411dc5e61e7bf781047bccb8b51ea1a500cf"))
    (573481, uint256S("21337c272233f5a25176b8fbedfeca58f0fcef18f68e18e268fe68f22dc6e551"))
    (585948, uint256S("2a6bf5c9f916d9f3c576e3f9822096e275feea73626a90b2d21245bc732aa662"))
    (598415, uint256S("b80a16d1fe0176779c984aa10997b8fc072608588454622b5fb23edbbf189902"))
    (610882, uint256S("c695dc563baacb1a299d4888fa6fc98aab3ed3bff57b61f7d90651f92a44f771"))
    (623349, uint256S("76ff6cf423d4f55722cc762890cd95f8d05b626c1a961f9a753dc1d1375af487"))
    (635816, uint256S("ac4c09e8f2af9badc7c893fa20ddbf1ccae9ab45b288589a1527ed2dd27ccf15"))
    (648283, uint256S("5dbfb6d1fb1157da52de476a027740cb710ebc16012ebcca64ba6fe81b853af2"))
    (660750, uint256S("90cb017931ef3d93608746da45844988e85123a76ac83ee4c637a2b426c29d89"))
    (673217, uint256S("00a23c7b9150263406adfde2d3d54dccca0ea07af2246c0387910ed151365f01"))
    (685684, uint256S("08457c020bcab1cd08b7ea9e0433bf1368ac1fedcb82093a14de3c709367971f"))
    (698151, uint256S("b420ff9d4b2769fce5c4be6598ccb704ef183a6b7a7139b73be59eb56faae6c3"))
    (710618, uint256S("ec3d6209a3ebe16f4d4985e7e806d56cb3e5e663d48b2b4d80333dd3fb3794d6"))
    (723085, uint256S("899ca153141caaf80a80939cab207413f5092cabbbfd0de3a0c5462da3959e84"))
    (735552, uint256S("24ce904967068081b35329e0d6e8a8a468fe1819463670ad9e9dbf60829345e0"))
    (748019, uint256S("a1682eb0bb4e02521f3b8ae679ff5f646c45089df065c2c518a0ea22741b19da"))
    (760486, uint256S("272b814ef72e199973e3762527d4ac00637c460c7ca103b7dd3730557627ed07"))
    (772953, uint256S("c58960df476590606d9d6a0c85add774adc4f1b215c77a79abee3b56af3cc442"))
    (785420, uint256S("3d7119896e01d494511c2df61dd5d3a94dfd9d02e194d432ba0ec95daccb01b4"))
    (797887, uint256S("1405dea945c88cd65d130ceac27f79d7c7be1e9457fc5fe01b93b7529f797dcf"))
    (810354, uint256S("5c5c79f6d0bed4f0b32a02b0ed19f6d72835906f1805748dac91be032887710b"))
    (822821, uint256S("42f88792434400a9155d8f52317d1d6c5e3d054024c5e03a84e6ba5768148907"))
    (835288, uint256S("81591eb300fb8c7393870d2167826b22a09074efdda6ba29733564fddbcb381e"))
    (847755, uint256S("c62fc9682efd70aa947c2fdf7e56874a7578f375354b3c27be754beedf2274be"))
    (860222, uint256S("2228a43f0af83eb6faa5c6c31572b8b9be0403b25edb99d849a1388b990c5ce7"))
    (872689, uint256S("3e0935a5cbbf1fef3c24d52eeff8262b6158a41c2cda96510c22f25feac8082a"))
    (885156, uint256S("d1e07dacbfaaa642caf22e0aeb2d68515216ed1ff335d42340e8c649faef687f"))
    (897623, uint256S("cb04211a0f7a9bfe60485827e2c85877a43cff0446a7adbd6d84571e1f446488"))
    (910090, uint256S("66ead40d1ab973ef136c8b1fbb24c91d2be70df55bfe59b9a839e732354029af"))
    (922557, uint256S("171543c34b87e93137caaf567f263b8c4663af1b5535acb9d6926a20d21e2519"))
    (935024, uint256S("a93b5e8eccb355085919c40ac5b33724b4f704eed2cb466e406fb017961d31ce"))
    (947491, uint256S("95e7f86eb5e484e9c0b630c509599e242a666444b25027146b20b5ad8d462f46"))
    (959958, uint256S("5b9433a4343737177ff955e4a25b7ec8d247275448ef8b4372ca4fe72cb0661b"))
    (972425, uint256S("1a2599b9825c465afccf02d3dd7c924c2d9d61e67f91d9536a6e245928a643a5"))
    (984892, uint256S("293ea93408ac8295c9f5075a9dbb9506468b2d518da1019aa3808c67f0b52f49"))
    (997359, uint256S("7856677b337eafce301f24c24db6631acbfc39c1cbb0606f66f88f1af96f6fc4"))
    (1009826, uint256S("a9537dc00b9abf04077343d79f2296305c595dd6e940f926a9d8639bcc3cc5bc"))
    (1022293, uint256S("f39c66e7fad87f8fc0277aaa7e8dbfb476323d1e9e3d21bb1c11799246b84db8"))
    (1034760, uint256S("33644f2470c3936a995c86649b61a1fc81e8443e2856e7f1769ec9b8b6036a4c"))
    (1047227, uint256S("2f847f422a8e75985c9bd1c9e13c67afd2fae6bd29340d96114a125da1373a74"))
    (1059694, uint256S("cb89895ecbe3f4d7f033e8b840a717c5c34a8a809099f06821f0baa256cc2bdf"))
    (1072161, uint256S("95e8805a7430cffd4ff2ed34b6e5e85702ce856a1b76e727aba687817ddc32ed"))
    (1084628, uint256S("f94760f0c2cc3d7287e2c4909021477ef75303d152b2d1f53ad0ac0593e55191"))
    (1097095, uint256S("f8d4001f179ee67495f6cb37dd75d34ac365505fd1d7b68e585a1e2bbdf15e79"))
    (1109562, uint256S("d952094cd20804452b12f0982e4a5068c83d18805fddf9962019d2d6bf7d2a56"))
    (1122029, uint256S("8447c42c57487b3e5f3dc00e72d0f5594e654f6d3ca63c31244ddc00eaeb6a95"))
    (1134496, uint256S("6a94696bac331deb752ab2ecedc9d2bf16fd34fb07c352b7b0b52b77ac89a793"))
    (1146963, uint256S("9e6e8533e9ec4059d997e222814e6c82c2ebedd367e6e93fe77fb73cd1bb71de"))
    (1159430, uint256S("770e20ea43545aa16425f9d89f342166f396e8c3d4378ee5416ef594bf347af4"))
    (1171897, uint256S("ef965ead62e090fcb86b671c0f4302b90f821a0d226ee3497ee5f004062cb557"))
    (1184364, uint256S("1ceba0e3ba05a00e7e6972f0ce8cfec857ef3dbb2f502315a6a25651dd1f91d5"))
    (1196831, uint256S("c8d19ebd404ed30d92db9e9957897f24e10f5a2aa2471fbb0c4a85e1d1bcae30"))
    (1209298, uint256S("0f7a9eef3583db3cacc0dee2a910cdea70a93c18994d435895da6fa80f14f21c"))
    (1221765, uint256S("9cb74039754a16defcebf48a3dc28b044ca64febbfe88236cb8fd3e271e51f95"))
    (1234232, uint256S("6807f19e23fd9fbd5db96e4ca523e8bd698e9ec229ea7dc1b4cd2fe926f49a2d"))
    (1246699, uint256S("ebfffae0cc48cfe2c129bbb900cec718d0692e4e8034409e7bfc2aa3df6cee6a"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692542220, // * UNIX timestamp of last checkpoint block
    2657558,     // * total number of transactions between genesis and last checkpoint
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

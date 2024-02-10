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
    const char* pszTimestamp = "Druckenmiller: Ethereum is 'MySpace before Facebook' while Bitcoin won as 'Google', COINTELEGRAPH, 01/06/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("040f65236f5c763bf979ef7316dfc2edca12b443c3fade71abfebbd931839e8fa775c214fb485003697d28b8fb2408b16114c219584376d283af0ca2fb38026fec") << OP_CHECKSIG;
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
    (0, uint256S("00000fbe4cbb6044f6156fa4f4396521b1d28d01307aadb0738d26a88853078d"))
    (13830, uint256S("e06ef715134e9859ae2bfb433cb57b51bd631727d2aa8a39cf6ec401f89ff8d8"))
    (27661, uint256S("b3881be166edcaf7f223d788773f436d706834acc340951db961795928580fa4"))
    (41492, uint256S("ff1a104363c4cc721fc9ac96310ac18051dc14964f6583a0b8e1cdafaa9711dd"))
    (55323, uint256S("6e07897415c5dea731c4fc0dcfb33df9c079c630fe78f18bf5e12243be0a08b1"))
    (69154, uint256S("8434e67e8b11df13f6f00fa783e3d5f1f1dde1bd5e0b3f42f233d67c4910e3be"))
    (82985, uint256S("cfedcb86e254dd5e8a6feddcdde5acfed04c4f8322eca0cfa4d4ee7857a2e2e0"))
    (96816, uint256S("2b0982c6fc19e62f3e6bec44097dd92a4f51c83408f1b162ab98914c790702b6"))
    (110647, uint256S("34be2a5d85cfa2506fcf7afc8aad3fb5800ce415e7a1932ce59aa2fd9735a3e5"))
    (124478, uint256S("5b3e329a8a1f8650fca716eb5d6f568d05a6529bf0d1756173e795106afc799c"))
    (138309, uint256S("843d787569a4353c1559cc26e0e251b263a380baaccb7bddcc9a4a308d8f986e"))
    (152140, uint256S("fc46dbf77a66edb082f5f49e32aca9eff6b44c901c51f3b6e9cee7479940a967"))
    (165971, uint256S("8ea1444a5348b6532a5e40eef3c45ef1cad7b0310be7490e5b8ec9bb4e59c718"))
    (179802, uint256S("20b0c2c9b44edbda1e46f418d7bc8ed1f0bbbf97619643aecb8d109428158990"))
    (193633, uint256S("d97bf17fac7c5e5b27f6afdda721e23f0d03c32e3e5a4e38eb5315869a05cc82"))
    (207464, uint256S("22913a073f23aa5e1b33b5d0a31144069fae8ef93baab867303461f6faef6690"))
    (221295, uint256S("3a777be83388ab634d9994b93fdb7eb26c7a0247a39f52b597734ce12d9d25a9"))
    (235126, uint256S("fcc329e76d23e1f040a88605f1cc9ea8b063faa651af8488f37ebad2281b88ec"))
    (248957, uint256S("f2c513b5224c8fb3fc0711518ea8c933573f826c9260bb4190d23650fb4d769b"))
    (262788, uint256S("0e462a99f425d0ef312129887f63f6a3d1f29898b59b2092cf2bafdcab83d1a1"))
    (276619, uint256S("782005d172ace598eff3c65a87328a2f075c81be00925e97f9ff74c40f71a1e4"))
    (290450, uint256S("d3e4806c4bd28f3f63f1eb3ca9a03ea5b6d1630c6676468b69ae133fc0dd424c"))
    (304281, uint256S("53470d26f77d58d4a98d00a59ea49151b1df4730e8e37a704e422393cf8e582f"))
    (318112, uint256S("10123b5e4c7a8376791f84ce64742f8bcca35826c0f19ec663eb3047ef7cabbd"))
    (331943, uint256S("976ce2c59c39a05c7b35fa00b1a786ce032fed2536eb4e588563009f26cf605a"))
    (345774, uint256S("56772a964a5d8b60927956912e349ce0f1da1ee3eefcd73665a02722a6dc1a4f"))
    (359605, uint256S("c2e92d346435f64592042aa3151e7281d769cf22c7bba1f21f5a81493cf56edf"))
    (373436, uint256S("2508316c383df70b3e4c50d80137bf56e5ea76f769a42b94cd3bdc0e0cd7670f"))
    (387267, uint256S("bd9776a65f31d12bdee0804a1c3485722b0ab777cba8f9dbca35c863d94e7685"))
    (401098, uint256S("d503045b16420c8907c2ea0b0f25f09a45f8fc291ba1f72e6b659b182168793a"))
    (414929, uint256S("430b6c620fbf3874b8f58613e30fba92433e90bf3deb350f26d495bd02f18499"))
    (428760, uint256S("007e53a8fac5ca92eeec3530367ea9edde3428c45b52fcf27ff4a62642036456"))
    (442591, uint256S("430779b80fb5bcdf8d3d6172a7957761232d86401940c4b858ef7dd127d830b7"))
    (456422, uint256S("1bf222f67e327b94b1e4ed83a1780833cf7e89941743e9bba4017fe5dfeacd3c"))
    (470253, uint256S("9cea09b866240a2a2c6bf8a46f974656d972bc4851f7fb4946f5a0cf7d1a06d3"))
    (484084, uint256S("1a141feab504532dfc1b1bb3dae9b220ad3d9e2c73db4572aa4c3bdf35465d2d"))
    (497915, uint256S("b0adb0e55d2dd5b39b2a06fc225551651c51c7697b6444a44044c7869ed530b8"))
    (511746, uint256S("728123fb3fdc299dd2ec2f10efba057651f0046a1ea33dc1019edd746628c46b"))
    (525577, uint256S("e116e64b0f90b5f8aa8bc88fa128c147ef35344746489113c20bd676ddcce0ed"))
    (539408, uint256S("49da8c1d7c011bf56d3d00e2fd9af996f1523daa8e1d4b241cc8828acc9b0194"))
    (553239, uint256S("5797016cdc3364b7185a69ec0ffd15b086be5d35b15a84dec2d03e513f0c8610"))
    (567070, uint256S("8c56a7358270dbd675e61dbab2aa8285efdcfe082840a5043e95e0d47e78ee3c"))
    (580901, uint256S("6e9e3590e9fed04232fc3d78f3712ae16f23c5fc4169040eac6162cdc673f104"))
    (594732, uint256S("35d9b55187b43154a5ccc31d2ab2c0d3053079fc43ae3fc0f89b85fc704f7bef"))
    (608563, uint256S("10614a9837cd5b2faad05a7d43861ad760f14a8f2779230928703f4deeabe309"))
    (622394, uint256S("5f9875a1c2d3d4420e2e3a16b6f2eb2e5a2a7d30f9bcc08804ab5f41696fa197"))
    (636225, uint256S("d1181d5c03a0b4fb630a045bc6e0aae25b9fe5acf5d6d6fa8e2636947bb0021b"))
    (650056, uint256S("c0865dee3d10f7055f0718f82ebc520edcf9b21c816af992e82e8dc98ef3d8e2"))
    (663887, uint256S("a8b19bb8426b9f2513c4e2dc6690b4340e2d3e05bef003b351b73ef8657db3f9"))
    (677718, uint256S("a59fd8ddad3366d507fc7acd7ad89d9aaa8629f76969fe4f1c1cc310d7095331"))
    (691549, uint256S("c4901349134328531442893d40717b17449cb179f9a02e0e5ae82a03f53d15c5"))
    (705380, uint256S("8f3c2a2f6749d4273403ea0d45019a6b6cb8a57e9e42a1b6b53ec74b85317faa"))
    (719211, uint256S("d71d5beef4a8344f42256c580aaf6cd1e45d2f10d77cae74e4f7c35a28d022e2"))
    (733042, uint256S("1ae5429d45879b13cedfd0a4fbdef55484447f20ec2098c5cf4e68c5ad7844ec"))
    (746873, uint256S("134f9922f50578833b282b2f8e93e88325fb2c7eba0fdf2507953101d397ece0"))
    (760704, uint256S("3e68b6b019ffe1042f7709781b42f9d29ad3e2678cdb02a66562e31b932968bd"))
    (774535, uint256S("b86c228b6b05576d2d9b86f6d2279388c2f65ea6293c35bf3eb621bec44dc4fe"))
    (788366, uint256S("eb23d75ccda43b51afaa3933a7e3d36ae3b5a6455f2619592a5dfdc76843fd61"))
    (802197, uint256S("d165accb1bf8699e141bdaffed0dc69c1a8b9e2a12f191a70d2f22bd396b628b"))
    (816028, uint256S("5fbb1639cea17ce6325bb95295a657dfcd1171a23fd0bbab7112aff0e8d59d91"))
    (829859, uint256S("b3fac3c59dd226aee6db86e08f6a159a6f3cbc83a53bcc3b4a47f9acbe71310d"))
    (843690, uint256S("5b3c7b600d5ad72905ec4dd19ad050bde550117d4ee523a9510fcfd61b6b5f2d"))
    (857521, uint256S("a03c6cfb421a4ee50020f46ebdfcae5c90481768f0f2fe522007f76e1ee3d699"))
    (871352, uint256S("af189054b98c195727c4f38271be4b4c5367c4699fc359734d088bafba39e58c"))
    (885183, uint256S("6195e4f63dcd20206ce5f676c6d4a384b58848987025bd8bd888bb3719c89ad3"))
    (899014, uint256S("3be9be62966f6d69f4299f26ea3ac8bb295f7b328422171f3526dd202f54a245"))
    (912845, uint256S("6365e507bc6d90d5cec0e10bc2c3a9e55f8de0f0cf8c72437acfd2586aa42ab5"))
    (926676, uint256S("dd5edd3b739163527441600e1543e785e668dac1eae7d76ae4fb16421cfdbcdb"))
    (940507, uint256S("6f3775a95f935083990fa5dfec856c639c50470abc50c9fb0484a0e8c721a557"))
    (954338, uint256S("33afad3bef7e07557ec724510cd8570c845f0a74d20c42b105027c10efd3744d"))
    (968169, uint256S("73b1d3f2e0ad4fab65d77b0f4d1bb2a404651e3432aa29fbba30b531f9df18e9"))
    (982000, uint256S("62eb2bb78eddbcfcab147d618db337972472aa613a0d14457e1d5be920ca09b1"))
    (995831, uint256S("1f3d9fbbb201aa53df91abcbaea968173ffc524ccc60d1bda972765e4ff719ad"))
    (1009662, uint256S("85fe34eb1c80ee95d65f9bd7c9f39090948963169b908083504a37ec5d939cd7"))
    (1023493, uint256S("3d30eb4d2f2f15243ecd68df25d2248aedae8692c8fe343ddfb80dc7200ec13b"))
    (1037324, uint256S("38691fda5c09ea54451549fda30b609a3d63ea0c0230929e12e0965105fc8aa3"))
    (1051155, uint256S("f3c8c15c76be9f12b283096583049305b632111f242507e32662eb0c274d2aeb"))
    (1064986, uint256S("499fdb7de42019a55abee17bd83160ce0947945f02f55a0678cfbdf031a1815f"))
    (1078817, uint256S("f1a33fbb8874c8aff01e92a2eb9e54ed16de2eddc548325593bfa4a8c422afc6"))
    (1092648, uint256S("10e06fff6bd03d84a216c7d0641d3dce6b3d7801f07ab924e0f212cafe09d894"))
    (1106479, uint256S("2e141d61be2183ff39d63e16f1531a5b52c0438f93a07de5da53c9324ca68b49"))
    (1120310, uint256S("a4d70d51dc36a1c3c522f84ce963a254a0c3e402c188a0f5af3dece91f8a9caa"))
    (1134141, uint256S("281899fff44f851944bb9511de3246e9ba3640bfd0b54b311507a49aaf8d895d"))
    (1147972, uint256S("eddc226a95ccffcb1220d6ac40f06ef50b4be080d7d1a2089cfda7ddf4979b28"))
    (1161803, uint256S("dbc2279ad6bbb8d28d12a775c68649e07c806b5c8fb5b8c731e7a4b9bd75cfa8"))
    (1175634, uint256S("7b9ee8e3559e98d687dc531e8d4f39492e81badcc4a934964c9b51cfcef81669"))
    (1189465, uint256S("c582779ffa07d40a8ae2f12bc057e75abf94ef23a77ddea6be99d177cf40760b"))
    (1203296, uint256S("eb2f8967b5bf8118e62d5367686a7cb75ca5dd013017f48f2eefbb246b47ca97"))
    (1217127, uint256S("0ce3f159ee3c52c0ed5b26cbadf261944724dfc24b1f6f1b88a68f06b097869a"))
    (1230958, uint256S("47286b992b3fd0baf0316310ef9315b3388114cad209eacc924511a91a390e04"))
    (1244789, uint256S("a46ce966eaf53f3a50b1c59245cce5f476eb6ee411708dd9061809d3e912a18d"))
    (1258620, uint256S("1c6c64af93b847ca1162de60b9c6143ba191ee76df078124ee3f526d26511f94"))
    (1272451, uint256S("9bcad47dd45b6f66a80e3ce0764eaa7f5f030176a5ab417b0856df7e4270243f"))
    (1286282, uint256S("c5d77d476873ebf40fb2b9f84fb152c66a1eb19e4de1364ee1d77d5f93d5abae"))
    (1300113, uint256S("f0ef63f72ec955481de16e4e6046689c8116321f28c0f17123f442b373c7dd0e"))
    (1313944, uint256S("fa8625297fffeb37d9739f66570d2fc9b52a7cab2e7715b34f9882604c85c9bf"))
    (1327775, uint256S("f94cf5c26bc3ed1cfa29e975de0aa8f5961639182bb5924ce77cc494ce463c8e"))
    (1341606, uint256S("3075efc74aa108e260ddf9dd8e9aafec83c3b0fc9114fc5c4171f38bf57930c9"))
    (1355437, uint256S("557d537c24c04bfbe1dc3f157528aa7ddd7ca90e58d5e00d7a3ac5a82fe17601"))
    (1369268, uint256S("af51014e5fd68c27fb0cce82ff327f88f7d45fdb236f73bde5471a389d3ae3ca"))


;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1706725275, // * UNIX timestamp of last checkpoint block
    3011613,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

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

        genesis = CreateGenesisBlock(1622547076, 269467, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000fbe4cbb6044f6156fa4f4396521b1d28d01307aadb0738d26a88853078d"));
        assert(genesis.hashMerkleRoot == uint256S("0x83046e5bd611dcf527e4b74c0ff8050042a58902c01b39a3306d31cec7c2c684"));

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
        consensus.strSporkPubKey = "020f65236f5c763bf979ef7316dfc2edca12b443c3fade71abfebbd931839e8fa7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "MXXXXXXXXXXXXXXXXXXXXXXXXXXXV9svHx", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 60001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1c18b394b406bc240073df567948a63b454b9e5412f71fbf37fb28e331d0c443");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("3acfdfaa6c021981acab0d79a461177c60e52a083be4ff1e193125a2d967c37b");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("3acfdfaa6c021981acab0d79a461177c60e52a083be4ff1e193125a2d967c37b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("dcf134c176a12efb445ee51c5c27f0855621fe5ac1ec1b6a50cc0ebecdd08c1a");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("172977bf61697a0a194fad26f6396bdacdd043521f2754efde6b004d797da148");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("636df5fbf99434e97d8f92e83188c82221e546fd55dd384682dbbb1c785964e1");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("5fb2b7a4d9d4fecca2b189c1a169b8709bea66a8d3bb60e95a10fcd50a246821");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("109e67344bf699384c934e58646a5f97061d2a3a9e23cefdfba8b75dd0a2004d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x22;
        nDefaultPort = __PORT_MAINNET__;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.monkcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 51); // M
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 53);  // N
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4A).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // monk starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet monk addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet monk script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet monk BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet monk BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet monk BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // monk starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_REGTEST__;

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

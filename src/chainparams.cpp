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
    const char* pszTimestamp = "China to socially blacklist Bitcoin miners in Inner Mongolia region. COINTELEGRAPH, 2021/05/26";
    const CScript genesisOutputScript = CScript() << ParseHex("04cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda03241a96752373dd49edef35f384368993d65afab7214bb870bd95be32606c477b7c") << OP_CHECKSIG;
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
    (0, uint256S("00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"))
    (13840, uint256S("af9434ba33f589801d0c68fccb0381b38629e0827dda5b737853ee2870b2e4a9"))
    (27681, uint256S("086ae56e29f926b51b62f8987538f68993c2b99403de6b4b89f49904f201f8f2"))
    (41522, uint256S("131ad38da49740697ecbe6a2e4bc914e7e68752d6eada76bc268820b52070bdf"))
    (55363, uint256S("36235ef7cfc123b4ed215f8f3a080d307302b9a2489a9095868c3984302008e8"))
    (69204, uint256S("c41e48646fbf974d1916e160d063229d2ec43832d97d914c54905b78fdeaebbd"))
    (83045, uint256S("74698ebc849c35fdf824accccf3a96ea7f0ec0f19720a3a6d35b4c8fef9755b2"))
    (96886, uint256S("755125546f0722c5909a40b02ff81dd331dcf7db01c99655cb04f19bbd7c7496"))
    (110727, uint256S("9c6bc4cd13eecfb62bf8546b390fe3c5f13ffaa08f7a936f4026a5a3c6942088"))
    (124568, uint256S("e8caf875bd70cdbb08096e17dc3ce1cfa5c339b8820dfe13b3ef442b217c617b"))
    (138409, uint256S("97e1cbcccb9e0b1168305d4777564e0b5fe09812d2321029ef513d82a6c496b2"))
    (152250, uint256S("c60dd36d0caeda0aea236cdfb975fd0324daa910e35549f7bd0182580c509510"))
    (166091, uint256S("10f554b8ca194d3af0456fdb7216dea76e452168e76eab3af22bdb87e6688c71"))
    (179932, uint256S("478e3c8a31847eaf02f5457131b89f43b75407be1af85b0a6e449e78cad41091"))
    (193773, uint256S("083d49cb348dde160bcaf955d89ffa53ede9677ee30934acf27dd1d1b48222b7"))
    (207614, uint256S("1a2f60e450f630242f0da5e36a781a7151900aa430691b9d93243ca40a32d4c7"))
    (221455, uint256S("49e9ce5dda0c5ef888b652bf5ae01b817e9dbe3c286c65ff4b83fd24b5b5c526"))
    (235296, uint256S("a256a7e569d84fc6316f2b73790057ca3b1b5d56d3668e3be622404cb45e06ea"))
    (249137, uint256S("a8a3c6e3ecde1febcbd543233c37509808e83886e2862ed11f6f549d0dbe1386"))
    (262978, uint256S("b29a95b90feb451319dcc4a0085933194c3d54fdd451620780da5756ff8279cb"))
    (276819, uint256S("06ab58be4f5f0ecf0520ebec80823f52f27ce846484077a14d23a0285ddeaae6"))
    (290660, uint256S("99ea428e4a5f0a9369e243863a08cb55744d290297ec5fadf484a49a24d41eb5"))
    (304501, uint256S("d30aea8d43e976934390751bd0bfa59b49bae3bb1084b57eb5da9e4f7c90d600"))
    (318342, uint256S("323faffb14835ab08b39eb92a369622c984dd4d167ef1b417505fbe128efa155"))
    (332183, uint256S("31f8e332998ab427a557fbeee094a00950b969733580c3ab6cdfc4c6716e9f37"))
    (346024, uint256S("9afe0b60e6eb6d19f11d2c95e68864e8003fff778c8390f5765d06fdf116f245"))
    (359865, uint256S("54e41f6638b6826221e964552b111f62bb17117e0d128ee262a105bbcc42a315"))
    (373706, uint256S("aad770e988a37ad424d071217cda85c1272dafe20c9d666d4f69c41b2768d1aa"))
    (387547, uint256S("f732af09dd3d003831a27d69c82fab85835063ea5a4a0627fea52cb29f8a9521"))
    (401388, uint256S("b8c73be85190477cb21cfe312e6cfd11c78279212f5c7b6a758659d95b5c75da"))
    (415229, uint256S("642780cadd33ee444b4436f72f128b014816f0688689c335ba15109a96a6fe4d"))
    (429070, uint256S("e68a6a9c8f7250bc0e1c7d060bac6252942830517886957456f7bc5529e679ec"))
    (442911, uint256S("fd7a9585b71394cb1cb3b10ce46a44e927a0e5edd5ef0ed6be337fa4956e632a"))
    (456752, uint256S("9b18ffce64c7b2b0ff8cf5ffdff466bdf731e416dfbebed93e4c8dd5671c6908"))
    (470593, uint256S("3a5f79adb5e86f16d09e25005c1b72b14780c52d9386b8f4ded3a2dacdb8c650"))
    (484434, uint256S("952826c14a770fb89d004a9c8717b7238222871a8d5be9b0cf801177051f4050"))
    (498275, uint256S("5e537c97d8e59faa0b90af81d99a88a3ed2927a412c45987b5056ba4c6ae3e94"))
    (512116, uint256S("99a162a644ba71a04631f71cef2de633d96718574ed74428bc4e06416690161b"))
    (525957, uint256S("23f501e9cb056030fd8408eba8d39d08b19245de152a2d0690ab0210e63a224d"))
    (539798, uint256S("61fd84f92e56961f4b048fb3613b313e076d1283874d9e0b428b21dbf748176b"))
    (553639, uint256S("807ba46d9004cff6e5dcee155eeb9447c69c8c4f3a46d637e47e3ea822b99179"))
    (567480, uint256S("8c78b61133e65e11f71753b0772859c622261b1eb6413b762c977496c922f95d"))
    (581321, uint256S("a9d3384efc286e28078de95856d171a228c934d0b8f104c5f42fc06a90960a86"))
    (595162, uint256S("f7d8a6ba75e8fa08ea2e26470103bf270af2e156ae45df6ba7d39b0f34a97a0b"))
    (609003, uint256S("eca234df1ff8ec89856ef568c0e36c00ad491eecced531d3b51efb691503b188"))
    (622844, uint256S("a58289f9d8101dfef070d697a247ef0f01481a7638ff2645f208b6a9085176f1"))
    (636685, uint256S("992fc35693142bea38ef4df02502618ffdddade09cb06614024e3d20d0fdd653"))
    (650526, uint256S("4404ffcbf192075f42b72b0f280ec4f4a03fc55dae9a31b2a007b62b6b1c9c02"))
    (664367, uint256S("5cb709c9be0ff0126e2f503f9140cd43afedcfb638062e7e026c779ca81b870f"))
    (678208, uint256S("c1fdacc20f4c4960b6622412132a36d21c05c4e69b94e2c02783da51a5ddee1d"))
    (692049, uint256S("636ea07a156767b6e88ed3e3ec102c69e9740d38c84688a494818339f611d4e4"))
    (705890, uint256S("097733c5afd900f28cb093c9838d81fcec4ec90acbf792cd3538361fd0eb6db7"))
    (719731, uint256S("88d3c92b43adba4925f189b490161cb8599b9233bd63c91e43820d75baf6fda2"))
    (733572, uint256S("931794f3853b2f55717cf07a8b3b7f3ba548e582aa1a3090d446a946fe66d79d"))
    (747413, uint256S("fc859c87bace0e6a53655b01be2999bc842f4e3856579fc88d77c5295d4a5ccd"))
    (761254, uint256S("bbd2f9f5d754417919e9a81c068db028f9650283c7be8810806495faf00a1608"))
    (775095, uint256S("2c564a8874137194415ab916e21cb88a25a82b1817a64a752f6c1081075d9853"))
    (788936, uint256S("5b83b086290bcac8789dacdfdf0289d213c0ff87e6a9f9b44d4f99c38f36d341"))
    (802777, uint256S("c893cc09ac4928327c67141f052ece4057f7df7d423e8d7950e2289b2923dd8f"))
    (816618, uint256S("6242b8a8dbf903e603b7b314b4553123717bbe5ff91c046ff0304e57ab19afda"))
    (830459, uint256S("303fd37e15389d0717db05d3da29c61c12257392dd7560d5d5ac1513d4d3141b"))
    (844300, uint256S("f5b5b199d9d72912717444b4bfc9ac22967ba1302bb15b3bb0fd629ce0f7b5d3"))
    (858141, uint256S("b9b13704cc6408c4e72b4c09ae9d81c81015e233bd24193f138227a1d8689d8d"))
    (871982, uint256S("ec6a238ca88b712cdf3d69210b1e7b682876823da71a663e9a7a451bf1d857e3"))
    (885823, uint256S("cb03d72cd2df6378124bfc2cdf80795a924d0b044067fc8ba20e5ea2e16c8702"))
    (899664, uint256S("25ae771e37366f496febc1666d6e9bc6c8513506049616d53e52f0b12dc97adb"))
    (913505, uint256S("d262f6a151c267a7d2bbac1cf2c38ac00ce48a4aa29e285de9349ee64ec0e7ee"))
    (927346, uint256S("d4024c5f601652e190e09dba1898de9d44a533a23f61950eb0c1f4c628c50e07"))
    (941187, uint256S("40ddf0ca609e940a68cf000934102388233fa856325e863750d82309b83e3da1"))
    (955028, uint256S("62ad6c2e86b125483456df892a3e094e0a48f3c5acf76b1a146b082fbf1c76dc"))
    (968869, uint256S("960486abecfef9c9d0f485845b52dfa303e3c85f3913cebfc3ed391832dc6bf6"))
    (982710, uint256S("d40f0e79ac8e2650c816bee7ce32a665bf80db5282e88594dc3c21f811902b81"))
    (996551, uint256S("0716a2ed33ebed0f58ed6b77bdb57644bd172d8061bb5118c5809854d9e576aa"))
    (1010392, uint256S("59313620577707e6de169ac393e5480bb29127f6c93a200ad1e3480503c3d78c"))
    (1024233, uint256S("3e0d1b0e2291bc630037bbb0d74569dcba671ce53ec9029e919a4a9992fe2efd"))
    (1038074, uint256S("132ed1f6b53b18c91dedca48e0221d160e7c1aaeae189d3f5647e67680e7309b"))
    (1051915, uint256S("a58420f478e10c8717833f2275e34c7df2380093f7443c1a5ca2b401a284801a"))
    (1065756, uint256S("0e194af537070db57c2cdf7288edaba5eb2ba6de448ea4c6e17c61060edb513f"))
    (1079597, uint256S("80cdd807a8a0997b0f421fba2c4f0c3c2047eb3bb2a3983717f87aa64cabcf5c"))
    (1093438, uint256S("03e0d290333b2e8f6baf16c1d4794b852de3da184d4ed613cd90f992f5e4e25e"))
    (1107279, uint256S("14b504c458962143b90f812dcfba2901a9c8b0990354acc03be84ad9e89ed399"))
    (1121120, uint256S("33f290790d5b968fe6af10d1fb727e6a3d1ac7932ec0b0128a90cd26b5cc7581"))
    (1134961, uint256S("3c2a411651c9dd01f03b9e8970ec5c66c57649a2658c47acb8fcb3e11964e35e"))
    (1148802, uint256S("d81d1bb0bff164ffd49f93642e9e5fb88b490e28f2a30c4ed5f2e2595a7b2f36"))
    (1162643, uint256S("83d812ead15b55b72def3ad9dac176a72e211c4d3fefbea09353301fd4631f85"))
    (1176484, uint256S("4acc3bd0a0fbf32537d8b11a23623f0c80223e91f63e3fb9bb15818d4cc5d32e"))
    (1190325, uint256S("d69caf724357c27e10ebfb5b79b136297ea64ec7f1c60bbd386206281335a744"))
    (1204166, uint256S("13e68bccc7728020d8358e261289c21743c0bf8998a59cbc8d327ba4c7f8af11"))
    (1218007, uint256S("7009d91f21887515e2566190484daa38ccbf00c9d1a0798e27f54836d54715e4"))
    (1231848, uint256S("0391118ab20e0f1eaaf81b8900596be8258c8e1b4134dd1bba78ccec279be2f7"))
    (1245689, uint256S("1dcd83780f90eb5b36bd203f2e2a747e4af3cf09d3306c342b414b383d9f65ec"))
    (1259530, uint256S("1e13466d07003ca0f34d7e7b14091ad1023da44180829e7372659ce5516d2582"))
    (1273371, uint256S("5e5c6ad314337548eb3abac51d7f9a4f86a1c10590d06e911d944a0eeb621736"))
    (1287212, uint256S("c499760be1ca9fba02e843c938966acdbae444cb7053b8b9c971a1a791cddff8"))
    (1301053, uint256S("9e3fddaa87e0912362fbed2119a72b5a88426b841e36301f51352e3bed053f5d"))
    (1314894, uint256S("dc7545655bd8aebe586576200558237336a94453ba90d45d1aae011b92138e43"))
    (1328735, uint256S("1b20a53685b925e9b8f095bf82fcefb4250149611210f238acc636f4eef0a72a"))
    (1342576, uint256S("4e2afd76bc3847096e21976a702927985d98255187133995358c294c749d5c46"))
    (1356417, uint256S("3e5564a187d4cc77ad4c01da0d9aac0106d8b28095737d4d62e5f6667da8acd3"))
    (1370258, uint256S("8c46df6f964d08818834ff53e3d9a4872c2b1ba5e82f5ad5e3d8dbf6acdc06f7"))
    (1384099, uint256S("ee680939d669a635bb945971c396ffceabf01fe2f5701933d7c1892e315007f1"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707147540, // * UNIX timestamp of last checkpoint block
    2952921,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2824        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1622058209, 1716299, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"));
        assert(genesis.hashMerkleRoot == uint256S("0xb81fed5916d638ae849e84e71bb0a920fa6858a0b83cbd596e6ef13c458c84b1"));

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
        consensus.nRewardAdjustmentInterval = 7 * 1440;

        // spork keys
        consensus.strSporkPubKey = "02cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda0324";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "sXXXXXXXXXXXXXXXXXXXXXXXXXXXVpr7nX", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 80000;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("59ea521b46edf374093a44c5e8bf88fe3db211aa9fe63dad1c065692047f6db8");
	    consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6ca0d4ee6fd87d7deb8a3f31eb57dc52588aad8c75766f6449135182f1b472b0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0f2a78cae02903adaee9b7e43a91b86725980e9ef3bb49303a722a48bf9a32f6");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("a70f1ced0cda9854854bda729aa9c93e5867fd583158f033fb16b50daa258a71");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3142c02979abdf5e8e8f6d0f5d68e04caee93fe720d401a806e5e074e50ed5c6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("be026155f0d3fce0b28ba5e0153555b34fe850beb0244803e27c64dd895a8938");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf6;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xec;
        pchMessageStart[3] = 0x78;
        nDefaultPort = PORT_MAINNET;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptosaga.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 142);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4B).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = PORT_TESTNET;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptosaga.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptosaga addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptosaga script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptosaga BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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
        nDefaultPort = PORT_REGTEST;

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

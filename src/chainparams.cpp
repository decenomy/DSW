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
    const char* pszTimestamp = "U.S. News & World Report Dec 20 2019 With His Absence, Trump signs $1.4 trillion bill to avoid government shutdown, raise minimum age for tobacco";
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
    (0, uint256S("00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"))
    (21064, uint256S("5f689c5c22e43d12f3e655e6b680123b114635cf4b904ddf2844f603bf84c67c"))
    (42129, uint256S("9b59396abed4b8b11a218cda47c5f52e7bb2c26d0f084298e4b6fa42efb2e59a"))
    (63194, uint256S("349144bf4449118851d80cff0566464bd54d8dbaeb68385e0df0c10414612c38"))
    (84259, uint256S("8062ce833319fe2de133a8e528f2973c6df0fac911ee929da71d0bae9b0b979a"))
    (105324, uint256S("f2cb381acaa194139382ca26331a0aaf2ec4f8432b624365d53cc0d674a9f38b"))
    (126389, uint256S("c307903b59f3e6a89b80bd199cedcb8005afc12d7887266255331a1e32c13c53"))
    (147454, uint256S("dbe8452af218b0735cea65d5905ad83435b4e7f030caa20279e1055c91394d99"))
    (168519, uint256S("b56f84edc409e8d73875796d9910135309964507a9d4f963b50a0037d4240ce9"))
    (189584, uint256S("83e637d7d813ceb1d844b7c2032f6065dd8d7f582105823e9dd664d7d7576590"))
    (210649, uint256S("9e14c7948ae072dcf389388cadb37c8209b9e15bd4305b073eb837a6050238a7"))
    (231714, uint256S("941fee0ae3db817701bb0b3b360fc0a509fb1783e77a50168ae01ddb2b16c035"))
    (252779, uint256S("635420c8a5ede6ac8963a7830f555e820acda42384ff186a0707f70c0bc3f49f"))
    (273844, uint256S("478612e18268c96e5f9e2ed84b0755d3a6f1dd4b17d53a7519e89fead8cbc324"))
    (294909, uint256S("929ee86d2da083131cc0ea5f3cfa7452f6e6e3a821c7c3cdd62ecafc0b9c312c"))
    (315974, uint256S("f299f01a262881e6e3f4bad8c8a8b6ee5c430f804394ed2c292767de0b017b06"))
    (337039, uint256S("d58d04da2cf9bd8de7d0f02324d229a4963305ed4d69149b854a6d958ff50e03"))
    (358104, uint256S("395db0a9813f78ab975deed65095d3d174b90e23090ea05601fa4aad24b15ea7"))
    (379169, uint256S("f16394db6935568eb3ea1d0e8530900cfe18d7344861e66789dffaa9f9430076"))
    (400234, uint256S("ad6a15f5a2b931b10b5111c05fadba65e34c307c98cacca469509e9810f61557"))
    (421299, uint256S("1791ca30fedcc387158673485567bcf078ca18e76053d690fe5352f62c523060"))
    (442364, uint256S("35475f6d70961ae53bfce6796d6864d21d2dc26cf2aabb7313aa630825a01776"))
    (463429, uint256S("4d9250acb32e54f316829eab9305656ace3812e14d07654dfb607701270bedae"))
    (484494, uint256S("d9710ad5a03cb3c56a69ff41d5d8a2fe514057e1edade8d817c4ad096ac7c412"))
    (505559, uint256S("2b6b87a6b38eaa7ded793472925c8719a8380f16f7209d0152fc2bdaa58d2a3d"))
    (526624, uint256S("b119280e0305025df8dedbdc54523490d892ef0219e31c59177fb27fa82fcca6"))
    (547689, uint256S("711a6933160349166e82ad55cbe0aff71af9883c5ca276d593904f5f2f9b6f4b"))
    (568754, uint256S("bd964a7ea705e157147a8b63de7e03f472760a77ad43d34c5506619f5447f66b"))
    (589819, uint256S("dc88c608079dea714198d9ec1c283e850674d34685a3edcd512d9c5d9883ea86"))
    (610884, uint256S("d30aaff584cad8e2c76fac628a2cb5b863b718d90e4ac7b1206480a7b43926be"))
    (631949, uint256S("45d5840bf3f78d1c70720e129756d0f84fbc9d151d1a91c1a1ce9c1eb468765a"))
    (653014, uint256S("3ef859e56042b8fb04178309e340637be43421ecace846f8cfa9546eb76d22b6"))
    (674079, uint256S("d45b90800e005e0b358450d8d519afc12671da633b26524ae59059b6de31b5fd"))
    (695144, uint256S("ae6f71e24a5b634493924a53c5233dea78d09f780ed3e1d38153cd3c171c618d"))
    (716209, uint256S("55bc106918d56a3ab8ff543f40b1b6687fac0d18c7c13f6bf098e7360577e959"))
    (737274, uint256S("f953bef77ade91ecbc3686156423e1b3896e41629fd96316ab029e3f131464f9"))
    (758339, uint256S("a5a16da2778c8e164113b9147e1d151809b0e09d8e9cde7b0ad97167cb5623e7"))
    (779404, uint256S("7e3f0ef985c3e0fc164b64bdf1a3b15a73b2cd3711f2f52ac9624f816cb098ac"))
    (800469, uint256S("586e940474201bea98dd9726aef8ea7be558e61831e66bb93bebd5dcac6f0778"))
    (821534, uint256S("2a7d939a09898cad15931c6ba69002b25c9ee79ecd153c215407cf0e2da42d88"))
    (842599, uint256S("7f6e8f911296a38146820631460a376b1e2f4f20a21356edae8ce43dbcbc9567"))
    (863664, uint256S("de718ae5e1657acb5a49a864258ae98844d54da234509191eeb31402ec7f7ecc"))
    (884729, uint256S("679be764735faf2d67ed858ba9841e815fad8359dde1bc6c05b6d111a9af2df0"))
    (905794, uint256S("e9ae1ae9cc14ccae091d4ecd21b965ffc686a7c4e73f12d06209c504460a3a57"))
    (926859, uint256S("07e2df01b56d85dba1cdc9ff4518b75fad1a2b631e6eba7cb8e5c56aa7564ce9"))
    (947924, uint256S("84d53cc627d4fc3c1e5b5ce6fe90293f491f37161a8035ef3dfbe1ac507e2275"))
    (968989, uint256S("831ac86a0757457f1eb88f047305d5eb9c423c603e2a7897456e29fb1aa1fb7e"))
    (990054, uint256S("37c820bd37b869cd4eef2e6041b14d743405be06b527ca62bdfce072565a5acf"))
    (1011119, uint256S("809cace0a8763478af1e60ced3388450b97a83a95aac37fbb0ac49fd4f6cd23e"))
    (1032184, uint256S("ab261b2051a1180fc24250fb9c7d2447527391e76789e9938a8baf94d97aa010"))
    (1053249, uint256S("6b4d9526c11fe0311a22ca539cc5a98ca404b9438aa57b66f82bb5f2a2d339aa"))
    (1074314, uint256S("9b762ded20858faac4ffe802dd3b29d654636f2bc7f2bcdbafc65b0a36165483"))
    (1095379, uint256S("d12354f91e5fdc2ba67bfe62f637c488623a27bcda58c55cacd465115842c087"))
    (1116444, uint256S("1956fb069aaac7b3bcb4d0cb6682cfb3e99540c6b8cfabe931660401ef1834d7"))
    (1137509, uint256S("b60c1b919b79f4e1d30b53ef26e84a6145442204a1a6d7e34ee9ebf1d61e3f84"))
    (1158574, uint256S("c011ca7a7a058f85f6b375f55d206f0b0651b395b23a4ffa1a9a511573e9f5a8"))
    (1179639, uint256S("1535d72c7b811ee0c1e22e76755dde434342d7556da2263819b3aa8b8a151460"))
    (1200704, uint256S("1abc9105e3ca635b2436fdc8604a3f14d5b496695080242917e62494c816ed58"))
    (1221769, uint256S("9e76fc065c41bcf96cc0123d25c3623c3c032ceb5e04378881070a4b21ae9582"))
    (1242834, uint256S("3560b791072b88a75293e8c6ed5c0c58f8b566cea5cef8e0e0e4d4d10e88f0fb"))
    (1263899, uint256S("dc0f0e536e905024537b7d5b3bf60f09f4ca0cbf0674518d32919454cc87d401"))
    (1284964, uint256S("9e3075f57ca673e4b32c67c0f93948a4a7bb00d03cbafabacddd35845b1d2708"))
    (1306029, uint256S("9ce34932b76eb7247bf33c30452d91a6f1593ffbe4f61daba63b83561b47cf59"))
    (1327094, uint256S("019d0629eb896e477e031d4b25a01d622735ccaed9f0c6f05600cb4204b2a514"))
    (1348159, uint256S("709d8d8eb19a10b749280651f837d142fd3aa6428778dbb48f67ff8efdfb9e79"))
    (1369224, uint256S("5d35c613f7cb4fb5f8c2faba457bb0f0f1167addf1a212d4ccc4fcadb8d48f46"))
    (1390289, uint256S("e9e3490ec3bd251fea70174f51088b70e7daefea432ff5dc7d0fe178e9ed8d1d"))
    (1411354, uint256S("0aa8e3261d21ff81704bc7a5da305624be7d31b1dbb3bca745e1f2c243f05113"))
    (1432419, uint256S("8a95c9723c3759ba314113564864613d3904caf62eeb17dafbf7d2bff9d4a9f9"))
    (1453484, uint256S("7dc85e4ec3acf5456d07156ec928c9816142bbd25c15fffe4ed636610169e129"))
    (1474549, uint256S("18ed9f11ea3a574a261d48b641879682d83922f008aefdd758d80d60ad4d0c0f"))
    (1495614, uint256S("e8925f1878ea503c25049604448bd1f3af70bf85bbb847ded1a6ebe7b56958c4"))
    (1516679, uint256S("09daa9e687ee5195c250a55c02feee071d982e030eb2e896076d470fb9de44cf"))
    (1537744, uint256S("3e81a07b862a25d6fa5ddbe8aeee31ba4f52a7e9b9e8531b334d8515c4a8c426"))
    (1558809, uint256S("a343fe26ed4fc9d6306aaac95380782a287b3e746a3e9e93200eb6d2515a70b6"))
    (1579874, uint256S("ecfa55abc47133e7099632ddd410c9a09b5259f48ddb52071312c8c5aea00212"))
    (1600939, uint256S("f9217ad689549b96d547719c28a8b524757e79b6d9231930840448a47fff0ffd"))
    (1622004, uint256S("9283f398e6190053f9db511c5dd94440b8932b802c2fea6d053d5c305ef7adb5"))
    (1643069, uint256S("acad6316bb97c813a5eaaf4f758547e24b36a00494e4d5d02dabc5d6e017a315"))
    (1664134, uint256S("ab243e1196833f3ca5f85b60060dcbdeb8088e7cfae1e3f137ab03267c967438"))
    (1685199, uint256S("6f8fa4f61f5b5a8250fd4bde6932936b088872330e9a4fcad90ce2f3aee64ddf"))
    (1706264, uint256S("66d9faaae7a164fd0d33720bf3b1da1b13dae856a5966d4e2cd9a33782f493f6"))
    (1727329, uint256S("52237b3f25c3ecca7da2f1e145481ca0a8dcd5e88ee2db89a590d920034e2bb8"))
    (1748394, uint256S("c26a0d553f56ac863862bc6b3eb902eefa145d7a86f2ae992197a84974842f2c"))
    (1769459, uint256S("8cad923c0f2870f03b873abf0bf68a1bdce565e354b3cc6e7f971a834191b159"))
    (1790524, uint256S("9e00c0cf3837cec1c43954da749e925ac6a3bfdf563194dab11bb541c77da644"))
    (1811589, uint256S("f80c3b98e99c1ab5fb32e784064b3444f17c919876d4aaf3831def058cb3bf90"))
    (1832654, uint256S("a5d5a1054cc7b4c1a8b163a8c2306ba0a3e0df6eaf264ba2f9f9d269e48323a1"))
    (1853719, uint256S("15376b09b283823cc8b133751f0417a981c044ccf140efe1087c91389800427f"))
    (1874784, uint256S("50dd1de0f0e149357641b30461aee50bc19a46b697d71c43fed8d981518110bc"))
    (1895849, uint256S("dac6e22a49885b10751eb7720e8bd37342b7aeca7d201d52ddccd151d266c1fb"))
    (1916914, uint256S("7a06e0f16d92c282c82c8265e8e3395d452fb29c1d13f1feb00a9ab642289275"))
    (1937979, uint256S("05bc49360904748502f1fed6576ca3c23425fd7d5803dd5c45a8f2cd8aaad619"))
    (1959044, uint256S("861bdd461da34362d7838ebc037a4fdef5a3c3c95ce94cfb1435b93d3837f508"))
    (1980109, uint256S("d470a36332930be4ebb6b2fbc8b62d2ddcc7d20aed887dcd36db9e55099e4140"))
    (2001174, uint256S("fa581216a53d6c77455dbd0e6f9f173e8f221256b24ae9b9b5ff37a4d2f4f1a9"))
    (2022239, uint256S("3d56d24996e77286c21cde4c7e70090f9118f945709aa7b6e51e40a1461c1ffe"))
    (2043304, uint256S("45a655d9c5a6bc30c6606be8aa4e1a4ec89a4d402862ad7072c056df5c7c5e1b"))
    (2064369, uint256S("7186340f397f4e9ad2705c3ce2308ca6f70ff4ed380325c425bab3a7b7fd1cc4"))
    (2085434, uint256S("ce8c5dcd5f482bb3e9adbf0533617328a8e11f16c48dc528547f97ec6942ccb2"))
    (2106506, uint256S("6b2b19984222036b7a0aabb0bc3295442ef26a63f3f06917c7a68d134466ae06"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707861540, // * UNIX timestamp of last checkpoint block
    4901756,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1618037081,
    2501682,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1618038166,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1576918337, 2012178, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c76e5393b390e03a0c0ecd6e773a99bb906d30aa8bc2a1108146bc78561"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

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
        consensus.nStakeMinDepth = 160;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nAZZRCoinSupplyMintHeight = 800001;
        consensus.nAZZRCoinSupply = 38000000 * COIN;
        consensus.sAZZRCoinSupplyMintAddress = "AJ9U4dLkwuxw4bLayZN6BMrVyHRsKfXJ55";

        // spork keys
        consensus.strSporkPubKey = "023a979aefef58890e1cae7934c5bed09a8dc8f70da29d884d84bf083eaac6d566";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "AbURNXXXXXXXXXXXXXXXXXXXXXXXTPBUBf", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 320;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 330;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 320;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 350;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 800001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 800001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 800001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("84ce0f65f4261b1d1e951c9a10f283c1c31d9915bc6e07eac170dc8803341d3e");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("de10b92f53b0ee686ce9393dbe0a175bfec8e3a1ec9b0a12d15dacdffa614217");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("134cf44ffbe2b8abfddad62e42fbe1ac48e00cec282cd620aebd80c0eb2cb001");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("de10b92f53b0ee686ce9393dbe0a175bfec8e3a1ec9b0a12d15dacdffa614217");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("6d41821d7438c430d602d96fee51807e7a3fb8412a456a8e34082541ab10b2a0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("64c3ba555ff22fc6a4bddb646a0a38a406a36adf7e896ea97971917c0914cf99");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x12;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 14725;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1",  "seed1.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.azzurecoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5",  "seed5.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6",  "seed6.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7",  "seed7.azzurecoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.azzurecoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 24);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 198);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x43).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1618037081; // 

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e0ffff0, 1, 50 * COIN);
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

        genesis = CreateGenesisBlock(1618037081, 3673827, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bc103d39f3620750bbf80d5cfdcffeeab5d97cbdac6b9f8ba3da04d8718"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // azzure starting difficulty is 1 / 2^12
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
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1569538800;     //!> September 26, 2019 11:00:00 PM GMT

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 301;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x57;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x33;
        pchMessageStart[3] = 0xff;
        nDefaultPort = 14726;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet1", "testnet1.4444.tools"));
        vSeeds.push_back(CDNSSeedData("testnet2", "testnet2.4444.tools"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet azzure addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet azzure script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet azzure BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet azzure BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet azzure BIP44 coin type is '1' (All coin's testnet default)
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

        // uint32_t nGenesisTime = 1618038166; // 

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 50 * COIN);
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

        genesis = CreateGenesisBlock(1618038166, 302, 0x1fffffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x006656221e2e3eed8679ea44b0ad48121ceb26b38408aec372ac8bca1fa6f8cf"));
        assert(genesis.hashMerkleRoot == uint256S("0x6df2c144da90964516839ed9d56ab2742cfaa8956824c16cfd0c4ad482f0e1dd"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 2;   // azzure starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 5;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x21;
        pchMessageStart[3] = 0x57;
        nDefaultPort = 14728;

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

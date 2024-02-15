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
    const char* pszTimestamp = "The ClearCoin Goes Live Launched! , Wired 28/June/2019";
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
    (0, uint256S("0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"))
    (23718, uint256S("9cd409ba4f00e38055e6656470663400bdf0587fa82ddff2f3192290440a4c7e"))
    (47437, uint256S("2ad2f7e19f33233f2ca1f8c27536564b509ec06f079d55fb5f96020b9e4edf77"))
    (71156, uint256S("c60fbac3a72ca980221b146ea4c84e52b6cfe1c093329113f0e6b599c6608f19"))
    (94875, uint256S("7d1b5ab8c3c0f5bdb4a9f2d1686ae43c569229716f62d16acf910c746fa6542e"))
    (118594, uint256S("131de4e1c8eef507d64187ffe6807ceef82662696706f2f49c21f9353f2348c5"))
    (142313, uint256S("1d9b298e179ba764c2cacfc78adf04dca33a8af9ef6d4529c70395845211d831"))
    (166032, uint256S("2020157b83571c916f6f679c66aa595f0efa7ce6f5c942bbed73c6cd58e8d735"))
    (189751, uint256S("531a2364f6b2ca8aa7d7b31247f0f1bf38bb805456d52c99401bd9dc0e73c42f"))
    (213470, uint256S("2d9b739373b02c24e2eb1f7b39451a858661e0970af1c2a909a400a6a1742833"))
    (237189, uint256S("e8efd836d28902a06001d5a9282d511da6594992c4983110a1d66584b86e9525"))
    (260908, uint256S("6725e2b318b307e954b45fa8e5b94a96a304a5506fd407535e671e7578d31ec8"))
    (284627, uint256S("a08fae0abd5d644e008d2bf055214d9300b3dbbeafc1f63ceaffd1b839eeefc1"))
    (308346, uint256S("ade4196e99b3d034478819f80f483ac37dd4ad1196eece998355f7f4bd3823de"))
    (332065, uint256S("b71aa49bf75190f237de6319c55a47d35d6c53b2291862ba84cbfa6cf7d4f09e"))
    (355784, uint256S("50e0f7535ed6e8c66898c512c92a6dd310a410c9bc2a81f9f2461c65e4ef453f"))
    (379503, uint256S("b87236b12a849e8b0748325710860169da69824eb17d33ea58bf33f007ebcd22"))
    (403222, uint256S("bf3cfac7d76719c74601e66b121aa92bcebc674e67ec1cf8e6290ef92b334863"))
    (426941, uint256S("614ba72cea940aabad8057d3e2b2bc8d6b638e4778876db0d1e6802038052a0b"))
    (450660, uint256S("fc46f76f8a2734ea86ea20364b88e1220624a4f40ab6a7518a3e0402214437d3"))
    (474379, uint256S("00277e4774de34115de2c381567111462b4d990893380ff40ac4c9816df4dfae"))
    (498098, uint256S("59c3d249afc4aa0c249e5a00d833bee99122ce1cd11dc0eb3e97f5afcb1f08e8"))
    (521817, uint256S("c09dd74b8431e4b61ad428f601a8c2b97cdfb4197eb3ae62a077b9b3815d47f7"))
    (545536, uint256S("9513a01940b9358308bf78b145c643d71671d77ceedd22056d5ec3e2ce094cca"))
    (569255, uint256S("40da36390a2b27b79ace08e4a5c665311e49c0488e77dd915d060de5025b3a5c"))
    (592974, uint256S("3163c783a0db18ad26e42d0e00839a011405d81466afe2291afdc2d32c50aed6"))
    (616693, uint256S("527b7bfbd9ec0336d4f72f93f435b30ab7338883aa668218b8f8191d60ab5d3d"))
    (640412, uint256S("fe9b6a5886be2c885273f58e2a92be11a65fdc5e0276a10edeba4014f385bdb9"))
    (664131, uint256S("005d78f97540afffc8582febe4f8420fdf65ee29f494c806516e5734f8d3b492"))
    (687850, uint256S("333b83f79ea09d1a71893c6d51557018cb9647deadf16da805a20a100483b3ab"))
    (711569, uint256S("1edb80e479391e20ec0964709af69e2f0a1f16458c7bc812f5aed7e7a322f337"))
    (735288, uint256S("e32f76084a57e53fea6de0d72bfbe727c93162e50327de43a097a630a7034338"))
    (759007, uint256S("947e57ec8f646d666d3aaaf6c417b5beff95395960df5622450f1538f9c2345d"))
    (782726, uint256S("28e6c73db71f6293a4dbdd74d162f12e2513d2e34995f76ac288f16e06ea717d"))
    (806445, uint256S("cc2d9bd8da16690eca20d3542d6a427fc348c69f0aa5893fa3e6e7ea1e59f4bb"))
    (830164, uint256S("c361d8bfd51f0d014f972612f141c215db763a5283b8b8e7af926945cf8f04a9"))
    (853883, uint256S("309f6a0271ed78e47459e770bf00a68e3ec383c576875e43742588e06f6b64a6"))
    (877602, uint256S("f71efb5a02cdf83297edfb598fab9b2843bdc457712ab5d2bc1458d07c1e2baa"))
    (901321, uint256S("9ea5972dc5a51bd366d8e949e343b08dbcd733424337ec60a6bb8e8b674a70b3"))
    (925040, uint256S("5c8c75c4042521bfb4c8d60570340b49f9a2308e1e3b371d580e2233ac929ea3"))
    (948759, uint256S("5685aa58af16a058da5a7c57a7c7b10876c3df29ecb65d30c617b3e3b058b5df"))
    (972478, uint256S("554dc9ab66640af58bb8fc35c907b5f559e1586762d11ec0189b83e9bcaa9150"))
    (996197, uint256S("463c7dd99ebea22b147a2fd2b713ff4ce4eb2d1c41506dd46603410738ae16cc"))
    (1019916, uint256S("3dd175cda35b84c46c6b630ff58cecbf4358a3253dab76c6855d148cded3076e"))
    (1043635, uint256S("caa369911273d17513431ade511e07b355cfe845c071efd8ff8ab0c41b132bea"))
    (1067354, uint256S("e5cfb246e671bae7327ec5d9783bd23d362cc1cdabe9a1ba438f3f83178a579d"))
    (1091073, uint256S("b3af9566d63565fac69a2e659baaf38c5f82b9986e590c1399f5fead91b24e7b"))
    (1114792, uint256S("8da22744929f2f751fd0124decefa531fc11f2b25dfff3e0ead984927c54a4ff"))
    (1138511, uint256S("e5a7e313369933e79ac43e9f08332d90536932f71c4fa70230b0b20205203960"))
    (1162230, uint256S("86d179a71f2c768958f7b04418c821fd3a229dcf88cf4ef1278ebacf6a5337ba"))
    (1185949, uint256S("36100538ea4a10bf47fd93f316172e95ff00a7c78779a177e20fcc5e6b56d2ae"))
    (1209668, uint256S("3d8ed9bc4af97995b9793383b722d4c0a857a732b582ee5e31df8f2d01902334"))
    (1233387, uint256S("cd057a043f6582550a6e9641c54ac0f15488b7c44449392093fd57dce718aed0"))
    (1257106, uint256S("6da55d3baedc3c67688c266625b0bc116360b0ddd240c1070c8c2106f8ac59a1"))
    (1280825, uint256S("e8be8a6e27765c2f2a3838c5de7b27d91ac2e64683eb1ac2ee72393e269b3829"))
    (1304544, uint256S("d8ec37377257db5ab23c90663548adb887b1671bd2e4d580d2d7ab9a86febae8"))
    (1328263, uint256S("66af934b98213c00eba2b34ea3ab751d875e4a3c57730761b08eb8e1ca116448"))
    (1351982, uint256S("defb41f060e020bf313de366584734a8220d67339cd79c0adeed65f2b4649329"))
    (1375701, uint256S("962c6d168748a8bb1d4cdb92b5cf6fcef4f90af018210e327325123eaa2615d1"))
    (1399420, uint256S("1d42a86f06a0f2beb2cac8496e84e3ac18c5b77eecc631d9dd38ba3f839d4dd4"))
    (1423139, uint256S("d7cccfe9eca93c6a92ad386545a339f3cec60cfb20412335bb8a294e39263497"))
    (1446858, uint256S("2553e5b8ea7c60abc2481c5a9132206a37d1a7a7d781389fcb818f30c91bf893"))
    (1470577, uint256S("a6463b88e1f6ba3ac5b86390f80fb1724ba74e994527aedba111a58300aeb6fc"))
    (1494296, uint256S("eb62fddda7b4f5b567240b518fe1feeb2ca4a811d43c0d508ffe42b01a8f075c"))
    (1518015, uint256S("0735b348c2d108fddbbec1b77d63d1e7911b5966b44da9e88ffbd59615cca25f"))
    (1541734, uint256S("9d30aa822b98505fa4a7197b5d42f0dc8f513db0c981c27dfb3ab234117aaffe"))
    (1565453, uint256S("2d763020fff1e1dc4b076d3b7d5b7530217a7bad8b29905e42db2a727097067c"))
    (1589172, uint256S("2f21a0456226b1b0a1036f219f406eb4375b464944032fe78e1971e1e85a4013"))
    (1612891, uint256S("03f1ae02fa2c843d990e7a33f8ee1c2320d451d57a801cd4e9332e5b2551b2e0"))
    (1636610, uint256S("cfabe5f27fd0ee1e44bf837b1a73e645fc959620bb8588d6fc0869b9b7ff55a5"))
    (1660329, uint256S("2967fdb69885927c7f3977630a0d02587a91cc154a66f7d04372363914cc7212"))
    (1684048, uint256S("0636569acdb8273a8e4b42a6166e946abe58721acbf25ec3749a5878ac8305c1"))
    (1707767, uint256S("c768d5487c9ac7f0b4d35b0ecf418b4ea5750ee4e2f5ec4d53e4a9d136477a10"))
    (1731486, uint256S("be24c1bd2fd258bf87080c01d9d9c41bd71b40e745580d6536bc89c542b0d56d"))
    (1755205, uint256S("bd3ecc3bdc11bacbbc1042f9ba3681f6266fe7911eda32e6637f898b0f5684d9"))
    (1778924, uint256S("300d28e6da824d82973704d639d281ff30e542e2a506bb3ad5eead4b576b7564"))
    (1802643, uint256S("dc95a1f2e7c0831f45caeb0c8dbd86c5d10d868ec900c8e4f125017995acd1a3"))
    (1826362, uint256S("b416b726120b064e84fb1ccfc703c5172bea48055ecbe0750fd988d196cbeeb6"))
    (1850081, uint256S("04d40f42dcf2d2288ac33a6b15f58dd4c28654997e4928900859e5eb9d178aeb"))
    (1873800, uint256S("40cb1aeeef92cafcef4392171d832ae92ff2f1732bae9c2d0aa5257becd33f98"))
    (1897519, uint256S("ccf413695766e8198572d9fc8290c7d6e3515f9423afadde9130f2246f808df8"))
    (1921238, uint256S("2684f67c6cd22f3fa0a025b3adf5a26a3c780542ff67eca2e6e1ddb1bb4e542f"))
    (1944957, uint256S("0646b7f06bfdcb2b1595364e0b9c8f090fe956f2f84ba528992d2bd4d026cef3"))
    (1968676, uint256S("711a35b5cd027341f175393cd003fe75864813dce19d0acde70475bff749f87f"))
    (1992395, uint256S("16fe10a09ab30c8a7dff4f1cadfc131a008cc4e1056eedc90e71118e36b16a2d"))
    (2016114, uint256S("dac64b1562be00a7bc6dee064484dd5b5ae4f9e59041c370f860cc1297e02631"))
    (2039833, uint256S("38d3a0e25f5fa69a0f9bc69db53892c9e5c8467ea4eb3e222bd6e4ddc19db78f"))
    (2063552, uint256S("86898a082e9d0c325550c87efe3296f60508fd49304640b2ffd3d5b3a2cebecd"))
    (2087271, uint256S("b9dbe83b6aa650be27a26ce95b0dea3487dd1c92cdd4ef1c54cbca373823fe5f"))
    (2110990, uint256S("e7616d1855ce1dad8336fff7de40562771db018c462c97eca498201a8f0800c5"))
    (2134709, uint256S("034b1d7fe2c84b088afa992cfe1281b2907700d712e0149541bab1dd782d355b"))
    (2158428, uint256S("3775345565a0690fdc8744d5b2189304f88c523c2ef83c87da26d461056fac2c"))
    (2182147, uint256S("1f28c75a96a4deaf434c6a0e722293eef8f52c30da0d91caa0c0ae8f6821b2b1"))
    (2205866, uint256S("db4e74d03b0cd48737810ebe129ab0c30440b71dbf4988b2af800a224537ec1d"))
    (2229585, uint256S("ed8820ae3699f3539c4ff7c2cd68cd0624ace0348eccc1cf01ccef70f2eaa92f"))
    (2253304, uint256S("a3e75c933895db07da7599ca6405a778a77af6de2d987d30a5ac1c7d5de40a47"))
    (2277023, uint256S("319acff4e06e253b81d5fe4af827649820efdc458f76198d1ccc1cae62c7ae15"))
    (2300742, uint256S("de205e7e2f2a16400301d29840d88e2522c6507b7b29c274a39c15c5f05435b2"))
    (2324461, uint256S("90015f155d70560638e2c155d799d5ca5000422943ff132d5c50ea346c2cd042"))
    (2348180, uint256S("efd40770cb4bccf49d510cbdfccc4baa31a41ce0d88cffd6b0c4b6fb63bb809b"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1706541150, // * UNIX timestamp of last checkpoint block
    5368173,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1561685759, 3380104, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"));
        assert(genesis.hashMerkleRoot == uint256S("0x57614ebefbc1a26b6cee7cd4bc94d060baaadf1ad2551a81153a588fd75b471c"));

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
        consensus.strSporkPubKey = "0391eb99d1d94bf8bbc66b39ba11c95814a2bcbcc1cf6c567c8bd58b8710b192f4";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1599033600;
        consensus.nTime_RejectOldSporkKey = 1599030000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "CXXXXXXXXXXXXXXXXXXXXXXXXXXXYGerr5", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 874600;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 874700;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 874800;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1075000;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1075000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("11d02f339a6e096c46be25da07783fa844d8ddae27b776641a6c82e55d38b315");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("898669ae99e12f86f773605a5baed05ea1ba99ddb3d59b5de47d4ec57e43ae95");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("898669ae99e12f86f773605a5baed05ea1ba99ddb3d59b5de47d4ec57e43ae95");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("5f5e467bdd92b2d3eb4cc82cbbd2c99bb8f9d8afe2714da6c429067e4650a837");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("a8632896bd6196956c070e1fcff8c2c2699851d484da03f15fae1f71f34e2823");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("6da440c85dc7f167d97719b8e9d7f9be4cb98641e3e9a4fc7a986c3f62f76dd2");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("8a1cdd4b7db68860752fa6ef7a55605e95b9554be932091b1d933429e6224ed1");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("8a1cdd4b7db68860752fa6ef7a55605e95b9554be932091b1d933429e6224ed1");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xfe;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 32628;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.ucrcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); // 7
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 31); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 63);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x47).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1612360301; // 2021-02-03T13:51:41+00:00

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

        genesis = CreateGenesisBlock(1561685759, 3380104, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"));
        assert(genesis.hashMerkleRoot == uint256S("0x57614ebefbc1a26b6cee7cd4bc94d060baaadf1ad2551a81153a588fd75b471c"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // UltraClear starting difficulty is 1 / 2^12
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
        consensus.nTime_EnforceNewSporkKey = 1566860400;
        consensus.nTime_RejectOldSporkKey = 1569538800;

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
        nDefaultPort = 51230;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.ucrcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ultraclear addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ultraclear_ script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet UltraClear BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet UltraClear BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet UltraClear BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // UltraClear starting difficulty is 1 / 2^12
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
        nDefaultPort = 51232;

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

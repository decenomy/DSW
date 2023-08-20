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
    (11466, uint256S("0e58fb0ef825ff9c527b336d5a33f0cb7cfaf4963c1143d786b58766b678d3ba"))
    (22933, uint256S("681371cc68b239035cdbe63cc9d8a4a9c40acaf69a890b27bd926dc3cf342deb"))
    (34400, uint256S("3331805bf5ea74e9b236ee9cc090327a4402e042dd7b29e8e9c61c02eb52135f"))
    (45867, uint256S("8f7f3dc19cd7666135983a9a48c5bd6833b9290e441353a499411dfb9ddd6c8f"))
    (57334, uint256S("ff447ff0d939cb35270cd0d6a717ed4f29f9484d7d3da38d25e43bff7d20b0e4"))
    (68801, uint256S("f78cb308067e764bdf114b06fc217c623a5199864b180100cf7a55371543a7a7"))
    (80268, uint256S("ad4c740841c9230a86e5fde86d789cf30e2ec48a220b4319c681d50e69418582"))
    (91735, uint256S("a3f5a3bf41e4298b111cf6a21ff7a32320693a311979ae4b8ff79cf699fdcc06"))
    (103202, uint256S("a47f60f40c985d700fd09c2589582099519ac7f27047af55fe49af337d11fc0a"))
    (114669, uint256S("eb5999f64dae7846e9a4e6af9c648a9c2c1414449a2ee454a9764a4b3d617cf1"))
    (126136, uint256S("80132d8e457ad9fde7ea47da7f19418343cbee631c36513826e4418f5ddb6ea4"))
    (137603, uint256S("c67154bc9d28f0e573c622f99d93109035277ab6e6172197bd8889fa5d57c3f9"))
    (149070, uint256S("81b64f4db12c41bade33c458b6eb9d01768b4148266730d1baf68e214bc04d00"))
    (160537, uint256S("cc7632fa7c4d11190d11ae7b9ccbdcfd7fb24679e3c567d214478347fc1fc9fd"))
    (172004, uint256S("1ccf2ae0edbba85b80495707b457317aba8c62935c0ee4921a77bc4c3f4398d0"))
    (183471, uint256S("cd5d7344f0635ada35316af6042d24d724a655efeb45b7c93b4ab73a6bb81f1b"))
    (194938, uint256S("694173d278ee7274a8c1b0b3acabe712ff269a94650e5cae6e626b9cfff18524"))
    (206405, uint256S("6c70598e4ab49559f7c73ae29566967048dd4fbd2310c2f57551631d18e19aa4"))
    (217872, uint256S("0971ec7c44ad6fee9325212486930f6c23e5e14db0157ba92e239fcbe77cd0bd"))
    (229339, uint256S("b87c8c6a3d93dd89d1db4d263b8dc11cf2995975d7a5624d1568e5dcad16f7c8"))
    (240806, uint256S("55eb517fdd1d48d4bcf7c60df8b06fd6c3681f184e9a411700d8d2ca16b574de"))
    (252273, uint256S("6a454419804bebfa2aa326aeb4aa8a8d6e986a33ea293c2bdffacb926e65719d"))
    (263740, uint256S("fe7d780bf11e7b481a93e463f77966814ad63e50b9842e76c770bc307ed34a24"))
    (275207, uint256S("8d3d05cccd7cc0117af39555bf189c3c36368cbfb74002a528b930fb69646784"))
    (286674, uint256S("6c093f268f345890480c5a9427af57dea440d2c3734205565ac7ba21dfc8ad32"))
    (298141, uint256S("b3b241af9dd2cdc6f96d6cf93a97f39585a0c0369efeccf324c3d83d347d6cad"))
    (309608, uint256S("57c9d6e29a60e99304b6a5e527ebd3eb588c9d1c601bffd20d15954dc5ad613a"))
    (321075, uint256S("93e64f241309d62706edb7b58d28701f69a59590ee1fecacb1eea5be26852526"))
    (332542, uint256S("d5e84a2b109bd1d66935af801b29907fc5ded1efe69713d24646ae51309e3999"))
    (344009, uint256S("8e09165490ccf1544df6a404891ade86da468833eb8e8419e616551bc62ec9e1"))
    (355476, uint256S("663312d12518e36eefed91d8483032fe78d368e8b14fc0ba1121dd68f2ff2285"))
    (366943, uint256S("e7a5e64b8fb97b34d45cbc5898821cd4718f8de39946ef2c4187b693bce2a6d2"))
    (378410, uint256S("cd14ba52bc357ace118adebb1d074b29e38744b8c8da5717639cdb99e398555c"))
    (389877, uint256S("13be86e6fe46b8e7720b90b731cfd038dc844c90bb7ddd012e0850dc1fa08e49"))
    (401344, uint256S("432f43b86a2a6482198a7c61648189e572768bf87588df0fb7091aa0c09e4ea5"))
    (412811, uint256S("a5e53227f020e16a53ccd211a28e0e8a1dc0dc07573d43ea77c8427ce6f45fb4"))
    (424278, uint256S("01a44a1a44666e26a879046f2ad023ea4e6297292ba8b1baccedfd3508561b69"))
    (435745, uint256S("19c15b962e2422f1e5438eb9d6e275846961aacf5b438f0437bc668fb1f0a8ea"))
    (447212, uint256S("8177a376895db39bfca8565047e7f4d280ec7ca47021f2255b821e85109ae13d"))
    (458679, uint256S("9f8471479c09cdb75d34a946abbb6f7d2d5995f8577a2bdc9f8873805dc9b0a8"))
    (470146, uint256S("5c00fb6cc82c04c2304bb877fedda81d57b41c9e35d2a56b1cd6bed5f8551f27"))
    (481613, uint256S("4b7df9d165c4e92fdbe3e51d79e502266055597834081ef58bb91f817bc2161f"))
    (493080, uint256S("e7a91166527f84448bb8759fae5bb6ce09896245a9cab714239653f5b13a94e1"))
    (504547, uint256S("0ee220c4096d1e2a17c1fabed0238cbcc29a3cbdfd0a63975c2ba9668c33d7d0"))
    (516014, uint256S("26d88d533f25143b1e658dbd8f1f0040b650aa0d29d922deb8c1f4b9fc11b493"))
    (527481, uint256S("37e4cdea76c960afa5bdf18ac70eeae38cdfc8f3b5a0cf510beeead83bf3cc7c"))
    (538948, uint256S("b503b4e1002efbb84cb7e7ee019466f0da7b53430504dffdc4fcfdba7b2f5b06"))
    (550415, uint256S("a45cfa11206ddb5fd067b3635021f23146e313d0b0619d2fe48dcb609998e5db"))
    (561882, uint256S("deb27318d467389e6c72d9ee36066e79ebb221989472d7d71645adca30e6ce58"))
    (573349, uint256S("68bea8070f186ae432a940aa1235701d9c2363b1021edcb2dff2d6c46ff5659b"))
    (584816, uint256S("c585b46d24ae0ead910671c71913d93962575c4cc6277446f4ddfb01e613416e"))
    (596283, uint256S("99ac7009d5c730bb988d32e3ceb5136cf4936c62eecb30c9838a215b15a06712"))
    (607750, uint256S("0d1a4a2098c4b5ae0997a328022d3f661e4c31a09e3261606f2a4a1ad4b66849"))
    (619217, uint256S("201bf84204bb39a333dae2a21b6323a52105ad9052780dda62c1eb729f532659"))
    (630684, uint256S("e3431e0f933dcf95911e1d275420f3d04ac184c73bef2a61ce9b093fd23b0888"))
    (642151, uint256S("270944d061fbb7f35408d1287b8ceffc8de0a50b7b59b4550dbddde796db86df"))
    (653618, uint256S("62ad2d144610c7e6bad1d14bb3cb78dcaacd54103fe0b256896343c46c5489e3"))
    (665085, uint256S("d390d6ac6bf82eafafa5c8cf284ee6e03ba0ad9e3911c097d4efb2a627eff8e2"))
    (676552, uint256S("6097283fe5d58bb02b37acfbe2da78cf2316f0feb2fb828541ad76355470ad94"))
    (688019, uint256S("93075066ba2d54390b041778106fefaee15537d7f7396e643f415ff8e0b8a146"))
    (699486, uint256S("d83f9503304b7be116604267f0911288c63b5e4cfa9ffcd69d5074e8fd63923e"))
    (710953, uint256S("a6963401415ad5bc0e115ed2b6c5871d1c21f3be0720637755646ee8df39cc78"))
    (722420, uint256S("c14bd4e82c68eff5ad41918807b151de158db0be5a857d5961324998c12c975f"))
    (733887, uint256S("2aca15fca153365a7d6556addec387bf2b490736098dc6e86d46a1ea470b5f5b"))
    (745354, uint256S("8851caeeb4db1f7e83768dacb61565aab5a3a90457248d2f1be6f081f845ced6"))
    (756821, uint256S("cd448c6ebbb4a40db27130eeb06a6909e22e160e70a4c7a1ca0b0f6f63278184"))
    (768288, uint256S("a603f8053813ba37cd8f217c5e8e3b399caebdfdd3a7e6d8f26fbb396090771c"))
    (779755, uint256S("0df86b2ff8382bc076944ad923d99c7ce75a250c13ce436b1cffbfdc014b5d9c"))
    (791222, uint256S("47827112440f3f2459b5400beb643325079d6b7d77bb7e6d75c422aec3c38a6e"))
    (802689, uint256S("ed6004852fec3be1cd0d1eb4b561634639c3774168f0fb0d9e0cd7d145a1ec5a"))
    (814156, uint256S("286c81bb1d4770ff8b712c11636b136602b1073b7d10f9c39d5f64001a7bfdef"))
    (825623, uint256S("b75cbb7f758239d3ef96c5bae8bcee3a583441b71933f0f577f7c4a9599b1b31"))
    (837090, uint256S("c214f986ed5a275a2367bc12877da541bb912a055945d065f318099ac3077de8"))
    (848557, uint256S("8bad3eeea3f66db2265718e1c56898185fcfd250aeb115ccfa39e22c712928c5"))
    (860024, uint256S("b7ca89f0b90bf2c8083098f44a315cbed077888efce00ce63014645081367f6a"))
    (871491, uint256S("d2e14aaed2c17a023b001db194e8e68af2c601ec47397c43494874fb926eb237"))
    (882958, uint256S("d91a7cd5ceac7c21ee9c143e857743c35efac27bda446f179c1927505208a583"))
    (894425, uint256S("b3b10117e2406aab46ac0ea26b9014f5f56341637d682e6ca7d969bf21d4ef74"))
    (905892, uint256S("be184a1cd60d6628e9167f4d65e2b36ce41784dede2cb6a41acf55c112bfe96d"))
    (917359, uint256S("a14ab5c4538477e5051075c0e7f88454bca07d1801ecef8d4d5f1dc0c0bce6fc"))
    (928826, uint256S("af370812b78ea52d2952e06087b6f7cb7238e05851c7847b19b0e4b3f902a6e4"))
    (940293, uint256S("01feb6a71ff011c14f5fbc381828f6f14abeb2207fed94e13fcc91f471d9fb4e"))
    (951760, uint256S("628d2dac1e8ab44e3c49e06a88f7dfec4f603485fd718ba06bf2f6c6f104a8a0"))
    (963227, uint256S("982be4b2b2986014cb8a5b574acf0d0d25fa66d12515cd41ce27e3052332405a"))
    (974694, uint256S("4f75b35c6032cc721002a294aec9795703f2048a8cd0be44f1575c9edd8f69e9"))
    (986161, uint256S("72d01561cf8c5278328084f45ca705148367cbfdde35a9f006f0d198e0052446"))
    (997628, uint256S("49661bbfd7f0c6ec901aff5f17519c7ecf2568d251b6da3b3b1ca209afe33389"))
    (1009095, uint256S("ab02f02cd1cfcbf6c72971911a89b849c0e75cf2ec6484e3a0f5ae4a2fad1319"))
    (1020562, uint256S("190b3c7dc0e2f5c957cfef048e635d70eb6e3b871ba03e0ccc7fa34fb9a9fd4c"))
    (1032029, uint256S("119f005720e40c7ba9b7a39a217e86dcdd0e07206b7cb5be6f6a2e27a7cf4bcc"))
    (1043496, uint256S("55adce624f51cefbbac108af4603b33e79849f8273c0d6bc4b2a88ead5a5a10b"))
    (1054963, uint256S("e41e63694671f186f870239cc032ee1282a3c4420353ee5cdb4f1a0aa9b061b1"))
    (1066430, uint256S("b667975ab439a69b13f68fa751e0a734f8d4501e435e42c4845b4e66848fc874"))
    (1077897, uint256S("dff8dfe6759cc06646537d7969e621f6b9a2d3dffa10e3ccbc7cc7fe69bab400"))
    (1089364, uint256S("5e4f9964303a4b7361f8ced8b71267050889b2c0212d9f48ee447f1e405cf3be"))
    (1100831, uint256S("8aeacf571f6c4740f70d933161082896d157cd38b37fac46f2d90a522939612a"))
    (1112298, uint256S("bc87bcf2d3d141c62b8bfdc323d994dbd886dd387aafff7d16c88acc4137faa5"))
    (1123765, uint256S("4ea98d9709456fd5ca62bdfd06a4d977a67383e3d814dd213adf0d72428bde21"))
    (1135232, uint256S("38330df4ed4469e17fece91a205efe5678932a9af27067bbc05ec39cc58bc280"))
    (1146699, uint256S("8b192927b3d2421d7da9a441344fa61703f6ac255ced2d79a5312520f7701768"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692557100, // * UNIX timestamp of last checkpoint block
    2470579,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2830        // * estimated number of transactions per day after checkpoint
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

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("59ea521b46edf374093a44c5e8bf88fe3db211aa9fe63dad1c065692047f6db8");
	    consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6ca0d4ee6fd87d7deb8a3f31eb57dc52588aad8c75766f6449135182f1b472b0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0f2a78cae02903adaee9b7e43a91b86725980e9ef3bb49303a722a48bf9a32f6");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("a70f1ced0cda9854854bda729aa9c93e5867fd583158f033fb16b50daa258a71");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3142c02979abdf5e8e8f6d0f5d68e04caee93fe720d401a806e5e074e50ed5c6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("be026155f0d3fce0b28ba5e0153555b34fe850beb0244803e27c64dd895a8938");

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

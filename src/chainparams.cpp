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
    (10653, uint256S("38c0398fab0fd8190bcba6d7e90f9749a75f3869749ac35ce40320f5d96ea142"))
    (21307, uint256S("944d96d072335e3176b34eaaf945a3d07b187d863a1899b21d07731b6c5f4484"))
    (31961, uint256S("eadb16deeb01e7db4e48e95c1fff6ae38d768f7edd69642d09ce53eb0366f835"))
    (42615, uint256S("7004f19c38a8a01768c54789e6a1a0467f433ca25b687f0644daedc419911ab2"))
    (53269, uint256S("ebbc1f071ee33bd461c1b8014bda3544596e8b120744f2cebc49539303026fb5"))
    (63923, uint256S("d337bf26141d4b1277ae5fb657de1f8f77be682c7a543b1eeacf52a7faa0a94a"))
    (74577, uint256S("421e2936a69f402729325a336638ba388ca19770e59f6bbb28ed7cb46f2359aa"))
    (85231, uint256S("b6f9b833c9ad6230b1c59b86f3e076848621a8761f9e735b8b120a213e44e2d9"))
    (95885, uint256S("534980788e84e5157fe4cc7155cc3004192d984f781006839707ed5f292e7561"))
    (106539, uint256S("a9fb3d33b1846f0b35c7297192516b293fecd4728f57747b0ae1fb67540195fd"))
    (117193, uint256S("913a5dbfeb547226707930576c532dd84b892182aa576a2bebcad43d27399629"))
    (127847, uint256S("d72c6686be7801f34401926d6678983750297027eff69b3377cbcf623376ede0"))
    (138501, uint256S("6f4dabf7aa5523ce5d09be2b337ad4113e9f96b9af04c9fdbeaba76176f3efe4"))
    (149155, uint256S("9218fcf17cc33ca5e3c8dd7b40fd04d24c92a2106a6e46c299a03b4f732b7bdb"))
    (159809, uint256S("eb076fa743d0dd9da773620b5a741cd6a3381378297ff08fdb80b17bf51f3cf1"))
    (170463, uint256S("bbcd44022fd57a73310edac9d9b5527f3bf2eeac0ca06b264afb3ead2ab336c9"))
    (181117, uint256S("8724533a4ccb87c6b6b642544aac27331fd4c51cf654734e6d6fe3a72c88fd9e"))
    (191771, uint256S("4bec3772fa759dda39b3df000d23785d7d1ab23f6feffb1c4ce7ac5861fc5f86"))
    (202425, uint256S("7fcf437cf354e01507a5191ed424524ea589bb75f8e738c3c145194c8f61e497"))
    (213079, uint256S("0f18553ae4b72001f36e8648fd9402ab0e04cd69cb08a2997d0ba0b91fa2db04"))
    (223733, uint256S("e8d798c7699cb51b2e2b425b4ce37bedb575c4732b78ec821be4bada8a76a262"))
    (234387, uint256S("a2bddf0d3cc3e495734d2df6d30fbb942720fca8254b3e797daa899059b0bf8c"))
    (245041, uint256S("1cd98ff03d5b272b7ecbd40fbb8d5f63195c975c639a17947a32f789c6a9da3d"))
    (255695, uint256S("f4a59885b964da33a36ecf7aca403f8d20697f15179ee6cac6ed95746853ac34"))
    (266349, uint256S("1760c95a3c8951ad5f9137fb685bd0313867dc202da04f7ca6c7f0692d00c7e5"))
    (277003, uint256S("e9be9ba0326ab005e0124c19e6d960f0adf3927b7ef437fe038ad4ee976bd098"))
    (287657, uint256S("facecb45330cb7ff1ff24b993e267d174883bc6fe2688e6c186ff6912ba03f26"))
    (298311, uint256S("deb2e3cdcddaf6834939ca9235d53d98369c8d5d6f33e7cb0e77a6eb4f2cb26e"))
    (308965, uint256S("ec98ca7a9021a272dd9fa8c6cd9331070cbcee8f467fe4473d1bf9244d3e4f7b"))
    (319619, uint256S("1dcc96bdee696f5fef771554b97ed8cd6734c1e85d3f7ccb21f05bc3012f34cb"))
    (330273, uint256S("d59d7e4d6737ee9d11306801a20e42ed6585c877eb9bfbb1fe2b955a900f5c14"))
    (340927, uint256S("b847b41d6605cb4eef54ada410c761235de36ddd8a646437853685226113552b"))
    (351581, uint256S("bf372e4ccaacb242a803190f6703a84134c7a3f21b83e060fc52dfc98e85ccae"))
    (362235, uint256S("d06d055f3c9ed8ff8c7510efdebc28f23eefcea67656bd34b32e12da301ecc44"))
    (372889, uint256S("cf02d54f93bc4e84cd7a5b2df9db4a00141955efa135d13572c8f16c79c3edce"))
    (383543, uint256S("fa526843647907519879de01d0ae0142665d68f1a51cba295e1f24df8ebeafcc"))
    (394197, uint256S("121e5fe1b3e429a79a14b812767210b578e206622f7b091e3d05669269a957e6"))
    (404851, uint256S("c55d90a6e8f3fc524551686a5b612a03f3d9ef32b34674c7ca063fb9fc714f98"))
    (415505, uint256S("6ee50e3ed15a4c9690dcd94267336d50d1ade67de37339475e12acf254b832b3"))
    (426159, uint256S("00fcbf2ccbb88b886f43daa8ad71f3eba9743b5997ce205947aac1c5e6acce49"))
    (436813, uint256S("0ec055e956cec3c080a7220a12c7b2b234a0c0fbf21763a17b20569b5fca75f8"))
    (447467, uint256S("d72f443f9c0076b62a0249453d112add362bfad0aeffa7d59e299a3d6491d06a"))
    (458121, uint256S("1796f2cba82b63fc6e7cb81cff1195cba5e54cd488b67a87b1a702596b578f69"))
    (468775, uint256S("e3e6021b27f8ff8212d031c916981ca351eaf8795c80862449f26e0cf262483a"))
    (479429, uint256S("294d72ac8bfaeb5f11356de8d9cc2805affac965439b01213d1e2533c4df0973"))
    (490083, uint256S("fa28f613ac8390a3f155be27e9f9ea051e6e97499eb33cb1252a0c41bceefd07"))
    (500737, uint256S("21a99e14b154409a4d81dfdfac09564d889490fbfdd6d7c5ab3d999cb881702f"))
    (511391, uint256S("fb578bb8c8d369cc994d3f98c5c0c263e4dc0136445802cf5b0cfd2fc684f4e1"))
    (522045, uint256S("de7df1d2507fc022dcd29cb9e6d77459625bbf6c38020bdaf0152e5652bcd38b"))
    (532699, uint256S("b10c2339a5990c2638ae24c412c31e020785c6305fda1b44767944fe39429413"))
    (543353, uint256S("c55bce983aba4e63663d077ce73955f4a59fbccc00d38ccf66b295255a23f09f"))
    (554007, uint256S("401f0e670fd2da86141663775d9f7f50278131aa66ecac313b92c3e97fcc9ecd"))
    (564661, uint256S("db94d423e9e098021ee67212fee5bc1327e393e44e2cecf1bd3401a509fadae5"))
    (575315, uint256S("4c64fb5a7f28a5e846433f89f2bf32ff9d601ba21fb89211a038055a5044d6fa"))
    (585969, uint256S("282312e2c201ba22618198575182a913e72e88040c4c26ae900342ed5a583717"))
    (596623, uint256S("92c65ff5e82ba711eae8facaac7d0909d6d9fd0422ced26e25dc1750f965dfc8"))
    (607277, uint256S("82e88801af24559b045f0a4370246787823bfcd19489a75710dece333b2e22b9"))
    (617931, uint256S("068c6f45f648542e7a53e424928522e3033f07f19acfbd693cb4cae118477fc0"))
    (628585, uint256S("efef88c97cf903eefc2d01f88ada94c0383e0a4512ab4483b4342a7b1fb73fe3"))
    (639239, uint256S("8d1bf15e08f0b5734b5b07eaba0ebb5bae6adbb4ad415e965c938021a0c4005f"))
    (649893, uint256S("590de999710906960f2827d894c0143cdb2c8176bc3fd2bf32aee825d7c278d8"))
    (660547, uint256S("13f745cb641664763937baf1f5146eac842d2179ec3b600d6c5aa914af53af23"))
    (671201, uint256S("454cbca2186ac4d54d7ea06d9b2fce5a30c3c1ff5e0d4f836d3c13188d6b6c33"))
    (681855, uint256S("e4c83ffd3b421bc1de1144ba041b5374c5326d7078a47a46d8cedc62f6a3fb76"))
    (692509, uint256S("bbb11bc0008162878b5bebcd34afd3704b7fec39cb72c3dae07d7e375e697761"))
    (703163, uint256S("a862a160830a33593b757ad0c3d70fe404add0441255abf4037613c1c9921256"))
    (713817, uint256S("2237a01d55ed4cd67ae6b897c3e0ddb69a27358108058697421159c946b8d4d9"))
    (724471, uint256S("7ba40cfe9bf80a971476f1c6eb2b5374c19f55b91eec243d9cd63bff7778cc33"))
    (735125, uint256S("0a303a3b28290da6948fa2de434d3042f77b02850f25acca07b260b67064f3dc"))
    (745779, uint256S("1cafb5e6954ae8a830ab99b6e0b31018d73bfbb21984daeb1198ec41afb29109"))
    (756433, uint256S("3e43331e5c459b237c6e5345a3e22a71db9c7fe1ee25f947e199a0823b80d603"))
    (767087, uint256S("42ee8060477a1924337c65d4902d64bf7019d7ffdd63000de8af763dfb0663b2"))
    (777741, uint256S("f1de3b8eae30e5a92ec822ee8dc03f4005685684c8c73ac9d7b7fbfa98128a17"))
    (788395, uint256S("db26dc45f2c7164fd958da10b500d4a4d438657f6bf7cd24eba85307b8fa1241"))
    (799049, uint256S("b6049a067c567428439e9aec72a671af329b3d345a23e0f9861ed21f9960d408"))
    (809703, uint256S("f1a2a80015f43061132a631a915db54493819c515d824eb0ebacd332e926d0e1"))
    (820357, uint256S("2ae29661c09b8f8e47ddd487240ceb261a17f204d2ea0d374f356afc05a54a14"))
    (831011, uint256S("693347d5b60c5bede094f394812dc8c91fd68d1774f5da1bdeac5fd597caaac6"))
    (841665, uint256S("3c3305505a093955aed68666eb2725bd57fe246f9f312a220034c346af6919e7"))
    (852319, uint256S("d1820b0d2eebdc765c4bcc1c54e3171739c2aad66443435df902ab91b9bf914e"))
    (862973, uint256S("784d908d43d135f1bdaa80e58d25651dbc713c8387649cd2fca8d4debdd21bd5"))
    (873627, uint256S("8b539fd410bc510f4da533bd5fb6bd2d1c4083e318fcdff40061c6619862d1b0"))
    (884281, uint256S("cac0edf8ebbc6fa31b79968f59cc38891f5f3084de5234f65c99866dd3d61024"))
    (894935, uint256S("8f35e997ceb51dd3a5847ab3c6baf51be87f9dcbdfdd75c77d9850cb645f327a"))
    (905589, uint256S("cb0961d02b493ebc77afa2031e947bfcf5fb05fea006647ce0b4f031d904c9ab"))
    (916243, uint256S("db721f84d3707b89274f1bc5486f67e9ebe62d7c23368b44d023cf04d70da776"))
    (926897, uint256S("8a63c4384e38ca35fdcc2285c6461c4b2b6c416549808a4ad50ebeeb1a111652"))
    (937551, uint256S("3eb6dd34acfbc19c626e98e2459df7c78aeab982b02af9f8d3d492261b5ca8c4"))
    (948205, uint256S("1f0de8c27cffa53c96c128e80e77e6193957dc1a29ce5c77ad0cc0d3dc0e9375"))
    (958859, uint256S("f0e759c1d5d78523b14c5db11b3c06d56996c99199f05ce64c61041bb26fe0b2"))
    (969513, uint256S("07193d90eb8dbaec4f6f3c0cb148894d2049ff0d6199c670d9a676b106f54478"))
    (980167, uint256S("5075c1f4275dc730fa877440a37b6c0d4434aea700f423a3d465917b2e86c02b"))
    (990821, uint256S("9bedb37571578aa2a52286e0d799afab3d3026ef62011d4d567561e158653c4e"))
    (1001475, uint256S("1850f92519b86ab05befa77d029507c21cb07b08c23d3cf75409aa0cde07f73f"))
    (1012129, uint256S("9694e88eb0d86ecde1da92550e2f7b3dc1c9a9150e970936073fd38f190b5908"))
    (1022783, uint256S("c8103250394ae551b23d13c810115114ac4d9da0b76a313c317618f5326962c5"))
    (1033437, uint256S("9e7aaba958b7689bde8e950a0e827e3134d187c2bf662d0e270d9405e7507471"))
    (1044091, uint256S("7116d6f6a54145508d5419ee213c78557086078de1525d6cdae94aab69539ef6"))
    (1054745, uint256S("114641cca48047dd2e88b8368c58207d1d4f76ecab46f8dd8a57e122ae477c0f"))
    (1065399, uint256S("4fa091b47b944b067b122dfb09f610093a206c4a05a77159bc473bf7cc452f54"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643916735, // * UNIX timestamp of last checkpoint block
    2672818,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2840        // * estimated number of transactions per day after checkpoint
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

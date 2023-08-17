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
    (18526, uint256S("98b024cd32e7b594124fcd7bad14f3d826506ed1ca75f09d11549905cede3db0"))
    (37053, uint256S("c4bc1605ec4c4dc2a120ea2117e03c019e2adb1776c19b70a1b9bb575917b53a"))
    (55580, uint256S("3a3b63d1b224846104259609282049dd3adc5331854a43e7174a3b0fe1ca472b"))
    (74107, uint256S("ae9aa93843f9e4db0b9286f07cc4f87044609f0257b7a237fd82c96772bdf3cc"))
    (92634, uint256S("293090265288f799aa05df9336dad5156daf7e4cade5b6da6f4d4ced6522051b"))
    (111161, uint256S("217fcb268f700e1496de58f686de1f189712e07abd0ab5fc15db25d7b0737248"))
    (129688, uint256S("48cdba920d4a53f26fb09549d685c609d6c9aa02d72ab78c46c6ac27ceeae70d"))
    (148215, uint256S("2dbf264a4dfa7447fff4c5c655cb25fa101381b0c69b5aefa6520dc831bdfe04"))
    (166742, uint256S("c548c9ba0c446e5cc2015b80dfe4c22ceec0e774275631d7f57ebcf2d6ee2524"))
    (185269, uint256S("cc6c6639636806803ed63d9363e556d7aae5f680ff5da8e8f44f7d9d56d86948"))
    (203796, uint256S("927b8288d62a9a0877e8e301500340f8e2d44999d0a94c769da321acd5877225"))
    (222323, uint256S("81965ca27b2283b56f223af15dcdc33c90be1d9d92fc65d8c5746f3035983ae4"))
    (240850, uint256S("fa8ec28e288edec8fbf9902b1c8bfd8332905436f0eb2f710faf8515b748ed98"))
    (259377, uint256S("fdbd16d2cd4dba7ce0ca67798cca4e2906e91d9f2d4083b138ac3eb52a0fbf56"))
    (277904, uint256S("33fb4eaf83abdc4e82f23d3394f792552ae50f3afdd39fefc2e336e8fb849dea"))
    (296431, uint256S("6e0822d826a698a3949056a8220b76be310a4e92118c0616d8b90cdf576569fc"))
    (314958, uint256S("6f0844fb3cea558a1ad657457a15f784ebc21ae7a1b47c174db493881c20bdcd"))
    (333485, uint256S("a962341235375cb449427325717bc9b1b222f9646ba06a6b38efecc3093f2f6b"))
    (352012, uint256S("6d34ceec438646933a1e2509fa4858ce6b62b1ec041b60879e950b98fc996d71"))
    (370539, uint256S("d84a40d78b88bbbff8848f7bec7c74162d2b774a4d191f6057b3b526cb9f58fa"))
    (389066, uint256S("ce5fe4d18b7074dc1059ce4233801090d883e1639f8dc1836a8948f3e9098d79"))
    (407593, uint256S("6df3adb235ad020dc74e9b9913be2e6e49b5aed6b737069f4010c85a2478baa6"))
    (426120, uint256S("b8541c2cae9fc9c87b3b89d1a7fb54c3f5c22fb2c9592b20c42ec0b73b7fdef0"))
    (444647, uint256S("eeba786e995e29ca0461eecd2a9bade1952f0b9014f6069a9a023668c966ab97"))
    (463174, uint256S("1a07f5230048a27bf2cd8b54ac7051bcd878708bd88e16a7bc3384e8e4cb23c8"))
    (481701, uint256S("8cf225032ed9c821c09a655fbc932889f377bd5b467c5eb078025618c04d551d"))
    (500228, uint256S("d4bba3b3b25c22aeaaac87a7911fc4e43e3be0c5802b093bc6d7907943fd7300"))
    (518755, uint256S("78bceff8da783f7fe727874b355308a9fa3038f891490f82e3df24e5942cf302"))
    (537282, uint256S("3e151bda7a6cdcb0a801b5741f572ed28e52b38325f1c47c0812d98d98e007da"))
    (555809, uint256S("a11649184500dfe7a7ed27b991cb39661986a456b25cb7ebe20e431c4c0855e4"))
    (574336, uint256S("e12d45cab12497be840ed95a9e04b09dc1dc1bec483fe1ea78f571dc7f81c157"))
    (592863, uint256S("04561183fa42a7302521cf3815eac505b14fac86b067ea5912bfc1a9972c93de"))
    (611390, uint256S("2eaa210a2d803a1dd795ce938df0911cc08c774b8d2ca836c56621b854b60c5e"))
    (629917, uint256S("58f8d0cee49d804bdd1684eae2ecbe48ec766961fd606634a944ae8c1e2e3100"))
    (648444, uint256S("925e531665262825426b987e31577e09fc1d78e821d78befe6eb3272c54925f0"))
    (666971, uint256S("c42b96d216620b4e2c7a51b23961abaf7ee7e3b78e4d4608bba390f0ec0183cb"))
    (685498, uint256S("6af071c3fba10297cd30622969c7cc2214b737d8d9822aec2f2928c46a736c43"))
    (704025, uint256S("8d1b514685944a387845098a149bb7c5d983f9ecbbb96bd7cefff21c81e031d6"))
    (722552, uint256S("e3a86f22861e9c2a91ab312bb335011d5f400442d270855d9190e476f5146a95"))
    (741079, uint256S("9fdeffdbb4e434e53bb9e47fcd335067915c70cf60179e54c3341f9cfc86ac34"))
    (759606, uint256S("b9809d89947ac755ead5223e38e33afd2b743aec94360971ea12772bcabc06bd"))
    (778133, uint256S("3f633cfea12406ca9ca4a3a0e59270cb32f59c13a1ebc285771456903bd4dc2f"))
    (796660, uint256S("d4265cded1ad05207c0693c5b6491bcfd28549f9c7083299822f5da0579a317d"))
    (815187, uint256S("efc9118a11782d3b2e4d878e1771b1b485dfcfc005b816c580963fd271ed39b0"))
    (833714, uint256S("ef1f3880921a8499f02f9f287c8912cef14de1169f20f4cab5abed31874a4196"))
    (852241, uint256S("3bf57b9f751d0927962f49fc6467b9c76d5242157dcc9a42bae2d39aa3aecf00"))
    (870768, uint256S("7ae29949e5e5294bd79a23109be5ecf59beec049d0fb88864a0c98f6b565b3b2"))
    (889295, uint256S("5c4d34396de8c3b464b619d045d78e9e8e6d5d68de38044702f7bb8fd24c3794"))
    (907822, uint256S("65bea5eded5c1a21cf9f36b9ecfa4d70bfab756cf8b61188d4369033231c8dbf"))
    (926349, uint256S("0aaa59a7b1fd03635fd75f98f6f82836c1ff0303a6c8bbeec11718a7a5953104"))
    (944876, uint256S("e0df60c483df343721aa626a6721c7c448f4b70f06d7137faad6f6a12cf4f18f"))
    (963403, uint256S("442a999a54d802a477e9fc5099eb53310209495071a1d6551f0df8990f776720"))
    (981930, uint256S("6c814173164cee08fe8c433d7f28ff8db486c8fed9ceb3a6208574ed08447111"))
    (1000457, uint256S("1cdcafc97999045f476f380f9ca11e92100b25070223f26117d0542d0054a031"))
    (1018984, uint256S("17890c1adfc1d67666b1e4f55c967d213ffc8128d5620abbaac5a80d31d77caf"))
    (1037511, uint256S("48583b41b31dbe7fd671946613c42a4d2e2df34c94c2b2989214df89c77964bc"))
    (1056038, uint256S("3ff731eae5c406ea9605c55cfa3ffb49df23904a9f1541b00f4005f23f921b9b"))
    (1074565, uint256S("1673a5f63c3c2a4608e8e4f8f691d05e0c386de54dde8e24a564a9248a2a6497"))
    (1093092, uint256S("869bf64197d626b823a0d9a541061d438b039aed617a3b24b630abf57a7690a3"))
    (1111619, uint256S("e4471b2a08fe1d820d9a501101de27837c29d61efb07a1e9eb8b92ebf73bf763"))
    (1130146, uint256S("d00be1cddab8de255ae5c9c6c60c6bb91f122abeed138836de1357ea538620cc"))
    (1148673, uint256S("41111dba2bef648a87105900fc0dba6b550793812a56d83d3f04be820bf7bb6b"))
    (1167200, uint256S("e7299d0624c49ab598b1eaa60cf0bf63c3f12406454c7b5beefad1f35aabc109"))
    (1185727, uint256S("1b0deba7df2a2e8bf6a029317fc9f3722579c72700ee7cf9d3c98bd4c436e0e1"))
    (1204254, uint256S("18454222ea0890f78dde2f210555f17a1575e7dd8cdfee8cb5691f2ebcfd1f59"))
    (1222781, uint256S("2200f6e27e189eb2b73ed74c5e46a3b52ed878e7d858e649d3ff22327435b136"))
    (1241308, uint256S("a59e710819ab73ff277b89152d1f6ec624c7dadfb4ab9b8bc95199980e6cab87"))
    (1259835, uint256S("850c9e41f266fa83a9683367483b9feaecb5ca97cc83c081a21e80713595167f"))
    (1278362, uint256S("0e03b27bc4d96c1f12a370bc9f22a079384fec298ca1fbd967f27ac658f133a9"))
    (1296889, uint256S("6d3bf5e4f84cca2036c93242d4adc797a162859b6592c8b497b2de99672b1910"))
    (1315416, uint256S("9bcc2db18f7276a8890579f9d64a8d70a8d2a21177ab439b9ea6fcd9f099946d"))
    (1333943, uint256S("9620137b8b571e1c33805e1387fec41df4bf35c48e00e7be15c31664c4bf1769"))
    (1352470, uint256S("35d52dce690921fe95e0e20ec32e6d448384e70052d15d8436120767a957f86d"))
    (1370997, uint256S("3c18132b629f5da6b3ba388b92cb624b7f84f701a5351484a65b864f33238d37"))
    (1389524, uint256S("94e4ec4d617a933444b855cee99939682b4bf63c72552496e84745019bfb81c5"))
    (1408051, uint256S("a41948696a591a12cb807e932ec07d745234771a935c5200bb7a9c034107a910"))
    (1426578, uint256S("cab41cc19037d435c135c0105c75792cf513a1e920b332628b486fbb349128c6"))
    (1445105, uint256S("9171a7375750c31ff6bf4256c63bb767af052bcdd3a792db65658bb48e682972"))
    (1463632, uint256S("f38cefccc50d8982ccb82799e481528bfb902989de8514d83c096f459f37d9a1"))
    (1482159, uint256S("40ad369a19cf66873e6a1544bc9dfc5c99318cac4a1f6b23d073fa930d062d39"))
    (1500686, uint256S("6a02f4338fea4045d178593ee3ac022230badcdf31f42c0d95d8f339f8db010b"))
    (1519213, uint256S("fe8bb74c1c001d0763c79cca8e2c6bb19f59439618509060d05c093a74017b93"))
    (1537740, uint256S("eac06157f03b1753be8288d0e45abd1033c1e4cdcb7d73656e43fb341f7ae461"))
    (1556267, uint256S("b501403f23c76a0e3eff138e31abf288617f5d475e6a1517ac62f4d97fd5242a"))
    (1574794, uint256S("0d7b774109e284ad17f3125fac700ffae2e25b830d927b5068e13577f4dee049"))
    (1593321, uint256S("6cb0885262e44c43e881eeb4e9b1e20fed2f3c4d30f92a2b9102d353664082f8"))
    (1611848, uint256S("36deae213749aa12548eaf82afc1a5436ed853fa2b355825da2dbdb7317c8873"))
    (1630375, uint256S("6f3b457eb78584237dbee40815841ccb0a108b03bff2b51900ee93f670ae543f"))
    (1648902, uint256S("046da1cc8340bf0c3dd26034827c614a5efcf05b3c4218d7f9e31adb362fabc8"))
    (1667429, uint256S("f9837303424fbc9c866d1c9e791be2825cdee7dd75b38eb738f029b3fa88a1ec"))
    (1685956, uint256S("06466101dd48b36a1d55d3f9c40845c7efa660b86439802b4341bcea60fcffe8"))
    (1704483, uint256S("5f9fa7df6f8dc18ccaa5f7e8e5e45e6cfd538717df90b875ec2fa3a1cd2a1a59"))
    (1723010, uint256S("a1ddbe4c4f8008b30ae95024e031718d8fadb59ea888a31dd128879c4960251b"))
    (1741537, uint256S("77169a40a67498900f075dacbf177ac9d507786ad32374c48fd5719790508739"))
    (1760064, uint256S("1e0f3d455d880017f34d3538b4133cae543549e147d06654b73708ccaedd4aa4"))
    (1778591, uint256S("8ef471858450f95b55a736592403385e046b2578676cda6dde2f7aa9c9bf1863"))
    (1797118, uint256S("121b890029fa92be8494f3e3903f0ea15de8455025ce3a2361bd5ce92a512827"))
    (1815645, uint256S("7f7640e902bfafb961fc61a128cf0c0cb8ae2e9ee9bda8b0c04ddb0750aa8428"))
    (1834172, uint256S("7cb773e0217c40108d40adc6738916987611ef0d30ef94ff2b384f9bb72203c6"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1691134890, // * UNIX timestamp of last checkpoint block
    4347153,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2828        // * estimated number of transactions per day after checkpoint
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

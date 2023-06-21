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
    (17728, uint256S("3fcb6d0d582839fe4d8eaca4ef1cca7c034c71009ac9c99041c79208f53e00e2"))
    (35457, uint256S("6d9eda87adcc025790bd8b1518433316c5a13df064d5adb683c1bda77d1db2ec"))
    (53186, uint256S("8daae39abf4e3c79b6e37ff1fa8eaae77b48beab0583e16c0e3d8beca3805e12"))
    (70915, uint256S("842879b72268512fea7d440bf1bb145f28e37045b9ca058fd9c45a72782d6f7c"))
    (88644, uint256S("5a6ca247a1c7007b1f191f6f6370e124827bacf83ed220024732fadae329f268"))
    (106373, uint256S("3669e97421fe042658d26b446624c2a157ab6fa643cd19e2aea2c5276a98474a"))
    (124102, uint256S("f032ad3937a102ec2a6473a423e9cd314d32bc2e727f44341de0eeee453eabac"))
    (141831, uint256S("0c35088e6c3fdedd34e2f8d88a8accc80dc2f27d155993164b7be61cc8210621"))
    (159560, uint256S("52a9d8a2b9969b11029ef084596960fe59ebef1e1e533c90d36280efb696e4d3"))
    (177289, uint256S("c175b383b50aa419b1c1965896e605404dd6f8d550b701fca1828328d5a576d4"))
    (195018, uint256S("ae84da5d35e2cf98a3309cf359f2f98e118a4f52a13345f0558b33c2ecd052ee"))
    (212747, uint256S("9032f648532e30248f851c6461a2716e3f9f2c323d2584bf7ed79559371f7815"))
    (230476, uint256S("92534a0589f715dd7b5eec1d5d482f462bb37277a563d71ffd28dd17940de093"))
    (248205, uint256S("2bbcd95e7023866c48b7771a39cac00e5d5f8be2e041b5d7831deb2cfb272db8"))
    (265934, uint256S("a682c31cf5e2412aba942733ec531f9a01cb8ddc92cfd7b10e46cf523272dce7"))
    (283663, uint256S("83ce4f9a4521bd3b4d529ac4e4e3f32444865097a5e0d55f7c1e9f047bbf06cf"))
    (301392, uint256S("42b2b391034a832a735d18db1864c2144905564a6e5164e1b31bb3f92347b0fa"))
    (319121, uint256S("f332a87dba280288a18be2456daef5a41b8abac3657ef9d22110aa87f0d10f7a"))
    (336850, uint256S("b08bba699bef7d07283aea72160758de4828373c4fcd33c374c96561d0a86e23"))
    (354579, uint256S("38028f29b81f81218f3142484b07dec879d601ffb6fcae95d17eb5c72d2dbee6"))
    (372308, uint256S("5cd5d8cf8287188b04209a6a5d797e6c93d72ded227d64f94d29a0f8c5850e69"))
    (390037, uint256S("d972799132a27088d5726a79a6a26adf09edc116941795e97bc6aa783639f281"))
    (407766, uint256S("58077e48248638eccac28d02f2e80b6f393492a2fc0e2edcad8373156190a451"))
    (425495, uint256S("00aa12cf4faa2c6301c8ba66466d4a239fdbdf80340d5be2251e6b774a278c36"))
    (443224, uint256S("ce391dee43ed66c01a4296f3e204cc434ad723ed539d4938b84dabf6acba33e7"))
    (460953, uint256S("c36d421a4eb5e9cade3f90d905d9e8c586ff2b62751912473b812e2a1fd1cb4a"))
    (478682, uint256S("49d31d09031c66466669a6a9bf3fbbd77478bf6b979b73da0d79807cf727b400"))
    (496411, uint256S("1ca9ef6102f95b5b6fb7c1ff69e875b7756f2c889c5a1e0965309f5c5331520b"))
    (514140, uint256S("c105fed2e18c2e9f0db8bffb184074a1e5275cab1e5fe67d286b444568e99d98"))
    (531869, uint256S("b59c0da52ae57b9f503aea076a719db7d9904bbae2035f43c727a59ce6b1342b"))
    (549598, uint256S("6f6da0d51feb75db52b6b3d60e34bcd04a35fa93bd8545148a1e7930a6fcac92"))
    (567327, uint256S("3d19bfd7a5aa84b01d78e17ca4d2d166333626f5f0631242be0ae11395cc612f"))
    (585056, uint256S("ea9c48d15120abfafcae0745a97f28ea0421766a55f95217f2805df67097b4cc"))
    (602785, uint256S("9e7880d27304c02b32b9005fda79c8212640392e9394a32e560a8ed5cbe64456"))
    (620514, uint256S("c2e6e2676ad1067138ce745fe601848152628d691b393631ceaa369401fa9286"))
    (638243, uint256S("0a37e8982433ef2ad8d8baff307b7751e1908d2ab0c1d36b76b1a56dffcdb5a1"))
    (655972, uint256S("ef8fae669e6e0eed62236529d22af39ebdcd37a9bb2421cb5bd30034e5cfd446"))
    (673701, uint256S("a63a28e548eed240455dc6890bf26c8bc536f905b2e875ffef3440557cd39076"))
    (691430, uint256S("37db74e071d684c1edcf991a8643a2c6218f3dee97128787d5bad0a3492aebfe"))
    (709159, uint256S("2b5f19a0f27683627dcef26712de66f64bfd673612e2d3eb5609c05add07bb62"))
    (726888, uint256S("41ae81c57c3061baae4f6b37122f1d6efc93a8be1faa3687441b4d54a909e580"))
    (744617, uint256S("b3a3f431547286a6479b3b96a2b8bfb2cfa2f3dbbdd25eb20d35498f4f39a497"))
    (762346, uint256S("a4313d4f200599d1c7e2604d48aa594cacd33c186651f07137fb6a16989e9923"))
    (780075, uint256S("094b03ece63085caf72bc95a6c9743c9c2e74cf4e5e14d981cda5aeeb0ee5c6c"))
    (797804, uint256S("3d11bcb9b380ad8484f5a8016e42cfef36936e3a5767a7102c7fd897f3d923b2"))
    (815533, uint256S("56562404a9d907a6e9e2fee960871a1afa11e5f243dd38215812aad410f85286"))
    (833262, uint256S("4ff3b054494351e16bf9b801f2ed83dd59f36f6c6304134e991e614aa9f3758c"))
    (850991, uint256S("a2c0e83375364ba3a0459e369859724b22294ac05de28ccfd73c541264b8912d"))
    (868720, uint256S("456a9312d7f3101b4518f9f4092e4af390b8786158bcaaa770219f403b65bc38"))
    (886449, uint256S("e28e0470758d6b7bb32b1b7c8309c8f987f82adbdff7d52f5ac682613ccc9e68"))
    (904178, uint256S("a2846f564a50f8a7da97b293bf0357ea3a97dab57115979115ffb69a81a0d35c"))
    (921907, uint256S("101711ebb6fa3876682db3b3cf2eb88a5b38916ce7b8883aeff10db91e30e7c8"))
    (939636, uint256S("dadb0c4d36d0baca00c07cf0fd9ef80d5f945bdde9bccd597c5621f50d73298b"))
    (957365, uint256S("1bd26137a1076bf94e5c3a40edf7872590ac05665b2895567fe3b3bf0fd690a1"))
    (975094, uint256S("f31e65653e4b4467d379459533b7e5234ccdf05b4ceb0dfdbe1c807fc648319d"))
    (992823, uint256S("39a3e87152ac9a0ed405ebdb3e4c0dbe9fdf0759e891d89384b84fda225cfa84"))
    (1010552, uint256S("c42600e9fa93e2f9accea0a47e9be3580eb496aa31d2418615d6699afd622736"))
    (1028281, uint256S("a2dc00c903929c19656c87436f7b0bc32d4ac7c8d4043cc6f930e605c98fd78c"))
    (1046010, uint256S("499064e5e9b5d13a2beb610dc4092d24e1b63dda813fac2f6544f1efdd6f0e32"))
    (1063739, uint256S("55c0495d9686baa4d51c4a7279f883a4255413c0a5f272190a609cf898ccc591"))
    (1081468, uint256S("fb18641e7b787c514b49af3b76090228e85360ed531c2180e80f75503a81b8bb"))
    (1099197, uint256S("b81797f1ec934d9af52169045ce0f235e9a56a8de496653718c20ccfb65933ba"))
    (1116926, uint256S("067923f2b65b95942e90ec62daf9a6150bb061195cbd6dd6776c0edec4491464"))
    (1134655, uint256S("4fe8cd47c997016dfdc33de2e63a6e24d42437b2ba3679497cbaf475bdd79d36"))
    (1152384, uint256S("8fe2319193111e5e3ebf87b57b11da5a664aab876e984781cff339ee69983237"))
    (1170113, uint256S("d59282b72173cc98ae9b338a01729758f4d89e87112889d671b4837254d37edf"))
    (1187842, uint256S("3cdc1277ed94cf74d7b2baee835ca5df8941c5d1df5a3d08be1e2a33edc8c524"))
    (1205571, uint256S("1e0260623ab56f3de68c53877fdaf47c7e0133ce003cc48a393bc2c9d5f836c7"))
    (1223300, uint256S("174be43fe48a3427f3bf202a7d3b51dc572c417244e0469bdf896be8e9f53a60"))
    (1241029, uint256S("1b7debf9a2c7b2da2314244303fa5f4a3b8b4a5def485bc3c4fe623a120e7378"))
    (1258758, uint256S("67cf521e3e78bf4d93903043c2a7e6627c525e8b2bc2c34d76792e42dd27ae40"))
    (1276487, uint256S("f49158b0a90c8d799735c6713e9f10a5433063da89a08ee09ec991fd35409378"))
    (1294216, uint256S("639285bc31777798a848a67bcca903fc562d887d81d40cf63a7e8936219ee00d"))
    (1311945, uint256S("beef5ef4d1c39513f3cda2e29feec0dc4311d480730e7f99f6c055cfdff165af"))
    (1329674, uint256S("c1b206f48c6ba8976b1fc10390ef0414885fa2a0fc35b29bd56e04b38dabc462"))
    (1347403, uint256S("bff22cd277972ef996113f54e0c7df9c2d73d8106d5b8f4f80344b5d361729da"))
    (1365132, uint256S("b8fd1b56a40bee8756154b79be2209d7b5234eb254e8e900015db468cc74b03f"))
    (1382861, uint256S("628aa7eb64eeedb15f2aeb9d61addbfd6a05cbe1fce6e4ff7db650cd0390c9a3"))
    (1400590, uint256S("08617562066c5944a74c539e47e88415358f1d73ccfd71e108a69f0e7fba3873"))
    (1418319, uint256S("3a8a830f6385f8cc7e40923977900e3751472a2a133387a74256d6d17c855c60"))
    (1436048, uint256S("cfe607d6e292067da979fa87672dcd8f84bd168209a0cfd8c832b37c0dc3b09b"))
    (1453777, uint256S("0166335f27e90bd2a7ab56a0e995ded80cf4444b0567527e272d72ea342669a1"))
    (1471506, uint256S("5eb46acf192075ffa57c6c22bf1a688af6afd2cba2fc50df133fd14533c38e7d"))
    (1489235, uint256S("ec18b78a2c3037cc2d08f140d242778b3f74cf43878dd2f66945a5994d572127"))
    (1506964, uint256S("c012b6cf204b0d77e65b989b518c4b3c8e888f2fb5098591c4230646af2bd4f5"))
    (1524693, uint256S("f8c9896c0741736804d36f8a90ac52cf246feeb856fe8cf780f0b54b4e198fd1"))
    (1542422, uint256S("73ea099f5c36185b604a3d5c6bafdf1fe8949678d959df025b5fa99945189dab"))
    (1560151, uint256S("6375a36a0e7835008d8a89795a375230829f58e1a83e90fd3a55314990159707"))
    (1577880, uint256S("f84a7726e206d4ebaaffd5c65d7e7bedcea877c5a4e5d72c3fdd0548ff2890d0"))
    (1595609, uint256S("6e57fa98e4c50f8fea468e712cb72fd48ce26abec762a80663fa16c0b8cf0895"))
    (1613338, uint256S("7032b5b057fbe2cd3231e8b9b9574baca2954dbb1a0c5d293d22d7f5d26ab6de"))
    (1631067, uint256S("9bca798c15b7b7dab569287517b2c24ac14988447f8fb24152c370df324f38d4"))
    (1648796, uint256S("87c6eff5d4689d856c918bf484875446175f91a46c2a2100d3e8398a015ba88d"))
    (1666525, uint256S("47e575826278eb7deb1ebdee0a9e53d823449ca2c872cd76ce3630f076d7ecbd"))
    (1684254, uint256S("3756647d54389aa29ba18a0fa99a08edb10b676be2590e406971c0a1a2d78eab"))
    (1701983, uint256S("8640e9768ef7c414c23d78db453b6478ac7baa25703514065afb2519d9ef690c"))
    (1719712, uint256S("df71a6c1374d976f886c333d627da1ad7b6cecace97635898f1f407227a07afb"))
    (1737441, uint256S("ed0bd3d9f71263c8f5f120e22ca3e048b76fcfdaeaff4ce13bd2aba4d3df64bf"))
    (1755170, uint256S("9bfdfceeb8fcf7704fac6cffac4a971a34da42bbf27017d0f6a3c78cdf3fbcf9"))
    (1772899, uint256S("5d7d30ca8e77c0a83328b31b9521719dd67570f68d88af692ec9157e6ba8d5a5"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1687371495, // * UNIX timestamp of last checkpoint block
    4222342,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

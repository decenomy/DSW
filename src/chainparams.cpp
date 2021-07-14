// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
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
    (550, uint256S("00000000986f3dc8cce21cbb153a88fea4d825887fd4c40364361f92d0929fec"))
    (1103, uint256S("6b7f76c5a48d25c26d95aae1d5aa567c81171ac2fc9f667daf44d825949f15bf"))
    (1656, uint256S("c4f7f1fc103cecf44583dac95c74b62b54b4e2d48bbddf677faa0300b92c9c12"))
    (2209, uint256S("c851a34be466e1a807a54c81820ad8258a34fc4dfd76597567b993f81b3741ae"))
    (2762, uint256S("4608a4a961115ac1e827c6c3ff097871b8d095fe942cd287e293a35120e45d2e"))
    (3315, uint256S("0e351614458c6e28cfa1c29b63ccb8ec36f38dd5f767310539a3873f657944e3"))
    (3868, uint256S("45c8e6397dcc3aaa1f43f89143084bd6c626f66d1b65c9884eaaac5222207bc7"))
    (4421, uint256S("f955baf6af4d664ffa610a5016a8caefdf0ea057742d5b931f69e3bc48488364"))
    (4974, uint256S("2d80c5edb768c54c9a243a97fc123fc8950076147bdc24f7636d4f3b71b59fc9"))
    (5527, uint256S("ea806ba97976eb721f592efafdf22c2558d20f99f5dc83fb14bef2d714066687"))
    (6080, uint256S("a194bdc8653bdb4b96e40295753ce76f9377d00b0f97b81269939714d42b381a"))
    (6633, uint256S("c0426c12bba81172d9782ce009b478f15e812bf9598050c87ed004509e5805bc"))
    (7186, uint256S("025351dae16a560ba03f55867346373819d88801f3e1be4200c4fb2ad1171041"))
    (7739, uint256S("e6c6930df2046e0bfaea39cf287cf55d62f34b5d326628f19694f1807264b3ac"))
    (8292, uint256S("225174d7b5f1c3d2ac3990852adc10347fa11133e5f853c00994d50ff5629d7e"))
    (8845, uint256S("4a1edfe4804435de1ad373a15bb9143a9976f1905c1cd66e6c16845684cbcac4"))
    (9398, uint256S("f567face229f4376528c130f0bdf0b16fda1e9ca32136e0b01fc99687eca3461"))
    (9951, uint256S("452b47c89fd335cbd7c8efd71bfd1eb4e94a1912b03bc543a18e82d32892fdf1"))
    (10504, uint256S("71e7b332eccd80ebb38c6f4d2c8b004f68878e35997611a696c9d90f6b8395f7"))
    (11057, uint256S("3570332f4d32c90a2fd3f35b96b63e651af71b1c9c149b4df122a99b93b9d61b"))
    (11610, uint256S("7698df67059d97a51dd214c4bf57f571b62ad793f4854342c684fe843e1e1556"))
    (12163, uint256S("72c202c42f04a297f656f2d467f614a520649198574443bd35434043e53eafc4"))
    (12716, uint256S("54d476d70f06071f56dbf25ddf39c3376c687691c6bf0c6ff42c3a1025bf6da5"))
    (13269, uint256S("ba46c0874d7a5a63ede7a07074c407bec12af1fc7fda3ceeabd32b42cbdce5cf"))
    (13822, uint256S("1629e323b5eb1aaf7d5d77ea6a594cfed929c0746f4678e96c4616db79f9d681"))
    (14375, uint256S("5796f06dca14f3d1483230e9db949e479b3c028fdea4f692180d196abbb7aa92"))
    (14928, uint256S("4c93b86486a62e1924b1b6db3f34a52161cd938cb1a03d16bf062b2a64e6445f"))
    (15481, uint256S("a74dec6caf8446f32e33f0e41b1c8ee138e856f67b350938cf07892d282f0b1e"))
    (16034, uint256S("3168bffec1909043b9e92e90f09f59f6f04b6b7faf5257c570d20f74e858d0f0"))
    (16587, uint256S("9bffb3d9bcc376cd9fbca45f62ef9d5dd541e8a17b575efe7dc9ebbbc332dbcc"))
    (17140, uint256S("04caf7472925284899e3240a9c9c53d60e64459c0e4254e11ea073a8c00f3b4c"))
    (17693, uint256S("2bcf0218929565dda51ce141b70257e5619c0e2972e50b8af9968e0624000822"))
    (18246, uint256S("e5c23a19dba12c40635b9427de54191c80d4141bae53e256e1a50c0d88e31628"))
    (18799, uint256S("ab55151d25893320d3acf4425eeef700fe3a26ae8f14f5d303a66dabaf4ec399"))
    (19352, uint256S("7559be76ed8197c2e915e75324964a443a021c4a8e4126996ad70266b4f5dcff"))
    (19905, uint256S("04989c07a69a7a8623eb05012d22a0fb9f6b0ffa2b2873a75757afe5079124a7"))
    (20458, uint256S("57f2b08512bbcdeede855d6a122a40b8853dab0f241d3bb7d14531841ecc70a3"))
    (21011, uint256S("452a6a985be9eb6aad6581ec26e8ca23d1b80e26496c7632fa587f6753f96a01"))
    (21564, uint256S("79cfdc2b95df65fad4026facfc2fe893c81995a994dbf5614b31006fbeb96e2d"))
    (22117, uint256S("529db2e77a570eeb1cbdf140515a8d7dd2d502a2ec3e203473628e0b83cb8134"))
    (22670, uint256S("c255dc5e15b458a48e35cf6fb1090cf4dc41b20594419e904d3ffebbd163c2b1"))
    (23223, uint256S("a53823bb942f6fcdcdb6c0181baecfad30d6c3a02939e42d3c67aea4895e5201"))
    (23776, uint256S("6bd1969b266198f4b28074cda6d689b105fab13b07794f5f47c46436d1642087"))
    (24329, uint256S("3db86e665f7560ee8bb58fef490705058e6ecd4b6bc1c31dd8f6e948db69c9a4"))
    (24882, uint256S("439e41611e374af9a4a244966f6d8fad7f7afba595339a50a190266e7f51e3b6"))
    (25435, uint256S("701135a391797c175ebc29546d24f143f9b6d3329a84632ec0d8075f81c2f4d1"))
    (25988, uint256S("b15c67ac078a4c733f20a1ac3e6a0e75f16ce2ea3f87b74634337ad3ac87e4fb"))
    (26541, uint256S("9419d1550d5f7b334975b919d3bb6f5866d80b28e0b2ae1bf32762ce4a5f542c"))
    (27094, uint256S("a88e1689c3f86894cb90e2a1f48a0ac258f8c61ed9c849a5f04a39935353f3f0"))
    (27647, uint256S("28b54cf0ea3cbb9cf792c460e831faef18978d04eee7161c057bf1c13bc7bd25"))
    (28200, uint256S("b5a4c8dee429822f0d9d8c608d024301cc5893715de3d3ad17962a5af35dc2ad"))
    (28753, uint256S("69f1da4ad12b146de48a8f0356fa89f9871b1a1f94cec42f8dfc757c625e48ae"))
    (29306, uint256S("37f28b67052b006a2be65d136ad296cf502b32ccaa3f36666c8eb2f155253026"))
    (29859, uint256S("fd553a30855f8aaef587f877f5cbb38138d8e452713e5c707f0352745d1bf3f0"))
    (30412, uint256S("825865179796ad62e138b4ba8a524f4713b279c40c219339b84aedc2435e93c0"))
    (30965, uint256S("0059becefbbc0d9acb638a8a11fc20c34b9479d4a766cb179f4087b0aa448963"))
    (31518, uint256S("4f9710214b88c5ab94af62451ed97eb3ea137a62ba0db2db54912bdda4cfdecc"))
    (32071, uint256S("de1ceb5b3cc509323554a7ab26b5f6820c6667539c6aff507c3e763e82a8d30a"))
    (32624, uint256S("c51028e6ca5aba93125373a0cb1fe40c272211a1784f08ab8558b66ce8d0fedb"))
    (33177, uint256S("1de726a1940d16fc09e5cd450fee8c96c3b8287235872911648a001432105544"))
    (33730, uint256S("0c2e43b199c2c62d1f999c1623345cbdf64bc8cabb9a3b31a090927b00e745b5"))
    (34283, uint256S("29e2a30f4b1b569850f0f6e3f282f91a3405ca73430b81519f619ba4f058dec0"))
    (34836, uint256S("70c2eb63389d777da4446b67e2f428eab56c1e7a6319049b93b4b6ec25a4b814"))
    (35389, uint256S("5d985734df61f363669f24a3754916fa3034d099094a84a2d0bb60164d279dc5"))
    (35942, uint256S("ee4407d587d4da98161c75228180a9f1e5328a72fc64e6c86db8ca1b731a8b8d"))
    (36495, uint256S("ffd69f76eea899c37fcd82026588c9989d15c75b11b6dad0993e0d7d749856c6"))
    (37048, uint256S("e8e175466fed8020e7815a514b72b76254c75416eaffabe1f3513d1ba762fe5f"))
    (37601, uint256S("7a7dba2858a10a9b80e8fee09470a619be7b32fba67923e8f6f93b57dd347d49"))
    (38154, uint256S("e5350d91d9690e383d2e2d5173b7bd4601e6ca9fb3a06fcd7ac82e6ad4a00639"))
    (38705, uint256S("60039ada0b4dab44d47b386dd870b7eb39d5f884e7a4bf8a6926b2f0e0c70f57"))
    (39258, uint256S("dde354edac93accb226795150ec5b45fe7ac85c585c585993b23781a4ba766d6"))
    (39811, uint256S("2a82ad9911da455e48adf5db83fa61c1d79284f9ec77b1799090cf6c9e62a7b1"))
    (40364, uint256S("87146106e22e572f55c01468ab089f82398309236d867db8474568b3d2d95103"))
    (40917, uint256S("1263f35ce11f246bd0e4bba1438e08237baa1963bf6011f3b263f984d2fd47c3"))
    (41470, uint256S("aa0afb044b3f07598cc4db610d5711f1fa2dea4d96ac18fc9c52835ca6820608"))
    (42023, uint256S("47045257955c310f906e8bb29fb1d9d4f75631c0b525cece95bc991849086aa1"))
    (42576, uint256S("d667587931e912f8b64615fbbf8907973d8ab885cdfc548e174c6fe04a1a22a7"))
    (43129, uint256S("ddbe4f65b97773241ea8fb10b4b541811ae83b44ab21eef253478ed1024f973f"))
    (43682, uint256S("43d6773953288bb3de1e16b0e3fb097e17f4c0fac58578b5294e105d94d4af4e"))
    (44235, uint256S("bc9bc57bdc9a9782f32a0bac9ced544b0fa7d8944d085c0865c8511683e5c575"))
    (44788, uint256S("c2e15ececb3c1d0f842dfc7d7ccf2a04b400177d098c8556286549a64c561ed1"))
    (45341, uint256S("26723a410f096e8d9db64b68d96db2e805c2445cb2b2bcecff23f73a47ab5600"))
    (45894, uint256S("2a574f11cf935fd782cf2acdd176c5fdb84812acf7d85d2e32e726f4f4b42ed4"))
    (46447, uint256S("d3a5da9dab3608d392f4e27f54b6bc8f91b01cd41321dcd5198f454308c68721"))
    (47000, uint256S("7bda54bff83d3cea4dd82bf1fe1327c9794e21f2f3655c256dfe7fda33929fb7"))
    (47553, uint256S("87cf97a242a25b50d4b67062a8d110da9df8f58b5b79159e24987a0ccf11de40"))
    (48106, uint256S("76efbe85e1fad775a756b3a4983c1e5970fc32be32e4a0fc91229e25953ec282"))
    (48659, uint256S("8e42488a37b7e8b7ef65d8f8b417cbaa9b1c4de3c930c02866e27b4f91b64db2"))
    (49212, uint256S("55151bb560e38acda176b6df573629774f69021241d1f9832dd73536de7a83bd"))
    (49765, uint256S("6b5ed15e14edb56a7e9860cc962a24dc9f92b52626af55471e3f50f53618bc5c"))
    (50318, uint256S("1a49c2f735b508c4d5b379a8b0a89b0951d9ccc3dee25a4852e5c4b3723a872c"))
    (50871, uint256S("8689a982b95e2a8b6efdd798271506c9e1b7efe4cba1729962d2ba8637cf613c"))
    (51424, uint256S("52e414fb92f3ee2bc18d82ef44faeac495cd2e8814a89cc4884628b976a76c78"))
    (51977, uint256S("a52ba19e7bb2f0487a00eae20b230e1210c8513a8644e68c53741c51abbbab38"))
    (52530, uint256S("6ac8b3ac225722e3f434e95479ee881204b2d5b7ce5bc8f4a823f0d5386ec056"))
    (53083, uint256S("975b75d3c0d2e81c4e8df86498454c1159168ed20aeadc94c40ba4ed738f2caf"))
    (53636, uint256S("b9cc29b0e5c68c9f8eec11824442fd6b8c49f4d33d6f8977ae895f3d71323c86"))
    (54189, uint256S("c87bd696b4637d4659b70032f087c449947f06e7493ea06638fb6dac38b53971"))
    (54742, uint256S("b37826048d7da5836adf783ebbeccca45aeb6db9c5714d9164386b55e29fc040"))
    (55295, uint256S("4146b8190131ecd9fccdf9451548ccd93a6ac5af9610a49e5a680fff312d9ef1"))
    (55369, uint256S("4b0650dcc5ec47625e9581509989d60c8a778c41b4a21f597ce82f0fdd508b24"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1625942775, // * UNIX timestamp of last checkpoint block
    135624,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2880        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut =  1200000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
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

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint    = DISABLED;
        consensus.height_last_ZC_WrappedSerials     = DISABLED;
        consensus.height_start_InvalidUTXOsCheck    = DISABLED;
        consensus.height_start_ZC_InvalidSerials    = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck  = DISABLED;
        consensus.height_ZC_RecalcAccumulators      = DISABLED;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1893456000;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint    = 999999999;
        consensus.height_last_ZC_WrappedSerials     = 999999999;
        consensus.height_start_InvalidUTXOsCheck    = 999999999;
        consensus.height_start_ZC_InvalidSerials    = 999999999;
        consensus.height_start_ZC_SerialRangeCheck  = 999999999;
        consensus.height_ZC_RecalcAccumulators      = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0;                 // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
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

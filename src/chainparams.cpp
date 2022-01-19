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
    (746, uint256S("000000006af06e819e6a7eee9d0fb104257d549cce1f63d57c8c2a08eae7c964"))
    (1493, uint256S("9f88a58502e1801a23f5f8c365feee070cd2ec9cd1291b0f3db58cd8d8705b29"))
    (2240, uint256S("60ddaee8204a404a041908222e628d6d956ce647df534be94caeb82bad6a9144"))
    (2987, uint256S("31d31b4cfaad529532d97a5b803e32ecf9b97fcd5f4e7f994d729c6fe7e86524"))
    (3734, uint256S("ff7257411d56b08696470fb7972bdfa92fd1c72acdd07ebd4c385213690a7071"))
    (4481, uint256S("4551b52fdec320e97a6433358a9cb3f82c2e1d42526bf12c4c2c30cd51776aef"))
    (5228, uint256S("f98b0b23e8ad45be5cf2953e8deaa4643169f3de32e66fdeab5ef2828a5957ea"))
    (5975, uint256S("f005634712a4aae52ef3352a41b974a025844bb107c9fcac9b6c5098937bd460"))
    (6722, uint256S("dd9070feac5f162aa0fe2230dafa2fc315deb544d20f2d29e911e876845d8348"))
    (7469, uint256S("3838879ef3f2018cd9c0b6ee90da4c59c3a8e318d3d26eb308bdf9de6463caaa"))
    (8216, uint256S("fad3f37a22ee019306629a41e56bce9aad6e0e10a5e1a15830588ab4e4a40bf5"))
    (8963, uint256S("29ea21654d64463d84a8fd5dd26951dd5e6ba0a9e1757b94487b5efeb262c8e7"))
    (9710, uint256S("1305f115614494ddce6c34873f4dff39559d91e9a59e8fd615171f9132877430"))
    (10457, uint256S("4e4f911ce8d6c6190140eac1b5405c60412b63fde2d7d426dc3e97f4f4e20064"))
    (11204, uint256S("2a81451e7db79e3c81f4b653b77fddccbce0a7644a57ca66d7ee03cfe6a50bca"))
    (11951, uint256S("a1c7cd0d85726d3b1b40016d952c795620c18c6b9d34343e24aee255ca11feb2"))
    (12698, uint256S("589a1c29626129ed8031e4681769fdd68b352afdacc29950f04f61d0dd7d5b58"))
    (13445, uint256S("9603afb0228e59fbddb8a573aa19a45372e2b3aeb4644622bf7e5238da9be1eb"))
    (14192, uint256S("6184a320a55017f0bf5f4222d0432b7b7cfb6f334d41912cef4041e47e8da1d4"))
    (14939, uint256S("43e14f0edf8adc8589d6b41a7f9a92c19e125342b6a86c4f3397b2fc2ea50439"))
    (15686, uint256S("0a1b4a23ba9266d857a7d1cca29c41a97efe799a3d207eb49cd9af9731a81c39"))
    (16433, uint256S("5ca53ae1801e6585fcf0e156a0df424c15c6da2c3f43f2afb559c2c9859d5244"))
    (17180, uint256S("fe01cd811e7d0f0a772d83b2207f5842107a68b408886a7c2c247dd8dffc3d6f"))
    (17927, uint256S("33e64b2856e7bcfb9c2934265e4e27f5b13192d76fb44acecff2953387cd602f"))
    (18674, uint256S("1051673ec0469ac00c06263983169f77f2225e60c037a09af5bac1580f6a7322"))
    (19421, uint256S("b36688a298979630f8e6d57acaa2cfbd382c579db44ca11a04ae5dfa5ba01833"))
    (20168, uint256S("79549098e3cab611b3b946cbeb36a5b4981d6fc0301cb97f599cdb00fb4cecdb"))
    (20915, uint256S("f8df731174d59585b444c7e6586745554be82bff35d28ae758716836738258d8"))
    (21662, uint256S("33cf6c567f10cde2fbae05ecc73a46e34ccac2e34c7ae135edf03eb21e7cc9e7"))
    (22409, uint256S("43b02235fd8dd557dd86d77943bbc341e2cb3b69a0b3ee72493abcf50bd9a5e5"))
    (23156, uint256S("3713f847402240fd58c1f33ed94bb1efaaa33829b32cc17fcfe5a14c1d3d749c"))
    (23903, uint256S("58dc51b475ada0636876bf00e68425ed0b12c12df0e3812925044030b8c2bd6d"))
    (24650, uint256S("81a50625ea6475cecfecd49f566213f077ba676a89d94b414d107d640aa6a89c"))
    (25397, uint256S("72be4ee9dadd637597f2dcfec2ff058ef6b998aa1bb18a8de451324c22fbab20"))
    (26144, uint256S("95839feae1b4049266c76aab4b1cdcb67c6c54dce39dbb87e90a4f761dafe62d"))
    (26891, uint256S("53c7155c66dc76e9332702e1bfe2da2a0e18aac480cea4b03a7099be191ff854"))
    (27638, uint256S("1956f976808c2262112935c9bcebe3e6a37844228c821f807f144b6b5e8d2e1d"))
    (28385, uint256S("9b16cbdad2c5b5735137df9efdce777433406eda5ac446e3988b845c6c250c85"))
    (29132, uint256S("cc52fca250ec0ccf1b67d77d681443ccd0a31a687a191b8cf2da8321f398157a"))
    (29879, uint256S("e5586d43cea996d6679969c3f3e46e15ca67ca93217223c3213026c533c85fb2"))
    (30626, uint256S("bffb0aaaa1a7c22a7e4495f528393b8bd8ae073b24d8728365fd8c386cb44f08"))
    (31373, uint256S("15334a881965e18916bcaf8c5aa5d636558929051a8625b946d5a55ac65d4aea"))
    (32120, uint256S("f79fbc02cf884522d1c63a08ed466223fa4e870af9d36b8f54d76b2372ffb998"))
    (32867, uint256S("f6b59de4c8a3d4e6d0eab66a65e949066e02d49142c1e656735902e782c63ed6"))
    (33614, uint256S("6d549b8688558068c793698ed381f7bdd07605a3f5f12b4f4e88dedb74e9f870"))
    (34361, uint256S("48e5a916046d868b182bad3e28bc62bac29ea09b14e5890a8d077d95c5fd5d87"))
    (35108, uint256S("eecb44197031557f89acb7df8e908af5e457b99af5b0ccff39fad44e9f1e2a9e"))
    (35855, uint256S("2523818eb6680e6b34b9eb4b932d323b45449f307342bbd374bd6e56d900ef49"))
    (36602, uint256S("a8622f5f1cbc679db19191d313d231c611e7e96977088ca59278944c5f9de019"))
    (37349, uint256S("fbabd9d7a2b50191e77dd7c689501e4f9a2784af423ec416fffc91a934031340"))
    (38096, uint256S("ed87e289efebddeaa0070700d9330097b786a29c5243f1dd40ac54ef6684adee"))
    (38843, uint256S("d654b45f0d56fc0662ae2be8324038c5696f136a40b91534b38f91461c22e834"))
    (39590, uint256S("e34951c4ce09eb7f8a6de28207b83b9156714b86f62dd6f343634ac5b33820ec"))
    (40337, uint256S("fbbc88ced2c2196e8afb13c152d32484d2099b1f2d616954ab149a1f8728e1f9"))
    (41084, uint256S("c7d65a22224acbf83f10871ea59f471ef901e3c8e98a6fd26a48a6c65617ea47"))
    (41831, uint256S("c831c0d61f11ede571253010ec088501b857db249e16fba98982fdbb2d558fc3"))
    (42578, uint256S("34b0c43d1ce6455cd59012914a7e4dffb20b24bfe29a11d797d235f11055c674"))
    (43325, uint256S("ad2a5fe6d5962fa454d8e8ae389defb88bc9490e6d3144315d68e85ea5b023d4"))
    (44072, uint256S("bbff610c378de67970f9a7df4d5092a062242a10ad477f52de25f8290206334c"))
    (44819, uint256S("a18a6aea4efc7806da92eacdd5eaf6e25b343c1eb3201e6e2f19e36a5209d4ea"))
    (45566, uint256S("f5cd7cb7e2864ea9d8e8bcc6f3dbcd3f17d7956dbea7804584e8fd7505cfb348"))
    (46313, uint256S("a984fa3af175d6b0ab4c491fd06784d6ba04fd8df14afbfb4bb5441fe3adb165"))
    (47060, uint256S("5e0bac7005b34e6fac61f6fdbceb2de8a3ba75bb7cca1f2fe1cfd747ddf7bd2a"))
    (47807, uint256S("c22478586349e389dd4b8bc9dfae88ef46c8b9799175ce36a1f3b119d80acdc4"))
    (48554, uint256S("f2db8183d8c3bded0c54c8be92ab94fe271a368fce0afdbe53e97a04158bfe86"))
    (49301, uint256S("444e7f2c095a9a511d08f96d874daa111b89b42d49992c9d6378b66889b6a53e"))
    (50048, uint256S("215e915114f7e13dcd2eea2a4127cf18ed778709ba2703a69efed910c4a06753"))
    (50795, uint256S("99b0515b9143325529bad95e0a270660d94ed3c76bdcffe9ca6b1285f4a900fb"))
    (51542, uint256S("ebddaff43fe31c09481c729c1859ea10990cd422f7e8ff51086243ae195eb18b"))
    (52289, uint256S("5e7c3ceb26a1006cb34a692aff04131e4083b78857ecd579f3c8c3af2fa7e46b"))
    (53036, uint256S("e61943c114eeca93316267670a4c5ac5b7c4a722cd2d312b80c3bd58a1658821"))
    (53783, uint256S("cb0b7f8b4bd67e15006ac26b9287d191a4ae38151e9bda6f55c1f56b996f398f"))
    (54530, uint256S("13ca4370c4b6b4782fcc673b6cf11affe90d2eca5e0cf7c2af99dddac4636c8b"))
    (55277, uint256S("39678507cb90397ba9d8da033a48d5693ec38d8571dbc1972beeda20af91d511"))
    (56024, uint256S("deceeea2076ae33fd9950a473ffea5b4a67e2b696fc22f0301f8c24e80b528cc"))
    (56771, uint256S("baa6d11a9475f1a182d9cf159bc54089d344f08629031dc258750f9529931efc"))
    (57518, uint256S("b2c980c805de9d9e68f76994b9de96650b0b705b82073abdf81a8dd812a86346"))
    (58265, uint256S("cb47c17dc7baefdb43f1a08a4f1200fbf833bde22b2e0e061f37f80e49841ca3"))
    (59012, uint256S("ed0a0d4610ff9552fa03369bb98a23b54d308ededf278d885c2525839fb8996e"))
    (59759, uint256S("24df33cdf19c40ec94cdde307a78ef342c50fbb6fdb33279340ccf888575ce12"))
    (60506, uint256S("fc08b169a67c5b2d452d9f157b18de79931915e854480223491b40787c86f6dc"))
    (61253, uint256S("385d690c071316c03929fd6fcfc19409440148073ca46a2a9ba9480a77bb2ea7"))
    (62000, uint256S("8b6ef14d0911f27a48f4c8547dcacf61a5f6b1a7dce3f97d9461e84f1a39fce1"))
    (62747, uint256S("0a733ef3e0f90e94bed8b5fae337ece369ab9b058cc44471ac2f59059bed091f"))
    (63494, uint256S("65bb13b97baaf78c9377e0d55685594cbdfe1ee0b495ced7c49bb448988702d6"))
    (64241, uint256S("f4f734952d85668a93ea117e22663faa86c1210b9d90abe058cd25c744250e13"))
    (64988, uint256S("6f2852ac520f38d237c6234b19f5d53c9c6030d6fa1a53a37b97dfac5c71b360"))
    (65735, uint256S("95b2a01a5c5a49cd0a3a239eca1ae544f47c305458854979954c7d8e746b6b48"))
    (66482, uint256S("b6430f2807ec36268621f93cc11826577be481abcea090436c0f5b5531f9cf08"))
    (67229, uint256S("2eb56c1cd9d31c11a3e37d3ce464ceff7dc2a8d99a55998782c21088d29c2a2a"))
    (67976, uint256S("66625e3072f80af278a09c92bb2adbdd472f422db2533b6d0586da59dd560b56"))
    (68723, uint256S("eb95b93088766e7b245c07931855a8b38191d9c6c47cecd4181eef62e310706c"))
    (69470, uint256S("679cc846b52edaead120fd5a6e2ef2dd52f312a0bf7f4cf033287a07c7c4dcd6"))
    (70217, uint256S("9e8953a0583f4a7dd6e67dc06e8a196c3a132416685ea3eb18d830591deee2b4"))
    (70964, uint256S("949985c9cccef526de36554fc75a15bc45ae18dde9bb5dc6ffa244a0896acf80"))
    (71711, uint256S("0532dbf9b6cde3dccfc36d47284370410cc46a556062ec1fd4bdf38db2e2a6b4"))
    (72458, uint256S("f4fe99c68143f472c1e968daf22bbec778344601b947b14dffe9059cf245b578"))
    (73205, uint256S("9c6dc31527974279bb04f71e76069a4198b464b198ffc7819ad0011e65dfe685"))
    (73952, uint256S("f807f513f9b754f649fbba2128e48b41d5754a663141cfc4e0f2eee48dd69bf8"))
    (74701, uint256S("6e16e3a7eefe132ad474217e36d96c4f4251969590ce73077624550c67e6ab17"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626645975, // * UNIX timestamp of last checkpoint block
    152089,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2988        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
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
        consensus.strSporkPubKey = "02cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda0324";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           //{ "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
        };

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
        consensus.ZC_TimeStart = 1621934936; // Tuesday, 25 May 2021 09:28:56 UTC
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 80000;
	
        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("59ea521b46edf374093a44c5e8bf88fe3db211aa9fe63dad1c065692047f6db8");
	    consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6ca0d4ee6fd87d7deb8a3f31eb57dc52588aad8c75766f6449135182f1b472b0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0f2a78cae02903adaee9b7e43a91b86725980e9ef3bb49303a722a48bf9a32f6");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("a70f1ced0cda9854854bda729aa9c93e5867fd583158f033fb16b50daa258a71");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3142c02979abdf5e8e8f6d0f5d68e04caee93fe720d401a806e5e074e50ed5c6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
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

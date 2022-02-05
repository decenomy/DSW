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
    (13318, uint256S("38377c1923b59f9c3e63318d30fa8212a636aa1d51405f986a339cbd5968feb5"))
    (26637, uint256S("002893b8fbebb879d487d9869b7d536e142cd759d0a9efd83d0a27d737927806"))
    (39956, uint256S("7c689079461b4bb5a81d50382935f6faac912ba70cc923016741e5e2be7e1a0a"))
    (53275, uint256S("3a96e917f1a8fd3e7bcef57850f6f5ce84e2148e387088353fa5be78d71d0c04"))
    (66594, uint256S("59ecf4c9f76599d967ce5d991f574b997686faafe93bb7186d7d4bf7f6805aab"))
    (79913, uint256S("00d0a5245e3b2eed14b9246a90817ba445e96f7c8318ea5eb6f02a581c15aa3b"))
    (93232, uint256S("5f8b87b1d99a8cf70409cc259d39291a625958aa4d9841d43d8ec8b7733521e4"))
    (106551, uint256S("230b877716972f19b5a91c65b5a8bc9efb14352d3e7f3517a83258666158e812"))
    (119870, uint256S("7fe4d48b44fa2234efdb61926af342b926f2035c03a773f29cf52cd68422d19c"))
    (133189, uint256S("0c76ca8d76771ba453d660b8d0438431b2ff48c6db75d54c6d0d256ca4ca7339"))
    (146508, uint256S("6a10bd91bfa46c5e3aa33245da760dca7fd0281e239c7d75a1a1f2dba383752c"))
    (159827, uint256S("183b31eb57844e0b9fbdc202f6c5cb99c69ed2d9f56e396d180a1c5ef72d7c8f"))
    (173146, uint256S("ca1422231d200ccca65cf5ab340a9d68390ae7e6d3ee196146156d61e23269cd"))
    (186465, uint256S("a57d5652da648ef546f6ae0307c6341f6f0ad5ce74f8d5b7b9fd97e83993e977"))
    (199784, uint256S("dcec839c8c751639e5999ca8d83c0da2a4eaa3968124c6ef83f5ea1080abbfb9"))
    (213103, uint256S("db31160f682e36ed63d9b624ba075055ed3822292c4f14ac2c2c8aea233a6e85"))
    (226422, uint256S("fbc67b9d7154aeae4747792fb6923bf5744b103139c81c37c5a5fe8459f71247"))
    (239741, uint256S("71ffac823a2e949b2ec543355325690e2b16f506e534e75edc90274fdfe622fd"))
    (253060, uint256S("9022a854e0286c47e85f16851a4169c88719db2876562a2002d54f6fa93c26eb"))
    (266379, uint256S("c14ddddb1cd23d2dedd7e8ca9334795ad67bc2450cdc5fe2c1b3caf9eab8bb8f"))
    (279698, uint256S("057c3e7891cba17c1cba3bbd3fee213a8a6ef61aa4fce77544136570edc37a39"))
    (293017, uint256S("872361c3bacb2ef7f2844498e8c342183bf88513ca2bd63f0fc72b1c7f169610"))
    (306336, uint256S("5a7c445a756e2eb0edc986122bdde6ddc99a46ed4547dce0f17154963fdf36e8"))
    (319655, uint256S("6a6a608873f03d31848f0c46868c06c5eb8d887bb84f90147e91575ad5919b4c"))
    (332974, uint256S("444ba4c6bfe3426bc3837729d6050e1794e716dd407ed7ff45e434ef3ca0f4f3"))
    (346293, uint256S("331c10627cc5e8da9566b8f77e602b83c9c8eba369f232dac5469a9fa34f57c0"))
    (359612, uint256S("50c788cdbcdecbac304d2ce5668aa74851d49780209ba68fb89bc9f755ffd471"))
    (372931, uint256S("53743e107c147b4cb7aba31ad18c320afb99c2b49fadac76a7d112500eedbf8f"))
    (386250, uint256S("aaf39be1091e381124a2c58ae4f142dec93ee2164d8e7bf150d880b0c9a7139c"))
    (399569, uint256S("e1c109fbef2454a98ed72cdc8a30c3c996dc6778877b9cee81ea8b17df27d77b"))
    (412888, uint256S("cf62a3af6979e8109ed7988a4f1be5a943304638605638b0ae3e0b948826ffe2"))
    (426207, uint256S("6d339f8929de14922ad54306c162d3e21e16f1f077d69b6e958f2bd8435f378e"))
    (439526, uint256S("57bbc41d1f26d5be63cb4ba717e63f59125962d74c83a6678a6714955cd66422"))
    (452845, uint256S("a0ee7b1b93bddf68e57915569c22753cae61390bf4eda6ff77c8eee53c88ca92"))
    (466164, uint256S("fc6afc5919793c3fe20ae729ade1e7c5b6d0c0261c30757979947383123ce93c"))
    (479483, uint256S("4794074814bff583917df43a7ddfba71c092ccc702ffb5e4339f5cdf99bb4cbe"))
    (492802, uint256S("084c313767c97c346acbe67a98a8a7e97eeb6182629981be150ac82b5355dcb3"))
    (506121, uint256S("0e260fc88a05982b8b99bb551eccf94888b6ad2205a274b4b9a0b3516122b2e1"))
    (519440, uint256S("7c29dca2f6b6f69cb861b8a10269e2a434e3a68e5df8335f2280d4578ffce54d"))
    (532759, uint256S("b0192d3ecc8a4ee63357578574ea9713db0292b3921de67ba43a188009f26443"))
    (546078, uint256S("15ce73c989105cdb7fdd0ed78cfeea26bcbad668b5f6ef260afcc4dc58052287"))
    (559397, uint256S("57143bed36d94944b3e18791d468a3f3a991862e4e2409d2d0225345db629b2c"))
    (572716, uint256S("0ef4002f018e389759399d3a7bed4d8d1cdd9fa73a27826247e3312b015b4a82"))
    (586035, uint256S("308ad7641e28793352c5a7cea46198ff91ab98ceca6bbddec1d461507023783b"))
    (599354, uint256S("6007fa60090c11ceb83368008c1dc3fd6b66dbf57122937c9f69991ef69e37a3"))
    (612673, uint256S("0519ffbaf2e683ffb8d6e45fe265b3dc26bae05ae5698adca1776d7a60c13f74"))
    (625992, uint256S("e508d997e5fa1f4f878a9d206fe3f75e89b431c8c0c99e5b5cc48f07d4bbdf6b"))
    (639311, uint256S("6c76cf3fd1f83340019e755ea5e5e9d2a2a61b0ecd199f6c36f580da92a21ba3"))
    (652630, uint256S("6015a3e20e2e891f7886ae0eb80d616d8cf6830314485f9467350e8f61cefbea"))
    (665949, uint256S("01b86c049013fd4ae90c15f264dc8ad4fda791244cdbbb3643a2e232c5e32875"))
    (679268, uint256S("a85bd1036cff8a68acf9e68617251a116b9c5f611c6e65b28bf7bb1be81981e9"))
    (692587, uint256S("eb7a058aa1c0e23500215221ef27d034142fbc3af0c000c51f457a7db041c573"))
    (705906, uint256S("934614ae542b2102a5c6560219c37f8b4ed7acd0a4cc3fdeb0f0886b85805b06"))
    (719225, uint256S("1bb20fe643186cba36735382664e61856e3de7eb7621bc8ad76de87b3a3cda9a"))
    (732544, uint256S("9629afccfcbee2e1720b2d54227abc96cb0e82183b3d10bfebb224dfa6964a51"))
    (745863, uint256S("a208a35fac457ab216c2ae9dd634960a633617f61897ba954642def8ec2ea6d3"))
    (759182, uint256S("59efd6d803ede73a3ea5316941890f57bda3a135e13fc01982c75509ae312164"))
    (772501, uint256S("dc85b9c37c3a69c9e94196c97fdd3723f9333c67999b5cc3a5113b192bbdef71"))
    (785820, uint256S("e2d1c16a7189a87deeb595974e10d69c5690367277c0234375b031d6dc138c10"))
    (799139, uint256S("736be4cbfcd31475894e9e30ccc5e224d9a932bb1cb723ced8d50bb7b50b7540"))
    (812458, uint256S("4873bb8abd275ff2a83e500f07e05e34cb060518011933ef674b7e4a78c67097"))
    (825777, uint256S("14b09431661f0811d20f13c60b70c9f67dcd6de143b5d623f1b6ddc06a7f69fa"))
    (839096, uint256S("de124dd9a62eb97acae7af5a9d7e74ecc3464a0f20fc317fc41b651802e3f6f0"))
    (852415, uint256S("641b22bcca7a3e83ec274fbc1bf645bee85e169a4ea7e52bebb816b5bc94d5c7"))
    (865734, uint256S("1210237624f2b3a518d6a92bb3caf6e24e81d6b7d467b3ee0b826354415f8778"))
    (879053, uint256S("21344e8c58fb403e5bb14ed6b0da24341086d6525677e1d9c1916a1acc12c897"))
    (892372, uint256S("c7aa881c20547900a9565546d775edc627c312e9b67f4207ca98e34e230fbc2e"))
    (905691, uint256S("f2ea626250e1ea77916a14dd26bfb706785153b9155c8f47b4b1edfb48081aae"))
    (919010, uint256S("ae16225906d1820c27a05a9ba55aeceed6286f9af94fe42d6e3d1de56e579feb"))
    (932329, uint256S("37372d449780dd8eaabf6e136833ec2b1e9a63fa442ae2bbc8f92983620dd10a"))
    (945648, uint256S("57c35109b3a2df86bbf3184e0e93fc32d03db24b209f64871ed85d2eaac32665"))
    (958967, uint256S("0b59c74512758fec801f7a878cfe65e0d25a75c0bf62acae63a99e3df2bc4e3c"))
    (972286, uint256S("ff6408a71a4fec942ae8a3f66ff5867f133e72a423c5d42210786e4a729fa2cb"))
    (985605, uint256S("fca142d3b1d1836ea18cb454e0ad57e66e7a527e476661fc597965cad415f0d6"))
    (998924, uint256S("0b3c516a50b70a71ed1ff929106d5b9a5a9b03cf7a599f8b0b8f27bd496e0b54"))
    (1012243, uint256S("b500b434fa21ec3d7e34658241a86aac2b45f28149fde6ecc97141a7a2415766"))
    (1025562, uint256S("5999057375bb56d992902cb4462a3c5d2a55b01e769c99137b97da62107f863c"))
    (1038881, uint256S("f107b8e1a155f2644affeafb46f07ea0fae819d240855449c74f4f49a1469c7c"))
    (1052200, uint256S("63aef6f34199731532e8b1a92d3033afa41a5776442f37b4d8ee3b48edf0b0a2"))
    (1065519, uint256S("48a81094c828fd00b66ecdab64cded3ddc8777d4918ffbb14cb66e06acfa216a"))
    (1078840, uint256S("853573ae5080bef1408749a17837a5359acfa0b32436cef9feee28e021a90cac"))
    (1092159, uint256S("1c083cebd78b19c9b7d013f1f44c34ddf5eab33e6d5a45697649cdb19ea11363"))
    (1105478, uint256S("a96c1f116cae57c2403f765a400363a460d3dad25754f9094e0683ae4c060d11"))
    (1118797, uint256S("c9027e8bf581fdef650789c4955f50f69e2b7a1201bd6b6d74423ca133d5d6c1"))
    (1132116, uint256S("ed66cefc9a981e856f1cde67d5f55bd6836f98a50ac341db5ab0cda03ce80583"))
    (1145435, uint256S("33823652985752143be55b8494051ad5ccd5c260c16c5e09a50cbe303bb09965"))
    (1158754, uint256S("454defc9718bad8c2ed06eab30c4d71ae8ee9c15d2ac00a3098238500e5512f7"))
    (1172073, uint256S("3b89bf1dcd1149e9857b4b8ed56f70bdc6f871c26ae5099001707d5a7e02edc3"))
    (1185392, uint256S("7c39f11fa2bef1f898b99fbda362f73f160a3a26e675fed213be8025a5741ffa"))
    (1198711, uint256S("2aed90b7f54ae9e08e09b08946aeff510473a661857445a072c3453353b992e0"))
    (1212030, uint256S("f75d46e4b884a1cec0cd6c9160992a506f7a04e486fb5909c9c9b39ab1bc57ca"))
    (1225349, uint256S("42188d6c6cf703d424a6dbfddf512d681fccad1e649178be2263245d0db79b32"))
    (1238668, uint256S("22260fb31285b069a4da9ede97658824b2cb4f2a8136d9e2cf05f258d6dc65e4"))
    (1251987, uint256S("6221a6f3fc39860f4a1c46be782c08fb13e430f65d2b148f4cd66d6b387e1922"))
    (1265306, uint256S("8cde170af7487813012b3097eb00bc6c000f0d3c2208cce20dbba43c6b09f9f4"))
    (1278625, uint256S("c1e6794657780efbc5b4d39cf94b287bbd9098f4f1f4d32035a018abf9a46dc6"))
    (1291944, uint256S("d29bdb9043c393289674ac09e190d42ba3ba39a4cb597ac5cfa104a984c810f5"))
    (1305263, uint256S("09baec8b3613129bfb01147f43d186c4663615a8669b175b317f70b0b0b00054"))
    (1318582, uint256S("be4c40021137b0dd9b8bc888e795a897efa3cec4eb24734f713e82d0c077afbe"))
    (1331901, uint256S("dcd30712a6e000eb9dc4619462fac4e7585ba7e48bbd55b0bcfa1cfb2e5516bb"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1644068850, // * UNIX timestamp of last checkpoint block
    3254611,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2832        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
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
        consensus.strSporkPubKey = "0391eb99d1d94bf8bbc66b39ba11c95814a2bcbcc1cf6c567c8bd58b8710b192f4";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1599033600;
        consensus.nTime_RejectOldSporkKey = 1599030000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "CXXXXXXXXXXXXXXXXXXXXXXXXXXXYGerr5", 0 }
        };

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint = 1686240;
        consensus.height_last_ZC_WrappedSerials = 1686229;
        consensus.height_start_InvalidUTXOsCheck = 902850;
        consensus.height_start_ZC_InvalidSerials = 891737;
        consensus.height_start_ZC_SerialRangeCheck = 895400;
        consensus.height_ZC_RecalcAccumulators = 908000;

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
        consensus.ZC_TimeStart = 1808214600;        // October 17, 2017 4:30:00 AM
        consensus.ZC_WrappedSerialsSupply = 4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
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
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;
        consensus.nTime_RejectOldSporkKey = 1569538800;

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

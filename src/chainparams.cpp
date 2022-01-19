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
	const char* pszTimestamp = "Bitcoin 'better than gold' if you study it, fund manager tells mainstream media, COINTELEGRAPH, 18/03/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("04bcfbea59ec97482475f554db08f7f67c5c5a95a52a356b052d0ed87862815796fe6022c33a0baf09fcd8d3ee98ebb6aa6a77fb43d716641242cfd45369a88e7d") << OP_CHECKSIG;
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
    (0, uint256S("00000e41db923032d1be957ad4be59aa287c9727ca7602dd403cf7312d259968"))
    (1675, uint256S("7f3b3565c02123682b7d03cc7d37b90f9c9fb9469f986db8ea2e2d665f647a65"))
    (3370, uint256S("36cbee1a35ed8f4fe5669361bc6e8cbe37f2d3b0eee48d34dcf76092060a4dfd"))
    (5082, uint256S("9615c1a50c0c5d8d99d8d5e84c587ca1f6846002bd3cb97baebdca7f1f698918"))
    (6786, uint256S("2439ba483cf765e81e67cbe1835413dc3b000b55cfd9c3cf251453b28dff0b81"))
    (8476, uint256S("19ade147ac412a86d98552bb66b436fb7e145a15d8d623ef6649809484035e6e"))
    (10171, uint256S("86383b744d3477ae384db3ccae3519a0e00d2972421fd01f0d0cc0a3e0aa5efc"))
    (11870, uint256S("c043a8a20883655487b481379bc74933fd5695b9609f52a2cdf484a7fa024ba5"))
    (13566, uint256S("74837ea12c20b0bfa7011e5f1065b64dd0e1aad6c49a4f339395e9534960b3bf"))
    (15264, uint256S("7fc563111c526685c75755942b54ba030c1c0cc66bba6782dce887f8db6b447d"))
    (16954, uint256S("e51e67cceff33bf800c003f94afe38b6f274e39addd14d2acaf4b1c72da087cb"))
    (18650, uint256S("dee2689b5f4777dec98a8b24a6654c1edeb3c1f510e1c387ce7bc3f56876019e"))
    (20340, uint256S("b52e21470f618a3c8812efe6eaef7e4d3fd8d7efb0ac91552ff2bdb04cba7dac"))
    (22034, uint256S("02a21076c0b2f32aa8268be5930e5e4d49d0f6bf7a3242588ab4a1055189472c"))
    (23720, uint256S("83c43649b30e0122f7516df41b77c88056c379b9e1f5a959d4087c4fdc7ceea6"))
    (25418, uint256S("3b096d3597a0c417e333284fefe1d6f2bd2963a19cfe78ada64a53d0bbda899c"))
    (27132, uint256S("8e8ec3780e4ddd89760b1e3a81b6ba33e4d0fda65340b92309b4c48168d6f516"))
    (28828, uint256S("25e34ccd70c5d3c74371c17785ae32d620b6fb505b466459fa09c6976a765dfe"))
    (30531, uint256S("50a29dd3a92965f03e1b4ca5f94b8ff2513130a899ab59158094565da4829340"))
    (32237, uint256S("759972c126456fa23e543369c3fc0d989a76e0666ea2cff013a653fbe56d0dbd"))
    (33927, uint256S("a314e8a6929975bc96f323df097625bd3a84802abb9fba56992e40c2d0f5873c"))
    (35619, uint256S("f468b7aa85cf4ca1ce3ffa26fe44b7f83d8cd166303282a5e48b57b90de1842f"))
    (37316, uint256S("b93401b043352b232574b43ea94e1e85015f429ddc674b29716096ce455ac9d6"))
    (39002, uint256S("b844bbe91eeb3d281be56e6d41031f4e818ffde9bdef6cc19e4534377219ca61"))
    (40698, uint256S("79bb5dcc5f9a46868186253b30d342589f3c077e5b6e04d81aa322c9b2c8cd61"))
    (42390, uint256S("ca1ec946df93cf2a631496c5bd04949ab1c673afc7ab409897dad2da4a5e9043"))
    (44076, uint256S("b1821a88e50b098078b6220d245b084a8d32055d0f3d3b22cf89d76bf3fb9d62"))
    (45762, uint256S("e6bdb6e42cd877f96019998213b36a5b88b3a3a4eb71155176cb5e7fed890d52"))
    (47454, uint256S("5ab80699f39a3f86d7793e348365c4cdd099afab91112c82420b0f11eb481599"))
    (49147, uint256S("54ab548ccb3fb661b53b8698faefd1ebf3203c5343f975fac99da39ce4226cb3"))
    (50840, uint256S("f0fa7584ea3e09f3818b4a25ecc45765d72446be790d268862abf4b1eda8acea"))
    (52524, uint256S("68f0f5892eeabe9da5288419e2daaed084f35872230117c35b6bd6b18fb6d55e"))
    (54217, uint256S("ade187fe04805a4b93dba0ee727d9f24fd0a4a4928a8d90a7de7267809d49728"))
    (55905, uint256S("dae812b53012f800b8ca555668f9853befe125be1ac734c7b6e8c4bc7ee7ccac"))
    (57599, uint256S("050b72f4058f6433ef538f9bcaf5fa18b3449d88b04962dd21c07aa19035dc2b"))
    (59292, uint256S("54eb7879470e8e6e47b49db8c777b880b54088d182b1f6c6395c7f51b66ab2e5"))
    (60978, uint256S("293ef612ecfa7c2495f3a2736ce33e2a659d97b710fabdf1e500bfc89d7fb0d8"))
    (62660, uint256S("730838e6074bea9f2d1d6518baeed59ba19d48b5ad1cce6b83354bae56cc0448"))
    (64346, uint256S("50f17f7fe168d5ce92de95e97790b111c3e52943992590fc94f75d1214b05fa0"))
    (66030, uint256S("60dbc75e432f3d794af8cb44ecc1c3653f08d4b36a87232b3476fadd68ef2b5d"))
    (67722, uint256S("68a2276db748d8b5514eaf69e645938337baef47d6e4449cd658c3059f5f8813"))
    (69414, uint256S("3b3087989101598c245438dcb61f25d860c2f331acede33d7729c47f0f91a5f6"))
    (71100, uint256S("a8f7fa1817dbb8216a51cfb63441538000092b31638618d2f077262493a6e312"))
    (72783, uint256S("7e474865091e474e5996a8bd6b811e86ed355a823606ca2d7fc6dca9c216f3f5"))
    (74470, uint256S("c43be8956d7838d79e7cf01974a1754f25ec53e7c7d015bbee8adfbef840dd4d"))
    (76154, uint256S("e63ce8f851c55c4f82a6dae0d697ec59af11051aa7e2757975cd4c5286aa256d"))
    (77842, uint256S("703de0e105de0cded111eae94bea64728d3c5f2a84173e6c2339a94aad2e82c8"))
    (79526, uint256S("a81f5e7cedc26ca5a5b19bf395f9b12dc31f7d53ff734992e6d6968ad2354512"))
    (81212, uint256S("102cbdfccb36c7144110c0c44f8efbf857352651a66d3cf6b1d96b318df8e90d"))
    (82894, uint256S("f944d54c56d4b7f7727b9d76df5970a1fe913c73317d22f741aaa5fdf86f52bb"))
    (84584, uint256S("5b128c48aa849029b782229947a66c289f2c551e2b336a390af8cd4d016886c9"))
    (86268, uint256S("46aebcde981152b5cfe20f4c8d9912b30bf7e840d843693640b4ea7e9f9bd77b"))
    (87958, uint256S("a6709ba73c40a177556d59bbf7441db7334b33646fb51904d58b54bb83aa25ba"))
    (89642, uint256S("c737529f55cb8950ce6e3b811d350fcbaf844302b7636cf89a0c6de400160ad0"))
    (91333, uint256S("35870526aa46c1037f47ae650b1e91d1b266c042395c801b0c80ec757bc52959"))
    (93023, uint256S("a9eea650750dc29c90fc6588c71bef8ea406090e0f9fcd13fbf3f85109163819"))
    (94717, uint256S("f5c5213471eee5b823f621c1e975828c63790082862d3f6eedb33e5329e4d450"))
    (96401, uint256S("7959029afcabaf919eebd3bc3341029d9ac23fa40663d2b2bccafeb10bda30c1"))
    (98083, uint256S("3da41943ee923bec21e80f4af17da3d344239b823dbb5e5460b567f23a3ad1ac"))
    (99765, uint256S("750b1831ac80505080f86597eed7ccd8330d77081bc5f77c6f23d467d0c2e2c6"))
    (101445, uint256S("637145499597579b5eb030ee406dc723a21e6e90d970a58846556725ecbebcb1"))
    (103129, uint256S("f79e5ed793773588075ebbcac9c49fc5a82e96b63c5bc95f08ee66c7363234cd"))
    (104821, uint256S("856dff7ce611040f9467328608e0c7dd3390a4637706041aebf4a69c1d0ea645"))
    (106515, uint256S("38a48bb10151af653c611fd5f0611dd036fcf0a576600de5e85f8d42c866ab18"))
    (108203, uint256S("6f20e5cbe6bfe7e9f3a26e05b2ee4a36ad6414d48372f039decfc730ae4ef6b4"))
    (109895, uint256S("f04f2c41b16383390cfc086d9e26bcc67ae69090056fd25777f1e8fd8e244154"))
    (111581, uint256S("bb8bbffb3374409dfe317e62e09df4e5ee0812a2647826c72336c3c5e78b2262"))
    (113261, uint256S("126a4a50b059ff835146d81f71215d824afd9e8da7d7c27b763c5df9ea65c4cd"))
    (114945, uint256S("582a3861636420f78e15bd09532f0742448b9f0e7011f17c90d0e91aa16371c3"))
    (116645, uint256S("217a155926b3132022ed9d12f49ab4618e066267f0a5f4b723340d4e10ec791d"))
    (118339, uint256S("5dadacd59c891d81267f389764b7c2ce757b4913cf579f4f84802f77fd66d3a9"))
    (120036, uint256S("08404378630da18de3caa134aab850336f2baa72bba1e1f58fcc4ea050e277e9"))
    (121712, uint256S("7cca4440dad0c2d5d4eab039c681ae42e4a974d4b49f21949511badd00e58e6a"))
    (123398, uint256S("ea8958612e8c427ea8e99d4805058e5ae85d4ccc63a6eaf9f469b180e58de3b8"))
    (125092, uint256S("1625aa71a0e2863bc2660db0aa49098f2bfeb1d1533f6fcbf3caa591ed36f37a"))
    (126784, uint256S("1a8a6e559cc3c3961c578765b9cc2256d8c5ca3edb27099ccbe00bfa3d44e07c"))
    (128472, uint256S("5c811d33b883e61fbbc1e49eed4812328e2fa57afb18937b8ac72da260eb18ab"))
    (130152, uint256S("1f2192c4c961a9f2247b6aac25588428014e0b147a1791624adc0f62fe957d95"))
    (131840, uint256S("92aad97689918c5b2a2fa55a01de01b3b9d71296025a8730864bdfc51548e535"))
    (133526, uint256S("964f601df96106c1e1cf07fe6209db2b6a6a9f3b069ad85dbb03e8033efd3660"))
    (135222, uint256S("229497d32ce7d16665875754918afee2080bfe3ce8d3c157c4bf63e367bf9fce"))
    (136914, uint256S("845eca37f9a90f87a8d0c6a3933c6c2f7cbff6fff244b0b949b2ea08eb2d54bc"))
    (138604, uint256S("df63f2da05e5ad17245291cc317219420c08faab4ad1f8c325954fa1d7c6ed28"))
    (140288, uint256S("18b0270f77715fa41e0a2e455ab6d24fd56f75ecbe2ab6069e4dc0ad273954df"))
    (141972, uint256S("2063cd6289665457451a521d019c007d59167833ae6e47260170e1af107cb5db"))
    (143662, uint256S("205b87be63835bd9b32f15695ff1a7e2f85f88fd98ddb19ec7632bea6444c232"))
    (145356, uint256S("bcbf9c38e33e1a42a95ca56396247ba8c3536696ed22ef5c2b889131579ae427"))
    (147048, uint256S("4bdaec38e93312cdf9e1930f3716c39ee2125fb2fb45a9b48552fc5dad2ed90d"))
    (148728, uint256S("d475764b746216ec917d63c927828d0bdd042d60b01a756f888f206a2c0989ef"))
    (150414, uint256S("a3f0e7b361472ae5cd8720e801ba00bf25c1746aad9508b30fedc005b3775a8a"))
    (152100, uint256S("b5bc74e08b995b643b2904b644f2b79f4486c5b2dfbe33017eb866e6fed17c3d"))
    (153788, uint256S("95aad15f2321b3bb9ee0c75bc713d1a0900e0e186d7f9e3fa1b243a36fcdcf6f"))
    (155478, uint256S("53bced04d84473c1049958b692f149a428b23817d56a5e4375c994b3e2165685"))
    (157162, uint256S("a48bf5f7ef4f33b04b14cae68849a722e962448657bb338213a947765c9babb4"))
    (158838, uint256S("66b5a9408156f6c37e906d99b7f4ef50ea3c600028ec4e41d0f8a9c545542e4d"))
    (160514, uint256S("fb666c5a3fe3ac7d24efb9b3f43f468e9e5742992064c373b925b2370379827f"))
    (162190, uint256S("aade5c8517d8cb835f0cd2a60556fe55aa8339a2e9105f7f995fe9a7b465d7ba"))
    (163868, uint256S("2847f9d6d1fac97c6b47ff2a91cd0a9038aa9030f8a9b1092c9417b1bfdb389f"))
    (165544, uint256S("0fa7d9535247e249af29e57316e74663f4a4e2b23167c0787bf3b1d266b072b9"))
    (166341, uint256S("98dde0cec5e90e767c911231cfd6bffb0d2a1a946c2a6926183203d548c74bb5")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626370800, // * UNIX timestamp of last checkpoint block
    385495,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    3338        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000034fe1805f04a440c06c1b96b1234b45d9fdba0fcb055d5caf4d83689428c"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1616082640,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
	(0, uint256("0x003279ba296f0376d7a8417354e0ef9bd00fa29f92ac5d9cdf97c160673474af")
);

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1616082641,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1616082639, 933427, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e41db923032d1be957ad4be59aa287c9727ca7602dd403cf7312d259968"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;  // trittium starting difficulty is 1 / 2^20
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60; // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;  // Number of confirmations for the finalization fee
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
        consensus.strSporkPubKey = "04709f473a079113abd0da53176c9ecdc2f67c86ef6379459786d757d6d03a1954c0d4a902bb17782607f014d3476b3c73bbff47aa5a4d8b3d870cae33aa497a10";
        consensus.strSporkPubKeyOld = "";
        // consensus.strSporkPubKey = "029e54031b41982ac1c22b780c1101cf4b0efb71f7beb435e46fc0b406ff545ef6";
        // consensus.strSporkPubKeyOld = "0464b1f34052a9fa87d18516fd97bfd70ed78a3424d59e9b9ffa9ea7fa35b50d376ec01b0923a2c7a8edfbfd2787247aadea861d4c6d8fb5814b708ddfb153aafc";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "TRCryptoLifeDotNetBurnAddrXXX6gvik", 0 },
            { "TXXXXXXXXXXXXXXXXXXXXXXXXXXXaoxzKN", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 166929;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("e4cd39496b46796b69b53c674dfdaaa789396c907f8f0252d72d89effdef8b45");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("80dd173daeebb1fc25e340d05f78dc17bc19a05f9f210e46db312c0c0532e9b2");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("80dd173daeebb1fc25e340d05f78dc17bc19a05f9f210e46db312c0c0532e9b2");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("506c9d4f33ce7334d429a6d5f8e4b608bb8d7c0c2f233fb7becb2b962e7f53a5");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("bfae8546b921841766191b5774e18405aa32986806767a5ac159ceefdd0cb3ec");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("05fb6d596455cb9b24af308171a3a5b3902aac2dc4cb0c582289b5df4dbbf774");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("ce797d5715d07dcabe6e6c3557ed10e9e34ea92e9ec1a54c6eb02905f665c0b6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0x51;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = 31001;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed5",  "seed5.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed6",  "seed6.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed7",  "seed7.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed8",  "seed8.trittium.net"));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 65); // T
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 19); // 8 or 9
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 239);  // 
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x46).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[PUBKEY_ADDRESS_BIR]  = std::vector<unsigned char>(1, 45);
        base58Prefixes[SECRET_KEY_BIR]      = std::vector<unsigned char>(1, 179);        

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

        // uint32_t nGenesisTime = 1616082640; // Thu Mar 18 2021 15:50:40 GMT+0000

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1efffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1efffff0, 1, 0 * COIN);
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

        genesis = CreateGenesisBlock(1616082640, 178720, 0x1efffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000034fe1805f04a440c06c1b96b1234b45d9fdba0fcb055d5caf4d83689428c"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // trittium starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144; // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 500000000 * COIN;
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
        consensus.strSporkPubKey = "04ae5f52611fc9f3dcd3f2db88ad4a9b10ab218389cacd1ed07cc893af6ad2f3e6618090edb54038e5a26d2c6d04db4a6c901a8bf52a72fef484f478519fdf0b02"; // Testnet spork key
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
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
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 721;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 721;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x32;
        pchMessageStart[1] = 0x42;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0xf2;
        nDefaultPort = 41001;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet1", "testnet1.4444.tools", true));
        vSeeds.push_back(CDNSSeedData("testnet2", "testnet2.4444.tools", true));
        vSeeds.push_back(CDNSSeedData("testnet.572133.club", "testnet.572133.club", true));
        vSeeds.push_back(CDNSSeedData("testnet2.572133.club", "testnet2.572133.club", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127); // Testnet Trittium addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet Trittium script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Trittium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Trittium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Trittium BIP44 coin type is '1' (All coin's testnet default)
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

        // uint32_t nGenesisTime = 1616082641; // Thu Mar 18 2021 15:50:41 GMT+0000

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 0 * COIN);
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

        genesis = CreateGenesisBlock(1616082641, 333, 0x1fffffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x003279ba296f0376d7a8417354e0ef9bd00fa29f92ac5d9cdf97c160673474af"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 2;   // trittium starting difficulty is 1 / 2^2
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 5;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984"; // Sapphire testnet spork key
        consensus.strSporkPubKeyOld = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984"; // Sapphire testnet old spork key
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight 			            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight 	            = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 151;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x33;
        pchMessageStart[1] = 0x43;
        pchMessageStart[2] = 0x53;
        pchMessageStart[3] = 0xf3;
        nDefaultPort = 51001;

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


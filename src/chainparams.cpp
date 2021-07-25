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
    const char* pszTimestamp = "Uniswap flips Bitcoin on daily revenue... and it’s more impressive than you think, 12/05/2021, COINTELEGRAPH";
    const CScript genesisOutputScript = CScript() << ParseHex("04f8e575ae6a7fcf97b4cb8b213a74b550ccbdb4cabff3d0bfe9ec15f5b863be758acb3aead94933428425dd5e934dced26f022c0b33682b4ebf5fdce242bbe0f6") << OP_CHECKSIG;
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
    (0, uint256S("000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"))
    (1038, uint256S("80af5672f852874635d6a8037375a3a350710482720e7c826dded86b385567bd"))
    (2077, uint256S("edc80174704a4a51a0b23459bd8d6705a5442b786adbca22b8f0e75d5260859d"))
    (3116, uint256S("0c2cb9313606b5a9c7ef46c4cb3bec41b138e4136926c7bb758c3281881ee572"))
    (4155, uint256S("d001a559404f5f6af313ad78ab12a4e35bf731a249c5ca27c28f88775ce20557"))
    (5194, uint256S("5677883871734af95730f0e0f420577fed35636736c6069526f4e0a29db42de8"))
    (6233, uint256S("181a654587d7e58871433c2a95f9df79fad9491a0cd6ed925820f95cc3d01639"))
    (7272, uint256S("8317df6f07223913b0b913a96ffa19de694c3289b6ffe8612355187b4f79c882"))
    (8311, uint256S("d7f1a53669366db324b78322d6e688283652d10b656512158918ecc449c7ae7d"))
    (9350, uint256S("cb472a1b7dbf8e3078ac5ac79780eca724ec09ff36888721794fc0286c906a04"))
    (10389, uint256S("51d5802cf83e5ea969070dc725c5c45d89d64620727fef29a52bef1abb2ff16e"))
    (11428, uint256S("4cbc746751bdd2c73106b000020fcd2e1fd4827e7e531b0cf00687e7ed859fae"))
    (12467, uint256S("d39f5aa01ffa7f065939203051f47eadd57876405b70890e187e74fcdb126e97"))
    (13506, uint256S("d629d145689f3c0de9052e6c8261abc38c40e686945335d2c2270ae475cd4526"))
    (14545, uint256S("5adff82d434690fc9f65bcff6111492c3adee882314fad330669e6635b94ea29"))
    (15584, uint256S("930c235e3685953a9f9e2e6e81c03ea83645f8383b4fc622f5d5fd72f7fb53dc"))
    (16623, uint256S("cc5cd0483539f8d9dd82485aedd68542672afb6df52417712e7ab61449151839"))
    (17662, uint256S("2bbfdeedd3a764644d250f556cd428422a958bdf2284e360495282027f20e6ac"))
    (18701, uint256S("62512f72b4196b51720102174af1f009d368b76be0d01d9c350b19b02723150a"))
    (19740, uint256S("9e8d18845de8fab728600f593797eb60acee5d98292bf0adf48db64e423a26fa"))
    (20779, uint256S("7f9471f416b8eeed59830ec50762275a0c140de375cd4c8cb7e86bc388a58331"))
    (21818, uint256S("c32a0916ae50440d33fc8f7c7957472664f3f6db3fd19152f4c0ee285308402e"))
    (22857, uint256S("a3fa1b6368887e8c94548044061e09a016f29352882428e26be9823ab8edbf07"))
    (23896, uint256S("124e3279bc602d13070e2c5613693eed141af4e55055d6886448cd12a1cd1fca"))
    (24935, uint256S("e23f57a571bedbea62b88732b2dd6e7d4b064bcee755877148064c69860ec196"))
    (25974, uint256S("0c049e9431dac594600ff03bafd824752913623c4dd8bcf4da41fd533857acac"))
    (27013, uint256S("70bd8a226ac2d830d67a22abf4bdd08a0d14660562f8037e105e6fe474542fb2"))
    (28052, uint256S("0eb7efeba1ee60d55d38712854c2436e169dbaf342487b2222e4988278f238b1"))
    (29091, uint256S("c68b1923ea5b0f422a9f476cdae2f609f43fd2e56f8dddacccbed3ffd2f9994c"))
    (30130, uint256S("3464464ce5af6145f9710c9ae01cc97135e5442ccae433962fea421550ff602b"))
    (31169, uint256S("cf5f066c8a6dc7cf340a95e31cd14ab54fb613ea2d19fd0a74e60def33e09788"))
    (32208, uint256S("b3b56c5c8ad5e70c1c25e258d6148c0e506b55e67631969bcd7e4ff4d43282fc"))
    (33247, uint256S("d0911867fdcbedf66372ee42a4930aae2d60fe679f12b097376935a65be8d0bf"))
    (34286, uint256S("f1fd17c9937dd0c59d9f22c2d94d8190e647fd3ae352168b1b8bd9015c203a95"))
    (35325, uint256S("c3df5fc6d7e9c77417e5c377aad36f83bd3f4fa2f2f70f657839df41e4c9c6aa"))
    (36364, uint256S("588c00c86290eac4c4ee7760ccb014de125eb1a36e30c89e6f030ee17c5ce6f3"))
    (37403, uint256S("a6b142dc2d811e44f8b9c6b8623f988580b632d194949aa6f72119228e9cc714"))
    (38442, uint256S("abe50bac19467dd8da9edc7c1ccf89e9e583ddd30ace7a01c316af9a6ac67d69"))
    (39481, uint256S("aebe30660d7b7ac90f254654df70093f87e9d5a9102873a9633f13ecc9b8c3c0"))
    (40520, uint256S("bc0b7ca887c7848d5871d751be93499258e4602a070ea773cb1c215e9aa67bad"))
    (41559, uint256S("998ba033a92268d4fa62a406b5c6d641f75382722cdcf0443143378543d3e2f1"))
    (42598, uint256S("46076a3dc640240841cf5b0d8fa2ed3f0b7f009e7d852d03e2bdd17ef05933d7"))
    (43637, uint256S("a675b16e18fd1db83efcc30c82aa480e228b919a7dc48413bc1db7e033b50a74"))
    (44676, uint256S("c5f0f73e879927fa3bca32ca671d890b15185a8a714fafd9eb3c66e725281138"))
    (45715, uint256S("caabe30082fa2bedc1a7a0d6ed03cfbdfdb0fed494b2538766206cf39aac61f4"))
    (46754, uint256S("e65a6bfc5a8f733f08434227db5e6a279003f639ebcf279a4ee31d22c69a9d1d"))
    (47793, uint256S("447fa883fc650a36d0bc5423155fc017611c67040a64d28385ad150c669443e9"))
    (48832, uint256S("4be984debd682cf64ec609d985f962e63b25d059f487f8f26d8ed71d2adb6602"))
    (49871, uint256S("85a535054918e69b19aa3ae56379f796a886b6cca0ddc2c4488fd634eba61a02"))
    (50910, uint256S("b883cd5fb879a9e5130e91e76b04fdbb37fec6a9948eb81cfb74d1a660b0c7ab"))
    (51949, uint256S("f900126836029843b869ffbee2b3bd6a3a9647680a2c457d7db0f9760050a64b"))
    (52988, uint256S("24420f3fe14214495e36b467a92b4dc12120071e8700fdeaeac289d563760451"))
    (54027, uint256S("1a6925c21b03d8680cc39ea1ee605fb8ff8d79b9cb498405b5e40d69387e3b04"))
    (55066, uint256S("4f00654c40fe86bcaed3c40a30ea88ca0b41f4175499f6da49a9600b373ea798"))
    (56105, uint256S("74b743267408726d2d34aa690835be03bb136da071f3ba2709ab3fb97e0c4f3d"))
    (57144, uint256S("9f1cb276199bd4c1b54daae010fe257a5a715831127c2f464a9865732c9b80f8"))
    (58183, uint256S("9c37db57d20dcad9c19b7d436bbf78919d6658298c70e2a7d9d3ecca0ded9163"))
    (59222, uint256S("71d6483625f33968faf83d8f3e7f3c074c4e1abe6875504b564e43daac6db7b1"))
    (60261, uint256S("a22208e85c52cdf5374daeadc71e7af3d0f3824ddb95f25386ee6cf52e7c9fb1"))
    (61300, uint256S("aeeff3a50bea1a48aa805047a929509e0e43de7db02a26edbd6c2fbae2cfd96a"))
    (62339, uint256S("b9a1a722e1010fbdc7ec6ddc7d8e01e7ad528167f77714bb262722d096f42569"))
    (63378, uint256S("28a5df176f758c35f9665bd6a0cbb1d3882c007aa6b9b30bca01ab1629153205"))
    (64417, uint256S("1b6c61f3e98ce64d779c4cb3d0a480130dbd5959705e144891f4e9c56145e599"))
    (65456, uint256S("5c903bd9c7d514d337d1a4de0ded393079ca38a5b0a89e771679bfa9196bb903"))
    (66495, uint256S("858f1de2bfdf575cbbe9838131490a12e733ed58209827496b68ce576580588e"))
    (67534, uint256S("424cc1c6d0bc5d49ce07c0f7a4707be9b808397eb2dbcb919111153b50162c11"))
    (68573, uint256S("70b4e43507fef00bfe050b521e688c4438affaf86d366b826eb2057b07969d45"))
    (69612, uint256S("1a6988d04fe2ffe78d83a0bc19e067ebb16373c2b84dde0a82e2a163d7ae6887"))
    (70651, uint256S("058255e53475a127ecce22003fa1921569e9f00b283c297575ac3ed41fd8b6f6"))
    (71690, uint256S("3540de8d7a5fb38ea9093324a6a7317f6b48db5961c30bf29f35325839dc81b1"))
    (72729, uint256S("634361e35338cbaabac4dafd5cdb89ac2423d16b65ac84ceb402e51d39d35dc0"))
    (73768, uint256S("891708c470b804ce0bb99f3999d81b47a6b2e0c2d13a958bc4cf508846e09683"))
    (74807, uint256S("18c26e24b95c77b1ae621472a514e75cd2ecab080230d6157f8fa190e0155c5f"))
    (75846, uint256S("b005263ebb630f1096d68273693cdca27b21407655c52efb6e4c388bc60ddc85"))
    (76885, uint256S("12591d9486d0b2ba0939a9b956f3ebfbac6cdb4dfd15b8b782cf821950845c12"))
    (77924, uint256S("3e597bfef09b30a1e73b12cac258beb5ae140b384285636a704ea001d34f28f8"))
    (78963, uint256S("2f4d08c6932d83281e1bd3921a4f02d994756bed6118d5bd1769f17a96a209e8"))
    (80002, uint256S("fbc6545f65e48e64252cf556f14f885722c7a6207cf7ec3308805b6b4d99f90c"))
    (81041, uint256S("3c851fc064c829c29750514d449c15c79fac76a3f7e2a035448f31b3ee8f4ed1"))
    (82080, uint256S("92227758d637a181deec6a2737a8eec01d49e905edd60943221ef0536efdf7e8"))
    (83119, uint256S("65728c011724221e881a52a6288c3f7b60cac10da4333bf6e14d2102a338407c"))
    (84158, uint256S("472463f39f5f38d2116a3fe1ef3a338d99e40dbf6c345bbe2e135489da62055b"))
    (85197, uint256S("8ca6a75d757e5c11f5fced9dd53ff5b22d059f61ae544e21c528643c063c9b22"))
    (86236, uint256S("3d89b70799070cb4fb3f529deacab561c9ad4709e4d1d2980e78ae55728d5fae"))
    (87275, uint256S("37ce804cec15b9fd6a6016c1a479beb4abfd01ea7de339971f12479d580f069e"))
    (88314, uint256S("1712c953281d663a82f0199000d49f6c374c57fc4a5a35b4b3a5a823f6d4d377"))
    (89353, uint256S("72c8e7c04243b76c205eef3198a4ae2e7a2df6c7f411eadf4b6e324abad66b93"))
    (90392, uint256S("8fffcd489ab593d17d16039f2281d161ef2718a6dd3108cbd8a82bc717a9060e"))
    (91431, uint256S("bb4a805e186fbc1c41acc5d05bc6c3f68762964f66530f62e5a3567191bde2e4"))
    (92470, uint256S("af2fba9cfac8cfc3e2285a33c89490af5851605a10f0ca0a1e8de2769399773a"))
    (93509, uint256S("ffb6ac1115a74a62f0468a424fce9ed3acedc9fa262ce8e6dc8faa5e94e1b823"))
    (94548, uint256S("86f92f33f383b8eaa5f8c097d7bc2f8d2b112391f3dbc5b9c5dfc7a3dc65d32e"))
    (95587, uint256S("1e9d7b1e15ea8f22d72d00955330699876f4ecd4577535ff328c5865cb2f7899"))
    (96626, uint256S("4a354086a8cfca1300126518f4aecf123cd4dd90efb67d2375e9a189ed680e17"))
    (97665, uint256S("38f76cee990c4fb0422feb490db9d343c1d32ca8a2fd59541ff522109f0e9e8a"))
    (98704, uint256S("32848505fc8be68c7e0e371ccf02473f3a682c2983b6fd8b48ca497e4ebc9a2a"))
    (99743, uint256S("fa7163ac8acbabbce7c367de2f62b0c21a96fdf20bc1d358d6049ca017ead71c"))
    (100782, uint256S("36d4df5ea477aa38bb941624c466291662e92d26b9e1a32ab298a476c00f7639"))
    (101821, uint256S("f536ed37da631631063e831244e96fa558d90c0c31cdc3bdbe0062b988ea11d2"))
    (102860, uint256S("e3c0dfbc01cf81cad9562af817c211edf3508f2e0e325f1e55832522a2ecf28d"))
    (103899, uint256S("fb8bc8d711f44d6d9f53105193a0c327eb1157d695a279ecf87bdd3e9b4ead3a"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1627206765, // * UNIX timestamp of last checkpoint block
    256124,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2968        // * estimated number of transactions per day after checkpoint
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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1620820532;

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

        genesis = CreateGenesisBlock(1620820532, 580458, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"));
        assert(genesis.hashMerkleRoot == uint256S("0xa5567533e1f5261c38b1b68fcb552f692558d820b338222777893e616bbff4d2"));

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
        consensus.nMaxMoneyOut = 500000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 30 * 60; // 30 min
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03edf6c42c34d7d7b43103b1d3360e7024f48aacc2ee14a05248b7656bf4280bab";
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
        consensus.ZC_TimeStart = 1617879916;        // (GMT): Thursday, 8 April 2021 11:05:16
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 110000;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 110000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("50b97b398887b8173870b04a31a2bf1e5b9c06e6e6a10e0b89ef6fd00e8403e8");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("eaa3c0abdd0fd1bef1adc5fd7e5219023b0a15d2713abe1a2974198989992227");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("c31b091596c132cc1a7ed4a87d39600f42203b50f82be210cf06038b48427cc4");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7e94341430a8419e2bd432bd5822a1839545fb35eddd73da1708c01888d6e22b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0x9c;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0x7d;
        nDefaultPort = PORT_MAINNET;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 117);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 118);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x2D)(0x02)(0x31)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x25)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x48).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 21000001 * COIN;
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
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet peony addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet peony script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet peony BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
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

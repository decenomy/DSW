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
    const char* pszTimestamp = "Sometimes you hit the jackpot and sometimes the jackpot hits you";
    const CScript genesisOutputScript = CScript() << ParseHex("0478505c5bc438e08c0c8de26a661bc5a4453378d0b149fbf17cb3e1499b1d3e552fe5faaa253673c5349b461bd964a2ee860c114e9d2b9fdb0328f37ed356ed54") << OP_CHECKSIG;
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
    (0, uint256S("00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"))
    (2349, uint256S("f2c7698eb0c6ecdbbf2826cd0639ddcec2e70e9045d1005c37cd41739abbbeed"))
    (4699, uint256S("e1806d0d63fe4bd9e2b3de18945861627250fb3d11431cb5d7bfe9af96c1f295"))
    (7049, uint256S("b887afe13e163eb47c78b9217e928ca4883d71128716148f373782da7abdff82"))
    (9399, uint256S("a6b74418341ca4e3f4046775dd2e3be5dea8e54d05f898732db2bec8ef444595"))
    (11749, uint256S("c6a27995faa6d9286855910317ff323eb3e24ef74fd19d496d9609dcf9bcd184"))
    (14099, uint256S("a23fa3e66a91b071050a07e6ca68e7dec606d4cf6bd9ab14ef6940e5c11a4191"))
    (16449, uint256S("67b1bd062861726be663facd290c7a7675b9de86121e1b03330496b0b6ef61b1"))
    (18799, uint256S("e242558d9ef329fef058228e90b7545fdc084f672f1cb4813e6cb1516d704689"))
    (21149, uint256S("9020487ad8f1e815054fdc958a4096da3db94df4475929de645d1b2542f2e0d2"))
    (23499, uint256S("4468af09e8b8ed4c8dbf788512ef9966b7cadf7ecea9fe3f2f9eb9c08a19a212"))
    (25849, uint256S("2f5cc8577503030b128d56a474711739c8bb06ecef9909ec4c14be57a112ae96"))
    (28199, uint256S("3292f3ed3923a9bfc258bcd0d69d3b77407e646c66b403cea79ebb9ac8259782"))
    (30549, uint256S("c5be3ad8c5598d560b3f2a48ac237e0fc268f89662653fb63334e5922fa4d58d"))
    (32899, uint256S("25ea190e7fc7d646e39896b38942dabe62b23199506728b7ae7eb2f6f937e5a6"))
    (35249, uint256S("1d6eeff6a54deb62c748d228eb19dc7079d75f4c4fdfc825df0cf1507e171beb"))
    (37599, uint256S("2c60d7b51b06daedf4b7b112a68deb751bd04cf443867c92b926434f8d2c524a"))
    (39949, uint256S("ad88e82e76fe4110622010da8b636ebf6d19f55b5cf006f2acc7e99bab446570"))
    (42299, uint256S("988b89aeeeeb95e2c26b9966244d5bc28a632695471ae5744274e186b3360622"))
    (44649, uint256S("6b02488b44467bea61920a448d343866b6fbf4e74cb2903a06f21b8dcab2f8a9"))
    (46999, uint256S("57df7d71879b9e811cc652e76e774c4307279a85ba2dfc25cc1a29015a3eb544"))
    (49349, uint256S("52c0c593efaec0ba9a93568b354c49cc234e99f234761dd573addc083006d982"))
    (51699, uint256S("7d9f12fac36f3f16d4db2350360595cee26961e4ce54a4953b86a09a23684d56"))
    (54049, uint256S("4b0f7993a8338879a9b16bcf514906879e329e170d6c2f3e86a258246e0d67b8"))
    (56399, uint256S("d7581eae4b78e4cad539daa7334386c3b090b4320f91c7ef9f63238a1bb69a7b"))
    (58749, uint256S("8fec73f4f86654eec6725180e1b91ae479914771849b29bcc79221bca2a90b66"))
    (61099, uint256S("ac37559b0d8e68cef7ce760f1ef460eb9934d5c0938d215ff97f926317943a32"))
    (63449, uint256S("a9c54758c931021e4121309e25011664f2e618166c4f7225cab0f1cff58929a0"))
    (65799, uint256S("b9c59553cbe70eff04b7b73b567588eb80e81ebffc1598326f311067866dd7d8"))
    (68149, uint256S("e8b2e3ac0dada4924ae2ac9c3c87b727002887b252136933be50de9aed8dc111"))
    (70499, uint256S("10a105865cb5f9685554adc0923fc5f2cc1f22d4822758acca6b97270bcc9ced"))
    (72849, uint256S("1c154da50da1e802db591c5cd62c19d481a0bdf8fcf2a62d72726f35707e490c"))
    (75199, uint256S("33630f414a86dbb28e8f32a0eefa5e3c36e34c4398f0634260a45bedf797905b"))
    (77549, uint256S("fcd4a612d738c8df3541489af3c3850ac48e9ee2c293426c1a3d1637a82760c1"))
    (79899, uint256S("d6de33413817e8dbdbea273f34f61920b28418e400af106f1fd398e831b79aa9"))
    (82249, uint256S("1ae5edeaf03665ec8d28f77cd4a952e8a80a0aa674bfe71d56ddfe86de97f371"))
    (84599, uint256S("fdf6c98ff9a1ae4f8d1f016ad5c1c8b3c003cc88ebba11dcd3eaa158c581faf9"))
    (86949, uint256S("c4f1992169104445b0a2204104eab5f43825b15e9ed261094a836c5588088dfa"))
    (89299, uint256S("214fb3cc64b08e1cce47f1bf960d9a02afb02540ea007ee8cc3e141bdc35377b"))
    (91649, uint256S("096c4eff315a04135700ad5f1ad9fec29b99a5731bc3702c9fc773cb3829bcc1"))
    (93999, uint256S("6a5204cd725d76013c8771cee7695d78888744843439af0a3c2d761749301298"))
    (96349, uint256S("0577e1bd6695ef5e7258eb63c7f5949e198fed5266fd5e0f0089208f0c0fa4ce"))
    (98699, uint256S("5c0eeec12bb3c3abd8f913c1cc9a9aa9da12393c806e7559ea86bc290c187c65"))
    (101049, uint256S("efe42eb54c08f563de78e320e642acb683d54783c811b6224e085ed1d1dc8976"))
    (103399, uint256S("3d208ff4bf19b8c95861737ecbef9e47e5c6237b08cfed0516898817d4029a17"))
    (105749, uint256S("bb2509b297e31408da83d91dcff8e3f350782bb0bc7a8855fd3ab7d46367fae7"))
    (108099, uint256S("79422b3c6e859192555f7a10c9af4e36584fa92afa786640aeb814df3b0eaace"))
    (110449, uint256S("ad5e9b4180deef75a3f592738d3a5d1f52bea6b2e2033e03f780d90b57b74250"))
    (112799, uint256S("9a2c837b75ccbcdc3553857ae1a1d70da6a2e19cfc79803835f4adc0e161d47f"))
    (115149, uint256S("a30a2df74554190fe0e1e0ab86e755327e698bead6917ffd1eacf762f848c036"))
    (117499, uint256S("dac3853fc5f4fec7f561fc435a795d869e63dcaed4e5acab34ffdad38f8e0262"))
    (119849, uint256S("196cbf0995603505ba7d0caf812d2340963fa5855a9223275a2ca03eadbdbc24"))
    (122199, uint256S("03276cb06a96d5f489f03da2a2d6b4e2e0c1e26f3a4394612c92dd767997e8a9"))
    (124549, uint256S("889816beb356e5600428e42d610b83e519738d0e7ea41b4cfdf85d4a9551098e"))
    (126899, uint256S("c3693b8e305ff3765e6db059acc4510a681f2d2c150b609d3a46a86c3afa56d6"))
    (129249, uint256S("6b69b29b02fe443cf83a334a4074294179e1654e367076faad343ecce043658b"))
    (131599, uint256S("bf2dcec9dba51c78b7bfc5c1ae3a5993acc8160a0d122958e4e0ca787151d434"))
    (133949, uint256S("8cc73ac36fa5fa72879be2f302edb7f79e6b6b00bd82ed00676995772aa82025"))
    (136299, uint256S("423d80c1c98a7f77dec0bdf72e8ba6880175701aaf64d7ac1b01c357c4b104b2"))
    (138649, uint256S("90fb531441cb5a5295fb999593cdb9faacaeacd006fb08215c3cff195c6dbdf2"))
    (140999, uint256S("f3a9f99c769f1be99a30ee9cccb0384d5777c55f2ba861940723bdf727ac4525"))
    (143349, uint256S("d0b3623adfe01ef8375464a31de456ef8c9d8257fc2813fd81194086770863a0"))
    (145699, uint256S("2e94a4c84d695c449c5a0f0e6914252ac255673788955cf7415986756cc847b8"))
    (148049, uint256S("624f14bcfb802402b25f27d2fa154f78d1c9f72d1ebd99f67303a040b70c6393"))
    (150399, uint256S("55b57c64e83e0b045cf163dcbd044c77ad1bce73a3e0934064d3a57b424674f9"))
    (152749, uint256S("e6fbed59c4ead0512ef14f3c9b6e161470b415f0e9b8417702aa974fd2dd0c07"))
    (155099, uint256S("2d2ea5a843507ad8243995d4b6d36e392ef8ff4b1ae855f998053200725adeb7"))
    (157449, uint256S("97805921c61eec678fe7fd79c858de6e100b8b66c2138791b7b37104193ce6a1"))
    (159799, uint256S("8e7e3c9d1bd64cbce40bf053519e76118d4601758501bef936892ca30cdb9ee0"))
    (162149, uint256S("18154fa904ee07fdc7b776bbb03cda193b4ae1528b5e2915401b2ca4d8816ffe"))
    (164499, uint256S("40d5eca8385a24e6aa79c1729776fc54f9f5b30486e366817773114dfb47e1da"))
    (166849, uint256S("f7234f24af3a195a5af2c070a096a7bbbb3b38ef494797500d4e0b03fca9c68f"))
    (169199, uint256S("484813582e3cb03ef2946b41793cf63915829289169940772255e04d5b55ec95"))
    (171549, uint256S("600f6b889dec335c861867b55c70d65ec2c0156bddb97a19d2c046b0b50b5896"))
    (173899, uint256S("c48646e035dc6d7ff92ff1b2575632f0d41de3890469ec2fa855fc34265f1d69"))
    (176249, uint256S("bec8104253fc07ca5e185242159dc45146ab35cca8d4ef721753a09d4772e4f4"))
    (178599, uint256S("cc51c479c6221bea693cb3186e1c6768a123c440ebed92628ebf7702eb797c56"))
    (180949, uint256S("d59209600fbc023bd8aa3b9b3c92bd465d72d973efc5c0299cfdfe6d694bbdf3"))
    (183299, uint256S("f5c8896fd0d891c710e5b8bda5f77c8e730c823b750e9d343df856bb5d13b0a0"))
    (185649, uint256S("87ff7456aafb798fd0f7f1861694bfdaebef5482865a05505092288fc5550ce5"))
    (187999, uint256S("798a844eb7a174ce66503cf80dfc384ecf8004f4a6302c9cee67e90488d8c23f"))
    (190349, uint256S("3e47d650694fea7b0b54c6f2e6c51f5cc72378ac5343bc709910bba33849026f"))
    (192699, uint256S("afefbe3512d97fc05b5999392e0f881745f034858bd019371836afcaa5013c91"))
    (195049, uint256S("9d657cfda801fed5fe6f78497c4d6863d7203b9d1c7cc826a6d2164901027a17"))
    (197399, uint256S("6786b6244de6c6bc9c94ad9ba981ca6c9e31c899e442e6c78386e30dd59c88cc"))
    (199749, uint256S("0debc232dad6057db0532e30b2c79635ee9e28f4bec50a38f10b38f5ef1293ec"))
    (202099, uint256S("8abb176b0dbc9e3219c68454ed0a38ec8b7aa1282dcbc4577b1ae601bb7086dd"))
    (204449, uint256S("94710441af34f9b0964851900c5e4a2978c5548db392014145ca4855ad8cd5d6"))
    (206799, uint256S("c490ede3825cb57c2de538c543c598d6ada5dd6a7823a81ff75fcbad6690020b"))
    (209149, uint256S("29eb3f1cc3591f16463c9b98451cfe5379cd66e80d1af37471ac01f67b6909d1"))
    (211499, uint256S("0c60b3f144f1fd008ba0f85e9b157d537b07a1ba39314dfe4ae9efd9c4e9bebb"))
    (213849, uint256S("9f127e3627d92a7304ba80483a1054b56a77a07a06af68c9746df577c397a30b"))
    (216199, uint256S("e886ad8a50a3dbb766721bd6e74794a176efbd891df2662ba0286dcaae59f028"))
    (218549, uint256S("8bac856aea4b4b58604d374b118dfb6a57b943bc296a9effc6342b8515ba7c1b"))
    (220899, uint256S("741cf09f0919df3143c6886c32f16bde768e789990de34b27933d5681e4acf78"))
    (223249, uint256S("2fe1c8900a6803429bfe4964b34f5b9b63a627b5488326e2990be24699cc205c"))
    (225599, uint256S("7f0e50c241bab993521d180af71475299004f58ca59a9b95230d995a1430bb55"))
    (227949, uint256S("279557893a08bc99e4488fdb08b5ec711816ca8f43583b13eab0c0b168429517"))
    (230299, uint256S("1d7666058b9fad7eee95aea956c9150414472fcfe2e595aec5a0dfe92bd3f7ed"))
    (232649, uint256S("fb227460d8ddf6737b44c9c200ebb182e1767c73285f93b7d0c2b5f97519ab4e"))
    (234999, uint256S("9446b1c9952858bcd366cf5f4fe28d2d9a5105504ce17849fb608b2c96b8389e"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626801210, // * UNIX timestamp of last checkpoint block
    577720,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2936        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1612360301, 882189, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"));
        assert(genesis.hashMerkleRoot == uint256S("0xad9cdf0829529533d9ebcda4f6981195860fdc01c7f6d3f14b847695835fc872"));

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
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "0371d4e47e0ab43865206e9df7c065d6c68471b154bab3815d99f8380d46c7015f";
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 235001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1bfd90165e662b99293bbe05a321377d0dc2f2bcf36d52e5abed63c4b006ec6b");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c17d7ad9fdc95b64409efd6c52054c8d547e72f0e3b5059c7148cbf345057768");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("8f53cb83a9d6dc495410377428e2c85cd80367456d55a82d64bbec5b0960286b");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7a8aa7d86ebf47008da5b39ba6eb07c380a6638a85d1a632de326a4f5238cc36");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("cb863ebd9d14c47dd733cd9a90b47e79a7ab82250a60fa6009eeaabf89778abb");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc8;
        pchMessageStart[1] = 0x7b;
        pchMessageStart[2] = 0x86;
        pchMessageStart[3] = 0x77;
        nDefaultPort = 17771;

	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.777coin.win"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 15); // 7
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x1d)(0xfc).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
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
        nDefaultPort = 27771;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed.fuzzbawls.pw", true));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed2.fuzzbawls.pw", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet jackpot addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet jackpot script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet jackpot BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
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
        nDefaultPort = 37771;

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

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
    const char* pszTimestamp = "13/Sep/2019 The EskaCoin Launched, It is fantastic!";
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
    (0, uint256S("0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"))
    (12005, uint256S("508ae4005be85e2b7316067df6d72f87bf06edba50caf0f4fb7a2b27cf6b8955"))
    (24011, uint256S("06e26832460a77a8d965a59251c91c58ad8ec8b8cb554bbb47fa19c81479f8b5"))
    (36017, uint256S("cf4d1eef2eb6fd5b7d64f7261fafaafbed9cec9d4216d485f37af4fd1d09deca"))
    (48023, uint256S("3cce4af26991e36c126fa9aa8ffc7d5a066647b2b5c88b1ad103dd56198f69c5"))
    (60029, uint256S("2b048c24783fa524188de9a49ebe489b31d8a7c47fd98a0d6ae7e6de909a9f0d"))
    (72035, uint256S("8d6a8a48dbace1872b9e698e02ee9d42da81d7e7a38fb87e34c2c6a7feb4e6ba"))
    (84041, uint256S("bc4b7afd75439dec902087500170eed54df045e6454a5882e7f14d422cccf63d"))
    (96047, uint256S("913ba4c9089db0a37c0eacb6055a3741cd4585348e2522be9275ce1e6c0e69a8"))
    (108053, uint256S("72222f07b8c03c3aae804d331d7854858236e02fdb68095eba1a821a530eb671"))
    (120059, uint256S("f240ee2f48dfbb41eff8587fcf24860078824e3f0429011cb741e4023813a6c8"))
    (132065, uint256S("c9528d1a41991f3701737a8d7de46052c37feb418356079c03fa155b271daa09"))
    (144071, uint256S("88034b883ea99a4869e6c8cb66026b8f28eb65badd7978409560b1a2e39a2c5d"))
    (156077, uint256S("b43cabe0885d59a62f29e1d8142329a37d713acfd99b0f7fcfeafb390b7f5c46"))
    (168083, uint256S("361fe83a98294d64802900454ddf86c5d6b4e976774abf3e894b5306f21d5433"))
    (180089, uint256S("30ffb5a13bb4f943476f140a031b42868b501d47fa6582bbd9496a98671d90f4"))
    (192095, uint256S("a613f08e07dbc3cca604d1fd843dbd60c47097e8f3ef33ca0de9464218c7c98c"))
    (204101, uint256S("9517ff6ac4e9dba16b51f87fc4f3c9c01b757a268998c92d08d481fbdab58f10"))
    (216107, uint256S("e151247c82b7a6146edf12b73456b955b467ed6ce767dc94a1caea7e50f64fff"))
    (228113, uint256S("3666ba1439114c1bfdabf9cfbd4cc50104d65050474c387123441075434ea196"))
    (240119, uint256S("e3312d994f0b16e2f3855ccf61588086194219e6677748b8ae17f563c189833c"))
    (252125, uint256S("0088a2fb505f1aa3159ee4e2e5272011534fa5fcdb628f42a79c20d5642c8161"))
    (264131, uint256S("f6cc0285c46ba1f4799ab6a375e5ae7439e7c979e9a3130f7f06deb78937722c"))
    (276137, uint256S("fecfdc6b1969dd0f5513dbe3d1c5102f7cd416a05192953c038ecb750c9ee91c"))
    (288143, uint256S("d0a4ee8a5e0e43b7b2b97ec6085f53fe1c581e7be4b90114f465f255243bb8a1"))
    (300149, uint256S("318661479b56e9636df31219bc35dce7e73b524099f289ca12d704ec9f579e91"))
    (312155, uint256S("bed168e9544c632348a6cab7c6b81625301b34090fff647587baaec2db2a15d8"))
    (324161, uint256S("0988e9d727336b1bff8ac60c29827d3274a92353ce15211a3047a18da7be8a6c"))
    (336167, uint256S("51b828b54bd00611e025ecfbddb5e986fea3178ae2fa1cd60ef07bb463272777"))
    (348173, uint256S("9363af3f5b6d6494934ac1509575e28cea50dbfe61afeffd55fbd09224f09789"))
    (360179, uint256S("e9b4a55c11a30a77c071709a6e97c3ed4911d7d15791cb48a0e287bebc3be076"))
    (372185, uint256S("8050f0a6d0544c0bcbd49765201166eaca9ff02056f851d64f2d3f1a3467e34e"))
    (384191, uint256S("0ef9d39a53c87414e0b3b82d9162a4eaded4b3b09a2b07c6af7023fda27dbd56"))
    (396197, uint256S("ddef20418f76b9951c80d508ee3a6cbf618e90b89b156dc9534f4b5d9f6e3adb"))
    (408203, uint256S("bb2696f51042cf2e8b1639b147a0b80892405a3cadbacfea2ecd354ff57c44f7"))
    (420209, uint256S("2b2fde8216231b9b292e4292c78aa2e5b4f1320244c70f3c13a5fc1c361b8af8"))
    (432215, uint256S("3ec36303221cdbaf33ce4b20a1f8b9f174137545d79d7c139258afb0a93645a6"))
    (444221, uint256S("fda68147fece1b9913586dd1c3f68a9d1b7431e0c363e3ab2a380ceb1defeff8"))
    (456227, uint256S("9e4186b3fd0675e9b4ec88bf9bdf6c8d596c05c5a0a9516d0b87f27a2661df93"))
    (468233, uint256S("6cb6dbc73c0595a6ace16525f61228d91c2b47b60955c7cc32d20cc09958a477"))
    (480239, uint256S("316b18fc7c5480a0bf8320939ddf79109089994c2961471b51e940997c6d3b28"))
    (492245, uint256S("d7b2022c87fd7210955a5c696ed08bf67aba10e44a83400ae52fe2ab7a2664c6"))
    (504251, uint256S("f3bd19e78ee6548d00934eff3914da4ee23db3d355c797fd3e2a4d3bb0e8b106"))
    (516257, uint256S("ece50267732ffbf83d0669d90d88807d2c8f3afa58f406b2571269b8a05f6ca9"))
    (528263, uint256S("167b39d4136e1e388120545d19c33d214e3d6d38f41d2e1f4707b64f534c8f14"))
    (540269, uint256S("ab23ad628aa32d308445cecb73729f69b8050aeda5f498e4819e2aa9bcf36b8e"))
    (552275, uint256S("f77f1e43b79618bfb0b98d88a49b6a49f23b1cc1f0c242d5d01772ad38215f1e"))
    (564281, uint256S("4b9ebdee96e472faa9847181d19bc60ad726ab15042baeb1ec29e43ad2cac9f2"))
    (576287, uint256S("ad9787ff97352530ddcd0be85ebf09188a87c7a38991df7fe0e6014519d2fe4f"))
    (588293, uint256S("ba6ac0308f233b4d4dbfea22af82d366a51708b5fc4514d06bbea7248a4694ac"))
    (600299, uint256S("873a280425042577bb5b8f721d633f6d3b1ed2847a9c4fe3b0a494d4c776ac4a"))
    (612305, uint256S("540c8cc1a32e4baf167eb69c63ca34f04bc287a9dbac12a08ef2f5f463df35c8"))
    (624311, uint256S("a3734ba99f098990c00c9b69d539d4d749cf0124167fea079806be9a5e21ddf2"))
    (636317, uint256S("360938a62bea3a75e8d9d449c9a38716afcfe2b9a4bba850e146fb0cac9d333c"))
    (648323, uint256S("35e2e2929c5602e0eef706b303c1682ed4bf98f5fb49a83d4c6611a155a8b8e4"))
    (660329, uint256S("ca77b655a9ff83d8245c302de8896056fa6979f6a1430cae9a6541e0e8df6617"))
    (672335, uint256S("701864fbc0863da8b5d9cccc7b0e36f0414db90913eb0de6b9331e3f706bac15"))
    (684341, uint256S("28f955b91feab0415ce5a14afacda8bf6a9ff46d31dc3c38b00a4812ed28cc48"))
    (696347, uint256S("f292dae436aa38cc04b392ed570eb0ccdcf5d52755ef2bdec2e5a170fbb4c7a7"))
    (708353, uint256S("3d14d000e826a5b7fd56b5a07ccdf2d2b761c3996daef5fcfd78d8391b2b14b6"))
    (720359, uint256S("7ddee86570fde30ac6148812f28689997294e8c0e88aaa6d7aea1d075f7fe589"))
    (732365, uint256S("e918a093f90a377af0f7daaa2f4a6183df221854dfd427e10d38dc86ced17f08"))
    (744371, uint256S("08b43e56ed5f5a937fba564fc18f1b98d3facced5d91333492ebc0c1947b7311"))
    (756377, uint256S("88ca9ffca793784f10d287819e2e37a874734ae3ac42d392bcde7c4a4f7352d8"))
    (768383, uint256S("c647ff498431c6596a3760c0d46ecc9d867646964f4d056d717e3373e1b4a954"))
    (780389, uint256S("54efb78cf54237d2daaf60e9b084f98a08534fd89142b937a46822afdaa6d68b"))
    (792395, uint256S("020809161828809a242d79e6d8ac49f06446d52933471231a9c91e607f8271e7"))
    (804401, uint256S("e7f35ff2318ca7a70594c2d971fa24f0391915c10d541a655df6616a346bc369"))
    (816407, uint256S("391a4676040319e9b026a3be45bf4dfbdbf72b8b46a28095ff9aa157df1dac90"))
    (828413, uint256S("a96bf0615bc6ecfc235d867749176784a82edde4663f5438d93294a3a66fb993"))
    (840419, uint256S("400cd9f4367e4be8f40829b803b04e73d19c33210b5455c68434d4300dc7ec60"))
    (852425, uint256S("b25be19abbb06b98ccbb1dd262d2763a5004bc83055697e16f4a3bd6f05a03f1"))
    (864431, uint256S("552a8b7c222e3ed32da57a9be8bb303f2027839015f03fa02a21c9618383fd42"))
    (876437, uint256S("5bf53dea3fac8d5bc2864b3be438ea19b6cb66d294b5d4e5127cb523b39ba55d"))
    (888443, uint256S("618ab48069edc8050df3c56d87aa520f25dc02a03ac0a90471cf8017f3bcc027"))
    (900449, uint256S("9bc2b575f94b6688b75d5ade99f988278e07a7a22711bc868dbd6bbd38b8a864"))
    (912455, uint256S("9f0733cc526bc812a127e0917db16a4d22104b9f1475bbe89a8d7764876155d6"))
    (924461, uint256S("679e95bb8c25ff59e8ae326d218a2eb85a543139f6c119ae971828ec4e9fb53e"))
    (936467, uint256S("ec787f4195faad5ec5b522be556cd8a3b747b2f5c503f9249a2a22051b01c4c3"))
    (948473, uint256S("90e07777716ae17e9fc52100e9dca6d4a00cc6575e1259d3f75fc397ea1aa8f4"))
    (960479, uint256S("d2d252e4ce1bf81ab257ac9496d0faf8e9e4abb802d636a798520d20c08e74ed"))
    (972485, uint256S("b92f28764ebc4a6527a873382f330b71f4db5cc3a5eb064d1cbffc5721072516"))
    (984491, uint256S("7ff6e25afae2713e2b6f010cac824be96e01f18222fe1e10e45dd50f61188390"))
    (996497, uint256S("b11ac62019e3b03894d67eac0bf57a3c59f9b33ef8c1bf3c7efc6e6aac6123a2"))
    (1008503, uint256S("ad2df084b6af14b89b5432ff8d3e6a104442f3ee13031a9ba8d7837af8f56e64"))
    (1020509, uint256S("402aff808a5b14e189154fe15a78373b91c6ac7b5e3ddf2f15414cc0838bb364"))
    (1032515, uint256S("37a44547ef9b58a0320b04355451d5a1f235e2e9b2c6d4d021b5f5fb0c0f153f"))
    (1044521, uint256S("4f0adf84d5c35a25f304e13f95472a3295608dc89016ecda7cc3951c5311b259"))
    (1056527, uint256S("142a92741fc7c24870c3fd4b4e3b39a82bb4ab0dee5049138ea7dcf3b88fe048"))
    (1068533, uint256S("21169d4b000eea6d22a73445ccc866ff0a2aa1ee5ffa5eb5298c8c747484a59f"))
    (1080539, uint256S("180868ff99143f3a52e40c40a2431cbeb2faa46a2fca5280ae244041d125b471"))
    (1092545, uint256S("addb399b2a735d11ca5e942a1ab1be99fd56dc341c490db0c4406b0f298468ec"))
    (1104551, uint256S("b902e7096b9dff0f66f9121397d6f15e936b4ed80b5456a18ae7a2166825a549"))
    (1116557, uint256S("fa9b8e164394c96846fa72fbfff4178f87511973f94f8a7fb9b1969963fca5a3"))
    (1128563, uint256S("5a62ebea3200cb46fc736653aa7937a0f65ae27a42517978927373430731185d"))
    (1140569, uint256S("2e5e30a82c4fc5cbc08e886e525f695db10e1e612100dae7089a249b909e0fc1"))
    (1152575, uint256S("f187e1931a24a3c7779f18b6d15e1ba2fae8e773d1829606b5e025cdcaa6de7f"))
    (1164581, uint256S("4a8dd65df9debdf6fedddb413e63927104f3a2cb01023389b050b827efb0f98f"))
    (1176587, uint256S("c62544e303aaca8f4e3b5efc496c84567bf9a05cac06f2226c7c152f97810308"))
    (1188593, uint256S("56e4c033413d5268ec00924a963ebfc54c976ad851cb94a9e7a4f5adbe53d405"))
    (1200599, uint256S("15a4e024d7954ac57199d7dc5de66484e7c9e2eea00ac37c35f6c89cf61888fc")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643048685, // * UNIX timestamp of last checkpoint block
    2933758,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2824        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1568452814, 7414, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"));
        assert(genesis.hashMerkleRoot == uint256S("0x036399fee1c5e4dcfa9c8c4f2458899d6de3a1ba0df04e77b7ac10bd09847b12"));

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
        consensus.strSporkPubKey = "02aeefc7f24b3919ff05a7d2661aefba6c37ca77c263a20e8516dea630fa74e9bb";
        consensus.strSporkPubKeyOld = "043B44A0D5F6BFA822208E19096A6F71A144EA1034A5ABB99E458DF1463CF98E72FEA9E5C5038EF7716765D248DAA709A23746606AF41CAC59DC071E89624C9FA2";
        consensus.nTime_EnforceNewSporkKey = 1626393600;
        consensus.nTime_RejectOldSporkKey = 1626480000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "EbURNXXXXXXXXXXXXXXXXXXXXXXXYdqMFj", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 252;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 930001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 300;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 930101;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 930201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 930301;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 930401;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("00000d59619662288595b3e38ab67f243e60fa47be9b8bc49ee36d835cf1d2b1");
        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("4f223b064bf7ec695c08bb41701ac4e59cea14169e86a2c5f802c8c6c29508f5");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0a10b03f191d41ea4d7c8f2170b2b5a57a193b77270e83185c60d0ab98ea82ec");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("6124f4600579296b9dd3973c13b6a24ff84aa0fd06e66b35356cb229eab8a6d1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("aa274bbdbea34da289250e73078a5912e6edf6e93977bd8474be1527993ca09a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("537221a9b3179f9d95c4d84c6c28321fe7cc1d4a1cf2329e1dde87643ed39187");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("dc97bc8e643eaddf4b0b0726abf437f39ffc7df5eaa646957bf7b03bf817c5dc");
        
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x1a;
        nDefaultPort = 14215;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed1", "seed1.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed5", "seed5.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed6", "seed6.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed7", "seed7.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed8", "seed8.eskacoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13); // 6
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 145);  // 2
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4D).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14216;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.eskacoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet eskacoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet eskacoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet eskacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14217;

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

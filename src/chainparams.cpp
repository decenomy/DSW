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
    (9308, uint256S("d4dbc49dfc22d29e7e8f175583af282a7c9b13d5429da6de54ef5dfd871a1f9a"))
    (18617, uint256S("01cf69e25f352ee6952d015bc02f268ee475df0b8bceb4815552588300722a9d"))
    (27926, uint256S("24b08997dfe8917e79a06457381c31a8d7a019fae4c80106b898b6bf2b5700e2"))
    (37235, uint256S("68ecce8a72fca5acc540a0532caa05459d95b0648bba37b85645351be238a162"))
    (46544, uint256S("fa38fa8f6cab2c9da3e87f8aabe7eabfb4c25f7fec01252b7f5c3f61eba04b51"))
    (55853, uint256S("ce8e7aebe4a19298df8c1aa6a0fb955d9797a20cadc7f77a94d9d823e3d28af0"))
    (65162, uint256S("bcafb7fad4c8408cf59f9bd1ffac8c099ea96baf1f363d0086eff7573367b806"))
    (74471, uint256S("f02ae52f5b6dbdef055a6ce99f27765e2bd2bb97c7e9207c0e35212c81874f86"))
    (83780, uint256S("37b8cd43bca48e936420e019c50fe008705392eb49804e8afddd49ffcc8e4b25"))
    (93089, uint256S("a52c092f6e51d4275e9faa061ffa8d0919ac3c0da3c11c683afd4367a113f317"))
    (102398, uint256S("0fbddf5c8283d59f4112472a971ce1b925519838e43520900c45ef20e9c06482"))
    (111707, uint256S("f4de3ae529dddeb167bde7e8314413b5360efd327fd2b5c244eaa59fda8289cd"))
    (121016, uint256S("ee85acf87b43b77216b9bf1fa2053eca0f0c48e0e1e3aec55b55eb2036adab38"))
    (130325, uint256S("49462d2e2b87e3a8d8b497bdda04e5dc2c528119598ab5693126da59e68b8b9d"))
    (139634, uint256S("8c1f14bf1ce11386a22e9129a871868e067a61354a618a59a13e1cd77c7482fc"))
    (148943, uint256S("b0ebf3d1ad16fccb2f89500674b66d3fd0c22dbedbd3ccd0bf43a2e62fc4bae4"))
    (158252, uint256S("32e4d1f509dcce4452a69698431290320d818c764764f2230bd5a1e9050f71d8"))
    (167561, uint256S("d3dcbd48bae0f081e67eef5be19cb7cbc0f1706aabd16676d75e1b5cccf56a33"))
    (176870, uint256S("add6ca6bbf8a31bc0e57c43f8a71d2b1fe55c559195868d82c4ab045c2bcaf58"))
    (186179, uint256S("789d45e71c8ad48532d4c8943ab6702ad79f7537d620c88b509fbdec8c7d64e0"))
    (195488, uint256S("6551856bbab3c9fa3034af1dca0d1340a5f9ddbbc184e13dffa9bddcaada0241"))
    (204797, uint256S("b03a754bf518c1ade0c2f2444a397a3482cd927e5ad4998cbafe597c4a0aaf31"))
    (214106, uint256S("a5241b3e3e5220c49029e5764dceda3d780d4adbad6f0c535d26cb506017093e"))
    (223415, uint256S("ce3da62d329046d74fd4927e027d1e62d682adbe70fbe25650b3d0ee48215653"))
    (232724, uint256S("395be309c8b34e73a466cdbc7b85d85ad979b9bbfb5c89b1def2f8487a6883e1"))
    (242033, uint256S("718b6b67a9821d5394fd9541811c19b9996818132680f03614f334796a8468d0"))
    (251342, uint256S("3abd78d10308e9b1d7034a82841124ac0bf25cff47e661b1d68c5b658758addc"))
    (260651, uint256S("630507206e3b1bef5739d2d291477573929032406ab1de94a5461b8a344319cb"))
    (269960, uint256S("b945d87442caa79da4fff95ba7d608bb8d58ed0d6e2298444fa229c03821f1e6"))
    (279269, uint256S("8e1a160ab763dd61ed74fd98a046321489450a0fab48e07598cd5f874dab5ae5"))
    (288578, uint256S("137e994658f54d9250ab200e46a287ab2fd8c5bf9dbe643797652426af5781ec"))
    (297887, uint256S("cfce2912c70715788127bd27f78d80e8b5487912c79034c1f90a8872af212274"))
    (307196, uint256S("bff3a114fbab1978dd9531ea577abe17e8d0198f1f58ad0947a020dd08fc1744"))
    (316505, uint256S("cb6d361ec91c538e0b3a7f03fd1f1ef8f2bc5ef16bffd02402e2dcb587114d60"))
    (325814, uint256S("ff3e390c4aeb97f1689a0dc984f7bf5233d5f4b0f725e1a5603c0d818ab110f1"))
    (335123, uint256S("70340426614d58a44430ce9cc4d2bb0c2c65196c2a6d8a35d3a81cf1ddef58d6"))
    (344432, uint256S("2a9e49059ca01dc8b8a3ee76bd053578bb835116c5d78524c82c3221d24611fe"))
    (353741, uint256S("4be125794dd9fd74cf98052e7993000ee1854745c74fefda68d66064e1246636"))
    (363050, uint256S("09265911a2a2097a5a800abb980fc5cad090749bc3a33458dccba54f37f75d98"))
    (372359, uint256S("e7c0d19de3509d93f80268e2f661703c348def7bacbfe132802fa0bac48c266b"))
    (381668, uint256S("c2c939ace6ac1f86a58af6567ada0c6e773da3c2af26c7c699b83e6446a7c4a3"))
    (390977, uint256S("34e3d51a7b1a2fd87af16a560327197749d410e5e4e0ad6495b0d35f8d4c1fa5"))
    (400286, uint256S("787a4e7a7ecd572d84b8490c539cf5a256fc2f4a7c627560ad04cf79c5d360c0"))
    (409595, uint256S("751850f7b58d72481f3ecf374357073dbac6ec37b7657c65557b95d61d86d54e"))
    (418904, uint256S("8817255e5f1536034b647f7393765114c3744c1e09d06f421f3d1483ce243fbc"))
    (428213, uint256S("a6d58d58c3a41093bfee3de8e249bcab1b20fc287ab58453650225ef460093bc"))
    (437522, uint256S("36fb6977e966f0d671cbcfcaef8da24a158d1598412990e3e5e6ebe9134ecf94"))
    (446831, uint256S("bdf7488df908e4ea9dc03a71e81ac65866da06e300e9717fb397e90606edaf6b"))
    (456140, uint256S("29b592d6bc854f80f0ff12f9ab3d1c9baebfffe87a4eb13b4c87b1a8e22ee660"))
    (465449, uint256S("495f57512bc9dbf0980a82fc52e121b039a0dbb3ee088d17cd023eb28eb728ec"))
    (474758, uint256S("6c814112e794a28723865f1c9f8adfc2a880ea0b2fb1926237c5bc63fec45c01"))
    (484067, uint256S("3fc0e8fd504ec8841da34c1c290a0dac15189b426eba249695981550abb88a95"))
    (493376, uint256S("78a540e7970792507ef0fd841a8aeb97d464d7ae83add055195bc7707cf9a5af"))
    (502685, uint256S("ab7587717245cafabd8c9ed232f414b7b493e6aafeaba619199492cccf6ecf4d"))
    (511994, uint256S("5fb5ff9f55a74aa123149012786a631358353a12fd9b92923ac78ca797f8db54"))
    (521303, uint256S("8e3c4647ee52cd91f1310e5d3b5df4510e54d35e9168ea417820b48936d979d5"))
    (530612, uint256S("00f99f5b6a7090fb6d179aa5c31e1eb873e7b7989752649e6599dd9ec441f3c7"))
    (539921, uint256S("6384db6557beb6db81c5eb56553de42adff9afd06b8a62553d1b373e1c1f3ad2"))
    (549230, uint256S("dff759a03209a346e81a4d39fba4445c38c2a225fd1aff761b0d0916c5345559"))
    (558539, uint256S("8b1e1f76349edd1e0263afbb8f8c4bd00621e4d953f3db008f95325e47671006"))
    (567848, uint256S("1da13ac7b64965f71841199ca949f009463c686a3f17060ccc1f4a81b86e2598"))
    (577157, uint256S("4fdfd1bc21a3f17fe792857a1566f2307e238de895d6273c41bbe57e243469d9"))
    (586466, uint256S("8f25783706de56a531ea05be7205e02bbad4c8785405572e020160fdd6b8af29"))
    (595775, uint256S("40b1a012c994a4b0ac4bac6e4d38a68b7cb56420b04f8be67b73496e46785470"))
    (605084, uint256S("141c1be0ef310d6b7e26440de9128af92b9fa5407f496d1c4ab3dd7e5f72959e"))
    (614393, uint256S("f8a312a22fca996fb1f46f86971a17381fd26f0289546c1283dbb87c1ae238a0"))
    (623702, uint256S("2584d74681b443afed15e706900d2c1e270ca543eff25b4a6df96cdc93e6a75a"))
    (633011, uint256S("17fa1416ffb68cbc8cd18117aa0e21f0bc0628f8b212c342133eb8e0dcd3ef46"))
    (642320, uint256S("9befa358411646ed379555c23fafef9518e96fb093ff1120d2d2715db81ec630"))
    (651629, uint256S("7afb9c315b8e0019254edc485f79276e443b906a853b87b6fc147679557a5ad1"))
    (660938, uint256S("3259b8fdd361abfecb8f707eaf39e4a9c607f87a7166d09318faddbe399e1f1d"))
    (670247, uint256S("f62a6cc8160cee1606cfe3815e5f6d6f9ac8b1060b1ecdfd8f2beeaad3da6203"))
    (679556, uint256S("65a504d782267fdda543bcea982a62de33477eff624dc9b3e361b295b2fada1a"))
    (688865, uint256S("de53a1bc9b200e24cc8bc056455779ff5c9a1d9f484eae5bc9a471ea7c1703d0"))
    (698174, uint256S("871335a69cb86133bc217d8e8081f78a98d9a4669ff6883228f72a5f1756e447"))
    (707483, uint256S("774998d9616064171b34c25d241c278b30c930ff9a49c7d077b2736913659838"))
    (716792, uint256S("b99adc45f393f6efe7fe3bffbd6d10d65c63a5087a4b3a9b9858204a7aadb0d9"))
    (726101, uint256S("682031e9c266f56511b12d7d35f1e78fa5549546a03e920dd120c2a6c7ce981d"))
    (735410, uint256S("7fcc827e4b8957fe354440840ba5e4ce0b2da52d6155c78c89b42c74d0ea6f1f"))
    (744719, uint256S("c2362776784c2b4b463736d33ed69badabb848717519877594dc9b423f9e2a86"))
    (754028, uint256S("f863b273039f6eff1e8bb2ac7786a215a815f67fab5a2523a08fab01c504274a"))
    (763337, uint256S("eaad3e913de768be9bd8e82b865b9d05944c1e364e543b1def6282decee749b8"))
    (772646, uint256S("0b23007882ba6feb166954b898c7ceb19f47b199b3cac4c078f7d65cba1be069"))
    (781955, uint256S("106c1b3bd7eafb18fd68bdb7f4971e3b82d51c2d1d455816a57368bb60ea0ddc"))
    (791264, uint256S("29a52a224a12116e7727a6a7e5e59abd756e257dc63bc41b6a3880f1305bdee0"))
    (800573, uint256S("3c720368afdeed4483b6706dc74f57d72884b235df4f5be2ea6a085756a2d8da"))
    (809882, uint256S("fcf241518a07006021775ff66252c12b9935383c72fa88c77513fccd743d3139"))
    (819191, uint256S("4be91025ca0331a516740769d5a02496a9bfde1434c579a6c2b3de37e4b706a2"))
    (828500, uint256S("37bd0d6cc4d34f46eb92e5dce5cf40cdaa1207eb0d6f0bf71f0ec7ee2ab4dec5"))
    (837809, uint256S("9c3047897c189c2d04a979ced623b2f864afdea58f933c593ea6848a8e007925"))
    (847118, uint256S("3301b78f80316d44ee7941dcd3004f44dfa0ed34d99ed459d85140756c3dd795"))
    (856427, uint256S("bce9d4d4f94d1ff46d47ea16751d74329e5e78cee69d1e34f582e789aa38b3d0"))
    (865736, uint256S("97407eafe9769b4d3017362b042765334c7ccca086597836750eba44c0aa66b0"))
    (875045, uint256S("033761dd2a8145dcae9254f38a47cdb2bf8ff980209edf29abd4eb00ca87224b"))
    (885247, uint256S("290cb864b8e6aa320568e6983356b50bfe9cd153199a2583b197b9a811cea044"))
    (894657, uint256S("207c44be4e3050256578e5613358496b4d6d64f743b499cc20da96163b44c894"))
    (904062, uint256S("3816ceaf5a90f678eddbadb17869272984034b633d5e9eb2c43710ece8626e0e"))
    (913501, uint256S("feb0c1a794d5719c91a604c67b2907ea7c3f7b516556891b44b5e836c8eabb79"))
    (922862, uint256S("c8b3a4caff19055e85fe56aea9ee28d94d9a267d88dfce021d1819474eeeaebf"))
    (929119, uint256S("c1627be9f14f6f6b37611de52fe2e934d7963cca8fbd7e6ec95015d149a523ba")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626106628, // * UNIX timestamp of last checkpoint block
    2314256,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    4880        // * estimated number of transactions per day after checkpoint
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
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 100000000 * COIN;
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

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                = uint256S("00000d59619662288595b3e38ab67f243e60fa47be9b8bc49ee36d835cf1d2b1");
        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                  = uint256S("4f223b064bf7ec695c08bb41701ac4e59cea14169e86a2c5f802c8c6c29508f5");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock    = uint256S("0a10b03f191d41ea4d7c8f2170b2b5a57a193b77270e83185c60d0ab98ea82ec");
        
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

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

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
    const char* pszTimestamp = "Soverain's blockchain #init";
    const CScript genesisOutputScript = CScript() << ParseHex("04dbc25a9a48add73d7f65d1ff4ae6a1fc80d2089fcdc78dc8e5088c6d27df962f393a07cad6fc632f6b891f5c81f970bf282679c39e581f856d6a94c9f814cc68") << OP_CHECKSIG;
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
    (0, uint256S("000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"))
    (20298, uint256S("442079455767545bcdabfef18a27778d92a0aa9bbd47662a556206f68169d1d5"))
    (40597, uint256S("fb2626b7f23927985df8f301791733d9e714b2b047240e16d49d52fdafa064f0"))
    (60896, uint256S("89ab233d7e82b35f37a9f16a36f034f1ce8200fe9777b4b92dbdcafd159ee761"))
    (81195, uint256S("50dc2fc7573d01a776fd21489ee9c6200c2370dee048e9eee16982f32578b172"))
    (101494, uint256S("394a8b43de98a5500e3cc72b49245804b1d91495089744c44a2bd3950e32aef7"))
    (121793, uint256S("f0ecdc6cce84050333fdb30acf353754c2f9d816d120f9886735d2bd6561831e"))
    (142092, uint256S("39dacf456165979b918ad47f2e4d648369b97152e30aa0212f556f3c0f19db2b"))
    (162391, uint256S("948dfa3bbed019c70bf7242741117792c4405024db42ffb5681ee2bebc9770d4"))
    (182690, uint256S("1dd4da26c0be8efef85f82cccde1bdc9e4a1ee6aac68cee2b585f18df04d6e03"))
    (202989, uint256S("a02537c78c5cb8304e7cc1b6840e1223295da1d9acf92b5d1f41b499566d7a67"))
    (223288, uint256S("12f94490c2c6b80598b4df5619c39c56a69a4094fba8ff8e9db0fe10b07bbb70"))
    (243587, uint256S("a28795b660b23708b2376422dac430d64d27ecfd5c132873f1a2d2197fbb7436"))
    (263886, uint256S("98a20562b2ee8d894acb4e4a9fbdbbc4ff5d4652d94b245f2d7ebc5016beec5a"))
    (284185, uint256S("f2630a810b162d01a4cd487475c2c9c97bb623034e8457b38152892ca6b04afc"))
    (304484, uint256S("75997eda64e55b6cd18e3f312f17113266c02ca2292c3d81e0157bf882b18ea3"))
    (324783, uint256S("6cb2673839b152c53916d4de9dbc6a739276e6daf1cdc4c502acbf0ef53177cc"))
    (345082, uint256S("6d01f4a1736594a12d9e8aecb1017518b11074ea01c53d09df204477bce5de3b"))
    (365381, uint256S("6abe6bf617d99c5e598abdce085df9ec4c2ed5f41cab457ad0ade06d0e293a0a"))
    (385680, uint256S("fcbd653e59e392c2a4dced24ef4d5ddea041920839f4997f8b931e14c662da28"))
    (405979, uint256S("50f15c2b2a2416ee4319cf82182e7b52680616d9d54dd821bc3d0fab07a2770b"))
    (426278, uint256S("0b1b0c0a9ac58a886a0d432bf8710580161bf61d1ea74167f0ab4c40bd657349"))
    (446577, uint256S("43843035051b51e4eac450986fbd35503f667b5c863f8c55d8fa2957e225c01e"))
    (466876, uint256S("f236c71acb4fdf7bb950b9bdc1583151e091720fbfa98151d5a282b6884ad5e7"))
    (487175, uint256S("080d1e24748f58242e340e09b39476399bb4b6608cb4650ec0f692a2cdf72e46"))
    (507474, uint256S("72eb419f84d67946e600daad712d68145ba630d0f11af3e3b7dd7907bd8a3671"))
    (527773, uint256S("ac611f2c5b715c3ac937a54463312d039ddd705fa184edf03ae2bdf581107e00"))
    (548072, uint256S("fc9c758d7ffcdeb23ae5b98a804e1b13e3add606ff16b396fd0485edeed3d973"))
    (568371, uint256S("c0d19cf94f7bc34908b76fa2a2807c5c6ff049052bfbd93701d39d0023aa3695"))
    (588670, uint256S("7cd77cd2aeb01ea741cda623ba9aa40119db123848ef12cbc9a3c686350af995"))
    (608969, uint256S("2a18a931fbe045011e4f7e9d9b9c46f12bf13488530361d56d4e384b7cee1226"))
    (629268, uint256S("ff28dc2c02bd001a976d75b0bbb806ba17cf07c380fdf84378cc2fcd4eaa1dff"))
    (649567, uint256S("fae1d7848dccc51b2897a68c769585dbe76fb6ad71ae3e4234013ec12cf14fba"))
    (669866, uint256S("3ef7e9092bffc0ebad98f0e44a25fefa0dd7e7b7a873dc3c1a111fb590808bcd"))
    (690165, uint256S("b13f46d92f3f11e7e09861aecad4e6fe9a0081c05509cb8774dbbc39fa7c1b1b"))
    (710464, uint256S("679027bdae51714c7975c9f9f007e5397665b5e4c60bb6ee1de39f8c54242c93"))
    (730763, uint256S("49613c85aa274a6fefbd2a4ceb0caa03fb66469b0ad7ccbbddff1cf0efd12ab8"))
    (751062, uint256S("45ae40cdfcf3b469fa7e7c664f92b053dabbd2680655f22983fb029678f13f53"))
    (771361, uint256S("a70ceb0971dadec07fd7451d377443d6bc3843a49954c45a83c2100ead67ee75"))
    (791660, uint256S("abc66a6a472e7055496f226c923bcf308424c369b69dc880f663e12da694c0a5"))
    (811959, uint256S("def3602eb8c838eedcc832e47505556c6afbe1d230f35ef7207b70c9ec654722"))
    (832258, uint256S("fc6b0b3e1fb9229afd7dfddc7b438ce62252d3c881e57e1f975509a70de63a7e"))
    (852557, uint256S("86f49935f6d45d359f6215f2d30e2f214a3a933f72f7fca787a0c1780455e14c"))
    (872856, uint256S("65dca1344862f2c860ca5ba9eecc8aa210c72eb174ccf7e16a369a3b07f61e6a"))
    (893155, uint256S("129fc4df2ec3d45d2cffbdb3bda4881da00196b64468748a5b3f2dc541a48609"))
    (913454, uint256S("72dc1f2ec619a8963025277ab59741c832738f3ac46543fd0a34321f9ca5dae9"))
    (933753, uint256S("7db58f56121297456e007f2b902c4ebdd0df5c4b0260af6f71ff8c3659b6c884"))
    (954052, uint256S("3606a09f45d18715e5ea21a5a92342a26dc72e175cc65576fcf88d159c620feb"))
    (974351, uint256S("b31e5a89c5561d3c233a9a74c6fb7fbe468de9e7956dd79b09fdc2eb87316116"))
    (994650, uint256S("02de883bbbe7c2e5665be15b4c2a31906132e236e8e11bf103a825aac5d67251"))
    (1014949, uint256S("d50fc1f4d17bf90e9a7f8265003c4b1792a7ec09923eb1b268cb525bd59ed9ca"))
    (1035248, uint256S("31e0bdadfd5a2c40c40a1b2e39d4419a951091c2efc7d2918d8e35677611245d"))
    (1055547, uint256S("ef41763c8fad3316eaa18289bf7c4163aa40d0a48aecd5abe28a654cd3d7a110"))
    (1075846, uint256S("72cda8098d7452aeeb3b4f6c28bb010f062b5216fc4ceaf30c7e71d06efae74c"))
    (1096145, uint256S("31a7e93a8843979df9161946e3942a9daa4824e5d4977dfc4086c3dd743f1aa1"))
    (1116444, uint256S("17f6e0403bbf19ecfa98103349f33e4c7a981245f7f7e15198473f6de58d2c0c"))
    (1136743, uint256S("8d5dee24f76453a39d1843367b811c78ca3b131396def13294aa03409afc110e"))
    (1157042, uint256S("9cb6857b804aeac0e7d5ffd792bcb87f58138d0cb2c535ec233eb73ac4a118f5"))
    (1177341, uint256S("fe6ed763619137d65b57c171867772653511e45af723996d25ea5e1b99f34723"))
    (1197640, uint256S("905ccfa2bb93656208f992d6265c7518869d8c35492b05701e29539390cb75b4"))
    (1217939, uint256S("4557e3909bccb41e4ea8b5b62c99e764ce4a3586af7ed5d8342f605592c0680e"))
    (1238238, uint256S("10686efd2c18cdb153b88e7a39e32bf9bff41b55190a1b7d8b3b72d8a11dcf19"))
    (1258537, uint256S("99ff857f59b816a79e8623a24a456f5ff740128e7e379b4d1f80f7a3ea6199ff"))
    (1278836, uint256S("90ae4c5bd1e7c7d20c0f44d0b2324b7e2918702736b9238d957815b244e9819e"))
    (1299135, uint256S("c67e144915ebac184de5337a087c486fae5464879e654ef4f05ad00b64bd9bab"))
    (1319434, uint256S("274fb1e38ff516af9a65a156758990f0885dea33b2fc1480d25c0fedda982940"))
    (1339733, uint256S("8c24ee49adb4e7fcd2136d2d71cbd7cbf8c85625a5fd4e4836d23c5e8158f465"))
    (1360032, uint256S("4c2059de9a178dca3d267707a1dba6d6540a508752b1e0c27b3e70a69ec31126"))
    (1380331, uint256S("492cec3eb8ac4aa1627a810917ecd8840dc9ea128cd30226f83f21fee17d5864"))
    (1400630, uint256S("2ef4ebacb874f57e54232d1a101dba1bdd9b2f071c44695f0d5e00bfba0aa3f0"))
    (1420929, uint256S("a4bbedde2bebeb7fbe8414fdc2bd1f4da1a03835c12bcc58fd47b851bc296ec1"))
    (1441228, uint256S("1b245f26148dda0daa50868b63dfba2494dd78e3b2b7cb95f79c3e9e5133bc39"))
    (1461527, uint256S("7abe0d57eba274c848aeec6b7706dc91d362f05226f4e3b2826742dae81fd4a9"))
    (1481826, uint256S("816822e2320975fcbae906e08163e6c1684ac49fdeabe3b99df54ae401a238d0"))
    (1502125, uint256S("8007684b6fdd505392309b28abcce4bd1b299fda71d64ed813f3cce52307c66b"))
    (1522424, uint256S("308936fa47bb8771aa4e1bfe096575d022e68f7193bd82a8303259364f67922c"))
    (1542723, uint256S("3893117c0db7b73286ea1922aa17385061dcb55bd54c4a519a3aee42ca640242"))
    (1563022, uint256S("b93e5d45be593f585ccf54ea272b39aea9e877226f69f0942b21bbdc05f9d162"))
    (1583321, uint256S("052b1df58cb7656a54b97c4a5e964cc6e4ee16c7568b9d55b38b88eb5c5b74ab"))
    (1603620, uint256S("8f35f144f8cf5ae2d36fda75faeeec06417e6bfba267c8d85bcdb1bfcc3d5199"))
    (1623919, uint256S("f5fc0918e21b54fd3cc0f4464dc59fcc6b69d4fc6ce7216e7e9ca304f8e9dc2f"))
    (1644218, uint256S("07c6408dddbbfded984d97ad7cf7b74118c2827e0d67b72c3bf66cffa30c4ba9"))
    (1664580, uint256S("ed1f3a6f136fc0d1eac3e380def1a859f520e02b93fca8fe80554fe18083ed8c"))
    (1684879, uint256S("89754c3225d114847cc83c45f5404168e7a94fd608c98871559826380b3f4898"))
    (1705178, uint256S("c1b1d9f9829e345122dfd5ddef797958f623e497fd96d33614c1140d5f94418d"))
    (1725477, uint256S("c01ed876ec0a8f6127c40b7dc2134d64ab2ff883ecd15026853b5f8ed222da67"))
    (1745776, uint256S("7bd4a1c054f25b62145f48e2ed2f0cfe5520e465a2f6ab90f2ca69462fc01300"))
    (1766075, uint256S("ae55b221d76be6d46d5f24e543253232256af3a7226a711a415d4a56dcbc5367"))
    (1786374, uint256S("cf04cff8c07d453acf7ed3e299d51326bc57a4f5c3465721b1172d2b77852f56"))
    (1806673, uint256S("d67e14f497bf126051c5cd31e3df7eed19aa68752cd89af4a33fec4eab26ed6c"))
    (1826972, uint256S("f537f9759cbc9d1950fe199e3dfa8b8e534555fe28d2bbfec3222fc657dfab9e"))
    (1847822, uint256S("ab41f330e5f92bc4a1b0b7f0f535805cbf3a200bef7694cfc536cc6ea09864f8"))
    (1868674, uint256S("0c65dded8d061f5428d75583e1cdc3c82f9f0fab7888f5aa64bef93ab81c47b2"))
    (1889517, uint256S("4a16711a2fc559fc8a755e16995fcdf9c9436faef17848a8fd084d21409b2b91"))
    (1910219, uint256S("9ffaa7448098387d264d0ffa21525c7328406683feeaecf9c8647956c014e7ac"))
    (1930899, uint256S("7a8d91ed09f6480897b541f737e8351765a51917a3484d654f3d1b9a69bfe4b0"))
    (1951514, uint256S("5dc7bf2a80ace5dffbd32cc243884b32aa56ea4a1f6b79767147d5c07f056a2d"))
    (1972124, uint256S("01e3471e6b7c88d40e28823454a4b2b0af083b163f4fdebc834b42301b12d8b1"))
    (1993015, uint256S("b804f4600079b46839b645c0c7f5e84b7ed9501015a0ec0fd32dd724e881d549"))
    (2013814, uint256S("4fdbda0190463f0831c44982f6c7ecf979a1a9ef781a081e70fd060be2b559ba"))
    (2024805, uint256S("43775b7ce7ecd9f6f83461c4e61c760f4013b03bfb7e91f065d06097ac46e966"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626350415, // * UNIX timestamp of last checkpoint block
    5626814,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    5760        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1563924366, 694507, 0x1e0fffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x79b352ef6aa3a1994a4c3d711e2d460385b53cce065611049a9a3c55e49b53e1"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 120;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 3 * 60 * 60; // 3h
        consensus.nStakeMinDepth = 120;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 20 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 30;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03061929edbb05141eef4ce4c9fc5c944c0ee67aaebcca5defaced677769bcc871";
        consensus.strSporkPubKeyOld = "04c90538206b7c4921e1e96e93e83dcc39f4351b997fc57934f5beddf916563497b99a315a772b626e072c9a903209c85172cec7052a54739dc392e27cda0d581f";
        consensus.nTime_EnforceNewSporkKey = 1625615999;
        consensus.nTime_RejectOldSporkKey = 1625788799;

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
        consensus.ZC_TimeStart = 1563924366; //07/23/2019 @ 11:26pm (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = 1002;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 2024001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("7aeb48ba5038096a31dba0b0a274236297eaab809ef24fe48d58eec821ebbffa");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                     = uint256S("3c15ae0fbf2b422bae354856c557fdeae8a1cfe8c1dae24dc5a3eb6e89fc801a");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("24975d012582291480d6604d469acd18b09acd87068f9f1a8309338c708dcda9");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("ea1031ff14a7c59c7df9291d347cbf1c72bb1a9b4aafbf3c215314a14aaeaae7");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("cbf48bacc3e1c8d843fe43be3baf7732c7ac4282f57e171980a2b50d18fb141f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("99552707f5e6815ac9c4bdf764817c21cd72dd095f44a1268c373bec8cb1648a");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("a538111ace7e59b635beac76a113d3a99592215f5063fae161a67bc1176e137d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x45;
        nDefaultPort = 18976;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.suvcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4C).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 10;
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
        consensus.nTargetSpacingV2 = 60;
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
        nDefaultPort = 18980;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.suvcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet suvereno addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet suvereno script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet suvereno BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nCoinbaseMaturityV2 = 80;
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
        consensus.nTargetSpacingV2 = 60;
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            
            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         
            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     
            = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight          
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight       
            = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 18984;

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

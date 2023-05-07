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
    const char* pszTimestamp = "Bitcoin On-Chain Data Suggests Miners Expect Halving to Pump BTC Price";
    const CScript genesisOutputScript = CScript() << ParseHex("045cc0738b254d30b688352a0866ce76f5c07d1770bd07460049a327f00c1921705f130ce64d28e83c24c7fc1b0b63958ab9b883131dcdb4dca5655e1e17350a6c") << OP_CHECKSIG;
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
    (0, uint256S("00000e7b446b97413bfec60b4d733b3765dcc2bbbb63fd655e507390e4c4632c"))
    (15193, uint256S("b1658268c008fed8272ee26bbdee6cff952f5ac89eaafed99c168110f2158a77"))
    (30387, uint256S("ba1e3cb9ba0cb9f4c863d1d5658ebcaea6f6867c5806560ab63e256af5d19d64"))
    (45581, uint256S("0902b2bb8176c9f3280fddc5f124966f1373654ca79c4e7662bbb90d379fb401"))
    (60775, uint256S("0f02a6ed03dccfe5f16468784500c67691a26432f4b511ab02efc87f5029597a"))
    (75969, uint256S("ce056d626b592d01335e7ed2c4488136d7709b9e1cdf4590c90bea2a0128e4b8"))
    (91163, uint256S("3f2e6f0cbac64234a126bd001c4d8cd8ae228eb70fc20ae130b0a3b1053d4e5a"))
    (106357, uint256S("e8650013b81124b31fcbd1a1d5b7460f7767c5bc0b6f75004cc8fd7c869d8ade"))
    (121551, uint256S("76e0367e4ededbd2e2bb455292634fe5d240446a66b2788d683fc363dd9fd59f"))
    (136745, uint256S("fc25d883035ac94bec31788cd18db33f3c40707d2b63e0330d8580fab0774074"))
    (151939, uint256S("61a1e0667547cc46a11aa24898938c452a60034f719090aa90413387a531315a"))
    (167133, uint256S("da98c18b8c00a91e2f691471e994af09fc8cc28720484e28e292bf7932615e96"))
    (182327, uint256S("7615c0181c0fa7f4929e57c6c98f56deb06b05398dfabcb1865af3d113ae3c50"))
    (197521, uint256S("e63a357746f53e25ba45809c5e1bab6385bf2022ee516b873e5ae1128d889b5b"))
    (212715, uint256S("3dcdf6a751dc3ca0f82927dd305bc54c1c837422907254f33249b897d2d21542"))
    (227909, uint256S("461bdd79b92a9363f17bdca12523e91cced12d4abc75e31a51bb7a71115b34c0"))
    (243103, uint256S("3dba1d8699bd1b30a8dffb328e97ccae85d63475f4dc0fd0a1e3cf2ae7bec3f8"))
    (258297, uint256S("1f2d3f8392f2a59f16772f601d1a9bdb0d8be13e0af345f633ac14adc48645a4"))
    (273491, uint256S("514ff2fa51c15727068aeb29f8060b74ca094e75b118bb4dd96beadc728f3295"))
    (288685, uint256S("6131ddbb1b4d8902091ecd0cf6fa14d21695d3c0983bae3391a8e2f261a6e893"))
    (303879, uint256S("36671fa99cf884010ec30222acc3649668f2cce3efabf8643a10c6aab36598b1"))
    (319073, uint256S("870440d38702c329aaad43174c481e846e3eaf8975f232f2d82b45e1ad307c0f"))
    (334267, uint256S("d29f5d599283298a1f84c5c1d28d2fc4fd2f41dc7e7e88b595393b7b8c059f89"))
    (349461, uint256S("95c5fdad414caae462c75d9ad8222ce2b33adaa07952fd5605f4b8af940fedd8"))
    (364655, uint256S("c28ea2b3b85af392864d90ca3b343b45d07b8d3ad2292108318c0e914e15fc23"))
    (379849, uint256S("595e515c5530db1132b9e3502d89b55104cd30c60f924ffd43e5148d3e097448"))
    (395043, uint256S("32a77c6c87de8aef8b96645109f6a8712cc614fcfebfa5e7d24c0adf2a8785e0"))
    (410237, uint256S("a2f1771f8a26c18e3478ff501c9c59c89313e103abee098bdf239406fdf700a1"))
    (425431, uint256S("96ce819c8444aeacf2fe82a5758a814bb2e2099efbd2e85e4a810c174171a0c4"))
    (440625, uint256S("bd045da0293fc9727bbcf308fec117d2fda74981522cc52b5808b45bce7e0fd0"))
    (455819, uint256S("4d62f7ba7fdf2b42b27dfd4d7525869dceb3cb2a1d5e815b5a0226bdf55d60f0"))
    (471013, uint256S("572a7abfb65ce3f5a595567f80eeaf8c1a0369eb6e0d3057992b0317b590322e"))
    (486207, uint256S("486f583ff32c56b82d14d1a5baf23ddda9b4c4494fff87440edb6d1e04121789"))
    (501401, uint256S("b12d60cd2c8f39d3370dc393b50be2675df4a82790cbb19757b7b58910e30a4a"))
    (516595, uint256S("11df2d358145d0feac39923cb5afb75e4fa46982be1fadac59c80ac47537ca82"))
    (531789, uint256S("cd9b4a83cd580b8365e016e7fe0fa6a442da5255af4fe85f4c72c911424045a1"))
    (546983, uint256S("93de039eb24dfece822af0d8db987139a47b21e3053c3c84ccacb97aaac7cd9d"))
    (562177, uint256S("9ba579a12308f4a88ab8426c1a168e3a8c068c9415d1f9246795b197a746f2d5"))
    (577371, uint256S("79a1a4532d26b97f7d8d838fa46529018d8ce745e35f9fb8b05785e9007735ae"))
    (592565, uint256S("957c3e1b9568a68b75918ecea3017d57888a4cff0393e071543168200b4dfef3"))
    (607759, uint256S("0d7e1af88206f7ca5940a41fe6dd15032f198ad801183ec34ab97fb6350207d1"))
    (622953, uint256S("841b7e46dacee989c4fb6b6e8bf9cdb58cb9244ceedc71aafda17e43b6ee7fd7"))
    (638147, uint256S("8ae3c94fc54005655bb24ef6b14a1bd641c78185c5a4eebb541850133fbb5e2a"))
    (653341, uint256S("56eb995306c984448c80c8dfd334b2c8af085a6006a037411ece2aea11e82d98"))
    (668535, uint256S("5e28d920b2e16c41aaee4da2e0737d9b04d5090417c6dfb9823fe2bc317c607e"))
    (683729, uint256S("52d4db77767f87f728de7cf99ba818871812cd05c018e6f315953770a778d21f"))
    (698923, uint256S("1829988d06a47943843fe249c6287816f8d40e136e95a70c5d46d09b0d0e38b3"))
    (714117, uint256S("3caa04a41d1f0f07fc354db23b3dd826955d1e69235a2ab8863b48a624b6690d"))
    (729311, uint256S("733af94d28c19591e6b598cf04b14352e47270e0667e1146ecefc630da421270"))
    (744505, uint256S("423c1a51bb5b464cd826e350bf8c7ab9b71d34fe640cff9d67a9b3f2472ad44d"))
    (759699, uint256S("b982e2a050be78504fac51a4124c519fc5f76cf180b47d1938c6107e461d41a5"))
    (774893, uint256S("869ef354f609fdb72ea55dfaf833397508acfa2b60e4f4e6283d359d49b43fbd"))
    (790087, uint256S("4fefeda353dc2db5ff0402b5fe00149f5bed3f41a3a23c65dd30e7fe20076ba1"))
    (805281, uint256S("7f6bd69457b1d61abadb6c9efc9f9189e892a440327fd05ebdca583f39e842e3"))
    (820475, uint256S("63ce3dc2891e95b31abb5ed900038d7925cf9717db523bd7ec3df9c00848cdd4"))
    (835669, uint256S("ba025820e2cb7d557163715a6a0559a2bd8b01defb641a7e69bb8ec9beb9665e"))
    (850863, uint256S("63c1b227d47c33cb854bdd0adb5432ffc23578e775bf9a15511afabd8f5a5e4b"))
    (866057, uint256S("669f453d93cda776c1012276d509947abfdfa64546de4391ae23a0eea5e16beb"))
    (881251, uint256S("0b36836481d37659665f2fda6b3758558c7f96d131de299b427c5bb380a04375"))
    (896445, uint256S("0afcc56e5ae1d2dacd36348ecb468b49ccc7915b873115a2b4d32e5510de8d8c"))
    (911639, uint256S("c8fa564dbf78e24b7004302e4b7b3b461e71a04989f5cefb5dc30855f3b0b86b"))
    (926833, uint256S("fcc414018787dad95f0d4c3b471470e45b0c3fd1160c62578a34413bc92300e0"))
    (942027, uint256S("2356311a609759a89fa21cb42355cce2125ea50b4fc5b1525a739cadb7da1ba2"))
    (957221, uint256S("a84947f606178b1ad9842049a0f88dfed25d9cba577eded727132d5d98ea6166"))
    (972415, uint256S("2ab01c48368f374aa3ba0b2662b1b1333d707f1b8a0090ca889a654be138b398"))
    (987609, uint256S("5a1f0d238813c65d8ea636c48a5659212698cb940011cb3df28296075a36cce7"))
    (1002803, uint256S("3e15d0ac213c974fb89390586c85246355b387ee6e435a934a57c7742f86b2ff"))
    (1017997, uint256S("bfd611c1a1fa81dec464724d676a7a88d4d021baf34cb5c97ce20680c1b61225"))
    (1033191, uint256S("c31c93d885d065991d435163905b5081ae42dd0ce9a39e1a66b9f3e3f5a78075"))
    (1048385, uint256S("786b5b35ec592a2feab9f0cb6b753ab83be2feceb85243fbc395d21dc5b981fe"))
    (1063579, uint256S("e835c8375f2d0e01e7d3cfaa57bfcdfd207a5cf7b8050a8faa915c818836e4c9"))
    (1078773, uint256S("33e5556569c3d4b3d2a298f960e32047eb20822c002e5c3c00ef5a6b52e9ff60"))
    (1093967, uint256S("d3fa42e50b55781610efde6c029570c2cd0911554825104092a654bc36bf3b7e"))
    (1109161, uint256S("76943ab18d2e7af4ce219d05b0f11038582375c4d91416b33f26724724b77690"))
    (1124355, uint256S("ecc6a251ebdc14958298658119ede93789d84bf40e3701cfaebe6c7b0666331d"))
    (1139549, uint256S("eb8c9c0447c748d5eb67a923463dbf239fce34037e0ec64f6ee513ecb37c5f79"))
    (1154743, uint256S("aa8d94eb2688b3d3d3cd56250f03b96d56ebd7eb0638b4150f349c9d6fb367d0"))
    (1169937, uint256S("b0df1dc9ff764438b2c701a145ef81f30f2e8bff1d1c13774f0cd7c492724cc0"))
    (1185131, uint256S("ee0de99aa4a59f332023c3eef2ee00b8c7e16734c1d916a2ac31644c15e1733d"))
    (1200325, uint256S("2fb8b408366d5880672680ee6d5a9e35d85c2e551b0eb0adc8e4a6519a7ba28b"))
    (1215519, uint256S("0a6a1605c3d4da96e8fd06a06ba09db9db14f79e1cadf18e1a8dc240315b99cc"))
    (1230713, uint256S("4edf3fd0565b907bc2e8dd142067987f30e892da2808ea4bee4b5dd94d42c32c"))
    (1245907, uint256S("ce22c0aba69c3d7c33acc471dcf834cf15d7e60728b7285a6f321d611eb62da4"))
    (1261101, uint256S("3fb49241707c9c8d6921aee30efa3fac7d285a31f96f48038091ce4f60ea9a3f"))
    (1276295, uint256S("9121ec21c7b55412272cb4bb0b00c4d749a9eead0cb97a79118758c58d180902"))
    (1291489, uint256S("c0e1e9b66dc1ee9d996c8e110f473f398ffb99c8f6eed07f8794cbed5357cac4"))
    (1306683, uint256S("c78a6b6ede545e14faa3cc35522803e56ca1aec9245147ce5f7e4b9561ca3576"))
    (1321877, uint256S("5f9f03ac64052fe30a790a7f3c900f5720072c92773a08205fe0307693f45979"))
    (1337071, uint256S("f3e8fb1688339f79d2af8f607ed70e69078795e2b0eecac8bc8e49780fe5fdfc"))
    (1352265, uint256S("4fb03174ddec7447b67a7903de7fe1bb1cabc85768c7336c70fbf7913030acef"))
    (1367459, uint256S("cd8f167afb501153b49107b75576c3ac963669238f96b0fe804eb1af41edfa39"))
    (1382653, uint256S("83f3e6d50edab82f3b07191669c18090c2e04e173c631d309127b504e169900f"))
    (1397847, uint256S("db0c07431626f88b734ba113d01e3a4f6bd9a5758669c9806e2157424845927c"))
    (1413041, uint256S("c386767eebcd8642e8f6dfa24d51a3321c4c55767652d04d6edcae84b709339e"))
    (1428235, uint256S("bf3eda3245cc131625d81bab74d80a98c2a303032b04f3c1556910e20a199abc"))
    (1443429, uint256S("f5e5a6805638ddb8ddebcfc9923ae557cad24cc2ff4d0c4f9f362a4445d78207"))
    (1458623, uint256S("dd8278d8895e78778b78a325b394b3265bfdb64cbb909d2220a1f9a5918dab8f"))
    (1473817, uint256S("e35d82c0c3614c996fbc56ecaabd2424ed51efe44e2fdd56296fa75971ec13d0"))
    (1489011, uint256S("6d17185575ab32ce011f373bd5db725cf08b406cf56f594de7db217844039556"))
    (1504205, uint256S("17b4ab661c2abd0604a673d1a07fc6b0c2742b3aee6c032e9df04505465b78d4"))
    (1519399, uint256S("663f1a341246efe5d5b436bab1293a97dbb9c04c07b12aae7e5ea67c9beeac1d"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683483570, // * UNIX timestamp of last checkpoint block
    3124383,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2812        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1590602436, 8798527, 0x1e0ffff0, 4, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e7b446b97413bfec60b4d733b3765dcc2bbbb63fd655e507390e4c4632c"));
        assert(genesis.hashMerkleRoot == uint256S("0xd5815c170eb44b9b7aaf67a76cba9da647ec1ade573c585c665a627a71b5405e"));

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
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03cb8b6b4f2fd42dda4a9fa037fc8e2bbabf70f626bc03b523d45e0dd13534cd8f";
        consensus.strSporkPubKeyOld = "046DDBE578C1DFDFEE9EBC4C89F2709B92D1D5DD0E0D99D87B84AF8E8DEB3AF370DF7EC30569FB1FD72624B4F3EDC5409EEC0D0A1F7D5B845304FCDCA9FCE157C4";
        consensus.nTime_EnforceNewSporkKey = 1633478400; // Wed Oct 06 2021 00:00:00 GMT+0000
        consensus.nTime_RejectOldSporkKey = 1633651200; // Fri Oct 08 2021 00:00:00 GMT+0000

        // burn addresses
        consensus.mBurnAddresses = {
           { "oXXXXXXXXXXXXXXXXXXXXXXXXXXXWc6ERN", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 700001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 700101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1000;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 700201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 700301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 201;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 700401;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1203611a86942fdece0314ba7b360110c7d8f1a604c063a61f15c52a6681de19");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("5544242267804779f8cc5ef586f1c8a288e82b90fcc0ea346813d0a98b9ef397");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("af29c9c7aee6596f45dcec12d4d6fecf11d83338b6188c0b41bfd400c5a67f2a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("2ebda866432d7e5f709cd47c33adc21d24a4bb064704962414de7c06913aaf5f");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("965d52a02ea15fd1e609993710eda72f110b7250bd7f64870767fddb4d9b30ec");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("9cd8671955df99b2127b70b9e663e6ff75bf29db9bb64b182c024b0be8b0be66");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("1203611a86942fdece0314ba7b360110c7d8f1a604c063a61f15c52a6681de19");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("00499a1b5db6df069b9b6f89aba4041de7dbadd32c68ebb28d516a3efdb8f52d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x20;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 32112;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.owocoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115); // o
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 112); // n
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 92);  // e
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // oneworld starting difficulty is 1 / 2^12
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
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  =uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.owocoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet oneworld addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet oneworld script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet oneworld BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet oneworld BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet oneworld BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // oneworld starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
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
        nDefaultPort = 51476;

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

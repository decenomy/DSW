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
    (16726, uint256S("322fa52bb22cc8c30d23f2910f1d70e7ecc948022542835bb7a21ead1782b489"))
    (33453, uint256S("2dc1b467e96d15805ee45acdc2f946db9307544e91b618be7f8543c242e6a5e4"))
    (50180, uint256S("16fba83c6605b0f3ff855d3eabc6a3a24367988f666d142b07993ca6977b7a2d"))
    (66907, uint256S("d2213dca321f35f428711814c94e6810f1146b8513cfbf1e108098f55575d5f9"))
    (83634, uint256S("ba8b56456a6795941d098b763d3fc9b74e001de36f794a94fb8fde58d08f44d9"))
    (100361, uint256S("db9a331f56b08a1aad95237e35dbcb268477eb014eaba91977625860a95d2600"))
    (117088, uint256S("54bb1a4c09660c88284f8ae6f0d09be70790610146839bb82676140a29fe147a"))
    (133815, uint256S("de8023c8aedef2a8c6821128bf715ec6ddb20d4d7da0e9572822cac304907a4f"))
    (150542, uint256S("d1ece7958bcbf56af6a0f0552b5038553169dcc3bbedbd9bb1806112a200ae62"))
    (167269, uint256S("82e0cfa7f37e656a7fbc72f97214bbb09a786bae05de3b90245c894fc720c146"))
    (183996, uint256S("c715e2e8e25fbfb427b66dbd67e46f1ab3f806105134e96d84dcc046c3f34161"))
    (200723, uint256S("3cbdc39302a35404236eb1d55b85bedc55ec057884efa7519a4f006f42b07e53"))
    (217450, uint256S("3edb6a273677e27df2a52de49ee55ad888c742909c0964b84e02a5efba5de0e2"))
    (234177, uint256S("ed92921fba41e5b6bb17f89b0f239f10fb545dfd4e8e0fa7cb48384eff298eea"))
    (250904, uint256S("3b9b637bf5451e3fbeca08b234b095c0155428965a55aa2f0947f7e4594490f4"))
    (267631, uint256S("1bfa53618d6bd6271a7a7ab73a73f3db1013cf4d9be9471df531b4e05276efd1"))
    (284358, uint256S("11306b8a4a294158d41e62193414619e8735ab3f092a242b1d902d87a312bb65"))
    (301085, uint256S("4cb3fd62031e5d6789ec730f17e6d60bdb198f245ab0e14a759e8631e7044543"))
    (317812, uint256S("41252bb66eef0d914c42e7f1cdfaba70fa5f47c366e299d292b0dbcf572f55fe"))
    (334539, uint256S("22025e18810efbbc248a44df471210a9a660333d64f6b919f23f2be7735e66a9"))
    (351266, uint256S("f61eddbf96a1766a7b46f1f5102c353e28b608a2af9cf119ba1b3baf52012206"))
    (367993, uint256S("951830a049156b264def73469f50df174c2f28ae384e68aa73edbc4817f8815f"))
    (384720, uint256S("89ad4d7630d90a6c2f6c69646dddac37ed263c758036d6b21d98e6a9a96f72ea"))
    (401447, uint256S("4abbb9603a86f4ea5cc26acae6aacb1ccae421eea20599b9278cd0433d7f6a06"))
    (418174, uint256S("ba571c53c2317e6222cfca5c4b2040e6ea9d31d23f4805d9c45d1f01717ab20e"))
    (434901, uint256S("0fa195d5fe36c97d91d612132a25427b34280acdf68e846dd895ccbc9784a5b3"))
    (451628, uint256S("458e0c46df233889f2451b3203bad18073561577a60187aefe075b58e4bb21cd"))
    (468355, uint256S("d9d2b0cc747b9866416c1947de3c0126762e1d2d1dd653738b6f7b7c5378cd09"))
    (485082, uint256S("c29abb69b9562660c6235443b49d7fb4e389b767290e9a5ea0763fbcbb1e41d9"))
    (501809, uint256S("8e21e42b6d2397106fdadca493a4b4c81b156d72372cdf59814c961e273e7f24"))
    (518536, uint256S("52434adfa2606a8763a3b1bb842d147e0121bf22efde25bf862630c53512ee5a"))
    (535263, uint256S("a65ee7ab15bcddae62db93c974a8d5d997f432e13df38e470eb35e36c7138614"))
    (551990, uint256S("20defb508bff387e820ca397a37bc865281380bf17dd59fe097eca3abc4a1bf8"))
    (568717, uint256S("161ea9a9012b162daf785b048c3d9d75f0af89a337fbc2fa1f87711d90e5f50e"))
    (585444, uint256S("8e87f6f0bd386ab082265e7c063cf6dfb4ff08053b0f0356e6765969b111e5cc"))
    (602171, uint256S("d6b2fe01d16be9e74f708471d8745a3b0a0d8a8473b57bb2326c4cb591ac8022"))
    (618898, uint256S("f2af0c9878b43ce5e8469bd1b133b04765a7095fc8817e6071bd9b6ac0dcaf69"))
    (635625, uint256S("2f5bfd7db991639b80dcdd7ddaab64e8ab12453659fff0fd5157ea2b363781ef"))
    (652352, uint256S("1de4045471c9a0bc949fa064f27c35728db7969d726e672e1deab3ed4d0f3c4a"))
    (669079, uint256S("49c53db26962a539e389d96c44f6339caf9415d919d09d0311afb43ce0426a06"))
    (685806, uint256S("fc07daf18c9a702d0342fae5772b79cde6a0715b157c7f430f48773b340479e5"))
    (702533, uint256S("de4d85f14d9ff796fe59544240bebe909d47910e91a7b4c75737917b0f0633bf"))
    (719260, uint256S("0263c8bbb9f7edcc1f257c80af0990774e04f861dcdd25e50d7b4c8cba63df29"))
    (735987, uint256S("33d27b05c2fd5186914b24a6822d426fb3ce161546b02f9274f342b4841d193e"))
    (752714, uint256S("776e7e39ec6e69dabca8fa43e41c63dc33a7dc7d7f6b72245b89d2f0c05c54b5"))
    (769441, uint256S("f923644785c88ea35522578bd148c683cf21686863648fbe98d9e3f9e3fb3f60"))
    (786168, uint256S("f8d3c768a5fcfd44ad1235a6a86292d71f71190928e2bed36c14e29f36b929cf"))
    (802895, uint256S("460545a567c16074743bab0de2bc715404edf7cfd8a48e18da8a26d623c5ec3e"))
    (819622, uint256S("8ac77a33d5c9a26d5ebafb9a49da11f3be209664c71dbf96dbc9d0314c53bae1"))
    (836349, uint256S("8d80a9e037d15b965a35309e8c27b0bb08f007c6853bd4a9b960d0d70e954e7f"))
    (853076, uint256S("8d177aa6e7ee155308246d3fb032e2290e8a352c657d4fe966a7c89b991ce7aa"))
    (869803, uint256S("293da24b587b00456e3c3e186e00731b5d5ee573e087ad94d4556d7d61f4640a"))
    (886530, uint256S("914ba277e818dff86b314294eb5ca90053bdf2095f081887c365a755d2ea4d61"))
    (903257, uint256S("5b7055909932b581995e099eb39bde7adf94fc86cd597dde43896d89249711d0"))
    (919984, uint256S("a90b1dd0e4d08ac10e16fb3a833fad1ca582c2b09d8f5a2d018b661a8741a491"))
    (936711, uint256S("1b3e8da16ea0f3c3877595d340f37e252a3ec0d723c83e577fa9d785ef5c94a5"))
    (953438, uint256S("3d9d99c8f47afa9827595188d58cbc1e0b08b2122dc04fa6554326e9bf94716f"))
    (970165, uint256S("06b8a48ea2210af2e7368d0a69a767ac0a6434b6fe12cb6a674e732a342c9083"))
    (986892, uint256S("5b591b03959af0dcedcbb601206ca2264c3a2684211c7c3662e81b04e6633cb5"))
    (1003619, uint256S("81acb851958ce5c4880326990e33e90456a3062ddb5bdcff11c855bd8d4ef8e4"))
    (1020346, uint256S("58731139ec0072effa84a81639b6b875312114dfc657126890031b08b57d6324"))
    (1037073, uint256S("6c425c7cbf31b0c08e7d8de659814f972b68ae5329d157ca63c881d9bfe695f9"))
    (1053800, uint256S("0f430115531bf9f65ef026d63d1a78e02ce6309a9ad661f377b89851f443c0ac"))
    (1070527, uint256S("ac443648c35385d5328861894610d02174915c6121151adacc2db52e8c75fd56"))
    (1087254, uint256S("90c4714f9ebc7b2db23afd02d093506eef858ab5823a8916121571e9d926130b"))
    (1103981, uint256S("5100661b9d594b493b3e6a5e71c56286d5b707905d655d28e4b1c49ca7ccb9be"))
    (1120708, uint256S("e71b4c8f7c84eab747b4f0cc1d8ea3b87331df0259e4fcb057fa5f80da3ccbf4"))
    (1137435, uint256S("245db2cbceea7b682490d0ecd0f0c781c78de9bb1fde8573d74bbb397125b4c8"))
    (1154162, uint256S("4409b928393b8c8d217e1444f2bb879496465ed30d5f5512fd5825e45e537c5a"))
    (1170889, uint256S("47a04f25dff743fe60424b2788b80d3aa9a9b481443428edbe1ca2ce8136f8b8"))
    (1187616, uint256S("068891ebd43428f51efcae70083a3fe9401ca740171c52ff98424344d0cd1d87"))
    (1204343, uint256S("8d7894e7be43b5281300adfb4b334b70e321165cb4eb3c6045e2ab29904eda2a"))
    (1221070, uint256S("86c6477c0e3ca125d54b8fa26594f7f7524c635f4b00c16d97efe8883f1e8574"))
    (1237797, uint256S("1cacfaf4411a64c80204e8ee962c8529c613c628ebb3c506d4b081c25452d7ca"))
    (1254524, uint256S("a464b62aad5c43e4b3f39490a9492ba192be20afaecc51d0d7f727b1c89a2c53"))
    (1271251, uint256S("8c8ad2bce4cbcb5b818d73621773af20a06276a74db79cd2da854a8308536ac3"))
    (1287978, uint256S("73abb7d9304edbbfc89b5bff714448decb34c5aea92b7d4d567f8ebcf59610ae"))
    (1304705, uint256S("ec15b0f108ae86b09eebecc267e306baacc49c67e4baa46306e3fc0dfd134f77"))
    (1321432, uint256S("4d701276c9481e912a9b703cf1507c6549552611014e8b5bdfbc7319fdde53bc"))
    (1338159, uint256S("4c4bb5af55a3d05a630c56e098158571f9886a8c6f0df527f169dc021c08e0bb"))
    (1354886, uint256S("b925acfd0d96a23401323f6a1e3cb9cb69deee0cc09e2b16c8e17c684fb9def5"))
    (1371613, uint256S("ec62d78a847b6fd22131e1712dedf759ebdb75de1ee0b215f960deb3d952964f"))
    (1388340, uint256S("8946ddd509b64bb4d9cb8d2f21ccf2e10b854dcda4ef94b67310d49cab1c2209"))
    (1405067, uint256S("28c473f8f357b184de02d4104f026635b154788b55df63b42578729ad76159de"))
    (1421794, uint256S("0bbabd28ac2c4b01be95e712ace23e44e2ad733cea4bb617ddc49633c34393a7"))
    (1438521, uint256S("2c0de724ce05d14f0834b4bc714855f047226d643ed4b6f1d9ccb9bad6b1e6bf"))
    (1455248, uint256S("3fdcaa7532b471746ba36fa213d20a8786bd3f5a7b8d60fce699aa576fa312e8"))
    (1471975, uint256S("17db49b8b13a0031b8bef5a90c88fafa419bf28c2ffabd7431ba3fca4d9f2f48"))
    (1488702, uint256S("022b5ab90af24c5833a81b0e84ed27f8fec2d82058b8f5f5a7492934413103aa"))
    (1505429, uint256S("3badde6cfd96b34ed26137562fc81f3d2d83f5f23b6511f81de7450226673c66"))
    (1522156, uint256S("d73d5fa52be2c5d39c10ef66e23a4b5f449d0ad6f630a3603104a3435ce5be6f"))
    (1538883, uint256S("efa2f346aa41ceaf7e052b1cbfb1c094d4a2e9516caa6e693acbd56326c28722"))
    (1555610, uint256S("3f93d4a0d034722c73f40a19885224862f30d5b5b75f1ae5d4a11ab52018c101"))
    (1572337, uint256S("78809753a654fab117649b0344d57b4ca1ae81a6b03ee749ff2e02824416660f"))
    (1589064, uint256S("8c3273688bcf39b8b7e800b6f40075ea4dcf7427aa29b2ed9f43c14b332d4708"))
    (1605791, uint256S("6872681d6effe6b43b2162b0c0a2add8b9c29a4011ae23d831f8bb450d8c9e72"))
    (1622518, uint256S("b99101795310d50fbcf1ee02d78b6e5c3ac015f886717f6a201e401d032543bc"))
    (1639245, uint256S("d9adf13639ffd402a1049fdf8d4d66855e24fe43ecc7a79f40ed362400eb0d4b"))
    (1655972, uint256S("a7e233889753cb631e95c9659f0e25307b4ad05800705c2bee46fcc90ee2ce56"))
    (1672699, uint256S("ba48f4dacc003a40b8e9ef5c515b5ac024f6634c8de45e3e6a75fef981b1244a"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692904005, // * UNIX timestamp of last checkpoint block
    3440765,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2834        // * estimated number of transactions per day after checkpoint
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

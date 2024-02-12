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
    (22525, uint256S("b059790290c83541d4ec20521fe41d7ac701d277f0047a08209cd1ec4920c5be"))
    (45051, uint256S("db1fe1cfe210a2c816a80f29ff811f8cbdd7573b6b7386e9553b398e705e8fdd"))
    (67577, uint256S("ab8cf5e91e6345bf51f1f6d5a19a56408141409785d1949df665b24127844019"))
    (90103, uint256S("3f3edeb1f9127a3c1e9c787062a9e2f4f68202b563bc84e1845ec2d039aa53fd"))
    (112629, uint256S("670500a5c60854f752e67a164fb38dd7499730ca764aee16085021fd87199d39"))
    (135155, uint256S("1ad9823949687f0dc3445e46537bdf36bdd1d9c5dcb25ef32eedd15b7ae6fbed"))
    (157681, uint256S("cc1852afda6eaa5aa08135996ed91438ca685390dd8a8f60d616368038a600c9"))
    (180207, uint256S("51f1a99124bb5cd95529a828131b507f89598d6641625baa2ba30bd8339c2958"))
    (202733, uint256S("65797d7b637ce52aa7a53ce73a52cac033e9ad7e7d6516dfc583b96e3ecae4ba"))
    (225259, uint256S("b00f9c4f697636e6f56a3e1fc4099f93a63d262560fb6990c87757fce94776e5"))
    (247785, uint256S("d01c7d64da4d168bd67b976c9d93413a49bd99b90b3c3b94eec454264a8f5be7"))
    (270311, uint256S("b66f9da2bf889e9edb559f5fa50f5802040fa486d3af4ef02838ebb5bcc4062b"))
    (292837, uint256S("8e313133150968668b9190696cfc6b6e944961954cdab7560ae2cae1035403ad"))
    (315363, uint256S("345be68c03d7ea9f66329d6387d44d45c3ffa73b9c48e11e188ae7e7e54641e1"))
    (337889, uint256S("073801b22dc1925515dbafbf42d3fa8db3208dad2348488020c54de89f2634f1"))
    (360415, uint256S("7174c16fb5f0eee61e8b571efabe84557807c3295dbc8c83bf6b735bc764fd7e"))
    (382941, uint256S("14e74d2adbeeef6759e6fe63d5e6dd2df404dfd3df002a50efda98f8507abd50"))
    (405467, uint256S("3a2747bf4a839d183749a166cbab75694666788187921567ef2174312db4d32a"))
    (427993, uint256S("301a42ac3666cdcfe1250c6656eaa782201bdebd9f41189801582cf36785bf97"))
    (450519, uint256S("27aadb778e64b1c5287b167cc639a6693c0fe9d7ae62dda992ad4f0179e5c33a"))
    (473045, uint256S("dcc4e02aaa7c2dfb383f0b3a1d306689e7bf17fff6b154274778b4e15fbd79cf"))
    (495571, uint256S("9f17deeda5d96ed15623926d11c1d7b3d2c431da9ae2eb837b132ae057e9d04e"))
    (518097, uint256S("a6e9768011c67d835f87aedb90f50611c101a9945f0efd755c683e03ce15b040"))
    (540623, uint256S("ad00f1988236283746f6831daacfcca0248e3708a304b13187fd3c5dbf8f5f59"))
    (563149, uint256S("2ded23db0aa96f74d866b1c8a5f06407632844e4708de4febabbbe18f358df75"))
    (585675, uint256S("13d305d8fec2ae88bb854f06434bd0772836238b29d834793c9f83c1e97df437"))
    (608201, uint256S("6593874e526442b812fc646f42b8e225bcf687109594ee5dee2e4826ef5d537b"))
    (630727, uint256S("057832bf2baad3ebbb0cf903c1bd8a14c7705f3cf428e8e39694f6927132ebbc"))
    (653253, uint256S("85af002eb4429e4a21863aba90f7f31c653b08892f06f838e293094144fb6cb5"))
    (675779, uint256S("131372c607a142654c6979b12a84e90e323e7b6c4f33b552d5f3d7d02af71b39"))
    (698305, uint256S("6cd4842862b828aa55fff1c6e3768922eda78fa0944418275d56461ead3bcc19"))
    (720831, uint256S("c9c89eb630381cc3550f294503fdd8b44df0c39b28780753ed8c124cd7e01845"))
    (743357, uint256S("ecef88024b3c2a812478760706b119fba6a42fb65e2b8bdca5e9d52c95188a3c"))
    (765883, uint256S("c5c391f2cf05fd971b18e0d2bf90cf60335687f294ec969deca1519bd15391e0"))
    (788409, uint256S("7e5d72ff876c1b694caf6582963d833dc649c607a79aa49592d68dd8b4780ab7"))
    (810935, uint256S("c5361659dc15e97221cdf2f7f09df56b70f061f124517823a3907509fbdad76a"))
    (833461, uint256S("89a452a719dd49dc898be65c31d81f6cfc26e2e19eaf52f2f7a9bb4070cd3860"))
    (855987, uint256S("8f8768c80ca1f0b8a7f82af47185dfdf55e794db33274dd7a494af03447c0f12"))
    (878513, uint256S("c7009cdbd62c9ff26e077024d34891f987a589d52697ebe7bba3279d9f15c2a1"))
    (901039, uint256S("fed5dce92a93767f51a09bdcc9e733c3cda4643514028e22204691a616a12b9d"))
    (923565, uint256S("77ed47e1a9d995e96df358b9ef37e9dd0be3e9622b3d2a50056dfbaad14fc15a"))
    (946091, uint256S("b8338277fc0d14ed10841194e4c7fa475ccc2d3a7494b584a98e413902e33a3c"))
    (968617, uint256S("b208f58a59d87c57a56803a3c564a688ab955ceaaa8f2884f031a7a2a2dbb4da"))
    (991143, uint256S("a9897e3d1556f3440f729a247169a280c70f2bfa014cfc7562fce75388c1e5ed"))
    (1013669, uint256S("1d2516d6a174b7f2fc24d990750c867cfa09a48aadf36371eeb190d62e59d643"))
    (1036195, uint256S("0c97aab13ccfc0b06dfba971c7209a726449d6e31ad1251848dbb785224c531f"))
    (1058721, uint256S("456dec0a00c90a4a475d049f9d8e2a56e40dd9d00c54ce728205b7c8847f9243"))
    (1081247, uint256S("9a38c11b3c0f81eb8df1a1a6acfdb5d40ebeb476b35ec501bf24701d0602663e"))
    (1103773, uint256S("f18e3477469606f661a16da17aec656e4c9a3727346cf8d998dec8017394663d"))
    (1126299, uint256S("86b86f336b08ac5fa4787c38a60aed663efa8c67ed2ab3b8eb5ac40fa381ae19"))
    (1148825, uint256S("b11629bdf440fe90a68b02100cd88c1cd2e9e677b497cf20c36dd974f2225f2e"))
    (1171351, uint256S("db5b76e2d398e497d90d53f3085154f0e4955fa8cbf01b7c7b59f78a44d43014"))
    (1193877, uint256S("3fad33b6a5840f1cec68d881f11d687198dade7892b6953badf5c4927fba76bd"))
    (1216403, uint256S("259cb0eabc21780802b257c1ef079c242955068a88eb4d40c755b3d4bfe3733c"))
    (1238929, uint256S("f227d167048213d9773ff3a34861ee325357aa976b744a78194a63afba737a9e"))
    (1261455, uint256S("0b86bde1764c69eee4efb2db2f83e8f93c3d4b4f0402ab6207c998927eb82939"))
    (1283981, uint256S("c5187754bc852e2007ef543960e79cd2bb2754cff7124a6eded818b2eabd19af"))
    (1306507, uint256S("02c116432645ba7a392558c82d3b0d645dbc0097f2d4ab56d82471bb70eb60f2"))
    (1329033, uint256S("99148f7ea36669177b9b6dde9d1276944528c2f5133b9eeb8cdb9f40a680fd1c"))
    (1351559, uint256S("fc12ff32d43f86ea2e3ad739252b21755af3aee890bd4e0297722dce4557817e"))
    (1374085, uint256S("48f62fa12b99c742f68d9ca2c8cf3d76ac9c870625fddf387538bc0489501b44"))
    (1396611, uint256S("265c796dd90aa5a259f212002c59c8345a84442ab74ed51e41427455cc83a04e"))
    (1419137, uint256S("6cb90d82ffa2971a93fe7d9855297223156499be9bb6bd6985c8f6e09377b901"))
    (1441663, uint256S("60bed29b32e96519fc5f664a85d55879d5b22fb0b11dd4468dcbc527425db1e6"))
    (1464189, uint256S("fb3e5fbc0925fa56183a51489c1086f8cbeae3c046acc355175b826a3009f175"))
    (1486715, uint256S("a8906775a2840e0d41639b02fe930888ec5175aca2f71ffc79f8a48e1cac7ec8"))
    (1509241, uint256S("162efda06806dfb4e064109f1b1dc0478e06bec9ceab2f7c80ad5f71683e9db4"))
    (1531767, uint256S("7ccdd8f6c93d82ebe1b035f9363af0e96cef534f7498c7eca9737e6897e52dd9"))
    (1554293, uint256S("bf1844cc6fe037e0a6f6031ee6ef7058a00c076ad8799ceb68adc139bd00c821"))
    (1576819, uint256S("dc92dbae8e5c1813c59a2319327f0af5317e70145a70881613492fcd67578b99"))
    (1599345, uint256S("b9940e992a4b36f939159d00c4e4eaa01707695ec13298a9939f5deec6c1dbb9"))
    (1621871, uint256S("b21353c6765a7ac55fe6cabdfa294d1c4f471620803dede6553fa2ad0377cb1e"))
    (1644397, uint256S("993aa99aff982a0b59b04c4626f020dc54464134def580f8735cb835544874e3"))
    (1666923, uint256S("f01dafd7c9516a28a1917e1d9dc178800412d74c686d17f58759cf58caba8523"))
    (1689449, uint256S("5c0f6599a6bf787d6cee60c113b024dc60b0ddda3c88a95b4358aba68257085d"))
    (1711975, uint256S("b6e35887c0cab6a01f4b5239d111b5270285b56963e9858c1f0a7c618366a9fa"))
    (1734501, uint256S("833e1ec2efbd0cceddbbc0a298e9b3cb6d3698c9c3e25b0b7a06a07d5df53cf9"))
    (1757027, uint256S("8a77f808cdeb439e7b313436fb627a5881b2eb4f1615342f44512569e4b6c6e7"))
    (1779553, uint256S("54bd91e5ebe70e75a7892ea8213f84957d1b60eeafd8c1e8650c9b0e92587b1f"))
    (1802079, uint256S("b80ab156c841a5a89f9614072ab78db2604ce5d3138e1811d682c8165249b5f3"))
    (1824605, uint256S("34257d7a30ce5a07a5d63dccfa95afff7c42dc53a64a54c7c377b6fd14d840df"))
    (1847131, uint256S("a9414b795e95e6541022fc21d53a8da46928d396deea9f11b029dc3db03fd1eb"))
    (1869657, uint256S("4d99e8159150af28ea739c0614e5162f46f9f10fb72a1aaeefeb2fb3ed158267"))
    (1892183, uint256S("b78e10e090f0071e1077cbf8487c8dd3f2bbd7882d3e578053bd02751818dc9d"))
    (1914709, uint256S("0dcd53afb571d8e9119431ac51ec66032f28d80ca12ed8215b9830f8f416ebe1"))
    (1937235, uint256S("5594fb07044ebad608101ca1bba2c11375644b8c96d2eb39410c6382565ba20b"))
    (1959761, uint256S("ec629169b3a3e20b3ffccb7f429806151def0457aa20d056ee917c706d478fec"))
    (1982287, uint256S("096559f714e09f420acc1e71e7df5f17f14e4e5f943f0db901737a696ea2188c"))
    (2004813, uint256S("66b545a724f90e8184e86a4597c39eeafa30e1ab91808f4c035fc3cc0f916fcd"))
    (2027339, uint256S("2bbf6d275abce51995d70bc7f5e6eac9a27fabb5dfe2ee8b0a562c587bdc73a8"))
    (2049865, uint256S("40383db12a7f57319706f5fc06c6e4dfeafbb6c337405225217b63965b6eb5f1"))
    (2072391, uint256S("69621b01627db0963853acbd479f8479e969d11e9a2cafbd1e9c9e329268a384"))
    (2094917, uint256S("dfe04febe29e478a0ab3ba62af7497d74ee3015a0946de7871db51200f6a4523"))
    (2117443, uint256S("e7601bd8143bf2d952706fdf4656cd22323249729ca904edf098d966c6c8ee57"))
    (2139969, uint256S("7e0f4243e9c13eaa374ca2cd1e8661cc3c909295de7c946b240fd3de3ccf0452"))
    (2162495, uint256S("41416ba5aedc2fe31eead2d791abb6955e7297b5c081aa0f0e424981ce38efde"))
    (2185021, uint256S("b21c992d01de4c4a926ebb55cccab1fdaf63645f2821bb57b76793354dba7ad5"))
    (2207547, uint256S("5785f3d51d7e2399f42417c4b3147ded754ef1c76cd241acfa02064f65496468"))
    (2230073, uint256S("7cbdfeceb6061e135c6c38a7a90665243da6f8d333212758413dea3a1cbc9824"))
    (2252604, uint256S("4d2ca1e4619d2e9d0e89b564c1b72efe84522475297bbee1e89713ea1cf811be"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707729780, // * UNIX timestamp of last checkpoint block
    5177399,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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
        consensus.strSporkPubKey = "02aeefc7f24b3919ff05a7d2661aefba6c37ca77c263a20e8516dea630fa74e9bb";
        consensus.strSporkPubKeyOld = "043B44A0D5F6BFA822208E19096A6F71A144EA1034A5ABB99E458DF1463CF98E72FEA9E5C5038EF7716765D248DAA709A23746606AF41CAC59DC071E89624C9FA2";
        consensus.nTime_EnforceNewSporkKey = 1626393600;
        consensus.nTime_RejectOldSporkKey = 1626480000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "EbURNXXXXXXXXXXXXXXXXXXXXXXXYdqMFj", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 252;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 930001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1;
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

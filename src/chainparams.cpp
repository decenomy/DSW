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
        (19980, uint256S("69f8ff379b7bfcc5aef9aceeae4a3e40da31a2bfa00b372a4078032fded10c2b"))
        (39961, uint256S("a3c0694c3cb8e2e9e3c9de10860aebc46c82aa3fa464ac7cbe87a6e5e7aaa8fc"))
        (59942, uint256S("a4f5553bc257e110207a0d485d87ca587de7b329edb29333c9e3d4ad5df5c237"))
        (79923, uint256S("014ffb8040756b82003288a0e1698e0baee87c55afbcf051ac2efbe4c8218675"))
        (99904, uint256S("64f07a8378886e543ae79e904bb03f2d793a38947f56f773bc3edb5675c3c778"))
        (119885, uint256S("20f9400b609112264e8676674997fa3cf9aa48bd1856459626da7cb46114dce8"))
        (139866, uint256S("b1d122477a5c38ca37de8442407cfde495421a23dbc34c7c820ec69c3b5e7c8f"))
        (159847, uint256S("6bdec6ce1bf854389e81cb6932708bca74abc9c285d4977ec6c2147d11396ff9"))
        (179828, uint256S("fb6d064965c9aa5c982441e58d5b0a8480525dca659eb4983c5c93c813f80833"))
        (199809, uint256S("82e1c9835452d67d1f8bb6f7fe3a044b4b2e9e47d3339da132071cd90810adf6"))
        (219790, uint256S("1dcb7925c6aca5ba80a3e7aeb14a540a73cc4353dbd47d96a9ff234cbe89437d"))
        (239771, uint256S("0999cabb7f12197376d17cf0ac1cf91896d6e57ee33b83048adcbe4e5f1e8803"))
        (259752, uint256S("b97201b812e018b8ed2bf12a70d6d1eb520df93246e664f1ea401d02adf7d6a4"))
        (279733, uint256S("498697a49803060dd04a259de274be4caf5fbb615d76027964212383da410019"))
        (299714, uint256S("16c49a3ab0f5dda73da22f3086654d2396709ad618e4e88bc66448f7f1c28580"))
        (319695, uint256S("3761ef89b0b024fa5cb16cbee70b25d800fc8addb875cf3e4cf15f17a70b3edf"))
        (339676, uint256S("ba80f7bff434a997ff63ba77b9927275ba00414492fd8a7fbc5fbfad265baebd"))
        (359657, uint256S("7194b2aa21f5f1c4697ff7f66206078387b31e8bd965b15233dd4d504f26e78c"))
        (379638, uint256S("ec754a5d0354cf111149f53cb198c2dab8d016e2b95637e179ac72892b4cb6fc"))
        (399619, uint256S("97badf26913838dbe45ab76e680823e5980be5a07c57a4205836ecf78f69ae11"))
        (419600, uint256S("08d2913cffd30e5a9664dd7dbd9af54698cd24685368786de607980eb86b5347"))
        (439581, uint256S("bfef52f4a2eed5c01bbacb6a96cda25c20ca69bf3023949a2aefa9c697b53df6"))
        (459562, uint256S("9dc7f5141030450ff236bffd81a98e96161bcbe0cf2ba20027af42f78cfa2537"))
        (479543, uint256S("ae3fade9ef5b7b22f70e9aad204f94820b558f4a2fe2ea78da20cfdfc2b5e279"))
        (499524, uint256S("2a9ad4e6eedd56ef014536c6ddea55e9962b36cab6955cffc501fbcc10bdebfa"))
        (519505, uint256S("4129bd422349f94d94267e6d72728342259dd6738949568c4faf40267bc5d44b"))
        (539486, uint256S("cb623531bf85b6b9bf51ce7c8339a5e5ec281bcd45d6f5787011d10ba38fbf6e"))
        (559467, uint256S("679fd6fd6cf6324134441c68314edbec04aefe448977b430d315910534bac889"))
        (579448, uint256S("37681c0b4dc4d6e7d70b8b8edb9d317f6dc6201da019570524412a5b84cbb56b"))
        (599429, uint256S("9e312e981e4bdf9b2b8678f25ae827701962821c1e42584b11c25de9ca2af14f"))
        (619410, uint256S("70428c0ab32561b4bca004d12364d7d647dc5f7e739f3eef00b857133b3817e0"))
        (639391, uint256S("ecdb19fd162490bd5b4eedcbda1dd804b2c359bb3af6effe42aa320f779cb11a"))
        (659372, uint256S("70ecd031f8f0a49cbb6ba00c422a8d233c35d35e0304ae24f9cb2d1889299e90"))
        (679353, uint256S("eeb19ca60ab01f0d3609329ad46cb4f9be73fd7b04ad1f3f1daac37301cc62fb"))
        (699334, uint256S("c2bde34e7f28d233f5f7e25f3b02f5d8896db5bf7b265dfa628e0b36320ccaf6"))
        (719315, uint256S("823279757c8cb36590785c633eec563fa9989f1fc6b3841ff12bd1a1cccc2a87"))
        (739296, uint256S("8c42a2423254d7dbf704d5273e158b5f88ff09518bf2bd1e662dde79fc00eca4"))
        (759277, uint256S("a640145fce9a9939e331b815b0e8ee5208387be6d78a1b56adb65d9c26c28c84"))
        (779258, uint256S("15447c6e5debb8efdc57ba6967aa4744c60f12086b0b4ac49b0335d199dff018"))
        (799239, uint256S("39ab2192479422775b9583fc1f09d27a6db2691afbbba2896b67f0364e0e2b78"))
        (819220, uint256S("e6b090d4d005c087a4361667006c1379ba067cd8abf3d4aa5e0bf70d3cec7b6b"))
        (839201, uint256S("f8f8d70d801656fec57326b689072fdde48300f9df810e821bb19398ddc15dcb"))
        (859182, uint256S("a6d1d082dd3c5d894824e6f0e81886d923ebd47944b66f077db68e0fc6954a67"))
        (879163, uint256S("640c0dcdafc9790852a15c6378573ee7b48af76d92f62a0aa11d62738f884816"))
        (899144, uint256S("467ffbb1e464d21036d135d74497296f53453502cd34cd261ddbfd330b7ee06d"))
        (919125, uint256S("83fe73d95bc0fb9313bc270eec85460714ca4da901379fb525dd1770306e6405"))
        (939106, uint256S("f8d0dcddaa79a232be3aa2eb13daaa1d2b9c3b43f4cf705b9e29cc1385000265"))
        (959087, uint256S("eedcab88463bf13b74c9313ba41e9e9f57914cefe1bb4d12b1f266310dbb01d5"))
        (979068, uint256S("d20fc1d38da05e84b21f96d4a05ce856c2f26b9f188fd672810785bd1f9c2d8a"))
        (999049, uint256S("b1306c4c58cfabcf800ccf6de752997b897f194644e40d8d72b8cabeb5e10b93"))
        (1019030, uint256S("afdf70d26cbd25f18bd445d00b3176db02f880e2ad05d64221a65e568cb088ef"))
        (1039011, uint256S("d9b0c7375923a8ce6a66b023c6c8f59ce3cb245687dbf0bf37dd57eb3af4d38c"))
        (1058992, uint256S("f2b0dd086fed4aed46a11397de665dade6a14232f2384b5206a725f24ba18848"))
        (1078973, uint256S("6c4cf3c3fd21e1c86c02aa291de643278f086709dbf56e38cfac5e293e4ac2e2"))
        (1098954, uint256S("e323f162d3167059a03d4f5670e1032e010088f902c54a2da602655947747c4e"))
        (1118935, uint256S("7b1c42d621cad9dcf19b6410b540fdaeb75006f9c8f5d8b3cacff6534118665b"))
        (1138916, uint256S("468ae755f60d38388a6f4b3fbe529c9b028932567a72c0f22027b5c394624870"))
        (1158897, uint256S("aa55d25df38feb998743031aa6b384f8c806ae9dfc3c792cb2714e7d9c92d42f"))
        (1178878, uint256S("81d30796f79ce47227dc700df5b58d2caa386d9ddf548a3c1aa1d31015e253f2"))
        (1198859, uint256S("d1e3a7b6ff5b60292f2b54607723917c99ae47a1aa9a710be01561a50cd60104"))
        (1218840, uint256S("9ab5ccf45930a548f9ed91c8b8e7189173eb9f9787fe833b4ee1e0b3d595cbea"))
        (1238821, uint256S("f100228cab84bf566f0ff8ff5815af0d41d4bc819b756a5a4bc545c9c90e04a2"))
        (1258802, uint256S("d3157e51b2ad7e0ad386ca167ad2ac40fec5b2f500879c9df335ed4812cc721e"))
        (1278783, uint256S("ff9f357a8024fb5c337ee9d9903cea386fccccb1409208aa1e5b516683c49eff"))
        (1298764, uint256S("aaf743f6df77b081b53122c5207506cb2e8bd4262f5e9e500b9cba1759c168f7"))
        (1318745, uint256S("b032e0d4f424e71ef6acd26f1cd85d9de6f37837e72f8d233f6a300c7d1db074"))
        (1338726, uint256S("897de8a644b94bfadbe5c7db040adac8ae3935c0d9b4d4fcf9f7c4cafc3998ac"))
        (1358707, uint256S("9ac8ab1e67ea684be5ac12b5e9bae67fb8c4960680e3a7de07e23ce849656085"))
        (1378688, uint256S("8dc1ccce2b434493703fbd2d042ce2e899b89b9848cca7d3438ff2e1d447027a"))
        (1398669, uint256S("8ec3f9962f244c0553943af4dd82de9ebcd367fc9b6e4baf15363a90ee7e6b70"))
        (1418650, uint256S("7dd525dbcb07d2b4e46ac038f63c0ff00240793fcbdab3c6c1dd60708f44aa54"))
        (1438631, uint256S("4170d169cd98517434a5038bd77e076d93c7f37374e46c69413a7fc632e3d258"))
        (1458612, uint256S("7aa0a7fbbb86ce4f1b89bc1ea159b2fcdaa3e37a0a22e94d9dfc73257a308361"))
        (1478593, uint256S("398919389ac931b86a8a64fe0efcba9e930bf48b5d999e0e80715ad7ed6656f4"))
        (1498574, uint256S("e9f1e28ba48a0913079d0861a9834e42e65b3764e668a4f4d583107a43b72e62"))
        (1518555, uint256S("04caead8cd932ec2e05249c78ded52cbeb1135daa571f0ebfaaffc74900c85cf"))
        (1538536, uint256S("c53b6879a2caa66cffc5e20c4e2f2fc3d9525baa2ed08b57dbfe769b484a1575"))
        (1558517, uint256S("8d03232356bab2a2264a999b4b1b345ab51081a4c08edfc6df19d3a7a35ae7c8"))
        (1578498, uint256S("ebd6dae047eae770da831073316915a3fcf00ca78858146f442efc0db729b3b2"))
        (1598479, uint256S("3cf7faa717b4f8ca6169490922206b3f7e101f81fd3b2ee8dc7efde60b247d84"))
        (1618460, uint256S("a8ea44b0cd590260d1896397f6572e4b7b359950c49890009d734b785918a93a"))
        (1638441, uint256S("e67d903cb31df683ce7d24a7fa29f5061c29fc1b8bc8dfcf6177a8bec5560db4"))
        (1658422, uint256S("50bec14605c257183f45bc3cd3f00f449b0a06a2329ba07e0da9124079d76b66"))
        (1678403, uint256S("9f611a10909f5eec2d17c902f5f18ea31687e44db79fa09656567be32279faf5"))
        (1698384, uint256S("8c86e6443c0fe320bcaa32f3e8d8439d22ef9db8d53b4b84421fb79148b6cb9a"))
        (1718365, uint256S("ddddd28b29170823abe1a8e36637de16883ff478b444ed9ce0b5bcc1cb106df9"))
        (1738346, uint256S("9aa7daa60561eecd558c9a13a58f62a1a958be5cb95230b66ae904428eba7e1f"))
        (1758327, uint256S("287468d502875b660dfb8dd2e4ecdc8f9b161a15667182efa780c4fc36c6fef2"))
        (1778308, uint256S("d82080b74181403a10ece14cae027ab099c23fd4c084e3ac98a1511596ff6f78"))
        (1798289, uint256S("dd1b09ed1d6447720e90a357e0df7e608e12c4962fe8eddafa53c0a0da15d2c3"))
        (1818270, uint256S("00941409adb56a5fe7286b99c1d886e6d95666d7d0665de9802e0f38ff8526d4"))
        (1838251, uint256S("bb346b8ce817721ec3c1cfa81af6f4f54f5f30da9777429bea4030a9908b8d9f"))
        (1858232, uint256S("249104d6ad2277860fbcfef269799ef099231807ecfa97648ab46a566be13b69"))
        (1878213, uint256S("15d0b9d867bfb9c0b75061ce495baecaf6f187f9b7017b6d9b9e817061c58930"))
        (1898194, uint256S("ba6ba3fb279f9453f10191703b6c67736739576acdee2b08f7382eefefea6484"))
        (1918175, uint256S("0bf5e4c4d389ff3468e2d6771aa89075a36b78292b99427fbe8898dadcf14503"))
        (1938156, uint256S("8874cca7988743d6e18200400cf953d4cd3187fb01056b81e64cb945fbf4ee9b"))
        (1958137, uint256S("bd76a23bb58a4bef3f439ab14353d6fe71419da44a5e6dec4ef0606f4a57c3aa"))
        (1978118, uint256S("bcb08ee35d424eaede2ac06bda826d39ef536020207b3fb7129fd957d5a06178"))
        (1998099, uint256S("a9e6d5953b2231deb5d1ed17ff83280521dc91bd03504c1de921f45230ae8842"))
        (1998127, uint256S("f372f0e9f3c57349e5a384b49bb6fc899d293197ab8b5e428e6b1cdaa501825a"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1625247838, // * UNIX timestamp of last checkpoint block
    5563254,    // * total number of transactions between genesis and last checkpoint
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = 1002;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight                  = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight                  = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight              = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_SUVERENO].nActivationHeight              = 2012001;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_SUVERENO].hashActivationBlock            = uint256S("0x0");

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
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;
        consensus.vUpgrades[Consensus::UPGRADE_SUVERENO].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_SUVERENO].hashActivationBlock            = uint256S("0x0");

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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = 400;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight                  = 251;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5_DUMMY].nActivationHeight              = 300;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1000;
        consensus.vUpgrades[Consensus::UPGRADE_SUVERENO].nActivationHeight              = 300;

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

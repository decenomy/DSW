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
    (15548, uint256S("1466eb0ff2de3fb825fec3a5666cb80b050d2dc1712b82dfc087cae77a45d99b"))
    (31097, uint256S("b34ee4488bdf503af26fcd82063133b14ab4eef04122c907dd8609de314a71af"))
    (46646, uint256S("ed1c1630475a83bcdfe80342369201ec3f383dc50d460498f278c8bef50b1bb6"))
    (62195, uint256S("eb8d5bd7e756cdcfaf7f8ce9d61433cbebf67f5fc1aebb7bb8c55f4274857c39"))
    (77744, uint256S("fd4936f1955bec28f5cb21391b12004d0b3f0992260a3bfb2f93a09fd812ad95"))
    (93293, uint256S("e896fe93f5b2042e4fbb91f8f1e989e93f2ec8f44b611c62ae672291d3ac184c"))
    (108842, uint256S("85201b1d37abf81a60c83c9352a7e9d7a9fcd8fa01aea2fa50472b6478ea5c57"))
    (124391, uint256S("d133c513929d7b1ad0aeed9f743e847e07275e2330eaf5d86fd96ef3933e1246"))
    (139940, uint256S("7d29a9daab96ed2c8191787580948761af0c94ac6fe22cbb28ebc133405e705e"))
    (155489, uint256S("9fc324ab86298d03234d68849e1a6ad314f59f313667f2675a4e44f4e6d3c5ba"))
    (171038, uint256S("903b24192616f1917627f47ec2be35fd4658124af9afcb7336ebf83b083837f7"))
    (186587, uint256S("14cf919f6df809207b64eacf9a0cc6cccd4cbc277b7073a5ceec0a973cf9bcd9"))
    (202136, uint256S("af8113147b0f1b4151d16d819a0ed2e8a8d094d8fb8d79a8128afa91268b92e3"))
    (217685, uint256S("8e1c0dcf40bf08d8161b8a8fa30f9309c5cc33c91502db1382a3b845233c37a7"))
    (233234, uint256S("4dda78dbd23607e26be435b1ffd02161e6426be5dff1e39e10c077d08c47a440"))
    (248783, uint256S("73091d01faacedf2702513300a73c652baa8b2eb61a49f4d74df121efe634efd"))
    (264332, uint256S("d05d9318e95814fc844b6cce1961bde7ac15ff9658727fe5f5614705a60dd372"))
    (279881, uint256S("04b9490ca7528091a6210a6bceabac6eb0df0a10b1e58eaf5669db0672aa17b6"))
    (295430, uint256S("c87dd08be9a72383bb4c1354abe3238d06d8960df5028f5dfec4abd316fddd52"))
    (310979, uint256S("98feefdb27d27897a99b4d366f9a10b83b1a6dc7837ac083bc20156bd78042e0"))
    (326528, uint256S("a85c84cef8caca4ca2b9f985faaea077a52ebfbb15962cd2a6b35ca4960eaf82"))
    (342077, uint256S("5c14e55913b33e003815c3482977ca4747b001594a0b3789871cad5f3a4e6116"))
    (357626, uint256S("e40eaab300f99b2442cc5b3f10d5fc207503cb02247acee439b33d376604687f"))
    (373175, uint256S("4d033187d2e88fa8d795218f63bfe96265281a9ce308a529cf2385cad40173d5"))
    (388724, uint256S("95778d7f9c67ba5823f6d07cd78766998da4ed0403bbd2c598b327bf560b9e9c"))
    (404273, uint256S("9b3ed831b631929c765ec1f6eb6acefa0e73b3c9a5f8d3cd221ce26dbc9be5b1"))
    (419822, uint256S("1818facf5f6b295071687511180b5c55dd8de5589da3328bcaf2f66b2aa3ac15"))
    (435371, uint256S("43d26e959a218a95dac9e406eb49e7580f251f39c3c597851032bd98e27a7dd3"))
    (450920, uint256S("322fad32fe2344cc7cfa633d6fc81bd97b37920efa112fb6233d76838adcff8c"))
    (466469, uint256S("14dd96103e6d52e8a15e782af305f8ac03307aa6f1431cfa80d4d7edde4ae857"))
    (482018, uint256S("adb5f691019ec1249b79562d61992f8b27fb69e02871250e0324a4558a8da5c3"))
    (497567, uint256S("b64da334a5d672a2e3602bf242bd687b79bf71157c891336fee17ed6b94d712a"))
    (513116, uint256S("1d4a51349e2c800ff6ac9dec152f449bbf32b48202933d263e85579735e6c795"))
    (528665, uint256S("ba5734fbb8cd9b95c9f7decd57b69aae0b061fa0f98628336b1afbfba12aab9c"))
    (544214, uint256S("6f424e90153e39445f1f447c77c04da566562d01c2f9baffa482081868c8ad1c"))
    (559763, uint256S("581323165f91c4d532a4c7769f9429974ac64377df881a3e13cd075d13bea796"))
    (575312, uint256S("bfa357c294c080b3dda8f3fd292c37a6ffca43531fba2e75ff669aa593e06edd"))
    (590861, uint256S("849fa218485c3be95bd51c6954064f9786fd3b317f9d81a8b6d1201a570f88f8"))
    (606410, uint256S("118b95315844ac05b7bb3cb352c0c7c1dc4f7eadb5061c68afde1ae6c19255fa"))
    (621959, uint256S("d2950ea61e82190c74a1c7f506591deec1621dc3bca93a714418114fc9104bdc"))
    (637508, uint256S("c16eff059802bcd9f787ada3154d030b6290ebd2ec7163879a54b3dcf6004931"))
    (653057, uint256S("a8f26d060ee816ee28b28b92421898213b83ec38a107bdd4d9f0f19fcacae024"))
    (668606, uint256S("b575c022f21166abe9e2d2599cbfb56481ab2f813acceb021d962651f998b579"))
    (684155, uint256S("d6a0e09ee6d8e40bbfea2cdea596e4e5842d555e850c4700cb9a9b1c08568062"))
    (699704, uint256S("c885f4fbe5bffd85c03afb24d37b184dd94cb49223e07c03787d4ac2761d6654"))
    (715253, uint256S("4835b7d23d28d6dac0e5d7bdb52f83bc8c84c540b1ac351a0a6fdde303637ffa"))
    (730802, uint256S("f48bbf128ec3d8ff2418712a1832daa390d65d63879c1530f2052b64b0620876"))
    (746351, uint256S("3f8ce508695c6399ae1e3a11b0c8d803d155760afbaf0138044fa6e91e3fa113"))
    (761900, uint256S("4e80e6f79262e963d307a1437c1f4414324ef98f378dc556a32830ae34bd6b8b"))
    (777449, uint256S("4228fdaf2f931d633d326cb27667dc485a1e774292b2d151cead797a76c34093"))
    (792998, uint256S("f3db41afe0b0bd642c6bc6cbeedd2ad5d60766465d09f390a6d9648af2b134db"))
    (808547, uint256S("21a54153ffead1f6bf5dd5d60f2c9e0f3e79267448acd3892eb8f2d4b74472cc"))
    (824096, uint256S("d3790ca8ca3c09ff86c5996681e4be89f89a7e804bcdfc39c93c95210074dcf0"))
    (839645, uint256S("31d94b60fd36ab156d81e797982818e0c31b3b189db4a64a5a1500649c5233ac"))
    (855194, uint256S("d95baea35698f5d04deff782f23e90227a9fc3591c3e26ec42e2b6949478e225"))
    (870743, uint256S("ad4dda2e82692bcbddcff1dfc39bd154070542805d59c0b645aead499cf714b4"))
    (886292, uint256S("8435711df702fea25b4f911e417dcb3a2f90be3d317fa4fd502b8c7ff02d96cf"))
    (901841, uint256S("30196f15817589fcc87575cd22fd17d3a7fef4afde08002bcbf5bc0af057406f"))
    (917390, uint256S("8c0f1c36eff98b2e7317f5faffd8fbf5c867bc509be2c3126ad324dc103666aa"))
    (932939, uint256S("2327f97024f19c21dfe290c3cc37826516cfc1ba051e58dc6c4ae9c80ff73a63"))
    (948488, uint256S("7e622b44db0930a3b8d7b2cccf741876a007eee6c5aa24a7aea2c1c1764ece74"))
    (964037, uint256S("c27fd5e6cfc8b9209ad336c1d406e328753b151da611eb42eb688697bdfe50b6"))
    (979586, uint256S("6f070955ffe2666a043a6e69557b7fcb2203262e58a71f7843264aff81920774"))
    (995135, uint256S("e5a43de27d94ed0c3d1ff31242a52ff7ad59e66c30f0261785b8e6eea05a094d"))
    (1010684, uint256S("71571ccf0b57f3e10db044ea6a9a1cf207cf354fcda12dbf7a9465d0160a641b"))
    (1026233, uint256S("fae9554a03b284dec0d1debf78f957c18556e9d62088e9916e1bf319f9aad746"))
    (1041782, uint256S("2bb60da0524150dca3535e5e10c2fe6d580e169cfcce464756571ff733676b0e"))
    (1057331, uint256S("e99ae6092ee940cad5df6a9fbf6aaa333ca0b6b30899cb0a2dfcfaac111c0910"))
    (1072880, uint256S("2db2d1f5fd148d6c586586cd9eedc1dac1dedb4f84b71fa7bea428133bde14b8"))
    (1088429, uint256S("11bf36524701c3e8f679af20ab61d68d6e54dbf5f645beb1f96278df7a6df44a"))
    (1103978, uint256S("fc84a43a10bfc5efd664d4a19859fd107653ff8e259d8bee2a4c8c5d32442866"))
    (1119527, uint256S("9b86ad6c77241c082a471b52e93c3413826d7cf89a68e3949f43c4c9c07c93d7"))
    (1135076, uint256S("95578a2d2ec6d18f2719d54ea368589a63c9c8b8959171229d66a234d5c3951d"))
    (1150625, uint256S("4513a938d35fdac33d9ce6079bcafaf5afa464f76ceea4bc6e6707847765b1ed"))
    (1166174, uint256S("91fb1b3c658f8feb25f8e55c79f9e81a93a2fd136061dead78c4d2171e322134"))
    (1181723, uint256S("1669e5842b50f70d2c0a51621441fb0b8cba4f29bb03ac380433ca5fb76dc67a"))
    (1197272, uint256S("982267e2ef8bc529484edb4d6212cb46829e39d5225cc04490615a89cb171790"))
    (1212821, uint256S("e2392c99f0408196c3648a989035b45da1027f59ff4a5f8ec192a93f1a35afc6"))
    (1228370, uint256S("8bb96a9898766b48c2f71d8e000d26137cbf975ae2bf0372f1bed8640b0fabd8"))
    (1243919, uint256S("462357359ced86ca0174fc1d1b9abeb8e00e1df93f2fe54bb659517bedd3045b"))
    (1259468, uint256S("8a26d3f50e834772def8a6cff93b5b9f92635fcbb0b2421d3ed7784552296d14"))
    (1275017, uint256S("dff3ebb841f18081bf9ebad3fbbf4f1f65824005807538c2530d1787a41dee36"))
    (1290566, uint256S("b159a4e1c8cf8a9ca1cc3e76e083ef41a524f6bf8069e29a713a6572cee4fbdb"))
    (1306115, uint256S("0824883fb655ec8742cf2eeb79be828be35caba58d6518ebfc7259a696c65669"))
    (1321664, uint256S("c43f7b3c6be13499c640c8e0cdbb34fcad1275d8f3ea40d0e04fc867a7d7d3c6"))
    (1337213, uint256S("de924d3050dcade63f0ecc528cf332ad92bdcb3719862e8a7f220d7bd0f71ed4"))
    (1352762, uint256S("b3848179442fa8b900bd4b646fd3e8a2f685066de15e9be55b2ac7aa2d3cd622"))
    (1368311, uint256S("ae43f2e0c4103cced8d11f9ef8e9c2b43a33aa22a6fe0d117268825bf3b5270b"))
    (1383860, uint256S("fc349f61c5d92fe748a3300c1f3ccacb4b29179dc529c4b81765161c71fa6bdc"))
    (1399409, uint256S("bb2c1cb811719f47fbbf9009eea433bf7448234e98f0f8b5bde3b49884088b8f"))
    (1414958, uint256S("1f77d44823af2c658c7e4393fe7cf883c6722f3a538c7f8e9f17d2808e94ea92"))
    (1430507, uint256S("c724e5604e9572c43a5e6205c8ec32e323d4df480db781b46124ca832e5b3d5b"))
    (1446056, uint256S("16036775eb98911c7d9fc2d51a708b7eab5eb091b63954cbbc45d85d0ff9dd00"))
    (1461605, uint256S("ba525a578e40d0aea69dc13b598305ceb0f9b0f8702e799497432e96c5ab3255"))
    (1477154, uint256S("456f0b397cac244ead68a434aa6a50213f61268e0d86adca530cd09d7fdea33d"))
    (1492703, uint256S("32c8e641de5c56466cb94a88fd48ec669dfd86d953f887c7f2ba3a5d6f6d7772"))
    (1508252, uint256S("81c1c909bd2536feb7a525a3282fb641fc88f3601a20e6052681ed6287d4189f"))
    (1523801, uint256S("e881c5904758ffbfc2dfea2a13eb28343d250e06868f8ed83a62028ebad5e13e"))
    (1539350, uint256S("1dcb3e1c12d719093bd4ffd2f3920fe30dd7b5134c04cffe5294835ebeff9b2c"))
    (1554912, uint256S("f5c54a5d12cdec7e5feb88cff3c16653ec458baa21439de1b181585e714e9f49"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707905415, // * UNIX timestamp of last checkpoint block
    3451101,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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

        consensus.nMintHeight = 550001;
        consensus.nMintValue = 34000000 * COIN;
        consensus.sMintAddress = "7BicbhE37YhQwmCMmG6qeQkK4USPzV29Dy";

        consensus.nMintHeight2 = 947500;
        consensus.nMintValue2 = 23000000 * COIN;
        consensus.sMintAddress2 = "7FTJn1XZXi7ods8S3fELd4T4YMXVn3remk";

        // spork keys
        consensus.strSporkPubKey = "0371d4e47e0ab43865206e9df7c065d6c68471b154bab3815d99f8380d46c7015f";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("b99924befe2810ac0a613e3c8b43c3d423b870ca3710cd81ab5f8f95ee316d40");

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

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.777coin.win"));
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
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 43);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x41).convert_to_container<std::vector<unsigned char> >();

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

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
    (12131, uint256S("80d8383d1da6dea93aa348aedbc600b8951f122332512d93da4d28417c7d47a8"))
    (24263, uint256S("25e397ac3a1f3f366685272b91cd3efeb5eb0aa7198a34b86461dea8071b2573"))
    (36395, uint256S("c35caff6897a2ddbd52f88d07b598d752d063324a0dfee1173ef4204934c5409"))
    (48527, uint256S("11b00b204f1b3296c0ac3c3b8c624bfd82b5cfbf9433845ed3a12bd53001258b"))
    (60659, uint256S("00d46325cf6c39b0faa4cbbe248c0ed7b8f2701a0078759ba6190ab72315bd2f"))
    (72791, uint256S("4a872fbf219c5f8423730a6e7fe9e7ef096ca29fa0a08d4d8be474ebd6295659"))
    (84923, uint256S("158176de0495709331c1bd49312d5afda6be7c45bc2357586990b8a9c9fa2fbc"))
    (97055, uint256S("585f9eedde475be76989eff4c9ea63a996ea8df39ecebbb273d48bf7b1b4b60c"))
    (109187, uint256S("2811fffc6eb5e425d84efff41f6341af1a7c3ed2b0571f0e2aaf94975daaa408"))
    (121319, uint256S("abba7e091310cdc4620e1631c3fc62418571a43bf45232966233439654695a2f"))
    (133451, uint256S("e7ba2bec74fe421147714e576ef85d7ec331006eb7642b8a87eb9ab863e38a87"))
    (145583, uint256S("04f8cfacb8fffbceec9e967b95ab00d5ffd984e8e223f320e41c64745ca8d43a"))
    (157715, uint256S("b7875f5c09e48a618cabc3e7dc63c26933efc5e41fd5a0ea6d4eebf03db69233"))
    (169847, uint256S("a17a178d02490a630efd6ca84c8061768a4651b71835babb357e174816756392"))
    (181979, uint256S("66eb0aed4304f729100e5de613f0b3ec855878b4341a722449f5efabde8625b0"))
    (194111, uint256S("421b73c665ac5a9aa0d73b917b7911111c76be3203321cfaf4f994b3ba1fec40"))
    (206243, uint256S("eeb2a7f410e4c315c48e1c8672ff6ae2c3af9b959fee9c655743f60f37f39bef"))
    (218375, uint256S("1297ded7ad05994d8686bed9ad14ecf8183e8f5d20be10e7517c334ed606e8f2"))
    (230507, uint256S("798f70bdf9cda875f195f701f78e3240ae33b5df911b25aba051a14036037b65"))
    (242639, uint256S("1dfd26b8159e6026691bcecbc444a0b6df4c53fa5ac13fdfab34698fd33caed2"))
    (254771, uint256S("b3b5c54a2d27d69dfabfa267e01facdc33b4da839ae5924817bfb76c8f09c58e"))
    (266903, uint256S("aa6f686aae5fac1f4a585a274b10f7d4f66bec934bc6270642f60e70488e996f"))
    (279035, uint256S("afac5d9667b8c744dd9b77041eaa7b25e852b487da7939b6c75f7423ba00b3ae"))
    (291167, uint256S("176400cedf87d8931d12f9189428cf20752ff510b2bd807c889c540ccf1850d9"))
    (303299, uint256S("1d878142572fbf0ae5e316eb2fe033a32ed482e833c4f57b3df7d6b74daae96d"))
    (315431, uint256S("2f352f73e501cb15c3347c7465990404570c2caf2638b1fb322d2347bf84745c"))
    (327563, uint256S("1684a16f287d2bce7b7a138afdff15308c1499350f7115fec1e236c8b32b3c4c"))
    (339695, uint256S("1e5e97baebf67fbe3156556c52e3d5ad4d4ce3b32f8169f36d799088d438ce1b"))
    (351827, uint256S("f8bb6ca87095e01582dcba7c49705a83f0e04d0b1d3d995b3d3c19f36a7ea19e"))
    (363959, uint256S("f0676132d3471ed6bd9fb7a6a65bc21b0d84595b3be556a4aae6847b35b31376"))
    (376091, uint256S("f716e23426f7f6520b6b213582d15e428b5e702f4d3deff2ff7d1fc04c87e81f"))
    (388223, uint256S("13e8906aeb75aa8ac0241d20125a88237cd967cc63e846c609732caf863a7d0a"))
    (400355, uint256S("bca50c12032d204cc8d39bdaaf2803b19049d7fa75e6b4850204489d06ed08ad"))
    (412487, uint256S("15b6f7db628780966f7426ba4daba757808e9fcf1b5efd63820aed961b4c09aa"))
    (424619, uint256S("524bd40f0e383f12146e1131563478b7d4e503e1832376c605230fe024c1200a"))
    (436751, uint256S("03718ec2350505434f2d7ef77aec986e125bc52de56f82281be9a7b029385c02"))
    (448917, uint256S("18f7be510ef213f4b4d8502fc292bb0b8c5d3c0d44d582c1185b22351174123c"))
    (461365, uint256S("186e4223509e9d76ca95c0c60eaa011abb429c78252502ccd8fca0a518524e8e"))
    (473737, uint256S("1d98f72331594ad84f9895c7729c03af728988171948c94d3ec4f71b5b357b4a"))
    (486047, uint256S("ce886db58593ec0062c62e90eab23f4713eb069e39e646ec996f18d249ca9b5f"))
    (498381, uint256S("deee1c4d73e1fa5d04a0bae2caf4b38798be16042666becfa40fa3745a5703ee"))
    (510790, uint256S("7210f558b6fa1a4b1047d9d9d15def4ca98ad42b56fb83d907742eb7ef3d639e"))
    (523207, uint256S("9647afcbd8826ceca64d721cea98bf7eb92d935e5ae2d6aa13fde7703c55cb6d"))
    (535575, uint256S("0103d7acfe358f0e576353d901c2fdbcd3b3e4f9318009e8dd1aea602b2291c4"))
    (547906, uint256S("b040212b849ecb0e1579bbfa8896277dd2646d637ed93a888c36c89d53739fe7"))
    (560513, uint256S("f062a87ca1e44189e763c5995dce88bd382db384164b28ce3b3cdc3a884c9296"))
    (573068, uint256S("b56adf97ef81314df9055b9eff0eab653c742c591061efd9ddb80dad0d6c4b56"))
    (585617, uint256S("9d32c2b6fa5e05c1eb4de79bfd70fa3ff1fbf29eacf5a12e5be37025fbdcab02"))
    (598169, uint256S("a4cee576943e8b227e6b631e902a2ccae607b38945a0be7713bb511950c679b3"))
    (610636, uint256S("b1edabe46159374d60cc2a0d66af6b34f24c3f58543991f99ca7bd9f7ee4475e"))
    (623134, uint256S("479bdb58e500071cef7bcc43999da89db815b8845335778444151fe54a718beb"))
    (635631, uint256S("eb2d4c6bb5bd98b0722ee4f4bd714b9eca7068dbc11900bafadb112f15dc246b"))
    (648158, uint256S("a1ce993cb6f83c5900caf902d325411deb8bbffe135b1810a363649d17fa5baa"))
    (660698, uint256S("f050c847d97ddcf03bdd9f0c516d77f6b9e6d6fb6d67d6d5d0e712f1c373ae48"))
    (673232, uint256S("5417c839e3426dae47b905d014f074c2380cb1abde06a6cfb4a1401d973df8d3"))
    (685737, uint256S("667d570e32fac78dfc5bdfc617e3373c44dfb95c1aaa6cedcf90df88e948f23a"))
    (698192, uint256S("dbb716b8bf87a66c2111c64a442787d3f95627555cbbc2d028aca0bfa1e5b7f5"))
    (710682, uint256S("7f4a52c133f284678a3c5aeacc40f7259797b32854aa5d22418c9df6bd0751ad"))
    (723154, uint256S("4c099ae9b8b3ff99fe3a7db25501341ec7bd1c8d9c1c4a99167abc5bcbeed4b8"))
    (735601, uint256S("bbb68ac75f094d5843935c660b24ccb9f6000b4be9bc1746017154b124a7673a"))
    (748019, uint256S("04901a50d592eec68504cd9ed7078a9d418a89b6463a454a2ff1932759569cc2"))
    (760368, uint256S("9f135611f027fba768cf18894ce15f6b9e4b9d9c94fcd399ec05708d72ccc4e1"))
    (772856, uint256S("f812b2d736b92d15b15ecab106f0d0a43add702b0971e5bb6f4531e5d6615db7"))
    (785470, uint256S("be2b6d1e424e0282a2f0d98737b82505a0b7b167db9b973342ca05103231d72d"))
    (798073, uint256S("142376feb32b6b9f69900451f2e39235e28407265d550554b1ce4f33d24dd810"))
    (810731, uint256S("7172e3ea279cb9cd4f5651adc0cbd419fb9923832b98c61e49257ab58c4a01aa"))
    (823257, uint256S("16ce09144b133b51c77c14faed618de7edd58f3ad225f61f538c144731842a87"))
    (835755, uint256S("0ee3a779107cf304df99272ac27e76a770edfc5538bf7b925780030091120bcc"))
    (848304, uint256S("06850740fcfa48624720c50a0eb2bcf6b6043f62079bfe73d3c492762be2dbee"))
    (860862, uint256S("efaa4d3bfeeb1d6335dd992b1d54089de42f39ac26a16ff28fb047594db401dd"))
    (873397, uint256S("c0dc9ff48fd8773539068544461be8adff155173c1823be39f939f00117332b9"))
    (885923, uint256S("8f0952ff5a5faee71132a752de62d098741789d4de69cc658b256ccb04b69b9e"))
    (898441, uint256S("7963258b3d5f15eb9f28a97b173da5e04f73e4f5b5282fa115faca48e7e545b0"))
    (910873, uint256S("dea445b4c61227ec980f06c4cb927c43258de5cdc726aa9735004c59e3775121"))
    (923450, uint256S("cd4397d56ee36aefb3e40ab4f42896c528a6dd4cb1c5cb062b9c98d34c79aa4d"))
    (935958, uint256S("b60f9a620bbf9e42ace574835dc34a086a8762e4697a504fd4b5f3b2fbe60739"))
    (948517, uint256S("b1beb4ddac12fa281e350bed56ec83c1ae2da46b266b7792e3a7e0f2a0580727"))
    (960785, uint256S("518673a364efc47a2f0e83ea5807f588ba506fa55386d08a8e2d560e80eda2ce"))
    (972917, uint256S("1c90f20bb235ddfe7a43cc714769596d39ceb0b164dfe42a0871a264f4a57245"))
    (985049, uint256S("099635def473e54750f3fef5c1e1b045cdd74703a6043c33fafe9b80eebe94c6"))
    (997181, uint256S("413127423e57a338c4645f09e8780b3198c5e033d456cd4f6a6e55934f972e6f"))
    (1009313, uint256S("96441b247f62c0577c6168bb34c52c47afad094d6598a9578e16b4106ed2c0e2"))
    (1021445, uint256S("9d5438dacf10a012630c11a2bb9c1fd0b66212ea992bf3327453326d2c27db0f"))
    (1033577, uint256S("ee78b339a03a97208c157a3a288ebccf340e0d8b005dfc4cc9a3795e0be32b3e"))
    (1045709, uint256S("6eb7b4fa9d4f7e286ce82b83545ad8e17ab1c681746352821d37686da01359af"))
    (1057841, uint256S("13c5113d9ba025187c71f7652a31cbe6f327fe7ec2fb3f58fc96b41dbf58d0f2"))
    (1069973, uint256S("584478bb1a0e410c9ae5227aeec42371070990c1c71f4f97fa258983fd9bb40a"))
    (1082105, uint256S("698b351faa56fb332b86f39fb58e249ac453b72684d4b19f2fb48f4479d54ee4"))
    (1094237, uint256S("178b260ebba7042ccf567f8a18b03d908895b5df7465a0a91acfec9d31001723"))
    (1106369, uint256S("a0f2d155a997886a435b5eac7520eb0706f79bae9ea118747272529c3694cf3f"))
    (1118501, uint256S("b27ccf5270b71fb11ee95db70aa05114cdace2108e06fe3cf5188d8ec098057d"))
    (1130633, uint256S("d29a8879273f2fb13fbf645b6dfda3d49bea529b1624e54acdfe494a1799e83d"))
    (1142765, uint256S("339043c9f9389c9f9cedbdbefd738068dbd104d423afa8723f868da44e419dc5"))
    (1154897, uint256S("79b80417c4913034971e0b67049d86d743d5d3908743023e08489cf79c307bc0"))
    (1167029, uint256S("4f1f4ff65021d8b6bf0e404d9992d49924ab8ff23eca5db57908b403a7118dee"))
    (1179161, uint256S("9866dfd67aafb09c01ac583495204638a43bddb71a2f9aba04d6c225e6664e18"))
    (1191293, uint256S("ed7c703f6494a3868a61fc91a8fb6ebcb0f698f211f2d97f52b6dcd807faecf1"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685573490, // * UNIX timestamp of last checkpoint block
    2700588,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
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

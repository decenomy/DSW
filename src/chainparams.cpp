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
    (9267, uint256S("7d456cb8d9855f99b1d2f893846f8b9d1e5c5c99407ce2a8d06b2e87f6d38700"))
    (18535, uint256S("0d9c2526adebb35648b104b50995e0ced984b05c6fa01b77dbac187cbf003007"))
    (27803, uint256S("3d58eb16f7dc591e72a9f1b0ff1994487f9c08f367f2db8296346c4d51157029"))
    (37071, uint256S("f9cf58359c836d736f0e55f01a8934b0144a75a8ee77adcc8d8e21b521bfafa4"))
    (46339, uint256S("5823678658e65950c5bdd306d8513c9579b133b3a3bb4f63e3685625d2c770a1"))
    (55607, uint256S("2f6b5fe1667f7e0abf8a1b5fcebab9bb66ae31507cf0b7605dede00652b81ea9"))
    (64875, uint256S("67dfdd5c8f39cfe9c8cf538f455f6dde685fbac6c176e118bc66b2d26acdcb80"))
    (74143, uint256S("487f115778c22f2fb985a53203710a851c09798ccabe8d68bb7a72db0a1eafa1"))
    (83411, uint256S("e541404e3dd038efc722316e2abbc860b39508d47d33be879d4e7921050c61ff"))
    (92679, uint256S("77a11b7b05ec01ca3b699c4aa0559b8be2d999df38b6839a8889d5a06a454774"))
    (101947, uint256S("627ed5806654032d4673b6d6e79d50add18e0f30595df560153a1264567c1a65"))
    (111215, uint256S("e288d18a350a2611de78a2092d6c991a9697135e37ec88fa46141928b6baa086"))
    (120483, uint256S("6e3e5d8be978bd8aa01e0b91c38d6b9ea885bab60001b3aedd9161c724e1976b"))
    (129751, uint256S("b6d99a3bb6edd7b7486ab6d8c808c625d3c6dd2f5dd89b4a3f48102e60fea7f7"))
    (139019, uint256S("0e74a90d375639bd4edc792b313cc935a6d84e2a08fae56cad37446523fd924a"))
    (148287, uint256S("00cc94e1b4d255c5633b0298531a12db035a648836ef21a247d4f620c70144b9"))
    (157555, uint256S("464c0fda297d77a126a7e6b55c547d9c7091b5aa836ad826541492b39e13dc77"))
    (166823, uint256S("016096577f47b5bbb0ec9250fe71af0fd89da2eb5296a1f4f6dcb7f3d20943bd"))
    (176091, uint256S("7afb514b1c198ba27f45a3c77942ab410c063494060e62e4a02fd51f9dc0318b"))
    (185359, uint256S("98c1013dd5b4dd27282ab656ea1a0d171444ff29662a3cc3bdc7af2864a1f3f9"))
    (194627, uint256S("55dd2a268f4af3b1deaf199ee2b7641ba97ae9be87530f4af795f28cfea10fae"))
    (203895, uint256S("add41d851255cf4a7ff24405a824d6a9d0210319928edfd13c51633e17920fd9"))
    (213163, uint256S("9aa84114651d7bca694f4ee5e68f0d2b63d3ca567d1b05074bf4a035eeb755ac"))
    (222431, uint256S("c9e376ca77d46e93ce497a872d4f9f6d9a0d05522ed6dde3a17b8c6c73fa4b57"))
    (231699, uint256S("74a1f383468080ed99c058eb79406d4b1abbdb8ad8789cc29caac3fa9c6e1a30"))
    (240967, uint256S("380d7448a4389c5cd96312778a925ce534b4d2e31bf06ce36401ce95f1547f7b"))
    (250235, uint256S("922a31c2c9bb6b1a9af21593812e8dc46179b681f66dd33ab4e7546c63421276"))
    (259503, uint256S("c2ba15212014055abd9dac851469d05847f1ff3a70bff38db6b4b8a1f1027926"))
    (268771, uint256S("c2ddad19412b4003a5bcb1139540671bd90cd3d726dbc45a2d3d460504869e3a"))
    (278039, uint256S("40d946c5fbd2a791af62d69c39d90a9917a85dfaaa174209874db96c164ac783"))
    (287307, uint256S("9e7dc03ee9b36a6387e6122caf17ca5e02bf487950d040c1a19f6468d5dc0dd1"))
    (296575, uint256S("655d8f6bb9dc0efc8b5ba30c1fed58fac3475a66618faa662e971e6b062fac94"))
    (305843, uint256S("dcd83854f8670ad07b95a5e7219e9e19ec4756cda7d7687371874d5b3591f3fd"))
    (315111, uint256S("ae9fbe5e6f35055b8c5366fa7c5e09d39f6537c9517c68e1fbea1a55c394b52c"))
    (324379, uint256S("1a7b42a7ec5e9c8b7f782123fe6a412bd165d2e6ec4f3b5e7ab062ce08d95314"))
    (333647, uint256S("9073a5b1979ed62eda9dde0581dad29be74e72f22ab357f17110132ceae64b4e"))
    (342915, uint256S("3ecf62d4c70323a9380ab56f8362ca7979d29f30a2727df87d904f89e56f2e09"))
    (352183, uint256S("03c22a37f0ff1295ad53c254b6ba75328de7a4eebb12d8b2a89e01447598b3dd"))
    (361451, uint256S("3f364b4dfd870d5e389859c6a6b0c76999996907164cdd2ada6c61336b3b363c"))
    (370719, uint256S("34cd1cb6d07aa52cb5b0f0fd9b5cff44e18b7aeac41e57643949db508a4ed55d"))
    (379987, uint256S("47efdb71a8d2d5738f84b2f24e83a75b6878cfdc8fc82d2611581f9d4af80113"))
    (389255, uint256S("f1aaef49e97c09f7e0924b86bcb304fe17f21008f2fc5110294495c3049f8d96"))
    (398523, uint256S("8d13e64202cfb81fb4eac5530ce39a6b6d39d7967abfb03c1abc5d813f669f5d"))
    (407791, uint256S("d7b281685264b06591b658d3df147486c21a194f97081723732fb54f72ff1ce3"))
    (417059, uint256S("7b3b9262a07bbc9e40eaf9366d8a184249b2c5c8e685fed94dd24488fd79f5ca"))
    (426327, uint256S("cec48ceb2411fc768ce074ac9f766c428c8d1d7eb7582389b57049cfe15b3ba6"))
    (435595, uint256S("b4b1e0c4c8fcf7fa46da0312e2adbb6f7c5440dcced7746d3fa6bcbf10c24a35"))
    (444863, uint256S("985ab92742e1f28c232d23c3836211558692fc6d0c2540114e58f7facbd243d2"))
    (454131, uint256S("1acff0dfa5a6990730d44f8573fe86a150772b9239ec0b04e3d97241960efdd9"))
    (463399, uint256S("cccb8e0f36cd71285f73579abf7a78b73706cb4b2c8db5838b7fc68488a2f48b"))
    (472667, uint256S("0dfa6dc92bb0a5d78180e9e255d5badb4c7bedc205b59ddf9c150d670ac7bb78"))
    (481935, uint256S("22f915532af87228d4f80f8b3ac268a6b711e194efa9e950378a031e96e892f8"))
    (491203, uint256S("d3ec3b79e2fa59ba3ce6509499cf4228a00f4513cc3652f87cf9f0a9f07f5289"))
    (500471, uint256S("49dbd46a1b56881af5768c4782a0cc7cf0fee77cf6a2ae67770f48c37921a9b4"))
    (509739, uint256S("a5a8672aa11a33fe001030a0ff2faa477ef470bfaad3c3fb1cabe23c13115895"))
    (519007, uint256S("20ec3440c774b6898cc33c3dfceeb04c33080fab29ca09046108d5ce55a49a6f"))
    (528275, uint256S("89f451ee40f858a9f4ace6ceaeed8edf315a918c86374e6663c586af28cb7b68"))
    (537543, uint256S("498444e40b9ae769a4b84ff6296b043b659662b84a4d10c3765b293bed0a21a3"))
    (546811, uint256S("1c14712edd6c419eb5eb5ef5c804da7aa4ecf84449893c71c2c305351ecc0da7"))
    (556079, uint256S("e7500d960b30ae024b94d97c509beac0e95b41adc132fbde2f31fb01806ede50"))
    (565347, uint256S("3800d13e167c21b76614b0d4ab3600d082a1362c280dcfb9913678278570d709"))
    (574615, uint256S("5d36b6abe889938c2caca85d340708c35a56f27e9a497a080986afa4696fedbe"))
    (583883, uint256S("8e9c4ae41dc27711711f7a176b3595a472d234c143e38ef6c2de8057e9056b6a"))
    (593151, uint256S("4f4a685d6e04934fa18fe3bc1d989880258663f4f4d85f9f1f4b7d0396313ddf"))
    (602419, uint256S("96f5d690cd8a0473aad65b59223b4b58c9121ec1f2a379afbc4fdd13a7f1c149"))
    (611687, uint256S("c81a3f4831fa3ca02ccefc55339d28cb49db68ad9f63f91d87e0710d40860ea1"))
    (620955, uint256S("e9f2b879fde0057d69aad2f1f4c8ef7dcbc9d67c63a626ab0ffa67ed1f2c2354"))
    (630223, uint256S("6f107a75446100dd5bb0c9da2b820be6b89a809b8b6a9634ffc9976a89deee23"))
    (639491, uint256S("19ad438f19b11cea9e5b8104a370dad0d0bc140785985861917331bf70447224"))
    (648759, uint256S("6cb39480c1e11274658f087155bac2ebdea7773cb4056e528caf4f4cf339b939"))
    (658027, uint256S("64ab3cc4b07758bffac9293de87fb0e9bae63540fc3240bcfe54c04129cd0790"))
    (667295, uint256S("45de41fe724e2742740a5fa253a571cc756b975898dc5df208328cf5ef42c1ed"))
    (676563, uint256S("90096cc49c7cf590e8e9560f94f0b422ca92d4b1c68ec2b9ddd775b83f8ab220"))
    (685831, uint256S("9f93d57cf605dad9d2a0b64a2f1cd9c8e16c04347800076e196a0bc86e0afc5b"))
    (695099, uint256S("c306c681f45a957396bdb2ae9cfaa434690a1ed2c635147c90446b9366ab5fc0"))
    (704367, uint256S("62cc0e765e92804c9016cda3d752b6bbb87254fc42f29de1b166953422a061e2"))
    (713635, uint256S("d6f5525b8cfc7e9f576b0aacfe0833479901c708271f451bb298e18029b9f36c"))
    (722903, uint256S("7b8eb70afa7323bfb42957113bb944bb6e7877c677d8b90aa068fda6e9275c7d"))
    (732171, uint256S("3b13e3796513445e58a667143ac85e8f66a55319e503c9f967e4da8d6f58a413"))
    (741439, uint256S("0f4b79c2baa4156d29e9772c21888aed832885d903bddd4031a04cc6c37b986c"))
    (750707, uint256S("0c302efc30c194497d314a7eba0b3507242aa44fa68fb922051d70ccff11f0c9"))
    (759975, uint256S("c794762ec3a04690672c5d3d88f47362c9c6eb7a25dfb3de3eaf9bfa8fded6d7"))
    (769243, uint256S("5ec4d850a314562cdd348dc34cd0cb663ec4baa03cf7a0e953a365ae501a2ac6"))
    (778511, uint256S("265e5b9c918f677bf95c9bd52df5210a9b7f9950245732e76f0f164d4699a0ae"))
    (787779, uint256S("fa71289dc02bd5c9b8eeafbfa5b59a7222fd867335f8e3f6397314cc1a69f892"))
    (797047, uint256S("130fdf005b39f0e2b4fc626dc4aa474089c13a6bd053bfce43336ae991ec5bf0"))
    (806315, uint256S("33e12a46fc4b52a380bc59fcb6bdc2a8698d966cbb18d3d753ccadbb68e12f20"))
    (815583, uint256S("43f04e06514e8ebc214c37d4e4e7ae5d1f1b1349d7fff56d24a2006dc02db827"))
    (824851, uint256S("7a1a1529339a2072219332926b6d42ef10e93f72cd8dbb517b3d1d4c800114d2"))
    (834119, uint256S("dbdf09cf77ae3d326289d1b7d76944e85648e94dd97c01ab53b2c29e4efc9b8d"))
    (843387, uint256S("a9b1bff8b78bf1e00863acdf17b8904ad86eed1ffc6ebd596240982a1efe0b49"))
    (852655, uint256S("67ff6b1b6fac294a3c708ccb4963e6a82b32202d0d60bca4c58d92012b9ad649"))
    (861923, uint256S("2612acd0233bfacd92cb2bd0506320e7085ae535f33658c381193acf28390258"))
    (871191, uint256S("d61d34a53245c542064e252227a15e468b8dcbf63f3cd7237c32a5dbe37b4ba6"))
    (880051, uint256S("0a77590a715633c7962b7363893870cba2c3d0a473654674e31d28c00336539a"))
    (888255, uint256S("384433f3d7985b910e58509fbcc6275d8e801daa4457ff97e48ead2a6f6d55ef"))
    (897461, uint256S("011ade0e84d15e6c645f6df7c44dca011e452157c876374fd07ab49ef86d9285"))
    (906589, uint256S("a56d8f7af720fa9f89509d009fdb2ce87d645df4467c0aac1158bbc452548edb"))
    (915763, uint256S("56c3d664ec67c1e028907bf2b8d06ceb1c07ce4f7af98739aeb73a659502ce80"))
    (924985, uint256S("1947d79834a9b77c88bc9073cd1a6904446c93ed620da8cf7cc9e9016e8b7def"))
    (925049, uint256S("d75a1304af2dff988945676726d713cf5c7a19cf78493781dca08c03de2207fd"))
; 

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

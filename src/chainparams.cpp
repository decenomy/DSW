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
    (15685, uint256S("453e3a7c0483157bf9705fce05ae5753970452c4a28525c7d546f9d3019e0c40"))
    (31371, uint256S("24252d5c5566b6ea114492322395318b24accdf9ff4a4286b7ec2f7c40d55a20"))
    (47057, uint256S("d69bb11d007da86dbde2cae4520abe06463f42c666082350eb7a23c62fa0bfd7"))
    (62743, uint256S("bcb5392d5aabf37cac32b2bc2404d37c80b494f0ef3d97a5653cb26f50e65531"))
    (78429, uint256S("ce8e988cf3d116f0fd317780042eadcfbb46027430fe1346a5725cfc9aec743c"))
    (94115, uint256S("8719ccd02e79ef4f21791d4131705b1fd79bbea35f5426b8551f315a2ffe9da4"))
    (109801, uint256S("1f1e8846137f5cc79a29d6027b5edd2d5625858a469007d275967fed40e94634"))
    (125487, uint256S("9e32ad5b0b16f50749e38d5361f1cf5bca929c87a92ed0147b338a247a9d84e7"))
    (141173, uint256S("a4f2b6118310566299b99b6f6419d1baba8ed9bd710b2c6553baa97233e848a3"))
    (156859, uint256S("32ea7b25808de29ae0be59de4752427d6dd3f6e4218ca0579b016b63911113bf"))
    (172545, uint256S("c63524243eef434a61db6d2c4f59a9f4f30768bc7e3c5349a4bb513650305df8"))
    (188231, uint256S("82ff28037a9a1b60d4fc9928840bd274678b236bdc0e78ce4a7e30d0542e315c"))
    (203917, uint256S("3b67a368d245f5ddf52719b1d37a04269931daaaeb0da8064b38bd6a133596ae"))
    (219603, uint256S("1ca99740af5a4d36ebc4aeb8c832bef218044bfcf2cdeae9de2c94dc57487eb5"))
    (235289, uint256S("721d60d274c93f410066200bc0adb3f1d9ec096d7bdeb8a2c88b52dba100da3e"))
    (250975, uint256S("733ab5f31a8cdb5195a3eaa0993f06a5e32ee9550ededb81b52eec63ea1921c2"))
    (266661, uint256S("c03eaf7a33ba2474b2d723c3c2422a584bf34eb0788502851d2d7465e83080df"))
    (282347, uint256S("c0689ea03455cf05f770154b71819453ecfd054196f38a3691b34db2d587dbb4"))
    (298033, uint256S("5c15c60d49ecfe068396fb9013981197317ea7370cf84924eecd2483c6b5be5d"))
    (313719, uint256S("c1cd33d8007da40a334e5a6ff448b4e6f0b1ce83ff6b32fecc0fe959e2db13ff"))
    (329405, uint256S("c9304c58800b00ecce6fd091f4962e2b43b45115140651c4d1cd9fa8f01416dd"))
    (345091, uint256S("a9cac3565f9dbae754e5e32c7bea34f980b6688b1ae32658e01942fa897f5694"))
    (360777, uint256S("f21cc0f1e2f4a2b58ef5379283ac1633f59387f90c7f15ff21c6b0b7ff89d3cb"))
    (376463, uint256S("e4499bb353be2fd63e8d40efc103b2575234fdcf3b2ef12cf4974f32a093e5c9"))
    (392149, uint256S("22c2fd8f013d88e5d01596b4233d7daa39e56685ce73f6ea5e296eec2b843700"))
    (407835, uint256S("9523606a4ffe8f51b6f53f35ee94f6a57bff52cfee7bae4a23e5e826ffcc9bcc"))
    (423521, uint256S("f58a1fd25bc4fbbb79049436b3967dcbb3d430d4b83fa0cbf6dac60e68ac9603"))
    (439207, uint256S("3b426847a5865b4214790c6b23cdbadf76b2e7357bb3c44274adf56fe8ec7067"))
    (454893, uint256S("396d630f6cd7cd7ff031bf2675b2a45c6ec60a72a7b5281b77394f3ed554ccd9"))
    (470579, uint256S("f5bec6063705ed60a1d415d67750eec0651a3fa1ed9a0aa4916ae43555a3def6"))
    (486265, uint256S("e30c8d6fad26bc2a10b8c57fa61572d0da4fdddd80d8aafeba966a8b4bee8058"))
    (501951, uint256S("481dc8c7c13574537637fcb40a46eb152c42e906a65c90362aba4720d372d085"))
    (517637, uint256S("2ec984d99cb191c4669567cf4d935fb430d4024a807cc0f4cbdd4be1839ac7df"))
    (533323, uint256S("b9165d9f094c5997e8762341cefc7d105798a63fb9940ef5423f3c5d53221011"))
    (549009, uint256S("3205d44ddd3b12619d3b4ba7fc36980d9892530aac5349afa2c70e831b9ac26e"))
    (564695, uint256S("e793df7c3214dca1cffb80571733fa34dadfce3c111e14b58779d8dcc79e611a"))
    (580381, uint256S("61dbee8bd47f5c5ad9651840450b07d62c4469aa89998635433b4498271daf77"))
    (596067, uint256S("669e4c132796f9c4c98c37a23c0b4a6adaad0eb51a4f9bb2b13a57b70eb4c5c3"))
    (611753, uint256S("8c0baaa33f3573a20ef150bc6e24a706b3ba3c285bf05c91e1b86ba35dab5ead"))
    (627439, uint256S("afacb6a9bdd69bbf2892279db54bf31dfe4e0aca9a5844828954852de7539fca"))
    (643125, uint256S("24d73339dc9770a91cc2e5010c2573554741703177893851a60cb8f6d5aa8f17"))
    (658811, uint256S("bcdde18fc361712322bc86f6afd4f6763a2c8551d0771212d2575420c7fa1b3e"))
    (674497, uint256S("7353d8daed1a0461ec26ebb10e0c8339511fff40aac4eff998b61334e21995f7"))
    (690183, uint256S("18ec9d6f62b33c8bc91ac0f1657d3a75b02462af32ec7bf0d6d1586bb8a037a4"))
    (705869, uint256S("d148d3d0f0ed43a2158e739e5abe8777627a2f4a755f05dc1c84b35c1196d53c"))
    (721555, uint256S("462ae02e5f4fd22d05b0eaa0a24ecb0cd29a240ca1f6c1d3b7e6a429aa16d6c2"))
    (737241, uint256S("e65c875c33957191ee9d4e0d0f64541f68bdd7d1380b856f2e7eb8b849862ba1"))
    (752927, uint256S("b6bd276e5e9a41c2bb2607422c8dbcb8f7950c60a13b12dd9d3aa6305bf87f63"))
    (768613, uint256S("8ca9701bf450e68dea447b503e8a9ea42242bded62e847e8691b63a560603299"))
    (784299, uint256S("eeb5c7ccc1c90458d853998090172a915293b6e7e50b2f893b4d2f112377974c"))
    (799985, uint256S("38237837e68928a9edafbb96727019da51ae4659d44ce8ca526e8c1dc9ae5d1f"))
    (815671, uint256S("1e483c2d6cab356f402762176e405fb374841c45b1d159d30a1d6fc28f1f3e2a"))
    (831357, uint256S("f47c241822c95e1f0e46af352607212ec25e0c4cf94b788e00beadb4eccd4102"))
    (847043, uint256S("30ae8f617741884a5570720163621ca1c6f3642be4db1e55509b4fc95fcf9962"))
    (862729, uint256S("b87cb1984200d4287760dbe1fb3788f7aa45f60f6da9d06bf055da0794e2ca6b"))
    (878415, uint256S("d59be6a03a3ff91bd013f44d0e988804a44d5f1617acf89a3880d62cc90b7d15"))
    (894101, uint256S("5a009fb18b393b72b530c7451cf61a45f37b4e3f614124e57bcf98451cae0633"))
    (909787, uint256S("b74a368366680d4d128f1f523d697b2e01cc0d874678e1ba395f4afe9425bae4"))
    (925473, uint256S("91fdd981a4e58fffae77d5a7f4f9a249ff9522180f79e45345a2ce68d3430c12"))
    (941159, uint256S("6184fdb00c33e1cd7ae662128fe92e1f52bcfb6787ecf020bdc68a39f76ce825"))
    (956845, uint256S("4e35f1d1e904202c156890ea42ce4bd620e8e87eb1827830e4c2491ec2d59f15"))
    (972531, uint256S("2fca1352164778bd07152b87dab714c9dbdf9e812f9dabac1c210e64e6b5bdc1"))
    (988217, uint256S("e08cc12a8eef86038723f9cd64d5b2df06566f971168d6cdfdf00c15b712d388"))
    (1003903, uint256S("943dc24b4fc106f6394304d5b27e249ef08dc8719473f477d9a2605c73fd15f7"))
    (1019589, uint256S("f8eb2c5ca09179ebf5a55c96c27288bfe3c33bcccc0258eff97fdb0dad501f4d"))
    (1035275, uint256S("13df6dee01bcf23d4d9ae10b612a67e81ffda4b3403a0a0a6227e510bed4c2cd"))
    (1050961, uint256S("d31bb3cbe23f5cbbb8490c9642abda5b6448959a5cd0dd121cf466a4cbf0a530"))
    (1066647, uint256S("9ce17192925165178af5f4c52f22d3a607efe68f69f1452537ca7cca5bfb4593"))
    (1082333, uint256S("35aa95dcb01df8f13cc4055a157b42ac9a23dbb2df67791fbc38290c492b3f22"))
    (1098019, uint256S("33acacc5042909994e11ee47df8de9c7bf155d9ba7a28117d9aa158a18db30f5"))
    (1113705, uint256S("fd19e960a06e4ebd6f37d08e54b0366222c432923098c9cd571a1d1f4b0f34b3"))
    (1129391, uint256S("b4898f2fa050ebb8ec17298fb601910562ecdba6f9037e3426bc535db3a08a43"))
    (1145077, uint256S("61bc7dcff9c983026eb921102cefb03736b46e8bcb3954644a5aa66137d6a59d"))
    (1160763, uint256S("86f1f3a1f8acf2ea057508afe01d87ee9416ece5d922c205b3e4943ba1c20ab9"))
    (1176449, uint256S("52f9935fc79fcc572480d29581fc50782dfb10cb86688a2d081e1fd0a12f2a2e"))
    (1192135, uint256S("8c43eddc260f682c55deea1e357590c715ff9affab130e1847066001049c8283"))
    (1207821, uint256S("23d96439930de27dd7454d622d0d6f663eb594a8eb1cd4ca1584e215b718e7b9"))
    (1223507, uint256S("df4826f0a42da75bd83d428c6a7dc4b74b83e9a131caa2d5322ad18e2dc0a1c8"))
    (1239193, uint256S("6f16f614082266e952852fafd3be7a18cc0d356593c58f8c2dd03387123aaa68"))
    (1254879, uint256S("77406ab7ed8e8d3f010e704790d441c2170066f1339ef6b608ef33c50bdcd020"))
    (1270565, uint256S("79516b2d3d936431b0bb919e33a335138ad55df0ef72c36abb9ad6a3451ba26e"))
    (1286251, uint256S("95c8ec1bf4f0141ff72d072be6c654a50a406b73a44a7b37604700706fe5365f"))
    (1301937, uint256S("06f59ae87de33bfccd51e5bf83ab549f09fe5c45a768df6c82e969adca31d361"))
    (1317623, uint256S("f0a808090b85abdb4870ec02242281a21ed7a35aad7dd44c37caa54899394776"))
    (1333309, uint256S("79c332e919563bd6ad348ba806ca4c5438971de6b43c95cede53391e1c85cbb0"))
    (1348995, uint256S("25e8b9e4b93bc861937e8388dccb5ad4a62d575a138869795b88791be084997f"))
    (1364681, uint256S("3adecac5339d426b240cf4c0b0d4ce7917a9a03460cf7d75da65de94de448beb"))
    (1380367, uint256S("fdb7d57391b743e8709ba75a6e38898611174b8a23ccf942c477e55fbc119f3e"))
    (1396053, uint256S("36ffd96787b3132f82791a8bad65e9a4a688420a12d4d75235e10809a6cb8b7a"))
    (1411739, uint256S("6ae876c7b08a7fb105183646fac2dae8518d276ca50e774b9aca4d3c3c5282d1"))
    (1427425, uint256S("e1edc6d6e86d36fbffdb054b6d89384a0a754c0de1047d98459629fb9672aa54"))
    (1443111, uint256S("7716f85405c39f770c10696de67434deda1cfd226a25ffc2afd62056a9d27cc5"))
    (1458797, uint256S("b7bbcc6a97eb26aac2d59ce1b8a47b9a58429eb6e4101324d2682c529bbab2ab"))
    (1474483, uint256S("4219d61196f84c1a35bf81a1e5831d9dbd730cee26258a5ac473553c8a35f598"))
    (1490169, uint256S("ad477f77e0faa6e358828dc7bff5a2f27a09a3ec4760bb1d6b182591031e2868"))
    (1505855, uint256S("8443bd9ebe80442852622b57aa8e890ac99057cd778c62cc0a28ee6243a183c0"))
    (1521541, uint256S("9d0edfaac32de30460363b21ebb49b583d782a4608c56b58b00abb71c9ff8ec6"))
    (1537227, uint256S("a24a7fdc35c90d9ac6f6253657cb16f55dd6d1cf423b45e8060fe0c3feb27410"))
    (1552913, uint256S("c69af57ab2e83d7406f6df23085862597d650b6a160fec33bae5671e55067059"))
    (1568599, uint256S("0d201f32b6a733fc9b10cf09a578e8be179190454dc1fa876e753fc8506987b1"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686505965, // * UNIX timestamp of last checkpoint block
    3225535,    // * total number of transactions between genesis and last checkpoint
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

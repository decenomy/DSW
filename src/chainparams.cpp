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
    const char* pszTimestamp = "25/Apr/2019 The SapphireCoin Launched!";
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
    (0, uint256S("00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"))
    (11880, uint256S("cd7f5d916094cf2d43dd9e98947f6c6473ee614a831d8f7739009b4f8417d548"))
    (23764, uint256S("9c2112e50b983db4b23057c2839e2aebd2b1e6c9bfc2b3331809f74c9e1ed749"))
    (35652, uint256S("4b2626c20e2ddbf5fc47a8b8fffc3193246529d22df4f40bd80076e47a1b5c11"))
    (47691, uint256S("4241a9193ec6b776ce7e14fe0b582f98eb64037d42a12efbc7b4bc55f2a30ea9"))
    (59696, uint256S("ecbf0dbe5da1639ab3ef1d333846da5dc9dab1f97d621c2499305342d6c8fa35"))
    (71906, uint256S("917feedb88950cae3a6c8f64e67084f10da0b8535363b31a1cd9472888ac3f3e"))
    (83962, uint256S("639836b8c169acd8435390578b76acd27f3dd7879c25992d75f1b6d28148cbe3"))
    (96116, uint256S("1e56af4c378aa0f3a4991dc16f72fa839c9db2994e8c77a744b49caa29267a67"))
    (108314, uint256S("8224d057363e279c6646ba884c3f0e833e8a4ad568f4c5f46257eb5a333d154a"))
    (120725, uint256S("9403d27d69c652a2eb2b4bdcd9b86161e1078b47225401696c653ddab74c69b1"))
    (132845, uint256S("7e5e3b3fa5045a64a7f59370788c645a1e8e797b5dd5fa9590a8038b5fe872b8"))
    (144873, uint256S("80067b7a053fd09c7c48f34368526fb45a1c7d7dcb09539fdf76e7f1fc70a4df"))
    (156968, uint256S("d42d1062c3078cc2ae048c64792f7c439e5fb10fa5690ec6200ff741c5fe928b"))
    (169075, uint256S("9c773a944112805070be3427c635f86f5dbd412b98dd98a5ac4088b8a113a6da"))
    (181202, uint256S("91b75b3e659f51dad30f9a185fcea8fc5a1bc21fcf7fc9513f2d2a8e2f802434"))
    (193270, uint256S("3504a238c313a8e71deef2f44fdc5713e1aa6f28fb9c533d7b045a8336e40f87"))
    (205378, uint256S("6e50d5d5ebc97d5be079e9d70ea42001ba9fb392ae1e86245c3a2d2239aa286f"))
    (217617, uint256S("2db8bf7499acc009f94617c4550bce958a40f935641980843ae358b445840b71"))
    (229676, uint256S("20606e270f53a323cbd5abaf782cce3797790c49501803e69266143e96ffa55b"))
    (241822, uint256S("72e12ddbd45e660a9074edf71b2d306be23c35c989675569acaa4936bf4baf1d"))
    (253893, uint256S("411e2846cf51189f1e49e309a34b1473c3bfe6967123049d4150dfe4fe0a0712"))
    (265938, uint256S("9c92b5b018cb8017d25efa04f05ff5c870374d4e4d28712b2b388bb3c14c21ee"))
    (277983, uint256S("fc52d27c97f559b69af3f81c1464890f2ef3dcc07cb41ccefe61fa776a903241"))
    (289970, uint256S("9da7544538c1f6d12cbddb2d77c157619286589e3977b67651bccc60037a39f6"))
    (301885, uint256S("46daf05e91430621e0ebd247039f4bd17e1203e1b7b756f83b509e46c8094b8a"))
    (313769, uint256S("459f189d1d9269e7e4101eb6898ce1367fdd85b226c4c71417cc940da8c63948"))
    (325606, uint256S("1b004d1bbe02607af4de71345f4f77196c169a8dd8bd7295787f80016a0488e3"))
    (337449, uint256S("ef3df799e92625163d8486f2db2593b179ede2f2195b1fec7dfa0c3833a46801"))
    (349345, uint256S("d386935f49b040cd90128006ce3cd2ca14bd9fbb955b1f16e65be9bcd15d4b7a"))
    (361266, uint256S("d441eb5a3569a65d00b60f1976576d456ba49cb73d2d7484fa8d57c8fc47ff8f"))
    (373178, uint256S("6e3a6bb9b46fc27f23300ecef5328ce4ff476d89c227c93276bf84d5660fa998"))
    (385033, uint256S("2a7a26dde668dc3c3f02edca7d9e81fca53a2c5690850dcd27cc09d9f91d11cf"))
    (396921, uint256S("d59788cebf083759cd54a07c6c9c8d7441a77131e039c0ede80720113d9b0439"))
    (408984, uint256S("3028740b8ad8a5614e477c4ca33ef42a50cbf7372cd0aee16d3593e059d65def"))
    (420894, uint256S("9db8abaabe9681bfc66ca66e651a8f2f325b783d822be1f173eb0e06cd760df3"))
    (432801, uint256S("93d074e41757e8816a7deaf1e74d23b04dd80ff2f82d87605f2ce9de9ec5cb93"))
    (444701, uint256S("26545211a382e596e57586f795ccb85d6a5581ea77d6de6ccbf037722e554355"))
    (456548, uint256S("bcfdfef2bb67f0243cfa4b1ce4bb0a215763eec6e4adce2381f70bf62d800b1e"))
    (468399, uint256S("8da9c7a4cfde69740b5130836c8884fd10c55d25f400a20323b051857104a53f"))
    (480299, uint256S("9782fe317e739e3060fee7f86b619bd0688f7ef6b5d0924c9510a08780fee887"))
    (492140, uint256S("63f382eb11f4f2dfdaae7d76aa291c7b71ee969dcccee6ade54e6c99312ec674"))
    (504005, uint256S("9432f9b7f586e8b1c4fbdc8905cd3838f675cd81894fc1d86557aaf07eac2b9d"))
    (515864, uint256S("4bcd22d87c4ea41e8bdf3c3edd62d8d42f085fd655073a37b3559183c1e98f8f"))
    (527769, uint256S("f8bdc5ee670c4a5631d619cab7a35256ee338408cb27891d072cbdb61d9c81cf"))
    (539662, uint256S("dbef7069f7e66879ce37869c2294d712b8c0b6267fcf3b838ee30465f99f07ed"))
    (551541, uint256S("617cec9e27213ec51e76f4b433b055335ca44e469569ea8605b000ec05046132"))
    (563495, uint256S("9e7d1ed051ebc33c8b87b8c5a59543f3133b685518a4d283694d10ea0ab7378f"))
    (575467, uint256S("25b9c2770e4fc3ca91f7b4f78efc4853c26087695036e2a09047818fcb1388d9"))
    (587413, uint256S("861d123d1acc8b43b6311aa7dc121fc425ee786c21b55dc715b71326aa2c6abb"))
    (599274, uint256S("4ce417c84dd4558aff5781f5480b210d27506fb811e7048ab294db7fdf58ea15"))
    (611149, uint256S("1aaab54f036f1199c8b3a931319ad7d920d45c96fec179ebcda62df37c0cfe70"))
    (623012, uint256S("50c1f3076978e1fe1050352f0af4aa1f40272201b96659dd964ed547294fbafb"))
    (634891, uint256S("1a0c2497ea5fd0918469b10110305461d996677ad26d9229f11f5939c02c95cd"))
    (646760, uint256S("d55cd8d96be002fe422e1380ee8cb8ec865514096e41590dad192fa25312ed49"))
    (658637, uint256S("02249fae8522723d25071b650689a09a1aa318a9a2ef5eab401674ebd3a4c7e0"))
    (670504, uint256S("433b86c62e3c07d82380241c45dd110dd0f1045598e60b0a9b12cbd4bc664cd2"))
    (682379, uint256S("64e4e58d87c46691d4a2af74bbe1a1e30477484ccf5ccce658b57a4efc79e8a7"))
    (694270, uint256S("4e14596189ad7116b2e83e64a92860385f3f79e35ef8dc5230c91d6ef7b27155"))
    (706147, uint256S("569365843984e08803d7739e7bc5b95a6343f8f13db905e37cfe05fec32afec9"))
    (718042, uint256S("48f3d0b81205e4a2f53f9ef3349fa8c2abbdb42bce5d65d7ac15a4ed5c0b4aa0"))
    (729905, uint256S("040dd2a1671625d31d46c2f14804791ef9d44eb0225cd4a3fdc5ef513aaff38e"))
    (741787, uint256S("a7f7aa907b927312c7dab89b52cdc6466eea530328254c9ea1ca41cc9cc4f7e0"))
    (753672, uint256S("3198541898f4f2a69413387b546e897c14f9861c54dd82848faee5dd6260dd69"))
    (765598, uint256S("818d985c2f6e67b4259bf24ce0a3aad38d04280d40e7af6bdac0d476400b2367"))
    (777502, uint256S("1441a6ad5d81d2d2dbb3e1b8e1380d57167eb82f8a4fb7ea1c186d31ddf5dea5"))
    (789430, uint256S("bd8386877f8732b9039a9aecc20657c2df427f6820bf09658e7f2963968af9cc"))
    (801347, uint256S("ac43d01776687e3727d2c3e503a261731b93895c8de96cb4a1d7ebe491e8c8f5"))
    (813300, uint256S("e20d17c81454281442a468fa2f508b8a62a2b044d62fb61b7b605bf9b09d1482"))
    (825243, uint256S("1f8fa3a66159c0aa13aa1ae118e7ed9c02c5cf98ceacbae544ea08ae6f72a3b9"))
    (837239, uint256S("87aec769759965aaddf2fbd694a1ea59f26c51d02dcf20e49f740ea6bace532a"))
    (849424, uint256S("b6b8b61efa890f66ccc986f1d4daa4a9405ae498bfca4040b623e1d5ae981219"))
    (862080, uint256S("c5dcde95a91bc355d9404c81df334ee10b67522b196c43dc546f38ace2f10cae"))
    (874735, uint256S("83e3e7cba5e3d74e15653df7340f9f21367167e16a60c04a9879d5c5d41a299c"))
    (886574, uint256S("f07f9ede0c461532978bca9445d541da0b5d5902c1f24f1e82447587c79b5d9c"))
    (898411, uint256S("f9fcf674d05357e091f1266e071bef0740d7596c41c74045f6c098f3d659045c"))
    (910248, uint256S("0c35f87f2a5eb973a05a66650a737e1ac0869707be7b4558d087db24c3873950"))
    (922085, uint256S("1db377ac73fb121c685c1c71371025dc4de3146bd8e629a71b8484d5a9b1488b"))
    (933922, uint256S("bec53380a132cf9ee6c2c5feb0fbbd851bb66875793b4a1c1f56d3e512bc682e"))
    (945759, uint256S("44555e85ea65977a2621a753736ccaf08a9dd5bb2a41d5dc55b712bcc3553c60"))
    (957596, uint256S("01e94900a6a6269788e84b8e8ea6817e94f41c003554bfc5907006f51c334fcd"))
    (969433, uint256S("6913253544e16f55215bd79d714c4df9ff2527fd64b4f33e5a46c03d2e8cf6a7"))
    (981270, uint256S("92914539c7801dced0439ca93ab1336a65659aeb80d0c60a6b1d8971f75fcb1f"))
    (993107, uint256S("d06b4c2cae47fc2bb1ae1e589d320833492a6c0b2872532cf478c4e8aba385f5"))
    (1004944, uint256S("458be9b1116332c960b3b43f4a71ce6e934cff7661c8f18640b95861dbe58b47"))
    (1016781, uint256S("38697136f149b5952b29b014f49e8c03280fa9dd473c3bed31a81706906516d6"))
    (1028618, uint256S("2dd5921927e4fbc4eb7b261e0b7254a81fb863972f49382a69e56225da5da7f3"))
    (1040455, uint256S("6ed1bf87783abe7a5352768abd5636791e01b4d91488e5add03b328a3fcf8dd4"))
    (1052292, uint256S("acb587364b93155e741db7794e259c3f2d9b382f79972f6bbdc7855e2fc8f3ea"))
    (1064129, uint256S("f9ba65f6ff189b902f2044aab152270abdf0fbb8df5b5161a7ea2c46a2eafc6e"))
    (1075974, uint256S("b127f6626496ffa286cc652f98c013a436a782c53e00174972dbd379a1940a34"))
    (1087811, uint256S("a9e7e0629bbca59a227414f6902ae9d6ef32ce07f49aac92ad48d97e6bc4ed4e"))
    (1099758, uint256S("a87ef74016850f248ff5dbb36eeb9d89f1ac706d17a17fd5bf90fe78e07eadd7"))
    (1111595, uint256S("51b758384fd7ab13281a1467aa4c5de1ce399ae92434dc76cff26399808f5ba4"))
    (1123432, uint256S("cf7fae4ba123ef68eab2bc16434bb9073506617c219ba26c19afed1a0b81f922"))
    (1135269, uint256S("d3809dc62705e009957878935741dbbf01692739c60a37d734b2e9881f07a059"))
    (1147106, uint256S("633eeadd628863afa0ceb1bf46f7eb422c7c3941689c065ce1ba1b428d92e860"))
    (1158943, uint256S("a3be98f51070587dcc341222d20028b04f0a724d26742eb97f86e2b89c4e5323"))
    (1170780, uint256S("222ab6656d2164e10790a484d394e52171cc7d61acd6dade98e8b46546aa68bc"))
;


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626875610, // * UNIX timestamp of last checkpoint block
    11936769,   // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1605265870,
    0,
    100};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1605265870,
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

        genesis = CreateGenesisBlock(1556165178, 2894113, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 3000000000 * COIN;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "SXXXXXXXXXXXXXXXXXXXXXXXXXXXXFdBi4",      0 },
            { "Sd2xcwvvtRH8P8sLemSiPjadTfBd9myPbW", 586593 },
            { "ST74xpmzemL4ELiBpyDmirzgahujSUiYmM", 586593 },
            { "Sic7sZBNkijna4zNLSVgTBkfr2ebP6c9wk", 586593 },
            { "Sh8N9R2Li5Wm5B7g3xxfEotp9Vpp38baJM", 586593 },
            { "SVAjKY5p9NPSNwG7PLK3VzeXUdJjm2W7CY", 586593 },
            { "SQfMZVatpQR9b3KdKp992nxeEZNWkcz7d2", 586593 },
            { "SNAgLi7pfHD6BDAkQQ74ixtT4o59wkqP8Y", 586593 },
            { "SS6ZgTuvafGX98YqeHdu79wpGrR1KxuqMw", 586593 },
            { "SMoP6U7uazpLdqZ18GQFVNNuV77UTK16wh", 586593 },
            { "SjfZFjCv2PxNKQeDgW1RmsFjSpq5PngaZc", 586593 },
            { "SPop7eX3kMjwojy1k1EHAqBoodhbski4tR", 586593 },
            { "Sf3KBrFqmD3PBHrwTpdsFgUTctEz9mQn5Z", 586593 },
        };

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
        consensus.ZC_TimeStart = 1556165178;        // Thu Apr 25 04:06:18 AM +00 2019
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 905001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 905101;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 905201;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 905301;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 905401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 905501;
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].nActivationHeight          = 910001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1200001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("ef544e9c4181e103bdcaae6153aa90495f1f830a91368364c4b8b97a3782e579");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("c36a49839903e01bc2d6c44f20516fd5f3d816cf2d16cd30c488986668bdf269");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("2033cd79c94ef01e04c0b886944350af7af4ee2dcdf2bb2a8f417ea48dabecf3");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("502226d6ce3e3fd036452b59b0045ff478658b00a42fbf3434630cfe775d84ae");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("9002e71bbefb2a10d5208b7e8e0a2182d2b13a55585c595752454c65dc9cda02");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5b37c32d7c08cf98df958953dd4c32820f0609a4f4bed452fcb0811bec60500e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("f6326f790d1c0d01843913b301b56dc0d984e9d76e0949669cbeebda37336cf7");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("96dc6197a2d0cc2b9dfe5487b35f0d5b051d1dd958de19e00043897223c08ea4");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x13;
        pchMessageStart[1] = 0xb2;
        pchMessageStart[2] = 0x3e;
        pchMessageStart[3] = 0x58;
        nDefaultPort = 45328;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back(CDNSSeedData("seeder", "seeder.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed1",  "seed1.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed2",  "seed2.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed3",  "seed3.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed4",  "seed4.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed5",  "seed5.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed6",  "seed6.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed7",  "seed7.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("seed8",  "seed8.sappcoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 18);
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 25);
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x02)(0x2D)(0x25)(0x63).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x40).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added

        base58Prefixes[PUBKEY_ADDRESS_BIR]  = std::vector<unsigned char>(1, 45);
        base58Prefixes[SECRET_KEY_BIR]      = std::vector<unsigned char>(1, 139);
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

        genesis = CreateGenesisBlock(1556165178, 2894113, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // sapphire starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 6;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.nTime_EnforceNewSporkKey = 1556165178;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1556165178;     //!> September 26, 2019 11:00:00 PM GMT

        // height based activations
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
        consensus.ZC_TimeStart = 1556165178;     // Thu Apr 25 04:06:18 AM +00 2019
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 878611;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 878631;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock              = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x46;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x64;
        pchMessageStart[3] = 0x23;
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back(CDNSSeedData("tseeder", "tseeder.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed1",  "tseed1.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed2",  "tseed2.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed3",  "tseed3.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed4",  "tseed4.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed5",  "tseed5.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed6",  "tseed6.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed7",  "tseed7.sappcoin.com", true));
        vSeeds.emplace_back(CDNSSeedData("tseed8",  "tseed8.sappcoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet sapphire addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet sapphire script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet sapphire BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet sapphire BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet sapphire BIP44 coin type is '1' (All coin's testnet default)
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

        genesis = CreateGenesisBlock(1605314006, 18440, 0x1effffff, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000529df5fae941569b6466128042f5f036a8d1d380dd484a06e8a12fb275a3"));
        assert(genesis.hashMerkleRoot == uint256S("0x62179b80cc4da52f1ff4bad5d690836a3a663d14d5581a63822963bf1613041b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // sapphire starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
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

        pchMessageStart[0] = 0xa7;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x72;
        pchMessageStart[3] = 0xa8;
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

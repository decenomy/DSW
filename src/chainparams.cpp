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
    const char* pszTimestamp = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam felis.";
    const CScript genesisOutputScript = CScript() << ParseHex("04eddc90a654f0335fce2081f682ec2475b935afad5a217ffc9a324b04665054e8a42e14cfdce6a5d11fe0f8e1de9b0ff375905dc58025db46b49f7925d3ff290e") << OP_CHECKSIG;
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
    (0, uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"))
    (17914, uint256S("8ddf5a517ec5a2ab52ec69e900c519a624d8cf35d93d3ef4033b97ba3ae99eb2"))
    (35829, uint256S("c4f132839bc7da660d4d9c010a051f9b7fdf12a2399ed8a59b9c0109d6a7c716"))
    (53744, uint256S("9f2b91688fb9b3c037c332372f6ccf1c6b837aa1eec08e3467b7fe4e8b0e97a3"))
    (71659, uint256S("df998283e19bf93c9bb1b1567211c2b2b3029c1d7612ad6ef7e502ab632373e2"))
    (89574, uint256S("f5501bb6c939abb720a23121bd8ba414fbe49b3f70339e21febde6950d276c0a"))
    (107489, uint256S("17a858e65ad67c18164ec7e2a2485fe6a9b468fc8118600326b1b42f93dc535f"))
    (125404, uint256S("4fd655ad51c74aa2237aa5ae32f426f33d0f2b713e826aa9ac29e6dc62ed6461"))
    (143319, uint256S("2683c69b8f963a37c4b77103eb7b05d98db8f6d0ebeb362bb4b437941444315e"))
    (161234, uint256S("b72db09c0b77245497daa0e7c273c9d41724ee8cfaa6bd7cc86b91153a2b91f4"))
    (179149, uint256S("099321274a629a028a898df9dd09bf6d63626fb09119f496e4d5706c0cf5ec38"))
    (197064, uint256S("8a9c23cb7fcf65f21c106d37138f99890666995a6a6f02475d360d99739870bc"))
    (214979, uint256S("a8819cfc36a07316bbb3ee74dcd65e98c7f9081aa55ebba25cb1fdfb763c94db"))
    (232894, uint256S("65e323470bbefca6f6c7f0ec496cc9b0c4a2721845698b0ffc7d230bb6d4091f"))
    (250809, uint256S("296e158414a4ff840b4380d10543a08cd309a85293803ae693821785dd6e06cf"))
    (268724, uint256S("2a0cfb398c110b8ef680f63e54fff14e2967741fa8b2b15c3e0dee1d649a2ee4"))
    (286639, uint256S("80d8b3a5a651ee8e9eb57d9d5b566610e014e30977e1967ebc0db13c6d4173ff"))
    (304554, uint256S("894f6da73d818b976af29742c55a1200a7469c9255af1d4c46084f44fe3814b8"))
    (322469, uint256S("d9caddf78858d077e4cbd9d724c51cb2bc40fbe77b6d8b727e4d70745e7b1809"))
    (340384, uint256S("b9f26840c592e702f83166fd11b383dd7e66014303f0a8ebc62d1f5f9f3daf35"))
    (358299, uint256S("3d0e0fb6a21340e3573be916e90d189ec54a52a8ec7b49d98650273bcb287e80"))
    (376214, uint256S("5dfd73b57ff7a6d9e82a392460040ae7727e1dba79fa50a00dc9390628e7268d"))
    (394129, uint256S("214d5e979f2d774f3fb8cbd0c2d84aa4e90ed634644c7c9d0206e8d4f8f7ae9e"))
    (412044, uint256S("e02b22cb2c680c8b5ef68d52d21c6114b5a86b2aec0d6752afec64a7ae161152"))
    (429959, uint256S("84c90deb6e21b65f678cb2885dee683d8b54c0e38f7cacff8d5fe024e38577e3"))
    (447874, uint256S("5f5b8d0b8c31c3ee7ff3f144ae45023a3573e4422093d0737eb079bf6c00e67c"))
    (465789, uint256S("1bb6a47b0fbac2c46d095578037d4221f8632a193d01d4f4b18fc6ac392f2a83"))
    (483704, uint256S("5d4184fe89d82e6fff9ba695f2f7907c3c717466ec6ae901c1f50b892a800c07"))
    (501619, uint256S("c813508a5c9e427f294fb09c47df28b10279e87adb8b0494aa252f27df5cd60c"))
    (519534, uint256S("613078c3c4881c86b72fc5955f453cae0b06a7b29f4e594574138515d59ddbda"))
    (537449, uint256S("edf4a070aba0b06b2e60f892e08296f557726df681fcfda722dc4bf6a3083116"))
    (555364, uint256S("52438f7b0424dbc13d43edabe277df77081d21446262941686ffddac2cedc212"))
    (573279, uint256S("db473217f2f44a7e4825459ed1262fb1aa5e0b67db5b64ebb605a12148c44ed3"))
    (591194, uint256S("9ec16b61b410016c17c1af41ff93afeef98f3930a53b903dd3b9ccb575de6e94"))
    (609109, uint256S("c1dfcd56f81685a2125ad8258e4b13a7f547388aa6d2235ad9936fb37b8008f0"))
    (627024, uint256S("c161ce9b7d7868ecc867aa40d0bcda3f3a53658ee7f806a6aea30d6570c7bc10"))
    (644939, uint256S("e170bc2b3b23088ac939be711218255bb4348fdae35bac8b8bcf47afe6902c6d"))
    (662854, uint256S("1e971aa1f36381cc6a42e1c8f6e9c2b9f8e092c83904fc5580cfa450300e42b7"))
    (680769, uint256S("644b78579e829a5e0017b95c1fefcd1e78f4e521ee9ce2d5f1259d5b510c8b9f"))
    (698684, uint256S("6c4677640a650332358b26d8b8ae00125bbef2b5ef5c4ab297995398c9c44937"))
    (716599, uint256S("2c963a06d445b657f36737c46422fd3e188fa2c4ff58464e80e904be1f2cfce6"))
    (734514, uint256S("19859c3d3b400f6a8ec4ce667ec4268305dfac3afd3e432c0101a972f81bbcc8"))
    (752429, uint256S("3925e5480425ea581871d8036563bc0982b2b7534dc7867ef78a630f55e05399"))
    (770344, uint256S("20e590d69ca9ad9a3d21e076e9c0940aabd93957d5961537b24c34826a119b72"))
    (788259, uint256S("4ec6837c6f8cfb9199367c2a66a433ccb846b97633b65c362b9503b8da6141d5"))
    (806174, uint256S("8e5c5793bdfebabf1cacdcb0c66237feb8a5e2133499fc89e04a7d4660c7b775"))
    (824089, uint256S("842068d1d9982004d1f3d434ebfc5a6ee7d08ebe043a56ef0b376e6eab3fa4f4"))
    (842004, uint256S("f5b86d6d448e9d3115697bca8625a5b0c38bd86911276a35be68f34276b9158a"))
    (859919, uint256S("b1fdb5d962488cc308a17f7c2fb055bc0b3b8566d0522e568de1e6c2a7ccf5a9"))
    (877834, uint256S("fabc285e00b6c9a471280f187e3c7f397b30096f196df876e1322ddf3af7b278"))
    (895749, uint256S("49b1aceb717b9353ac65ccca37c2b8afc5c34fd571b71e65fdf2147e9d6aee28"))
    (913664, uint256S("c5f45619921b6b6d290cebf248e99721ccc44de5c8ecfa0c25ec9b02bc7be0cd"))
    (931579, uint256S("96de82633a2140419f8ee6187204b369af53166ee25cf8e347a472c61622ed47"))
    (949494, uint256S("a4fc44f6dbb3a42c2bf11a33e00f5280a4984edaaeab9fbfc665ea645a74c6b6"))
    (967409, uint256S("690c452fcf3c384daa12e7e3c97b6a945a8148931d8005eb97898ef55283080b"))
    (985324, uint256S("8f8f0a3ce2afd2139f17ffe675e182fd29246a1b650a88cc236b10857e40ed22"))
    (1003239, uint256S("1659fbeb1060913ca570a316e5317bb90ccd092f2309fd60fad842056fbe8eef"))
    (1021154, uint256S("ab6d30ebe8cf60092d484efd5ed7a1beeacf08d129f0dfa1ef67e8ffc648e929"))
    (1039069, uint256S("679675dda3c7ce8235664922e6ebd5e327478413de07a8cf1dbc14860fe53c6e"))
    (1056984, uint256S("ffa933d182e1211776a96c7e9eec8cd83b780b17b79865f20c95a9bd19856367"))
    (1074899, uint256S("911c679ee5efaf8bbc1d1ecdb885bea78715ee6e66758e0d41c4e8c9d15cb30b"))
    (1092814, uint256S("782811b802ba03c3c8294a6667d8e14bba400587fb87c37bb85fa478ba256833"))
    (1110729, uint256S("0b603620788d57f58c055c089f1eb3babe6746fa90336dbd6a2e2f6c1c651f53"))
    (1128644, uint256S("1a299c428502d1028ac7da23dd13876f20acb300947a1d8b81c094bbf76e2c34"))
    (1146559, uint256S("a1540a141998ef565d5ce8504d2e8310942055d25d765aa7a632c161dbdb90a3"))
    (1164474, uint256S("2cb4f63bed238e6d7b6760911d54a49cb7beafb18748349e39e69f26947faacd"))
    (1182389, uint256S("02c8581bfeac49c1d117339c1a3297a4a71f4b31996bd829a09f1c0457a44a11"))
    (1200304, uint256S("5ef2464f93931c9d25e52f3e1748c34ae3022e2a10a282964f177c5fd46bcc21"))
    (1218219, uint256S("bc8d4c603387823bebbd785ef8cb4043f147af408abd3199ef2ed50a91aa1fd5"))
    (1236134, uint256S("f5c525bba43628c2f578dcf1e766c2b682c74f91285c13249589e37a19a65630"))
    (1254049, uint256S("31e83b468892dfd383f3360dfde825ca43d7b8376012a5e10a770d5214edc9df"))
    (1271964, uint256S("e989401feed2c8aa67c3de700496295d8cce410c2f5e0f9af85ffcdd533c07cd"))
    (1289879, uint256S("0f7d6883be32095c70cdc8ce4798f5a4267083a919909e24c0ca3fa916af1b11"))
    (1307794, uint256S("62f01c3c5d7e9dee6226acdcab8e3faa926029d771d1001a7f2b399c1e6e7ed7"))
    (1325709, uint256S("199dd5a0d36541cf90e8b521bb7878e00e32219311841d0ef770fb82147814db"))
    (1343624, uint256S("d1271f85475379f7eccd3ee2d1a8c398c46d2a95a9f487a707d9d519e9db7204"))
    (1361539, uint256S("13dd687c746a3f199cbd8a6f608306d5e12219a6d00daf740bfac96dee0cfdd7"))
    (1379454, uint256S("1bfeb956b2dc4fea9162bfeadee27753742b69e6dc64f29f4c5374340524210a"))
    (1397369, uint256S("cb389e6072399c42319c4af8ce03345d1aca2e0e48c3eb35163afa8b4356dfa4"))
    (1415284, uint256S("71cb58b119ef46094662c24ee7def93ada4ac577a4b13fcb287df63bc04363f1"))
    (1433199, uint256S("32a5bc00ea4900250c4b45fea60c01b985e618ec6326adbdf17b08b2a6054375"))
    (1451114, uint256S("5fa0e17d75bea90f02d4322f81c17cd3148cc59ef5ba6c1df1e6ce584a01e0bd"))
    (1469029, uint256S("24875e505ccbb9bd863ceb2fbc02d1aec0cfde9f4cdd16925e3e10b0ba760492"))
    (1486944, uint256S("81ddac50fb00350fbd4513e6056fcebff6046c975e13279579c1724bbed2e99f"))
    (1504859, uint256S("916693a36e0e6ac3a3b2a84dfd29b8cb7ee5ea0f6b645aba9c01abbce451e0f6"))
    (1522774, uint256S("7f725b3d6f3deae751251ac0ed85c3b138215325ab558f4044baae260a52aa7c"))
    (1540689, uint256S("822d6149ece5e1ed454ff8eea9769412bc01285488ce182dde8eb214118ae9a8"))
    (1558604, uint256S("ec6cda7e7c790184a8e7efd41d6fa3dcb2cd4c71d8e964b0cfeca43a636713e2"))
    (1576519, uint256S("6d400d8a7d9493d9f01ec589f52853e85cb9efb82166485b7cc129ee1ded3ae1"))
    (1594434, uint256S("6d2a950b55550470e2b202dbf6e9333ae5686a932c38963c1cb59ba7eeddbf33"))
    (1612349, uint256S("a51a7a716ee0ff3c75aa469db0b632f83d9ec9a5e0c5ccc15c974b83330b3183"))
    (1630264, uint256S("90b1f1e2591ff14d4d4b781feca3233a574d5d35ce01f70976e642fb7aecacaa"))
    (1648179, uint256S("e0bb5fb301dfdef2608c071683adf6b3b6c4488913794bd5b272ec30d6cd34e0"))
    (1666094, uint256S("5e400c1f12de2fd1473ddac9961ac704d8ec5aafaf569ab80953db53955232da"))
    (1684009, uint256S("37fb4b6981b810552b14c8148d659537c6213790d0db49cee5ca6bb776ad1cba"))
    (1701924, uint256S("ff030ddc56f8f2298a8e73af4acc212fbc59ef51a11d48ea68d47e0751fca1c7"))
    (1719839, uint256S("6f2367f9b6e8855dbbea0b60d592abb93264c6288fce66c439e5c3f782394f03"))
    (1737754, uint256S("03c4acd57c374f1ef5779c95dc7a36991c0219a1e186738f9b0450b33559250c"))
    (1755669, uint256S("f723a87f9e18924728a48bef08ef64f3322e3c00e8ebddc31bf67baee26a78ba"))
    (1773584, uint256S("a56d1f9b677feb8c13dd923c067cad1ded964c41a8bc75d8ee745f0f2c14f2e3"))
    (1791501, uint256S("b92fc39090229d4397d131448dcfc034f26e6a6c1b97ff91029d4e2ba37c5ecc"))
    (2313795, uint256S("a405ddb6db325a8b1d5950f108a947935ace291d0521460633bbebfa93eb95d5"))
 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1675914735, // * UNIX timestamp of last checkpoint block
    5928681,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2880        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"))
    (1016800, uint256S("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231"))
    (1106100, uint256S("c54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30")) //!< zc public spend activation height
    (1112700, uint256S("2ad8d507dbe3d3841b9f8a29c3878d570228e9361c3e057362d7915777bbc849"))
    (1347000, uint256S("30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882")); //!< First v7 block
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1575145155,
    2971390,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
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

        genesis = CreateGenesisBlock(1533728621, 936030, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"));
        assert(genesis.hashMerkleRoot == uint256S("baf314231c2c162bb4bd33665c67320df47e74812821b1ad78faec22c9795553"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 50;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 600;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        consensus.nMintHeight = 1700001;
        consensus.nMintValue = 8100000 * COIN;
        consensus.sMintAddress = "KDkx9d9GRYenjfGtuLSEkCzECH5zXHJbGW";

        // spork keys
        consensus.strSporkPubKey = "03458aea0319e726ffaa7e97b278d0c1d9bacbd983e4a3cec6506e7988380da53c";
        consensus.strSporkPubKeyOld = "0443b94e8f01b62c33c61a8b53b8d7a4d522dc6183fe04639538470930a4bf7f7bfc2453adcdd0e7e8a1a7208c651054bbb0dcbb723b2013f424fb9badbca39462";
        consensus.nTime_EnforceNewSporkKey = 1638316800; // Wed Dec 01 2021 00:00:00 GMT+0000
        consensus.nTime_RejectOldSporkKey  = 1638403200; // Thu Dec 02 2021 00:00:00 GMT+0000

        // burn addresses
        consensus.mBurnAddresses = {
           { "KJXXXXXXXXXXXXXXXXXXXXXXXXXXW2cAfW", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 751;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 615800;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1700101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1100000;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1150000;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1700201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].nActivationHeight          = 1700301;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1700401;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight   = 1700501;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1a2340ca777d4c118bc4725e5326fa23e9072086728788ddb905ef9acde7d4a6");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("54136b30651f42501f26dab7859e8884860b5af7455a6707e0afdbd2957164f8");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("b479ca5af0c99323020e603fb0e96de1f1a0ea13c376e6c3a26ca62c06c3829a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("5dd0f62b4819eb575f886b02acd272e07de7d4ce8101688c15fe42d48200b2be");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("bd5886ac6694f69c9179f1ea48c458af0a8d56dd76c3347cb7742c5849b9f7ac");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("f025a2eece95a7570981a72ae9cfb9cb15a50314ed513083d9930131ca0d606b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("d05b24a598bdb2bd990fc6d65be4343081c6810f538111e73b0c071268d8b663");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("127bc8738c0785e04bf1088133bac09545b84591b7b20088d88a6732eee7fd77");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("c3069fbd79ba32ec7dd3ae8a1be59b2d2594e458ad5fa1fe5ac29ad0c2f64754");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0x95;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x52;
        nDefaultPort = 39697;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 179);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x50).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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
        vSeeds.push_back(CDNSSeedData("s1.birake.com", "seeder1.birake.com"));
        vSeeds.push_back(CDNSSeedData("s2.birake.com", "seeder2.birake.com"));
        vSeeds.push_back(CDNSSeedData("s3.birake.com", "seeder3.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet birake addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet birake script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet birake BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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

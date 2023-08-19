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
    const char* pszTimestamp = "Another 50% daily gain for Dogecoin confirms 'alt season' as Bitcoin slumps, 05/05/2021, COINTELEGRAPH";
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
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (11746, uint256S("e747f7fc32d7fe2805492b10771b7eff29858ce7e13f53e8e7e5778a29ebaff1"))
    (23493, uint256S("2bdec0dd834afbf4578b4a4bee2df9fae28e9419612867105c69918222fb8f35"))
    (35240, uint256S("76fdab34208b5e891199872d20a6a07f52eae1c19e7bf5d8b4feb9caeece0554"))
    (46987, uint256S("2704e564e85ceb14fbf1901712d76bc3dda71606315bdff87efb6d68abd17e09"))
    (58734, uint256S("165247f4df07a46743732a474d4f2046db479ce4bb711ed26ba33ca036248028"))
    (70481, uint256S("8123fdddb2e32315f0acfa3126e223722e3b318bdcbd9b9d74a4c82306d91cc8"))
    (82228, uint256S("0832c156e93b91e33f56a9d8f5f5add040e014ac656caee74deb0ce8920fb461"))
    (93975, uint256S("5b24d1792d6b65687bdc35846c58cc8ce72053423a96f98b5d9ba76b72a3b6b5"))
    (105722, uint256S("a8b5d2794a927d5effaf9c670e1e6f40cdba39e615acce5aa8a8f75b708fb7a9"))
    (117469, uint256S("bc14c9ddd6944093e374bf99c7b47293f8b8ddf8f6314b9032f4ab2de7390154"))
    (129216, uint256S("d42e1b06728a8a49e739a7aecb5ecf47ba563fe9d7c3d6b509b7218ce422d6eb"))
    (140963, uint256S("841be82164c5f74dc256ef598bb1d1a0d9bf9b3e7fac4364f8884799e5e693a1"))
    (152710, uint256S("858cfa562152e9d8f5e61cebf972d6dcb0b1c931e0efdfea69e90203aa9e6677"))
    (164457, uint256S("df2f6d69cd8bcdddd1978ac9bf3a31862c050e59c971827fed7a0f46e55d795c"))
    (176204, uint256S("6950431e0a7aa05c3951da1ed2453803a2f19036f2ddab1b38e39b258a5f2b4c"))
    (187951, uint256S("33698bf84fe5a8e8c51aa2d61e146730164d6df2ddbf439334f1c5696e63c9fb"))
    (199698, uint256S("3ddfdefe39d840e2404406e804199129119a4c4d15c22f9d61dfe02e9113f0d2"))
    (211445, uint256S("d8c28a68568c3b357ddece85b61c7a79bb3ac9b23f0ae95b21f6f64292a3bc08"))
    (223192, uint256S("cb5fda34ea86efd3b22eac3240e9f277c9d6614ae72d8031f659592048789a5a"))
    (234939, uint256S("09b1445f0666851d5eaa2503c9fb0fa86bfa18a1f28668e80282e802cbef4392"))
    (246686, uint256S("3fb13a38014678b2845270dfb0601441efa8c282e7e9c699d2d6cc4f883f10dc"))
    (258433, uint256S("b95fdbea2fa06317a287a9ad8a577b89e93ee99d1ffac3c226cb5d1ca5f04b6b"))
    (270180, uint256S("5d4a6be02f119b9c60eeea09a526fc92c1bd94f2cc7e7e77fceb3636f54f974d"))
    (281927, uint256S("629e424ba4533a5dcee20cbf225862a644921e14ae44c8c14b937a70660be64b"))
    (293674, uint256S("14bb31e2243b77f0f1b3d0dcf32a7faa518a8fb3c45c1b2c67204c20bb4bedb4"))
    (305421, uint256S("eff1f4563bcb9524254bb35df1fb1bc33b248159dd32ab2adf6126b7b515f476"))
    (317168, uint256S("252c42cead538cbbf5878e0310497fbf3d93576856157ef10e335e5c209d57e8"))
    (328915, uint256S("3d9ea2f5179184a53e6a3bbac72633ce51a22e664736793eed7fe7cd2288bf8b"))
    (340662, uint256S("bfdf020af33413365b954facf227b9468d8e3c2e6995b87b045451f0100c8391"))
    (352409, uint256S("ce040d29d1737344a6350ad39021be5b9df4ff09f5e6ca418b434e79bf30f8a8"))
    (364156, uint256S("5f61bdc9caeb143db09a566e1500077a54b0db79d06161469c1f11b6cd25863f"))
    (375903, uint256S("c36c954532f1fbdadb3d5b270498e508a034a44506ac189153949892a2841365"))
    (387650, uint256S("4fdd3dd0e2fa6285b1973b8d3cea440599d99a3c7a408cb692f67a50bf5ef507"))
    (399397, uint256S("afe7d046d564b010e577b06cdae9fac383e9f53ec8d1b8d994fb2677895bcfe6"))
    (411144, uint256S("30ef09276a417732df5499169fa375712b03968d692a4832ebe3c817b8f3aab6"))
    (422891, uint256S("01d5c3d96d60634133c807b17bde91b557750c62f88302f4f081975aa57d0edf"))
    (434638, uint256S("00831b02c62bcf540c51d864112e10f1ba16ed500fbc0ae037ab470ee02d854b"))
    (446385, uint256S("5d384a78a66a6952fb092074aec180ed4779c7bb8f11453afed708674d3a53da"))
    (458132, uint256S("10f0a1613c102227348682a2dd3912a58e5b394b977045948313fb274ef1aaaa"))
    (469879, uint256S("d47a92e18a2b0a743cb7011ac284d6927ef450cd8bab0e1e8154dca1ce8a1ada"))
    (481626, uint256S("7260dd25abb0022f0346dfc44b4482f0d4b301049899a76cf283102a477c14ba"))
    (493373, uint256S("ad8a8b52371d4802e609ed44b3d42c6e3f232fc2ed7ed9bb4ebc140d52116fdf"))
    (505120, uint256S("81058571c67ca8cbd1d9a26f6f9fcd795d022a5e88db460ad481ac96cc4cc9f3"))
    (516867, uint256S("41a949f74fc07b4171c039fcded2532c4437d4bfa98befe45912f714ac7cc049"))
    (528614, uint256S("47855861493895e824c376726a3d5395b6bbb5a7c5ae01b96d9c423f1cdf9223"))
    (540361, uint256S("967f7679c39c25167fdf6db6825c1c587ce46c20ac35cc89a78606abf9229ed0"))
    (552108, uint256S("102b8135d7a5bc18a5a66369f4fc946e411492030686d106dbc55e93c67b4bcf"))
    (563855, uint256S("0af3be8dd11c4bfad495fa3743560657eb7bd5ec53a3c6dfba93ba29d4af7cef"))
    (575602, uint256S("bdc54e11910244d57bb58b5d212b6ea124f8bff5d2440bdb12690aa7fc456e22"))
    (587349, uint256S("6be623174616cc7333dd2a3ee89dc2c6bbe429f46e97dbd759b7d6143f3231ab"))
    (599096, uint256S("7547c507d2e80a5374a0d542db5f4d342f36d79ae22829090787779d5e6f6d6d"))
    (610843, uint256S("c5f2dcfe3e5e5c120aef92a2d6a592d1a7860caf35e306f3442825b67bbcc355"))
    (622590, uint256S("538655e4eae420f3c159201303cb736d6a9cb583b4973a7d3630dcf92df24dd0"))
    (634337, uint256S("61cf0e79009828404c92b470337891c78e00a30a5f7aa5c6e0ce82cf00a65517"))
    (646084, uint256S("9b4a6f6e1627cca281d6a52e3d19187f6c2476a70d90c11ab0d2c7c4a0270783"))
    (657831, uint256S("09b4f6b8f537726aa3830af14124f74ccbcc3617a66eb0ebc1744a00c1acec6c"))
    (669578, uint256S("2775349abd7001913fe1ebe39eebad50825583ba7675ded33b86cae1d68f4839"))
    (681325, uint256S("25a8e56805ae8b2235315152881fc353edcb0b9589c7a9ee034305e34a48f35a"))
    (693072, uint256S("b98470c0090d8f6a07cbeb65ace6636adc7636d0ab6078810fe5bc1bd8ba9f9f"))
    (704819, uint256S("1cf400756aae8268a1c30b2c988dfeaa59592e95e2eb2a79d6277216a8b8c800"))
    (716566, uint256S("3cca15f1970c94ffe1a24021229bcedee680c22557f75f40840474c2deae1a0e"))
    (728313, uint256S("3162505b061cde55f34af56ad5beabcdf12227819701daca6a66e0079ef4ac4b"))
    (740060, uint256S("545efac74a9ea3625b0611c7c17940d111b5311b28e5355eec3d5f786c19b57c"))
    (751807, uint256S("032e85d43f1f07d36db11ba9b760fe2eb24031c776e44b091202f4b19b07d941"))
    (763554, uint256S("818b80065b2fb42c0a4d27f9d779dded4e7a65c544b2f1eb5bf70cfb0d044998"))
    (775301, uint256S("0ba89bed3d2fe435109c930d52aa2952f7371e4d968fa371484a5cc463915c96"))
    (787048, uint256S("b0aebee0d43c3532ef954559441b2dfbb1896366642ff05c5e3e990d719be08c"))
    (798795, uint256S("255f5b1aa08bf84fd11787405931777d90cf7c6ae920beb60e8568b3402fd604"))
    (810542, uint256S("b30481ba7be2411caebfb6570d2baf3bd34578d4f14112374ed0dbcfda0da78e"))
    (822289, uint256S("c06f19abdcfed1510ef18b08575f9ebcec35dc62972eb7f58533528808e1b708"))
    (834036, uint256S("dce9b4b87a0f843b491e47eeae82d652be9cb3ac842f4ff0e4bde223f7100114"))
    (845783, uint256S("2bba59090e891f4a04ec7000078b4a890ca2e5e5af8688011a849671834e74fa"))
    (857530, uint256S("8f922d6926d1da940e87d8e30e7262d3180885b1898d22919f85154bb59bf256"))
    (869277, uint256S("cf5ee6b4fa00a04b7f3f9243ec0eb6ba6cc5d48c502b845a9c873de490d43204"))
    (881024, uint256S("5d068ed081016307a15f73bdc4b5dcdd22c1391e38d991ff113571286db80c63"))
    (892771, uint256S("83a03fd4e035c4f4821457e6ecb3286cb192449969867488430bd710b50994f6"))
    (904518, uint256S("e01d4e735111712b5074c069c2bfaa58dc18eaa0ad97f32663c4dacdd832425d"))
    (916265, uint256S("77ffeeccdfd6bc42855f5906db1015c979a6cc30de35f5c14aec6f5382428f85"))
    (928012, uint256S("770eb598824e1248f2817001fc26d79c98ab03dc46dbc56a32846b847d6fa0b9"))
    (939759, uint256S("5bc57127adb566fe23cf1f06c4f1c369703510973be0619793b25f2ee50bae4e"))
    (951506, uint256S("71a357bb4dadaa925cb4c80515dd500bfe3cf4df69a9fa0cdcb521d91a308264"))
    (963253, uint256S("f3ede48d0c82a3b4dae765d118f5ea5d59377cadc6b22449be2c0be32747f032"))
    (975000, uint256S("8bcbcc609b7d6116c0899847d0bbaa4713c7cf578b6272d5adb823ee50128386"))
    (986747, uint256S("680cf10ad53832f0c57fdc0dd0d089bc9957d76dc7fc316e84591854fdf19875"))
    (998494, uint256S("65852a79e1c368570fc34ed7d765834aa571a4d36ce937f39aea1352f17059c7"))
    (1010241, uint256S("541943ad0d476ce4d262efdaac64e22806144a24dfb6e2cfd48fc84bd9cdb063"))
    (1021988, uint256S("6abe2bade08d5dc95b08e88c6eb83468045de30e06a0027276ea483a014897b6"))
    (1033735, uint256S("cff796632cd8d22205170dbf52c1339414ca327b5cc0f43a1e7a8c7053f4908b"))
    (1045482, uint256S("285c384ac38de0771e9ca133dd442fe1996fa032efd45f69effb33ceeda607f6"))
    (1057229, uint256S("1aae84a233f1f3dde5c4b3c7c397239a801dcb1db9308031b7f9c41ace0bb172"))
    (1068976, uint256S("c51ea20ade7a5c2d4abd99c15a1985037e86ef8619959e58a94b40751baad8eb"))
    (1080723, uint256S("5fe8f61dd86e1e84cf7689648bbb15dadcd6ba64e82a0200e1e541b84b6357b2"))
    (1092470, uint256S("7c56d89d6b6e50dc38e460be6a0ccd18c6eb84a4e661f5f306e98aea9383c31f"))
    (1104217, uint256S("c5e7902fe2d5dc276de9a4e48870fc53093437364202573803bc49a97185cdb4"))
    (1115964, uint256S("174e5a50efdb3f3cb0dfb98d55f2f19b1bef7dc8963952c06ea3b586468ae9da"))
    (1127711, uint256S("73ce0a9ecd161c302604025eecf24bfe5f5a3a23e2f71e28145bf1fe14cbfd63"))
    (1139458, uint256S("525e753bebe4cd2b72ea72cb7fd2ee4d9de376fe0ed0deaf792ccd8765e92d9e"))
    (1151205, uint256S("e8e44cadad90502cf1c01d1d2afa4ad4328924c925b1361dc144dd4c85a7eab6"))
    (1162952, uint256S("8a57e2c3fcc22e9d07c6147fec9b520b95685b31b28f14135872104a7f2ca685"))
    (1174699, uint256S("fff3534a8b83bca1619b0b11f8983b7bbb1407254e81a134145aa88a3668a9d4"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692449295, // * UNIX timestamp of last checkpoint block
    2482845,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2830        // * estimated number of transactions per day after checkpoint
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

        // uint32_t nGenesisTime = 1620224091; // Wed May 05 2021 14:14:51 GMT+0000
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

        genesis = CreateGenesisBlock(1620224091, 1077816, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"));
        assert(genesis.hashMerkleRoot == uint256S("0x5322195c37996cc752786ab95a76b328f2f8e03d3a9b5ffb465173613d4f97ab"));

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
        consensus.strSporkPubKey = "0273914d51723890516e319ecf24d71749da673c76606941290a0db4842389d693";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "bXXXXXXXXXXXXXXXXXXXXXXXXXXXZEYRfd", 0 },
           { "bXXXXXXXXBURNXXXXXXXXXXXXXXXZ7L2xb", 0 },
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 115000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("f4f586f27b0af2d9307015d45b7ff3ba72821ce54bf45110c0e034bda22a98cf");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c33e160f767be68f93c57e2c5af5d77e7d1c83bb82a345f6f2d4ea968a3f5d95");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("70ce131e9bc06cca48bcf8bd0f0f8efff93fe6e34ce9caaaad984c66616f7245");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("b13b0ac7e05c537438198d3e181c2e9796d0fbe9139e2ab3f33352fadd25dd35");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3e2e44e642974c48c9c2e1b6efd5fbb88b253decc6878a9ee64e7242abd5ed5c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("9ce29639f18a952d53bb4aaa2600279c1aef9bce52089b1c970da24be993ae3a");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 36552;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x49).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet beacon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet beacon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet beacon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_REGTEST__;

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
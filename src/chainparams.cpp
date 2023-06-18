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
    (24949, uint256S("39260a3fdda94fb944c3a936966b99ff944930f11ea6e0c62218fbde1514a12d"))
    (49899, uint256S("7ece25a13d771cd892c0def46a482f7b50c634ea81ccb2cec007bd24f9561f9e"))
    (74849, uint256S("8948352309e6fbd77842435c5eb0a8ccc37de25f3b891ee57b0411718f877f00"))
    (99799, uint256S("079e5856c7731ab654ce85eff4b9e08a370595dbc9267836cb0d57c0c3f92b14"))
    (124749, uint256S("c3410db446650d96aa8b83c369f6e522136ddeb4a2b4f4e453e09951cc70770f"))
    (149699, uint256S("a28236f1e54e2a9e10a6996134bc7ecde7dc0feaa8ce651ff3394f99d856b7dc"))
    (174649, uint256S("8ef228670deea6c7e019a783780911eca3d509366c5e84f88f5874b7b9563223"))
    (199599, uint256S("11125b5ec3a43f2fc17a9fe59f8579e9afe5f66fc5790088b718b31128b92b13"))
    (224549, uint256S("4be79b5eb949c27f3b9b049619690049fc60269e4a18d20f0732afe11831a1c9"))
    (249499, uint256S("002af53a18009c4df44de2eaf0fa524930a0053d1de70ea943b30df7eeeb1008"))
    (274449, uint256S("1155093ff15a821547f3b2be95b4916e2b36638feebe542c48a4e047e9c91e4c"))
    (299399, uint256S("24a68fc71859184e23fee3970cba1ff3afde52007d05e3f7d30921b5d8555f5d"))
    (324349, uint256S("61b13af1ce088b57e94846de26f75a17d623eeb7e03fcb4ad6d7a061b62a3b6d"))
    (349299, uint256S("8a7db48a46c46ed21137ccabe4e813abbb2373bae1a7220f7d746a7bd0298c27"))
    (374249, uint256S("5f9b0f4a3e2cbb392b6bec9cbcf1376c5bd5b85e3fae81da611970a94be50b9e"))
    (399199, uint256S("3961d7edb3fa2df7d013991d08ccf64104132fef1553ce2425a1e7f766f4bed6"))
    (424149, uint256S("6092900af698b202f7266ed9ba3960ad702112a70b2303c8ff0df7d23148fa82"))
    (449099, uint256S("aa69c1690be2e5c4a82e1ac72eb063718b31f5262d578a8279d362fcac4ba5cb"))
    (474049, uint256S("968a0032109221d66d07d1aca5f12e040f828e0f691f6c907692ce04f70eb2eb"))
    (498999, uint256S("0c84a8450252784aa3c7a5b34ed8e22ab5f41af189de8ff3b5d5ee0832b29bfe"))
    (523949, uint256S("955ec58c147aec348c65732addb7cf32bb668a8768e7bbda3486cc6e89519e84"))
    (548899, uint256S("10cbc938c54c7e13e70b8ec217b2638638c94ba37cee8c961dfa6fecf9e697b8"))
    (573849, uint256S("73f65885eef30f7ae9a8a917a71cf85c01b7bd59a80f2bfb55d5834d66c2896b"))
    (598799, uint256S("b453ea925c08be073c8bc4f0c7e3d3e13bf967a8f35eddf016b3387d50d51179"))
    (623749, uint256S("4833d6e63d094f68aec0c742b26ca66c0e75155c6983a9925753b1eb264336d3"))
    (648699, uint256S("2845f28ce15a9139e7f7d944ea047dc7c021aedf5d514a4d7a142ab8826ddcc3"))
    (673649, uint256S("c0cf7a0373ed47300e81eafc24ffe7b23f1200271b578341a0a51ee61322ffd6"))
    (698599, uint256S("84bb0bd6ac61389f10cb989e24a1bd2fdcc95c23af64cc15efd587ff130e8e1e"))
    (723549, uint256S("aa46fa92d65158d108867600e308232157f0d65b3e29e4511d8f8b1fa30e74d4"))
    (748499, uint256S("ade14f7fda5b74b4181581f003bcc3e7026b9cea88ded8af35b7e35f17ee6398"))
    (773449, uint256S("83e38d6631345edd9626843f5e7953d4c7cf640b97163a977f0e7d8329e5fbb5"))
    (798399, uint256S("d3b60fa40becb03b3e61870fdc3000263b59c23f54d615a12f4c379cf805038f"))
    (823349, uint256S("b9d88614eb98bdc2b01421bbb67716b9eb849d980f2365a94bdc6990dd5c8b4f"))
    (848299, uint256S("5a0e8bb16a9346c89b6c2e681d427b523bf28f7357cf277097dfeed53f69909f"))
    (873249, uint256S("63bcda1d7c5131d78c7961729e03e7db5266969e7d6e01291a37c1a5c7684494"))
    (898199, uint256S("7d21796d93f84866dc0a64b6fc392c210d7b246372d5c2d8e5fff7cad563bfd9"))
    (923149, uint256S("588659a0be54f1d6b3cf02c2f3a685747dba432e5a8632e851740c1b8323b5ef"))
    (948099, uint256S("8d00640686715dfe629f525b762e81b096e68ef6f6b7a0d399997bc878b42f00"))
    (973049, uint256S("9c0df8602cf54796001bfc7a19cca24271cba3c849e5fe26c74c9dbf7c11a4be"))
    (997999, uint256S("6d6d5401ed2393813ce058e5a894cd9f659de4d59b424daa5cdb5a0ed988f257"))
    (1022949, uint256S("06944102f2c6b7f311f6817911c0d0238c6bfd2e0e4852204654186657d79f26"))
    (1047899, uint256S("dfd80900d72d2e5f7f54ff62c3132f86cd75d16fcef9cbb28b7290547e49bde9"))
    (1072849, uint256S("7dd1b2f6be2b3d2748be814ed26f55f4e9e1914c009b5cd75be1b5dd3dc5f0ee"))
    (1097799, uint256S("b1ef3490270855fcd12a1ca3697997d19fbab62b7c5263cdcb4b59410b78906d"))
    (1122749, uint256S("1c74783d8bb4f8341a88b2c253fc83eff36155391da6b5ad5d3a1c37250dcc75"))
    (1147699, uint256S("1f4875158f70eaa7d81de3e0f3f8400ba30fee47175f9d2825cb44c5d6126fbc"))
    (1172649, uint256S("d15ef8641669b81bf838e5a32d58cff34936cda7a8db8a7e2e677e2df47555e6"))
    (1197599, uint256S("ff2fd65ac7e5ddf9086f84046a5aabb8a179196f81c1bef1d9c1c4f1ef63c741"))
    (1222549, uint256S("48671c0b01d4f928d057a471feaaf07128df9cabb56528c0bdb1ec2603c240d2"))
    (1247499, uint256S("82a699ba84b8bbf585295b4ae36a7b71eb89fcf3f50efaf643a7476163b5da38"))
    (1272449, uint256S("822541086db1716e069f1c5a7c4c839ad1fe6eab12f02d497acbf61ffbb8dbe8"))
    (1297399, uint256S("5e79ce7fb9e83a700bf7ae70223e1bcea82f0f9b769d4d20045ce0bee24d5744"))
    (1322349, uint256S("2d7cf74accce3b83d47d258d43969d53c7870beb7adf2593f979255ce50bab22"))
    (1347299, uint256S("a9377d2b42b0d3a41a153f9d0c632c8eaee2bbdb3e1056ee2c9a680c6e8078be"))
    (1372249, uint256S("a2ccd645d7a1d1457d526ff3758a9f7ada6060da79c82930d11648609a9b7c1e"))
    (1397199, uint256S("f84333c45f8001c741e6613b72f1edcf22c1c59d513fd034827aa6b139543ccb"))
    (1422149, uint256S("280fab13ec86256c6138a4c6240ca4ead4d66affd4fd50e7c85c5a867a7fb236"))
    (1447099, uint256S("37967f852c248d97bad22d40f0650c1735099c193511cb4a07d429b8363d6fe7"))
    (1472049, uint256S("555229e5420bdf5697340f747b84d234ccbdcb8b1a777705a850d49a5323fe7f"))
    (1496999, uint256S("221e32f9f46a93f76d181fa8cd77f139f9d83a9358ec89fba7e2eed3e3f9b750"))
    (1521949, uint256S("2d41935303d1943c8b62c30b6474e93e4e0027c9d840022993ad84bb19719145"))
    (1546899, uint256S("8b94331e753bd3aabdd8b3bfa818018ea375b7a31379d83e007433d13f1dbb6a"))
    (1571849, uint256S("e70b30542c8b621a33e176c8c1145263b931cabaafb30e3256d4e3aea927b36d"))
    (1596799, uint256S("7feda4da67b6647e7004009bf4141e879ea624e90bc6d15fc790e6469d369b9f"))
    (1621749, uint256S("8c74f2cd1b456357962a9dbecb073c2d7859a529ac2a10000119886720ae7f72"))
    (1646699, uint256S("45ebc582fbc4aa45a060fb2dab6e9b972e53640769d8a43981debc9aa86ace5b"))
    (1671649, uint256S("65bc49b7010bfed7c8e19d7a5abbb72b0516e24d2fc9aa871c918c14f5c912ef"))
    (1696599, uint256S("16ac34d5c8f87ed3d409bb6b3c0158bb7ec35fe85ad2602179747dbe04dea980"))
    (1721549, uint256S("66a80a319cc73f177bbe134a79264408ca7968dcc0c16acafe58533b098f05a1"))
    (1746499, uint256S("020629760bac9dce175ce275f1e84cea61c7dee5a6c65f9169e748ff654dc6d2"))
    (1771449, uint256S("0ab168b4cd8937a0bd68a563ed7b0d78e1b044be11decd8a0123cc7284ffd464"))
    (1796399, uint256S("e64b488e2327fad37738738856dffdf3bafd23f3d1583723e991be5cc8655873"))
    (1821349, uint256S("832883c86e85ab2f45ea82294fc47793fc9a900151058c7dc119482463e338ae"))
    (1846299, uint256S("8d296e1d2ce28002e3e683bf3681ec509a5ff583c812b66e506df44cab12d78e"))
    (1871249, uint256S("7f2938b3a5311a75c6313db68c755800c1e02e80719a327511cf88f199415b69"))
    (1896199, uint256S("6ddfa1ada5f62c9315e4e63ba39b518f570a6f7ec6ad39441adfb685f914731f"))
    (1921149, uint256S("5882463d39d718e7ee0287d3779f3bab4f63589ce06296323216e0a9bdc73bb1"))
    (1946099, uint256S("58964c8261cb71b415a245a59f2ac9d56be82018759f5b490cdf2350ca099b3c"))
    (1971049, uint256S("70489e4fc4adf4e3529af8a0bc5751782f60994a8eb5cd141383418c5b946807"))
    (1995999, uint256S("1d9ec7f4c798304cd5ce2736f805ae3c01504fc0f810ca51a788bbd560d5e180"))
    (2020949, uint256S("5a3ce94d6ca5265b4b32d1222a047ac5efe91eed96cf32ad523cb125c287d9d8"))
    (2045899, uint256S("115f4f6f7b9b4c1ed4162c08cb86886a606118422039e21d79f0c44fc7c9f2a0"))
    (2070849, uint256S("968fe9a4fb1cefb39388fb2754398635880c4e86146fb3e902db0bf975e050a5"))
    (2095799, uint256S("3eca714ee5e018c24ca079f84530ffcaaa15781267d21747a5bd0ee48cf7e790"))
    (2120749, uint256S("20ba402d5a47aa72dd98410e41074eedb1cea9784f87f9d25adc74d278fa0745"))
    (2145699, uint256S("750ef68cd2489fbe738eb784f766867b61818ac2162f13b46e241def573a896a"))
    (2170649, uint256S("46b53e4906c359432a63dcb2e20e680e3a418f54b8290a9dc9a4e6c191876fa8"))
    (2195599, uint256S("336499271cead301a4cb7cd086006505def7a7512aa53617abd5c143bceb978c"))
    (2220549, uint256S("0529278a4e0cbe9d3fef89f094db56cf88f5d3dae2cb3c8ccad780b9c6ce8578"))
    (2245499, uint256S("9df0d881277ecc29f37c280be4e733cd6bc95d8ce2b205d5622c73e7b55aa307"))
    (2270449, uint256S("c420ed14122da872235eb42b6e023b7ee25b217f68de7c0a561dd7c703d71a1e"))
    (2295399, uint256S("7923b7d3a2dab40f4e615a90d1c187502497ed2ff46b933d8b1ae11499c19418"))
    (2320349, uint256S("bc649bc1888143a60b3068758c888fb65acb7daa3cbffb13ceb142049e59103a"))
    (2345299, uint256S("4722d8c095047bb061a915b52403f1824a677d513cbcafe3e5c35adc57cee4a7"))
    (2370249, uint256S("1e2edbcc4b6d6dbf9fa3b131fd1e6842ad4510e2d5363c7043f41454d567981b"))
    (2395199, uint256S("71ec51472e38f9924d764bcbd435192bb0e24efcc6db4b2352dec2009a5cafa9"))
    (2420149, uint256S("600e5db3412ea04ff92d91cd4bec8147ef5f50d1b5d40830c0b66fb9968e0150"))
    (2445099, uint256S("2b77fea457a2edaa269121e5259a4fc333a8532b5de356b308d2d53a44fdb2c0"))
    (2470049, uint256S("30a9ba5ed409698daeb3c1a492879005c8719d57513bab8a9a101602694027f3"))
    (2494999, uint256S("9ac150cc1cd296d9b7f98b75e034c69735509efe1b0b69671f1a311f48a932d0"))
 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1687047375, // * UNIX timestamp of last checkpoint block
    6325405,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2818        // * estimated number of transactions per day after checkpoint
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

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
    (24882, uint256S("61215442f0720eb79ed5f21c2360230e5dcde9b5e6982b03c192ad6eb1bcc5da"))
    (49765, uint256S("95c439538d8347278256927d2f573cf3b013056cde386562dbf888c2f87cf779"))
    (74648, uint256S("23b3ac5d554c3a791f5e9648905aaa3e6d845cf92ad750a8f0e6b519bec0fe98"))
    (99531, uint256S("a7496853377c31a35a926353bd0a5db1fb622cdad3bdc6fe062553fcbc3f0096"))
    (124414, uint256S("299848eb2beb5fcd6fef29006d26d737858c5f956df6950b2a956e175a24497b"))
    (149297, uint256S("92451235a09e2f6cca62ddd58dec9e9f9fb766f087cd1cc8dbe185dba26c8513"))
    (174180, uint256S("067ed2af16b8fbb585b6d18107904a9b09755c6eff12f5bc7ab8de6d1358cacc"))
    (199063, uint256S("ec4df288536ab1ec8f0751dae5e379abf49c8f5b2dece4c9347941bf26b366f1"))
    (223946, uint256S("fc11ad667d14b52b7aecb4743653bcca4f1b6f5d32e6483f6a0fe25d8adbc40c"))
    (248829, uint256S("f341c8035886b3c672650a59af8737021efe8533fc85552dd380886640c4c250"))
    (273712, uint256S("86e7d60c2db87df0cedbb7d63558a09cedfe4b36722674131d92828f03dd01ed"))
    (298595, uint256S("a8016cc7913301b5b4ab8e10cad6db275579e4890e8e56c815e3eeec0b0683cb"))
    (323478, uint256S("0f68e7d6b31dd628add4306f8b28b84558a3dd5bf478292a43fc164892d05b6e"))
    (348361, uint256S("72343aa00a7dc009b7d789394b5cba4b9731701e798dd1debae66314432e2282"))
    (373244, uint256S("03ac7b4edb87f09ea0e24db7aac43d66e087ec6faff0ef46929c04e9dd69b4a9"))
    (398127, uint256S("1f4529c3c6dd1ef6c0d4bfb1f1440d9f93d82b1f797e1a51bdbb91fee680c0b4"))
    (423010, uint256S("a27f42dbe7b8317d0bb39ea63539caf7683028c7d489141ea98558e50048c07b"))
    (447893, uint256S("53887360dbdaf9b171c1e5349b7046159ea36761824587508d41fc88347e56f7"))
    (472776, uint256S("6351d8ef1ebf72744ff8e5515f38581e02a4f931003b3c80c9638bb899db63f8"))
    (497659, uint256S("8c1cc089016f62bffd935ad753f692f5e85f1f2650f2b75dcce0742c7c8639f9"))
    (522542, uint256S("77878b246544e098875e229ad121dea49ba03a7586ebfb0a9d6fd24ad1b7357f"))
    (547425, uint256S("b8eeaa71e5458ed617534d423515a0e75a41fbf420a08c703ba2a3c8f04839e9"))
    (572308, uint256S("ba59ee5da9115502dc55d258714a8213ce7b37fbac4ce1e22acc5cc117b2441d"))
    (597191, uint256S("bb8a2da858d218e3f919b776a0d560ce09c23dfa92cddbce904ce4b1631c082c"))
    (622074, uint256S("e1051b8ba77a5d94441f2eacd62af8664d27aba74e9257612af187fccb159984"))
    (646957, uint256S("4b9ecb4f32e9d8e1776a71392e4789ade00f855ea60fe8960df93d2cf1de6713"))
    (671840, uint256S("dd8aa489e28a8983a8c712eff9734ae0d4871292f932373d1d058dbd7f545f76"))
    (696723, uint256S("ec014c9fd658d5427a40ee4d7101854972acb2da7c91bb3f169eec5aea71a281"))
    (721606, uint256S("8f0f0ba82780a70830d54c43861ec9456474e40120b75baf54d5b1c428f371fb"))
    (746489, uint256S("bf616037bb78d4f812171457d7126d1e3be0fba1eb897c80cb13bfe7e8c007e2"))
    (771372, uint256S("8ea1f62b7c8bfb97b07b5fea3404ea024b1590cc5f4ccf9be4dc70c8b203d4a0"))
    (796255, uint256S("4b1b6c0d9ea49f0feebe7d95e2873da871368cdedd0b1cd929f0cf3647805ce8"))
    (821138, uint256S("0cc25b5004765af5855a6d526f906a955d041c152484937b95aab6ae18cdf926"))
    (846021, uint256S("1df49da4b5889585395c77cee0bcfb9692e659e6fb1a2e68bc764b978da3d4a5"))
    (870904, uint256S("c88d3513cd0da9f286b2ae50787b592989191c8c681c27889d8d1c26499bed66"))
    (895787, uint256S("c4e4d8c3f3ea6cab63aae4df2eb15f17195cab62d6d24ba76896bab4f17ba16c"))
    (920670, uint256S("7c109e938fded96816c5c9f774806f720898b9492f4672ba0e7568f534e0bd12"))
    (945553, uint256S("30f2b4375af4a7dbf3452252ebe4f2fb49b308312ed3252b4ec1de7da5a0920f"))
    (970436, uint256S("e4a1d04c0f0769ea18b26743207f83424b35b5cea7b14217224257b1d4356de3"))
    (995319, uint256S("4f5a181d67c7559ac62bf2dd515fa60edc9ddc5b0a6e6d17662bb136ce4be87a"))
    (1020202, uint256S("e7cc7799d46200c9556a236dc5eef6232228f6d167cf5c4d3f3d1bb1cc64bcfe"))
    (1045085, uint256S("d72465e93bc8cdaebcf462f18d3a1a4ac6ffb9a60bf037ed0180ee388647c906"))
    (1069968, uint256S("d3c5b36547bb2757865d04866e29470fc3b9061c74bc477cd6f7d0eb1ca8c100"))
    (1094851, uint256S("ced97db3bc3c9ed2e07a9a30bc9e0b130a539f9ca544ed570e5293eb62c85074"))
    (1119734, uint256S("397433b6326ba3ac013b10d3d64e8fb90408db554136f031eae3b78e27444731"))
    (1144617, uint256S("3b65cbd9c273490c469a192efe935e9836f34e96048de8afa1e98dd02d8262f0"))
    (1169500, uint256S("9f527238c454398d345264d2d7c78159df65345026c6ab7938d0daba414a5343"))
    (1194383, uint256S("7492d57bf68b0fbb4a4198f0af890b85a6beb092e2cb9700607c8a8367de8eea"))
    (1219266, uint256S("2494dccca87970b1816df41cfdc1069f523ae8c8d579cf02dde15780c7db1b5e"))
    (1244149, uint256S("f639372c405623aa84c641c9099cfaf1db18f7a25ae73b9c360d356f0c7c51d8"))
    (1269032, uint256S("956c84a051944a356bc3665a66cbb4047077a1e185eda3b3b23a7a58f0919fda"))
    (1293915, uint256S("de5f48f96e11d11129dbcce797f78de34aabd3b18aee79b9b2462ed9d14c5e3a"))
    (1318798, uint256S("236b4b6650f5b17471872d9a350c257248f56133645ae73d01dc16dfb0155e61"))
    (1343681, uint256S("45ea7d8e04df6bbca842924d5c5e402dae8bab60fe42cce8f6361252e9e765f5"))
    (1368564, uint256S("f8bd27a1baaf7c61b0146b4c42d39cd36f6e03069144ae05e7f2caa381910d1c"))
    (1393447, uint256S("7a2dd339b2f6495ad3190ffdb96a7c3608198ece73e304c4e78e55b64e4603b2"))
    (1418330, uint256S("d630a10d00c320d9830c55cb0e2c3f820f12fb75235b7da299f784effcebb55f"))
    (1443213, uint256S("f6c43780dbc93e1616b123d748bb0dd7b5b3a8f0b8e7545bd815d89bb9084724"))
    (1468096, uint256S("5418b96783ac90b53cab1bdf149b0d386df4613c296b37bb05f787124e7ccb3d"))
    (1492979, uint256S("69451041e6e8e64a53fd7233685854d9ac982fa65b42f6d9a032cac382e4c9c2"))
    (1517862, uint256S("eb4c33221df4332121588013435b15ed816189a8f87485c5ca0af29d1abf38d6"))
    (1542745, uint256S("f417006853c8c4d154a33e46745fb47a5183857d52fc7ace5ff73c514d6813fc"))
    (1567628, uint256S("3d97e068e3312fe7a2586fbc2ea1cf10afc59e91b27007e46960acddb1d388a8"))
    (1592511, uint256S("a8ed6f4726b51f793035a465ccc3d997a26052c3141c5e2c9ff4504395c32039"))
    (1617394, uint256S("ced9fc0ba15b108ea1dda6dccbdc4ea3f46a7d80df81df52d7f1dfefc696e989"))
    (1642277, uint256S("518b8ea321cc7e006ba81c13d2508984b9d4051e4161728885db1fe04c0db330"))
    (1667160, uint256S("f596e8bf9df4dc80dd669cd1766db2c05d3361fa407b40429386fb68f5cf34b1"))
    (1692043, uint256S("92d09ec8e19cc88d48c740516a0fc0199fd879adca98ba0f7346ebfb05acde6f"))
    (1716926, uint256S("f9dc9ce12c40f229ad8b62caad94c8e8f52f3ecba27442fe61fb6b00de7f8d72"))
    (1741809, uint256S("9499d6336856273c9acc97fc4b6d1b64ed24df2fc4d09bd6ebfcef3547cf9a39"))
    (1766692, uint256S("c638dfad21cf788fac7ffbb8d5468c0e4fe31197e2c4de9ecad9d6191468ffa0"))
    (1791575, uint256S("e1b801aa6442b0f4eaa52d9af04f7b491252417f4773ac7e65c85a510e0d7102"))
    (1816458, uint256S("6785ef4c1ab842e1b1c0d0023a16917b4408d99d3416ed6df66526ec832c716d"))
    (1841341, uint256S("d9d5c44845ce50bf381aff2e85f0d1610458788efef0114593606699d722758e"))
    (1866224, uint256S("23bb2cffa9ff54ce5eb853ef3bf691906bce699941c4341834db30b9d466bbb9"))
    (1891107, uint256S("4694447ba08b001ddf3f97571d50254783ba92a947f9746b279d227d8e571e76"))
    (1915990, uint256S("6ccabc40c513cf10c06f3376946b213258ac57ecc163c3901dc6276399ec0fc2"))
    (1940873, uint256S("b0faaa4c0c39e017df91038205f87b21eb6f1b3c66a9bf8d57dbf3f6870fb6e2"))
    (1965756, uint256S("ca83403f5dddbc87eb8ea95025c1a09228864ef9f4c55a010b29122447e97072"))
    (1990639, uint256S("7fcd362260bf2a563fe8ddc516bb55ca24bf62f7c976039d2c96800a140cafe2"))
    (2015522, uint256S("ef32201dc917c21041316b0ae5163f1265294ceb91152463caac541af79ec6db"))
    (2040405, uint256S("51df1a884e26673ee008b9e21f4cc1c6ce3acb20fd8400b4a70a1535957bc2e9"))
    (2065288, uint256S("23ece291174b75fe520ee7b7fef3d85b042c8bee7bdb2dd4845395b3ad2f83de"))
    (2090171, uint256S("fb994705eca24e41224001f7f3aa3e0d02330cd308516e0ed83098e5167871b1"))
    (2115054, uint256S("32b8626743bb23a3559d0ebec94f5ecb45e181c04f53093c98351f98d016bda5"))
    (2139937, uint256S("dab8bc013303c5719276c4ee300a2d2b577ab69719edbfc7dfc42b7c8db25028"))
    (2164820, uint256S("ecc257aaafc8c7c4ea8248088770db6b346519e515789ed9f0001b4c6bcb6b1c"))
    (2189703, uint256S("e9f14371ccf4e261aa66340b7ba01362d2b36bd22621aa00922866543ec84bcf"))
    (2214586, uint256S("17eaa0330f8fc4f4bb48d2185591d5b738522f8a36195f620a7325bc45d97b26"))
    (2239469, uint256S("044856a8819e9c01528f01c47da0b0e1366fff85255c4155953d2f47f64e7a97"))
    (2264352, uint256S("72f994845c8a3aae371c36c8eb39f3c572942b49532550c274bd08ab6889cc9d"))
    (2289235, uint256S("3dfbfe253060306cfa763d8ef4e70cf8809042c710d697baf2b8f19f1faaf906"))
    (2314118, uint256S("a7fb145c83d275a81dde4448b579c1e1025dfd43fe62353d34fbae608ca99706"))
    (2339001, uint256S("b7497e6c541eb49a50ec5825d78733296c61365f4cc5655c0a480fd847d18cb7"))
    (2363884, uint256S("d9ab5a860580fd45c7dbdc1717d79100e1169fe34c4fc3fa9cedd00374c227a4"))
    (2388767, uint256S("1c1fbe0664fe8f327945fdf403939c59d832094a8d5b4f8791493e8a6d69f42f"))
    (2413650, uint256S("201ca7c8bd8e85a6cf0b66e2a9f2da4d797bfa551773ebaf64d85a84d42d29c4"))
    (2438533, uint256S("8514a64e448e0838a2028ad43ed50b77485f8e059f43dc8e43b6eeab26260b70"))
    (2463416, uint256S("6c701b3c38564ce670eb056fc619fc0277eb4e3085fb1a26eba58d25f1be5372"))
    (2488299, uint256S("30afd1a54a3567777cc72351a30cb6ea3f3208435db2cf950be400ce96ba789f"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707814170, // * UNIX timestamp of last checkpoint block
    14786459,   // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 60;
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

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 905001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 905101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V1].nActivationHeight     = 574500;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 905201;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 905301;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 905401;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 905501;
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].nActivationHeight          = 910001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1200001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("ef544e9c4181e103bdcaae6153aa90495f1f830a91368364c4b8b97a3782e579");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("c36a49839903e01bc2d6c44f20516fd5f3d816cf2d16cd30c488986668bdf269");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("2033cd79c94ef01e04c0b886944350af7af4ee2dcdf2bb2a8f417ea48dabecf3");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V1].hashActivationBlock     = uint256S("f0cf896ad6fd9bfc188853d5354ddec23972f9854023f92a7e3ba0886f3ef4d9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("502226d6ce3e3fd036452b59b0045ff478658b00a42fbf3434630cfe775d84ae");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("9002e71bbefb2a10d5208b7e8e0a2182d2b13a55585c595752454c65dc9cda02");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5b37c32d7c08cf98df958953dd4c32820f0609a4f4bed452fcb0811bec60500e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("f6326f790d1c0d01843913b301b56dc0d984e9d76e0949669cbeebda37336cf7");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("96dc6197a2d0cc2b9dfe5487b35f0d5b051d1dd958de19e00043897223c08ea4");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("92330b37f9e362b521a77ebe3fb4a1dfedb8d055770bfa601eb0420c4d81b3f3");

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
        base58Prefixes[SECRET_KEY_BIR]      = std::vector<unsigned char>(1, 179);
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
        consensus.nCoinbaseMaturity = 100;

        consensus.nCoinbaseMaturity = 15;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.nTime_EnforceNewSporkKey = 1556165178;    //!> August 26, 2019 11:00:00 PM GMT
        consensus.nTime_RejectOldSporkKey = 1556165178;     //!> September 26, 2019 11:00:00 PM GMT

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 878611;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 878631;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
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

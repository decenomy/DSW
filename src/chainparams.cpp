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
    (25832, uint256S("cca1fe894e8a26dd5d1083ef24f8ca77233f6fea416d5efe76b13df42aebd35a"))
    (51665, uint256S("97199bb8afb8b5ebca1c809a45fdad9e171c151c1f19ae7ce1965f3387febb69"))
    (77498, uint256S("afb4a8f5b6b11ea64f8cb47fa1bf28950a9d0c32a9516f1fbc86698bdd1df37c"))
    (103331, uint256S("2e835839613b250dca96aff70b58f8c90f351e9d569ebc45d57a6c8bb1b99e20"))
    (129164, uint256S("32c1406eec6d2bd950a63f54e8dc09da831acb705e83f8d47836cf23ecf110dd"))
    (154997, uint256S("f4eb304aa7aad9233e818662906fcff24c4f85f9b376fcfdbe4234e62c4bcd8d"))
    (180830, uint256S("a335bc5c5b0cebbb34c84ff0b108d7270b091afbfca301ed1ba4f8e8fcec4ac5"))
    (206663, uint256S("8a658b2703b1027abdc3a53ac59408ee22a99505346dde3c9c757f20f226badc"))
    (232496, uint256S("3fda65332609d4f19e336d34ec4e1d8710ee2aaf20f30454a00fb3a4c810e50a"))
    (258329, uint256S("ee34bc0223754fad6ca6d7ce5d11956574be1f23711cb1ea5630253b280bd8d6"))
    (284162, uint256S("3ef96f865f5b2edb3ce4eab657af42234b1ecaa45c456d4f648585b4561ca194"))
    (309995, uint256S("baad90bccac9583d36a7963b67a44f50106f287ed0e10cc5b8db318156028f9b"))
    (335828, uint256S("2403ffb3c47f58243cf4320ace737442541b3c2694f158baa091c5eecc820aee"))
    (361661, uint256S("e4d3df7229591b5bde55c26021bb3b4a232bd0d2b69d0cdacabc34644be448cd"))
    (387494, uint256S("8354c11ed6e677fe50d13ef380d646a092ea53bcafccb28a2eb82848558678cf"))
    (413327, uint256S("58ebbb78018ae3638308f6b27ce1513822044a9633b3f675d07b1b5d130ff2c0"))
    (439160, uint256S("5cf69b7c38e3b79baef2591310e21cd16fc355ed32dc053b48a732d63cb93dee"))
    (464993, uint256S("081f5b67e61a02256b0989fffcb6bb2388b9799a674b7bfd8103e1e30193560b"))
    (490826, uint256S("ef2c020681eb89b52e27299f40d72424bd88b342cabe4d267f63ba5981461435"))
    (516659, uint256S("7dc22724024efb345df0e30605a969fa843e8b3ee572eb0f5b13441968b08af2"))
    (542492, uint256S("c7df9f1f60a9d128c0ded34967d6905d5c6a05fc2d7d24b5aa2119a808c55571"))
    (568325, uint256S("c6655a6dbbc569d7f4733faee2ebecd5b22d9a2133ab1bf43730647e61b290a1"))
    (594158, uint256S("3dea99f389237bd6371fb2e82fb6163d8bd74f3af673b8572b690159c5e814a4"))
    (619991, uint256S("6c41a641f10c65b7f3e27b6c3e7bccb47fdf1926982ea2a79a716c72d1d6c883"))
    (645824, uint256S("6403112f344302ff0a227a3a51149999135ff05632f38497b8b17f7675104ce4"))
    (671657, uint256S("c586b84d2fce70b8c442b9dfc1f459693cd8ac0d52559a23e754e92fb83388e2"))
    (697490, uint256S("7da7b92fb746746caf12bda889bc55fa1451822a75f870870d05bb307c07e32a"))
    (723323, uint256S("3a908f487a2132658ce6060fe20aef98f376e1d58399e13bb871ffa768ae7322"))
    (749156, uint256S("ec390a6d4a7c81f5c84594d0c193e6522344ca72a188acebe0e9837b78081a82"))
    (774989, uint256S("ee32fae21b07c70a5631f6772f53297f425962034cd1a1864c0395c1ba70e59f"))
    (800822, uint256S("ad8ac8d4bf8fb0c2c92de02acc950e306f38ac58ffdc509f331e2548792442fc"))
    (826655, uint256S("e2c7f5f661c420dc92d3eb33f58bd417d6296134a02b71e6eefa23ad8a192388"))
    (852488, uint256S("f0f677cb0ef2763986803cef38b6022268b3d0a4f6b6c3586950a390704deab9"))
    (878321, uint256S("68628be3baa1d10bda4753cb05e5b59f0968dd415ab21b8017c5e5d5cc31d66f"))
    (904154, uint256S("2ef48468c0ecbe3f2fcbb63e112b030d34124448ae68a0d6f5af6b9c15d27645"))
    (929987, uint256S("f03aff6bfd11bdef056489c3ca3126cb1adb4bd8bf9f3fb1cbc9a45994b675ff"))
    (955820, uint256S("1275576eda1cd64dea8f7cbbc02cfdfc061feea0f543005351274c991129f372"))
    (981653, uint256S("0fcfef19fa8a9da59bd6f1786b5ab49b22ffa8cfa1a23e99a7ac304fdc3156da"))
    (1007486, uint256S("6b0ff47350199d48098906f3d5366910bf680a32cdbb9856593c5c6d649c2941"))
    (1033319, uint256S("d4f2981316edaf714443d2489cd4d0a03e0cd44daddd95c59564b5b4107df435"))
    (1059152, uint256S("8335a923db0dd302bb807b90938ae2d75df46f7e09e1196ac5fb9437ec013962"))
    (1084985, uint256S("497f1eb88ac629eb723fa08d54fb85fbeda1ae96d93d995c45fc9fe7fb64caac"))
    (1110818, uint256S("d27d641ff49a2833d46b4318b21dd6b563ab5d3b76c0da7f5cf87330f0d32516"))
    (1136651, uint256S("9e1c394bb0750d1b9b7d5ac0ed6d72c4cf7e4e72aa7cd26026a0413cf19e7d8a"))
    (1162484, uint256S("5704c9a6a8a552cf19e66e493ba9343bd0d8410b13052e065c4ab3dec28d6321"))
    (1188317, uint256S("4e94cc52e2895501cb2a60da02d411f42a2ecb507ab9c76a169593cb4951d7ae"))
    (1214150, uint256S("c2f4acc085f2de5b80f706c0160d7ec364df5386fc281fc5d5499135ee0bcc8b"))
    (1239983, uint256S("fb4ab078ffbfd4f9ffc3ff1aee43eb2dcf682a9053bdabef7116f3a5d94ddd80"))
    (1265816, uint256S("268f643a8b13914654b4dba56882a0f60762ba0d06b0f65535fd20f67cebfdbb"))
    (1291649, uint256S("bb33f5bebbc293b986ccca1a73bd2ee4b5b023eec52597d9065e232fcc7e2d07"))
    (1317482, uint256S("55f6a4cfe61174a927252a54df65657674f7374e50737e8fe1619b87b1f9ba35"))
    (1343315, uint256S("a12c772f7bcdae3d4b1aa1239f60bdef251dd1633e57d43cd511ef7e133c8bea"))
    (1369148, uint256S("2f9c4642511781b9c182f6d6d4c9b2dd151e89516438de07efba8efc898b14ae"))
    (1394981, uint256S("433872b083d64cd023b8c5130d2a5cf16b43deb34220a31518369a33f5136749"))
    (1420814, uint256S("b6dcc0f7837d56dc52f7f0f2f392ef57d742b3b6be93edc9166abead337ac544"))
    (1446647, uint256S("f9ef12c48a089a2fb66703983fdcbc43f9f09a6379528b1d9db2868b7c656cc1"))
    (1472480, uint256S("f23a28af4675e5fe3c8fa5b5117b15bdbeb345c6c0b41a94eb57a8f75d87e3b7"))
    (1498313, uint256S("0d473b6e509d0e230a0df6fb73a430d33681e61d53a7184bdadfe1f0265cc057"))
    (1524146, uint256S("d1590ad2a5f41d37dd4fa4a99f0b5d751b9289d959f830c9c1a06b43a047ce4a"))
    (1549979, uint256S("5a7eb30c8c3b6421c2b04000fecbb42ae2d2879b3f95fb2e279657c96ec0b0f4"))
    (1575812, uint256S("234b6f7e853a2479ef6a2300fd1c582c7778e6ff4e7e325daed468a064f4f8dc"))
    (1601645, uint256S("46e4b23a671f302aecc0469ddc8c2719a3a693984603da3e3e2b5e9dec38e110"))
    (1627478, uint256S("77fd23ecf895efb352cd603cde33711a84f47db70c415c39817eba325a5b040f"))
    (1653311, uint256S("7f6669e88011a2c6bc868dbce94ddd1e54d647b815d36d18c2248a083c1e07b2"))
    (1679144, uint256S("17f8f52a90ae0f8ee99e58a7047d2071bcfc153ecd875826aa711b27d08c1db8"))
    (1704977, uint256S("b526641397cbf4199a13015bc5d0bc32bf6cf2da9f4394e53566ce76797aed3e"))
    (1730810, uint256S("b5bcb9dffd85748be91122bea5053982c0067ee4a077d3dc490a3cccf79d8fa9"))
    (1756643, uint256S("4a6bfe2fcfac71c12ee30e7ec82e0bffb84ec4a97a9021addc801f9c6803fed9"))
    (1782476, uint256S("9d831d94f025d549856b377ce76c4ed47d17684b7f615e9348941833d169e821"))
    (1808309, uint256S("59272268be48d50f8e85c309c552a5dbbff93445367a8d0977e5f3629cc2c92a"))
    (1834142, uint256S("1c39145203065694586d7b07e67615b752f64ddc3e431137152481f1f034d07c"))
    (1859975, uint256S("89a23286286e732bd447dff1f69a8dc400410a8993e1ca3ca51ce37bc5a4e1ab"))
    (1885808, uint256S("794a7bc2ae983e86f0fca8abf453d367fc906e85f9c9dbcc7d36ad5fa9947b72"))
    (1911641, uint256S("b4012f60e2c4d2ec81b903d50c6d0e4d287eb5a1f0d6f17beb6fa2e6b570c608"))
    (1937474, uint256S("9ff1ad9f5eb43231808cc8b44e232e13fc19f88c644235f276e99acbb1178245"))
    (1963307, uint256S("9b0a26ba22d3b49a6b794f7ed6d109aca8738ff44423045201c914058940389e"))
    (1989140, uint256S("4696c6958bb6004ab63d2ccf24805f01951db3b713f6d8cccc165ef55a63237a"))
    (2014973, uint256S("80eafd0ce9b5d95296ee8fad7c4d35a2c246c7a394c2264691a1de66c8ceb91d"))
    (2040806, uint256S("f0ded13218561694017d80380d78d4a996fdb7a0f93d1feb9bd784ffe21617e6"))
    (2066639, uint256S("d264705665f75343e39d1c3b0e6f042861e45ee9e90d36a5e708bf36c4535e3c"))
    (2092472, uint256S("ec1c9f51850a6c21565000098d3640b83c6358495a83b476555d972ec568fb90"))
    (2118305, uint256S("e15fb8bc59425f4bc1305f59ceb4fdd07523bdb724845ccb73ffeb884ba365da"))
    (2144138, uint256S("f5baaef0f60c7366100007d7e727a7cb74794af09d1d2b489ec471439e5c392a"))
    (2169971, uint256S("167e2c8519eb3f9b8b672881c785964e003be73bab57bb03c43b1281549cad9a"))
    (2195804, uint256S("d2b30129672e8b6718a2c71c160d03e695644fc8fe48c77c39fe90e8364dfa06"))
    (2221637, uint256S("b535e8a2a9e46582d4ceedddb360515c6125b572594eb1d74718bc7f8095df5b"))
    (2247470, uint256S("77fc6035a6d5a7622af7da2157c1b6107ab908f166569a25613e4b6a9781afb7"))
    (2273303, uint256S("33060a0052fe6f11175e6fad6931e91a8fec2e22f62ef044e41f493d6dd7088d"))
    (2299136, uint256S("1fd38ddf876aa052a8674bf8913daad67a9b4d50f5fcf380f80f63911a1ce2de"))
    (2324969, uint256S("f66fc80d98b66d103f7d52a56f3d3698253fd0a15f036baffb45cd681f2e319a"))
    (2350802, uint256S("f8074d4544bf2e6ba86dd224f16488d1c888d36108d1d2ce2017711dae273a10"))
    (2376635, uint256S("013ef21ba7b31364b004d9fbe2728f4388a11f95e98bad2612973b61bfdcf68d"))
    (2402468, uint256S("d72b134e736ed82c772eeeccb9841ac73ee5dd4a6e93c063226810e257b9523e"))
    (2428301, uint256S("611cfdaab4eef6a96b32f45eabe8be83a1a631b4e4b9d43b0d026998043bd111"))
    (2454134, uint256S("6676f76fa17529e5c7177d95343614fbd3ff473ab9819cae48a632d4ac2e2449"))
    (2479967, uint256S("a5d3d5c6b65e9eeb940bd9c2ae73adc0fd6aca920fee59e1c2860ffa1dc78667"))
    (2505800, uint256S("df864f6ddb9564941a69690ff3feddf0610ba3abe04c344e1b890a3cdb213cba"))
    (2531633, uint256S("4b382dda7c0d04764b4697b97db560cdd9438c6e652b343360b307693f650d45"))
    (2557466, uint256S("acfcdd31fdb8d1acb22d52e6855c63433e47cc7c415e52117f856c55105de7cc"))
    (2583299, uint256S("9f764cb4fe429334aa6ab49150a0b271bc1730c335aea86bf9dc3fac7c5c83d9"))
 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692469935, // * UNIX timestamp of last checkpoint block
    6510700,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint
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

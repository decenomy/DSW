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
    (22466, uint256S("24f3f4e17b7542cf87a0264f5c574cd908209159ed8c798d290afd4491fe7a8a"))
    (44933, uint256S("3689dac544301ff0be3fd01eb39717fc4fc21c50d23ff1397845555c82bbc1fa"))
    (67400, uint256S("7858c3dbc12136c9b924d698dc210165b6e3c9b656c4d9cfbf3259f3bc0ae826"))
    (89867, uint256S("81bd7b22f2be94b263ef6377f5a04c505bdf6b30e53e9d19f42a27853e6e37bb"))
    (112334, uint256S("6881a446123f5fc47ae0751ec924259de8d0829e9d87488066ae08689bc3d64f"))
    (134801, uint256S("54b239d2e5e9c91f646d0e9fe49ab426cdfd9691e2dddf333238442dc5dc1108"))
    (157268, uint256S("921eda5b1a20ec5b799b2d3f2fd5709118541338578c5b8b863d064aa92f6300"))
    (179735, uint256S("2fb007c3143b38166dc777594f624f88f3ff999c754610379fae00c6c9eab652"))
    (202202, uint256S("af8539b761c2e2a27e8dddecf9f92bd9c3cc29786754dfd468b3584d21b97dc7"))
    (224669, uint256S("5f5dc667dd0b931716bfb5d9e25aa4dcb84094c09984942a51740aca3a6857db"))
    (247136, uint256S("6291c32267475ef1eeaa37dd158816f6bff17c0bf904e5138e733f4806832959"))
    (269603, uint256S("445f1ed229644ae5333532b5ff97623010afc5c14c8b7bf81c37f614fd68f52e"))
    (292070, uint256S("f0194e93ccf7cc31172841f427f11417cf1d5ce1d30ba0493a015bc1380fa90e"))
    (314537, uint256S("831461f7bbe31acd71bf14bf201ec43e260580f22d93ffba30fb562056166ff6"))
    (337004, uint256S("430f328c6eed9a26d015ab60b19a561511347a670738dd54577defb350e772b8"))
    (359471, uint256S("bf357546edbb332c51182f92542c89f465df6b490d728a3070c4ff5a6f9461bb"))
    (381938, uint256S("f8301646f34d657d2137a1fedef46cc09919ce3cfb114c84b29187a9097a29b5"))
    (404405, uint256S("4331dad426c7cd9e532c2d351ce598da79e20e47bd197eb3774e67f810c148f9"))
    (426872, uint256S("0f46f2c4a86f8639b7f7c6101a659cc955b70c79f2558bf8e37f75c6bbeec564"))
    (449339, uint256S("3e132f3be2a2918728bbb63d85e469b59da90feadc3acc1774d0b3ae6194917e"))
    (471806, uint256S("30b1af2c222602e8c17edda3202ef3fe3a896cde1fc96ae742817196ca18e5bb"))
    (494273, uint256S("51e87e69df8052e710fa0eb9af82ef30d039ba870f3af4bd15e7601e7483af04"))
    (516740, uint256S("646763c50f67ec1535e5159a5ce54d5cf6b6fdeee5772c33cb5186914280a30b"))
    (539207, uint256S("7b68497023b59d516b335ab075d115e0066a186c4c2bfe8c0ddd93ceb570d09f"))
    (561674, uint256S("062e12a95e5645a63b93a3b2e08a447e1fbd0501e03d7d7836bc772b7bb4c9c5"))
    (584141, uint256S("8d25a902fe87753d23eb96e32486e614ae3f6e2eb8d8290a3d989ee8a48db693"))
    (606608, uint256S("d5a776a2e3f6d0595d92fd03df5285cdabf15d8fc289f4e8e5d97ffea689fa3b"))
    (629075, uint256S("134c84cf852203fea430d95128c950dc11ea01c2cbdbab0694c5c99aa46be5c3"))
    (651542, uint256S("cdd642719a9f64cbdf1ddea39ec74760388690a13d8097a3252ebc7d2fa22535"))
    (674009, uint256S("0740790eea5582face68c990915beec97d65720886a4f85d0b12ca8e5f5c72b6"))
    (696476, uint256S("6f61dc376050d22dd0d0b8587a572fa8e7eb082a2270397739fbc826daec8d21"))
    (718943, uint256S("3c94bfacb49b9e0e3188288bc439fc35f6283c77866835c0dfe7dee948bb901f"))
    (741410, uint256S("5c62daf1905bda978b86bef2d6385066e8f8ed419618de3b86ea53e28d336904"))
    (763877, uint256S("d8e4e2d06b7f3e95ba798b5b599e7b84bcdb2fd01119a39223322bbb0f0869ec"))
    (786344, uint256S("b29fe14838ff46678f1f360a159040ffc514ce19dfbcd5a345c3a8c16ea9b8f4"))
    (808811, uint256S("dcee4e6f8b34b82f24ee2bd47772a7633209347c5ed2ccadda3afeb2055379a5"))
    (831278, uint256S("860ef14998bf701920cfb6c20c1816a257022bf83c28b0ddd93fe8abe58a508d"))
    (853745, uint256S("add6c0dcf01d9c011c2c9f2dcabae0774e26957864b5c5bb077cbb40c53d8f92"))
    (876212, uint256S("be3fbf3e00663fd003d5f3f4264cc7bc6a2761dfbf341ba8ba0e58642c36ea30"))
    (898679, uint256S("3bb800281c0f1317d7e647460b774e45e3b8eda8e5e2e1888fc7d1d2101a3093"))
    (921146, uint256S("ce454252560f4e058b05bcbfcc4270961df2bde996e0d8e7c83603e1199600c0"))
    (943613, uint256S("2d9b03b60016ad8baf6720d870203032d676c5363e93b483b393a6fcd085e0d6"))
    (966080, uint256S("1743d0f8f64c85c2513a796d872577eb06f85a668413a5ddf62b00998f3e09f2"))
    (988547, uint256S("2f7ec62bd104290310246375cbb5af27bfdb0ec76ae453560e4c13f8556eb253"))
    (1011014, uint256S("39f1372066cba47cfe8fcad97446c7a674b38acba70158f9ef8330a8acd13b7b"))
    (1033481, uint256S("7c7fb2ff34a3a3246632ea647c6edc11bca737594d170939ba75091259bc04e5"))
    (1055948, uint256S("c8b1b4f3465c9a4ac213496ecb9d4884c38aa68d2dd5e0ae091b5dcf31375043"))
    (1078415, uint256S("866f4685533ba2dede4d5069e8bc7e67a5b390b57993f31dd71db531e3a2fa43"))
    (1100882, uint256S("2f173ab007d8b0552c4bd35862b771de654429bb369b4675abc264fdaa5978a3"))
    (1123349, uint256S("92dc3e59bbf42a6eff7d89c29e9f799bbd56861da31718880c0a59f63ab0b3ad"))
    (1145816, uint256S("33980e61d91c1bd871034ec196e21a869b76fc1121ed2f1c8af2fcb8117f0a63"))
    (1168283, uint256S("05193b8845c03286de00a5053d43acb67722790049514761826260e8e0454f85"))
    (1190750, uint256S("46b48017d79db5c368ece44717a7ac20266f590868bbe255f76ff4ba12d0de31"))
    (1213217, uint256S("f64cad8107c3be7c5b080b73320c8d8652a75c25c27ddfae7978f14cd00a37c0"))
    (1235684, uint256S("d03aae7d47b51d38afc2acfd04739814cabf260719178faf87487594f9beb9cd"))
    (1258151, uint256S("5e8a3d0ac7629f6500c6d499d3a7e4142da2f18e0befd62dc7a58473f6357a3b"))
    (1280618, uint256S("ff669d2e4f079b50697f9d9882d87d3ad3c91bb46f56bc4f0372afd262545335"))
    (1303085, uint256S("3c168c9429d1aa35152e80f1f757cc954d808cac38ae0331d04433018f24c36a"))
    (1325552, uint256S("a947ab57049102decd9d6e92dcf62920ef15016e5c3976e6cc882bf3ab28e956"))
    (1348019, uint256S("6a52fcb555fafbd77066ef927edaece4e0ad0325aaafe7fb534fc700d6de777c"))
    (1370486, uint256S("f257ec8fc7c92772ad567aa6e91d2b3d767b2615656ffb2adb8092be0aa8cb2a"))
    (1392953, uint256S("8893e4afade8d6f4b67d8c132884ecc598df077e6deca14316f5191df0d88e59"))
    (1415420, uint256S("1f7c287b171dbf52e15ec7c928a7029480cfdb3dadf87a9363c5fab1d3bd2928"))
    (1437887, uint256S("28912d9a6b2298a52c3a679fed63d58e31e94277a2f3edfdbdc24a702347d29a"))
    (1460354, uint256S("1bc8072116490c2af3da0993558ae594f053b18870742c6c4c1fd05a530e2a3a"))
    (1482821, uint256S("edb1fbabdf7980422fb480fdab13bb0892378a85e0ddb549038f2acba477517e"))
    (1505288, uint256S("a724fc247fd488d4505d0e1cc8ea6adcc511d6227eb7497fecfe7775561075f3"))
    (1527755, uint256S("30fdd321e38a5c0582468cd9e088c5810b88257f268a19d33b0f111de511546a"))
    (1550222, uint256S("6d6440c079ffde58a1e89276a618c42506958be85f8a7df231ff7c20bc2686d9"))
    (1572689, uint256S("87befcefa6099dc132a855af89436920d00b8ed0b8b7fb97c677e8058f773435"))
    (1595156, uint256S("fa1c2a9ce671ae34b36879696120591400cd0bf5407b5d0989d4935cd0c8823f"))
    (1617623, uint256S("bb3f08a7767200a9006491bfeb5414927249e1267e271236d8cece5a06dd63e2"))
    (1640090, uint256S("21855331f1da1a86ccd2352c79a6ce046cf8c68ad1057e70a371a2d7401a8919"))
    (1662557, uint256S("89654e5e4be787380457f099fc57a370baa9053aeb4dab10ad21dfbf089c2137"))
    (1685024, uint256S("c4b8ab2b1ae9e905f3c9e7449c6e6226d217a30771242ee5e30251a0f38b4db1"))
    (1707491, uint256S("008a4e40fefcdba035e8ebf9cf3e165d9d8906fa0921a83ef84852629b308f99"))
    (1729958, uint256S("fc82cf1ae9370521887fefe230dd684e83b595f7cdf538ad609d71742dc361bf"))
    (1752425, uint256S("5173fedfc9be7fbbc0ad81d760d59d8e1e5a728c18913d66118adb75c26b5470"))
    (1774892, uint256S("b5073b2d3875340c9884dfe1b3921fe714e2d17443dd4d541d46b5d06bb99128"))
    (1797359, uint256S("182b27b0197459b509bcd35c71747e5b3ca53c2b48cb19614ec697fecbd3e683"))
    (1819826, uint256S("04e01397d342911c8bd777e6bd95d3793111c44210b4be30d8e75d8832a3782c"))
    (1842293, uint256S("854c6b3ecae5b86fa3c212f65d4c1a9cc09d1873f7663fd9b5f1f9034a9f115e"))
    (1864760, uint256S("0a3b42c00c87b46d8e9b9185dd94ed98f32d7b5880eb2d8ae92707cd653a82e5"))
    (1887227, uint256S("7e58d8c1c0d92429695410043274a343561c02d2c319dc3aa683153d762a24a7"))
    (1909694, uint256S("da4eb4d7aa74791566290a84b38a3af748adec4083db6138fe0a455ff36995c2"))
    (1932161, uint256S("9abcba5ac1d0b5145c59bb63ba991ae2a2e807e27b64ec71c21c04fcddfd322c"))
    (1954628, uint256S("6ff4f4c60d417a6a14c4caff7a0ec86b03751c02d66a1ecc30cd0b45e9e1ceea"))
    (1977095, uint256S("cab307e233594cd0913edd2f8b3bf763b26044e2832b9610619c73049f7cd669"))
    (1999562, uint256S("02711ddf5ab3c41cc53c9f1c1928ced4ace06c93760185487064e50db85366f1"))
    (2022029, uint256S("2cb7f22ff1cef414b2b42b421b2619d4c48ffb0642b1c1b927289b40df552033"))
    (2044496, uint256S("97255c33e7b5fcdc5825085be9db5070fa568dcc500eeb68f3e41a5bbb755ae0"))
    (2066963, uint256S("32d17ce0a360bebff6fe47bbaff912135e0ad571e06eaec3b9ec418d48dabc02"))
    (2089430, uint256S("72f3111be54ff868fcfcd50c1d8f03af6df463d265298d5dd3bcfb1262748a9e"))
    (2111897, uint256S("1fce1cd5a690866387d15ea80ed9810b2808447ae0a07bfa4a150e7d76f23c67"))
    (2134364, uint256S("0df8b5a35696adb55ace7c3091642e2cf26691db9fb721969ab3c646894c689f"))
    (2156831, uint256S("c049f8acea91c2fa481f9bef41ab52ab26dec064ea179c359b3b6e8ff7bdf630"))
    (2179298, uint256S("0091149a35034db47074bf725868246740f0502481e3445ddc6ceb5269a078ef"))
    (2201765, uint256S("c0a5e1b81c67b2ed73b0e1b5d036b52be9a861c71e7ddcb06fd49df60831fef7"))
    (2224232, uint256S("064e3c900836537257cf1f218b76f9cdf1f25209259ab501f07d5b9edf51ab47"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1691600340, // * UNIX timestamp of last checkpoint block
    14240675,   // * total number of transactions between genesis and last checkpoint
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

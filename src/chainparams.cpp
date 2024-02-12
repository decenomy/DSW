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
    (19140, uint256S("92bb5de4332fc5b4bf2829084d17e66f3d3bce4d4dba9b8304b05d61fb1d300e"))
    (38281, uint256S("4c0770345207d7d243a4b868746fc1b799acba8c22436cb412e438aebc6e08cc"))
    (57422, uint256S("15ce2b0e7a4b527879eeff3ff2ad1b267ee83b48a617c8c4eab8c9cb222f8d26"))
    (76563, uint256S("48e6e2cc67baa13873ba1d1800e3385594db3a1a020194c3f78f7afc18bd1043"))
    (95704, uint256S("b58938c724f6fe4da41e70da3b85e841a27317e90d51e9d424cd741967992479"))
    (114845, uint256S("a0d33ea5b25e2a325c681af82bb5fd84e5df6d3059b39e944762b2ac545da513"))
    (133986, uint256S("049d0125ef11d512cf5481c18934c12a98ac5209d62af0ffe04e2a6b1718c300"))
    (153127, uint256S("dd78e02b73b7019440e340fdaf1d902603d4a103147c549436ae76b143f8ead8"))
    (172268, uint256S("3c4cf6078fc743b5068f9f8804e23637d6cd333301c3917d9b4b481e72c23511"))
    (191409, uint256S("14e34c23a57e47335f4cd6a257c085b27024a6b9f03fc9009bb4dc89537fee09"))
    (210550, uint256S("4a607f4cfa94c62351a3bddb8945a6057a4521901e926c1f2587e25a874b8cb1"))
    (229691, uint256S("cedba6b749b9b9952d25029f75d5f8fe9bb3e639a092f3725fe03de00db93508"))
    (248832, uint256S("dcd65962fb3b35719752bb553b41c16a87079113fa643a6c499752f75f22f0da"))
    (267973, uint256S("5af86d8c585823a1a1f6bce13586aa20fa6640bd0802ae37570698ec697ec2aa"))
    (287114, uint256S("e943249b33b65e73a3464d6a540ae05fc7e023d2ed5909d1b3da3df7327241eb"))
    (306255, uint256S("c751163ecb9c1d31222d4026466f6a4d2de270dff389ce2a60ad548879217317"))
    (325396, uint256S("010755697defb965522241d87f6f744642f2d80c2c519e1fd6964f085697aa27"))
    (344537, uint256S("60e44874cbf9a308989f84550c1efd6ff9278aadbe93fc1cbe494e4264abd9ed"))
    (363678, uint256S("4ce4cc4dece532e50fcc3f84e574e0faf39893c8c58ad5c93688107466965520"))
    (382819, uint256S("4e293fb43485472e8e9f3320ed295d8a7241dd19d0d5c24d822874a6084969d3"))
    (401960, uint256S("566ff232766f28795995f347d501038d39ca9d679ee62f004078cf45ac48798e"))
    (421101, uint256S("17b86cf0d2ccfd0f534736e9a96b0cf2a5ab751ac4efa482d924b94b9d8ef03c"))
    (440242, uint256S("1d22c36efbf1a6a8cb6849daeef08b3c3fd42388824ebe87e2377baf8947cab9"))
    (459383, uint256S("dcc2425065c7ecb178341c21605f28845e75fd112af66544702dd55302de5269"))
    (478524, uint256S("d6ce1fb2793951a893711ea50522beec406d0291a487e600bba9e0557cb4facd"))
    (497665, uint256S("0b35d4e502ee5d60516ac48735ce6ccb286c6c11ca3a239f54660539ed90af4c"))
    (516806, uint256S("17c181af8193da0a51b79a1a441ce7717d10a16084f31037e5fd2265c4c9e86c"))
    (535947, uint256S("7d7d1126c985e3c5a64da6aec6004682680d5c015310bea493ad92798342d48a"))
    (555088, uint256S("ef6074882ced708788e8d9b6901e385384745501008eaefb61f55dd87584ec0f"))
    (574229, uint256S("b21209c3da95e4b76b5c042c5dda1a87cb00c5ff2035210fcd840d382cf1823f"))
    (593370, uint256S("80c57dd6802e0c947215ee192d3b0b159d6e02cf7528618086d63f00ac0c39ea"))
    (612511, uint256S("843f9f0ca4a75aea223623122ab97bb9eb94515b236eba1e46b4b191ed945592"))
    (631652, uint256S("9a3e32113f1cb07b12e8b8e9d5d46d6a3f4fae0eae24866ff7fb40ba33a41de6"))
    (650793, uint256S("096f7211032038598ed612539477319bc7ec2241a997c899a8e7de29ae673815"))
    (669934, uint256S("67692ae485955da111ade5648c37df522c2bc2ab9853df83c6c70f35b3c1834e"))
    (689075, uint256S("affc4103f8eda5350ed7d19977e847072c1dd6585a5cd7c22bf792bc6cc5e2a1"))
    (708216, uint256S("cfb5a7c4945c4af76c3f0f02b4023b4b7e89e908abcdce1e3e1064cdfa3923d4"))
    (727357, uint256S("0fb2af83d00f78ce0cdf681de2ce97269c5209dc36af4d95056fa2eb276cb78b"))
    (746498, uint256S("b320be8635b72b4d67b53d85ff48fdb3a5dec3c9475b0d8fd2fa5bb5f0eaca91"))
    (765639, uint256S("13ffb97f55bde60ce70c734f37b06cdbb2f3a68338a0f5594b9b3603a609ebbf"))
    (784780, uint256S("cc00cc8adace9c36a610a8c71839b1f7a2a90088f02928ecf285e51f9dd041d8"))
    (803921, uint256S("65ca81b622e85b7b5712bc20d7bb25e875fb10a0e99fafd5840c96fe27cd1100"))
    (823062, uint256S("62e85efa706447a2ee0d477bed44d91317edd19f9627cdb1f334f0308f23863f"))
    (842203, uint256S("73e32ff11d92f144c193498fc8b38f09d00e3cb154f054bd82e4cd3ea3479ffd"))
    (861344, uint256S("255718a4d408f60ea2460859df535133ceb7b12304e0520772053a7e64ee03d4"))
    (880485, uint256S("b4b33a4394f76a2d79f3350e49744d65ed061764f53c5c642b86168e52bf749c"))
    (899626, uint256S("ffb44263c9b830a045ee6adfd60e0852b7ced4486e0c065eec50cfe11690e897"))
    (918767, uint256S("5f73598228e81ef732a5cff0c6b33267ca212adb1514699e53b08c842be4d7bc"))
    (937908, uint256S("4554a47ddd6699eeed302343c68b30b77f63120f37f990db67dffb02d1f95ec5"))
    (957049, uint256S("90b04cc47c49f532b02c8d6d82a461a115c3ff905b661fec2fe4c552ff00d7eb"))
    (976190, uint256S("96be15b37309062c8e50f01d44e4ad366e5da05e5cf6b388341062ed90c5b4ef"))
    (995331, uint256S("b7c6afdd2281874b6af0b2a431c60cd2e4dba26a1a322008a9c35d73a6175b54"))
    (1014472, uint256S("a7b03ef78c1f3717107de4a249a3dea9583804b581f01ba93f0a52b6afd3040b"))
    (1033613, uint256S("90a88759975551a8d77c553f6acc5a965af6ebfcc3b2e3f1ad7ccb4b41c78e28"))
    (1052754, uint256S("3a786fac40a8d9deedb5040bce9d62fad9486732fd31859ed33cb6d0a7ada1a0"))
    (1071895, uint256S("b17b16a40c8522d5174b0b5e15813f09dfe3775dede75fea5bbb8b0039e6314c"))
    (1091036, uint256S("a7bbefb5ad847602fee1d5b8cf5a58bb7b6fa80d85d8ed96addf70c7e0fe6b2f"))
    (1110177, uint256S("cebeff608daada6ba0ab59abead52e40b3e215c159734d0c2bd95c7a75d3c0a9"))
    (1129318, uint256S("734cf31650f27cc107cae575a9aea46359408c99a3412265ad484919f7d8980b"))
    (1148459, uint256S("326e968ea6f04d11bd34a6634d23f63f24f0bc98dee61fbd774edec61e82f8d8"))
    (1167600, uint256S("5280741fb184d07e50eb99fed879cfb634c117f005a24cf33821a8d7064ca2c0"))
    (1186741, uint256S("a821a5993e538ccfdd737cf27b17374ade7f96944f9d486af0db7b1a3f3a3274"))
    (1205882, uint256S("c90cd5cf950fdd388d464c9da78a094398af7d0e81fa46061be8c4a0221d8e5c"))
    (1225023, uint256S("311bc0603e0e9d91c1a99dfcacdfccc41b4f76e085795672fa92cde05f4fedbc"))
    (1244164, uint256S("a2d9210e5e6ba0e21c151a7b68cdfbe061d11ca8d0aaff9ac5dcaea4153a974b"))
    (1263305, uint256S("afc4a6233cfabf309527b3fdf9b9c9cbb227946a76e2db6b54aae73784c559e6"))
    (1282446, uint256S("36b95b8176119c39718f8218c2f97d89646d4ca7f60aceb82b91106bf0457f95"))
    (1301587, uint256S("eb7dfb45993329ea212dcece0324f0fc7caa7184e6c54739b67cc6f46e618cdf"))
    (1320728, uint256S("0902f62b2a7cb3079d99f00f62db7639097112a11145cc99ba03fa0c33c7adf3"))
    (1339869, uint256S("5f0431fca26d061605feb262d2bfac2fd06165de5669728b47aab1233c2123a8"))
    (1359010, uint256S("10a8ef420f5d7bc2a89a2334a6926e3ad8ac73a8843508908477e41a7cdc10b8"))
    (1378151, uint256S("e97b59b5bdc44ee5a4dd9626a072ffb15526179fce539883f7951b28488494aa"))
    (1397292, uint256S("39838deef7681f1227231bd0329cb79208c0513d52c82e79b3f42558d2d6ffa7"))
    (1416433, uint256S("d0eb3a3afb81836c59c8ef63520a72dc4501a4e94844c17243c65d44b11762f4"))
    (1435574, uint256S("9397310d57d51f0e385e2bd21a5196d19ae5fa53c0b3f4313aa0f28dd7ca181a"))
    (1454715, uint256S("b1f07f293f4f1813efc04446ef6d7320824bac898f4b5a1ad40740738d494d45"))
    (1473856, uint256S("d8d116ada5ca5187a793045f053b8b658574d816a266942ed1357907675fa41a"))
    (1492997, uint256S("40d4ad48b9b08cc367940ff0a984704083f24827cfd3b92636d25d3277df2e30"))
    (1512138, uint256S("c980bd3161df62d4c25e6ec63d8de80ae25e47ec5615316d4c18be5603ddc5f7"))
    (1531279, uint256S("c187032f0dbefd8beb39f66e781943092e6e9eedd4f8d275e334c41ea48f2803"))
    (1550420, uint256S("dad414ebb2bbdad8e2fac7e737cc81918e6c76b12ea7a571923af18a0a337b77"))
    (1569561, uint256S("7dddb9365dbbab4a530918c45ab700e791d5b1914ec37610957e18e63826f199"))
    (1588702, uint256S("5a5644dc88a9f03ddea8b77d43c4518982c82d255420b855608aab8ced2144f7"))
    (1607843, uint256S("5178f9a60c395c05e825807ff9606399b874745a843316ae96bb665aa9e09148"))
    (1626984, uint256S("43ad78830ba13b8559ce0fbc5391fd752f7404c8e3b43e6fa3a6b945b09d3ad3"))
    (1646125, uint256S("dfb6d54d0ecb56ca7e962766af10187d554d03668588f948500aa444b5c2b866"))
    (1665266, uint256S("0b2a7311527637693b92838cec7ca61ed7bc6b856b81463a7316cfc328a5e2a1"))
    (1684407, uint256S("068c6a1e73a937c23f8ba62d05606091313531aae502b42e0884bbc191f64c84"))
    (1703548, uint256S("7fd3307bdf0f8fdb45a97809f947ab88aa64b42e30c32efa055694776bebf682"))
    (1722689, uint256S("3b020f90febb35a63564f57e9a5d860b3bb35c515a940b106be877cb7fc13e01"))
    (1741830, uint256S("30f86cd68b4f15b5095b76e32015c24cc775cf977515ddc451456748ab463d02"))
    (1760971, uint256S("860dd20548deb22316dfd1a84b652b1c809e240e900d5fee2049ef5793cfd25f"))
    (1780112, uint256S("7d3e5adc238bbee4f59c8be3b808dcd785509dfcf63ae48c039faa5549267d6b"))
    (1799253, uint256S("a9c8fbf623082000120c308fc59af3086f80a12a0c15df5c56b7e128b2ced2f2"))
    (1818394, uint256S("eb0a8baf5ad10d266007095d676af6180a20e1151af3ff3bf72b5f394084f52c"))
    (1837535, uint256S("f904039df823aebef3c86617486c5de7615af86cc889da27e0fc87d265e2ae0e"))
    (1856676, uint256S("db62696a4f0ba22f92ea555b49a5a86d62afbf17b3a77e2f91dce49f5d0cf358"))
    (1875817, uint256S("e1a9adfd1695839d443be873c363f177a886c5be7a856038ab3491042728c561"))
    (1894958, uint256S("0400b088d1c3c718590b94d2db9807beb593ee2f198e20adf7f02c5782a94a80"))
    (1914099, uint256S("4ec52cef3a0611cd4f6a66d4192ff66dd27a45d8e43120179d204d422f156b16"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707741375, // * UNIX timestamp of last checkpoint block
    3936938,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

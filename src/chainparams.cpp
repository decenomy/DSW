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
	const char* pszTimestamp = "Bitcoin 'better than gold' if you study it, fund manager tells mainstream media, COINTELEGRAPH, 18/03/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("04bcfbea59ec97482475f554db08f7f67c5c5a95a52a356b052d0ed87862815796fe6022c33a0baf09fcd8d3ee98ebb6aa6a77fb43d716641242cfd45369a88e7d") << OP_CHECKSIG;
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
    (0, uint256S("00000e41db923032d1be957ad4be59aa287c9727ca7602dd403cf7312d259968"))
    (4329, uint256S("7271daba1a98085b9e922ccab0113a733110bd1966fa849cd477e38cece3309f"))
    (8659, uint256S("e767377fe02db296ce491f767bbfbb663fcfddd1dd4814b21f13f20f730447e7"))
    (12989, uint256S("b4079d4842bb99853bf9fdd69659b3175e41becc3bca39eea096dd61cba0eb80"))
    (17319, uint256S("2ae21b7ef49df73321a5b6c4a52e798fdbd1884698a951963e56a73a649e477f"))
    (21649, uint256S("051abaca570ba3857535002b613d1e1476665434794d467ec67676f3f39f1cc2"))
    (25979, uint256S("8468be98b147c58318952822d99805127f2b4223d92859d99b233257cd06b681"))
    (30309, uint256S("9a86b922450610d6cb93801c982c9709cbcf3511be775c4080aee64a00136a2e"))
    (34639, uint256S("a908bd13fe255cde6bf2e5e8840d410b60d95e01ebf7290d6a4aebba7dd0a08d"))
    (38969, uint256S("75ffca3fe6f0445429d05a1122817281d02ea9b6c3263f187daf0df1baacc306"))
    (43299, uint256S("9312b94f7b236ba6e90bda2be6b1b71c487369b294097f4500522bb61c844426"))
    (47629, uint256S("96aec69e57b92ebdefe6fb68e35acbdca020fea97105b4fc62d6fc2185db0765"))
    (51959, uint256S("315c486a456b5b191438ec757f9fa53ce2601033f47ee66f2a91f54ea5ee84ee"))
    (56289, uint256S("07eb010d9f3b5d52d42da745132193f397e2565f690300712e600f62258b8bcb"))
    (60619, uint256S("bb9a22b73c7562fe4089e34ba0ae0d99f407aaca37734dad591d77f85e438e4f"))
    (64949, uint256S("84952260a09382d5fb6828f83de41f10080c5cfc52df28a60a3106ebc1147d54"))
    (69279, uint256S("58d34542c9be217299815200c322d89a13330b480b583202258d92706173ca27"))
    (73609, uint256S("0b08c4010ccf34f668596230b948687a4dcc38b9d83a18a7612f12f34110ffd5"))
    (77939, uint256S("88673f3754efdb2ce9025a327e460c55659ed63dd4f8520f9790d1a83021a9f7"))
    (82269, uint256S("773a8abd260438eb91c5a509af925069d248171bf395ad16b543cddbe68bb53b"))
    (86599, uint256S("da1b2b894393ec862a94e1119fc3af4b0a9e64fbad9e92f3402c128dcdf9101f"))
    (90929, uint256S("93a976d03187d85ed71420bf9a9ec2a77d24efcb9415e49c74091498b790a2a6"))
    (95259, uint256S("b5b4e6259f33ce84364ff6696e87a54d81935814d01cfac69c325b7d99819c43"))
    (99589, uint256S("af31f4cacbc263359f4f546c3544c4c7bb498f6797302a36826ecd2bdc83ccee"))
    (103919, uint256S("d4f7031512a596e8ca924079382cb182c793c2cfbee13661977c7446970d3760"))
    (108249, uint256S("bec6e7051dd6b82d029c1031a2d48b07e21806d9b6b7c16947e3800250b75ea1"))
    (112579, uint256S("167f43b5541fc4181bc27999d6a9b4d15120317b6ab84a58e33a2f7a82cd02a5"))
    (116909, uint256S("4164570429e1c49bde4d66826ec1b897a31b7bd774c9feb57f8b4add494caf61"))
    (121239, uint256S("abfe85127b9203a594d0bb520ab14d08dc9b4877569a75c6561c76f34c0826d9"))
    (125569, uint256S("3bea0b098f68a3a7f6408ee9592b879ec64e2d3884a91cde347d4751310d21f6"))
    (129899, uint256S("8fe6b6f9b2b95a2a189b0fec09f959ced360a8221ea4a02b3028867ef72a411c"))
    (134229, uint256S("144df106bbc44527ba2ccfac27df93b507cf4e089f039b6a7b17f16b3f96893c"))
    (138559, uint256S("9bb2f068b8b43bf8d1d65957b387d76f8bcbb7dc59d6bdc9db229f4d7b418028"))
    (142889, uint256S("9e3374821306fef0f4cca743ac52269d96a55eb26943ff67aad03c54423c58d1"))
    (147219, uint256S("a98db98b3b42282c9d566b2b14bb886041a7dc4c546cecc566b294eef9a6a613"))
    (151549, uint256S("64691c984012bfcf295af30d1470ebfbbc69f3fd7f612ee9455d9c80767a550d"))
    (155879, uint256S("3bbb06c3bfd2efed01ce5fa84697ba4f21d03bb0e85cabaa98189d523742d4d0"))
    (160209, uint256S("7b2a004e0371ad3ba33d0ec95be639337ca374f443be14753dde2e7a969a5316"))
    (164539, uint256S("5f60eb483281ad7225dcab0fff2a3070bc8a7269b19bae7e62d18eaf74c2b63b"))
    (168869, uint256S("a35b0a534772588c57848e37f92705163741a72d619463b5cfef274bb4ee5de7"))
    (173199, uint256S("93f2d6ef14c7bdb21080db8ee1a630b774c3bc97641d68de9b97f2c1b2bb9301"))
    (177529, uint256S("cc845c4a985f9c64c9eef954fbed017aa56ac72b0f8f7a2eb52d6ce93dcc3fff"))
    (181859, uint256S("54da809d173ad8bab4a145760d6b3f0354705e6bae19b2dc5958b10a2e6ca251"))
    (186189, uint256S("51a96e9d2bba316a32b66aa7a0f23905a1fef11aa41f4b630fec70f61d109843"))
    (190519, uint256S("56847ad45a70f70148edacfcd5c978bace09052502340c86b19718e46b5c64d0"))
    (194849, uint256S("9efdd940740680de3820eba20e354b1ef572b5169000b123b842bc4b810a7bcd"))
    (199179, uint256S("341ce015bdf7ffd749e79a0bc0dbb7e9301707f88047c9ffa82f37badd07fd98"))
    (203509, uint256S("45b7899f5f39502b9b4c23405e61b9cbc48e8b47575f32677a774a64d0ff70fb"))
    (207839, uint256S("70f1810d5b8ec62ea12155f51362ec9d99afac6c8cdee95ca27d324740442bc3"))
    (212169, uint256S("3b12fa29bc9ec50e7763a363c7945444cc86a457e024e35c69b7dbbf79b074e8"))
    (216499, uint256S("be8cce29fdaee9835a3e83ae4a6b99ac367585dc27bf5cce9038d41b90487e85"))
    (220829, uint256S("19deaf17b1482aa4d1a195babf66ea68518dd2742b79361eb674acef9604258b"))
    (225159, uint256S("42d5ded85534cad2775daaf5496bcf119f55c17bec212b6cf73144bafb27a73f"))
    (229489, uint256S("16e5aad4c86581f3f0ffa52d84d12263170b1790424bbb7f4b6d57103729c707"))
    (233819, uint256S("edb9bb0a196a8d8e82e48b9ed6b6f2092c9a986ef31d2a08b723d89793c12d04"))
    (238149, uint256S("b49baebf33294c73606db19d639001587973b8796b753989d5b78d7580905f73"))
    (242479, uint256S("6e3e267e2d628dc62edef83f297e387328faa1deed094e0ef74c5439c8ba48ca"))
    (246809, uint256S("443396e0be126eff991f106a185ece34c7c8daa5a9d2d9657db9b08e0de00b9f"))
    (251139, uint256S("6413c68a3028a7d69bb6eaf7279eb286633882282ae6353af6c32f710e79d4f7"))
    (255469, uint256S("e34bc4be8faa130a6822dfc6369c78cc7c2965b0ccb5ea13be584d863796541b"))
    (259799, uint256S("d937c44506ef41e10970002337188fca718d4f1f03829a07ff9ccc3d9aa8e5ea"))
    (264129, uint256S("d9b33b2ed997230ec0b8cd8d6bf7bdf45cf949ff32b75ac3eb3452af11925e0a"))
    (268459, uint256S("0f2161e38e4d415faf7626611e66515d8db0068b63940cdb70556c16418e8be1"))
    (272789, uint256S("ec523197193b8cbe5e35f50157ca7b052a1b4862e3bf0274ebf2c503b47abb92"))
    (277119, uint256S("e90297fcbdf3ee70a8310adbe53f41afd3cb7d6464108790bd39ec68f9231fe3"))
    (281449, uint256S("51fd5b3857817a3ef2c37581a7a03aaf95592953fdf7b4387829de5f2e52e122"))
    (285779, uint256S("72d736d7501622e842c5a7a113ae1055054218831dc95fcd61a66dfc84cb2ce1"))
    (290109, uint256S("19dffe9ee77cf146615a418756d28e4180306491f7c8f7e981cce45f3edca361"))
    (294439, uint256S("a12e607048d3306f6a7c4e85a98ac1db78ac09bcba0364b29366b5d389fb696c"))
    (298769, uint256S("f20bf0ce25eac72208e47d6435e56b562906f0078e3211b7867f2594b4466ed3"))
    (303099, uint256S("38fa64d2d44ef02e73c1cf467de6648a95976d84f17418fda589c6573161d802"))
    (307429, uint256S("348953ecce65ddd0722c6f4187f510729b418ec79badb708934fcf9ae777e11c"))
    (311759, uint256S("228cd4d855eb278f001fdcbbf5a08024899beddfbfd1d6104331d0684b4db787"))
    (316089, uint256S("bd395797695ba725c9eccef8cb52503cdb1e9a6249edd4047f381c0e2846d96b"))
    (320419, uint256S("96e7eede55e3de1dc5e25006ea93ab9b90cdd369353bb70e01dbc89a0ad81242"))
    (324749, uint256S("500220d6d205f22d1ea77bdcf58f614554f82e1f6ae2d9001ebe922450089750"))
    (329079, uint256S("28708d3c03ef749412993c832f289342c85982274c44853933a95b51e9b94f1e"))
    (333409, uint256S("8523bf4651536b3d70cf1d593ef384d44541210c698d9622b6ee6cf3127a2dd2"))
    (337739, uint256S("f66dfe8f3d91abd8922edd1beff38f19458692766c36983d43ba72290de778bf"))
    (342069, uint256S("ed11b6f0f2418cc7e58c53c199986083e050a05c951577a82653e73808926fef"))
    (346399, uint256S("c7f94afc473bcf1444a0d989df5dee2384b64f0f318a6b9e44182b6477e45867"))
    (350729, uint256S("b4c4622caa21357d40002520473042a885fcd0904a6a61fd6d883e565ed8ecf5"))
    (355059, uint256S("15169427a1b8cf22bac492a4a3fed8b0fe0fbb077e1713cf28f5f98c73310da4"))
    (359389, uint256S("9f22d17833b02adf7780077171317b3cb491d2f07cd10e9e8af0bc2be5589b70"))
    (363719, uint256S("1c925585ef9e40b466d3398cb266a99def3cf9538f0518c087c3b1fb331fdd34"))
    (368049, uint256S("9ae9e4a3ab7dda068012d54728c7e466424feb82c9017f9825dc340a4e1286a3"))
    (372379, uint256S("71caca8c678b42f58f154c9e3747d658cfc0b12f175f5df248379be8da98cf3c"))
    (376709, uint256S("4bbb91a0abc63171b87d36ac3691257634c920633bbdd8764093d1c294a0009d"))
    (381039, uint256S("7a437c0fba2f34e89afe3ec7f51d297d84350cfe8f56314df71e57074c742c00"))
    (385369, uint256S("57202b10a1e4c6f23b36043ba1d909ca842860b5a83dfade1342c32b92692f5d"))
    (389699, uint256S("4ccdc1feb02355b96d6b585bc7be7a9648e076916f86cbb04fe0ba6664103c55"))
    (394029, uint256S("632504140870431d5c2d2d32f2652476c77ef41385674a6c8b12f66c778c1265"))
    (398359, uint256S("8abc6eca91b1de5828ca08ad15dec902bac18d0c31a19aab070b796d6efc49b5"))
    (402689, uint256S("f5bac62a61ef6877ab17f966d40b9ef557ca44f414c45bef91b673147bb44854"))
    (407019, uint256S("c6c8fcceed8303bc4c865bba23854499c62656df444ee80d2c2ea2c38ce6bee6"))
    (411349, uint256S("e1d59097dfc6fb6975bb0db812e436d0e507d1a5559497a00b3971431e04f83c"))
    (415679, uint256S("32b132c32332ff942314d172ee848470a13ab8e5eb8bbf40e34d27010ea35a18"))
    (420009, uint256S("695c09b33ebc4b0c334740096fc25af4da9130fc3d1c9777612e1c44c2a7e86b"))
    (424339, uint256S("7b756189f139c607e9bccc51352f034cbb54167d55ef1d25cf221f06b7a82f15"))
    (428669, uint256S("8898d7602bf8390a56d024c1aa198f6ca2b7cebe934373882bd34da7e88edd78"))
    (432999, uint256S("af40a2742687a22c3f7eaef776cc7be20d5ea4c61de86949234cb6f370e41408")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1642771245, // * UNIX timestamp of last checkpoint block
    991542,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2886        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0x000034fe1805f04a440c06c1b96b1234b45d9fdba0fcb055d5caf4d83689428c"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1616082640,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
	(0, uint256("0x003279ba296f0376d7a8417354e0ef9bd00fa29f92ac5d9cdf97c160673474af")
);

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1616082641,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1616082639, 933427, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e41db923032d1be957ad4be59aa287c9727ca7602dd403cf7312d259968"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;  // trittium starting difficulty is 1 / 2^20
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60; // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;  // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
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
        consensus.strSporkPubKey = "04709f473a079113abd0da53176c9ecdc2f67c86ef6379459786d757d6d03a1954c0d4a902bb17782607f014d3476b3c73bbff47aa5a4d8b3d870cae33aa497a10";
        consensus.strSporkPubKeyOld = "";
        // consensus.strSporkPubKey = "029e54031b41982ac1c22b780c1101cf4b0efb71f7beb435e46fc0b406ff545ef6";
        // consensus.strSporkPubKeyOld = "0464b1f34052a9fa87d18516fd97bfd70ed78a3424d59e9b9ffa9ea7fa35b50d376ec01b0923a2c7a8edfbfd2787247aadea861d4c6d8fb5814b708ddfb153aafc";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "TRCryptoLifeDotNetBurnAddrXXX6gvik", 0 },
            { "TXXXXXXXXXXXXXXXXXXXXXXXXXXXaoxzKN", 0 }
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
        consensus.ZC_TimeStart = 1893456000;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 166929;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("e4cd39496b46796b69b53c674dfdaaa789396c907f8f0252d72d89effdef8b45");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("80dd173daeebb1fc25e340d05f78dc17bc19a05f9f210e46db312c0c0532e9b2");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("80dd173daeebb1fc25e340d05f78dc17bc19a05f9f210e46db312c0c0532e9b2");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("506c9d4f33ce7334d429a6d5f8e4b608bb8d7c0c2f233fb7becb2b962e7f53a5");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("bfae8546b921841766191b5774e18405aa32986806767a5ac159ceefdd0cb3ec");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("05fb6d596455cb9b24af308171a3a5b3902aac2dc4cb0c582289b5df4dbbf774");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("ce797d5715d07dcabe6e6c3557ed10e9e34ea92e9ec1a54c6eb02905f665c0b6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("6cfd21dcfbcaccb88c8d96ae8801b1c1a925c63f0b3cb263e8b450858262c505");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0x51;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = 31001;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed5",  "seed5.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed6",  "seed6.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed7",  "seed7.trittium.net"));
        vSeeds.push_back(CDNSSeedData("seed8",  "seed8.trittium.net"));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 65); // T
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 19); // 8 or 9
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 239);  // 
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x46).convert_to_container<std::vector<unsigned char> >();

        base58Prefixes[PUBKEY_ADDRESS_BIR]  = std::vector<unsigned char>(1, 45);
        base58Prefixes[SECRET_KEY_BIR]      = std::vector<unsigned char>(1, 179);        

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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1616082640; // Thu Mar 18 2021 15:50:40 GMT+0000

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1efffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1efffff0, 1, 0 * COIN);
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

        genesis = CreateGenesisBlock(1616082640, 178720, 0x1efffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000034fe1805f04a440c06c1b96b1234b45d9fdba0fcb055d5caf4d83689428c"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 12;   // trittium starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144; // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 500000000 * COIN;
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
        consensus.strSporkPubKey = "04ae5f52611fc9f3dcd3f2db88ad4a9b10ab218389cacd1ed07cc893af6ad2f3e6618090edb54038e5a26d2c6d04db4a6c901a8bf52a72fef484f478519fdf0b02"; // Testnet spork key
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

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
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 721;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 721;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x32;
        pchMessageStart[1] = 0x42;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0xf2;
        nDefaultPort = 41001;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet1", "testnet1.4444.tools", true));
        vSeeds.push_back(CDNSSeedData("testnet2", "testnet2.4444.tools", true));
        vSeeds.push_back(CDNSSeedData("testnet.572133.club", "testnet.572133.club", true));
        vSeeds.push_back(CDNSSeedData("testnet2.572133.club", "testnet2.572133.club", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127); // Testnet Trittium addresses start with 't'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet Trittium script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Trittium BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Trittium BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Trittium BIP44 coin type is '1' (All coin's testnet default)
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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1616082641; // Thu Mar 18 2021 15:50:41 GMT+0000

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 0 * COIN);
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

        genesis = CreateGenesisBlock(1616082641, 333, 0x1fffffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x003279ba296f0376d7a8417354e0ef9bd00fa29f92ac5d9cdf97c160673474af"));
        assert(genesis.hashMerkleRoot == uint256S("0xbeb39df5e5c3029bb4a6d66357a41d06c275ea69a96c9081a3e6f8d2f8efe918"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 2;   // trittium starting difficulty is 1 / 2^2
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 5;
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
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984"; // Sapphire testnet spork key
        consensus.strSporkPubKeyOld = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984"; // Sapphire testnet old spork key
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight 			            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight 	            = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 151;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x33;
        pchMessageStart[1] = 0x43;
        pchMessageStart[2] = 0x53;
        pchMessageStart[3] = 0xf3;
        nDefaultPort = 51001;

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


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
    const char* pszTimestamp = "Sometimes you hit the jackpot and sometimes the jackpot hits you";
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
    (0, uint256S("00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"))
    (5007, uint256S("a96bf2199d4d524138a4cbe3cbbf9d1a7369134e3c8927da668a261f062cc61b"))
    (10015, uint256S("4d1b2f9abaceff7c5ad0c5631f46911efe7d71af65caeb3fcdc6863aa9021b29"))
    (15023, uint256S("39fae9bf03dab84a4aef5009e0ae4dcd1096f19131ccd555a44f16110da33519"))
    (20031, uint256S("7da5a604b61f7a51b2ab7f8d980eccf9ec9a1c082507f126d2f307b1dbb7e62b"))
    (25039, uint256S("f5de341c4258971812c899a2d5fe7978e1033afe84b329adc510414bed100aa5"))
    (30047, uint256S("01e0d6896242e5bade9975827eae904f19fa4de305e0bfbc85ee88898158fcf4"))
    (35055, uint256S("a5c5dba76faa4004a761509db6be40974b0dee79da9e567e595c15e4bc7565d0"))
    (40063, uint256S("9f916129d2ffe6e66753aeea06ba96f1d44890a92218d86763130de80c62c191"))
    (45071, uint256S("6ae76d1f0638293d9aeb4d4f146b08078c964024247f1dc409de5bfad04fe202"))
    (50079, uint256S("0a0ba59c4134b2bd1bca9c37f04deb189d14a79c3ee8faeef3c00555b73919ac"))
    (55087, uint256S("fd217fcf1d77879aa1de17b0efecfc2a9f276d2ebeb9a9347af9155e61eac2b7"))
    (60095, uint256S("70fe1aab39ec5947500e3ca1d60f5213a1b20b4fc0740e3cf7d313de053c39fe"))
    (65103, uint256S("840749caaec0d7d48cc97c7ba93d699e5cf61670848d1a9792adf9ef1ed42c54"))
    (70111, uint256S("a157a49588722cafde0f40381c79cf8151b292cf1c33e013859ceeb33bb9bf42"))
    (75119, uint256S("ca11cf28a23c15aec9b06d8550ec0ce1ca457776186fa9b71262dc958be25b3e"))
    (80127, uint256S("6a12457376655d3ccafa1eecd309d964412508c7f378859f2828a094006c45d3"))
    (85135, uint256S("d72c29a18208263cea957eb7cbe8b64857ce873565c82d78f52cd8fbf06ee348"))
    (90143, uint256S("b030430b275e8daa82dea3cee99ce42c102ae8fc17839cefe878acdcd15784a7"))
    (95151, uint256S("dfa8f54ab022c85108717ab3dd537ba0aac90c8a739d56702452449247db835f"))
    (100159, uint256S("4fe878a07971b5916d21c0e38ca74bcc43091064e2c1d48e03215528e1b3f9d7"))
    (105167, uint256S("b94a4a198c7b887a4a77d3d9ecc77a00a9f9645ff2c940fd8e62e5a121e45381"))
    (110175, uint256S("9756ae308b3cc46fa461951c90a4a5e178edcbcb37b875882d57d83ab68c5717"))
    (115183, uint256S("e2cc486755476d105716da57f67f39e28f47efdad0de0a7321436cec2180c5db"))
    (120191, uint256S("8d25fcf3ed7d616de1b8b5aa5c58e1a1460124905ff119f0736cf26142f38d8d"))
    (125199, uint256S("b44c6bffb6150e622bdbd1e2b89dd99e0ce126572a793d82af63abd4d307e64d"))
    (130207, uint256S("a4ce24817feac0eb59babdc10f763e2cd13019f96e44a287b0da72f20a4bc94f"))
    (135215, uint256S("2a25b7e115bce45ac8d346690351679570cc3209edb1e7443da277de128685f0"))
    (140223, uint256S("1ea9596ace8648494671ecf61dc58b7b71fcf213d97c73dc0fde8856ec525f68"))
    (145231, uint256S("ab8884a43be4b0a19edcb8a6a3e0f77cb1e8893a92d16631e64cda6066e970a3"))
    (150239, uint256S("b9b36668ccbb6eca13fdc4cb167e15095802cf2fd0bbdae21ac2bad2148b9560"))
    (155247, uint256S("64d183ef6993c11fd77a45d3e6f7dc9e54694d4c271179971e4d8f9fd26fafd3"))
    (160255, uint256S("bd65ea641c27c9b7418e7983ef090efdd6df4e3bddb313b3cc007035734714c4"))
    (165263, uint256S("69cdac1f414b1f40ace980bb0c00e13db74d85b237f33f7d2c86a3c57618c611"))
    (170271, uint256S("e600a737e8e89e6bcec6ab4e07410ed1eb06807d9d7cf92403daa45d72beefac"))
    (175279, uint256S("8b3acba71e75b48eb6ef01d88e51f345acb443dad23754ba16d361421ab3be9a"))
    (180287, uint256S("006684362687afcd77b0b314e903b38002a12e88aa789b74219d1b13744b2d22"))
    (185295, uint256S("2be1a93e683d068fb33639f894bb76cdabf1244fe987f770348a5dda59ed31fb"))
    (190303, uint256S("14854d1e7d4a1785f6659c019e58faf0913f66d863418603d94e420a5200b252"))
    (195311, uint256S("e09c0496c81c0378830189964df780793266e0ff8091df1229f1cd366d3f7aa4"))
    (200319, uint256S("4207687eaeeae2e6d79eff184ecd8313aaea83cf7a288f77528160cf4a4880a8"))
    (205327, uint256S("cdf87b4286cd4151f2e2c21c5d505e2ab20687770a80e073749efecf89330546"))
    (210335, uint256S("d2add7cdf2ad93c484f0545d653eb6a19b12295044972ede633b7c26234a9d89"))
    (215343, uint256S("bc997a2a12ce393f2baa592342add2a7d8dac96647d0febb03836f47aa0d3e10"))
    (220351, uint256S("866084d5edba39c44bcaec2a2c69237fa4ccfbbd8da0ff38e9dcf38ab830bf20"))
    (225359, uint256S("992d3c4f9016daf09846be82e4d8ca0a24cc522fd7ec33705d8004c68a9846ce"))
    (230367, uint256S("a44fa38d89415904f9b91c66be40efb05e22696935c4139e8a7294b44597f75d"))
    (235375, uint256S("44087e5cde30243d83696291d32b82b52df718da2fc7d40edc42ec803b370c2c"))
    (240383, uint256S("48614cd246c4def709f403c732ab68e6cec4131851edede179787c2a30b5b16c"))
    (245391, uint256S("50ee9019401dfa591f27a8260a0aa7e5b558065663a9fe3f6ab38621289524fc"))
    (250399, uint256S("e5ed2c71132c45d452769ad774fcd6c5c09277f4b2baac22c208260a5f5ffe03"))
    (255407, uint256S("58d8b8ecfe8000ede3afea38b55a625dc6d1f7b5c3ef130ee8e36d5c53d6c0c6"))
    (260415, uint256S("ed42cb722bc0a8a23728917682fc8c132ca71e157ade1d1ad2acf2a9bed1ed63"))
    (265423, uint256S("266dff1eac1470459abf98296f9450474aa3107f6caabd7cf50d245034ea0572"))
    (270431, uint256S("2e6d734f952b011c8976f0272bfd9d0553b3add28b7f37fba0dc102e19f34020"))
    (275439, uint256S("96d2c13eefc4659466e098433ce5813af967f9802d17931519fc628392482536"))
    (280447, uint256S("0580f84ec1d970fc782911b7c61caa5c4579bee1653a617d0df952b957b5b257"))
    (285455, uint256S("2a99bec5ae15f28b913ecc5fe656f0fbfd6d2f64bdb32ce2ce1d622f6788596b"))
    (290463, uint256S("ef2ea57dd431bbc3223c7ac9c40ee6cf227e29cdf8b9eed6e8087eff55a688c3"))
    (295471, uint256S("5fa117ba87a4af42e88acf744653a886ec07739e914b3e45f5ddd795e7c78c72"))
    (300479, uint256S("10ad69ab0c2be051d5b6b71b9db2019667d33fd042715b22ce1f5edbe46a9a63"))
    (305487, uint256S("646f9694edaa0b96451e6b92243095925f73d04e387eef14e58c758d6d48efd7"))
    (310495, uint256S("a429f5d5a58687fc82c1be1f0c5751b17ba7c93f328adb79d724ba0dadac99fa"))
    (315503, uint256S("62de65156c69a2fe7d2b1fd6ee60cd6119b36bd0b22d994b122f11e661a096e3"))
    (320511, uint256S("32683a5ae19d84892e178448d306a1516a9ea03b65793b2644b4e3a823fd9ed5"))
    (325519, uint256S("51d1cb1b02f9959e840afcf8386c55b8864427221f724842be7b9459c5d9bf63"))
    (330527, uint256S("b440c05e6c12d01580a52fbb34256c1d8bdc128cae951b23ab022f9209c5a9ea"))
    (335535, uint256S("51aee32fe6317df0eb4980af30432a7e1c2fef78e36960e152186fc833ca5d13"))
    (340543, uint256S("3db3d4776f51805909842a06e18c9a2ed16441a29317e866e703beaff35aa011"))
    (345551, uint256S("b48ff8773642edfdf0329812c72b2cc85256ada50ef71eb730f00c118e04266f"))
    (350559, uint256S("2edcae094a5dc7ad20aa6b6b7b10aeba1c635c092f1eec664fa1cf875bc325e3"))
    (355567, uint256S("44f289de32713eb16ae0ab071620546a8861a4072fd327954a05b2ab63ef5a4e"))
    (360575, uint256S("0c25125d8d0d216dba27ea31754b71b1522fa62df5f3e0d9724935305656664c"))
    (365583, uint256S("06f9fdf89771089a0b4eb2979a2584dda62fbfe4ce24a6cff5fccf9ee36a206e"))
    (370591, uint256S("4007cb30287c6935659a65f3737362cdfe981081053ca4126643c3f35124856a"))
    (375599, uint256S("ee758eea4825c40f644c79eba42dc6804cb3351b46588160ee9eab43829b1445"))
    (380607, uint256S("5ab404115f20b064926f6de453566b74421f9037b7f8f52673f397517b152606"))
    (385615, uint256S("643ef5f2de628c0004cb15984f5e2d3b79114932f05d4b523eb29f71c87c0b82"))
    (390623, uint256S("88d5df279d0b2ac668752adee860e51b553635387ae2787f1a0682ff3df08def"))
    (395631, uint256S("c8e59f66d0b706ddc45c537668d4eca9c603dd5b865bf872da18b4ddcbf4dbd4"))
    (400639, uint256S("d03e3e3c74716674ca80113cec68587a92c2010051ecf441a41f869bc07cf2d3"))
    (405647, uint256S("e80a97c4034a9c2e6cea9aacde3832ce3326ec9aa7d09e8bdf79e425496117ee"))
    (410655, uint256S("8421636b7ba9ae74053be8db20f2a7209d58625268c219fffd89ba5daf9517fa"))
    (415663, uint256S("1caff73832b7ce95ea53a337c36c49731774ffffdef9d2375bd38c2883b56e60"))
    (420671, uint256S("061af6a0c46017b07062a8f583bd2fa0ef277fcd9303d13828a307b5f38d90c9"))
    (425679, uint256S("855294d579dd3b3b4bdc54d6a6b188e8f1a45291715f2f9cb895e823e6ec6e54"))
    (430687, uint256S("4da5b1b2b86bc37d4d595f63860270c2ab2f3bc0722aa196091115309f88ef36"))
    (435695, uint256S("f5e0178822637fb5b6f779c706b0ee2748fb2656c840dcf44c873e7c33f018d2"))
    (440703, uint256S("75ab79123e23ae43ca613b5697cd2030ac50d210b4bb069622a4c1bffd878f65"))
    (445711, uint256S("57e1a1e81288dded32bfe66518b734f7e7ac22f85b2b063958a22ed8630be578"))
    (450719, uint256S("773982a4b86c770bca495b4bf0a38c63e8dbd9e8a4560ea115669e4e65542ff1"))
    (455727, uint256S("c09faa0f7bacc881be7f858699ba7fed40ff5fb80717ab5f3764d372aef46ba8"))
    (460735, uint256S("09d04711e01f5c8b26ed3d5c5a30821762f7229420c9d4a5f16024c294471679"))
    (465743, uint256S("37cb7f33ac9cdf6965647aba278f30235c9e03a253a860a7ce29d4dbd3fb915e"))
    (470751, uint256S("7727c24b37d5d8e77320ec7f9bfdd7d9603fc2ff8bedfcf5dff6f0889ded6a47"))
    (475759, uint256S("cc0115a55f915fdf2fe6bbe65d97ee7ed27e6bbdf3731f7f00c754d03039d7de"))
    (480767, uint256S("a134d2eb4cf7e65c21194d33db8b368ad3c16591ba9e2e0d80cfb1eebfa97867"))
    (485775, uint256S("49d736520fd0367f93033f26a1e6bb3d93cda2b6808ed5bd5b3cf125219c62f9"))
    (490783, uint256S("7d40161eac3710edaae5596327c3abc54d2ebb3ca355c621634c7f5f2a44eb1c"))
    (495791, uint256S("f16e1aae1741547fde4cdba858cd533ac610aaed5e0af0d931c960eef1a9b9fb"))
    (500799, uint256S("8e3d1efeaba328ed4d134e696f39bbb00c9db42e13c6ce233d33d98a4753338a"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643148840, // * UNIX timestamp of last checkpoint block
    1193743,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2860        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1612360301, 882189, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"));
        assert(genesis.hashMerkleRoot == uint256S("0xad9cdf0829529533d9ebcda4f6981195860fdc01c7f6d3f14b847695835fc872"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
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

        consensus.nMintHeight = 550001;
        consensus.nMintValue = 34000000 * COIN;
        consensus.sMintAddress = "7BicbhE37YhQwmCMmG6qeQkK4USPzV29Dy";

        // spork keys
        consensus.strSporkPubKey = "0371d4e47e0ab43865206e9df7c065d6c68471b154bab3815d99f8380d46c7015f";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 235001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1bfd90165e662b99293bbe05a321377d0dc2f2bcf36d52e5abed63c4b006ec6b");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c17d7ad9fdc95b64409efd6c52054c8d547e72f0e3b5059c7148cbf345057768");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("8f53cb83a9d6dc495410377428e2c85cd80367456d55a82d64bbec5b0960286b");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7a8aa7d86ebf47008da5b39ba6eb07c380a6638a85d1a632de326a4f5238cc36");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("cb863ebd9d14c47dd733cd9a90b47e79a7ab82250a60fa6009eeaabf89778abb");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("b99924befe2810ac0a613e3c8b43c3d423b870ca3710cd81ab5f8f95ee316d40");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc8;
        pchMessageStart[1] = 0x7b;
        pchMessageStart[2] = 0x86;
        pchMessageStart[3] = 0x77;
        nDefaultPort = 17771;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.777coin.win"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 15); // 7
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 43);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x41).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
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
        consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint    = 999999999;
        consensus.height_last_ZC_WrappedSerials     = 999999999;
        consensus.height_start_InvalidUTXOsCheck    = 999999999;
        consensus.height_start_ZC_InvalidSerials    = 999999999;
        consensus.height_start_ZC_SerialRangeCheck  = 999999999;
        consensus.height_ZC_RecalcAccumulators      = 999999999;

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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 27771;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed.fuzzbawls.pw", true));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed2.fuzzbawls.pw", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet jackpot addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet jackpot script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet jackpot BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
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
        nDefaultPort = 37771;

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

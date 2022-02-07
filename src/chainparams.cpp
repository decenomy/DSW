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
    const char* pszTimestamp = "Ask not what you can do for your country. Ask whats for lunch.";
    const CScript genesisOutputScript = CScript() << ParseHex("04f3d4d3f0cb226411855ac25a2d47e63dbdfb4e6b26a3de453a21fb7824104ffd341826e14455a29c73760c0cffe31ff8d87cf82b494417a70ffcf23d9d02e5ff") << OP_CHECKSIG;
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
    (0, uint256S("000002be4a05e7ce86e568cd6d106daca9d80bdeaa6564701efc2cd25a5bd86e"))
    (16365, uint256S("691f28aa644942f5b3c2fbcbd7f4aec5f7bbe50a55415c338ebe5b095c99db22"))
    (32731, uint256S("6e0718e6f8fcef0fd77646e385aeac48fb7f49a9893287840d856359c8a9d3ca"))
    (49097, uint256S("ee7bf05e8088b852401d00ff95273be599608ae43155736937a26d6bef65d1af"))
    (65463, uint256S("8f8ba78c22834bf69a0eb94ba3b70635592dab320fbb617260a82f8b16085337"))
    (81829, uint256S("8b85d3aaa58699c44162d4591bf6a1f282b6e506432d3f4c83252bd1c48ac03d"))
    (98195, uint256S("b0593708724349447d48b5fe120579e6ed0f885e9eb65c885cf9f24740a99a72"))
    (114561, uint256S("3c33f472989376c668a7a9be0f47da3543bd038258faaef39a994e9317a89942"))
    (130927, uint256S("b4894d66a191f44380b5eedcfc4a21ed543b4610e30f103bf3be8871ada8856d"))
    (147293, uint256S("d43395245f51a016ea9a7b5882e1d16495162d487f358b595f843b22200e85fa"))
    (163659, uint256S("debb7a17fb96816b0234d4e388a19f8ccd2ee647ab4efccc3f0ce8cf68787f15"))
    (180025, uint256S("df51e0ee4ee8c0c36f1fdf685fca918a55b770d4b2e35d76f5451fdb6ebbd983"))
    (196391, uint256S("a4206f2a751a9506a595874992aff745e0c745b28656949d60668c986650d765"))
    (212757, uint256S("92000a2dc92008d58693e51de5ea3b4913db6b2cb76a8282ea82d59da30c41d0"))
    (229123, uint256S("8e40c40140aca7711adb6c6eb81d8c46d79d5001f29d049d761e3c9755803efc"))
    (245489, uint256S("41efc70f720dd963d601483cef129bae3ce6cb365cb6c8caee8e40558d35387f"))
    (261855, uint256S("327c179358f0fd9178caae0dbdc061e845d567955987f98d29c37e4c4008cdce"))
    (278221, uint256S("31d222f517094a5b1ac36dbf56f92d7ff4bf475f61e8210da4671898938cf612"))
    (294587, uint256S("444c59f74521c94401888c765cbcac7e7db0fabeee22c9a68471fb2fddfca1d7"))
    (310953, uint256S("8e2256b4f8ae96239209f119c802a5e9540c3356e0a6ab37c452ee243d168ccc"))
    (327319, uint256S("714ddffacd399d2702eee687573bbbca29247251bc757f5969777f3d4f922b07"))
    (343685, uint256S("9fc7702b3a16e9fd50761abcf891f1763798a4c6fdcf5e77e71f85456bcb3f0a"))
    (360051, uint256S("33425b7eec5a578b96ee616a0e5eaa5b025e352bbe0f0e910766ec3942038cea"))
    (376417, uint256S("decac5b3662529b96975adb941912e5c7fca4daade448e74609ff069cbe8bc42"))
    (392783, uint256S("970263753c149e643f0d93a501821c296ace71513867bbb861afd91b48528a28"))
    (409149, uint256S("9ebf7e7d0e0e1b5df2647bd5111a962490a1704104baa3dbc71914075bf71646"))
    (425515, uint256S("60ec1c09e68762ce45f88181870a7abc831a39f387985215d227ea1c9a069d12"))
    (441881, uint256S("a8eb6bb0053845be286f3ca0c04c1d5d7bd714753ca964d34e9caa705bb197a0"))
    (458247, uint256S("40ca83b5c4cea924dc341f061361e809402deedc9bf6e420734561efb7b68956"))
    (474613, uint256S("95a4d9067f5bf9be8b5281e60e815ef7cd0ce076b94bba51fac023434e1c0908"))
    (490979, uint256S("7cf4bb9511c027c5eae57e025c0ef965dae37c30f950704229fcfbe3c4adeea4"))
    (507345, uint256S("e061ad2baaaebc730aa8762f9323661c9fef0eaac7ca2430520421ed4e0817e0"))
    (523711, uint256S("f3996a1d4e0257ca3c0474246c512c0ff7807d1eaad376e817553c04ab739355"))
    (540077, uint256S("6c17903baec920b4af43c2a09729f3542a3d45fff5953c6f18beda39b81b18a5"))
    (556443, uint256S("6193595f07024cb604a525aa139b5faedd502bde528ebe5870194f28918f124d"))
    (572809, uint256S("64222462704a41148d5722e1d1e5465b8b834446371c2b502cc4424760aaad84"))
    (589175, uint256S("6a0691800e42ebfc99b24da296aa380fd27f9d08377ec460637b2698890fd5dd"))
    (605541, uint256S("186aa012b7dd7a488658dad7784a118eb69d37378a57ac91925edc3344485313"))
    (621907, uint256S("69cfa1572f8ff0f49cdf7653944aa46168c09ba023de465f0f6c7db6dee453d1"))
    (638273, uint256S("03e8dc53549bfdfdde372d1e0b68496bede563efc8bb0a995e96dee3cebbb86d"))
    (654639, uint256S("bb2d94c3ef30ef9d21abec9111c935bb9721be9f9c8571fbcf79d227a8d48769"))
    (671005, uint256S("4cf1331b7d40936ef1442d8f404b9a9cbdbf2be3e5f734a913e5acbf84907159"))
    (687371, uint256S("8bd7a16f6e870b4aa69c55d9e8220df8b932bcb88daf138742681fd62b4edd2b"))
    (703737, uint256S("2fce5b692d0358da1b57b795e954912d7ee5770872175dac4a1ae455fa65334d"))
    (720103, uint256S("f9c6b884f22bbdf789009e150aa873f4a17f7551ec8120246cbe7439265f7807"))
    (736469, uint256S("bba0c6eea2d03399b0afc67364f3055df1a8a4c7139a98426605d5582b622437"))
    (752835, uint256S("c5ee6cd6e9887b70c175224972264dec540311cfe656171bfd5b46e6e6c35a9c"))
    (769201, uint256S("ed3418f59267abd42e53eed531b27a2bf2196dad27ac5435bcb762f23a3d554a"))
    (785567, uint256S("e613412387f8fe32370d9b515e7b1acf0299cb9289e0dc2df007d9ca6a8c86d5"))
    (801933, uint256S("d574b0deacbd237b741d704020c0f1ef9a2d33bcfa827eaa1f187b15d838df55"))
    (818299, uint256S("516f76741a1bc4b09d44fa01acd7af4e1cb5626b4f68bcca3c2371cc0692d312"))
    (834665, uint256S("9ec3864fa5284df032698da3e97e6de32d309c485a1512da43843a8b86ae540f"))
    (851031, uint256S("198031afa4893ef7596e09a507ff0d3c58e6df5305a3b8e6b73c03e96c36d068"))
    (867397, uint256S("0210685ff6dcfa4bc5b6facdcfd00ec7edbe0191cf3b3d640ca1e47ce0859d46"))
    (883763, uint256S("e778726bab181aa0749b6c48f49464a1f8d588292cff40a4092fe75339cc75b9"))
    (900129, uint256S("1909f347e8bf2ddbb92fc788e30fa3e609955a512e9ee6429c990c21dd8655b0"))
    (916495, uint256S("bba71ef5ab36c5bb43b72c209e2ce72832144e4f1aa1229de796dabe312918fa"))
    (932861, uint256S("8ce8711e02b68c311ec83abe6d537f6c57bde2ce0525f9923a65b6eb14acc117"))
    (949227, uint256S("3c459205a9c738da63e47f7aea9b9749129a2aa6539749f1ae05e8c55be2be8f"))
    (965593, uint256S("4689b66955ca814ae3e22de35cd439e1d38d55dae013765f598c9e3163d37b8c"))
    (981959, uint256S("29639a51f55eb17ec2a2d21d2a02dc3394969627a0d3122ade1684bbcd2c057f"))
    (998325, uint256S("2cd4e249e13f9f9ef2fa4061c280f0bbf2d1f977905ee3a7813a5872c0587108"))
    (1014691, uint256S("df92f089efb355490d550dbd97731d943c6c9ceb7caea91c566376e05d029d9c"))
    (1031057, uint256S("327553fab047d375dc69c734a5a63d73158cf7ff3d200067446d57346337e880"))
    (1047423, uint256S("91b5d33a356db6fc9d2694e843702fe1de82e2552be7a126bdaff621a6f22fcd"))
    (1063789, uint256S("ffa2b64d1ccbbd0276d5ff832e2c5fd0b931d62373d18dd9bace41be8c23b4c0"))
    (1080155, uint256S("614d7737bd0791724c128f45d3161e566eecd891a09298e70053adc2a3f57c2e"))
    (1096521, uint256S("a41296408a8631cd1cbb512ef7c09b2fcd594d510971839551a43521414ddb8f"))
    (1112887, uint256S("4f70b80d9833ad9ade725f9ccc9ae7c96b334a11a7bf1a2f86ccf92f4fc62660"))
    (1129253, uint256S("9e1ecae5b73764992f4b972a89f234054baf5e72dae6fa5653ff393904aad17b"))
    (1145619, uint256S("d3ccdf8d9017d4c01b008ecf06c4e5c8c09ac689bfcce6e90d4d5793dd7b4470"))
    (1161985, uint256S("343db35a7c6290486e7e7087f10874466a9b71da73d74b7c124dcc2912781d5b"))
    (1178351, uint256S("b58c3c6ac1ba86f62df86612d5e14c2b1d6e4897f0df233acff0d563b3c43933"))
    (1194717, uint256S("c2477985b7634ddfe0883324a5a2156c8ab0d32c6bfe877fc29bf8ab529e173c"))
    (1211083, uint256S("cb943e236133da257f8ed2eb73ca84daba640b5a169222d01a3f575e785f517b"))
    (1227449, uint256S("171183b3ac6137c9eef560cb9d15a92bd6c9de7abfcab7d33625d6e8fc2d5d24"))
    (1243815, uint256S("5682da03fc330d0e6b290306461f4ba4b573d76bc79f8a733d969378ed52f99d"))
    (1260181, uint256S("0c3f13484b152f08b952b96a55c8062f3c33fae47ec6e70cf86d4d0b67493936"))
    (1276547, uint256S("7b8b5c6322f36678cc72733576190a6215338b6e52a72115a78ee0da1869f516"))
    (1292913, uint256S("4f39c779dc4dcc423a200ce5a7fe652515394d4dc8348ec94db05421575cf657"))
    (1309279, uint256S("daac2866eaab412be8143f326532c03c6b8ab73b69ec41cd037657a3493d27e7"))
    (1325645, uint256S("f4bc7edc9476e3bed34c430619e336317385e0f70499a9d96dc173afc7342b3a"))
    (1342011, uint256S("a2a85331f8d1c9881402a8002aef9b1df31137b88fa7add63d9d2a557bfbe276"))
    (1358377, uint256S("ddcb1577099204bc3b41cbd89a1c365b5d0d734e4cbe6c825db1350c0629ba12"))
    (1374743, uint256S("ad293ef31dab01ae348198437d51833c8d2e45a10b075866c7eb53d64cfc2518"))
    (1391109, uint256S("19519888061cc09f034a0b800c39b2e57e4f35bee1078368b2bdb86a223dcb15"))
    (1407475, uint256S("0e6d4cdc5481b3858f5ca2736d23daa57e59058d6aa01db57ab9305d5223a021"))
    (1423841, uint256S("1d0cd76a3088ac8115089786b077aa2603e67ff4345d9350cf7c953b5250c8b3"))
    (1440207, uint256S("6565c4548fda74088516793093ca28b50d8891134639d3bf42f8aed5bb113ec6"))
    (1456573, uint256S("1d16c2eca8f848a6d25743992c7f2239215ae2842c0f563f500193c5924a6b3c"))
    (1472939, uint256S("4a0842a91e0062cfd6459305b954ca3bb130b18138a348396b0b9986cb262646"))
    (1489305, uint256S("0cab6d495e971468595804e3277da0c662114295804efe43b2bee32cd5248a3b"))
    (1505671, uint256S("db49be90f1101122f34e4ecac30ae53603913ed581d23573232f910d673dec9b"))
    (1522037, uint256S("b7eacb60f690e805b87e59076786794cd0afb80f8ce8aad6fac60ebedacb9d3d"))
    (1538403, uint256S("6b65263679f58e6e31c34b05a3ab310fbc3c65f484efc393fc0b690c3bf9982c"))
    (1554769, uint256S("5dd2b389039048d7bfc44bb9dc759b80e87e1794984ba6684dabd3d5509baeac"))
    (1571135, uint256S("dae3ab6c65631d6dd031da982fc8967dd3277b1bd23a1aa504bb14a8478f2def"))
    (1587501, uint256S("6190538ded475fef26dbe1ec93b7938182eeb5210d0fb38e9a8943ea6c029518"))
    (1603867, uint256S("624d358715c62e0c630bbd2b46ab4e32460f46e97befbdeb7597f23ca47d4059"))
    (1620233, uint256S("59ea6005e39fac6b45b36ba4afc217341472d5e084781669d34b7344f45d2faa")) 
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1636734658, // * UNIX timestamp of last checkpoint block
    3419452,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2846        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1538310996, 3667246, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000002be4a05e7ce86e568cd6d106daca9d80bdeaa6564701efc2cd25a5bd86e"));
        assert(genesis.hashMerkleRoot == uint256S("0xa59340af760f1a7b4f816476bfff59dc858588c4cfd1557bb9f3debe718cf378"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 76;
        consensus.nCoinbaseMaturityV2 = 100;
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

        consensus.nTokenSwapMintHeight = 1650001;
        consensus.nTokenSwapCoinMint = 10000000 * COIN;
        consensus.sTokenSwapMintAddress = "PUxx7vSa88YY83QFWJiMdLMprkyncrwNJs";

        // spork keys
        consensus.strSporkPubKey = "03b64dac8c2acd3c69917968e5eb188fafd5b299191c261fbe41c9288ee2df3639";
        consensus.strSporkPubKeyOld = "0414F669AC091EDE9237A4B6754C34A60AB13B26FFA38CBF3E61A07B9C05A6E85BA4C8589191D45F7D45B09C0D2A17865FA2F16132DB1922C73EE3DCAB43EBBC44";
        consensus.nTime_EnforceNewSporkKey = 1638576000;
        consensus.nTime_RejectOldSporkKey = 1638662400;

        // burn addresses
        consensus.mBurnAddresses = {
            { "PXXXXXXXXXXXXXXXXXXXXXXXXXXXVtkn93", 0 }
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
        consensus.ZC_MaxPublicSpendsPerTx = 7;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1538310996;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1650101;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1650201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1650301;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1650401;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1650501;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1650601;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1650701;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight   = 1650801;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("286cd24e42aad7c862376843474886f0463e458c172c40e0e5473bdf06a876f5");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x64;
        pchMessageStart[1] = 0x32;
        pchMessageStart[2] = 0x16;
        pchMessageStart[3] = 0x08;
        nDefaultPort = 15252;

        vSeeds.push_back(CDNSSeedData("seeder.peps.today", "seeder.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed1.peps.today", "seed1.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed2.peps.today", "seed2.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed3.peps.today", "seed3.peps.today"));
        vSeeds.push_back(CDNSSeedData("seed4.peps.today", "seed1.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed5.peps.today", "seed2.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed6.peps.today", "seed3.peps.today"));
        vSeeds.push_back(CDNSSeedData("seed7.peps.today", "seed1.peps.today"));
	    vSeeds.push_back(CDNSSeedData("seed8.peps.today", "seed2.peps.today"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55); // P
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 92); // e
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 117);  // p
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x2e)(0x21)(0x71).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x08)(0x25)(0x39)(0x2F).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4f).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peps starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

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
        nDefaultPort = 7777;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.__decenomy.net__", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet peps addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet peps script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet peps BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet peps BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet peps BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peps starting difficulty is 1 / 2^12
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
        nDefaultPort = 51436;

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

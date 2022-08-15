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
    (17443, uint256S("1a00f930cd6ee863219425f50fee814927063b6f8c491cce2a6dafa67d053e99"))
    (34887, uint256S("8c845800efc78031ba1d16dacc2c7e38f6204d752cdefd5f7e25afe04e12c8a9"))
    (52331, uint256S("80f0b0fa1aac9e3412f3f7dfddf4743f94b20f9136faab2a4103c521e6bacad1"))
    (69775, uint256S("e0cdc54e58be559a8e34d8baf0f42982c44f8901c3e5be2f4dd67739f1cb52ce"))
    (87219, uint256S("97cab9a26439c97bb53fbe151df09cd59d01144d73d0964381d384ec84760c85"))
    (104663, uint256S("b888f6136c7769abd90ad72b319ff4679d554bb1e4a144bc83a75710a9f4bce7"))
    (122107, uint256S("e85c36221cd5c129f37db7c4c28b20c706a55086e5a5e299a4145f2c60f94220"))
    (139551, uint256S("f6d28f74c7d17b6c3074090f8fd6bc2d8c971618cd4927631e4381be430682f9"))
    (156995, uint256S("aec770c4f713e08e98e0588a347319dad8c776f931c2526965fd69ebd18ba4e7"))
    (174439, uint256S("b902c212783b8f9e766b26501eebc33534425beb7c4bb07eb345994cc85b7a92"))
    (191883, uint256S("8ca28ac807efc913fd0636536464a86fa996eae1e0dc4886f58d9acafbee6983"))
    (209327, uint256S("b855e2a5e665f0b0d75e8343d2c9d3d75f5a752e6c7687995039a59ebeff2721"))
    (226771, uint256S("184f3f28a80879c4cae525eeb943544486c62565be4afeb7bd7f84d0c8b761d5"))
    (244215, uint256S("0f22dda63905c5e1111473d7cff94cb99245c69e50850b375dda83e8c11c2fc0"))
    (261659, uint256S("7b1a85b35365ddd8149895a1f8ab7cd8b951cfd28985ad63657a4584c1f93a51"))
    (279103, uint256S("e65185e866c2d62c1f3236082caa3ebbb999423f11fc5c350052c7c4b89cf5d3"))
    (296547, uint256S("95523d3a157c310a56478d54d209b01e9f375580a99288b798390e6d9df46802"))
    (313991, uint256S("405edb2d4c136a87deeb4266369f3da7736bdeba8cab9d6581e9118bbb9742b4"))
    (331435, uint256S("cc6123c89ab3224c1812f5651f7d774e7a66a74945b5dd31c9804e6a69042086"))
    (348879, uint256S("89252a24678727e72bc8dc0ac45bfb6d242c8dbd277ad43df019c070da5bb5a9"))
    (366323, uint256S("3024d3d9f6171bb6b70f9cbdc99687521bf8b7aa9169a0714845755362fa2226"))
    (383767, uint256S("2a8f06b7aff25f6bbd56fdbea80abbbfcb5721afe91f7c73881c00e392f3ea7a"))
    (401211, uint256S("9e206f70ba1babf7f4b6bca961f99be173f0dd89035828afdfa0374543acbd51"))
    (418655, uint256S("a15c46491491ca91c93c75023df2a651fa7eb9876d5fe7bcbe190fa236239eb8"))
    (436099, uint256S("0818ce6cf13fb86d1818dd24f4adb2bafa3197346a92370e708e248a01bb1bd3"))
    (453543, uint256S("dc50b80062d3c4f125db64205a5f9ff2c0a71ba6d50070e403dc532f6e0c42a4"))
    (470987, uint256S("41ff1a67f75f2156a001d3294459ba9b1b98bdba8f47283281843d0442259492"))
    (488431, uint256S("47dbc06ab48dff62cc12d27d5488aa51bcc6bdb1c591d41e74086b8dec7baa81"))
    (505875, uint256S("14ef563ecd52a8cfbea23efce33aee52eee013965c58008a979f8f272f087231"))
    (523319, uint256S("08ab0f804e60232fefee5ff8aa66c7d7332d23e4c1eac43b33c5a03ddecf9411"))
    (540763, uint256S("fd12bf589783ed207b2499a1b513a27a12ace739b14cf6ce271929b9927022c3"))
    (558207, uint256S("1a8c6655caa4b7477a64f49b62d13d82e9364abe7a62a2e19dc1110b506bcbb1"))
    (575651, uint256S("0d42c8a93392ec3b7e9a4ad150fa2b4585706bc21e5f99367ca316c63c85643a"))
    (593095, uint256S("b02f2b43ad09f8b95961d72f8a452d0fde4f706b03bc284f74a6f58264f88475"))
    (610539, uint256S("8638564ab46f645925bee4c8561b8e59c9f15c742f815e29ace1cb3ffecacb83"))
    (627983, uint256S("86cf5a5e45d23fe108bc86ebbbc2f65d29bbfbf178699b6bbbdbb5da16c273dc"))
    (645427, uint256S("2f1b0feb4552579fa0b72321da55543522b44b78fbde510d5b227913eea83ebf"))
    (662871, uint256S("d0db87db46b7bf4525d95344dc7f629b7dd0945e04995d84fb56f1250845664e"))
    (680315, uint256S("85a7514632f845a3b47533e44ecf1cbb8b3f52b001431bf01aa697923dcab75f"))
    (697759, uint256S("551646e719be3c457cd019c669f8e8e297ece9d9e07db11417f882df5c148bf1"))
    (715203, uint256S("345580f4bfc38ef4ef6575ab40522f268b3f32bc3499eb0a11bef77f0048a8b8"))
    (732647, uint256S("e67668555ba606d83692a4f979bde0f4a8cf3b79e654175a53179ce9fe09a510"))
    (750091, uint256S("2c537a25ae50a156c97068f5ac5ecdef6ae89aeb069891f60754d5ea16848633"))
    (767535, uint256S("9b7fb60780d5708e6d922a262571f7b97d73b5fb10440fc32e52aa655692f982"))
    (784979, uint256S("748526fca4964422af6f87f47f9aca265e02c396319b15e5243873cc7dbba78e"))
    (802423, uint256S("bfb24a56f292b0fc23b475154c810064f3a209a539a66a5978749fa034d95363"))
    (819867, uint256S("80ed5d0bf53bd2b531298793aa108ab0b0f0e3085a643142ceddd1b39c908e45"))
    (837311, uint256S("90178f069912f91b66dcf0ed2c184fa7bc92df1e9f4cb92be92ab5280e522b19"))
    (854755, uint256S("b6d46b63cae39216477887f3ca35bcff4e57b6a757c73d00482602dcb3b29a8a"))
    (872199, uint256S("569c57bbf9d1e8f57d642f7e8f49f6f3e1ee88c74650e5b19a53ac6a20630c15"))
    (889643, uint256S("76919512db05a1252f9e94d19de1c8988491918a473edfb03a8d056f3faf8664"))
    (907087, uint256S("e8e1c7f08c5e3025ce22be790cff136d57a995868a4e803ec45b9c5f470b0698"))
    (924531, uint256S("d5348dfbb969479192b08bc76cd1bb4f45fc90fb20a8edc57e55212e5b9bcd60"))
    (941975, uint256S("b8e50cf7b7c24c3e2b7708b9bef0daaa46ba833098811918ddb1b0cbc16443d9"))
    (959419, uint256S("3b30dacd0363dc07054d73f1cc7fc7fcc62429213880ab94b0ad3e4cee44abc5"))
    (976863, uint256S("afe33fc3b0c9faf701974647e0d90de7501f58a4de58f7c400e6306af6be823a"))
    (994307, uint256S("13e19557840c170d18bc6b88877ffb98c65f3bb30634fb553273aa0ac631cf36"))
    (1011751, uint256S("18dde7fb3636822a684d9eb88eaefbafc29b1ff7ab28fefbff3ec2dfb5c589de"))
    (1029195, uint256S("68e691d0b9de58d27a04458815f1892af1ed1ad8730dd39b779ff01e63a1aa18"))
    (1046639, uint256S("bbd8ba436f9220313b6fde98b7f264681c95bc6226fbb16eae18373a19a6664b"))
    (1064083, uint256S("38c189054203ebe7c789e540fad7a81b93b485017b402d455263b7fa2b89b665"))
    (1081527, uint256S("723104dd3c10ca4ddbf23db749ab3af04a37dc3340c1f6d55493614c6246389c"))
    (1098971, uint256S("e4c554db1671eab9a27980f5aadafc8d76dc77d78aa4e9ae0c60e046a7a75ae2"))
    (1116415, uint256S("9c12583ad7c3cb97eece0bf05c0539a76d6e2bad0851bf08f34bf2a7d207d9f3"))
    (1133859, uint256S("5ef812220edf56838192296ef1751f5e72f9b2ed385cbd924a4a3344bdb38e68"))
    (1151303, uint256S("90a604181a28f1c9b59179ddcdabf7651802e548f2f1a1604c2fe99e2af69cba"))
    (1168747, uint256S("58a22731f99fc03c7f30984f7f893fb516acbe51fa2e6812fce1ce007a837e01"))
    (1186191, uint256S("05ccd204488a36217d32da52c9ff37ce4ae3ed31f400e24154b8e32d5b4ae02b"))
    (1203635, uint256S("0454e45190d58866a2c74ad6bb85b7a87048eb48f7294b15e8b10bbdde85dca0"))
    (1221079, uint256S("c954b1eb6f6453963a88b65014b109a3f154b42d40085ad5b610e8629278efc3"))
    (1238523, uint256S("ae2f77ec9d6a706ade4ec967eae916c65fb8ac83e269ddced49b74d0edd597f7"))
    (1255967, uint256S("accaea3fb4430fce51b01488f688349ddf0946ba3585aaf341af783ff0ad39bb"))
    (1273411, uint256S("0a2554b7207436306f0ee3238049ad7ae5f538876d63aaec65d821722b67b682"))
    (1290855, uint256S("b15df8287b4949d015acf08fa243155ddec6ab33f7f6d1732267d5c64f60679b"))
    (1308299, uint256S("5ba2d9c99804047e73dd4a307f10daec3c4f13424fa5c9ac44427bc2e7ea4e9c"))
    (1325743, uint256S("d0259c6e0e47065b8e2ec06aaa824a48c07770a631e2bbbaf25cbf4c0d676671"))
    (1343187, uint256S("80d0f3358ae4547b64f1b412906d640caf80214aee7c75e27128ec6f71a78078"))
    (1360631, uint256S("e308145726781d1e0f828d94a9d71047343772049b2a1406c8bb19dba659679a"))
    (1378075, uint256S("19c0c1a7f46b98b5064a8d7d9f7b4579cae5452956d02c56b10ae4d8ce922bf2"))
    (1395519, uint256S("5853ed0e25cf44116ee3468700b8a162b5f4700281556e68cd3d4db8406f3b2f"))
    (1412963, uint256S("2c291170ddab166bf889b890a24f9cdc84b441c1f1f9ab2b81935b1a9268b87d"))
    (1430407, uint256S("8d78bee2d5794b5444f466ba4b140481b4dd74d9ddc3bc6ebbd1cde9777f6059"))
    (1447851, uint256S("9624d8bee2aa40ab972f7a0197e3d489dc4249e7081de47b01a598ebf4aa3d5c"))
    (1465295, uint256S("9272a6083cddeda33a3a16ba9459bb04ebc99f180f9cf481274001b5c286ed3e"))
    (1482739, uint256S("3a58dc3326faac11ac641e0887573e08a1557ab859b92371912fedf704a91e81"))
    (1500183, uint256S("e06c86148fb541c7521b7c0bb5420673732e4e9776e07538e5ce6026a35d053a"))
    (1517627, uint256S("93480f0202f82d85c656aa8f4cc8e6742297c059ea119d0daa32e28eb3359add"))
    (1535071, uint256S("3166acf463ead90387ad3a7537644c77083f86ea6a0d3e1bd430e396d0c38c90"))
    (1552515, uint256S("b5751138fd2203eaf0aeea869a2cb5d763edcedb191e7bf9f124b38652c04f05"))
    (1569959, uint256S("15a6a6b40f28b48a506d915a894c1581476af1066bcd2d685f86bc982ee23ccf"))
    (1587403, uint256S("7828e0d5f593c3d3da081a774b3e1ab75a4bbefa8b3e4d8f49ebea22a3ca5a8c"))
    (1604847, uint256S("a5e5e4eef426fe0899054a21dcafa94342e3d43c90442e92f919e2683ae89258"))
    (1622291, uint256S("8a0509f7a1ed0135864bdc2cc42c082ff80431234de90a9dabc11660ed71cd23"))
    (1639735, uint256S("a0407c06430f549900a915b8ebf1d940fa29edc7cf2a53fa10e28bc246b3e6af"))
    (1657179, uint256S("6ad7d5464aceaa778bbe80bf1c942e4e76de3165d7572b62a4af18b8bdcf467e"))
    (1674623, uint256S("c9f1b4053247d59eebc78c00bc147142a995c6f1d7e48c912cb4de77e2ab0acc"))
    (1692067, uint256S("bc136ca10c21574ec1e003ec1e9596ce4481d6bab0ad528ea7f9b3ce6e3acf7d"))
    (1709511, uint256S("f0feafcde2db20d310524825e797a785566435abf4453eb7d18a0631e88f74ad"))
    (1726955, uint256S("610c3cce1ef7f9596edc4af620984e4f5b8a1be369bcd6e1f95e9f5a91b7ab3f")) 
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643258925, // * UNIX timestamp of last checkpoint block
    3646946,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2836        // * estimated number of transactions per day after checkpoint
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
            { "PQdawbkogbPqKWNfQ5WUdgrJeq9nP5Y1tT", 2008645 }
            { "PSdb6vuvsZvu2v28tzhUSdFDLZtBTmCmRY", 2008645 }
            { "PX9U5ogR57D38zFQWXyKz7GHFnNFMjHGet", 2008645 }
            { "PJ6bmV2vjKBCf8twBh4vvtrEEt6rjguzJ6", 2008645 }
            { "PJLfihK29Wro3rp8H7pBMw4kWDo8dXsrnj", 2008645 }
            { "PWJn4eCpxL9YEy84vTSELG6Yf2Lyjy4B46", 2008645 }
            { "PHRkNodFMDApFL6KrCsJv6X7ykHXtRtFmG", 2008645 }
            { "PHjDdS7mXor6WSgg1oCa1gfzcnF8fVf3X7", 2008645 }            
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
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("a8953c75d8e353d60c8d593de57cf6b9edbd9335bc73d0579c98fa8ebfb5a484");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("993e0cf1a9296753129b887e70d01aeaef96020c58469f62f2ba111926f14a42");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("2c23c620d5c2e8e7eafba0d930ff884a156ba42b168f2aada7921520b4194e4e");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("b6cf900288be4348841d91b926b3f34dc06d6d79c92d7203680fa35692d9cb68");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("529da67f86dfefb510c4e640c3a21ac2f164b0fd02472fac4ec72f32311edd68");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3cf8561095e7a282e5d67e61411947a384c612b2790a5d6585066ef1b955437c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("b07b244e8cd962ab90bcf103a58d690378b039da66089cb239fe17aa3b192496");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("f5ad1925af9b9b00728756b383cc00f0eb4f9860e31afa34159f0dcef65cf052");

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

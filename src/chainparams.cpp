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
    const char* pszTimestamp = "Its hard to be a diamond in a rhinestone world";
    const CScript genesisOutputScript = CScript() << ParseHex("04269d7e08ec3f33895e990cc9d0df716a860c1165f0c4108a9d5e0ce04dc93803606b1b30adcaa48d6fce12c676aad91a9117aca59f7f60f56a1369d6fb2e9729") << OP_CHECKSIG;
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
    (0, uint256S("00000e474f09929213ecad858b8c24002f8146cb459b98e5f665c27eea85f279"))
    (9960, uint256S("8bb09b60b59744279a467edb04de9c176e3ba2b039fbf9fc3606ba3e84030a0e"))
    (19921, uint256S("ed74782a51bdc6edd5882bd1fda0c581fbd74f67b7294d84cd046e66d76438d1"))
    (29882, uint256S("dea6426bd2dcb44c00aa912cb5c98631eff338a2f05240716dae2e6b2316c3bc"))
    (39843, uint256S("d48bea196a6d1f7d0e0934ca0d020c9caae4e0089ab88c7aadb2097e641a6e72"))
    (49804, uint256S("3d380b08173625a1861064ce4f0f61eefaedfc9c65f9605652f57df53113117d"))
    (59765, uint256S("b4d84540e0b49c9de0bc14d475fd8bb8332521c17466abe3516ecf64f6b3fb90"))
    (69726, uint256S("34bafda7481e3fb9cde4435efc56a035b66de9aca2d5865ecc04467417afdd7a"))
    (79687, uint256S("f83e480fa8af18b194919097f304065914005c03b1b7a97a3bf55672aaeb3784"))
    (89648, uint256S("6f0533701018b730d29eb37d1a9258d241b4858846833ccf43b3efa4b92b67c5"))
    (99609, uint256S("199f4faca6b05315b65931cfad6442fa4f8c3f35f51a3149c7bdd66f8b409a05"))
    (109570, uint256S("faf5eb1a0e5b548d72568db2880afa0a518cd4a8ef028e233f9f39b4cbdd0875"))
    (119531, uint256S("01fcb5fbbb490e550956520cb758585abfd40a24cd5cdb56a1edbc9625fef323"))
    (129492, uint256S("ea2d1675f2de1e6cfdce13f99d10db4b14527b5ffda50ae1d751bc961e184237"))
    (139453, uint256S("6a5cbeae9162ddbb09aa2e5d51a17b5b9c047399096f28c991f6b477f172e946"))
    (149414, uint256S("c961b0ad879db0df76780eae30c3e8004bb0f9379fff1f2e616163a516d966ab"))
    (159375, uint256S("15afa7c7baf0c67df0df5c408672030bbe7d8c15f0635f3cf26a446d5fb13478"))
    (169336, uint256S("36ce9837faeeccad1da5f4123b3c924c83f0cc5b2439fcfacbacc970678220da"))
    (179297, uint256S("0a594adf34664c16ab3cf9cb38fab513e96fce2cf85e3e10ccf44720428e9431"))
    (189258, uint256S("bee4791f9571fbf49acfa988d565f893db3253e90f3e086c1ea9883f86fac905"))
    (199219, uint256S("aad7bb7d4106cd4c53242d882f4a32dd5c2897e47f924ce18cac1715d5010982"))
    (209180, uint256S("3695c26c964f3afccda982cf836eab3be16e9d94d36d67045b8fca957c26f8ba"))
    (219141, uint256S("3d9fd69af7432db22238f8694bab6a928da06e4b7c2d194c167a7d6a3fe6c9be"))
    (229102, uint256S("03f4827b9ac996747ce4b2f7c3e5f2594a22fe06c97e3215a6a8eb7efc59cccc"))
    (239063, uint256S("7bb8c36e395c273c65ac08d974e526d34bf34c89a812298b856bd270b7d0c124"))
    (249024, uint256S("dfebc973368bb4ee507dbed89776de3b7cc0852bb683c9339965498b92adc250"))
    (258985, uint256S("be50d950f8f536a654914cc25b0165f0320efef068c573fd60f4f85d63a3eca2"))
    (268946, uint256S("456e1dc14ab185e2aae0c616d7de8ceae22c7f1c33b16313d1be57c33673b0ff"))
    (278907, uint256S("991303d15cfedc46f71409be5161a435e8fdf7bf6882bd7be7a768cb7d14a520"))
    (288868, uint256S("77249a8131bf2f1b4c7a9c278fbd9ebf404e2e9c8deea49a692ebe3cc772de0c"))
    (298829, uint256S("4d1712bb3e609ad5112ead0fe1804d6b9e7326e4dc2c91314abce11cfd885877"))
    (308790, uint256S("d0d1e9b20727dc9bdfb15b83fd6997b90fb3ef37db437d428966bc3b0bd303c5"))
    (318751, uint256S("fc03f30e0b116682f6f7c8f2532e64e91e131b8a1b7155d854277c963337a442"))
    (328712, uint256S("75f8abe1222654a4f5adfcca0e7753c93fa88605990e0be0301702b211f8bbbb"))
    (338673, uint256S("4d855a678678210a65c706e9f5492dd90fef409791edca7a14c5a244127f956e"))
    (348634, uint256S("0f2c34f027037f5e627e18a83fa6db19e64712b4db2b9f63b436663f65e58152"))
    (358595, uint256S("5b0740a90715822b190e71a8347e8a25c849f3095c2f9b87284e7f394dd6a4e6"))
    (368556, uint256S("6ca228abff2d7c7e0daac57a83fb5094c4661ad86f55bec15ff8afdd83471a17"))
    (378517, uint256S("3f2f12a8dcb3f3cabb2e39b68246ec572d1829c5f5ecf30b1eb5777ff83bec9d"))
    (388478, uint256S("ccbca9489ca9c2ce999ecababfef5846e112e2119cfc6557151bb3e8e382c0a4"))
    (398439, uint256S("e3494333cc6fcd6e8fd18181c4d451a43d3285efd79eba456afee7f2d6a8dc28"))
    (408400, uint256S("82fb363dce5ef237ce1d8880f8287587772215e9bbfa67620cf453a5f0f109c3"))
    (418361, uint256S("effec6d28af820f283244d34aab6b311051db85c4c01cccfcefd6d06e72f7a00"))
    (428322, uint256S("3fcda7d965d1924405aeab75ebfc0ccf8ffe5e657f50a1bdb117dff85dd615b8"))
    (438283, uint256S("4680a5a37674d82d15890bff7d9282d23d62eb9c1f514c6d779c143d2a5bdce1"))
    (448244, uint256S("1b087d3ad6e37be96c539bc21d6b54e5b364642db1d579dfa89e403d16d93387"))
    (458205, uint256S("9e55356559503ad91e2c59995c1e70dc1cdabfde8e735d59a7f1b9192bb288e8"))
    (468166, uint256S("a3370d77ad4f4fea2ddac04b3b03bb1f53d9a54441d2049d2e64c95b089c16ba"))
    (478127, uint256S("02e77365fffc86a9338fa5dd1586f2e908d5b7e7c86cc054dd148d4a327fcde3"))
    (488088, uint256S("902f22b43c1409ae2ccdc33ad3de048203bbb0a229996340f7981a9aeb44a121"))
    (498049, uint256S("fd97a12c0d133dc0114f74c262724807945710f0be4eeb873688f161bbe053b3"))
    (508010, uint256S("6e4d1f40ac79b7daaf40a8dd4bc786e7678c08b3d85ef5001c639852732118e0"))
    (517971, uint256S("c8dc80f05f33387cb74d9e82d3146bff8955a4feee78c5676e7b26ca5c329204"))
    (527932, uint256S("c26f510ec68ba9742977642a6fe53ae1441a26a37c34b2b11485628424b4ebb6"))
    (537893, uint256S("ba11b7cb9bfbec5cc0109e25abb1a02f194c26f2a0b80f737c7c46e920af796a"))
    (547854, uint256S("c29d83c38f19ec378e787ee0c4e2a01f59b73e2dfb86e24a5c141578ae7190ce"))
    (557815, uint256S("41ee35fe3a7b05567708074f637111ba836bfa96d9bd5d22790b838e14f42144"))
    (567776, uint256S("fda8ae8c2b2ae1a8e9153528c65a782833ccb15021d63e253c193c6d41e92420"))
    (577737, uint256S("f8bc905fd4ed2b061e59e2114ef8bd2fa39200fb75cb634689a8312dbebe4cfc"))
    (587698, uint256S("b60e21861f55873700da22960bbaa2396d84796591f86375b3cd1ad66d389fdf"))
    (597659, uint256S("c9d2b10171cc408ff144967d0c5c21c165ca060b6b71afca6ed0c9faf221e037"))
    (607620, uint256S("c1ff9c0dccc4f449700d16d0ad3bc60b62dffbfc3f985a356d3d73fffcf68bb2"))
    (617581, uint256S("80535da8c735dc7c9f39aae3717f2cc35b6c115a58a76b9d01b9aa99f98821ec"))
    (627542, uint256S("7a95e6b0c1f1287245bd0663da8113d6044314a7c80932d3ca8d6549965c1976"))
    (637503, uint256S("4bd09be3421be4ee1f4ab29756f4a426c558df8b29249658cabac89cf89dacf4"))
    (647464, uint256S("052291973087a7c149cccfc741b6587fc8dab89d04877bb9b405d53422cb476f"))
    (657425, uint256S("9f1d446a443deaf55456e3092e2feec7e015d4a8549bc72322e3d653e7dd6b5a"))
    (667386, uint256S("97d2ea6aa1b3dde9e7c30c0838a538c9a76de68b2c19ad2f501de5b7124f3a40"))
    (677347, uint256S("dfbff7e662568889ec8e0a00269688bdc74fbbb87604db25c8b6c4a9423c8f22"))
    (687308, uint256S("1a3df4c4bff75d7f4710aabcd36cc96253b6c28056787ff348eb1aead59a4e7a"))
    (697269, uint256S("eae068cad67ea9dcb0bd948bddceaa08ea96e6eba8786b3eb0db70fe8faac08c"))
    (707230, uint256S("56ff470040175f789326fbf32c26a0bef88a692cdb6cf74fb42e40d89b2ad461"))
    (717191, uint256S("90ac7e2d633fbcc8613658910cab1e127c96f31fa80b7a5805128d0eed1c1efd"))
    (727152, uint256S("20410e103cac537370a9cb9a557636f1e515193bd055bd009060a22be19098cf"))
    (737113, uint256S("e9a22d4551ca66c7d910ae3c581c87d4930d4b2170ace7f687c429b38cbc2f58"))
    (747074, uint256S("b8f843b98d170d4fa324ae4c498b87586d5c3c708a6e9c3851d168bb6527adca"))
    (757035, uint256S("729b784e9320c8e2712cbfb952bf2e90a7242dcfaf3f2591c756bfcbd610fa2f"))
    (766996, uint256S("4eeef8c15499b434d2e67cfcb0892ed7032eed98fc90a01fa0d3fab6a57ffa38"))
    (776957, uint256S("eeba2cbccda5cb33809a61032d89bdbf2836e9e6afddde11d7afe153dd1a415a"))
    (786918, uint256S("210b0dbecb42bc84fe3c15618a9b6b281699688c19be451d1a41ef7d80b84b87"))
    (796879, uint256S("67b8949db771d55e1a225b2ccbb5064e644a00f20cad940f37f414aadf2bf427"))
    (806840, uint256S("b9b778980e274033fe1482fb125f0bfcf8f2f6c0b703edafba223a644cb1cb99"))
    (816801, uint256S("721e9e88b27a81074b50163d3759f0e9c5d03b2ca3a9b8081f122e1127831b5e"))
    (826762, uint256S("6caa9a9079f7d27139741fe8aafb51affc27f1b9a0f58a45e0e1b8f9b02bba02"))
    (836723, uint256S("370b6fe28c0ecb4beed8f07ae2a52beece66d37a2522d19f2dc63ff252831ca6"))
    (846684, uint256S("6af5224305d591be06d3e711d92009b690abfdbc352a82db1f5ea01f7beee751"))
    (856645, uint256S("352ce796bd1e03082c83fd0d185e38a34098fd7b80d26728cee775a238653c31"))
    (866606, uint256S("ad46985e6c9cae196a6f18180e1e2436fe48647e762060b5aa3db1bcd7373286"))
    (876567, uint256S("52a2e3aec2fbdb5cc5b124cac8d3506e0f447f91ad940652d336bb7b7e2df6d1"))
    (886528, uint256S("f77b3fba6b03e41c7ea773c138ac13ba5bdc3f115d8a97659379309d3e0d1d4b"))
    (896489, uint256S("9f3bbd028c6c1411a273ca1833ed967029204135563464622cd0c198fc47b504"))
    (906450, uint256S("dfb5ccf8897b8b8f9c4700126c1de9553b085dbef88f6ec9659a1763012c4884"))
    (916411, uint256S("fa9d9f157ec430b6785402ded861347f699de2803b851f719c3379b7106311cf"))
    (926372, uint256S("5600a00c1e52034cedb5b57857cec0275711e93ced3501b94560a5de56926699"))
    (936333, uint256S("81e0605c919c8c6102cdc3d94e52ee96cbc7aac9b1306555680f1f00b75c4e14"))
    (946294, uint256S("dce97b35b82be33c7b486f7c20ffb78083b1df0200c1e28a40a2cef9ab5d681e"))
    (956255, uint256S("b67ee3ed52cfaaf78b1a7979760b79ce24bc448c10a7ec408ace82a428d9d3b8"))
    (966216, uint256S("7e2dbdf3a4f865b9c10e1bd40629b98726728b8e7cbf0582adc5fd7c1e377b12"))
    (976177, uint256S("4339a94abc57dd0421d486d896cdd8d098604944a84dbb1707d070865646289f"))
    (986138, uint256S("2fe5882c719e764cb5438e39b8a8d627fceb6af80d2f5919db8f4b38d5b0b032"))
    (996109, uint256S("0a9e26e68eb67213312f3e087b4317d43ce924453ef256561fbac789311f1e52"))
    (1277504, uint256S("724029d5a1ccad7b843e0ca27c67c3fb543985b7e1c38cb5a551963a46fb68c1"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1673366715, // * UNIX timestamp of last checkpoint block
    3612539,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2880        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
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

        genesis = CreateGenesisBlock(1567042340, 1911933, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e474f09929213ecad858b8c24002f8146cb459b98e5f665c27eea85f279"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 15 * 150;
        consensus.nStakeMinDepth = 15;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40;
        consensus.nTargetTimespanV2 = 30;
        consensus.nTargetSpacing = 1 * 150;
        consensus.nTargetSpacingV2 = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "02d8e66d000dbe1c014cf7d0a1fe89fec297d78603cb5d0b1a17ec0e6809e9271d";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "DBURNXXXXXXXXXXXXXXXXXXXXXXXYnc6B1", std::pair<int, int>(0, INT_MAX) },
            { "DAbELx8FfSDcX6qjtLCqrFn7HBDkZ1KNAG", std::pair<int, int>(900537, 1300000) },
            { "D5GAzKMg3yg4qmd42e3e1x8scy9QxSBnhS", std::pair<int, int>(900537, 1300000) },
            { "DT8EJc8uCjp69Zt4DjCdJfFYeBjZSa6zQr", std::pair<int, int>(900537, 1300000) },
            { "DSKZgtey3TWnYLeQBxj138yJ2yt822u3gv", std::pair<int, int>(900537, 1300000) },
            { "DGkqE8zGK7vTxJEDAgE9onrQ6NW79tjpi6", std::pair<int, int>(900537, 1300000) },
            { "DBCwfTHKj8iUYRd9i529ssUcBRhBVinjx4", std::pair<int, int>(900537, 1300000) },
            { "DJoXpFsuuheFLrkvoYhCHQH85Eg1jhUp9n", std::pair<int, int>(900537, 1300000) },
            { "DD1uDEQWMWXfavbnZjAbiRZNY4N3zCfsqJ", std::pair<int, int>(900537, 1300000) },
            { "D8UwYrzy2LcvLGJQ5WhEosFV27d3EAfCn3", std::pair<int, int>(900537, 1300000) },
            { "DE7xCPEGNFxG4tsmrffZo8mjUcJFv5rqJc", std::pair<int, int>(900537, 1300000) },
            { "D6v3xH7duBdMns5wPmqxkQdSygLCDVGxGW", std::pair<int, int>(900537, 1300000) },
            { "D8jsEtrCaYZm5RY12FXtCpBKTLJUfAzZRb", std::pair<int, int>(900537, 1300000) },
            { "DQMHcE3BSXYB6j484ks1uYNP3ZAAJmyzUs", std::pair<int, int>(900537, 1300000) },
            { "DSZCYoq9VijYwBbRtvNuHdjj9vKGG8WJyx", std::pair<int, int>(900537, 1300000) },
            { "DTepEVAUBoDPDiJRz8xuFk2we6SdBpsAXB", std::pair<int, int>(900537, 1300000) },
            { "DGsAikWijivMPLYrWNxpjpDoYVsNXovdu5", std::pair<int, int>(900537, 1300000) },
            { "DHdAgQSfUEMHMmzkCXkVV7PkZcicGKZr84", std::pair<int, int>(900537, 1300000) },
            { "DGHReU3Jj9tcYV2VvxtDpJk2odGtiaaCBt", std::pair<int, int>(900537, 1300000) },
            { "DJmVY6kg6SH7LB4gudPjKhcjtZYENDygtq", std::pair<int, int>(900537, 1300000) },
            { "DNkDebTUcieJ4TaXQFhzaQ5PTqdeixTbwg", std::pair<int, int>(900537, 1300000) },
            { "DDAUZUz1DWuEYEi7GN3BgsTvUqv7TW5yap", std::pair<int, int>(900537, 1300000) },
            { "D9rxeSd8fvGdgRdiSBCCSyKXP1nprnjuxK", std::pair<int, int>(900537, 1300000) },
            { "DGgo2BeNbdbtvHhpD96oxya1MmELreP7M2", std::pair<int, int>(900537, 1300000) },
            { "DKywMxFgmmEdTkKcoZNsV1FvULgjdLhzw8", std::pair<int, int>(900537, 1300000) },
            { "DNR2ehG2CHHZVwRpnr7D59r64bfptckFpN", std::pair<int, int>(900537, 1300000) },
            { "DFUpqpsVFsdB4RQ3tcgQryB22GpiQV9CHQ", std::pair<int, int>(900537, 1300000) },
            { "DDbrPCnzwLF6CiNW4uErqZAAHoXB9yio4B", std::pair<int, int>(900537, 1300000) },
            { "DDYJ5SunjJH88a6XaxJoVtrWZGRfz7AMHF", std::pair<int, int>(900537, 1300000) },
            { "D8EWD4dhQAupRU7wbo7zpqp2mYrFKnC5NA", std::pair<int, int>(900537, 1300000) },
            { "D5C18FLjL8m6nrrZ52JMvnLaf2McsqnMQg", std::pair<int, int>(900537, 1300000) },
            { "DFK47Bij4pCRExAQC6La9uos8W4CcZmXwC", std::pair<int, int>(900537, 1300000) },
            { "DTNcPqByDBzSYhfbwfwr2hCqNg9tj6wji4", std::pair<int, int>(900537, 1300000) },
            { "DTjK5an9tXHoXgfDmthfD6uVdoy8LkJsYm", std::pair<int, int>(900537, 1300000) },
            { "DSU6bf6PPp9dJ7szfZHgckoncPi8VWV2g4", std::pair<int, int>(900537, 1300000) },
            { "DTLfCEicRrxbmFN2362XtWJk5wTEi551Y5", std::pair<int, int>(900537, 1300000) },
            { "DSEdtVYEZw7WRmLff8ZPXmQEsbQbjHBRuE", std::pair<int, int>(900537, 1300000) },
            { "D5S6BH73TNJ4mitAc1qsgcKyLXYaobLe7Y", std::pair<int, int>(900537, 1300000) },
            { "DENGPYFTr9mrWfDhB8yqqYTdrRVJrxGGou", std::pair<int, int>(900537, 1300000) },
            { "DAkxhqgt1ATAVjs43VUdNkbyadXCWA841i", std::pair<int, int>(900537, 1300000) },
            { "DM9dHLbGs5ZDUTrDePD6oVqZrNLYJwFrxq", std::pair<int, int>(900537, 1300000) },
            { "DQgBvBpzKdhXkiArpsRWbr1EsSmhDsfXYy", std::pair<int, int>(900537, 1300000) },
            { "DDyLXUkD4jKrZDFvxkVhgksPdfK9VqyktZ", std::pair<int, int>(900537, 1300000) },
            { "DDyw67fBnVB17GW3GF3Q6PvxuSSh7WMBDE", std::pair<int, int>(900537, 1300000) },
            { "DCj8PJChZ5ZE3HyeonGnXGtV8GsqoV7j8i", std::pair<int, int>(900537, 1300000) },
            { "D96NkYkVhREyahWqZ8j8eVDrMTw8Aw48AE", std::pair<int, int>(900537, 1300000) },
            { "DSW2Vhzn8vA8WZngVZUb2FsJV2g4PnzF6Z", std::pair<int, int>(900537, 1300000) },
            { "DJoCjfPBmyH9tgsvYejL9GFEZf4ohKZiQT", std::pair<int, int>(900537, 1300000) },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 337700;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 337800;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 337900;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 338000;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 338100;
        consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].nActivationHeight        = 292001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 525001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 523001;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight      = 525001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("d5d5436381a5aceff75bae332b4a35f3c24b52194a56518fecf0ad25b03c2a80");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("11374e214fdc781a3ea206ead6cf23291ec3abfda245d58b0e555bc8d9711854");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("154c490fdff3943de777c76cf00072cedc0d2306886570fa78a32b692df3f2c3");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("309bf804c3b8a94b48ef510f0fb932ee837708c42ffe5ee02a520f3daa10f899");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("641f2baba0202043bb559452d494eff8a1c5f3de1d8b8adc4f572b0a3b24f03b");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("c06e7c7d19a30a298ea59f69533d66f68b4f535a9d6ba957f6d738f6ec965281");
		consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].hashActivationBlock     = uint256S("f39105a85aec716241fc717add26b08cc2785748aa4c7cf3c0daec5d578565f6");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("8686d0f1739d6dfc6eafcefb4c9ad1b56fc256a852d5087593631ccb0866b8f4");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("982267b09fbedbfad523c97f2c73a483dd070b11c00042a1fdb5586e3ab8848d");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("8686d0f1739d6dfc6eafcefb4c9ad1b56fc256a852d5087593631ccb0866b8f4");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xd9;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0x3d;
        nDefaultPort = 12341;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed1",  "seed1.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.dashdiamond.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed5",  "seed5.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed6",  "seed6.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed7",  "seed7.dashdiamond.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.dashdiamond.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30); // D
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 83); // a
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 125);  // s
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x45).convert_to_container<std::vector<unsigned char> >();

        //vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
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

        genesis = CreateGenesisBlock(1515616140, 79855, 0x1e0ffff0, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x00000eef0583695d6da23a78bab1c39939bbb54cf9bd5f0d4881c8eef364cd26"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // dashdiamond starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 60;
		consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 150;
        consensus.nTargetTimespanV2 = 40 * 60;
        consensus.nTargetSpacing = 1 * 150;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04d45416e4a64b1b051e2a2ebd80ced5efe148cf5fbcb70e56860957675a2da1a21fd522c42c1ed18a1ec42641589a09cf3f58678d213825dc21798183a005a984";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT; 
		consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight      = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
		consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
		consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x43;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 51434;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back(CDNSSeedData("dashdseeder.4444.tools", "dashdseeder.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd1.4444.tools", "dashd1.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd2.4444.tools", "dashd2.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd3.4444.tools", "dashd3.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd4.4444.tools", "dashd4.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd5.4444.tools", "dashd5.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd6.4444.tools", "dashd6.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd7.4444.tools", "dashd7.4444.tools", true));
        vSeeds.emplace_back(CDNSSeedData("dashd8.4444.tools", "dashd8.4444.tools", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet dashdiamond addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet dashdiamond script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet dashdiamond BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet dashdiamond BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet dashdiamond BIP44 coin type is '1' (All coin's testnet default)
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

        genesis = CreateGenesisBlock(1515524400, 732084, 0x1effffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000529df5fae941569b6466128042f5f036a8d1d380dd484a06e8a12fb275a3"));
        assert(genesis.hashMerkleRoot == uint256S("0x81c003fa9402b6c2066b34f13788085487aac22a7ba0bf626a67bbb4c69addd4"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // dashdiamond starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 150;
        consensus.nTargetTimespanV2 = 40 * 60;
        consensus.nTargetSpacing = 1 * 150;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x69;
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

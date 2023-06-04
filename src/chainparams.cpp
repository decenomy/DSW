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
    (14806, uint256S("8e2a2f3497557104a72be0823543a77e7f134a05319aafe0d9473ce8b82ed3ed"))
    (29613, uint256S("8169c3a9cf4b8ebab62f54b069f81ee184d44c6523b31273d795e58a3db921fc"))
    (44420, uint256S("c26fe1b693a46ba5e352d52bde29882f47653f2e7ea49579e3f75093bac680cc"))
    (59227, uint256S("02c11e8b619e27d4f4e5a54a65cc34eef1fab31612e81ec170c90afd99ae7c99"))
    (74034, uint256S("497cf9c6feb8b24776464b36c41426e46faadfa21fabcd58facf2312def7c40a"))
    (88841, uint256S("75cf91dcfa1b773fe70c2997b7fad61eee6d4bcc81e381bc9e68146d704be141"))
    (103648, uint256S("f152a747e693e64091f94f3a398ced2acd589c9a83761b9eab1745441bcb8eae"))
    (118455, uint256S("8e631fd46707105e3081c3ad2dd5857bdc20a00bd53fed2e0dc9d59868182ea3"))
    (133262, uint256S("c15ff70417096f35453604632db5466da78cb0c6bbdbcd90682651fe87de5fc4"))
    (148069, uint256S("383c7f640a2bb83dfd37d06f433bbc07a4a224e1374ea8a712a47a8ddb05ec7e"))
    (162876, uint256S("bd3cd61488dec4890329dfe1e26236883e9530f08e203077ef01830f6edae436"))
    (177683, uint256S("3b0109624e3ca0045271f3321a887d1e88db045a2904f0aec66fe028ae89e6a0"))
    (192490, uint256S("c69e304db83a64ccaeb61b5f92f21b7c7eac85fecfa694bcc5b720395ce9762a"))
    (207297, uint256S("cd918b1afa1fe1344b6081bb80577007939ea974635a62ce989694c2bcaf06a7"))
    (222104, uint256S("b5e9ed2de4e414c9d7164a040d4dd37df44ba3b630618d100d9d46df478e1101"))
    (236911, uint256S("bbbb588755480be3d0baedce18772d6dfd5b6a9bf9f2afd54b9d843d68508169"))
    (251718, uint256S("8111bad05d37e95d82c0d4eb3a67b107e2dcd3eb33b7142c0010cd39c00ef4ca"))
    (266525, uint256S("5545524f0bb42c10df572fd2102234a4e5f1056433605be18bb28a6fff097c5c"))
    (281332, uint256S("a649079d47d3d0e1dbace8db68595078aec05555cf746abb78c7fffa624faf2b"))
    (296139, uint256S("b07477d1a4344d7c5ea87c15b74240f88c8aa9acc496aebe30747587472f7132"))
    (310946, uint256S("f621f52976c2d56bece02478acbc53365c7fc8671699405edd6ab3b53ba1fb1e"))
    (325753, uint256S("c5baf04643d396cf5d9cf3cd40ed384954772fd508ea0e42c6e521370d9bdcaa"))
    (340560, uint256S("7770c4d3559e5623fee4af7ddb1393bbbf05d5260ce296fbdb1c86665538bd3c"))
    (355367, uint256S("eddd686d3c6203cdce031341ab432f5e098db0eda0f88d309c1c07e42bf37cd8"))
    (370174, uint256S("43fc137ab28245e8bc8c88e3dfffa3e32401c54280de17ebea2cfca097adc502"))
    (384981, uint256S("8f777fca19fbb9e1bcefa063ceccee1df043863d130cc2b9486804fac721a96c"))
    (399788, uint256S("b921924a835e286094d72b06fc9c336ce14dabc2bd8bee8296e9b3f54fecf8f6"))
    (414595, uint256S("46aa7664f41f30f663a118c090e2ed31fc2b68b8197e5ecdbaa1e237fe0c1843"))
    (429402, uint256S("f1bb44cb53c349e40ed2e337e7a31d4990547b39c9c2a1a22eaa5f99d09eebbd"))
    (444209, uint256S("f4dd32018dfe167af8b1c3770163187010a50bfb15c3728d995e0b7d5ec17e9f"))
    (459016, uint256S("eb454937bd99b4366cf539d76d409ae4a26051d2cf4b73ee51c3ca78eeb94f6f"))
    (473823, uint256S("c81f184019449da799aecf9094f933bd59a1b20c47a113d5f5b1242d65899f8f"))
    (488630, uint256S("d9b8e3c9ff642984299160b6d489be30fc6a2b25a062b54dd3430d42fd4f6d31"))
    (503437, uint256S("e8e9131391fa1454af1062631d70840a7aa44568e0f96ac037a183b25a37a7ec"))
    (518244, uint256S("a4255c31ce628de95a8d6cb5dec32cb70e3d2ad385a9aed762bb58fbccdb6418"))
    (533051, uint256S("cee0107f6aeccf3524075c09d3db0ee521c91b8de7482ff76bc56f2c9390b6e0"))
    (547858, uint256S("cd4fd23c5af0640a8c18028201a464c413978963c6d12280a8ace83c527e3a1e"))
    (562665, uint256S("2565d61c72f398a9f6c5c675ec19a43dcfab4881eb7957933504238fa78f64cf"))
    (577472, uint256S("c6c16c99d34f424fc55c83c5fbf49b3b3629422fb9a0bbf492e8d9f7460fcad6"))
    (592279, uint256S("aa7e898de80f68485f374a1c29fe5fa0613865d02fa906f5be8e0203234b6f79"))
    (607086, uint256S("0598af9a0213efa62c1c9988fdeb7a38137291afae35782d437399a3a1b5a517"))
    (621893, uint256S("33e82940efa9fb58e68ff6f0b0a43179c6702c3ecae722814f810ef4bad54a02"))
    (636700, uint256S("d8da75461e2c8fee85fc4e501c9c5304d093a8d29ad0fce5d3093ef6061026eb"))
    (651507, uint256S("24d3135f0c5cd4b28fb9a3de45aceb6ab89ec1b50a5e0b10ae0bab0818ef30bf"))
    (666314, uint256S("240c7ad754aca8f40178427123c55d5d08e492b70df5ff734d5407eb532d7b8e"))
    (681121, uint256S("05b36119c84b170bad8bfce8c14d871793dcde6630c4b6c4e41d91495e64ba5d"))
    (695928, uint256S("4931b8739c5e00677c9025a1695d928d3f86872c8562a13a2583b182c26edee4"))
    (710735, uint256S("aaf8518544771f6b3eafc07c5a697c19974d22ec8f870b951565c4670e428543"))
    (725542, uint256S("73718d97064d20c65930918b6615a576083d4e7502225a9430e273eaf30910df"))
    (740349, uint256S("546ad03fb6776f42f1416256063b334ee5c8126956ffc676751cf4457cd7ef57"))
    (755156, uint256S("502e3b8253966f044153140a17c322585268f2fcd8327f526efc6d791d913bdb"))
    (769963, uint256S("b4a818bf6eb439688ea683e25df4f8605619b9b8d7222ae5b35abb6728efc36f"))
    (784770, uint256S("3086b4c7bf2453fbc2847f28a87dc51dbcaea5b610ddb1f7ea5ca4c5237225cf"))
    (799577, uint256S("351ebf63a5d68649c67e8dcc50ae1e66078f7e10cfa86b14ee1f4cc4603afdb3"))
    (814384, uint256S("923caa7780a26c4579813b1a4fe6da759a2661ac386dea0d89c34641ed5a58f3"))
    (829191, uint256S("744c3fd3ef885bc9f5c13af15459e300c3aaa49ad974f222f2896319a2d298d5"))
    (843998, uint256S("506dd65016372a1594f196ffefadfb7af3f12717778d1f1f948bb33b8df329ed"))
    (858805, uint256S("73e5b3614da0d5fbe5fba6f03b1efe6c748dcd69f84b9c2d31e9d4ec17d0eb94"))
    (873612, uint256S("df39ea6800070761e02b44d19dd0c38af044906274e574fc20a9afb2c07c9048"))
    (888419, uint256S("48d51bcc7a6ff5c85efc6d15670396653b9e32fae6a26964deadca408df4913f"))
    (903226, uint256S("6781825f3b0ca37396aa8bd4b2066129986440a134c3c268138ea58a18fdab14"))
    (918033, uint256S("99da2b9fdd873878e47aa1bde4de5687fe52c1cd0f17977250162b86c10ffcad"))
    (932840, uint256S("2bdd419a874716728c578f9fd558200435d709b0761e1746f4e0794e37ff40b7"))
    (947647, uint256S("87436663a10efa1a52f583cedbeadb66f597482f610832d2b6414366e31c78fe"))
    (962454, uint256S("b77403cecd388ebca72ef897384f30ec56fb5215b18522b6163d53eb7b33b9a8"))
    (977261, uint256S("154c022acd43a16b8e8563ed1c98dfe0c20bc49526b85530a0ac01e507cd2f17"))
    (992068, uint256S("06e4ede0587bd9c2f5d29017581ea8ef7d5fe35d72573530b650527ac90ee7de"))
    (1006875, uint256S("6affd54b22f1db7625c6be226f84344231ff8839a3dec35c0f52565fe066ae07"))
    (1021682, uint256S("6ebf1fc89764321a7ccc65a1fdd4a7cac29787cfbf22e7506f3b947505e4f7ed"))
    (1036489, uint256S("8cdb8331a4027d62b3938d1a173a3732377d9cc0d8653ffea7f897f84112df18"))
    (1051296, uint256S("b3fd841964b352912903b6452cffc3bf13a100d6c58cfe0e6b3466af0e2badd0"))
    (1066103, uint256S("d26be7da1894fefd12be80bd4392fb19d831ecf3000a2907506a90a46d85ea1d"))
    (1080910, uint256S("030f79cf93950574e73eb8c558ffed344142d22bcf5390c32e5ce7f9f6eacc93"))
    (1095717, uint256S("35819ae5a0fe4f02c49cd47c3af040154481f253499afa141646c7b42da80f4b"))
    (1110524, uint256S("a20ce4381e54af73c61ed1e2ecdfc8a550869b7bfc6eee8ec1412fe276d6dd64"))
    (1125331, uint256S("071463936687893c351081144fb3c921b9803959b7f479bc6da07e707634dec1"))
    (1140138, uint256S("600bd0d79c6c1986b4981adcd9b6ffc24dd53bf1ddfe0bd5a4979831cb3962a8"))
    (1154945, uint256S("9f1d4d94c60be0be4de330f2a052c2043bf53115551ac23b200ac53f410ed351"))
    (1169752, uint256S("2204445db92222084b564fddd1adfcc9e896e3f67e11b1b7b1aa45fb6dfdd607"))
    (1184559, uint256S("c315853a9b645c9af2ddc5ab88800f16d064ca518d52b43354ad8f0aa215eac1"))
    (1199366, uint256S("b5c67d04a5ecd8264f5ed9a33c1f89c2ec490dc1f988fb10c8e9075b4186b63f"))
    (1214173, uint256S("b0361ddd18b747d9e1518b48bff9433221b00605d0ac3bfcde6894651ff10dac"))
    (1228980, uint256S("7ee8ce77ae98a8a08af1096d0a0c773bfe90733816364f98564fa86d4ff2910d"))
    (1243787, uint256S("6d1297536fcd10ca1b9c5242f57f38e688f1862fe13b266966c0b8ed9cd42bd1"))
    (1258594, uint256S("1d2e07d9e3ddd3b1a72eace6e5cbe96167b353a15c45e742bbca65ce977e2ec3"))
    (1273401, uint256S("c746be7d63651da34302b1d76fda5393c44288dcab4d7ca9fb4cb403919149d9"))
    (1288208, uint256S("e087e3a0feb3ef1337ca7911e4f76fab0063909a1b955cf73d5555a6121a4686"))
    (1303015, uint256S("3a92c91bb313b27af261394681c2a68502fe38cea115106c373b9e027a063e26"))
    (1317822, uint256S("d8ec52c690c74c77042034aef484bdcbd0b04578430332bf9379f71f163efb3a"))
    (1332629, uint256S("b93fa053f929f27a874bb859f70b0072da403feac784ccd5a0f80704eea8b99e"))
    (1347436, uint256S("dc74b2a12ffdf7e5f06091e6aa0c2fd118b103e9cacb8c94d877ee089fa29d8d"))
    (1362243, uint256S("b2c2d0e7d788047f3be9bf5900830a4f7ced558cf0f7504fb44e7f9947f77617"))
    (1377050, uint256S("77809bb5d1120d52167d8895b7051bb6e0f1886f0a089ecc767ec940fe1fc09b"))
    (1391857, uint256S("b7f70bd55d1a14fadfbd1fec64a21e2cb0a128238d8a9fbf70b31fc49a960e74"))
    (1406664, uint256S("6b990338b0a28879847868b6cc60ed5e3a49bdae18b03a1b4d825694fa3356d1"))
    (1421471, uint256S("5b0a4756df5c80b3c778dc60dedc5865fccc553c03b31e08f29bc4d851d0aa5b"))
    (1436285, uint256S("8f1b8517c5de90a4a8497113206aeb58b6030f998836d8f8e4af3e74fb9d4c90"))
    (1451092, uint256S("b80ddd168ca97348229ddb3f95208cd15b4c0ebe06eb721149e911ff44a968ba"))
    (1465899, uint256S("249ec24ef5210c00bcd479e1b12b4b4dad8804429dba202cf7488d5c0dec22bf"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1684949565, // * UNIX timestamp of last checkpoint block
    4012744,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
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

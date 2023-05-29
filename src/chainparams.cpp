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
    (14718, uint256S("551ac6d21615f4b2ea437fa9248cc39a50449b594f5e33ccfacdcc3139fa9085"))
    (29437, uint256S("7d696b02825a935ac062461da39e0085285da0748f1686258c86054fca5f542b"))
    (44156, uint256S("c7610139c33640e14901247d55e3857fb09216edbe13c77d2584a1a881c8643a"))
    (58875, uint256S("348c1c5edb95b355b8d8cef1b51ea3f09699a4874eaec17b044d3f6736371352"))
    (73594, uint256S("eb907afaca5033a7cdd8e99420c3ac04b37c351ddcb6ab7481467f2e2b3a36d2"))
    (88313, uint256S("ba39e28667d1e05da352ac4347a5959f7e75a5bdf4d4d1a3cd7bd99f24946a3b"))
    (103032, uint256S("ebbfafdaff2880c07590daf2d130373976466ef5346e23bc6b475bada2ad7173"))
    (117751, uint256S("d91807796e35af2556c53f066de0d4485dbfe942cfb5c5cfe19024a08a493f30"))
    (132470, uint256S("b4733ec878b60ad920b17219581d70ad30dc61867a645ec4fec3e16fcd86dc4b"))
    (147189, uint256S("e4f6cc434ea53f900e6c4b0227486a99a892bfd61e63b47d5b50012af0c6da89"))
    (161908, uint256S("7268ca43f9284976f0a0b59c239623e840770c0a4d3bfc90de4023f6f89a7bec"))
    (176627, uint256S("c9804f604fc0252ffe17decd2c748698bc026b03ec1306386598a34e10fabaa0"))
    (191346, uint256S("ff6610accd0a61f6eb74b3645756a6736fd72f719745b67e10f746f5e437bc8b"))
    (206065, uint256S("763a9866922c4ad782ad209b29d189f87f6f168b04082c1527eafe5f7a7df4e6"))
    (220784, uint256S("8aff2a59483cf6c7e8d30a9b26e3dc2de3769ac198d9fccbd711110effbe9806"))
    (235503, uint256S("28bf41e54128e83db40d9648036b58cd5765117cf628dc52e97f0dee484be866"))
    (250222, uint256S("7f970155fcfdb20b9669999e5a6f607c855aa3db8557c45ae322ffab791f0bac"))
    (264941, uint256S("3669fc6d2f3a28f3cc5e70c81d71539841aeee2e496496b1cf72131e58b2c2b1"))
    (279660, uint256S("95170ac4663e70e4266f57cc256d34b0bed3c57e012ac540689cc1be503a079c"))
    (294379, uint256S("4702c369328fe064cbb15a690885b00cd8da3e062a131da213ef496ba20263ad"))
    (309098, uint256S("fa7c49fc5a8fb5a5bb1183dbe4436c6dc18863f07d055092b4666df38b1d8d2d"))
    (323817, uint256S("f052285b4e6d658de9ada867e6e34014d3d011f19bc3f7bb6207e3e181b5d158"))
    (338536, uint256S("74c6f01d0e07b2598fb37378309db8a33b03da08ec1c7db6c0039fa739fe8496"))
    (353255, uint256S("1fb2a6d29478c824757443a33ed04fa30fb5091d4bd4cad4d6bfcc58060a2b54"))
    (367974, uint256S("4d0be20868d7da6a33ff4d0af363dc8602bfc9b56300c9b630577b3ec58e5666"))
    (382693, uint256S("935eba0cecf36d7bf765ccbb117af972fdebd2cdac3ee5be7025b7ca1de85911"))
    (397412, uint256S("0045ef869264671970234b42f3ff7c86535bf0bfd26a30af5da03b2791227634"))
    (412131, uint256S("ae68cc7367048286d0c310cc0ab00296356b15b911f62bf5ededf36ae8471553"))
    (426850, uint256S("4e49ec28de943138def86c938784ada5a34590a4bda49265ccd3799a6e0a0470"))
    (441569, uint256S("a3e8079df1d4e60823be5f6f0fa32f22cc704c0ea2d63ad1d9b69410753176e2"))
    (456288, uint256S("7f9844d23e9a8351e7c92968847799446c068b4ce4817ba7d8333246c774222e"))
    (471007, uint256S("17ffe6e9f9f507762bee6e6c2cfcd58e7469b29837fa99f01d8059bb76b24f85"))
    (485726, uint256S("b28203e3d471873853d12f7e996632363db37fbdaf4cff7edcf0210f79fdd536"))
    (500445, uint256S("f0e9bdedbd70edb99dc49b51c4d96fbfd0eb89f8c389ce1d92733df6be63d969"))
    (515164, uint256S("eed6be8b5e50c7fd3bd511a49edf3c2de55441f375aa20f8bf10372315320394"))
    (529883, uint256S("4adecc9e6aa7bc63b548fe9efa509c1989c564938498df9aa4252e0519329015"))
    (544602, uint256S("65eda506d7497d10c5c0eaeb8045c70710a32268fbf41af1e1a0496b0d36ea47"))
    (559321, uint256S("4a908980b6fd26873db13b0afa8906eedba8569e67886ed36de79c56d17cab16"))
    (574040, uint256S("0ccf779d052a02bfdf1aa129baf761ca29bfc96b4df11ea2dc189c05a5552ad5"))
    (588759, uint256S("cda1ed2f4386ee4385b920e9753e74b9631ed3c6fcee24f59a81ca8984f5eb42"))
    (603478, uint256S("346d204e81865a839771dac8ae5b7cffffffcea93518aabfbf200e89b6ef978c"))
    (618197, uint256S("5f10ab2727b1b38ebdb85d1cd21cf447b6283fbdf64d17090715618a8e71b0b2"))
    (632916, uint256S("270c06d5c25fb202f1c0e71e5be190a01cc73946ae0c81e2a409e133255a6fb1"))
    (647635, uint256S("55578096c143fb88a32cbda67110739210729ed8fb7ee98a529327dc520698c5"))
    (662354, uint256S("3e20f58dd4a9ae8420d198964ad1b5ed7063fb48bd4a6d972cc784af4c3b24d9"))
    (677073, uint256S("07d446642a00374919259d66476be697d67f000c019ce97fec7eada4f94beb73"))
    (691792, uint256S("7bae78c2943ea320edd7cafe75bd19c1825a47fea20bbdc31a70576fcbfc022f"))
    (706511, uint256S("de7eacec3e748ff401b3ef76bb1de0496e18e056d4abbebfdc0da4528ab3842b"))
    (721230, uint256S("4e8f589a68ee2e2a9ce5233d516ce2dc2fa12115d7d4c42b5af2b1d87b5a8587"))
    (735949, uint256S("67269202eca00e8633b612d87fb1b38666fa28f6805713d6ad0cc4a74f3fd399"))
    (750668, uint256S("b72719052975f5292f017ad57cf213701da2ba1e266a9d076f47c78eeb0cdb88"))
    (765387, uint256S("187160c9330c4f742f26b1c2624ad0650ef450cde2a20190cea8f41dce827734"))
    (780106, uint256S("7315b9b1234c13d42e488cf64587d199f18d05a2fd14dfca672638608de192f3"))
    (794825, uint256S("3945f364e61009799ab8de2c8f8b38ff756611bde53287f7d3571f4ba06d776a"))
    (809544, uint256S("84487bf0135a280ec56e5300156f33ad5b0034c1173b62e67aaf3df6b6c61081"))
    (824263, uint256S("f8c17872fcd466013cd8fa4f1f89f276b5ac6a72ebcad1cddf546ff4dc26f08a"))
    (838982, uint256S("b84825dafb2f8fb03f74f26e58b6f0542865682af26ba352f31f7c3ed5184bb6"))
    (853701, uint256S("cb734b00f51503672d51aff81c1a1e715246b8f42a1916616d57e6b9a53fb28e"))
    (868420, uint256S("12706beb8969489b021b6e48244e247586616791d4f3dfc92b71af2897e6fdf8"))
    (883139, uint256S("b36603018c16c6164fd41421f9b4c8b869e95963c940bc0958049f07c2bdef8a"))
    (897858, uint256S("80e8234428ce776a6938964dc4c347d269cdc6c06204b5926867c87a3ed2e7ae"))
    (912577, uint256S("5c8ff295b5e15efe61bff2a2108fb0b612469104e821c1515c6eb6fc5733ad38"))
    (927296, uint256S("0b8bdd1cf547fb8fd33775fd1529d6af9c6c9ff52b5f93d1dc27012390f0b6aa"))
    (942015, uint256S("20c6863fd4bc790b82213bbac8daf5bab7066909b7aaf879b8ff9a0f9a19ad49"))
    (956734, uint256S("a1cc4efb0ab1c2658b4e879bf5bc68e1d0c81c50635c45f41a48bad4a4d4b18c"))
    (971453, uint256S("8282adbf588e4a69d3a1b91269013b1cb502295453ec22be935def3715ffd444"))
    (986172, uint256S("5fa1ce262979558dd446056b1e6d035af56982f7f3a9d0611b7822bd75436ff1"))
    (1000891, uint256S("dc7342a1fe331af36ebdf32fd28e34efc53f99185efee38ecdf74e31e95c353c"))
    (1015610, uint256S("5ca006da8b9f1cae69054ad19e5a60e9f1640fc6c47bc40707b19e4a1262441d"))
    (1030329, uint256S("8605bf10e54802af8e8333e4910f9f443453b5a11f6eed9b8a5bc365f7754fad"))
    (1045048, uint256S("7a853c6fec2be0eac77f7eb0e1df5efd3935757b4f8583d2c0ca81319dcd8fea"))
    (1059767, uint256S("4d6a2f18ee63c3526a8addc8c416dc3e29715242ae132ea7f62e24beef134869"))
    (1074486, uint256S("369d1b9d3b5f54faf25f137a653b6517f3ab4a4c187043228f4f2d54fa026dd5"))
    (1089205, uint256S("c662540d86b0e693a5655a376d890a516207adef5f3b41ba59d014d91fd055de"))
    (1103924, uint256S("b3a9e0b760df81717bb6c277ffbb6a2c7172e46d1891072258c52bfc73c46b08"))
    (1118643, uint256S("8507d756a42fbf427a87ca5b99ce7c1375bdbc8e94edcd54fd839d60546987e1"))
    (1133362, uint256S("c78fdc4e3e33a4f0d195833890f71201f5c13003f8028ca3354e7d0116221ce3"))
    (1148081, uint256S("44955e907bcf310bdcd794fa699871285736f1976651df4bfe212d0df3b6b970"))
    (1162800, uint256S("673261f0664cf4759cbe1ac70ecca097f8b543718b17ebbeba1e4b88e3212b64"))
    (1177519, uint256S("a78fc6125a0e5e411db53f5959189378b6c3bfaf8ac3c7eee3c1e63119759bdd"))
    (1192238, uint256S("a89283d053c75bbf7e6b1d327adb58c6f4685e1ce7bfd656d8f4287972639f21"))
    (1206957, uint256S("bc65925da0bb4f20b30691c38ed4f9618729c4bef8782c71663dedce45cdf9c9"))
    (1221676, uint256S("30e1760d9bccc0050425d83ac8c1e8a8e342bb4a577061dc327bcd6331360b2a"))
    (1236395, uint256S("05ae76bd1d68e04cb38d076d4316f11d508b2bc6ebd883f5bd1c2c14382e9a8b"))
    (1251114, uint256S("a56d9a8f968c9c69ab4ca6f4ad47f1289e508fba2be31adab214eb26bf2059e5"))
    (1265833, uint256S("b4b8171bdf5bfae1fe163c52583004901e0d8b52d5a29b0142b73faa71c1929d"))
    (1280552, uint256S("bebf8d52e3c67f8f94da16bee6bc956b8c5b6ee607f97d2a753d46958ca3d3e5"))
    (1295271, uint256S("7ba9f482fe9cec332832065c245de005361849bfded9fd005c1d3cc4d84cfff6"))
    (1309990, uint256S("e1f7a079f5b93af923d78b20403cf4afbf28df2c56cfa1816dfd8fc9a925a2b5"))
    (1324709, uint256S("847a3ffb857207fa0c41828ae3867ee46fbfbb9468e4b315fe1667b699810002"))
    (1339428, uint256S("c6bfbe9f6f2378f8bbc4e1470d0c69da3167884374bff62dbf0de93b9eff5ccb"))
    (1354147, uint256S("14100fe4b20fe6109238f8991049f3152d8ff83c29b334711fdda9120bbb5da5"))
    (1368866, uint256S("a222d145c0e59ecb7db76cb17f51d17c3b052fdfd0cbe500ef31d468dbb3d8d5"))
    (1383585, uint256S("7388ca74e72e86c2da0dbdc70369ca826021044b59c92bebfb5a6097b90c16c4"))
    (1398304, uint256S("3ca3f6be4849856b2b828310d83a6d210e35e59605868b7acd4db21c14015e08"))
    (1413023, uint256S("d79a48b1c74e51ba8b0c065ddf31d2640206ec17f4ebe36bdb83eb6ea12a7f1a"))
    (1427742, uint256S("8ed2f19741503bae8c066746f8ce1c89d4f5d01e91287dec3a1b4e1a680fb605"))
    (1442461, uint256S("07280efc35ee5f408b47f48dec87152554d53bc4260de9a27dca48b220a66d0a"))
    (1457180, uint256S("3362fcdf626588503813ff8dbfdb2637ed0e80399a77045b85fad580926d4172"))
    (1471899, uint256S("dc8d14e9bc46a75edb21a3adc723e16a0616c7ad27b781a2e786c0b28cee0864"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685318595, // * UNIX timestamp of last checkpoint block
    4025106,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2830        // * estimated number of transactions per day after checkpoint
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

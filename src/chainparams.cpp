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
    (14755, uint256S("4f5fa6402545b3d284789f114b649d4b7b68807d817a068ed3f826794f2e0ef4"))
    (29511, uint256S("9879f6863e9f2e33c3beb8c3a8953565a6253aa62b2118135cc6e8b1d2869c9e"))
    (44267, uint256S("b5852d466135fd10ba10e44c95ea1160ea6cf0ba051767b738adb6fee78f6cd8"))
    (59023, uint256S("36eb847ea773e3a25a78c7ff32788daff078d6c00d30a48ffbaa203bce4cc04d"))
    (73779, uint256S("61a18f2f2983d3e715bedeecde25c09b65f998cb2e6bfa5452e1dd365c7a0300"))
    (88535, uint256S("280276d7d4afd95bdd4eea4406a4c29872588228aab801301dcfbb297d56e792"))
    (103291, uint256S("5515f706b518bda9a42d876504dc3afb24a94d2d17b69821a9462efbf5a6fcb9"))
    (118047, uint256S("e2294387d30df25b19f5734e02d95250c060539509036a30d573d57d7cf33b7c"))
    (132803, uint256S("3d0cf4a1e1eee749ad20e1b90db4f04ecd23bee067da018c1366e7eddd9d0491"))
    (147559, uint256S("d9c0741d104e2b019db728125e0ded7ce2bb9735c61035050304c701f12ebff1"))
    (162315, uint256S("657941a878b21e5d25cef0381c41974798126a96402eac65ee7b70bb1837978d"))
    (177071, uint256S("6d4cd3f0ffdd3e15ac9cdc8818100e308bac2e7dce1ab6467e7eea3d927883c1"))
    (191827, uint256S("91e2b4ad51c500c8aa52c859f59da01e4ee49b2644d6c970ad20549deccd698e"))
    (206583, uint256S("36e684de49ea757ba2f23b8ef971f884f948365b662cba3336059faa106a01eb"))
    (221339, uint256S("e343b942cf1f47cb3b41cc57b94bec0258713d6eaabc66328fe45988bd7b8445"))
    (236095, uint256S("42a257f64ae25b70817c4ebab9199c654745b20f753b9a98e54c7b0243ac8d95"))
    (250851, uint256S("4b6bd9c559803e99aa7c7e871a50bed7e59d8ba2b874b59f6577af368cbf5eb8"))
    (265607, uint256S("2ee82382112fc96238b5cb9ebfb090404bcbae5541a3ddbda21148664f2d95d4"))
    (280363, uint256S("b2253ee32ce53a73b66b56b3ba9d570a0b6cdab959248ae8ea794dc0547941ae"))
    (295119, uint256S("aa4aa3e8c94254597f8eb82423138e9d38cd050fdc39807be34145e25ea841b1"))
    (309875, uint256S("2fb4f5ce6ee44e67814c6c982807084a99298ddf1aa342071681dfc4db8b8853"))
    (324631, uint256S("7f52f8fab1cbf6d7a08a0d5f833520e85bc94ff67547b50d0065c8b402e468f5"))
    (339387, uint256S("e8b57b92ced743e248c4ce9f5deb07a27e02e7ce7106d0b3a036747cb13f58b5"))
    (354143, uint256S("8fb2fa21f00c758cfde6ebf81ef45cbc8ca06b60d0c89eb69191fd3a61bc6d08"))
    (368899, uint256S("5a219b8001719d58fae3e5e97bb5b78588d4ccd4967f16f8bc939ef206eecb26"))
    (383655, uint256S("7335efdaf3c645ef6f98c15dc72cfd7befbfdaa310c361d24b7cabe02219df4e"))
    (398411, uint256S("84e7f0400cf0255789892207864850420394b99c79b660c39952b2a05505d390"))
    (413167, uint256S("cb5962ea4505e86005cc2c6c9f8001205430d3dcc733088b7bd771b59575a5ab"))
    (427923, uint256S("cd3d91d5832f4040c196ff14b2359f5c3f1c4b585007be4860688ec3be13daf3"))
    (442679, uint256S("ce4c82d71f37b718db6ff4352c86757ed52a96223d53dde31ec2796d74feb63a"))
    (457435, uint256S("7e14e340625f948b9816264c9559c190775343fcecd4e019fda55756de44db71"))
    (472191, uint256S("df3c131179ba75b40aa3571f6bec93711705433961f474ddb502df20e4381579"))
    (486947, uint256S("c32ba49511f01ae9f75ec6209ecb04226cfd90ab4d632941ffc4b298c90768ac"))
    (501703, uint256S("97b95667ce8685e7d63824ff47cfc003d622010b8ea9fbe6daa77d1574a01d6d"))
    (516459, uint256S("3ec9f867168b3497a435417ddcc4608b8c5aa801fcf536c76f82c9bf0d250929"))
    (531215, uint256S("938f75adf7563e2c92b75ed93cff0c2e19d3ccbba9079e8e9cf4a5a46b873c07"))
    (545971, uint256S("97ffb98ac93945af4bab748d826385c4a2a1c66c24ae8eb72732d46a2599bc4f"))
    (560727, uint256S("38a99f7ca331e8ef9395a66e190e71d78f96180b91a9ab81bc52c6554e273cb2"))
    (575483, uint256S("9a2c9988aea0e7a95f65824fe9afe87e79618ca9f1b564268ab326eef5269922"))
    (590239, uint256S("34e397fb30df23903a1db72a0df942c054129fd7af37fde2db85a325ba866b7e"))
    (604995, uint256S("51d2a7bac2ee29f7dd1ab33891b9d94fcbd0f3eda9cb9f4f04e498e6d1bcb608"))
    (619751, uint256S("1a1764282fcade5720633b157d362cc04f4c764700b6d8645941e7d94ff8c357"))
    (634507, uint256S("159c0dfcdd390257424b4469cac3ac02c63c4e318ddb8851aecb9f3c427c6794"))
    (649263, uint256S("2883cd974eb1448fe8c74855ab65d5835664a84514901c1dc90c3ae20343cee1"))
    (664019, uint256S("0b7a83b61f6d37e4c54026f44989f5506e56b74a656df7e04841a5a179192a64"))
    (678775, uint256S("e680e9fa0863e068ad304d4d9b053c35687c12017a042cc393768a9b7ea43a18"))
    (693531, uint256S("b2c6cce5b41bc5447d6b78d6525a9e9497d3a766506a80cf486323ad16008016"))
    (708287, uint256S("bea55c32d76117b747d2d765df296c2ce19134ba244fca4750de27e9eeb68941"))
    (723043, uint256S("14659e2370627ad357aa01da2e6ae19ca3b834cdc8b6cdc1204eda4860eee24d"))
    (737799, uint256S("6d25a2c078f2fe78e47bec845d946987de733a9767bde7b84277f052ee5544d6"))
    (752555, uint256S("54dd18522f6320dec08060264f61964987b8a18c4000b5aa498589b2f36f4258"))
    (767311, uint256S("a746a47d6bef045a802eaf8618e9eed5ca2dbf6a3403077d6dea6bf537b0f8e9"))
    (782067, uint256S("96cb51de29392844540f2ec8bdd0170aa9585691aa7ecf5a40552ca250321c01"))
    (796823, uint256S("3df10102b2c480a45c126b8ecdab5922cf0fe1dba094596ae29e881c0b39b754"))
    (811579, uint256S("ef41560809c64529c5381bfab59523efcf896a821755e2bc5393a0d59c3f2592"))
    (826335, uint256S("55db0414305c8f03e0a4483e66471aca01f63215ce473cc223fc5c3b0f3064d5"))
    (841091, uint256S("5b945ea45c0c59989a49127a84c69ff9f49f75a90822c19141518fe1557261ac"))
    (855847, uint256S("02bf21f356dec76845e3a9c71f49d9fb06071e41022cb658678039636cf1c097"))
    (870603, uint256S("41b2ee56fc0dce93268857d0e3503614dc049b0281c5ed2aa71b832c1deea63a"))
    (885359, uint256S("eb4e7d5b289c26b7d8a9c644b7e33f3f7392bf4143c375bb1c572fba5bd9363c"))
    (900115, uint256S("740606be6cae2b9f64d766b345fe4c131d2ac2114b980e3942c15cc8aa4d6e3e"))
    (914871, uint256S("2ca6882e10f992ff83b78aff83e6e36a1f4c2353b1a464de57bd5ca366e57b38"))
    (929627, uint256S("70478734905168d997f51a146c2ced4737a1e42d48a73da9ce551b0d03261d4e"))
    (944383, uint256S("e108133b32f68303b5e736ba13a0df4f1c68869ed8463e4dcde116dfdc14279e"))
    (959139, uint256S("afec55c3c57ba554ac70c884a8bd25d42dd25773ad5d52410e4f330dee5d64e0"))
    (973895, uint256S("e64c4c5741c49603280f6208b67c903a742d887126c4478d870af200a263f652"))
    (988651, uint256S("d02eda10d02a9731572ddd3a5afa379e60e075d0e6f3fb3aac1a49eea9f4e51f"))
    (1003407, uint256S("15c72c999f98fbf863fe8cbaa3d0a12fc2b48090d482e2c08defbfa8b4ea31b1"))
    (1018163, uint256S("89fc8a8a120cd9d38b697e25ad087c18310a75f4b5430925e73d225e0995565b"))
    (1032919, uint256S("fbea8b97d00426364b996932ff936d2e4ad426c2931f53d629362446d968c6cc"))
    (1047675, uint256S("4b84eb7aaf1e59a79036d98520a76aef366e5e24405e339c353a35ec02b7e34d"))
    (1062431, uint256S("7eb33f247ffee1012647a38bb3fe8d3f5686d1eb0caa2dfe0923b21fb7c4beca"))
    (1077187, uint256S("f19b24bcfa6169bc15e99621ddc2c077d7871398e9258bb58ea3f4d22594f21a"))
    (1091943, uint256S("b3d9721eba80df48a056dc2b654c8626d11bbd9852894ee1d3e12d0a799dc14a"))
    (1106699, uint256S("1f2620ed188a247af354e0bd25a321a6e21a381be82f5fb7376e521cab84a335"))
    (1121455, uint256S("e6848319ea5369501fce2d47b0108e5c0524c98e3407c132619c9f64dbb03c7e"))
    (1136211, uint256S("61614595ec4979c2e937f7c5c3c477782c582e195ba34edd271b78cb3a605538"))
    (1150967, uint256S("4ea699b47dd512cc1816df90dc1a5bc522bb3d209d1c372349191ffcb4773c52"))
    (1165723, uint256S("70ad5f4efb4c325eb865c59e19b0c1ca38bea4e1062829381ff925b3182a1708"))
    (1180479, uint256S("6438d5c9b4a79f72559accf72cdcbec0a0f18b7b3023f9ab8d0266a2740cb623"))
    (1195235, uint256S("e809531dfc5b882e31f8227798767b62eff97426a67f5aee19bcc47a9cc51a80"))
    (1209991, uint256S("8993d878bae98649ba217a03081e5350613e4f9c410b94622d195e229c90ed69"))
    (1224747, uint256S("3719529454f91d51bb869d30390395924b23ca5fc9f2ba7da28af590590c667d"))
    (1239503, uint256S("e12697ccc30c5c3685799bb2417f6785962bca329582165ecc5c5248e57cabc4"))
    (1254259, uint256S("70a3fe05e00c93ad43eaf39160a464e4510d4d6d3fae27e9fe57a14843b876da"))
    (1269015, uint256S("db799f2b5dae189a99bf3104578ed4e6cc6ed378e4b55d8998c45161deac1c54"))
    (1283771, uint256S("5a5713312936ead512abfd6fe815b6259e53b4c155e0b4e217156394d44db323"))
    (1298527, uint256S("13ab6918f0b5ac87130be804e8f4d564d010795ad817ff344653d25f30a6a229"))
    (1313283, uint256S("5952ae4e3f2f576c20a683cf83abc9e83356162c61d44c6f54c60cd33a83685b"))
    (1328039, uint256S("e05ba5e1eb984123bd3bdf5b2edf39b875894c3c4d6fb72091fbbda3ed34f55e"))
    (1342795, uint256S("2a91455d8b2e5c4afc0062659c3e5b1d88d2269816842abba5e245d191eb0fd4"))
    (1357551, uint256S("8245892d1329cdc0324d6ff00fce31b457438875fe967d2cc22d4a28a59e4531"))
    (1372307, uint256S("645c53ef3ab906e0c30fdff3cca248363c68f6f63008793011f0cae027b6d5a2"))
    (1387063, uint256S("63ec07665bcedb7f30858f4ddbd0fdc24a7a70e199e85881b2ef6147f8db412c"))
    (1401819, uint256S("ca4c4b3429e7498788fcf4524c2c62f9e1ab732bde8809c6e6c80ec81e722a8c"))
    (1416575, uint256S("3bfba1c505acd053b1d38463c3b31433e01f7ef94502cb65087a578ec7ca1945"))
    (1431331, uint256S("d415aa7c5d70b003617f94698315e6777de9a6f2a4c3d4997584609f063d7c2f"))
    (1446087, uint256S("01092d8d18bad179ca317a5303bff9c31129a60e738421ea8e2be54f7d77486e"))
    (1460843, uint256S("ab97ec5fcead27f3bb66839149afe0f69c2e63c60a0389bcbd098c1ce468f50d"))
    (1475599, uint256S("92f2813066bf80d588c3f54ebae144c4d08c31e94a10ff12a1c7be7605faa410"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685545680, // * UNIX timestamp of last checkpoint block
    4032761,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2836        // * estimated number of transactions per day after checkpoint
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

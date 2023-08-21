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
    (15909, uint256S("fe7163263a8afbb0e9fcf1a5305addbbe559d79cda4ba25d45e745a7e7d14e97"))
    (31819, uint256S("4bfc5fa1d3f3ff283c6be057473fb20eab5a0150659988ea120d128321f31519"))
    (47729, uint256S("201c3e8b5f2568f873b0f30a276a1d00b90374e839a249749b0dc9e237ac3d34"))
    (63639, uint256S("010747826d01d7a6c374c0e994d0b3fb0c09839e3d82ac855d33077546cc3c31"))
    (79549, uint256S("bf890ae21a6778929739286d4918f9f63fa960d03ae44ece3a00640f897c3889"))
    (95459, uint256S("359de989913486fcb3208272773fd27894f7856f0142b90699d2e18ed4b9b242"))
    (111369, uint256S("e2277a3ea51b449ffd47b46455b9991bfd048aa98c02f550c89734dda8c6edba"))
    (127279, uint256S("ff3419ee90f7b853e3b1c5627b39223e7690101b08a36b4bd8c95a0b5649b5b6"))
    (143189, uint256S("05eaecf8b348c28a7103540b9e4d8fb5289fa55dbdf85c239957f4506740114d"))
    (159099, uint256S("72e32cac4b3fd0bc487907f80a5a5ceae225d8c0b9978951ffcdea11bc608c37"))
    (175009, uint256S("be012a065904a8ae676eef4d7044c27e6d0b5dec16297c501b2fed9f793c6fcd"))
    (190919, uint256S("6f8e0ba181e9a025a9bf6e0fa0381076381dab9e8c751d365867e0c68466113d"))
    (206829, uint256S("9facdd094d90ee24a57ca765f61bb0735370713216c28a8c72f8686ea3cb17ba"))
    (222739, uint256S("aa9ddd68f81cd6acdc7d2c01d816e88d4ea9ff26c99ed03704a408cac9d7b3fd"))
    (238649, uint256S("4581bcdcc683ccdca92edadd890abc7d2c72013632e009eb3bb05f474fd72ed2"))
    (254559, uint256S("8b51fe5ab1812827e033cee8a7bb4392738a195314f321d8710c4eee9dcda221"))
    (270469, uint256S("386d760e5f2aa93a959f4ffbe92edfa4b567beb3cb196259447425a9e0787e16"))
    (286379, uint256S("78dc90e715dfa94c0c42fcd6f1ae31731e9ee1c6e4b252c3ecb0b69b14a6f151"))
    (302289, uint256S("16b4a6b5b04bab8d704ee2d83150f44e60d2b1b09a13624014d7ac1c92599646"))
    (318199, uint256S("2ee8c3580ae879a67bfbd1b435708343240b5a86e705ddf223e1d44780b6a1de"))
    (334109, uint256S("0737da6accd037e583782ecbac7b7680eeba74e2bc0af315e5fc7689a38b40c0"))
    (350019, uint256S("c77f01b2dd4b1df9d2b39fc6d33c1ba3a7b9538662341b30ce304622f392fb84"))
    (365929, uint256S("4e8bbc491a054f58bcfb04f0458683e94d8d7b2c44d65c54c8853607fb289410"))
    (381839, uint256S("c632d48212789015679e6a4623ceb05f71f57c3d3c46d81a8a26d3dfdf87ffdb"))
    (397749, uint256S("8f4ecb66a52b364db30c1890f33d1168afb53ea7b133aee323e15cb4f85540e6"))
    (413659, uint256S("444c149952af0c92ce4427ef9e31567342103aa7f3903cc589eb9ec87f845221"))
    (429569, uint256S("29a43e7eb26860bb91de294ae64eb6c67c5673e51ec7abc93875a9c771c451e9"))
    (445479, uint256S("adb57b626a7e0116ddce86c385e5e7f904a02b98ab89027478c362dee1c421c7"))
    (461389, uint256S("2c330a4d0a927a0cafd7e1cc5213de8837eede9dd709106f1ffcc0ab2c1284ff"))
    (477299, uint256S("41002b668f1c4479bc4cf000ce6862811fe636261268d20912aff7b5e4ea8360"))
    (493209, uint256S("034bd549be0118ba5ccf847fd401cfcb86ad4deaf2d52a10c3bf74a7c17e848d"))
    (509119, uint256S("1048ee52379c4616c39864f7786fa0a89bbb74e0c335385c75266630ffd7b58e"))
    (525029, uint256S("9ae6a1e6fb728d83dc4d5d0e3949cba332ce258f3302ff3ce6a8a7059ec28e36"))
    (540939, uint256S("0e928a8595b6e045fde54f9e63b25b4f8e7f8ae519fb12e81e569b233072a612"))
    (556849, uint256S("8799973197981dc12f6e60c4827b46f1cbc8208a172594eeb1b22acb5e6a81eb"))
    (572759, uint256S("cd3e36bf2da7ad5074815783b79fd4b4778d7a37dbb3578a9ea3ac52aba8ca99"))
    (588669, uint256S("edc30e6a09bed476a08436b7998147435fe68730b8b513bc4f804a6f0d00498f"))
    (604579, uint256S("4e2a5ddc50266e8cbd0e38b34151f9ca8c51344725f31830e5ccffaacc3b362a"))
    (620489, uint256S("6cc3010298a98d193e65007a87ff7ad1f740b07b6f1fd543813647e14e74a740"))
    (636399, uint256S("31f676b19c38bc6cd9bf72139dc886a848e4617eb77d57d804b72684b341569b"))
    (652309, uint256S("713b686b453f098554ae64ae8daf5c4db2d38b49cbc1f6f8b032aae59a30ab96"))
    (668219, uint256S("c4bf08d66d88650dff72c8f517185dcf4d1006d978265f44a89744ee203dc00b"))
    (684129, uint256S("4262481f299c87f3233ea374a88246cd8f9c8c8ed88e2cf84f3042382813e76e"))
    (700039, uint256S("cd7370f30a200585d5864ef5d73c3e98af1db10b8ac4b69aa707f85646f74a8c"))
    (715949, uint256S("f015260790ecdd6dacddae2116b258a6cc81f67e78ccfcf455b1cefabdc0d6b5"))
    (731859, uint256S("1f3ef5d8cb5905092ef126f72a115e000ddea34aa22715809c9b0e70c272b7bb"))
    (747769, uint256S("66cde834be3161a300ec58bb2032b1981c9bd00054b310a631b8d219a0f113a6"))
    (763679, uint256S("770d23818360806adf0a2a5fc70b133b480d086621c942d961b26418e921ce6f"))
    (779589, uint256S("4701f1fb83eabadc986b912a66f1c49aac95d784355a286beb509285d600055a"))
    (795499, uint256S("804916ab784cb399b5c597b2e999cadb1b826d2a956c8283de88c5b88ecc25df"))
    (811409, uint256S("61df89bce3525ec0d2100d9219ba691f997f1e1ed83649382f4d95b3b0a563aa"))
    (827319, uint256S("8f1518cee420e2f1fa26e8a32349f981892418ad7f3a67f6d26508dcef8e8704"))
    (843229, uint256S("1ab5cb74e20e96a9280283165b8d5f8c67c0ad5bcd8ef2c1ee45314cf2482c27"))
    (859139, uint256S("7c8d2c7ea76c6be0fee1d11d4445cb9ce6fc29968729e94ccacd193e7b2c55f3"))
    (875049, uint256S("c3a9e5fe64bd5f4b59afeecb46f887c0c3ec7339e57d0a928f9826cdf5b06bcd"))
    (890959, uint256S("f65e7e413961fee600aecc943f9386db54c96dfd92b2a5d0f1f1728b21addff4"))
    (906869, uint256S("1a6dcdc10caa2b03ecc4072b26cea5f71da24dd231b3e8bea445ffdcce07af6f"))
    (922779, uint256S("7189a277e522c62468fdc31cb55072662c41a3a7d70aa368700e0f5a0e097eb9"))
    (938689, uint256S("6ebca59a31dcb00ac73859e9a0c177f317beb7ad7a1115eb6db61fafdfda0b70"))
    (954599, uint256S("bf6754c08d7d230ab7ecaa2357d34aa06aaca4f11aa261c09016784bc21e0a47"))
    (970509, uint256S("3128a28511befcfea64547a0be90d687e01952779eec9333873cb7f0e99d9c42"))
    (986419, uint256S("4a03436af652599e8e4fa39f8e6a9663382a929105711b8b6c612a2abf220b43"))
    (1002329, uint256S("644dce8df3a54a5b0a347a12d2d5c9c12b3be59ea67e9a7e1c685b96b783821a"))
    (1018239, uint256S("ea729320b8aceaa144e5c1e09e16c1cafd9981a1db1112cbb74beb5375509704"))
    (1034149, uint256S("85c834555d4c790a52f0b379c57329b7f386f5694bd8e5a5e791ea6689b7c6b6"))
    (1050059, uint256S("d95b82e18b29777496dd2fd257cb369d29c0b2d7b88293e15265d8458a87eabf"))
    (1065969, uint256S("e1a426e617ef6c23d94d0da66360028a59e8305fc3065209d05977a67a53e4bc"))
    (1081879, uint256S("433052f10963057a0442b9ff14e83c69b15c0def4e561d29fcf39b431e4693ba"))
    (1097789, uint256S("dc5704a62f903cb69daa3359a6585083432e8105fe2bc17fb9f8a1ff07487f2f"))
    (1113699, uint256S("d7a219bd3689b83d589777a2c40027607e0118335b3e46cdc7b907188c853909"))
    (1129609, uint256S("d039bcfdd19963ba83f3e8eae659aef1f0e09f13d2e405669da6d7f06ccec6ec"))
    (1145519, uint256S("493d29b753099d5765938aca130f06e5fd2db1a2c7d869dd0a83d5dfb3143c1c"))
    (1161429, uint256S("26c750b4acbe838972fc153f761f06726d3cbf82ac1d92d13c0d60019dbdd4c1"))
    (1177339, uint256S("8252f224dfcd3ab6e00e166dd0335f0e33420ca40625dcd768c817d225bea952"))
    (1193249, uint256S("6d04974618787ce81edd29e08ba6c1a68b5da340e10eccf24de0a754a68f8aa4"))
    (1209159, uint256S("57f8c3dce0a8b1c5992c2bba237c2d9d6ee49d8ff141a8998afdf0576ddb6a90"))
    (1225069, uint256S("0abf7bada3ae887233756e231d05314330e5e3d07eeb61b64ff45aaa30efa0a4"))
    (1240979, uint256S("f5456f9fbc7cbf41c79326dfa6d5e6b4dfed4d853d5382e3b8a6dee91c0bdb58"))
    (1256889, uint256S("b3abc84e0c57ace5bb561478e11eb4e4630570ee4f1e7e41b712543e7db19eb2"))
    (1272799, uint256S("658f796ebaab93d5349d2fd916dc77fb0fbc9e8b9fde06989a340ec864be1f2c"))
    (1288709, uint256S("291bf2ce6764f85d2b31620a97b1739663fb31127e7ced3f87bf24005495cfe7"))
    (1304619, uint256S("f5a3cf311c576811bd45363cc40dce7364328983fb6388e81d20f86cfdee7ae0"))
    (1320529, uint256S("7b52432de82012e1e092bb16f3bb989b794531225bc591615f68121f909ec84a"))
    (1336439, uint256S("20fea0f0fc1a5e69fc128c759600bea66a6e2171b3369b77cb8f6759dacbf4f7"))
    (1352349, uint256S("106ce88a66a0a16043e8003dd98330432c872efef3b8570857371184d6b9be67"))
    (1368259, uint256S("e4e29ef0ca8d78c65f9767201bd96593686c56cdc3f2fdb11a3f2aa4a7bf250d"))
    (1384169, uint256S("10391b5ae65cc0d33f929d0089d4747d4a61b77e2f54be18076b5b74e6dea576"))
    (1400079, uint256S("e12c5545d1d8bd2c112d0302a440db78485f20bfa53fa331e977e71b2739edff"))
    (1415989, uint256S("2bf298ad3de97b594f5cb58e644d09e96955093c889ba5414088109676edc384"))
    (1431899, uint256S("2d0ec6b7db1bf5bad8d897da3dfde846ebeded615bfeda84e280774900cf8859"))
    (1447809, uint256S("319842cbe5b654bbf95e66a9dcc25d939c8e2f8ab3a669a8472bad46c000cb74"))
    (1463719, uint256S("da53ea45dcc5026bc9f7a4cc870b2507ee6ad3177504b60b8d08f2ad6a707269"))
    (1479629, uint256S("79f799bd109ea43372297eb37984569955131ea585e4123d15e118909795be2a"))
    (1495539, uint256S("ebc5483664e8e951def946e467e9f4df1a1356cd9aa5324e9168fb18b0c98b85"))
    (1511449, uint256S("a0857b7e9f250d5a61adb2aa48fe845c261a3c8a2a2f20e04d49c39b46f883ce"))
    (1527359, uint256S("9d0a2363c9e5c5cdca95d386261847f03f077bb6b7a2cd4c0737dbcc84d832ea"))
    (1543269, uint256S("a45189fbcfbce5831cf5e5fd0b37e53ea9cf33d1f3c4783990a4f774f4615951"))
    (1559179, uint256S("ad65bb2ee79f9e33fb0d06d3ee196fee7b1c70ba056c06b7ae62db8764ad7145"))
    (1575089, uint256S("fafed06105d775191d19485b802deb29cab7d942812d1d7aa55b8b1c9a267443"))
    (1590999, uint256S("e7b492caf828e2f8a47466284de5de83b976af905979b5cbb7a8def7aaa45c7d"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692637455, // * UNIX timestamp of last checkpoint block
    4272455,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

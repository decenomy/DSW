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
    const char* pszTimestamp = "Another 50% daily gain for Dogecoin confirms 'alt season' as Bitcoin slumps, 05/05/2021, COINTELEGRAPH";
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
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (10807, uint256S("91fefdb1d14dcc1c989b1b54ee70877f15b0115e19ec55e5e89a78620f307bef"))
    (21615, uint256S("d236fa8b6488084a96bca2ac6e694c49a533424e0d25ad240d5b094b45e1907a"))
    (32423, uint256S("c24fa541020b705843214eb3db487adcb19cc03ebd9ff0380f7fb3d57377accc"))
    (43231, uint256S("fd8a3e4aa162fa228c1a66bfcb3eba27947f2e8d26aa72d52490ffd3e7ff5041"))
    (54039, uint256S("af8f2dba9151ca971fbd6a17de2ec33a880589cbd141b3f06668ddad1d26c51d"))
    (64847, uint256S("5d79e5256614d716cc4513ba03947da3660663860cd9415f293b078f1ea1d353"))
    (75655, uint256S("4da0f106600adf53e117676882c49e26fa5a1b73088af819d812a64c18ff3fbd"))
    (86463, uint256S("19e023a9c1827f89ced00ffd4ffedd59fbe9f72194b81c2e534c04c7411e6082"))
    (97271, uint256S("38705b7982ca0ba0484a6e9147cf8ff1f88923f0d4ea7ab0b87f73f7515c02ca"))
    (108079, uint256S("812685747f94eb1c2a842e0d13b7d8f753443ec178b11cddbe44175ad882813d"))
    (118887, uint256S("21c5298b71c9540c006793a62df47fb93ee317c9d7cdb15fea938128c0256b3e"))
    (129695, uint256S("5fca36fee438d97695e159e4607d07652bd8715e32dbd56cb4e1fc8ddfef13d7"))
    (140503, uint256S("ebb95a583a4801da684ca77b4bfa92a203eb89cf03bfcb097765f2787e574292"))
    (151311, uint256S("52346aa12f504c2b3262dcc5633bb8b878ee1a08da84a8cbed6aa9670049ae6c"))
    (162119, uint256S("192b1db0d6914cbd1f36cc31687485d57ccc914e0f0440575ad22707315e8806"))
    (172927, uint256S("c9cccb2a2a7f335da6ca7117434a222642832c6b418d5149fa14e6d94da2113b"))
    (183735, uint256S("ae5ad0a480878bd36e9632ed88051992972b9f2342fb1f2601736a79b5e3831e"))
    (194543, uint256S("ae5410e204d2047a887d84e2518bd26d199aac466cb49fae08ca0840e8e598f5"))
    (205351, uint256S("60bff2493a0eb69f81d0ced76408580eb24a61b02b24b267bd91a70cc5e1e7be"))
    (216159, uint256S("1ff7241eaa12a1004027cb574488223b9f5147f204838e5bba0761092e443e79"))
    (226967, uint256S("33370c3111b657d87e93b3fde284c77812b8a90483fbbddfe9b4d63ed2fcfa3b"))
    (237775, uint256S("4d408806df5f4097a3461f837da543a08265e88fbb6c720c4bea428105a687f3"))
    (248583, uint256S("048814a7fa2706007d7b81467c596a6f09e29c807197e844f197efb871459956"))
    (259391, uint256S("2953abc85fac78ec9bd0cd17c08140263b7567a11b0f725515d3f48b7f795511"))
    (270199, uint256S("716db2caa6616a2b5adb994ef2e87949c82f5ddedb83cddedff74df46ba19d82"))
    (281007, uint256S("805f190bdf2ec029a297f0a8b8e3db5d70993dd954c717db343126cac132c371"))
    (291815, uint256S("2ec93521d341c1bfad5f19d0cca520c5069df4dbc4666e39dd445c6287095028"))
    (302623, uint256S("04ed967a1487b16ef9e9e7a9af3c40a23152a5cf8955801de48eb895fd8a9afd"))
    (313431, uint256S("ab0b7327d37bcee43e8524062f72f94f94fa04ca210f9d65a31b913f3057f7f3"))
    (324239, uint256S("15b96c5e9a4a3bff91be5c4792760eacf6e9eacedf9dceadad02b608e3383139"))
    (335047, uint256S("a836c144ffb4e760e8d8363bbc3313f4d770fb42006306e03331e3a7df88d98a"))
    (345855, uint256S("e36823b48fd954f4af0808a691439c2edc5b825f282e40d0df3e6864d0f98608"))
    (356663, uint256S("794f687e271862da04c5af69ddd047e8640bc8aaec1e308fbc82664ea2d13758"))
    (367471, uint256S("8a8aa9f904a336a234edf483e0bf110a7596b7f481e037d9a8b9e8cdf4f4752a"))
    (378279, uint256S("b4b335ac157fd1cd5d6aaa6a5d40925cdfa283a63a3e11c96a1de0162f49e33f"))
    (389087, uint256S("6a9706889f32ac609ae0fb44ed7ceecce6a8224fec181f00848c0e0093fc8476"))
    (399895, uint256S("f4d687ebf66cf95beba556162299abbce4bb778481d8ea95fd291b5afc37637e"))
    (410703, uint256S("894b4b01f4cd9f7dea0db6117ee32bc37aba78ce871822e3076c0aa874ff8388"))
    (421511, uint256S("80bb4aa0c3b408012b34d16b0b113c1fb210ffcfcae01248db484a605912b7e3"))
    (432319, uint256S("70b66693afab9a95aaeb3531e2a1222e33f8663b5d4c4c0a4d3298af6384b075"))
    (443127, uint256S("8573a3e79be1c5a6968be2cbf258718387cfc8ea3a4f2bafb20bb49bf4f02936"))
    (453935, uint256S("5b98c4e5dd2d6fd5e80075634befc1e730d1b147f9e4fad0b1cfc82300e46e6b"))
    (464743, uint256S("2d6ad950ac0dab163ca450b5147333be911148653dc9bcd0b77f42f4e96aa344"))
    (475551, uint256S("3bee028a87a242f56a069697f0fcfda56c00fe88630f4038be1b148bbcd89ecb"))
    (486359, uint256S("d9afbcb1aaff7d8dba8622634897a8ec083869f56860e22ceb627538a36aaf5b"))
    (497167, uint256S("9ccabbc4d4c3c2a25585b51e192cb2c9d2e1adcad98d67d24a6442d768d07830"))
    (507975, uint256S("71693701cc97dc3abfe65585c0c5d4775d101f633acf302f9dde2a7a5a4b09f6"))
    (518783, uint256S("85b939dee7ed339cf84a62ba749e1ec34fee23ec9fbe7b156495db2ba738c140"))
    (529591, uint256S("2df99b88f1f87ffd02d5db17021e229c3f35ca1f25375fc3a9e302a5ff3184e5"))
    (540399, uint256S("834f5504bcff617ae2f8263a361578b333c9f573cb13c0eb36e122592717dad5"))
    (551207, uint256S("7de7bbe7e3f255c06211b1bf17e7db85934b9132c937423e1c8af0fae6c649a9"))
    (562015, uint256S("b8897718dd6047059f5965c07d8b96d9e07a6ff31f5815c36b9a09c4a7497e14"))
    (572823, uint256S("b9f8ab323e9a5c93f275ce091ff6ac87192eed1d18e36b100caaef1de540da66"))
    (583631, uint256S("6348b9da8fa18f8ac653e298fe5375c9347fd77823242d285ba81afe8e1d0903"))
    (594439, uint256S("2bbcc70fd3949a39d6ac0e9fb2288147ffd4755126dfa73df6f0bc340fe08b96"))
    (605247, uint256S("f8fe81d41ad181f8811b1c4987ba93f4e86e0550d66db5b818aa2f16bef5be92"))
    (616055, uint256S("aeeded50ac42c3fa364b64755eb48029f00bce73d778d7341de275dad03a3f1c"))
    (626863, uint256S("4f2ed6e28a5b651615078b415c5a910301b9e064a7622f3ef391e81ab32d32ab"))
    (637671, uint256S("6ff5cc3b3165a7920ba692fd1e4ff24658698e033b157bbdb5d25c842830f1b8"))
    (648479, uint256S("d3ca4b2ec17a2f836374ba99e7a2e3ad1c75ee373e76a643d100d22b15cade28"))
    (659287, uint256S("76722d3c4ef13569d092ee79765bbaf84e0b5047a61ffc1c5077630ff0d9fcb8"))
    (670095, uint256S("d1093e6f4ad2cc7841c63441602f26d692702ade4bf1a436215fe578b7788a4e"))
    (680903, uint256S("525dabf4df8108dbdaa1ba984c38be9ee9c838d23b68ef4c55de6f6ff64a482e"))
    (691711, uint256S("e5c721e56cca31dc7985bfd51a075be01228b94514913699b1cca8bea4c4912e"))
    (702519, uint256S("14dfb7d3044a31934768a49e5535a85be09b0368d61f6f9b99f35492dfbf73c4"))
    (713327, uint256S("7dd6d3d5420c798de9c130575dc4d038fcd6640cacf0341e357a2827135cf84f"))
    (724135, uint256S("9768b77960551765042ffafc44bfe34237bf4740f910aff09b34ce7771dc03ec"))
    (734943, uint256S("776f23f6493038ed9cef7a38eae8c109fb7a91165ff409772846ed32673574f1"))
    (745751, uint256S("3dfc26760ffb2ed78702ef3616ee51a0ecddca6c018b03b46344dd6c33155369"))
    (756559, uint256S("4d997d0def58bf57ce0ffbdbecd08aff9247943ec0f7153982c5a6427f817af5"))
    (767367, uint256S("5651549f0efe10358337b8f1cd3fa4b4145f1dca574c56b6f82f29ba0c616d1b"))
    (778175, uint256S("d286d8b281baafb448484c1e628b3fa0fe35a30499c61b47b57167654ceba22b"))
    (788983, uint256S("65f873cae71c4b9881c5bde626c4f6af44f5f01f35273c3f78c1bb31b05e9700"))
    (799791, uint256S("d6f68b4829f07507f5393a1d06b78b0fd998fcea7d44f9ca791e96dc54ff8781"))
    (810599, uint256S("7e5156b459cea8baa57568426f15badca427c0968829920173513eb47855826b"))
    (821407, uint256S("390f678333c7e8716fea4dfac8466d3a71e159a7f336d4aa19bd7c5d2e91bfb0"))
    (832215, uint256S("644a35f0bbbcbe526c091339af97a03bc6e2b57dc424e9046cab0f51d51c937e"))
    (843023, uint256S("3ef2d6fc3d175bf77d9f5c92dd6a25b1d729146ddc9a690de6ef774672b04760"))
    (853831, uint256S("8ddb3346f65314a975b9d93264e5a796f2cf5aae927b7fd578ffd7ff81bde09e"))
    (864639, uint256S("0720871c47345eeeecf23328d8e1e03d72fd40a4a19514f61d88da4ff717595d"))
    (875447, uint256S("5b8bb7a22692e070c092592b0c2a4afc836d0fc3bca21ca80e2ea8eb4869040a"))
    (886255, uint256S("987a2514850d5c023adc4dd031f6b277652026aec7d1abe9a3bd5a83f40b3b24"))
    (897063, uint256S("ff6d8b7e6871781d4a46cef02ef2e3072d28d3eaa0a9d19dd1dc69e04eadde5d"))
    (907871, uint256S("5480744baaf5fd5d7c017135d9079b424c5c3f922784ea50558cf442afb940e5"))
    (918679, uint256S("84f913bff245af693a2e260aa828ce5e43b99ad84d3cce58f91cdb37b2099ab6"))
    (929487, uint256S("ecaa9c4419bddc6a387b8ab6977b0489b345356dc8a7b19bd58d6d0926b3d2d9"))
    (940295, uint256S("950030de8b09b0f7c7712ac8b787b046f138d3d1050ded841fef547620bd5534"))
    (951103, uint256S("4ab6fa890ed8596562eb88938b8fa8131e8e28d0964d20fdd8f9cb5a9fa0ddcd"))
    (961911, uint256S("022dc35766af1014e26a8a89e74a220dd498be65d84ce9173362ff94bb4cbf2a"))
    (972719, uint256S("e87949a90209098ae787b69a0ca09eeaf3d9ecedbf393a852b1c52b4ec960ed6"))
    (983527, uint256S("1cfc42aa07dd907a07565af8f0aff535623f45d3ccf150a3109eaaa2a873e24c"))
    (994335, uint256S("fda20f69e4b98bffd5d5cfa53c6ff72ab3e3d9c23a7ec70e41e522e530c9fd42"))
    (1005143, uint256S("ccc5b3e8835eb9dbbecc412587fe12aa59a897df2cfc990118d821f96fda3055"))
    (1015951, uint256S("47ab2272f96d65edb7de31fb16558574d7268124f498c92f1455b939d268e61f"))
    (1026759, uint256S("ab17f050ef0f849d693ae98f9f485d39bc4d9d56eb20cb2fc94eda4572e74032"))
    (1037567, uint256S("459666d417bba0e9e1aaaa9f08eb8063643fcb5bcd497461d8bb74ef2fa5ac61"))
    (1048375, uint256S("b9063bd95a15fe3b20f2847e1790edfe97a74d53cd5bdbed4710616960bf2739"))
    (1059183, uint256S("b996458b7be96736cb9b0b36213063b63b7526adfe8a70e07648d678a6a6924d"))
    (1069991, uint256S("f47699ea754d154e03dd2781f0111f4d0162c366c0ca78d6ffcc2617aa6ded7d"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686015480, // * UNIX timestamp of last checkpoint block
    2271431,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2844        // * estimated number of transactions per day after checkpoint
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

        // uint32_t nGenesisTime = 1620224091; // Wed May 05 2021 14:14:51 GMT+0000
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

        genesis = CreateGenesisBlock(1620224091, 1077816, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"));
        assert(genesis.hashMerkleRoot == uint256S("0x5322195c37996cc752786ab95a76b328f2f8e03d3a9b5ffb465173613d4f97ab"));

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
        consensus.strSporkPubKey = "0273914d51723890516e319ecf24d71749da673c76606941290a0db4842389d693";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "bXXXXXXXXXXXXXXXXXXXXXXXXXXXZEYRfd", 0 },
           { "bXXXXXXXXBURNXXXXXXXXXXXXXXXZ7L2xb", 0 },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 115000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("f4f586f27b0af2d9307015d45b7ff3ba72821ce54bf45110c0e034bda22a98cf");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c33e160f767be68f93c57e2c5af5d77e7d1c83bb82a345f6f2d4ea968a3f5d95");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("70ce131e9bc06cca48bcf8bd0f0f8efff93fe6e34ce9caaaad984c66616f7245");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("b13b0ac7e05c537438198d3e181c2e9796d0fbe9139e2ab3f33352fadd25dd35");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3e2e44e642974c48c9c2e1b6efd5fbb88b253decc6878a9ee64e7242abd5ed5c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("9ce29639f18a952d53bb4aaa2600279c1aef9bce52089b1c970da24be993ae3a");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 36552;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x49).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet beacon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet beacon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet beacon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_REGTEST__;

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
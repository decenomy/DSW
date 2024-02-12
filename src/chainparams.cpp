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
    (14235, uint256S("67c2a2682674578ad9c31b4a3b725094498f5b9be99fc608de80c5406185fbff"))
    (28471, uint256S("bf785500b9889936c5b868bc3c76343c256c3b2c8186825185802a01e86a75f3"))
    (42707, uint256S("51d2f8196ecd369267e6535bbb92ebe906711a4bedc9bd88eede7fbc48b4ee19"))
    (56943, uint256S("e9833df81082d60c9d47e0efa8f509b2ac402bccbb4e396d8faaa2536dbe6afa"))
    (71179, uint256S("5e7359fc59c7004ff428b34f21f3acee489ca490dac76eb8e905a9a1a067330d"))
    (85415, uint256S("d1fc150cb987753bd06f1e92a2cee8e7579404be7a6e857fd38398513b700bd7"))
    (99651, uint256S("877f2ea7f4ee403e672d3f46059bf43415e9ca7d8cbae88912ef9efa1cc061c3"))
    (113887, uint256S("96e9721772f531178384bf18c20f5a23fb206f76d36939da202532b1e6989824"))
    (128123, uint256S("c7e2463a6a6ba2741795ecbce883dc582ed5784754db902e97cc906e876c9eac"))
    (142359, uint256S("4c4816461dbc9781cdb32b403e44ffe5b1d6a3066921f52b421a09fb44f81dbc"))
    (156595, uint256S("7dcb36da4ec3a42b1246b3fe128eef5e13f96e9efb93359b28e66e2d2d5e2faa"))
    (170831, uint256S("d492da449f31b8151e1599461c26a35dfbbb846c7a0e8df1128bfdaa98860863"))
    (185067, uint256S("1637d329929d8edc1d3d72b00251d0cd05f7fd53ff4f8162eb8b495386261e4e"))
    (199303, uint256S("91d889a91af080ea6f037792495927e18ab36a42a4a53b2e54fb38eefdbadf13"))
    (213539, uint256S("afd3371d48524a89f55460a19ea109a1e30d46991a0034b03c27928c665d7c38"))
    (227775, uint256S("f7607576f53d0b2b7a315fe9ade2c6bfa8f564265a63ba0e4b4bb5921360bc9a"))
    (242011, uint256S("a88e58f9dec90427dc3e59ccf9fe2421495ff4fe6160d212d4a1c9eb2c3ea867"))
    (256247, uint256S("c021bdb177ef363af2ad5dfa3c0bacfa09b8a896cf77b8bac23d5e7eb5d930ee"))
    (270483, uint256S("60b24cd4c305bcacd881ffcac820bf7b3d7900af0b6c323a0c2eebb23f586f14"))
    (284719, uint256S("3519248e6f28bcc95737250e98eaf7b63aa0ed448ce283f5782cd8e55ff8813a"))
    (298955, uint256S("6d1ae88f400f6a80afcb036ab70ade932b3ab426466ef45a50a1c4102da0790d"))
    (313191, uint256S("6dffb49e9ac7fd734c12d1365bfb5c0202f182657e5c674e7d6242436f0b6dac"))
    (327427, uint256S("346dbb64374471c8acc0825c57662c6ef0755cd882152d82ee807a571bd72570"))
    (341663, uint256S("36e824c3868cdf17c438fa52d8728d0c137112bc8c0eb0b021f230a72d7b499d"))
    (355899, uint256S("80bd87e5adb4c815db13480e2dadc394acbf3988a84e74e4a05e6413af3753da"))
    (370135, uint256S("b2508629db2595f5a4ecefa69e7d83193cd513152f80ddd1805b0b9a27d0b7d6"))
    (384371, uint256S("2cd521f77fe70d258b1bb6938f52527d4ed921b209ef9f1bd41346839f674250"))
    (398607, uint256S("ee5238a12187a8976d6ab37d499c7e6a1bdeede4fb6431d398e09a9e24dba044"))
    (412843, uint256S("a9a2e4d1a2f19f1bbdc3a0e6c4160c9f9ae9dbb3cd78da6b514c70362797ee4b"))
    (427079, uint256S("dd429bb9ca12d711edb160f4c8e9f500813219aa122c65717a01ebd8545c4b85"))
    (441315, uint256S("333023860f89e8d66266058ad05e8467ad9f4b68f945f67f990f30afdf8d0499"))
    (455551, uint256S("86029469f48da7cd8db7238c055e9404ffd85db6ede634f5495484e68ec211e6"))
    (469787, uint256S("bad6d3f86c89f939ff6d5521ed407eff4016fa1bfd3c1269c9e6fc04ece4cf2c"))
    (484023, uint256S("1c2656930f2a6ea1e6db423c22f6b828431e9004619253d1c302c5ec58b4af69"))
    (498259, uint256S("8f82d58d50af2e0b7f2ecbb70b1675aa950ba593c1ead7ef79583f3996880e58"))
    (512495, uint256S("dfbdafa6866faffbe1ae80f0d25b3bc510360fe012280a3ddc4f45f4999e5ce1"))
    (526731, uint256S("b1717ba38e7083327e11d95daaedf2aa94f260b6ff7fbd1576dbafa426372626"))
    (540967, uint256S("2f6fda5157bd440e2e47a64762c773607fff7cf74d42ddae818aeed5fe9f0f4b"))
    (555203, uint256S("e271b1f10f0e9a31a466d1c4ef3f53ae694c0e90dc13faa0a7ca4283e2a3c26d"))
    (569439, uint256S("400978c2cfe22b717b7681dd4d5d1ce738796c6fecab23c3778d380d783410f4"))
    (583675, uint256S("7c44a7fac0c8ef61e67f6ecba585c91c8f328be230b68b4f009fc3734f0b73e6"))
    (597911, uint256S("6d3a43a9449ee63be1aee04127ae232854ffc00ad5b81cfdd82c767fd98e296a"))
    (612147, uint256S("4e9310253e7320b111906f6a3a34b01000cc077703a1ae34cf649b0f5eaf225b"))
    (626383, uint256S("ff3db78e175e21615e2ca6d00f7e7460bf81301222c03c11839ceb5ce739c2d7"))
    (640619, uint256S("f65d5dc0bb4d4785bc870b286be1b594dfad359fd7760533c2fdeb4a6315c9d0"))
    (654855, uint256S("1e7b521c9ea230adaf8ffe4bb41522e3d140a238109656f1fbf3500a4c78bcd8"))
    (669091, uint256S("3581807b6bf3ba0b4f549da0ee79d61d05c865f02ab8736a03a6ba4b7182291d"))
    (683327, uint256S("5561c77ffb25c52f60dc881fad4cd84c1b5717fc931283c65943cf49c81ad5f8"))
    (697563, uint256S("41d0b5da3517567d8c3b9127338bbbce7ac815cbca02776bf3135888e40ca843"))
    (711799, uint256S("798d030acfbdfb5ea0c457665175f58789e0294e3b878fce76f836ce043f796b"))
    (726035, uint256S("b85713bef72a4c7b561ea282f9ab1ed7c8a5d66eacf25a9c6afa24af9afc1629"))
    (740271, uint256S("41381dc39548cd3f78c75a3ce9eb5e9551ab64c2b3d258d38c5850928464504e"))
    (754507, uint256S("720f93b7e1ba394a081b251becfe86392080dd63f5107cfa6382c8ca5a477681"))
    (768743, uint256S("d8d49b39e9249b0dace3c6b612e34852474ebb091989007312b86c963fb841a5"))
    (782979, uint256S("df81daf5a71370945b0f361435ab5badfacd0097485cd13e1a987f6196978183"))
    (797215, uint256S("a9f6178eb38fa2adf33158c6f309472c888e5d09a06150d06dfa532403e741b4"))
    (811451, uint256S("e749a8d2712ddfcd432a4e113b94049eef14803aaeb1f77bb86d23278b223a98"))
    (825687, uint256S("a952b9a259dfd19629a47adb1a842eeb8cca250209111b43bfe228890122d872"))
    (839923, uint256S("60c097134a77760f05670a96f9570a160b9ca6e87b750f52a13c8b663370dc78"))
    (854159, uint256S("9964e5affee2ae58fb715f4b839c66f473ce38d064ff8176a76e85b793df3629"))
    (868395, uint256S("25087d376ee3a1ac2be9579de65edb71f537807b3ffcb45e94bc57c7b8fd5bdd"))
    (882631, uint256S("af4a0dabc7daa3cfab4835420e7a2ee131ea7316ca53de502373721c875519f5"))
    (896867, uint256S("e0ccf411d0b29172481c0c6f91cfa4c629e6c24b83373faeec4149bdfec18ab2"))
    (911103, uint256S("a6b6c5e8a64016a4e5b84aefdd18d8f010df25cad75572e138f21a845373b5c3"))
    (925339, uint256S("433924e010377a69a1f366398edbecd69119a54ac4ceb48c6924276e0c1e7013"))
    (939575, uint256S("4677a9b40574da6038fdee9b19926719c33356767f747dd9699f573535e77414"))
    (953811, uint256S("8d7db0ca368400be2fe6789568c28e6443c37176af16c933e82f5dbd0bdd164c"))
    (968047, uint256S("e2ca22edce730ba472e21630941b579c7746527926a45dcf6691f50f8ad24396"))
    (982283, uint256S("96142d3d09534df51f7b76fbd019e3662c9eccd48d40f078953a34feaaa9768e"))
    (996519, uint256S("b38fe9596f7853e11a8c3df78a161db8f79bc5a503efc2fee168b95c804bfc64"))
    (1010755, uint256S("16010a2d7d8c60cb8d9e2347e2ef09f1f99c65dd3c7ed06d51f8af5f6b0a241f"))
    (1024991, uint256S("6ea0804fc0ab45a2bebebd2df1d35689bc685b092e25725a21245e10182e601b"))
    (1039227, uint256S("79872a4b511bb721831db939e870874774afcd526c84663a018aea213711ed6f"))
    (1053463, uint256S("0321b0d10cd0603603e081b74c6dba00094adb7d0e8956553f0e54eac931e9db"))
    (1067699, uint256S("33b5a9b6a7aec6028965c584e6907270de07d9e0cdd5728f153f2d0b0135e58e"))
    (1081935, uint256S("da733f9798e6d83d24da72eb9339a4d8a37346e3f743cee50802fe85cf8f9e37"))
    (1096171, uint256S("cee205f372428e7fc3240c97d4a7802517f07d1993f824a93ab2309f9c1a33fe"))
    (1110407, uint256S("c10f1b35d344241f68b2c1cb26f5c2cc3218b49fbdc62a6289e12035ad974e30"))
    (1124643, uint256S("253e0c261d334f1c3a1fde0f4fce4b0209ff04847cab5b6a689e86974e08ebf3"))
    (1138879, uint256S("86986aa7d87e1d30755e3401a380e4ec42f46d0fc404d790a28132a3cc62dc83"))
    (1153115, uint256S("c22b3b2d595c650c4a4378bbba4dd303ffff780f247a8aa6d71fe4009a837119"))
    (1167351, uint256S("eab85072689cc1666794ff6ef2b1341841aa8da849565f3baf8f78ed204646d8"))
    (1181587, uint256S("398abfb7683556f03ce61302790d2cf525320b8f116c80bd1d2368164af85c50"))
    (1195823, uint256S("d1d6218ac396dbc90ae06314092f253d8993b74a76f3905a4ad583289c7bd7fd"))
    (1210059, uint256S("d64ebf49017d34bce8a1bc0965b6c83a5bc7a6b91cb954cc8120c50da8435655"))
    (1224295, uint256S("f09519c2f39f2c5c10471b574ede642a7c5a990ae7bfccaa838985dfdf188108"))
    (1238531, uint256S("bdd47cdeee21a9f78e72c6b576858896a9117846e29f38654843a72b95c30619"))
    (1252767, uint256S("a7926933584bcc848018befefa2d6263db8d47e72311f9a02a0b8bc7426fa045"))
    (1267003, uint256S("7c38f6ac2abda6592ef4e721d7f4d6bf0487db49bae503638d158d06ee377199"))
    (1281239, uint256S("993330b2934c250b170a0407890ae3e33b3cd4bae1e6d68a9eb1e156b60599ca"))
    (1295475, uint256S("38555cf2f6b1e87b5c0da166160ddfb7f0e0705e8ee98ef3f2946c8c5fb0fb3d"))
    (1309711, uint256S("f4b644a6577eaaabca9ec438bdd735bd9d733d11f34a4d20f87506e8912753c7"))
    (1323947, uint256S("a03e3a5f47f23827ecee670fbae2750a91d60abad8c20cc69cf9f3054dcc0696"))
    (1338183, uint256S("b9b1f2e62fd7cb57fea399ae31719ac7c087670245a2dd31438c5db681290beb"))
    (1352419, uint256S("74f29d2c64c3159cac77dc128483c19799ffcec15ab35cd49ed2d0fb9c8ea7cb"))
    (1366655, uint256S("0f8aed7e92ceb16bbb8005f20016de7d7183849a9e8b1ef4ed76e119f44f0c90"))
    (1380891, uint256S("371fd5ffe40c96d8f8d878f80ce9f98cc42f99185e9111e998e7662991cdfe13"))
    (1395127, uint256S("f548c89641a9919f89d265ec3eb72add4ed3c1fc904b096d6740c024c75dfa0c"))
    (1409363, uint256S("f7aadf8f3104b5b11950d1e798408c5a1ec9bc7ddf7c9c563d40ed019c9db137"))
    (1423599, uint256S("f16a6f9eb1dab344b61116ae060f86aff74778137f2d10a1e59354001040383f"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707742155, // * UNIX timestamp of last checkpoint block
    2986570,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2818        // * estimated number of transactions per day after checkpoint
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
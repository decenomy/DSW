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
    const char* pszTimestamp = "Uniswap flips Bitcoin on daily revenue... and it’s more impressive than you think, 12/05/2021, COINTELEGRAPH";
    const CScript genesisOutputScript = CScript() << ParseHex("04f8e575ae6a7fcf97b4cb8b213a74b550ccbdb4cabff3d0bfe9ec15f5b863be758acb3aead94933428425dd5e934dced26f022c0b33682b4ebf5fdce242bbe0f6") << OP_CHECKSIG;
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
    (0, uint256S("000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"))
    (11730, uint256S("417ca64adba235e49b7a4b2afbba02e4e0108fd8d04f0100146c1f4b8cb8583e"))
    (23461, uint256S("a430bea2c14235c382a43a1c2d85aa66f019cba65dc47aad9113dfd76914207d"))
    (35192, uint256S("e2b0cab95896edf6eb1af451cf2175d0610ebce70833725abc5e62684aee8399"))
    (46923, uint256S("a183fb7ace0e53a011b56400859ce561f98a8d2cef619d457c57abb456a08818"))
    (58654, uint256S("4f606e5397caaf5a1ace4e166a2961db6c42b8e6cb6c9f63b0f8c16e74dbf080"))
    (70385, uint256S("2a27ffc9dc8ea64845f3a6b77c0fb45a4f1785b1c92bce080f524c4ab505ade7"))
    (82116, uint256S("e880bd65551b63ff2a4e30d46e94635e49aff2f65f429c883a54df8247c74165"))
    (93847, uint256S("803f43532105d1b41d0ef03fff873843c62e5482fed0c81b3828c49f0093ffdc"))
    (105578, uint256S("f32af80b104a8da2122b491cfbb2f9d0e6cf7ec0c4b415a130b41331206b1cb6"))
    (117309, uint256S("64cf27d7c3a57b1188b1ec780fbe9fe01d7ceedbb9e69974f6a580717a4a8f3b"))
    (129040, uint256S("6d1a8ce840d034ed676139a47f30017b4ecdbe63e407f1f4dbd17f24e0ea533f"))
    (140771, uint256S("7d1f4fc2042b52de01607600bf8cd7a93f6b01663620c09fa4995aa37e51de81"))
    (152502, uint256S("c3e6422acfd977af9e32c06f8f2093375acce8fba53509646855ee8929c05592"))
    (164233, uint256S("578bce5acfd2eb9146dc09894fd3d57db48ccab33ad6ab4de881b79e01815fda"))
    (175964, uint256S("565fd19721541e8b7a367de97643b96729fb7f01628a30fa9ea2961e190d19cf"))
    (187695, uint256S("1c9f053f9f95ac6fa329f4eaf80ec7222ef720152e04fa9e46a14322b891a6e2"))
    (199426, uint256S("298643efa9cdaa4c4b5d5b255328bbb705d2bcd1f74212979c030f2d85616125"))
    (211157, uint256S("aaa1b97a7889e7d717219f04ae5b5f5c7830590fbdb32eef443ea3220dcb7d58"))
    (222888, uint256S("bd73016d063628cced9373b0f9de37a22c73174d03e5da860f49539005322876"))
    (234619, uint256S("2b394e4ccfd940558e7fc9125f616491efe72f9fd0235a77ff7f5cb8a7bd9d8e"))
    (246350, uint256S("5a68ec9cd6648b9e977e80b23dcdd826422957efeff4e6911949de5555c62911"))
    (258081, uint256S("189d8748ebe098fd35137253247f6c89d4f5573e68e592fe416d58a9bf6bd761"))
    (269812, uint256S("2afc8ed2e83059589875ab3e35b9bcf3d66019d6c37831f6f0116ad3f4798b3b"))
    (281543, uint256S("37f55168a812bfabd57c9c80c267b197a70f4ee5f64cfe99efd05f5bf57eb64e"))
    (293274, uint256S("be1aa5082839bf45c7ead1e2ab67a25d4ca6bcfb3f1f669ef9559cdd8cbef5dc"))
    (305005, uint256S("e10525a30008ce7a1344391e3cd2b0a69c096c39614aabc4f3f20ea8e3029cc8"))
    (316736, uint256S("9249a03662fa440f2ba40a7d935b95909b16d1d2d859530721bcfc391c00340e"))
    (328467, uint256S("2f2961616e77314e710bfa176d9235a8264b3f350970d92ebcd010e99d3b2b46"))
    (340198, uint256S("877d6091843dc3206910f8afcf10ec36efc37aa3a8f5106d7572e4e0950fedc2"))
    (351929, uint256S("68c7e1dff86afb39623ffc63ced6182d0f86fe4e7d033dc17fdd9fc3613faf0f"))
    (363660, uint256S("5e31b08be29a05a2c1f6af3d9f777bf52b160f07efc0c6db51f8c9c4deef7597"))
    (375391, uint256S("5c62f3bf0dd9a4b878e3abc4c082c27566eb02080d11092207ca9e2d2265cc53"))
    (387122, uint256S("a05d9fa360af121d3e667fa182529370c212819d5b73463f2bb18982ccff8a89"))
    (398853, uint256S("f32b819366bd87a82f58ac49c4b4a8963ef368408c7543e95ce10b286ba25488"))
    (410584, uint256S("2252644767ff5d86edad81b5c84383536a825eadf9a8c8cc2b46655afaa31316"))
    (422315, uint256S("845a197339d9ba69e1aa67f3e0c1784178186784692bfd1cc03b5476238e9944"))
    (434046, uint256S("3ff6779f1e3dfe1953a5fbe04af44ee635c10750228930e0bf2b4a9a10223b24"))
    (445777, uint256S("be1599ac04953590e2e6844d355b81764e42c8eea4c66670d12e3e2cb4fb29cd"))
    (457508, uint256S("193b754e74379355ab52274933cd9c4d3a429a36c0832d485c4b50bd301443b3"))
    (469239, uint256S("2ffb84969d84e1739b46e93120fecc8ba326b137b803cb0a0589d9cc3e543709"))
    (480970, uint256S("fc22db194e1c52b2f468aae4d502f8db4aa026a517f2d4207859247c75919de8"))
    (492701, uint256S("57164dd6b80cb74f086fa2756e2488073f85283ec244cd987a3ec81132967736"))
    (504432, uint256S("b0be0d939386fdb4b2de3dd24a7f0946b5c2f8e0a7520bd8567411038890b62c"))
    (516163, uint256S("d114d3a2af0ca1e0ca6d647e3df251c4a523f26dcc263f478b40a68b444a060c"))
    (527894, uint256S("972a4bda1df53c39b0d81c915739dda317b82c8d71a7adddaabcb43977224d92"))
    (539625, uint256S("ae56a4114d039fdfb8112f0c248cb808838d5c1756b9f90ec7ad9ee6fc04d95d"))
    (551356, uint256S("789a721516bde8f65e0ab8863fe2848af273d2c20730ce1d8535d5ff797b2af5"))
    (563087, uint256S("32a12768d257fa71ba0a3f781a4d73c4b17d605cdd068df874d6d9b62686c66e"))
    (574818, uint256S("ac00540b45a5c9c946f1666f946cc7335e7142a329fcfbe6d4afd2efbdd1d634"))
    (586549, uint256S("b69117fc7f67cb88a5a5b21d7ece623ff9607231635bd11d06de1e6609235bce"))
    (598280, uint256S("3d35996bb7ca8e9dd70e50000489d91cddc80ff36f06f5be31e1dd23a2815743"))
    (610011, uint256S("094fad24befcdf82a0e440bae46dd55da5464e3eb46ef743bd8fbe154ba41c1a"))
    (621742, uint256S("9674052706fed6f53d14debbde7bfd59bcf14d2d9ca99060211f0c093ece0ba4"))
    (633473, uint256S("30bf1287f879fb3272c34567afabdbac64b05ee3c033a82d22b539dbdd842d1c"))
    (645204, uint256S("3b51cba8feba8058053131f675e1ce344d373c64fc0100f7eaa4679e0639efb7"))
    (656935, uint256S("ea32af06646b9e3f74d0ad7bbdc08d8d3ad637aee9b24b119d7c08cfbfb83328"))
    (668666, uint256S("68a7e91584424ac28e0fb08e01639ac638bbfe95e6d3d053b3ebf1a235a74233"))
    (680397, uint256S("6463393e347fdca394d2d03332ab0d1e3737c80dcdbcd2de911bba0e6715034a"))
    (692128, uint256S("d1c4846ca1283a3f5f230002951c953e605fdce57853cee8e18a34c83bf7c530"))
    (703859, uint256S("3949168be97d98e93450cbfd7b8ecae44874c01d4a0386b42f416548178a0779"))
    (715590, uint256S("d8572faeb166144a9b5d3ab2fd9295d427815539cd403fbf8f6fe526613a5242"))
    (727321, uint256S("e0c597fbfd6bead7c81d7df9278310ec4b978a24eb5e76dc646ddb7181bf388e"))
    (739052, uint256S("182255142348100cbf1302076516fa567336cd391f963fbbdd761c5f624d01ec"))
    (750783, uint256S("23fd07d497dc564db8a041ace76c7d30f9b9bbf50f68f054e925716f4c6ff600"))
    (762514, uint256S("ab54129493878827831b8305069e4dcfe9ad3165d95fe202d9627effd4e11a10"))
    (774245, uint256S("7423c1b6e03a2d564eaed928fa151ace6e6b6f3811d470115f419afe4ed17ca7"))
    (785976, uint256S("6b7a3996acc40502ccd6e5b540b8e17dbd3bd32dfc1cba185b56f59f3c5397d0"))
    (797707, uint256S("9c121600089d031e3c6dcdec8a763a3fa078b8b2644c4044782ed3ececc1ec41"))
    (809438, uint256S("b3d3a793dc983f6c721e65120bb138efdabcfb4cbf7310b9bc085ebae99f3690"))
    (821169, uint256S("16682ced2458b0bb87edcb9a5c6ee0fe17e80f65d3ad936da4e91eb4261e39f1"))
    (832900, uint256S("c4f7e97a005066f0fa4fae670f09ba3734bfdd5d27672585f66abea4a4899eaf"))
    (844631, uint256S("fd081caf8948641feb6594f29fd0b34b4ef1446bfc6f9aea3cb3f4b9b69578be"))
    (856362, uint256S("7a3e390ac34da3fc48e254b009c79fe1a80b0f206a18f3e7c7f00850c5f14216"))
    (868093, uint256S("95a8d826c0a5e76404ccd25b4ad4f263b4cc9177a4357baa645bd5fc5ce55a35"))
    (879824, uint256S("c6548cdbeb206048b52b3a55b0b88f172d37f215415c6b21fd5c10a22446cbdc"))
    (891555, uint256S("19c1c3c65db6d2a7e589660d10314df25a44487cf15c41505b38a0445e481de4"))
    (903286, uint256S("99ecd6e635dc3ba5c64ad9de6a4139197cd3e2e6e2e11a3eda39da34184b49dd"))
    (915017, uint256S("c9181b6c2c7caaa20bdba88d7df33745d8e72bfac690d1f4e1bd7a1fb9872ff4"))
    (926748, uint256S("d5af41b72ece95150ec0d9986bfa44e950663437f00fd4ba54f220da452038e3"))
    (938479, uint256S("9320164cb93f514567d25b64f5f15cb61b84bcdc1d73cd0b761982f2c5182d32"))
    (950210, uint256S("24a73bdddc87e8a8200aea53e1c1982658a4d499a9f2597a70ea851ffd20cc01"))
    (961941, uint256S("90957409e646df30c864ba735b989230843c82f99b99dcc15331a4d1a23dd5e7"))
    (973672, uint256S("49bf674d4ce797e419577ec4b792b7711b0c47e3ee0d27d61b9c55e64e73d802"))
    (985403, uint256S("e4aff312ef0ddd304cf39288a2061399f50cd5386591545843f16e82673954b8"))
    (997134, uint256S("5e24737527f30dec7a92c5e282d90cc46765c44641c0c40d6090485dc9795cb8"))
    (1008865, uint256S("25357b358bbc5fab9019573900d5d24122688ae420024ffc04f7d4e99845bf6d"))
    (1020596, uint256S("10b8568d7d45f522f6a103bfa84c9989bb69e26a44df531dfe947929f8a43dbc"))
    (1032327, uint256S("a0fd011ed39455a35e78160b1b1667355741488c388df4659978bb21673625e5"))
    (1044058, uint256S("07055957da82e40e327a6a1704cc41dc5f7dae4c3df2a75a260a82f844c38c80"))
    (1055789, uint256S("8d4a2010fd99a6584b8a8cc09ae5b4b5a3d942ba2112e1c75280069d91b77ef8"))
    (1067520, uint256S("4e39c37254f7e02be53aaac31f9e762959defe0570ab27f7e03a1d272eb59238"))
    (1079251, uint256S("71b10aaacf5bd6b9eba2812f4beb82ee74457c8c9c1ffead4b73192d1503b118"))
    (1090982, uint256S("6a2b6b6815eadd6aa83e304c1768219d50429c3447f3c186a9c23cc55c192e98"))
    (1102713, uint256S("7fdeeb62ed2089cb538639b1263ba6e21f408148c895fa51d5944e4f3b9c3e10"))
    (1114444, uint256S("ae6cf9636b33adf6572b0975bfa595a2f4b78a0c34fcc64d133f135b0fe0d91c"))
    (1126175, uint256S("2400911e8262cb7fae307ef1c30426d5a79a9d3a5101cd4362586ce2d2232f0a"))
    (1137906, uint256S("0159551ebe1fc8c8bb55633718311101133e9af567d16ec0e1c2c5af20dfda6f"))
    (1149637, uint256S("0b993a040e7be0411f7ddf57ebe6f0a80539f5910f1862f2809f213989c07ee4"))
    (1161368, uint256S("2df04192184a9e0c337ab02926a488ddd061863fa293672a64483301aca62c6a"))
    (1173099, uint256S("6001f5146a42165a92a0e85ba93e6b13a34a49d33d66c6771931344328e0bd8f"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692921375, // * UNIX timestamp of last checkpoint block
    2703959,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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

        // uint32_t nGenesisTime = 1620820532;

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

        genesis = CreateGenesisBlock(1620820532, 580458, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"));
        assert(genesis.hashMerkleRoot == uint256S("0xa5567533e1f5261c38b1b68fcb552f692558d820b338222777893e616bbff4d2"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 30 * 60; // 30 min.
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03edf6c42c34d7d7b43103b1d3360e7024f48aacc2ee14a05248b7656bf4280bab";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "PXXXXXXXXXXXXXXXXXXXXXXXXXXXVtkn93", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 110000;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 110000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("50b97b398887b8173870b04a31a2bf1e5b9c06e6e6a10e0b89ef6fd00e8403e8");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("eaa3c0abdd0fd1bef1adc5fd7e5219023b0a15d2713abe1a2974198989992227");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("c31b091596c132cc1a7ed4a87d39600f42203b50f82be210cf06038b48427cc4");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7e94341430a8419e2bd432bd5822a1839545fb35eddd73da1708c01888d6e22b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("eb883c9b495b398ea70340e6af8c9352622fc3b7bc2d462fff77c132b1d92d4f");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("eb883c9b495b398ea70340e6af8c9352622fc3b7bc2d462fff77c132b1d92d4f");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0x9c;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0x7d;
        nDefaultPort = 36779;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 117);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 118);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x2D)(0x02)(0x31)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x25)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x48).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 999999999 * COIN;
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

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
        nDefaultPort = 46779;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet peony addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet peony script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet peony BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
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
        nDefaultPort = 56779;

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

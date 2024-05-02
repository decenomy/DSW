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
    const char* pszTimestamp = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam felis.";
    const CScript genesisOutputScript = CScript() << ParseHex("04eddc90a654f0335fce2081f682ec2475b935afad5a217ffc9a324b04665054e8a42e14cfdce6a5d11fe0f8e1de9b0ff375905dc58025db46b49f7925d3ff290e") << OP_CHECKSIG;
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
    (0, uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"))
    (28349, uint256S("957f4a555dd535fdfccb2702a161a1f06c298bf3a9dcd20cdd02ca605d64cdb2"))
    (56699, uint256S("2b5fdc01099a0472fa722824ce60578431c12648e2a4a5aba0f3cc6f40afed7c"))
    (85049, uint256S("dd17dcc79e2254b9e515465aa474441f006ec13be6a947121485f07c15ef5c53"))
    (113399, uint256S("3953ee9f268f53ee76225c5486ea3ec7f8b36f84de2ae31ba6dc1828ceab42a1"))
    (141749, uint256S("380af2b50bf945aaaaee281ff7e468157e18a0c773f2e0e08861026b1af4846f"))
    (170099, uint256S("088ff1c394ba00eaac32473bda4121a74dec7a85d96e3ef2c70273a2ab607d1b"))
    (198449, uint256S("37c48d6a93ccf6281440264853662a8f306f52a71306d38048fd03257c808c96"))
    (226799, uint256S("b1c8ab7560c73d9f4e47716af31dcc8485ddf77fbd98311b8d6ce806fcb39399"))
    (255149, uint256S("844b17b1ba69be8eac465cdf954e9df0a30f6947cbc4655d7e5e81357c416b42"))
    (283499, uint256S("19cc827c0c142b5007fa155f9707e4f2fba0eec9881dc5e41364837eabad27e2"))
    (311849, uint256S("59071880f65c609f3b3ea0fd4f803252fdd1f26f9e3d89f880bc9f5e147a9658"))
    (340199, uint256S("81cf9ab0314c78be3b28211a4bb2443cdd62bcc0ac367b4f7f73957112ab1e86"))
    (368549, uint256S("09347f743ecee028d0e048b691c573c6d41f565f7238ac7eb7855831d769d45b"))
    (396899, uint256S("93232ad01111aea5ab4efded39cd5213c9450f4a9ede95eb2950ec8fa99e0b1c"))
    (425249, uint256S("d5f6341d91fb84ed09dde9dd251109ce74cc163dc11979052fa246c6df3cb258"))
    (453599, uint256S("6ea3b7891318614c38f772cbce498f6cb8eb84b58de1434afd7e75ae6bd53b23"))
    (481949, uint256S("3f407c5dd7e7eb69d511716a8db18a87d7ad1c21aea53669ccc1621766e618fd"))
    (510299, uint256S("9e09d1849432dda72e292ab4f227f63f7992fd63285f049fac8058889fd0443d"))
    (538649, uint256S("bf4e6424803ebed73ea32f80bb19789df452a1d6578baec8e283a11d1d4d7bd7"))
    (566999, uint256S("157831416fbdb0f15f7d8cc30fa811d1e28612858f28cbef612f5c38c8492387"))
    (595349, uint256S("000af66def952baa29f6ce4557b6ab58ff0fbb762aa4b732893439e973a6500c"))
    (623699, uint256S("b008e0c2e737eabab851bb0223c64a52b320ad652f7596068fc73ce9f42e35d2"))
    (652049, uint256S("8f89b5315f582f7fcabaa5498d5c040d115a69c5de58ea920699cc890a877a01"))
    (680399, uint256S("6393c876b7bf1010984f97309137aedce170a5cbc83d6beef9899b2140bd3e5f"))
    (708749, uint256S("47fa016b77d702210306d621b1392f486d01a48b7ae3259b863bd8407ca2e898"))
    (737099, uint256S("c721790ef2c76ee475df2dc438cb1a4aced82e0232d090a048da2f80b7cb44dc"))
    (765449, uint256S("b62bc7528ae341f1d302081124742d6167c7ad20eeb9e7f4b08eee7986d9f9d9"))
    (793799, uint256S("88a1ca0e8f2d43ecdc5cea41e86f401e5dbcda80aa7fcb82be0ca50089dfc1a1"))
    (822149, uint256S("a0423da256d472b45ebae2c2dbee146cd55ead4faf7f3e750050bcd492a0564e"))
    (850499, uint256S("2a95a2dcdda07a0ed90ea74101451191f711bb7537430f203749164322484bc2"))
    (878849, uint256S("22278b96dac575ef4639dff8107b3d9ca548080f1b3cd7d965de98c0f5f9ee51"))
    (907199, uint256S("5facb37348c966a0b1e0bcb99222fd47e676497be5040a6634fe4cc746daa6f4"))
    (935549, uint256S("e6a4ee01ffc8c0de779f6692eb53ba909fc0e7a770f3eecdf4f59ded43bbac46"))
    (963899, uint256S("09e88b579928334fc1efc9071d015674b46687e2b4ca455abc83c44c777e6834"))
    (992249, uint256S("f4eaea0326fb4516f5b898eb2fd11dfb7bbd39be05a37c986abd4ef0511ef984"))
    (1020599, uint256S("1a0dd896a33a67978bb615a3bc9458fa30e30173d6401be142214e0edff0e52f"))
    (1048949, uint256S("687754c4baedddd27a2298fee00b9c1211e3c2c5602ead9e4304e007d6e1673b"))
    (1077299, uint256S("8fcfaf5611203ef82308af63a9457c1241912543e0d18b65dea9f6726cb20e99"))
    (1105649, uint256S("091dba2cc7a11df27e2a9d74941344bff480ac8df5a05f79c5b68623900f3055"))
    (1133999, uint256S("081a467a125785e169f7237cdb7f143c1fb8892426698f2b748095edb0523949"))
    (1162349, uint256S("700eb464075a9d80b98b5c557dc1df63abdb0f968ded310c6b89b4bbef3f7066"))
    (1190699, uint256S("bebb7faf31d87c272576372a5377311469e811a5cdf07978747bb7e506b5d58b"))
    (1219049, uint256S("39a528f7a4995b3c74a72081ddf7eb5a69d5aa27146d4bc83e516cb8d4dfc085"))
    (1247399, uint256S("d014b535817197cab07bc70338c446063ff435eb350b5ac79e1bf4f9e6c57ca4"))
    (1275749, uint256S("daa0e04ec54c0ef0ad043a7699143687e88f718ee1c7c24e0dd203de443f687d"))
    (1304099, uint256S("3d2d29f6dba70b1fabfe3ec3d598315e21531e27bccc5628e6b23a5041d25be4"))
    (1332449, uint256S("7e876d5ec2ff9a36deae05d005fd491c35d427c7bf979c157f9613ee03273e7c"))
    (1360799, uint256S("9de1a1e4b780116dd6794ee46d9802f5e12b5914e8fe4cb5564b66f0c3ef97e8"))
    (1389149, uint256S("74b6ca3088b6a7145f79f6aeb8f13c944f836aef25099369b4e6b1136a3e5b13"))
    (1417499, uint256S("a1fa5a6aa10264622f4693ea9f38e03ad9d5005d61642e3889fffa624adf0f77"))
    (1445849, uint256S("1f72801ef961fb5b699568279aafaa21f543fbac3c6532903071f99d1fb21bce"))
    (1474199, uint256S("6529341fa26b85fb4cfc8f1d078e1de731381a9358cc79e924d378943fbcf8b9"))
    (1502549, uint256S("70822bdd2dbaf31a5a43b402d9766f4f9d090aad7aed20c50150c568a9001a4e"))
    (1530899, uint256S("6dd58bc69016ae0771e8d85f0f61b3e14d4f7893ddaf8e44dda2db6bb5600635"))
    (1559249, uint256S("d2fb5aa766c3906a2b2d1b52fdccdf169ac7f2cffa80e890c046340aaf05ab9e"))
    (1587599, uint256S("5dbeb39b353d682382686120cac645199cb9555f3a29f89a94c3a4d0fd3fcfa1"))
    (1615949, uint256S("ef14fcc311d5e70ea51a9ee4764729aab67166269dcb8009fa11c45568aa96fc"))
    (1644299, uint256S("250cab55eb5366f2e5070a64379f8c19e12105197070050cc53665d16d90c290"))
    (1672649, uint256S("35212aba499aef934fa9d62b26861b672da2ba8ec0fa9c88916a3e19ebff993a"))
    (1700999, uint256S("5eedb3cbbcc82f3b241e4d6ba726aca8c6a82353f1084cc6d10c338ea5f7ad73"))
    (1729349, uint256S("602f26c2bab61e65ce0aec908c95043c20819288a9b6a7836e3808dede20f7a0"))
    (1757699, uint256S("d2af302efc67522af7869d926bfe69c65be4b7a9b2295583b6e16f55b540e700"))
    (1786049, uint256S("2b07b9c0eb9393f541063ee90f76046cf858bad48306db25ce2604f0860848b2"))
    (1814399, uint256S("bde873f278b54c501b62f36df73903bd0fad50fe63356466d91bae535dc37103"))
    (1842749, uint256S("b2f82b0bb9033fe0b9dead6c0f5175266d37566679a07d5af42222a94e625763"))
    (1871099, uint256S("f5bcc06de3dfb5db585d07878bc671e8af59954391659add57badef38da0f7bf"))
    (1899449, uint256S("1f79cb965b0a46e105c89bfaf8ea02ce3688a5da3b602f81fe67a6eacd390ddf"))
    (1927799, uint256S("8a11a4dbfb2fe56456e56d296a1552d6a1641af16b02f2e8e20e3f6d1e154645"))
    (1956149, uint256S("a0be93ff5661c68637d756edb740bea4b77bfa04b676f7ea0ed0da36f3ca9c40"))
    (1984499, uint256S("61120d2f0473ea723cf5e440e1480b92359ec599c516e35965fee45ae237f99b"))
    (2012849, uint256S("5ceee0ba479104c0e8e2d6eff997be59e4871a0325b0a0a52644168f11de72cb"))
    (2041199, uint256S("26bf0430f2100652ec3bdd399f3dfcd512542553ac37d07dd9a10f6820fd31f1"))
    (2069549, uint256S("e9cf9a20ea17d1d54b0fa6a00d805a9af9d1f88c0f75a591fdd4b874dc946b0e"))
    (2097899, uint256S("f12076362d6895e7eef879f4484915171b8cadfcc8d5fcf9b696648e9e35c5d5"))
    (2126249, uint256S("3913c93bd44edb7f55e434188d8751453b0ddbe635eb0d7f08cb9b1dd6a861a6"))
    (2154599, uint256S("374e37c5067564b193a30f4ce6c969b17ce06f6c021515fc082e68ac6033af02"))
    (2182949, uint256S("dc7106ce6918a5d72c0c16bea76c85219c47c2fea85cc7ef98eb19d3d795a09e"))
    (2211299, uint256S("991f56265d4a75209c669972c11433c871b17918eae97909cabf39e1336fa203"))
    (2239649, uint256S("f14793913b18071e3b3d53ffc2882c34dc245e63b56df1da284b4251bfe01010"))
    (2267999, uint256S("2a7cca7a5d49b5ea9e4be8efb8d656fde15a7ff9e9508f6fa4806308d27f1eb7"))
    (2296349, uint256S("7cb6cc473481b327e5a1e0c1c3374baa437befa6bc6b0d4a74e9cfe64683310c"))
    (2324699, uint256S("2451247280616542c32d20a681ff898c47da07046861657e36ed8937dc4b0219"))
    (2353049, uint256S("b6a531f0aaddc9c158343a48cdfd806fbb0e4237008df6eced7f9a2f9a7b456a"))
    (2381399, uint256S("084eed97e350c984be0091517e0dcbf1e0364514c927d6d4ed75b5f5d6bc6a7e"))
    (2409749, uint256S("05c923ce5c398ce6a6c94eaa53422f46341c33f9a5c66d4560d0c5d96a2cb42e"))
    (2438099, uint256S("78badb1796f6461855b251da88c98ef48a2609594a3dc99991dc5c953a687c0b"))
    (2466449, uint256S("386d1a36bdb9334c118780ce7e77c71ddb3960470b306be4b3f3ee1027553823"))
    (2494799, uint256S("3cea7fdd689abb31c2c8521b3766acfce19073413bbf953cbe451f53de665c80"))
    (2523149, uint256S("82cf7c2a78b4684d2e2f208aac1716fa215a428716b01a10b4e750ff6e2402c0"))
    (2551499, uint256S("539110e28ca721a71c1c27dda620b5a5f822990f067e0b02e8a1640f148a2dc4"))
    (2579849, uint256S("0a596f0a9b1d14ef552d9e659dfd3c94345352286512c593a84a9cfb75cf4d60"))
    (2608199, uint256S("2ff42823517e3a837b6b27c066a64ec3391e89e9c730eceba1a10c890bbd821a"))
    (2636549, uint256S("0ddf57052dda6559527b8886fef0b33494ff2e18587f0428fc667ea510af1281"))
    (2664899, uint256S("1f0988a071f54c6cdd82e567d3c2e1c360a750cb69c5943c71dd770d6e685a32"))
    (2693249, uint256S("70a2d8a535de5185086614d4e345153b4c99f48f18de2019034330a10781f052"))
    (2721599, uint256S("2d6cff615f9f588e417ba5de7dcae2b9317a8039ce29fefd101ec5780de08f37"))
    (2749949, uint256S("deffd29942ebaa5e50ca72677ea6759e593f98c1c062a8016e0c46af0a5858f1"))
    (2778299, uint256S("f6e6c973fde4c851ff761e452828251cad1dc10c434802b432a5882ba2b1290c"))
    (2806649, uint256S("8c553a088ee8140a6360c0b672b7338877afd98da8a0618312a5be9c6a9b44af"))

 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1706179920, // * UNIX timestamp of last checkpoint block
    6971450,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"))
    (1016800, uint256S("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231"))
    (1106100, uint256S("c54b3e7e8b710e4075da1806adf2d508ae722627d5bcc43f594cf64d5eef8b30")) //!< zc public spend activation height
    (1112700, uint256S("2ad8d507dbe3d3841b9f8a29c3878d570228e9361c3e057362d7915777bbc849"))
    (1347000, uint256S("30c173ffc09a13f288bf6e828216107037ce5b79536b1cebd750a014f4939882")); //!< First v7 block
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1575145155,
    2971390,
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

        genesis = CreateGenesisBlock(1533728621, 936030, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000c89a16d5d75011aed4ed5e21efc7bf3ffebe7411f46632771c0ceb907c3"));
        assert(genesis.hashMerkleRoot == uint256S("baf314231c2c162bb4bd33665c67320df47e74812821b1ad78faec22c9795553"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 50;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 600;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nRewardAdjustmentInterval = 7 * 1440;

        consensus.nMintHeight = 1700001;
        consensus.nMintValue = 8100000 * COIN;
        consensus.sMintAddress = "KDkx9d9GRYenjfGtuLSEkCzECH5zXHJbGW";

        // spork keys
        consensus.strSporkPubKey = "03458aea0319e726ffaa7e97b278d0c1d9bacbd983e4a3cec6506e7988380da53c";
        consensus.strSporkPubKeyOld = "0443b94e8f01b62c33c61a8b53b8d7a4d522dc6183fe04639538470930a4bf7f7bfc2453adcdd0e7e8a1a7208c651054bbb0dcbb723b2013f424fb9badbca39462";
        consensus.nTime_EnforceNewSporkKey = 1638316800; // Wed Dec 01 2021 00:00:00 GMT+0000
        consensus.nTime_RejectOldSporkKey  = 1638403200; // Thu Dec 02 2021 00:00:00 GMT+0000

        // burn addresses
        consensus.mBurnAddresses = {
           { "KJXXXXXXXXXXXXXXXXXXXXXXXXXXW2cAfW", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 751;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 615800;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1700101;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1100000;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1150000;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1700201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].nActivationHeight          = 1700301;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1700401;
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].nActivationHeight   = 1700501;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1a2340ca777d4c118bc4725e5326fa23e9072086728788ddb905ef9acde7d4a6");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("54136b30651f42501f26dab7859e8884860b5af7455a6707e0afdbd2957164f8");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("b479ca5af0c99323020e603fb0e96de1f1a0ea13c376e6c3a26ca62c06c3829a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("5dd0f62b4819eb575f886b02acd272e07de7d4ce8101688c15fe42d48200b2be");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("bd5886ac6694f69c9179f1ea48c458af0a8d56dd76c3347cb7742c5849b9f7ac");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("f025a2eece95a7570981a72ae9cfb9cb15a50314ed513083d9930131ca0d606b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_CHECK_WORK_V2].hashActivationBlock          = uint256S("d05b24a598bdb2bd990fc6d65be4343081c6810f538111e73b0c071268d8b663");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("127bc8738c0785e04bf1088133bac09545b84591b7b20088d88a6732eee7fd77");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock   = uint256S("c3069fbd79ba32ec7dd3ae8a1be59b2d2594e458ad5fa1fe5ac29ad0c2f64754");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x3a;
        pchMessageStart[1] = 0x95;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x52;
        nDefaultPort = 39697;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.birake.com"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 179);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x50).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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
        consensus.nRewardAdjustmentInterval = 60;

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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 1941;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight           = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight       = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("s1.birake.com", "seeder1.birake.com"));
        vSeeds.push_back(CDNSSeedData("s2.birake.com", "seeder2.birake.com"));
        vSeeds.push_back(CDNSSeedData("s3.birake.com", "seeder3.birake.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet birake addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet birake script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet birake BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet birake BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // birake starting difficulty is 1 / 2^12
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
        nDefaultPort = 51476;

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

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
	// pszTimestamp = Headline: https://cointelegraph.com/news/another-defi-exit-scam-just-made-off-with-20m-in-investor-funds
    const char* pszTimestamp = "COINTELEGRAPH 10/Sep/2020 Another DeFi exit scam just made off with $20M in investor funds";
    const CScript genesisOutputScript = CScript() << ParseHex("0448790ec8f49697a1b0089fd998e932231ba4728c8c3edc2b50b65821e58b441117036ff66337ea5021baf94e29ea83117e885d67018654d0869bbe2eb1d74dd6") << OP_CHECKSIG;
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
    (0, uint256S("00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"))
    (12984, uint256S("211ee1715b57105b0e9a38d53aa0ff3a60992f9c37a6de5e7a0447e31550ad9b"))
    (25969, uint256S("94960d54cc4a218b78e41fe3017f473f529b563486945bc8ace5e2c298502cd1"))
    (38954, uint256S("db784f82088bb0d43dcd08164168d09e886a3fe6255b64887b4fab758873e603"))
    (51939, uint256S("07bf87150fd0618190a20d9f6da4d6e735311e0e03ae2eca9fd242c6abddafac"))
    (64924, uint256S("f073af3bc7eb18396267bfd2eb10630fcf778f8ed2d1d685f17baa2aec5120ec"))
    (77909, uint256S("c43333640bae62784a1f34becb68ca33397b18e021f496b09afd40d37e2b67e6"))
    (90894, uint256S("e133080e6d6827435b46bcaf6b0ed64465afa4c0628e885c67f396083e4e6f1a"))
    (103879, uint256S("0416fea939de59eb6a343b421ecefc9cc3515d483c23d153d5aa4690c7ab95f2"))
    (116864, uint256S("ef50f3918aae00f280d80da23a7114000b1a6cc31a162004f438983a5d5a32c8"))
    (129849, uint256S("cac2e3bdd6251ac1acfddf14c24e54154012b34ff1be5fa6daff1352a7210589"))
    (142834, uint256S("1c699c7aa4b9da9b0bba8bdadfc4e20aaceaa6c150e27e60e76215a018deb38f"))
    (155819, uint256S("1fe98ae79f6ba0de31e244e2c4806c1ec683e0ffaaede65701908cf4f4ecb46d"))
    (168804, uint256S("121a10fc40e76b6eeb886debbf0f0cd36f1ea4f304fbbfb1c1bc769ec4b329eb"))
    (181789, uint256S("0441773edf8b34adbdba3930c37f33368a99e5a45a8915ffc655069e2e49ddb6"))
    (194774, uint256S("b4e65fa4e631cd1b24e529e02c500d6c1f298f90746043294fcee36f207fd92c"))
    (207759, uint256S("68316bb286773d0c1980956a50af4ad77905e48b746b9a31d4d7b33120affccc"))
    (220744, uint256S("230f9db45628d8610e1aafc9f9b77d9ba7a47fb742c71defaac203c56fce92ce"))
    (233729, uint256S("4d2e24136df2f4d248d780c6c42a4c6b8b259edcbb35ffe2f31b1fbe77d925b7"))
    (246714, uint256S("1d7bbc8a14ae6f5f510ee27c34dae1f3a37471cad754b19fcaeb7f922baeebca"))
    (259699, uint256S("a2b343f2f9bc60211a89645c2b5b6ad8e9e996e84cf76ae9efe8266a211b5132"))
    (272684, uint256S("c0ce9af48abdca42266eb10c10654b1d346025494292b380c286f106c86b7753"))
    (285669, uint256S("f9adfd663a7db8b67c80b27a9f74271c18442b99016f6d10f2fc9b60e212ed9b"))
    (298654, uint256S("e05e5cae66711a4590264849560dfca5aed07e5fc25cb31c11f34e358f80e75d"))
    (311639, uint256S("47818b19064216e378a2b5b497b4cd0c8ce77331609e1f189ea1ec02b697b9aa"))
    (324624, uint256S("980bc345f37a31c31e34bc9b8992691d0dc4a6f38e76de274c091b6acf8da5bf"))
    (337609, uint256S("d58e91f958c37b11fb2859a563e6cad09e5eb188d021bee1a9d5b1249300cd65"))
    (350594, uint256S("db8edb4946bf75a1c6f96a89127b2ca2f144fae7ed0d71503ee67d7d5da09819"))
    (363579, uint256S("34dab37ce153115bf8d6635c267c6a3724e70367067089ee2cfbc54fdc6dedf2"))
    (376564, uint256S("f91b686d64b285fbc29a0e68a29e71071269658c6ab6af40cb534404925fd324"))
    (389549, uint256S("b78026bf08d78001059794374f88898ab56dd85606de736def51ea9f0ca01a28"))
    (402534, uint256S("bd8e88bec7cfc1fb9fe5445a32c5145d67cf5be537841441b1cef27c1ab6b7f6"))
    (415519, uint256S("742f212b19636af7895940ff17a0220580b7e658141b3018f7ffdf6b92eda60e"))
    (428504, uint256S("a5d35e1340b331b96b7eaefcb042017a6d8eddfaa16920e6ff8dd883393b579d"))
    (441489, uint256S("93fd9599680a175e24e4b5ceb59e5e5df1cd59fc04c0485cbad31f5ea8a73611"))
    (454474, uint256S("ddcb24e3d9c20139b7bc74ecdd1b7c17c9845113f7144f43c4961fdad7971a88"))
    (467459, uint256S("177299201f4c3cdc51b963a82368a8740736375caf5876a22355d32e58316c5f"))
    (480444, uint256S("dcef79cd7dfe41750a0697d46acd1b046ed5ee3f0da40a1e6c3d028f331025fd"))
    (493429, uint256S("576e29b992a5eca7b1f3fd1a773052a43477ee1a3f13302da7321cab55371756"))
    (506414, uint256S("98ab323c126cc62818a877ff110e0adf0f4dd9987eaedf21aa3d03f3ff9911d5"))
    (519399, uint256S("fc83f66981e8ccd2aea095df6d3b9e0bebc0957b2e75841404a9186c20cfe4dc"))
    (532384, uint256S("aec28b385c8d6ab9fe762dc5203032451dd05a828d6955c50255d8b8ad8215ef"))
    (545369, uint256S("260a2159544f4e13c18defc0f5257d4bfc27eff35044c34ad2e70400404272d8"))
    (558354, uint256S("f87dcf0c973eee49a7184a6dfca377a86a37f03783bcef1d56fbf2fc4efeb577"))
    (571339, uint256S("3954ff17007b29df6f4cc21fd2dc5503ec886d10db47a84b041c5d580c9df4a0"))
    (584324, uint256S("9cd44e2d7d30d7c0ba5dbdcdde9d0429a0bac89cf3d657795cc331006a768646"))
    (597309, uint256S("a5cf7b7dc204d3c7f8a913d67d1f6d2eb4764fabbf7aedf222f98b55eb61f281"))
    (610294, uint256S("ef82ae0824a4ff8296c3f6f3d6b5820c901fdb642897875612987f47ab011171"))
    (623279, uint256S("d230d971413867b54d4735097af439b92eec0d284bf82a8b8232a59f90d7aef2"))
    (636264, uint256S("ebeedf6761e989652afa2256c76700769b226c7f4a206f6e521ff2a3bbb41713"))
    (649249, uint256S("5eb4c2a1d0c34cac6f91ca3d23799e697b6c0b8a03947dadf5e45058e1b487da"))
    (662234, uint256S("fa88f266a3d412f4483444150fca6762d22858218e7519b94dc728d7996a2a43"))
    (675219, uint256S("7c536c6d7356307e5fe1cf8635b642f952d21c2062da61dd8f621e4590101f4b"))
    (688204, uint256S("b11a67a529a5b3fbe5248d9d8c7c580ebbe865309d5c5c98208235c60e5a473d"))
    (701189, uint256S("0241038e5d542981489d81c0d4aa5843291d72d6d1f7e60aef1a28583d408196"))
    (714174, uint256S("bd09add95a49436df48dc6a0beb515302dcf8e761578dc2fc80407b7bc40650d"))
    (727159, uint256S("f74af8a919a5879f932996f8aa1dcc7b513bd6570ff045566b4ea3ca4f8b44d5"))
    (740144, uint256S("83e8e35bfa1e51e14e504109704573ae8b5a3e9d9b974ef8c84ac73f28a5e5f3"))
    (753129, uint256S("8be30dac301b976df11a6c73ef245e11095d051f61d0c99333409050850327f9"))
    (766114, uint256S("98468fbb843d8d73fdea75fa5bac3ce79d8365897b436f49f25113632cdeb23f"))
    (779099, uint256S("ac054231ac0cc316cbb7253f2200ccd9adc7c726bdc0764acbad680350ec551a"))
    (792084, uint256S("f125cfb04c25a533a34800c2ee851a7547783d4ee798e2649af2eb6d93dd8b25"))
    (805069, uint256S("ea4d96448fdca83084248796bf23dc1d68fb2a3854f201c21588727a29f85613"))
    (818054, uint256S("a9b6e8eb0df0d4018537bf542588267bb0c9d1d5dadc668b380f89893746d448"))
    (831039, uint256S("6cc6e21505edb9a3e0cf3dca32f73abcc9aa624a97a2cd0620a63e5dd5c37401"))
    (844024, uint256S("b0d8f2164c726cb83213ed3a4a405cc469b6f0546971b613a1aba818e94dc886"))
    (857009, uint256S("29db0b9df62930586e382254ceac576a7322d20d9395b32f1354077efa42a490"))
    (869994, uint256S("7c843fb01ec318bbe10d454020f863442af2fad2d760c6e44c316cbc90a34b26"))
    (882979, uint256S("b7a2a22ceea0b3d17711cd0d549444e58dc8205409660a980d4a7ab4997bd2db"))
    (895964, uint256S("22f418fb4bba23ef0ff479d1ca8b431fdcebbe4b65acf689ed49bbd4ab1f2672"))
    (908949, uint256S("5db3b8d1031a0e6ae6283c23d315417e8c78cb3f93078901359680720ac1de4a"))
    (921934, uint256S("7e9144c97e551995100da617dc8749dcc34e749308361fa5f0e5eba1d7c16342"))
    (934919, uint256S("8ca23faebfbd84c5275ac55dddf2b7897e1351c281aca313c1ce1a31aa70ab45"))
    (947904, uint256S("7429692660299eee7fd7d9c8ea7e8a59ad2b8258094ab3c621111ef56ca3c1de"))
    (960889, uint256S("129f70ef0e039bab36b1d3d158dcaf65800c5ed5693868c7abf64b243d45cd5d"))
    (973874, uint256S("d9120c4f3507868a0155473c03b2ca0b9fed4b0b371756acdbaeca6e767f1d12"))
    (986859, uint256S("699f62c9536dad7d8fdc2c258293e02a87f956b552a371b7ef0ca9f21bf587e4"))
    (999844, uint256S("19da9403d6f22462eff83b340f07e89fa6bc5c6fb3e685e69abc50078ff9c553"))
    (1012829, uint256S("1c933e2a1c2ca011eb2e5db85f098f6fd505f58cdae39b96a71030577f47a443"))
    (1025814, uint256S("ef7d495e443e5e616bf02da42fa2481289b2bf5a9fca5a5c2777f0334df8826e"))
    (1038799, uint256S("156797891a12d205668260e7791232ca06fcaa2f1b84200e6e37f7dd02656bb8"))
    (1051784, uint256S("31c4803cc1e4a6d4f3872a3b1e5d8ee85856a86e0f070ec785d61db4c902cfb2"))
    (1064769, uint256S("a4ce50ae510223e4c0713e19ecdc54fb970d8dfeb076feac3a3c4c4f84112552"))
    (1077754, uint256S("5278ba287f1add7f3063e39b1ab4a238b878dd3b69ef64fc27a702792e8bb3ab"))
    (1090739, uint256S("a121a7f284691e9a88f5c6cc597ec88b793bc97a0870cdf293f79b468532bace"))
    (1103724, uint256S("9d29f50ce6a8c1dbfd5280dbe49a29b6ce4a1f62e8b66f9a8dbd979e66544fd9"))
    (1116709, uint256S("c927e71a94c42aa69501453a273a4b8b263843284129b146f7c974a5d70fbd6d"))
    (1129694, uint256S("afc1005342ab35ece2e94e86c5144264e1136145cd46517a1e2133401603466d"))
    (1142679, uint256S("7e194ae77a513bd03366d4f5530ca8d1922cb36e6187a8e13a41d42e61656bb2"))
    (1155664, uint256S("f72a09aa54d8eb80829e477601be47df559dfa266fd2cbf02f347a3efa504181"))
    (1168649, uint256S("0f35a4776767bf2c9236eba0f75be25dfeb9b7d21a42b2fd387685f6cc151d04"))
    (1181634, uint256S("02538e8ea78bc41e39c72985160e5bf30707cd2fb8572d723ae33d7466351ce4"))
    (1194619, uint256S("122e07677b71508c97c6a589de7ec96a2f2a352060c0f361d4a94ecb16ee5e50"))
    (1207604, uint256S("d4956fbfb47153e07860b020d2bfc9c93a82798fd7638d45c526d313a0d60ac5"))
    (1220589, uint256S("b23304fd345c4d6455c3b044cef6860696884a9405b5bdeb4975f1a8c2e44504"))
    (1233574, uint256S("e4e265e8d7315ee10a3af7ccf2f62cc89a28f347dba509e0c43acf87e70c2538"))
    (1246559, uint256S("ea122f5c08fc56cb9f28106e65f00f7ea1af3d54d1000d59d008f331703d2ae1"))
    (1259544, uint256S("9514e006d4458400342d4152b14625a8fa9ded18c86ea517b6bbf8c79181fb84"))
    (1272529, uint256S("0bca5155117195fb0cacbf6e01f6855133f254fd38ff9c7a88910f38bd4aead9"))
    (1285514, uint256S("ac86531689c8973afd6db06926b845c6623c1a46bd766ee2dfac6b313967b208"))
    (1298504, uint256S("b14f1a40e8a4c28f45c054ab3a15e89694cf74cd08314311003f67e9082eb56d"))

 ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707563835, // * UNIX timestamp of last checkpoint block
    2768673,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint. 2000 for 10 minutes of bitcoin blockchain (1M block size). With 2M of block size and 1 minute of block time, this field should be around 4000 * 10 * 6 * 24 = 5760000
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x000000313693c8b25165dbdc8498b8c0084fa24ffea6a02765733700fbcf7467"))
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1599766365,
    0,
    2000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"))
;

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1625312841,
    0,
    2000};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         * Salute to old Kyanite code based on DASH code base.
         * Original chain launch was made on 10th of September, 2020 as the pszTimestamp headline.
         * Genesis block creation timestamp (1599766364) is reflecting that day.
         * Original chain consensus.hashGenesisBlock: 0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1
         * Original chain genesis.hashMerkleRoot: 0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71
         * We keep both consensus.hashGenesisBlock and genesis.hashMerkleRoot of the original chain in the new DSW code base.
         */
        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

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
        consensus.strSporkPubKey = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.strSporkPubKeyOld = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "KXBURNXXXXXXXXXXXXXXXXXXXXXXWJmF2X", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("a68286b8dd2d7730ab2025201b38020fa68592010ac3e4bcbeaf066b40533802");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6b369beb95e63b6dab9c5f52e26339aaf5bfdccce0bad968c21267464829c904");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("4278660ffb8d8d12cc070eea2f8390aa84132fef799675a865717e444d5722e1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("2123647f29f91a35aa429913db96e666d7de476f1fc109a8298bf6f291b36584");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("04721c90cd55aa14dbf5cf0b24de60311b37b2deb0e98004b01b2e90c4d3b031");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("8f7c1d65300983dbf2d99c70051d20470f0088275d6bca9a69fbb2b8597585b7");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0xf9;
        nDefaultPort = 7757;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.kyancoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 46); // K
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);  // 7 or X
        // Kyan BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Kyan BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x42).convert_to_container<std::vector<unsigned char> >();

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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1599766365; // 2021-02-03T13:51:41+00:00

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

        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1000M KYAN
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 10;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.strSporkPubKeyOld = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "kBURNXXXXXXXXXXXXXXXXXXXXXXXUwNvtS", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x6a;
        pchMessageStart[1] = 0x9a;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x9f;
        nDefaultPort = 8757;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.kyancoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 107); // Testnet kyanite addresses start with 'k'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1625312841; // 2021-02-03T13:51:41+00:00

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x207fffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x207fffff, 1, 1000 * COIN);
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

        genesis = CreateGenesisBlock(1625312841, 1, 0x207fffff, 1, 1000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"));
        assert(genesis.hashMerkleRoot == uint256S("0xa50c4f55f3df2d2ecf33f0248f631ca20935c49dccad9bf2107911d94c5ab0fe"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // kyanite starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1 billion KYAN
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
        consensus.strSporkPubKeyOld = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
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

        pchMessageStart[0] = 0xd6;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x9d;
        nDefaultPort = 9757;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140); // Regtest kyanite addresses start with 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Regtest kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        // Regtest kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.
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

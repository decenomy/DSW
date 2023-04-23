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
    const char* pszTimestamp = "Druckenmiller: Ethereum is 'MySpace before Facebook' while Bitcoin won as 'Google', COINTELEGRAPH, 01/06/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("040f65236f5c763bf979ef7316dfc2edca12b443c3fade71abfebbd931839e8fa775c214fb485003697d28b8fb2408b16114c219584376d283af0ca2fb38026fec") << OP_CHECKSIG;
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
    (0, uint256S("00000fbe4cbb6044f6156fa4f4396521b1d28d01307aadb0738d26a88853078d"))
    (3472, uint256S("6c7f22721ef10ddbe0c0d3345369352ee80e055cdea56016ace1004e85d759f0"))
    (6945, uint256S("098b9628e33424bd42f217321e6c7691e885496d54a9ab55c2284e2c5ae27ed9"))
    (10418, uint256S("8ea622ed2d58d306cc14d067275f490c08d9c2a09740925b72a3569729773ce0"))
    (13891, uint256S("8273c0b0eac3eef0f29b303c6aa75706437c222a2e0f07c6f852dfdb6f7c6fc8"))
    (17364, uint256S("c10c5f539a3fb9765817e81808b1fc65c720510360dbc95f817775fb163d7f20"))
    (20837, uint256S("7c8b7f0a2347dd284f7972c0c8aa4ced62a7299fc0696a87b8075822d2a007e2"))
    (24310, uint256S("1a33225d9b7c9ef32a53810ddf7668b3003c5d2f8f91077e27db07484451642c"))
    (27783, uint256S("6751ff3d21853bc333b5275e15cdba40659a68501e62d7adc10ad17637ed3fdc"))
    (31256, uint256S("0b26ea4da9343455ab6115a1360d4e9f86db70006c2ac0491c7a25b46936b58c"))
    (34729, uint256S("d30018abe7e142958dd17df749887909270bdc78d123b152e91816b4e94ade1b"))
    (38202, uint256S("880fac591a4b94b1715f9e6934a364a569bb6aa1d6c9bbf5da5cf667df5e21a7"))
    (41675, uint256S("11197fe519e73239adb35153e758403656bd82ab27b47cae43d41d0b05e935c6"))
    (45148, uint256S("eba1fcc54694421de0e2408943c6f244e695646b745ec0707b7f636c88a62c63"))
    (48621, uint256S("b87443fe72efd53e599adac88bc51ccaa2d7af1c9700f2f2881ed7d1d1d8a70b"))
    (52094, uint256S("7d1e4d0517a021e63e48782c84de3f0cc2ef7d2c5f4a3a9b86e281ed3b3e9580"))
    (55567, uint256S("307142e0a7b398464136a75f001dcabac05f27008a47b89ee360d9f284dea9c6"))
    (59040, uint256S("4c1d7c0b4c32913dca1a31421e904bb896109edf85780189ad67cb9e45e30f9a"))
    (62513, uint256S("832612f61b2dac4648c11003ce5ee893eb20e2bf2235ec97d312a154df672f07"))
    (65986, uint256S("8d5fb427a82ca8dfab04d22035c99a55c0018b99576c5ba6547e9bf3bee14bc9"))
    (69459, uint256S("24601439e03dca48fbce420a26bfd5ce954d6339ff7981cbf85346d3d24b5d53"))
    (72932, uint256S("b6ef6a6265acee048ac4cd2f1699bfa7c2d6de4cbbed948cc0ae843e1ba1ff0b"))
    (76405, uint256S("e893d1dee892d6c1cdb8f9a75917dc829d05de0c97c017b30021ddb25187a969"))
    (79878, uint256S("5419edc41b73251e9086a7cf728e1ef757ceaa7495f3886d7ace2b1347ba35a8"))
    (83351, uint256S("57662a28369ba5514638bc47843ba145ecebe64af18708eaace434c59a0efc17"))
    (86824, uint256S("ef250c9e8148cd6a390da12c7080942399836dcc5cd144a88cb2dddeb59787cb"))
    (90297, uint256S("5340a9d45f0a8e4702c62bf8e62d57b330ea152e51676f6927d6852998bc69db"))
    (93770, uint256S("2be232316db5a14b81f193e84af3fdb176b2826a8f1031393a5fe49b84dc2678"))
    (97243, uint256S("4c354541511a115a8d24dce468557e330e29acd9a012cc2000e8c47ffb6a5f30"))
    (100716, uint256S("8b49c296068b5c5d13dd14698872374de9440b20e7ed38b368b46d4be59fa46c"))
    (104189, uint256S("cabbeb1bacc7ad63d616962f14c686984bff5f2aa1bbbf678cb02737497bcf64"))
    (107662, uint256S("ab85477863d393473a873b568e836fabb51092f2c83957b716a9ce6295d2f7f0"))
    (111135, uint256S("450fd2b952f3af53eb963215475cc5743ae01c3380c0bf4908fd41675dd0f0c9"))
    (114608, uint256S("0bc85ad6d7ac53c4186daf929cb4e93c62a7cbbb6a3c6f1e3df9af3dede91428"))
    (118081, uint256S("cd788a159b03c4b3a8adf0f087c82ebf1a626fbb2ed9c991fa22ed5240740b88"))
    (121554, uint256S("93bbc98ffe20bfd9191dd539a00e363c8dc945e406eef996495d4a74a64cfbfa"))
    (125027, uint256S("83028569a39231d52abfdf6d7e0d0a284a0c4121d02dfa232afc8be4d9f8614c"))
    (128500, uint256S("510acbe3c42140079aeda2911b1de5d05cef871bc771e766608da1f407aa4afe"))
    (131973, uint256S("ec5b80bba6f1707b7263839a399401674974020f8a2cf66378481e2182c988bb"))
    (135446, uint256S("07abb4f70e44018b50eea9bd3233f3d5f3f8af77aff9d814bebe6de6f677018e"))
    (138919, uint256S("9c2545bde544fce1136ea91f502095d780b4f18fb3ba8740a06d9b4b39554c3e"))
    (142392, uint256S("6bcf86a94c2c23a6829c836e16c7560993c505df29d6ff68a45d44f32fb499c5"))
    (145865, uint256S("3d3072866f679517a082a7bd8e837371db1f85a16801163b25ddcc95ee8aea5f"))
    (149338, uint256S("ba31fc575c7d8137bbd74e3aea75be0e9896246ff1f0b0d85550f6dc7139c1b5"))
    (152811, uint256S("efbb319e1f987d5be586482a8910967185177cfb26ada7089c7687f1e957f7c5"))
    (156284, uint256S("af52d3bf0677c9601eb94f19d213488e000b863c0f6f7684ea6d11077a8edf60"))
    (159757, uint256S("e2ae39c0703080ac2889477cbd0aad595640a9ea0c69ccf770c5cb98481f52d4"))
    (163230, uint256S("3d063d6e7cc019d91cedd567332c2da23a3f3980e5018ac13f938b04ac1c1848"))
    (166703, uint256S("de4e4ee5e7c98a0d4adef841d1cc79ba3ac07494d27aa8820172ee0834a8eedc"))
    (170176, uint256S("772c386c46931a415b4eaceed32242d0b9b44b4247f69fd6708aa693b8328f74"))
    (173649, uint256S("aedd24ff7292d8633ab969bfede7e19c95c0f6527445b83b46151852d9ba147d"))
    (177122, uint256S("77b66f73b254fea274b29e6b5042b1b74ea8918df8ecacfbb7a142ab5856cda3"))
    (180595, uint256S("e7578e3100742d47b9b1e843be742f39a4512b0a6757a0708f9856b17344007e"))
    (184068, uint256S("5a68db22fabee1d9b6af73077ce39a25263a10c951c78e31afb2a0b5ba12781f"))
    (187541, uint256S("e2f0a84379d2e5f67623e94c541a135b71940eec9128d15de0b2d39bf689d16f"))
    (191014, uint256S("046f72cfa5b159ed9dd5663cead16d913c276451647f645f5ed6f702979cbe66"))
    (194487, uint256S("0bbfd4e30afd1f1a73583e8e56671ae932d2df8bb074debd227903227ee98409"))
    (197960, uint256S("954c8443e11196cd3275f93e53607c01221e73eebd409e6d5a902109eee431e2"))
    (201433, uint256S("1bce8d7c34921d8320949c4ef179bc020bcd754e53e0192096743933cb2bed0e"))
    (204906, uint256S("17da586a7c2f1c269f985b739344dc05c30317cfcc149e51123510f2e1e60cb0"))
    (208379, uint256S("507f505c7a2bbb9e53bcfd9e0eee7b18f9f9983b3680c7b6910c594416b36ade"))
    (211852, uint256S("3cfea55f46c5fd10b327beaeb8e8189bdb3ece92883d0ebb03149544978df53b"))
    (215325, uint256S("75efd1b154ed001fa8effaa515ac490e081cc71b69f95db0dac9d785967ff68f"))
    (218798, uint256S("00fff431dc119a7e30bae6770efdf7e0f9f4905c1b5e25010c3c35bb3e5768ef"))
    (222271, uint256S("96106ba16119d1f83cd683ea4714f5da7244004ba09ebe57f607551fa71aaa7f"))
    (225744, uint256S("2f6649c72b979b5e870d4f9f2826605831acbc932f95546b9b4e6cdacf5f5e69"))
    (229217, uint256S("7832148548186adc1949096dd659242ee5c675e170ce727d4fbd266f12131ff5"))
    (232690, uint256S("950d3f71fc941b45c2c698c49b8332389cb7169eddef2a0d7762c30c4b2d89ac"))
    (236163, uint256S("3a090a83cd50da6a3c12c4c52a6a126f0ce7d3f6d474479cc98d95add679ef79"))
    (239636, uint256S("fe929109f81c8656565dbf034b5a0974666c795a154ec814501253cbd41bbb62"))
    (243109, uint256S("63157a380c3e49a0fc3da4bf2618b6339d98ffe8a4c3005ed6a33b72bf75abb3"))
    (246582, uint256S("3bc49a89f9e81eafe05aa6b466f6ec51eab1bfbef58e4e44644d07e5a90ad4d4"))
    (250055, uint256S("07a202751b101e937e25aaeb201d7413d3d9a8631fb5f7c7953b5c6ddda2b43b"))
    (253528, uint256S("7b5a7286c76e640ad9dfa8a7b662e9937df77dd0e70912a07960519e3c702d59"))
    (257001, uint256S("6dec08ad17be6ceac60de32953c21e5c8ac7a505098025757a811ae0f2af041c"))
    (260474, uint256S("ac0e9e0ec2f0c0b2812de58def4dd5694090c4dc79a0599ccc559201f4d3e9ea"))
    (263947, uint256S("a4a8fbc32c5ede149b4ddbb42706f42ef6b27e7b97b4fab53ac4e14ab7516179"))
    (267420, uint256S("a70af85ce65ea0d5c82edd2d704e0eeb9adaa66aebfff1ec75575130b8ec80e9"))
    (270893, uint256S("5fcb409a06954b5e016141c5cf6ad5550d504d0c0617ec848db9d31909f7ae6d"))
    (274366, uint256S("3a4aa1e698cd5f7cca9e57a27d1ad8a474afdaffdbac2ad8f9a44461a8952af2"))
    (277839, uint256S("84111029ceaa7b717a1129fbc269ea2ae5c29e291faec5570206cd7089d5dc7f"))
    (281312, uint256S("b4023f58d3baa4261a99d5f5265343ae08d14481e168fa5fb99a8e1cc20c4349"))
    (284785, uint256S("3ab1b9ff22e454e23968b680d1b29f1482bf166fce78c8909b7b5dbc3ff8bf9f"))
    (288258, uint256S("a216e9e26e1eb2c4a00fc7d9392efd2b2e76c47d5080d23adc7cc9771358bd0b"))
    (291731, uint256S("745e832815765ea7f0e15e863b4e73350d10a4655803e58eb7faa5f950ae1268"))
    (295204, uint256S("f84279bf89ef5dfe75f19882e3836c1cea85dc2f607e8ff81667ac1dd3d785e6"))
    (298677, uint256S("35a82980a0a9da9da189589237b607fd678270793061d4a53ae976ae385e13be"))
    (302150, uint256S("0128ea84427822f2dc221edeede9c5b521768976a9ec1912b4de3f190182a5bc"))
    (305623, uint256S("7092205ecd2162a3bb39866a3c47629267fc6bd36f81e1f32b632738de4a2b51"))
    (309096, uint256S("b8136e86ee588f981f1cca003fbf7928ac966be4b912c7f94ac4d74323b5b5d3"))
    (312569, uint256S("ed3ba9b2ae9cdcac005e26e886523288f615e96629b8dc412417f6ec8646e28f"))
    (316042, uint256S("bac8dd40965ef5ce7b9c8308e8bc300ba3cee9d2b2da77dc9fc4ad493e96dc62"))
    (319515, uint256S("927a02702a1045f35629109b613ec1881b9f12c96828ff391eeda619375500ff"))
    (322988, uint256S("16137cc68527c889ae7049421793209748b1df8cad8eecc455ef4cfba40c445e"))
    (326461, uint256S("99b406a24f9db73412b00ac5f9f6c7ec359bc20c9244e9bf96be1028f21713b7"))
    (329934, uint256S("4395cff5b44b5c333bec244fd7848909b2b7bb047d5d7111ae841876f616bf08"))
    (333407, uint256S("5faeb3734a45680b6a192a581188cbe806291c7bfd7b1fbfbcd938370f5b8d2e"))
    (336880, uint256S("ef19f9d5faef7fbb11c8a581804464994d7e36c888c5e01dc7f138ae470ba4fc"))
    (340353, uint256S("3356ef66f4f9f3ddf088965ddb8be1b80b6c916a4dc2be4cf6092725b177f9df"))
    (343826, uint256S("706207499191b100af440449b9590286fec57cb3687121d7d3deb9083a39b652"))
    (347299, uint256S("1f9f255b394ce004c52fdaeb4880719f0aaf896692c5ebbe004f4632c7905fd6"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643897265, // * UNIX timestamp of last checkpoint block
    783287,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2894        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1622547076, 269467, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000fbe4cbb6044f6156fa4f4396521b1d28d01307aadb0738d26a88853078d"));
        assert(genesis.hashMerkleRoot == uint256S("0x83046e5bd611dcf527e4b74c0ff8050042a58902c01b39a3306d31cec7c2c684"));

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
        consensus.strSporkPubKey = "020f65236f5c763bf979ef7316dfc2edca12b443c3fade71abfebbd931839e8fa7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "MXXXXXXXXXXXXXXXXXXXXXXXXXXXV9svHx", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 60001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1c18b394b406bc240073df567948a63b454b9e5412f71fbf37fb28e331d0c443");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("3acfdfaa6c021981acab0d79a461177c60e52a083be4ff1e193125a2d967c37b");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("3acfdfaa6c021981acab0d79a461177c60e52a083be4ff1e193125a2d967c37b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("dcf134c176a12efb445ee51c5c27f0855621fe5ac1ec1b6a50cc0ebecdd08c1a");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("172977bf61697a0a194fad26f6396bdacdd043521f2754efde6b004d797da148");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("636df5fbf99434e97d8f92e83188c82221e546fd55dd384682dbbb1c785964e1");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("5fb2b7a4d9d4fecca2b189c1a169b8709bea66a8d3bb60e95a10fcd50a246821");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("109e67344bf699384c934e58646a5f97061d2a3a9e23cefdfba8b75dd0a2004d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0x2d;
        pchMessageStart[2] = 0x95;
        pchMessageStart[3] = 0x22;
        nDefaultPort = __PORT_MAINNET__;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.monkcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.monkcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.monkcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 51); // M
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 53);  // N
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4A).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // monk starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet monk addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet monk script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet monk BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet monk BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet monk BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // monk starting difficulty is 1 / 2^12
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

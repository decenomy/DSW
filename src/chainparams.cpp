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
    (18366, uint256S("1edaba484ff9ae2ff30a9f0a093b660c0dc026bc05d70afa8b23cbe251ea3663"))
    (36733, uint256S("199dcc452d8782c4d72c8995cf07d906a841faf9eab3151fadb81e5f3c9d57f0"))
    (55100, uint256S("a2ac8a7f20fb32b9f4be4a1a739f1b3ed76fadafe96d53ba5b4648dab9024b4e"))
    (73467, uint256S("9ac9dbd3ff17459af3020073488502e8c68c0339acca9ae3f8949eba864c8554"))
    (91834, uint256S("3ccbab2c24824fddc24f92a9b6d59708874fad8bfeed4e07205f4538f4f116a9"))
    (110201, uint256S("e098d95f706eb7848289e28f690afac1640b9beea9da8f2c96bfc44e0e3c8865"))
    (128568, uint256S("9a979c166d048c175917fc773887f40b830888691a3c66239855ea68e3372b9f"))
    (146935, uint256S("55e1330dc918cfe3844f67ae592ae70f3a19d099c91ca7144f91ff7f065d7f73"))
    (165302, uint256S("7fa48e8a33908a80dcd37998245499857f5258795ea9732df863dfa79418f339"))
    (183669, uint256S("f39aa097ea9f5795d8bb0745db058315a211996228691e0951305b22117f6572"))
    (202036, uint256S("c02095aa50a07fc57c30f730b94051a7014958b31f234c37c9277eb5c00bb396"))
    (220403, uint256S("bc65f08744c9c9c698aff424027f7185308b53045aeebbef1e474b1e212d5c1b"))
    (238770, uint256S("743c008e8c6eb1388dea6583e611de1814d614d248eda09ac5084365de683ede"))
    (257137, uint256S("4daa8cd841f16240b829347a322365a8a8efda9cc7483ee727f8c3e5ce7f780e"))
    (275504, uint256S("ba28604e7080fc0511bdd9f8ce7613f1025b869cb58b7a833ffe01a88fb7a679"))
    (293871, uint256S("7df1c73b59c8f114ec7ff739536698a0051c55666756eef4669c5f6b0fdf667a"))
    (312238, uint256S("d739fd302ccb6745d556565e52ab54f6e623f49507b716a4bc5ddfb79f42c536"))
    (330605, uint256S("12c29ae7cb4c9b43aa0ee4e70648ca8e6fa3e6fbf90a664ed663d380dee8dd85"))
    (348972, uint256S("541ddecfe29d090ececc55643e05654c9ede7a19115374406b8dade784ec619d"))
    (367339, uint256S("3addb8d59bd537d9bada9990486d1acd98220a93726da1fcb89af987976372f1"))
    (385706, uint256S("caa106cbf6631c52e8ef57de2479d5d46cfb0f4b96e8e0b49332d2b44b402d01"))
    (404073, uint256S("fcdfb507420935cc0b23fb2a3d04eeaf96c29b234a696cf8f3241bab1af0df9f"))
    (422440, uint256S("b342d42799d072d2798474d9e03c0081500e12e0b49707bc335492c8d05a5b96"))
    (440807, uint256S("4379d3cabcc1ed5360d3eae98535c918c222397bef8ca1b72f39f38d526ceabf"))
    (459174, uint256S("74ce187e3fc7892e785c7aedbe481b0f8ca435026e3876f2fdffd5a0399df7e8"))
    (477541, uint256S("c5d5d3a9c7220aca4b4985a16dc40b217d471c4e825fbe146cf74b51416c8c89"))
    (495908, uint256S("2a792ad078ab28c654ff16460363562511618bcd2fa9b3d42143c450d348b9c0"))
    (514275, uint256S("2eb10578b15ae2d707dc7b7b8460ffec6f3c6c1fb70f25dd05f46a0cd55e1baa"))
    (532642, uint256S("4fc953a05db6da3e1f1c40150e012277744c1b73e2f547e3ef70b9e7cef55b4d"))
    (551009, uint256S("d43f5fb8ab5130ae6a522a9035921bd22b3287fbd168374d14917ff64734bb6f"))
    (569376, uint256S("6eafee88138fcd5e64d2c60e332af12ffd28023407db535e4e4f9bf046546b72"))
    (587743, uint256S("db392b9b6028efe765c5f92416495d63566857ceb1d6ba80bcd882568279db52"))
    (606110, uint256S("7bd87b925acc3992a4c986567ca1cc53e11b3245b974fa89ff48c1567bb57724"))
    (624477, uint256S("fcf53d8d942a415ccef5dba9351f1703973625fa6d3bfc3bf87611b0ee83e595"))
    (642844, uint256S("73c04eedfdf140bf3582ef77d004bb1dde0328833fdfad892f4d59806d809584"))
    (661211, uint256S("41d90f3b05c930288a6bf375f59ddef3b4cd57b6d783c10f40248b74f6886761"))
    (679578, uint256S("baec518eeafd70ead19fb69b1671f1fb918a354c671038e97d5559a3d58a04bc"))
    (697945, uint256S("72b5ac7c0f3461edf11d21c3a44ed44a8c5e54a9970c9f7d47741680a64d89a3"))
    (716312, uint256S("00c707fb4b7c9a9e7a5e9f209f2ff0f91674a5b2e8646374f0c08ee77300ddd7"))
    (734679, uint256S("fe9f7640135d75f03ecb33db0c3cbc37b128d1a9f29ae06789b08b285e6eaf36"))
    (753046, uint256S("513412fcf608297379cfe6192727e21143e7547eb0646cdfb1b4b290717c3cd6"))
    (771413, uint256S("b3678d7953bad9e4c218c1f74df509dddb2f9771accd90027983e52923913f06"))
    (789780, uint256S("23befcede57edfa36ce57b82c9b072eab915b4fc7d7a6c96e1d7a1faa609e58c"))
    (808147, uint256S("b29731d804a2a7fa32be3d98a443be78ee3d11f2dd91fd1030107a8b24c7adb7"))
    (826514, uint256S("4606421eb98df396bd2028cb576378ee70b91c6f9b6b9ace2728caef62858079"))
    (844881, uint256S("22ebccb083cd35b45f550f2164e36c56d19fb8cee3b64461a83e752dbb663b01"))
    (863248, uint256S("ef9213af0f54b877e8d6727a30b82ce0cf7ec80c8743340df532cd9a3dd3be6d"))
    (881615, uint256S("11d925c7d27201b328d3cda9f351478e0ac063603b791e1e417c10e76a4c3c44"))
    (899982, uint256S("f1c82bb85704b9a9c2af6d0b85a2275f966a4a342dd92e7ac1b78711a22d3cb1"))
    (918349, uint256S("aaf2ecdcd20f72d6b3077a1b2a0c27ec0429bc2778aa117b3c7e648ce81cbfc8"))
    (936716, uint256S("576f06bf0706deb6e213138127e1684a5bbb4ed2eef09703a6e494d131dbc510"))
    (955083, uint256S("296635ae396b74c1cdd11f70692a51ec1c52866d7a0d1ba3105ef8be9d4da0a4"))
    (973450, uint256S("62f81a3bf50373a99fa5f2de4afac4629617164574d5a0f98dd5bcd6b8122380"))
    (991817, uint256S("5818a3fdfc81ca59ccdb945ebe1d3932cb01cfd7a8664b5be46f76cffe27ff97"))
    (1010184, uint256S("2bb27f418b83974edb09acada301fc90d003355af52a95989e52ebe70bc1ed36"))
    (1028551, uint256S("f4f6780362a43d9d2938ec67551963dac55a9a1a1c7b66e982339454def382cc"))
    (1046918, uint256S("ae153a9d276b9852c2ba44f45d1ec072c5bbc59ca9023a7f8944c6c0ae6f8140"))
    (1065285, uint256S("3e6b048ae8bd9a73881eb50cf31caa2df9b87525bbc3804544dc0a5f09debdf8"))
    (1083652, uint256S("6ca764c2e826907c213a94bfaf9f82424cba8108d03e4571d0b614a72e33318d"))
    (1102019, uint256S("3fe0575a78a6d55154fc32d94b7f523ecd263c4e417ae520a071120b624da746"))
    (1120386, uint256S("07a2aa2f68019c58fbd22a605e3f03e6824e50a422726755bbaf2d3851daefde"))
    (1138753, uint256S("96810023d9da694e7d78b04f3ec79317458a54dd34bbde7a9b46ad4070b2a260"))
    (1157120, uint256S("2fcc33fe57dc05b2923a3b62abc8df7715a53c8459953f1febb7a980cca248d8"))
    (1175487, uint256S("b52226602216a721b1a6017781b2406307340ac7bd0b4bab8ce50b7144c0c9e2"))
    (1193854, uint256S("c1fd96eb95e18541a43375217c8013e79c8d863214f2891b7c4eabba253ab079"))
    (1212221, uint256S("d2024ea885c9e07171180a8fd1afe2b5d1a5a5b434d14e63cc3c1149833ab332"))
    (1230588, uint256S("9dd3a3843d6987f08dec8d61537279fed6c3a127b0539702c4d3d14dc37b9376"))
    (1248955, uint256S("8baf9c22164ff169e8c0b7bf6c88d89e4ee8ec86d3c90560edbdd0f8c42ee170"))
    (1267322, uint256S("287ec2163a0fb667744516ecc2ad33a85a73f66a55cf918eea5656f3fc80d0ee"))
    (1285689, uint256S("38bc25477c5bbf396a6e1e13a212b2151439429748b93b9bbc5a59e18a63563a"))
    (1304056, uint256S("465ef47b0ba1da8d14a79e97bebd3ba98962e961f3d36da4abc685e7e3e357e7"))
    (1322423, uint256S("124d0e2ebb21fe1837390e98127cbba7a705586ea857057d7bc56db50a42755f"))
    (1340790, uint256S("e580aa668873a427f76c10797bf09de0292b151943d8f485c126617df73f7265"))
    (1359157, uint256S("139c2e192945dbf8044ada7e783c05caa8714dbb5a9196a51d49d2a012082dc5"))
    (1377524, uint256S("adc7da69691bfb45ca9b7f46a435b3d40043ddd056db273b120bc4341e19a090"))
    (1395891, uint256S("c4bd7d8b9e813bede8d4571f911383e304aa806755d4aaf06d223e1cb86b429e"))
    (1414258, uint256S("92dd01ac0252577a037cf5bc622046371c9fee1c1d3a571a48992f00c08a11f8"))
    (1432625, uint256S("f41b6f25208ec20bcbb14d5e1f860744a5660d8d57c8b5526b015a826416adfb"))
    (1450992, uint256S("a155f857b5f273aef8116d765ff0465164fa698e055071e9bd8b341530347e23"))
    (1469359, uint256S("94242bbd14860bfec88f9d5732bc5d8f3197dd52daa147a5caa2eb67e2440f4c"))
    (1487726, uint256S("5e3e46eb98944b1532a0de62f3210ad1e99fb817c038fc4b0f9783081a22466d"))
    (1506093, uint256S("2b2e3547edef92da17852c67d9791217dd6e3ecd92d4edec38cbc7e230664497"))
    (1524460, uint256S("d878ec4f2c04b5559c070261066a69e7ed5bf4690b1081e6cc5d627a59bca92b"))
    (1542827, uint256S("bc02d0e6c4a6f7bc3ee43da2de0819da2ffc3be588e446edd568c6a43d6ce06a"))
    (1561194, uint256S("b1f8a001b98f9d6da39e65dd50b9c68eed7e69705359e56e19376ab15a54e361"))
    (1579561, uint256S("6d11f9c533f9621a73d53bcf45d9c3260a3bd756253e31d52e26d41866f02b09"))
    (1597928, uint256S("1d8db24ee9f2f7ac9d33871f5dc1a9155f0ab5f7972c67ef948e2718df53db59"))
    (1616295, uint256S("6aed472ec84a00b562e1378110f5107669c0b0e255ea849abab176a0399cb629"))
    (1634662, uint256S("58c7ca25a5e8ee173b9d7258d49a7bf1a28c5aa1901b031846d6a121d8ae5b3e"))
    (1653029, uint256S("d75b40961a3ef33e048d5492ad38cc7c7b563822cc985740ef7817858d7fc6b0"))
    (1671396, uint256S("8167e37b2309c8fe5d63e17344864a118d8a864f71adb55dfd8774c21a6bc29f"))
    (1689763, uint256S("cc7a7cff428927c3aee25b381a5d8612bc58ed3d979d11aaa3b49ed45e544be0"))
    (1708130, uint256S("4397bd553ee8dba7c75963fe6ae9cc366cfbd41b518bf83c6658b823e69580b0"))
    (1726497, uint256S("6591fa2ef96291c5b6a8c61a07886e7a7c73c5beb17b71e42b0af3772c52faa4"))
    (1744864, uint256S("1b7b6bdf8e78a61816c6db3dee948b02f0752b0cfdd091587adafa250787081b"))
    (1763231, uint256S("bde09ba32ff11419a0b171acffa2f4ff346c9dca54f7302c6a667e61b15e974e"))
    (1781598, uint256S("e6bd90f411c8fabce7b1251ea4b1ed663143ad074e1fcc187c8f89ed8eeab0f4"))
    (1799965, uint256S("36f1ca2e9d821a54875fc0db405f001db7fd3dc437bdd5c07734137a272bfac6"))
    (1818332, uint256S("0e115d89cfbda4bf4f9c7d93e1953502f91f89e1e59049e717ba05ec85fe9dfb"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1706606025, // * UNIX timestamp of last checkpoint block
    4743902,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2824        // * estimated number of transactions per day after checkpoint
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
        consensus.nRewardAdjustmentInterval = 7 * 1440;

        // spork keys
        consensus.strSporkPubKey = "02d8e66d000dbe1c014cf7d0a1fe89fec297d78603cb5d0b1a17ec0e6809e9271d";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "DBURNXXXXXXXXXXXXXXXXXXXXXXXYnc6B1", 0 },
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
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].nActivationHeight        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].nActivationHeight    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

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
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

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
        consensus.nRewardAdjustmentInterval = 60;

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
        consensus.vUpgrades[Consensus::UPGRADE_NEW_TARGET_SPACING].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_COINBASE_MATURITY_V2].hashActivationBlock    = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_REWARDS].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_DYNAMIC_COLLATERALS].hashActivationBlock    = uint256S("0x0");

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

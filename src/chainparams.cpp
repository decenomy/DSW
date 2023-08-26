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
    const char* pszTimestamp = "The ClearCoin Goes Live Launched! , Wired 28/June/2019";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
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
    (0, uint256S("0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"))
    (21279, uint256S("6cecf2667c1abca0d0146b387c0518e56a6719982baad64c1854249835f07f56"))
    (42559, uint256S("6d2e65aa13fc80f293db02cc4c0a109d65354f5fc0917eed37bf98dc4f990307"))
    (63839, uint256S("1a0b8e65383b5b8a95b6b6d0ef2fcc7990fd9668f39b4a54fb5cf3764fdb7a8f"))
    (85119, uint256S("4c654fa5e55ba2cac304a204f481d87d303326b2716865634efea11eadacd79c"))
    (106399, uint256S("93902cec8dc97ba5ee6c3b45e9452fb13956a05ef38fbfaf1409eb1a64d95ece"))
    (127679, uint256S("378345fb75271fa71cac22a04fff07b0f99249e5c8e442913186ad9aac628c4c"))
    (148959, uint256S("fd2091289dc210d2997a75df40fd5cc60a18123698086bb45b21efab7c6151b9"))
    (170239, uint256S("c53e9f0691289e6885ba08ece3e10ac1518ca7f7d246a309fbb34ac9461b8e5f"))
    (191519, uint256S("8047e4cf4a3367c745ed93ce18857463f0282b3a76db4d7b2a448870cb8ca2c1"))
    (212799, uint256S("c1a14e622ac20ac76a08f9ec90cc57ce873987ce40560069d4218c9e9dc4f733"))
    (234079, uint256S("69991ff9557fc48c1e9fa9e6c33041cbcadfafd5286f0ed45f31509bfad25d6e"))
    (255359, uint256S("bd3d161dfe67447569759f490d175df3f4c9b878c4bcc14938768b8f4597a474"))
    (276639, uint256S("98ce60b8d053358d8255c278946fb1484bbc672f4532e4496ee3e81af4d6d46a"))
    (297919, uint256S("88a47508f71c90080f6f5d2e122f9ebb41f9c0c12bc8fe66e2293433c6a417c2"))
    (319199, uint256S("bbce5ee32998099555eaf9420958c6429bff88e005e414791f37881910fba04b"))
    (340479, uint256S("0e4dd00a2113960d71fcb2a4d24d08268453e157b03bcf817210350c4d46df6e"))
    (361759, uint256S("d9e0cc3a5efa4609b329a8ed389c2f94f32f2441e17819eef3b6022f5c718251"))
    (383039, uint256S("1cd3c7595a4cdbd8548cbfeb889e292fb0fbd06e23d66523440986a1a8509afe"))
    (404319, uint256S("1a6ac6dc0bb6f6f00b8e71e48b2e60d3db29dccb2e83f70d272d505f4b1287f5"))
    (425599, uint256S("c8841ef5922c05fc63d1f69fbe6aa03e473674ad1e81b06697f2741be326f466"))
    (446879, uint256S("6171de118ee346edb19b965b88fb005b045c941c4dd2bdf6710db3b5c2beca74"))
    (468159, uint256S("9773eab60b4fcf56c0f1d60372261e457d4fa68758565d0cd13830e93a2e5305"))
    (489439, uint256S("dd645b690e8e11471dbf023b0aa937d022adb133bfc428f9f881aef8840c12f7"))
    (510719, uint256S("847c2020283c4d2e5a72f8313a9c7c7f6c371254fab0cc78ca6c50b7db04f59f"))
    (531999, uint256S("49d36638553442fd307e033773a6f475c7aefb063b3de6a5fb7a774fd4a8aa51"))
    (553279, uint256S("fa0672f39ed9f62428da6c12c577dd42a59b1fee667204cb4f2914bb75ea49bf"))
    (574559, uint256S("6546877ee20af4154710cedad027704f1fb02ec8fc4a269fef6ba1fb474c027b"))
    (595839, uint256S("c17c05196297a569afea5c8719629e29dcb904683783297641ef654340ca9c29"))
    (617119, uint256S("9746d65da4395e1720f2529ff3b20478a4c3ef1b254dd1b86e079dcc0e92a33b"))
    (638399, uint256S("ecdaf71ca698cfb1425c9945a50f5fc6c047f997a12cf54323d7c22af537985d"))
    (659679, uint256S("c40d26a54858f59065f1cfe0ac0d6e15c5edba3ef811d91156066d5af962165d"))
    (680959, uint256S("5a8382f1ed15b2bbf4bcce52af20fcbaa40dc1c8475ee7028c3cb28ce1886dac"))
    (702239, uint256S("c1b256815ebc290be453e159d514da8d1f2fe689061b54c616680c16fc7068bc"))
    (723519, uint256S("cc318c1708d7a9657efac3eb20d71f2deba5e5d9e9e058a08077b71aa14034a0"))
    (744799, uint256S("e6b5912921bd56fed8d10fcd97b383e57604bee9c215bb5a557f71fbc9759316"))
    (766079, uint256S("8f8b5af159553b4544877b0f1ea2b41747586bd5b995c76fe2785d0e8774ed62"))
    (787359, uint256S("10e5823933aaf68e5ae12863a63ddf6d9a42dc285541e5bf9cd44c82cd11c3e1"))
    (808639, uint256S("da618b8845b8d0449075f76b698e30699fb3b2e882b32e99a5bda643fa1e65cd"))
    (829919, uint256S("3931685856c0b0979920d81b8f51b00323d92329c5fe7c4dfac657bcb9023ab9"))
    (851199, uint256S("7533909db2ff0f5774d09463157682ec9f8a97e758feb155b8a81d5dbce20581"))
    (872479, uint256S("7f7c02596cb5b86b14b22dfa9eb51d5e358b86e806b7d512a2caeac3084421f5"))
    (893759, uint256S("8e14b386972e4dc08f7a9b593f66795948a03f541fb34c336f53110299f190e9"))
    (915039, uint256S("f70c75422466f0bfc00a05dbd910a58b32758b979ed0cd61fab0bb33c903407b"))
    (936319, uint256S("d78820a7d0c8c5ba53e390365108489aeacc2df6479627af42c7c12ebb0f72e4"))
    (957599, uint256S("4bb599856f0a76457b90e8c708fef9bd6c5ca4fb63dfb775b4921ea110d8f67a"))
    (978879, uint256S("8fc3c39108b33db754b8e70d5fcccb0ff966fd0aa30a44e148d36c21a7d33d92"))
    (1000159, uint256S("8702c6106f9161dab3fab11130bea72f1edbf570a2025cfdba40eb451d903ff7"))
    (1021439, uint256S("d59198af1c6f5c1d198dc218c21ec0c906351728cbc63edc2b712d310e5fbd84"))
    (1042719, uint256S("03c413032a134e247999b60d969ccb6e8a215015335196a8c0b892027c126318"))
    (1063999, uint256S("7e048a0f4add95d53a31d06f5f7cbdacff67f4328bd923d1a3f7726346de0989"))
    (1085279, uint256S("49957d3605896af92b44c7e34cd2195efddd4b6d79603f1cc4069edffa634ef2"))
    (1106559, uint256S("dec45e0e653b676ea603de634b4c2c5c7426bc9b4e6506cb0103109632c44a15"))
    (1127839, uint256S("7896e355ab46e21dfe2c9b1fd961ba65dd49333c34f1c2ab47c3700f22a1f59a"))
    (1149119, uint256S("a5decab0b5f7d42da8f3dcd67877371f785923bb594b865bfd814f7bf6d8e16b"))
    (1170399, uint256S("b82c46fed0a5b4533f23c192bf5bbaf7879e6862c6cbea72a8920ade7e10ef77"))
    (1191679, uint256S("705cac7aae4c19ec95d684b5e47d65832976fab5f092476720c950b01c896bd5"))
    (1212959, uint256S("1825347d948baa6a273b907d6915242950a2bd2b7d51d36f00dec9dd9e68b74f"))
    (1234239, uint256S("5f3b588bc4120021b012bbc43d1792b6dc978beffbcb6ee1ca5f075307c36f8a"))
    (1255519, uint256S("1a82b8d4bcd8611e4f3de4bbf86f4186c7731df69b531690107960be78b009e9"))
    (1276799, uint256S("543e52db9a19b1ec01cdb4ad5be8aeadb00cd8184e259d1d6034ec5dac6dc461"))
    (1298079, uint256S("460c058460fbc21183eaf462fcfa2536a9a84be4e997f6487b230a78d2f13739"))
    (1319359, uint256S("6ec7904d35d7adfa941fa0a3aad98be5870ee100385352d8717714769bffb750"))
    (1340639, uint256S("4ef837f2cd6e81aeb5ea71a855ec18a12200d0d2d50240bddf872e894c01b888"))
    (1361919, uint256S("63923ddd64e3a5d538684872f0cc58ccae45ea406cb805580d9fd37a8601faa6"))
    (1383199, uint256S("4dd8970a034bd00d9b177e482bde7a6f7c3246085b0a01cfeefe8005e014e7f6"))
    (1404479, uint256S("f74607a7a47baab1da5ee5211e5b77800a8e8dc90ba48e8f5e18bb610bd86201"))
    (1425759, uint256S("01e9f2c541c0dae393b3de69c382ae41a479d892f55a82689ecbea6a3ae444e9"))
    (1447039, uint256S("8e63d24b6c88aefb79d656fa93dd457e955029f9d56288ec1062846741b1e4bf"))
    (1468319, uint256S("d493071c8c8a22a8223ce75786cd37d9afc5a05c5ba720db4792e160ffca447a"))
    (1489599, uint256S("7aebb318e1cc06ec7149b78796558afa5feaed45664c26308aa90e7da35f5273"))
    (1510879, uint256S("f43980433aa982d3ad08131c923ee73543b9b62b8fc829d481d6fcdac9f4fc23"))
    (1532159, uint256S("dce9266c5b2ba1d1f94525d9d446d7f7b85b9633388e65b3bbd83be94f0f6d2d"))
    (1553439, uint256S("0a133d763c3b0a1ee51a28694eadbe6d985c6713607276151ea6bd8f87f482b8"))
    (1574719, uint256S("7499e894d7b103296b1c340ecf2c61b0882d0af6d9a8409b892c3f25e1d533d4"))
    (1595999, uint256S("34df3a45999fa068fa372aa319399c9eb57c6f20bedf55fda754f16e7b707658"))
    (1617279, uint256S("e00863d1dc7f7fa8e3afaf9ae3c16d21babc6376f1464a5a51d88d05e7c08426"))
    (1638559, uint256S("bdf0c25394c2cd765fb06737652a1070de7449fa61a98f34d38e5a11934a55ae"))
    (1659839, uint256S("d5eadf8b9a522f372969799e2ff6461dc3b2dee210499f9dd1d438d2f5d8f87d"))
    (1681119, uint256S("8664fbff2881c580123bf6bd3a58ad25c9fa3aa58987d9fe860dc2071e2ea923"))
    (1702399, uint256S("9463d5f63ae0a312d86cce23c69a3f1e689d9f63a8cc3a1c7e1ad8d6931dffde"))
    (1723679, uint256S("de4942c42f35710239dfe931029bb35904894cfd0af714cd9a32172f8086e2d6"))
    (1744959, uint256S("37cfce7f9ade273a28d895b963eac0b7978de4757fc2bc7dba4763671f427261"))
    (1766239, uint256S("d5e6e0fe51f0e923956d1ada12eda15bcd3657a00f428777c334c62d7d4044fd"))
    (1787519, uint256S("b04efc3305e5b98a663f7d08151af8d88205258afafcd135c356a29cd428fb1d"))
    (1808799, uint256S("7bf840d1e3c3b1018d2c9447716f1ff69aa9864ce04f2de5330765a129168f1b"))
    (1830079, uint256S("f4b5473d81c3249b7d949fc05d947a26a307526773aafc7da41dc1d7be708aa7"))
    (1851359, uint256S("b4073f17380143822c7e870a3d730605522ef09d1bdaa4777d119f9ced234d92"))
    (1872639, uint256S("1863f7795229af0bdd1296cc48b05508baf78fdbc5e16cc7d0c2ccbfd06cec58"))
    (1893919, uint256S("6edd93032101ef8cb8b78f9a1f0359ce8f176d70185692bff5531fb9cd887d3a"))
    (1915199, uint256S("8e381e1d2626c4d0d3a243103c25772959d40ca3923e926957351435a9878f1c"))
    (1936479, uint256S("87413f71719db3bf7e1b1a43a5964746066179bfb52d72820b4be7ecfd15b73e"))
    (1957759, uint256S("3ce8b3ccbc00ac50fd01f25a644c4105ce5d30b7dda23dc3d45110993c088443"))
    (1979039, uint256S("65526e5c3ee03f7b0d71266ec93fb5e3e5d7455a5cde5526d9dfff96a3f6641d"))
    (2000319, uint256S("f3c117004aca031faa9260e83ab40f0497603a4be84a94313ccf15bfdd63b21a"))
    (2021599, uint256S("001a42d683a17da0f496f171aac2b60cc93c45047d4a4bc2add15e53c2d0d8f3"))
    (2042879, uint256S("0a4223035f08f54dbef376f9967b6b6513e33ddc157b6242c23bc4b1144d1e26"))
    (2064159, uint256S("e371b32e26913e86c934a701a082b65ec7ebee16f0f939f631a9edbdea234bc7"))
    (2085439, uint256S("3fe4104922b0d4333adf292034aae13301008629352c6d8ca812c85e4829ec0c"))
    (2106719, uint256S("25683c29869cb0abc977825cbce5645154c4ea62aa516fb4bdce9c9d84ea13b1"))
    (2127999, uint256S("5e8e482806202f1880f0c72ff9f73af60ebea4e11e31bccb59352f64a268e6a0"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1693016430, // * UNIX timestamp of last checkpoint block
    4920115,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2818        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1561685759, 3380104, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"));
        assert(genesis.hashMerkleRoot == uint256S("0x57614ebefbc1a26b6cee7cd4bc94d060baaadf1ad2551a81153a588fd75b471c"));

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
        consensus.strSporkPubKey = "0391eb99d1d94bf8bbc66b39ba11c95814a2bcbcc1cf6c567c8bd58b8710b192f4";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1599033600;
        consensus.nTime_RejectOldSporkKey = 1599030000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "CXXXXXXXXXXXXXXXXXXXXXXXXXXXYGerr5", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 874600;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 874700;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 874800;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1075000;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1075000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("11d02f339a6e096c46be25da07783fa844d8ddae27b776641a6c82e55d38b315");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("898669ae99e12f86f773605a5baed05ea1ba99ddb3d59b5de47d4ec57e43ae95");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("898669ae99e12f86f773605a5baed05ea1ba99ddb3d59b5de47d4ec57e43ae95");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("5f5e467bdd92b2d3eb4cc82cbbd2c99bb8f9d8afe2714da6c429067e4650a837");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("a8632896bd6196956c070e1fcff8c2c2699851d484da03f15fae1f71f34e2823");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("6da440c85dc7f167d97719b8e9d7f9be4cb98641e3e9a4fc7a986c3f62f76dd2");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("8a1cdd4b7db68860752fa6ef7a55605e95b9554be932091b1d933429e6224ed1");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("8a1cdd4b7db68860752fa6ef7a55605e95b9554be932091b1d933429e6224ed1");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x31;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xfe;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 32628;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.ucrcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.ucrcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); // 7
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 31); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 63);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x47).convert_to_container<std::vector<unsigned char> >();

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

        genesis = CreateGenesisBlock(1561685759, 3380104, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000086d20056b2feb29fb638fe1086ac017b481bf52f0cc1cca297385a91f44"));
        assert(genesis.hashMerkleRoot == uint256S("0x57614ebefbc1a26b6cee7cd4bc94d060baaadf1ad2551a81153a588fd75b471c"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // UltraClear starting difficulty is 1 / 2^12
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
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;
        consensus.nTime_RejectOldSporkKey = 1569538800;

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
        nDefaultPort = 51230;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.ucrcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ultraclear addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ultraclear_ script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet UltraClear BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet UltraClear BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet UltraClear BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // UltraClear starting difficulty is 1 / 2^12
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
        nDefaultPort = 51232;

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

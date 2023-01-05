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
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
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
    const char* pszTimestamp = "Bitcoin is now worth more than Visa and Mastercard combined, COINTELEGRAPH, 16/03/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("0459d0cd928dbe01d8ce77979ef8c87c1f6ed3ccefc64502ac599a38fde1e7424e8a9a7fe8660055332e693d84ee9702d3ff583e2445e201bff209b7b67b405447") << OP_CHECKSIG;
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
    (0, uint256S("000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"))
    (4300, uint256S("98ec023f14dc6479b50a45f8090e01e7127e5b1726184f09c2416bccea26a8b2"))
    (8601, uint256S("8d946a88b999213d4db592bfe07e44ad2b1e2f005e154e108b3bea51d49d2a33"))
    (12902, uint256S("5ef433ce24827b8facb1e41d366bd1075294883f8647839f2049445721e45700"))
    (17203, uint256S("e237d47910dc89442070c3e256497dff0c27b6194f63fcc509452c8df112b066"))
    (21504, uint256S("558b1664607bef0e80de58d2180e37837a58944f3d60c5bcee7d42f583c0392e"))
    (25805, uint256S("ddbb48f8874c4b74357f4c866fe686a0a8cf2f451ad854adc8827c3460accb9c"))
    (30106, uint256S("e9bdfbbb362d20a95f50832269b37f2a7b29a538a0daea41df1193649dfe360a"))
    (34407, uint256S("f9298ff35e29a0dc1cc9fe6f392b7c24c0999335ac7ccfb201b59a015bff9426"))
    (38708, uint256S("cc7c0e53511da28eccda4f9041978c06afe5cd45ca363ca2ae27db2be237b4a7"))
    (43009, uint256S("5880289edbb43eee1e41d856dcb25302bf16f9a589badf5d7567a3025dd3c39d"))
    (47310, uint256S("11317940ad02da7718fd312a200fc058f441c259b28c863551c2acbc7c2d1644"))
    (51611, uint256S("d4984c4a436f92456e08e408833d4e4627e9f9b6a06143dab6d0a8ebfed9cec8"))
    (55912, uint256S("4731d85165b4ca3248ab1ae94809922206736fbb0ec5f99d01464ec9ea93a398"))
    (60213, uint256S("41edfdf3c88e2b90f84e41825c065117a0161eb762f7d3495750b13917727417"))
    (64514, uint256S("c4b3ffc5bf2fdfd3ac32f62609f4c4831862a86d12179a94b1557a86a3334f07"))
    (68815, uint256S("53c87ea63d1b82fc21b1243bb93df6a6f1bd8bef0b46c5ccf9a526441d2920a4"))
    (73116, uint256S("4d3f3284d73b56c4a59321e20c90c6f78335bed3175c6c174dbb3e41dfef179b"))
    (77417, uint256S("96bf1d493a15543d90d590697c7eca942e3b7c12a407193e6df5aed5b1a0d6f8"))
    (81718, uint256S("782169c6bc51cf048a99481cac9e5064eeb835279a011875795245d947e785a5"))
    (86019, uint256S("34891117fec1d4cb534d679a12898b725953f3b8cf9ca88f432d9c23d7fe8085"))
    (90320, uint256S("0f9ead60d1b3feb3a16660122fd0a3ce0ecda1b5ec92c699829b8272096f3004"))
    (94621, uint256S("d7f7748d29369a48ba34836b05ab5a75df2596b0fb1b51ce6cfb1c9a608f53e1"))
    (98922, uint256S("c3e0242741636beb25d2e00b8c6827a8a22404ff90aded3b2e0f3e0ac5083b6b"))
    (103223, uint256S("8d84e5ca09ba950d81f5f74f8d3cd37255c143d168d26769d9fef14246477150"))
    (107524, uint256S("dec3fc4b0e81fab153de1ea7b8c97ffe0dcde8e73ec94f84ca56bce8e6f2cb2a"))
    (111825, uint256S("88b85bd3cfd46f8e430432ead3ecfe63f1274751379013d1596cbd47fcce2a74"))
    (116126, uint256S("cffcf808940404a73df984c8cbcc931140449433eb2905ae3b80070b17e6565b"))
    (120427, uint256S("106f14bd793f4704c0916e6680e107fcf95c8f55942479d37ca2667c8284def7"))
    (124728, uint256S("5a20822db8dad2f805800ba4e17a5072055adf7de98cb34d4c15aec3d422850c"))
    (129029, uint256S("6b4549af63651fd6eeb943add7d44abc8d6adba7b2e2dc6857c33bceb9dca41c"))
    (133330, uint256S("d6229a52509d0470086f142f008c8e5d3b3d64da9342dea7d1f06b6bbb27ba7c"))
    (137631, uint256S("ff80187081c35601a0e8977cd614720cda908329e0155dd04c1747c7c18e54aa"))
    (141932, uint256S("73c41ddb81b149a4216422280096adec371870c9efb750f5095d4cb26c4d1fdc"))
    (146233, uint256S("7d7ad7ae8cfce853b2ad686014e428756298212754616a5fc1f4cd729971ebf8"))
    (150534, uint256S("6350260f0a15e1420de41ea20807060fc4d08b8787f4ac33feae2b86400cb489"))
    (154835, uint256S("708dd17c1312be476946ca5cde240c7581a483060d4c38a3c55422e0ffe75c71"))
    (159136, uint256S("ca8f28b4eade78403416da0f213d8c80144b0b4253c948bdd339e55536166bb0"))
    (163437, uint256S("299159f0765de49f9d87a8e580840ab80d4a1c5784331d20a685d8d006014a9a"))
    (167738, uint256S("878bc56c365682adb71881ac9fab00f93861ab86f93f8d04e05f54097940a1dc"))
    (172039, uint256S("82e26aa040895cff1f530fd9e41cb19a8dbb5b0f94686d0682a12fbddc688a74"))
    (176340, uint256S("5ec9fbb167f2a27b3b609dc0cc627b0c651a500952fe5a1d6ba66a7ea21eff03"))
    (180641, uint256S("52fa7c43e6139533cefb9c91248d8bd4025b7412e9fbb867fcb5ab043951dad6"))
    (184942, uint256S("0e0c78e5fd25d0e761a9aef45d5a142c361d87a8d788840ea2990284dca878b8"))
    (189243, uint256S("f8a7898275386360bda99ba2a3f68de4555a7254476672f9ad679a8180653533"))
    (193544, uint256S("60791402273569a82a8d94d6b947d65417b54c289b3e5bce373db8d136bd5bce"))
    (197845, uint256S("827e175a85e63511a1f8708b415d68e849cf8f4d9fde0bc22e13648133ffa2ba"))
    (202146, uint256S("ccd8bcd6295e56e57fdb1334692fdb728215f0318327b4eec5e90d73831538cf"))
    (206447, uint256S("e651898a1a7bd4e7d3746cb24547b59c01c4b39a9808d9aa6d6ad18c882a7d72"))
    (210748, uint256S("41388208fdb218ca2b7aaf26066512faa26e26ad85f7580ef3a989d1608b54a6"))
    (215049, uint256S("6f465de8c99d4ad842acfb26d205a49ee382de84c5a18ffe69c7f93f1703217f"))
    (219350, uint256S("520bc6f773e2020ce3d36e27738b898ed135510da2ec58fcfb6e32e2f12d1199"))
    (223651, uint256S("b702ac657ff7b3d2f771fb995e73b7a7e34b197152c5877631a2fb836063ce22"))
    (227952, uint256S("c2ee6fecfeed94d99b7ecb7af21009c0e1bb53d83c5b1a34b3d04b5255559c80"))
    (232253, uint256S("8bcac006641f94142fa705170eab48c14ac16c484d99fda0121002b0780ecda6"))
    (236554, uint256S("39c826a257f0de435f9f0acaff1d3b493fe71ff6129b7449105024b802dc2ce0"))
    (240855, uint256S("12a034332442b9ee1f61b47d5c9982a09106a4d57f53e79e4534708d49c0b3d8"))
    (245156, uint256S("456ebb7ed8cb873f9f1e45dfaf21ec7636eab5606d9e9445326a60e864fa5522"))
    (249457, uint256S("d8324bcb136bdea125226c9a3d1b7591da848a6a44bed16d53e4b20a815ff249"))
    (253758, uint256S("b417160b18cccdc6178cee6d5d80be8b5512e6cddbe1f13f1478157932137bf2"))
    (258059, uint256S("7e01329571a8c3c9f8cb795d57d24b37281fc1370f144eaa0545fd9e39798373"))
    (262360, uint256S("fba62534a9ffc92eb3e274edf55132199a1248c37dec2959f371912e99cb1b6a"))
    (266661, uint256S("337140a6c02b39d8ceccd4246ed0584c7979459019d022f3e1f958ca00663113"))
    (270962, uint256S("886067e5f7393195aae047f33d7d63e34fb489f6f8b19770bc71c4d40aabe56b"))
    (275263, uint256S("4ca3b1d2f5c8bbe0e5618fcba3aca105c6c4fcd04f3a9064d30503d57d9003e8"))
    (279564, uint256S("738ecf5d265194d20240be1ccd37afa6bf5df29c3c27ce5905d8f33122ce0a9a"))
    (283865, uint256S("8603caa8729dbd84cdc3995f05deae84668e35c4f4233d2ea777d1c2147b9653"))
    (288166, uint256S("cf70d5b200f780ca603470eaf96e1d451b9a22a9c8d019feeef345b0eefbdf6e"))
    (292467, uint256S("cded11124084a1ed834c355f13e87de03d60ed06107e0e31b67a014ca5486dca"))
    (296768, uint256S("0557332d3ad35462bf39b891293d6150531f56cb6146ce0a9c4893c7093ae79f"))
    (301069, uint256S("622c3c6ec87835ed5bdc436895e7cd37c97a92e02eeb6f856d6bc97b74326c10"))
    (305370, uint256S("c09e349e536d2a999a9710e5de92eb2da429e4f2be317ff72ae2fb74fb850751"))
    (309671, uint256S("37bf3692c5fc32aa0383e3cb059607458cb68290a9b103884af8ad11190e2d8d"))
    (313972, uint256S("53bcdb5d7ff45cd1dbc61908e4f0c1e4a809c54d21ae1cb612889f2ae9e80080"))
    (318273, uint256S("f3a8d213c4b1ff4efb4b488f0a1bf0ab22457077b5c3359f9bd1d2081a780c67"))
    (322574, uint256S("7366779a6d7c168cb6e6671704837bec0b41a1c4726614b987ffb05cb5d1e20e"))
    (326875, uint256S("e3a8331b956fc0ab6c8d7ebbb8b1d46d87e6f64d2ad924c2114dff71dc713885"))
    (331176, uint256S("8592633341479d64a04e5ac8ce21148c8d39c75516701a976738be72fcbd0efe"))
    (335477, uint256S("611a498ce6dd42f94cbe8b9eb8d99d2ae248d14044eaa4dff3b291f1c3ea39e1"))
    (339778, uint256S("619ef54dc9a0096ec757c33b36f1f139318bd4cdc03f64169aa6c26a611bfe51"))
    (344079, uint256S("d2755c1a6ee4db78dbf8eb95fe591f5555da85b24b77b724acfddf01467574ca"))
    (348380, uint256S("11c71646addcd0fd6afd70364a735a1ec4350a560724993199ab424690c3111c"))
    (352681, uint256S("75722dac4ec0879d1196201dbfd1eb34280be3235b14848dfe2d7359f79fc74a"))
    (356982, uint256S("fe3f98a3061de75ab869c787c01ec3f3b3aa70686a8393b28fa54994285b890d"))
    (361283, uint256S("78d40b15bb52ec3f30e7ee256c1f25ed950d2fa2b4664a43181bb16c47956429"))
    (365584, uint256S("1976cc67fdf227e957714067e46617dd45f9678584043c80426dd487b4c506c9"))
    (369885, uint256S("1db9c1938e9618110fa977fcd64b90602e7945f1b2787a94e892aba4640e6536"))
    (374186, uint256S("87fb17c7deddd2acfad3513adb7bcad7168fde47a47c89c3aca760a6b19e040c"))
    (378487, uint256S("4cd524ed604053c04b55b14352dcc9749366b402794efbd53bad7cffb1b1c909"))
    (382788, uint256S("dd9ceedf9722dcb776ee6266848fd04c5478ee01c958cee4105b41cb4097fec3"))
    (387089, uint256S("f30c9a4a2396a2b2178a7b57187a5a0e3223fb1cb6c066137eb0fce40b9980c7"))
    (391390, uint256S("763f7eb23827fa1eabc692f4b43c4f475994b6754e0a9d468a827ea8d26c98ee"))
    (395691, uint256S("07a22df9c4d620748a7407a49f063541fb41fa1d956df364cf6b2cd1beafcffb"))
    (399992, uint256S("2fef4c213b289e7c3a7ba3738d140d045cb8f5f9ef9a4dd9c43865793cf820aa"))
    (404293, uint256S("5adb63716540707bed3638d6499ad39e027344f8e69f60a30985719344a7b1cc"))
    (408594, uint256S("901905d06eb646fbfe715deebd55157e403adab0181dc3454f655082a0276541"))
    (412895, uint256S("f6b67cd7f8cbe03bdb5fb31437838beca9c62a0afbdfdc4930e1a24c97e4a05c"))
    (417196, uint256S("5b975a3ae807ea268e736085036f6244e8757818ce23131b564ccecc46fb9add"))
    (421497, uint256S("66d31195683a6f2a02132428d668337c8eac46b5b6835d5474435e4a3d565874"))
    (425798, uint256S("d2a7e41b998dee477150ac8bd3f1d378279e8a4a9f9217c02ba8e43bb265e7ef"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1642087185, // * UNIX timestamp of last checkpoint block
    929082,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2866        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1533446237,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1533446237,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1615902863, 1765803, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit = ~UINT256_ZERO >> 20;
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "cBURNXXXXXXXXXXXXXXXXXXXXXXXT5p8pX", 0 },
            { "cBurnAddressXXXXXXXXXXXXXXXXVrq7yw", 0 },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 190001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 190001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("d2b726f6c67aa8f9444c918a9ee1a7a3f3e71b6d214d930ee1b486e1ccfc49f5");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("13eee22f4b637ad17bfa5836fb086d4a3985242e68f32d483138bfe9240c8a3e");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("5c592d9ced3bf780c0d9fac0a46a479e4b9b0bcf834d8f6faf93475aa286cf94");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("6ee546e646f1277c4d38944a83212b051531f745c4bfa54bac7633c38c47fe9f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0xe9;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 13333;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptoflow.eu"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87);  // c
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);  // f
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 102);     // i
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x44).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1615902864;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
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

        genesis = CreateGenesisBlock(1615902864, 42773, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c5ee0ad5d40f6b26125819d873afabc0c0d47034c97d7b1dd74511215bb"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 12; // cryptoflow starting difficulty
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
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

        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x16;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x15;
        nDefaultPort = 14333;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptoflow.eu", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptoflow addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptoflow script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptoflow BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP44 coin type is '1' (All coin's testnet default)
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
        // // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1615902865;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 0 * COIN);
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

        // // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1615902865, 506, 0x1fffffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000817f2ab1c84d7ae24a42b8cfe71f401f6c05bce5499b9550128e73606a238"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 2; // starting difficulty
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
        consensus.strSporkPubKey = "04ae5f52611fc9f3dcd3f2db88ad4a9b10ab218389cacd1ed07cc893af6ad2f3e6618090edb54038e5a26d2c6d04db4a6c901a8bf52a72fef484f478519fdf0b02";
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

        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0xa0;
        pchMessageStart[3] = 0x93;
        nDefaultPort = 15333;

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

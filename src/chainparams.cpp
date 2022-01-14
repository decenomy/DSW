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
    (1721, uint256S("17d51894ce371a79d2014ef5658891669eec07fd4767c6a91cc7aae8a27304a9"))
    (3443, uint256S("9bfc89825baa9bd86a02e68056896744cb71b25790d23332275482a0a0bedb8c"))
    (5165, uint256S("e19a935a5c5c9504cb5454b47fbb511ab717e43f9b80ba798493a83bc0cd218f"))
    (6887, uint256S("3aa9db5ddee82a4f49fd4730b46d33bc1f1a53d5b84d9ef12223c23ae06b54bf"))
    (8609, uint256S("f19f49e3ff8c9abd608d4b96dedf2aa8efdd3946d6701abf738a95f28f087248"))
    (10331, uint256S("ef7ce8388dc303ec60987b6cce8e2fc95fd524de0fded6692ae9cb450afa580c"))
    (12053, uint256S("ba60cddac9271434d08f5c5644aa452cadb808ad75b67f2d55aa2c704d4a0475"))
    (13775, uint256S("c45f7113de30bb8661dd249ef22c73260b767ceb893b6c8f2e0068d60760a69d"))
    (15497, uint256S("9eedbc9eb43fca1af0f0dca2d452ebf47b931928d30d9fcca2ff0e7a6eccd88e"))
    (17219, uint256S("5be49bb11935ef3663ecbeaf557dbc839920f07ef1aa976439e508c875773e35"))
    (18941, uint256S("c4dbaf4a9d3661544f9543e9735df404e6adf4e152af67c05ecc1b3eefb587f2"))
    (20663, uint256S("6fc155add2969fe7d034a85869424c29b6dc68fa7db405d8935e6d926bb1596e"))
    (22385, uint256S("d20e279a40605e745f988667377baeea6aa5ac8d77e4b1dc3a708cb601a7a52b"))
    (24107, uint256S("720a06043a6d513fb085f354ea553f443ed8cdb9098941ca47077f6e09f8cd38"))
    (25829, uint256S("e3970ab83411a143c527c369fbfc1cc67c22ad5e6fe2c26d44fbca417ba08c2d"))
    (27551, uint256S("2abd4c3c2c3982984b0f17aebf56f5e1d6df83f59b0010aa9ef10cb577778ea5"))
    (29273, uint256S("23a32291103e17fbd21f8658af3889e6fb067b8442940e2b008d34326a4aed9d"))
    (30995, uint256S("4830d629545db48daed025a855e73b421f236e480742a3d35d4a3ffed500d34e"))
    (32717, uint256S("7724f2e498e6798136a34f923bb249586bfdff02f4026e4a2c92918fab0ec744"))
    (34439, uint256S("6a54b3accf76e034a0030aa20e28d7797a033d0fc24c0b967c40c42867bf3dd5"))
    (36161, uint256S("734d025d9835b37b00065cb135635f4f799f1a5eab9d2df006ebc32c441eee26"))
    (37883, uint256S("3cfbec289b116864ff24073943a00de674dc77d83c68f5a53d36012f4eeb169c"))
    (39605, uint256S("899f60832a82f27b07d4c7aaff89817430d9ae4e32866bc42f90539f8cfcdbe1"))
    (41327, uint256S("2ebb935258be7445cab68a2eda67138425f4bf9825ebf2502e7ecccf1123f2d5"))
    (43049, uint256S("335e006e31cd007fbcc5b7c1cf27039d474f8c225f8a99241d7d1a737ec1ef73"))
    (44771, uint256S("2be61ad2ce901d13d8f2ee94c5ac99b16c6d74fb5a420ffe1eaffcda710fa6ff"))
    (46493, uint256S("9896352e8b8f6a7d7625301f7e8da4957be544eb011f52aa1f8a8ecf7db937cd"))
    (48215, uint256S("ca5605085bdf1fedd28efb03dd3a20546034cf00b7f0bdcc2314118feca16e49"))
    (49937, uint256S("6e8ecfbde5837d55fab0a1c9d69be41376d99169441aa03131ee794d3d24a57f"))
    (51659, uint256S("00fe563ce0cb134cf8fc621fe8973dc3c200a96f472907270938252cff298342"))
    (53381, uint256S("518d265f73de1418b0b7ac6bf162119f406dc07b32abc97fd0a7159bb1087b38"))
    (55103, uint256S("5daf2a05129df6035c3bc278a82c2422fefc698f9f2d3b59450875b8b148b460"))
    (56825, uint256S("852461b8878454e92faeaa16a0fe1b3190fdba3f7a65f3bc4884ac6f212385d8"))
    (58547, uint256S("8bcb054e58e3c1b2d66d800813b0e708cc8a0e5d14240ccbdbab080fa44619d0"))
    (60269, uint256S("57ce82ecc638874efdde9b0a049c40f885a2acfc08c5340215eb27b5eeb2c00d"))
    (61991, uint256S("47dff9257107d301c046cb357c554300e6631bf5aa1a2b9e4d1f63139fabf546"))
    (63713, uint256S("6cccd115413d8555b4fbda19c9536a96e637c3bf29b4f17befcf2469f6c70d91"))
    (65435, uint256S("5b2c6dc7c4b2a4c313b2076a3e36a6cf7f1b91f60b9f3fd71a6e8491d0378cf5"))
    (67157, uint256S("68c2dc082511a0ac919618ef9f631caa82808a58161ba9528782e6b65cb6e99f"))
    (68879, uint256S("7704afa890fe5ff0528205390e77d05f1dbcc852812835337bd4b551d0da8a5f"))
    (70601, uint256S("3d3a9b216908d3ced34c4f486a02fc04e5de384c6554bf6fb7cfdeb5a141595d"))
    (72323, uint256S("3e1b3e50811c69fa5b0145836a82d21c212a7b230154840b6eb3e3eade6906cf"))
    (74045, uint256S("3b543bf47499da5c0f37ce0ce252fb4c048cfb86fefff93a37ff7a68818042f8"))
    (75767, uint256S("71dce5ef058eb992372149946e7ca70aaf72a24073f47d1ddba525d965d65227"))
    (77489, uint256S("2baf016d20eb86b49501c38466325db35cf00a1c9bac480990b7cbb9e98b4618"))
    (79211, uint256S("3c6f10ffdd8da1bbe1a2e0c5cdcf4a14f9dc679a538505ff441982b57408f2a6"))
    (80933, uint256S("c3cd7df2c07b0bd0ad160ab1ddef89a596cbaa8ba7b19927881a4a6950a59685"))
    (82655, uint256S("3bda265770a8baaf3c714441626da6ed08ecbdbd4e85db798f4058229c6bf145"))
    (84377, uint256S("82e19e79f56ef64af3e537c45a198e69607b95b4013cae088089a7f3b14ed4ac"))
    (86099, uint256S("131f3731553f23e000a17de256daee638b5d535ebfa752298aab8b989a7581f7"))
    (87821, uint256S("606841770fab2fa59ed6b52d308a4266809fa7eb84f5fffced0644ce8e4bed44"))
    (89543, uint256S("7492f2c8d23f214f03d75f7d708bc1ac6ba15c12fae9743f4f0ce47798889d34"))
    (91265, uint256S("a8b3d59ea33f4d088a31f78a7399b7cc392a25080738cecc257d0b53cd8034a5"))
    (92987, uint256S("383d75045a0c5b9cf34cd9f3a0005835ffb7b965e338e9d265f606ec5f03f88b"))
    (94709, uint256S("3c3ee70e1aeea6bba36239064f338f6628d953c1a8863c7f9dcaf79b7e9546b8"))
    (96431, uint256S("b5793d89df5c2e127b1a6a10ccb3b953216f8b77aa32626f9f0bb0b1064891fe"))
    (98153, uint256S("eb204f794711575f3a97c1b182226fbe511414cae2317c569045bd4df0e6acc6"))
    (99875, uint256S("e5b5bebc9d6fcd878a84ab9012ae546495c6661353e6500877a0d54c6b6b591b"))
    (101597, uint256S("fb0fcaf8047bfad0aa0505e02c64aa3d64ab6ecd570e7a4fd1f1833853e52dae"))
    (103319, uint256S("b21d3c396d1bcc8d2150e5252fe40bc6993d327d1e2ab36a3a146466827599a3"))
    (105041, uint256S("a07c4dd963a4d9f6e0ebaf6ad26f7b119f11f40f3f1e70f7867e262a69d1b67a"))
    (106763, uint256S("57f8ab50666b34ea22be23347ebda072ea9f49702a45ce700672f85495a3e5d0"))
    (108485, uint256S("1fbd94a6e7666703b9216db52dbf6a67fa6f103673eff4f92308e8b95c1374f1"))
    (110207, uint256S("2acf750fa8d82034398e9c3374a0ff29f9b49a1ca6da8e8ccdaf7266bcfccdcd"))
    (111929, uint256S("1d3cde90f07f1e4a5e5db15d3b5965377be4394779665ba70903f42477760837"))
    (113651, uint256S("b379fc53382d861eba90795623283207d2dde11f7265960e3bc8e5898b61c868"))
    (115373, uint256S("b3e03515019bf2b1de98f9b6309fd7418c9148372d41c36b7b989915e5b8af4e"))
    (117095, uint256S("ccdcfbdaab6a7109e6cfec6a1e0fb39fcd7cdecd7f6a002aa11f0ff4e3bf470a"))
    (118817, uint256S("a63dfaea2f5859596f0655532cb701d5880f350499ce143a4e947e0a34f6ea9d"))
    (120539, uint256S("881f97e64664340166d5a03d5a82bdec39711640236f736ad4f48c1ade6f00d5"))
    (122261, uint256S("4e7453f43fb7ebb6f15ba8e3700fb1d6930b3229e5fc9cdf943c1b2f4e5594b9"))
    (123983, uint256S("5b1f27f993507a89d2fe37e858b2e4913a211b04442bd9315e63e12291b82b35"))
    (125705, uint256S("a0758c4b520cde72caa9e393c39c419821688732969d5cc752919dcd5100611c"))
    (127427, uint256S("4c4c2120e29aa3dc1d96c22bc66d183b4a5ef92e323579986ae1894a131e352f"))
    (129149, uint256S("6a2d939972336f2703c6e4baad79c63a3356089abe84e6c37cded3b357de03b1"))
    (130871, uint256S("5ef472923a2b8dc4e6a2a6b9f2b7bbde61aed762fa9714659517901ae1840af3"))
    (132593, uint256S("64881f67cab66dad31cda032d3416bc48b23d3ea53a06d17198b6421626a272e"))
    (134315, uint256S("3a2da04d76c3a148a760bfa9ca969e27fc0652950530f3ebb8b97c3011d9c1f4"))
    (136037, uint256S("a2bdd3f36e23ee6464fddbbb632ba99a01c34aacadc7873c99414194b44f5bec"))
    (137759, uint256S("e3860098457b1824c01c95af2fbbfa41f2e273fb965b4b44091967b01a19ca28"))
    (139481, uint256S("cd26300c5126a447c4c50c284f897a58e31c3da8881a7d62a2f558624557a651"))
    (141203, uint256S("0a7c77e91d74c312bcd7ad38eb862c949b844876a841ce91b29561a64fea71d6"))
    (142925, uint256S("5871e849d30942075c61c3ab8d2ae86ba7f6ed8cfc802789640c20a28c9a6720"))
    (144647, uint256S("7630d6060250b15bef3ca7e8509f009b73233788d3038d14d0fac9d5052bfa07"))
    (146369, uint256S("1b21aa2322c7ad3e36a726b41ca82464079d6742d9df2c4aa61b2ecd21927984"))
    (148091, uint256S("360ed515e6ba9cc5e60a703e11481786b454096dc6eeb2c0dd36573d6a409601"))
    (149813, uint256S("43de18480583c1093562a3598776c5be8bb19b841f67e1407b81bac9c01c54ee"))
    (151535, uint256S("b00222e7460f2be74889640c61d8f2e7db504302f06d7f05f5c200ae25b88972"))
    (153257, uint256S("0da8ec44057d9b28bd058b5ff468e4fe1db0aa148a1854c2cd32951aaf5df4ab"))
    (154979, uint256S("d2f8bac9f6188b745b0e1f58a9135bfd21c9a21a8acf0e845872872a46fcfae5"))
    (156701, uint256S("4e76060fb8027d3c6ff534beed76e3ac167a27d7635759aaee0d4a439cafa540"))
    (158423, uint256S("9e430dce4ab317482656b3e7723ab591780c74ecc1dd476b58fb52c95c842f7c"))
    (160145, uint256S("d48d758c2c1e76457d4e6116fa609ca5f6f250a1080b0f291adedca738b50feb"))
    (161867, uint256S("7286f995f0ec9024f099165db17bc125930fb07d45d3bb22f8afa603f43a137c"))
    (163589, uint256S("c81855fb4afd262c9b798448f389c61d3ef0516f5311651b1c582594f399988c"))
    (165311, uint256S("c37e9bcd49f53071e5ff8eccc27e10eb2847776f70ffabfc5188aadc40974a92"))
    (167033, uint256S("8f49b556a484c0d2c7d254ca88fc53225225d5d5eca5a1f8ddc1e7d1a5fd27f5"))
    (168755, uint256S("03adb0f6fc6425ddf3268d4011b6704768b7837fa31d15c1ce4fcb0e61154b17"))
    (170477, uint256S("4b3bb78d9d4fc17e982a37dbd335986f94505da5b6af1f52db6b68cf2a2313a1"))
    (172199, uint256S("5b147f84ad7708e7e6cc9ed647c096e635cc8c73cfc3085f5dd551dc65b2ffb3"))
    (173921, uint256S("ba4547ebf7158055a99f0e8af6eb956882283411b58de2a7a451c01561c96caf"))
    (175649, uint256S("758218b769331902fb41b5cdfec14885400fcc01d52a4ce1f575edeec57cf7d0"))
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626699585, // * UNIX timestamp of last checkpoint block
    373698,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    3063        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 30 * 24 * 60; // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;       // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
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
           //{ "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
        };

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint = DISABLED;
        consensus.height_last_ZC_WrappedSerials = DISABLED;
        consensus.height_start_InvalidUTXOsCheck = DISABLED;
        consensus.height_start_ZC_InvalidSerials = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck = DISABLED;
        consensus.height_ZC_RecalcAccumulators = DISABLED;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1893456000;   // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;    // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5; // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint = DISABLED;
        consensus.height_last_ZC_WrappedSerials = DISABLED;
        consensus.height_start_InvalidUTXOsCheck = DISABLED;
        consensus.height_start_ZC_InvalidSerials = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck = DISABLED;
        consensus.height_ZC_RecalcAccumulators = DISABLED;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0; // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("0x0");
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
        consensus.nBudgetCycleBlocks = 144;    // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3; // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 5;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5; // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint = 310; // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                               "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                               "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                               "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                               "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                               "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637; // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;         // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0; // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                        = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                     = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight                 = 400;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 300;

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

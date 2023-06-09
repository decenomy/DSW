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
    (10375, uint256S("d0f79f7e50730fda0d9169d69d10a64ac3e9b81dbcc60e626d1a1965db754cd0"))
    (20751, uint256S("f1ddeeed6d8a32e45c24907d625c0b67a84290133ea7bf758b656dc09d4c7d20"))
    (31127, uint256S("28a13a2214fb99a453068f7047501b77e37075b800029aea72fd47cde54797c7"))
    (41503, uint256S("2d5985561bf1141c44c13a522d7e7205eabf37954fe884185d97548bdc46ae01"))
    (51879, uint256S("d4f97371a53520edf103c6e2a91d7aebe77e0f7bb6abd72c9db51697100cf95f"))
    (62255, uint256S("f63bfdab1a0fa3b01b323cc6b0c0449907c9f9413ec866379a6193f60492bff3"))
    (72631, uint256S("6a4ad1b45698607ebfec1aa56be1168bdf5a71655d94e6672b25c6475125204f"))
    (83007, uint256S("766ad12c6c967d0c0f6382f83ad86aef5b923234699f7b429bb5b76e2a8dc856"))
    (93383, uint256S("fb819f7c1e261a8abd5d476a631803f029bba0a5f8378b129e917018c51205e6"))
    (103759, uint256S("9b232dc44b2b9eb4047fd550cf4a09d6aceca4b44092d5b0454132a834d333d1"))
    (114135, uint256S("821f5e70e174fb5941f3c44b23b58de4d25105a8318df4047786383cd7d29752"))
    (124511, uint256S("3ff76486ff2d86e9d07028802d9d02b3306be599449e5d7bbf2885ebad468855"))
    (134887, uint256S("88cf6d5ea989b5ce201042ed5e30ea3019c56a296615c757811decf2ad7246a2"))
    (145263, uint256S("38e5203524a8fca999d0570e1e75468cbfd6c861a672fcdef7c70aae484cb474"))
    (155639, uint256S("b480e92f4ea3a34926ed20dfde05833ad55d25a80309a6823562ab7f74173a0d"))
    (166015, uint256S("c42cf12e3b074bf9fa0d336074428a933583e9e84e214bde8867aa8df1bd21b8"))
    (176391, uint256S("7cfd7f17505e28ac3b606a478a9673f0684fd8e6373787f9a38cde2c05eca559"))
    (186767, uint256S("f97e366997534337ac46a10b52adc750c29f19b95877a253f2cf6e8b474bdb32"))
    (197143, uint256S("ba04acbc61b5edaab0616bc6de1eee9e02629120ac2bb701026bbcbe5cfc8825"))
    (207519, uint256S("7ead4df1733479f87fed5190b4df33e881715231445a8890e28126fe8b36a901"))
    (217895, uint256S("8bd4b299afd0164626e2d2b7346ec4a4117108ff859dd0d1415f9a736cea82e4"))
    (228271, uint256S("8065254b57a30ea8785ccc0d5b4c8e6dfa465456a5fe23717a3b816056bbb79e"))
    (238647, uint256S("f827b075f01c674989e0c938f7307b293e805a5a80085ffa63351c39eb442113"))
    (249023, uint256S("dd8a335095ff97e8a8cff2420cb0eea250b3d52cf17c3c8285548bfd4597529b"))
    (259399, uint256S("56392136f08340aab59767e1866535ab4a5163e11d48c6739e0e0365b10540d1"))
    (269775, uint256S("78cf5025957196f707a5106e16051f976d00f198252b7b768e45a1452e260a0b"))
    (280151, uint256S("b664fad2c5d3a56ce615aecaad9172235db049a62269951696f27ecf8899013c"))
    (290527, uint256S("36a86426cb9d3c42546a32affc94f94cf294b20f0d6bd3bf8895d7dcae4f3b15"))
    (300903, uint256S("db4c384e67c588e128f126f4bccec2aa15ed8e7840ff56f7eb3b1f58c8ea2f11"))
    (311279, uint256S("357e6543603d98b88d175564986aa5f13f91ea8127fe34ac584f3c1df9945cb5"))
    (321655, uint256S("5b179e5ae5e403bac0823fd26b671413a40c99e856158149bb03003ec377b647"))
    (332031, uint256S("a160993498bb17c6098f50cca563df615b8700df8ee061a135af0b8fc6cb5a95"))
    (342407, uint256S("9444c6f11ed1a836c48788cad08da5e64d9811b3a33e192cef133db733c33299"))
    (352783, uint256S("28f6b908cb4d174b6cadab4cef9683c36688e432f7e513cec5fb8ee0605f55f5"))
    (363159, uint256S("07a9a48ec87cd719c788ac007c44ff96c88f2d0a09655492c6aa6e6c61d9a053"))
    (373535, uint256S("0745ad588efbadcb1078c0ebd5b604ae37e93d50b1e9744bdbb31dab3c358838"))
    (383911, uint256S("741b677d16d0e29fc8fe0789b4d216955799e4aa39400dce9beefc79f4491348"))
    (394287, uint256S("e2c279da513b3816b884cd923f09cdbe82a8775068df19aa60ef60ccbc281371"))
    (404663, uint256S("74b8585b6bdc8cd660023e4bc301c652a223504c99ddba990c8353066f0a4825"))
    (415039, uint256S("e7b4dad5848588d21899b4b024e29b0361058844262a0ea39e3cd0339d057004"))
    (425415, uint256S("65d523821590909b48ad8135541115e4b84fa3e939b4b894805b599fdcb54fc6"))
    (435791, uint256S("8c9d07197f5046806d9b676f76ba23c517b3a37a6d956595faefe0fec8243df5"))
    (446167, uint256S("49304b547c4579d6a202a740fad5136e0834c29e5b8dd7db825867eb99591751"))
    (456543, uint256S("13ff5eef422eec3436c0461586a3d3a38b04bf0591599589b07abf6dc0d16811"))
    (466919, uint256S("a3f11a1db38a26fa484b6e5e9dd79d66319371f70cfdd1a91a34ce97da6b0bee"))
    (477295, uint256S("1a52976e5fe8eeac72d35ade787586ac3b4ee029b057a693b953210b26997d71"))
    (487671, uint256S("f9ed6a86eaef663736a181e91916d8fb7e8571ceb54d3567937c022f5355893b"))
    (498047, uint256S("34279bc630fcb9c9ef0a381e449e758578a1cb070d19ba359d3be609bd38d6ee"))
    (508423, uint256S("81dd146ddf0b0a8b0b535aabd059d50d1f4770eaf6bd5d8d97fab335a983ee50"))
    (518799, uint256S("a312d7271b344faf15cb77a39bb04233594f5afe43b3b8f47e2d56bd381f8510"))
    (529175, uint256S("8aa83dc737dd0d419dc2b367ee8b7c9a7124fbca359398166aded8c4fa234828"))
    (539551, uint256S("e5983d4d5cd0b0a324572e16d6bb80ff4bbd0a7f72991b455b843dc4e4dfd81e"))
    (549927, uint256S("2f1c6a3d9066bab9356150164e77fa1d8f44611fd1334267ca3770f7f4f2316d"))
    (560303, uint256S("4c8a430fdd48e7c2a0ff479de98057f5d5091c5c9c454229b20b51aa6e00694d"))
    (570679, uint256S("6c916095350cadbe108848ccb2bf7481c3a51fedcbf69e90ca1ffe2627dff6e6"))
    (581055, uint256S("2e319e239834381b44cd306fe3bd89e981fc34b81e81ef06730f79fa5e1a8795"))
    (591431, uint256S("6880d14682c33c89c8e039ee19c1688a32dc403446119e4922750add225457f3"))
    (601807, uint256S("c3fb3c2c7c567b81b31662c5ba8af3260ee173bd48594d714a7d91cf536ba9c7"))
    (612183, uint256S("bf5e99a5f252804a5d772ed93fcaeac8ba9a0e60500e9e1961e5e29a42662ddf"))
    (622559, uint256S("b08ee7a8909714d0e2d2808a10d40f470cc0528030a9861f2db4876d92f72de7"))
    (632935, uint256S("521ccb68d6606482d4c55d3f68891862d833e1a9aca81c44eb0aad923c27d8cc"))
    (643311, uint256S("d395b02978242affd67ba792f40bbac6e13c7f3a18c7e36cf0cc2a6ca1611cec"))
    (653687, uint256S("f1f94e76365f4cff993ac5708da7bbea4637471112f02bf47b5d724bdf9ac353"))
    (664063, uint256S("ecca26ef0afd41bb7c8e1a91493f8165b4e0f377d872d7bd6735da5a0b55909b"))
    (674439, uint256S("e2ed38fd75171c34f106175f458ea057352b96ee60138891377b89316cfbfb32"))
    (684815, uint256S("1b030ff4422fe40a2b6e66abf552bf1608fd08246692722e8345a24fba3a12e7"))
    (695191, uint256S("df24fe3afd4cf085e79f783fb08fede56da6acb29e6c8a730816f03bfab52a1f"))
    (705567, uint256S("03191b04451e944e806e19ae066501270cae7c5c134c6f87c9e02ea36091db87"))
    (715943, uint256S("caa3215ffdb95f636e62f15e718a4bb66751aae6538582481c47d151e0878f5a"))
    (726319, uint256S("ce99113a7226843bed1cf5d754c96990fca0376df59ef0e4f91957e454919370"))
    (736695, uint256S("287dc3c4341d61f87caa539a02c8579d3a205c2ab250f8039898db5bbff2574a"))
    (747071, uint256S("dad68a8f38ca013c718810b4589a079108aec14191501007a91112151561b7f8"))
    (757447, uint256S("47ec9a1c53546e52c2b1388941a697e8a8bfb3bab1931b0af0f6b6db5d890d0f"))
    (767823, uint256S("d6271bc47e6db1bd14f02dbcd7767c7cca192b412ad71ad26e1384a95fe44eb8"))
    (778199, uint256S("1d6789542f020d0a1db310298a7e33cb73ff70034f86664eb5933f8d04bed39d"))
    (788575, uint256S("4c9701cdc1420efd1a1b418275e1fc4f734da070f1f065494b9ddf2f511f0b9f"))
    (798951, uint256S("c85287342c171e39c807823a9734ac764f65d23e9bed6464c7b90d8e95b29e98"))
    (809327, uint256S("fa1668034f944f1f14c32cfca0033e004a0d61092d8f8da947f14d15376121bc"))
    (819703, uint256S("7989323b1d6b723d838df53ee71d029588c9f57f8b6a733a529d5fd3c9f0eb56"))
    (830079, uint256S("cac49cbf9fbaad405af2cd815a027cb890c9afaf02d0158f44b00c737d7ea2a9"))
    (840455, uint256S("1747864c8ac6dbea93875268211bcf8b94669ef35effb8c7cb0094bae1112d8e"))
    (850831, uint256S("de5918e9bb72c923868250f19aafe8e05755f24cec3dfb78814d3ca0bfa2f209"))
    (861207, uint256S("467d0e943d97d4d6c5e7b42cac055e50b2e0466ed00ebb2665cf779c0925c313"))
    (871583, uint256S("3c15c341999a393081602eade931a54472d32a6bc2f4e0fd5094d22da84e0b6d"))
    (881959, uint256S("bb817df2ce3a665bdd242ce2488449b61935400782c2f1ab43b483f1272fe5bf"))
    (892335, uint256S("d936a590b4454d9d3e54e1bdd17102037e0f493e3c552a691d150ee5b03de3c6"))
    (902711, uint256S("1c5984c75da27ced00c638b7ef2d878ac9ba58808b3e9c1d7e3e3686852cbaca"))
    (913087, uint256S("bac430496e88de7a27a90c1b9a08a6c9b7be371999258d381a160284a3198b8b"))
    (923463, uint256S("97400065166e4b848fd3af2020bc504ea40a7cb3f93986eeca772b120e33d7e5"))
    (933839, uint256S("6a72bcc17dde2f9d2fe68280274139d20cef2615ecb3eb63fbcf980d8c4e5dc9"))
    (944215, uint256S("e49eaf033d668e9aabcc958cac6cc376f26e0143351a095d3489a701e46c4978"))
    (954591, uint256S("3f37b94c8680cee40b252a9d021413c2cad5f8082647c03f22f0daf2e9d5768a"))
    (964967, uint256S("3ad9d4b9e58283906a963dc82b73e5c8f9956a791361c6a3624bea694850dfff"))
    (975343, uint256S("aee53663368485762092b3b06226a188698a44073ab03b29d880bd7dd27821ad"))
    (985719, uint256S("e934a6c4af0601d0d837712c5808d83073f9185dc4a1e7adac644b6acaddd17d"))
    (996095, uint256S("2712f64d2e85d8db44832fa80b072a7b4959e027fe7b5bf8cdf9d79bae18ce06"))
    (1006471, uint256S("e563a2236b4d856733e2b687759bd943ed760ce53b7277e9e29429a4bc8ffcf0"))
    (1016847, uint256S("53284958f392eaf06ca221abe7cc8d8ec21a0de1e406a12415333422f5220d36"))
    (1027223, uint256S("9b6d7ec8d173ed606bb4cadc38505500f0e8a8babb181d47f1b4638ba8bc6559"))
    (1037599, uint256S("9d6cc0bcf465662b98da439017bb5866c72ecdad806f7fbbc3907744a08a84ea"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686345240, // * UNIX timestamp of last checkpoint block
    2323952,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2842        // * estimated number of transactions per day after checkpoint
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

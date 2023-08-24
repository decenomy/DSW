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
    (11440, uint256S("530dd7400b76141d3dd6f02d8fe0991db81062bf2abb38dadc956d064a209d14"))
    (22881, uint256S("0170683a1e3abd368826e3f8cce539beeb47466c156de097a43928e7a9cbb7c3"))
    (34322, uint256S("850250e26ddc5811d39fa85cf05c5850ef42280ae3935284393fbbc2c722128c"))
    (45763, uint256S("8d4e6057715b1cba3580445a8bf637aaaa6b08977bfccebdb2ba981849a3faba"))
    (57204, uint256S("571984e31678edd6b01f0567c3df3d7a85b923cc620cf952446ab68febb7e469"))
    (68645, uint256S("66146f4b529ddd65677f5471732024d97edaed30b84dfbb99c83b73e83cb1388"))
    (80086, uint256S("629d4de2faa18787b6af08dcd755aaf984c828ae019055c035354c802c1be68c"))
    (91527, uint256S("ee81feaa9ed536a52f78ece354d28a32d0024b087240c29a137e6d95aaf1ff66"))
    (102968, uint256S("a812e584b99a89fa7a2691ba957f646eb610425233cae0e5528defd40e74795d"))
    (114409, uint256S("bc022555e7e348e833055ab174b6efa1ada20e1e271f41b6aebf35c4be3ca9fc"))
    (125850, uint256S("a38353cdadf4a01a91d2241717596e7bec4b4644781275698b4070d4b6eed02e"))
    (137291, uint256S("bbf54ff91ee6147133905454693747347e23b1eef77c8ce64a64b28250917cdf"))
    (148732, uint256S("4db2d4b19fe3aee362acccb00e60823ff8c271d4dc3b875ee463fb34b6964f99"))
    (160173, uint256S("87b602314b6e24c1c1ec947f6e9c5c3c328f5c8382f51d60f1b85a936117abf5"))
    (171614, uint256S("cc84a23966716854e45cc78a912cc41d74c61ccada07357d0530d15abd970db0"))
    (183055, uint256S("94724a062eea37c145ffe430386553a7a942d63adf5a6d2fbb8d2b4791a5d531"))
    (194496, uint256S("d193c34511ba32d7283b1c4b0e0dfd744375c55f6860be370d7d5722da5c5951"))
    (205937, uint256S("7a9f4ebc8fc8748d89e65b785a27962d59dfd5c1d78a5b7f01ccb5cba2629ecd"))
    (217378, uint256S("bc256ea63bc47ad3a18ec9e1118665bfceeb3dfd5d569806608ab0c56d7ca82a"))
    (228819, uint256S("dbdb1c073af8bb88027d3ab965a8b999d2a762762b4d9bd191fd44cfed7cf050"))
    (240260, uint256S("cbdf9002df58e2ab6288010b19f9f30fbba971671e85e5cd7b0c039a527e6000"))
    (251701, uint256S("fef9fd53204da8960e2f5a95b29ee22107e4217a6c036f7a50b421c7880cc353"))
    (263142, uint256S("bb07ec6f390e120eeba54361e0160dbed6cdb0664199354c9705b1d1a410bc92"))
    (274583, uint256S("39e939ec6c5b628d3adf838561464f94a68874fdc568695060ac15f4ec40b68d"))
    (286024, uint256S("0926e9acaac7ca8e92c370aff9976b2d6f96054a07c927cd0c1d4e8b7cf0f30e"))
    (297465, uint256S("7ba200b9b39b1abc6bb642372d4f7fe650725b8cca81bc09fe4088a73c46bb21"))
    (308906, uint256S("5f9fea1e94d21b782f0e5d9eb42bcfa221d918a5ca9782d1b3111e67cc86fa2b"))
    (320347, uint256S("d5e94a698c1754a318efc9de9f6479836f6d1f78b66d237db816af093fc5129a"))
    (331788, uint256S("57d5e948317fc98924bb9697b81ac9eef23a6e6e49750d32bd77a88d0d357ea9"))
    (343229, uint256S("681f5f142593e004a5b2182371a4b2c45966d77b27965bb72d2e5700865f0cbf"))
    (354670, uint256S("6f1f94db6a34f39ef6092b0480b7be98a6fcf05f5415d4c5a52531db45dcaeb3"))
    (366111, uint256S("dc739f858c94be113f89ba24f09f2ff5320808ee3fa9987a12315bdbe7f408d0"))
    (377552, uint256S("e34b0a4332d490d84ce617bd73551578afcc509ed5d8e484dc7a8d28c9d38323"))
    (388993, uint256S("e1e925ea13bed9375f65671617a5018e60c14dd8118af5febd3fa9d9ba10058b"))
    (400434, uint256S("20f2c2e86aadab37cd81a31a449d5239b281eca098c4fa19b63b8f3c0d9b75ed"))
    (411875, uint256S("9e4339527136449f569a3620656acf72634e250150a147d033ff2de53108416a"))
    (423316, uint256S("8e3ae0117d627952181ed63bd9b0cf1e56c5254777c674c887b54c99fef8bfdd"))
    (434757, uint256S("45ca2f1d1457102af8ded261a02ca84342c2e4bf3a32ffbba55768c3ed05097d"))
    (446198, uint256S("601f8a38cdee00af4fce40f853786163e9d56a43a2f7af216868b13ae2b61b9b"))
    (457639, uint256S("4d19c0b7fce6e0da823a1f33c1fad50d56d65411639cb6fe40f7a8c73f0217cd"))
    (469080, uint256S("c6e1a2f14c3bf3775ede70fd6edd3ac431e5cc1dfc013c45f4d6b55696d72c88"))
    (480521, uint256S("0b2f9fd2736426c6e94aa9ce8b8623d9260a3e25fdd2c89c8df2aef824b4fb66"))
    (491962, uint256S("23c6c933b2865a121a4aa34037efeba684fcf64dd358ea90d2c48a1fdcb9ea9d"))
    (503403, uint256S("6af78dcec4978152d8adc5e77d05e315912142f96c00a1c4b0e9099ed85f1523"))
    (514844, uint256S("3b164d08fe48e55ec7b50dd4355e0ba297131862a8f67c50b33bc6943588bae9"))
    (526285, uint256S("093917b3ea04abfdc7fa25247347408ba7051d3ce1b6758a540c445b6cf822ba"))
    (537726, uint256S("cd9ed0aae24f4e33b6f1b43f40523367f96aec4b6af5034d629d6aaeb69417ca"))
    (549167, uint256S("9775b1153ffa5edaf487eae9a97514f7312debf9ddfa86b57a25349bf8f10ad9"))
    (560608, uint256S("44e0b6f07f9b4893db92de6c5279a47c1d44b86bfef9b0dc5003fd6ac6e66ee0"))
    (572049, uint256S("aceae4c99e98a9dc6ed8767bd463575bda759347a775340bf4d5497e615e8c40"))
    (583490, uint256S("5daa53fa0dd754f49406dfde64aaa48c4278d7004d19f4556091bf6af535fd14"))
    (594931, uint256S("09f631880fd73bc6ca3515e07352247537b18ba6bab02580bcc65f15f029d8f9"))
    (606372, uint256S("ec020e17c0d7b4a94e853041e6edfa5b5f32f5babf6f6fe0fd3add653bdec866"))
    (617813, uint256S("123ba1ded3da99590c559dcd1c88a9569741bb5823d9873fede6f32c28fcd765"))
    (629254, uint256S("87d400818abad3deae83c15184c4e7921adb8581b4b51b12c4a7c5dbd9a92af1"))
    (640695, uint256S("3fed586946c24c393902aef73d1db330daf3d8825a513cb0d0a991b0cb1201ad"))
    (652136, uint256S("4746973923378e31d077d2b0e3a50e5d2df9c35f79c5d339b5fe11a4c669e682"))
    (663577, uint256S("685ad5ae11f01653394ad0ad43356013e0d8f3af6bbf7c59c300c11501f315a1"))
    (675018, uint256S("a31efc4f5226609703b2c34880d53a183a6eb4ccf55e8f128dfa1e6e6cf34688"))
    (686459, uint256S("775a02f9a5842d14f4a4524d0c657bc24c761b614aafd16211a59909e71d9872"))
    (697900, uint256S("fa642e38759722ef6dc7fced242035e122d12e368c3ff61eecb2b0c09c1fccdb"))
    (709341, uint256S("7f88f08b41a6550adf44c3e51f734549159863f2838cd893d5b341f95e61651b"))
    (720782, uint256S("2dfb6d01592bb960f6a2db4263592435c5c704fe54416ce03b56679060084974"))
    (732223, uint256S("cb98eecbb54510ab560ac038455508b95f6710acd66b070c957846295c053954"))
    (743664, uint256S("a54d4afc0013dd9dcc063bc67fa9d92c2b5a58ebba231051e06d68be4b7aab6a"))
    (755105, uint256S("5a6c505f0b22cf3bc55181de9b0c74cd9afd66a7aa3be9d1779fd870910d65b7"))
    (766546, uint256S("261ca85a8ebb01214664107dedc040669de719246fceae6f8ffe82ca098b746c"))
    (777987, uint256S("00f86610dc83dee363c46bd69db75321a5dad4e2c949d60b36722e9ae800f684"))
    (789428, uint256S("a225c3bdff75ec0a182482ae2de9f4b053381b8b5b67d5a7e1e7f99fd31732a1"))
    (800869, uint256S("2402ed5d5d3341f3dc063f90fe2c5f8dba4665fa8cbde306acd5aa8f6c27ca2e"))
    (812310, uint256S("162a2d85a23636a6e1d688069cc0b8ef8e96620feb98ab80c4353544d7bec96c"))
    (823751, uint256S("badd01c43d32f9623c061420bf82d930bc91d7ceab109aa3c4153a562ba62856"))
    (835192, uint256S("af29c23339427d86a178b458578f11361365b20f21e59895c7d36f9f9c373fc8"))
    (846633, uint256S("db89edcd3ced689f2efb5caef3a7061085feaff0ce7bcc0c0e2b63c30ff121b4"))
    (858074, uint256S("fc6d6f9b339779da417df4b48f77c502e46933cb5b756c07959c5a3f3d73ebb5"))
    (869515, uint256S("540e5e89b986ac2bef990cc2f1b83400625ce5e97674e67cdf5d01fb3f48f99c"))
    (880956, uint256S("0e2441af8b8b92b22ca0baf43999dfb93c23d69506c8f8ecb9a8e77e4d4ad023"))
    (892397, uint256S("2dfe417074cfd838034632022af045544fd2c998b5dec2632a5695fac26bfc75"))
    (903838, uint256S("00fb2de68f91b587ce6baf8f58ed3efe918c44657928b5c3235fc30850d56dad"))
    (915279, uint256S("c65464cbb2c1db11995f33399cb184336d2f6b98b4e0f54c7ef92f1691a60e86"))
    (926720, uint256S("36b2a47acbbd97598a5bb4aa0836fcbe68c2d5f68fbe62f376bddd79f916ba6f"))
    (938161, uint256S("7f99039cb062b1e636784083827b6d64cc12b70af97ae6ee3cf2d2adb0e5f277"))
    (949602, uint256S("d2718c51278f7f991d7dd69db9220fed1dc0863ab6b41accdea473b864c80108"))
    (961043, uint256S("28b2552cb1cc52d2dfc5f558e8882670cedf8d4c43fded7e043fcbdc1110a41a"))
    (972484, uint256S("73c6cffc99af75e6776b4a7173915244c932a35fa215e36ad50cd72bdf6e2e82"))
    (983925, uint256S("0895a5fd5b57e9c54f2b77104d1243f9be05555eb0a089303581ac6121a2fdb0"))
    (995366, uint256S("eb6d35ed3347ea857a4a652f3e84cc95ae74517adc87ab5d0153c131136cf52e"))
    (1006807, uint256S("576d8a08ac7a3bcfdc0c17e391c4c0674bc0b3b3205ba995b01a8dbba1bcced9"))
    (1018248, uint256S("e690d79663d24014ab855b03b86d235a9f97b141962cd2f530114ebbc3bc8c3b"))
    (1029689, uint256S("55aa363d55932fddfb6298ff0d156e616bae522ea01b869ed3bd21f4b1711eb4"))
    (1041130, uint256S("f359d83ecf5d76ab817255d38ec997f975937da67c53d5d307ed4500fb904d69"))
    (1052571, uint256S("d98834c4e9c1d8d9b322a900fafc92563e7c92f2578ee9407592dd3854bdeb85"))
    (1064012, uint256S("7d0ab35a0db1fee030b4857c388493da4a6511ffbba310da7d64d6450d04ce0b"))
    (1075453, uint256S("cdd301257b034c5de214584d131e1677d7590d71aaa5c107f0a8b953471ef6ad"))
    (1086894, uint256S("4608090939ff1a626f1d16554dc0f5e909d807409a5ebc6c25b63bc045d71b51"))
    (1098335, uint256S("e35b19668d2698603ab0a0cb4c3aeaec666449a96089091e4a64f75b84d9115e"))
    (1109776, uint256S("4c0b7bac1e71373c7176704ad0354dd8ff75b36e0c0ec464a25a230dd13b27d9"))
    (1121217, uint256S("fe796d57ccc4fba2c074d458783bb3783a8873471fd7fdd8329090e7bc4a3634"))
    (1132658, uint256S("2e793c7ef0be88ba9035f7e364dde811926039d5729d4cb4825861c7d3ac902d"))
    (1144099, uint256S("44864c7a56280188ad4cc287201fb0273acfbef2e92479f1821b7adddba72113"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692890970, // * UNIX timestamp of last checkpoint block
    2544490,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2824        // * estimated number of transactions per day after checkpoint
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

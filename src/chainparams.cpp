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
    (20322, uint256S("53c670b3927ecd566f005589344cffeb3ed61e785994d228ae11e146c7fbbf40"))
    (40645, uint256S("6ca3d452234cf9a25a37f8d3d86631a126097a76122c2d43014d59120f409953"))
    (60968, uint256S("4fa565f74306e0616980c0bb1baca19a0070e0460f58356eed1a29d58834e6c7"))
    (81291, uint256S("6e5667acd0ae9f921b54b0942bb082052fe0aef25e5cc978048241badb843f0c"))
    (101614, uint256S("8fdffe3171696639c8b5fd0ebed79cd065e36f93fcb7ded62260a71a4e2778b3"))
    (121937, uint256S("b37ad38676e809cdcdb9bbad84148e66c20c44337d07592182b970ed64c1aa00"))
    (142260, uint256S("f4075eb573d5252982780f5bbf35eaea19b12bb588d9372ded2b22dfe884c01e"))
    (162583, uint256S("3fa18d4cf3124c02bc5ed09f79e05c7436dc186181a3d13e6903aed9802a1bed"))
    (182906, uint256S("db91085b6f5750fd2d7763586ac8d44e344a52426f0c75a97f61c0dad46ef2bf"))
    (203229, uint256S("1187f82f0a542e99867db80f6452408f1747f8ce53e84a1c169d7d26ad02ee9f"))
    (223552, uint256S("2fde3c25c6032b83ed8893942ac58c2bfec4d5703713408c2789b6e4c5182ca7"))
    (243875, uint256S("d085dc21e3a8fb69ae41a5ffaa9125191891fc64bbd7624298c960e0cef78736"))
    (264198, uint256S("14895ff69df5b9b51371a7e74b7b64184d339ccd3f4291692e216b64de570adc"))
    (284521, uint256S("e60e4d90cced0f7d0572740aa7653a96370a06341fd695d6fb601d55b14dab2b"))
    (304844, uint256S("922dac364137b440240443f2f6865aac1beff042aa24156917a0b4c12458da06"))
    (325167, uint256S("9cb853fa4094e773d873c2f528efd499aec3d32facb56ed9c42822d9066ae254"))
    (345490, uint256S("07a1f0eb40e11c38f93e537bc134be499ca73df51477f566f41c49eb42260aea"))
    (365813, uint256S("a56a3735683f7d5a89f675b9b07718dbb3dd55656cd9d18584955b84c6a2e46b"))
    (386136, uint256S("aa4b351062e66db34a52076fd89829c9350e81bbe15035899d95f0b11695caa0"))
    (406459, uint256S("b3fb1781c3d74b52faa7ac5c6b4b6c406b0995a7c323c0cc9c9dd2e6207cdbce"))
    (426782, uint256S("f0030657b432e26bca91e43cc6f1054ee707dea87d4a59e319ee7f54468ac4ff"))
    (447105, uint256S("0e85fcb3ed148599387094118ea9c086505ea5c6d35b7ac8245a2256a17cf28d"))
    (467428, uint256S("9f46c58bac482f57586e36f9f5a53f87f1500990fe08d4b2a532eba81b13ffe7"))
    (487751, uint256S("6ea2d39eb60f00a1bfc114c38e6367b8d27ab77f871e34309303c905f238b4c6"))
    (508074, uint256S("357a1f515318939f5e0f6b0dda9c0a31be29e571a64328c01566d0f2f44f1b1e"))
    (528397, uint256S("84c18a440b1ecc73de41fc32bbfa34fe3f6eece4c8035f5d04bca42f4708b78f"))
    (548720, uint256S("fdeaff86c803594400d3cad5fc4a959fa2af2e3557d8cfdf896e29fecfa22c2d"))
    (569043, uint256S("412cd12de10d0963a4da00708453d7b759f52848b3b61b4c04e74c730bd4e1f9"))
    (589366, uint256S("264f051c1d4f79f47afe7c0fc48f702637a7dcf81513788775f707e47e948369"))
    (609689, uint256S("226b0938adbd8e2ae48c92ea3562e22061c6673759559af24a3280f8583fe425"))
    (630012, uint256S("e3988aefe3ff40a419b39741c4bb1aba7980b3ac654d4d06219dae53deb9b0fd"))
    (650335, uint256S("b983e958326f002b7cf5b9129dcf3033e784460a7fa54ff6534d77e0080a514e"))
    (670658, uint256S("6655abaef8804da36da66a7cd5fd74e05cbd3bf90faeeae57ec59e355bc651cd"))
    (690981, uint256S("3bc1d2955a4cd13f69d276645c3dee2b9597db1de05f2d0c4baf337ccbd725d5"))
    (711304, uint256S("9362cc8558e2f3ff36173bdf7416bfca995b36b0a4f1988b6550b361901a9f99"))
    (731627, uint256S("106498330e458b2d6d239a4aad9667abcda4f2eda8726c40143a580751748ff6"))
    (751950, uint256S("537057d44e96f0e9ec0c8756f05d33b047630744725dab9882bb45da1e43dd75"))
    (772273, uint256S("8f82bc38ec85913acb847137c6910119cd6eccc31e4345f1d5877ad1c0c02e6d"))
    (792596, uint256S("00421209cfe4eb6283b322c404ed3754ac070fb07d2bc576d77035a67c84b6ef"))
    (812919, uint256S("1e128ff83cdee782d8e9cedd775f449b786506d3bd6665b2882fc2bc6e7a0e7f"))
    (833242, uint256S("6564495a99654ffad9c19342378f8263e478749ebe5cda189b1ac7e24d493a94"))
    (853565, uint256S("23e9009d9f645451a6980d5a213e79f88ac173f001f922b990bbfd4771a6bcd5"))
    (873888, uint256S("7d647e58b6fe707c067005ae1818ddb2abf219da8d8182aaccd7705f5863c5dd"))
    (894211, uint256S("40ad09e7a023161a44ed974c7acd5098461c4cb35f42ee65f4c23f842f448116"))
    (914534, uint256S("4d7439cfd160423d66a0b7b886ad32db06d4787477da17b8c58f58b6c1674507"))
    (934857, uint256S("29dd7cfbe2235c85d4fdaf601217736ac941f40a3f1c8c4ce75b2cc900554b7f"))
    (955180, uint256S("07ba7874fba520db0f5a9f0c8166339c8c6c3f6b91cd0ec7d08e684a0371d7de"))
    (975503, uint256S("6a86ee167f59a51a8c8a1c6a76781bbd6d6be251ca3f878ab2735c903670c7ac"))
    (995826, uint256S("862cbc6a69bca6433e966cef3931a721543fa7e99bf70bfa69f64aa648506694"))
    (1016149, uint256S("a6613aa7459a9b234920eaa7a265a58d3cf0e0b10145e6872390558d1032d818"))
    (1036472, uint256S("56109e3ae65d7fe4be7d2bc68ffe098afdfb2069be354e30d6bbd7960eb12cac"))
    (1056795, uint256S("9916ad9f2d2ad9d584b919594ea504c4ed16f455c7b9dadfecb95a52da1cb97f"))
    (1077118, uint256S("8a868740069485d70e812b175ee7074dba59e39e2825c3ae29c31c565b33e442"))
    (1097441, uint256S("78871835aebf064765ec045d312c566c9280431fc53afc5c968cf97498d9d1c7"))
    (1117764, uint256S("f1714ae88e86ec4a0dfe07f2dad55e8af6f5dc2564d4c52809eb1b38a31434c1"))
    (1138087, uint256S("235fbea7fd7a31af64151624ca900906a94f1d37a67381e2c94f2fd7eb039c0b"))
    (1158410, uint256S("7478b75e58d4dc8c70667b5f5b0a6460dc6753c75de67fb5e1bb91575003af24"))
    (1178733, uint256S("31e824bb880e36f2d461473810706d7dac1d0097b45e6a04936b400748ff8367"))
    (1199056, uint256S("4c9b365fed2d2667a1d7c8b21ff65c01f169d96d4d57ab8590caf7453f63c79d"))
    (1219379, uint256S("83521b7054b48b67af1c88c93ae58afbfe1ab85a7f3963372ccf2cbbefae28d7"))
    (1239702, uint256S("e583bd13b01ae27f4eb925f418f9a89ff024e139392017c5282504c1698e3b8d"))
    (1260025, uint256S("539edd649861d7085d79c524ef8438411bc9da08289698c9f17926dd12f88ee9"))
    (1280348, uint256S("8f6a661cf29571cbbcbcce3183195440d689504f128bfc88a9c7e52ae9daa4f0"))
    (1300671, uint256S("34b021e40ca5f4e270bf041a62ba54dc22968d32c0b7dbeff760a4dcd1a4fd38"))
    (1320994, uint256S("44bd5fe1b5be28d803c0cc37b04a4623ad698abde1b3597133a77905d469a24c"))
    (1341317, uint256S("34597bbf9a82b5e13cbb94f729619f756c0ed563307c56f4bdc7538c701e4fde"))
    (1361640, uint256S("58e4b59d6a24e69a3baf2d888ee48e6790c74001ef3eeb3be877a15a8fb9d982"))
    (1381963, uint256S("8b20548fffca83ab8e23d866ec799af222cc6058ce642abaadbf19bf57d44e75"))
    (1402286, uint256S("66ab7b514d60b1a7ff890a5d82f124a97ce272838d766275b1fb0b68fc9ae163"))
    (1422609, uint256S("b4a5794a95e35845c132223b6a70ed381cca467566fad0d4d3d8d32dd179efee"))
    (1442932, uint256S("694a193a7da43b51be2d8092409db2b7021d355c10e810a9b89f23de533ed210"))
    (1463255, uint256S("ce6ffd69b7452fc76fd9d96fca486eb4825f50974e6349a876a4b10351bde3a6"))
    (1483578, uint256S("8fc9114d76a158a483b665edad42f547b81ee031a321e04cdfd695a74c28e774"))
    (1503901, uint256S("dbb9fa45950986ddac9e4be9e4d3c720a13f3db1a23beff8e936a69b4b0a4fff"))
    (1524224, uint256S("47295e00161f36f4be03c842d39803f104f03601e5eb8d11777e2df70e25e401"))
    (1544547, uint256S("e2ec8516db3293c0203bb3785db419086a34efebb0ceff39691fceddf884c757"))
    (1564870, uint256S("c6576209b527f427f5aa6a79abcf6635d8f87ed54b71559be2c16e057865f60f"))
    (1585193, uint256S("41c9b2ee4b3df0d648f7890bc36f397c8f3aca64d7f794c51abaa04f5ee45491"))
    (1605516, uint256S("1946f10d33dc6a7e299fced22709ad4ffd078ef67c29cb53df5147baaea211c5"))
    (1625839, uint256S("a6a6a3a79ecf591b89135d7598f9941be69d1e7640e54d5ba5e8f036605ada5e"))
    (1646162, uint256S("fa3a9a828afff39299b9a831d90c9201ace9c4c6b0903e95f708ba845aab325c"))
    (1666485, uint256S("ae1d4d808d027d310658b949566b75c56ab1405c068c04df0500c86f8f08e676"))
    (1686808, uint256S("2926f290c3e07a7ba1d561fb0ed186d9d42e9fc64146427c7b2cf620c25f9ffb"))
    (1707131, uint256S("b3e415d8af8bae06a817f465fb25fe56357a6a33fa32407ab2eec9cdee42e957"))
    (1727454, uint256S("88b3638d791a6df786885187207f3ee4c5ca83aaea302900b2a03061977d79b4"))
    (1747777, uint256S("572153d3d15577bd841e29728d9d5a4f8f746efd55b56d1ea80d5b82c789b79c"))
    (1768100, uint256S("8b2a2e3fc35c857c5848aa044b73e9a8bf6dbaf0363b21704f5663602ec56c2d"))
    (1788423, uint256S("1be8673ff94e9f5f6af00a6fa7c13b5ce0d67d1027a446053441d5b9728fd95a"))
    (1808746, uint256S("414118ad38239866ff4b5d3cef104015d3a9199e5e49aafbf3c6a09dcb7270f8"))
    (1829069, uint256S("830afd39d697e71f79d7bae6928fc376b6a81c9cdf515c6f18d74de4213da279"))
    (1849392, uint256S("6fe9c36241e6c3a70fb0fed7ec852579bca2e1fb7eaa9832b735cc2f53f0a6df"))
    (1869715, uint256S("ad4b6ff26c771ba934d5e0687bef1fc291a870756b5e6ff3ada77de2965bb18c"))
    (1890038, uint256S("fca0e05096a6f6f139ed5f57bf701e7d9f89d37c122ed0300c175713ff795a5f"))
    (1910361, uint256S("0f8ebef0c5939de34727c7cecdf35453f6a4ae26639c9bce0e8d57a28a6400aa"))
    (1930684, uint256S("e51e364b95e80d21d5da3f7bf0aa4f6ff9ea858ae8da5722f9e8aecd1c312b3d"))
    (1951007, uint256S("d250c0deb336ea002f0cf46f955742c4547cbfbae609689440b33a85ce9e53fa"))
    (1971330, uint256S("55bb706d2eb0f654238fe19a7a07df4406d12109283d78bb3a843cd680954b33"))
    (1991653, uint256S("b3fb754d655935a2a39ddca2e3ae34a761ce26508981498bdcd25ba0e3b222a5"))
    (2011976, uint256S("ddf8dcad4dfe3fe0fbf6a004b505204bd4b3d7bb6a591e46c64d3654d3cfb914"))
    (2032299, uint256S("0f2846bc42ed22ce465e4b53cf7a22f0f87c2c342222b07ff822d6adb3d42767"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1687137315, // * UNIX timestamp of last checkpoint block
    4724866,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint
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

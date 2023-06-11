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
    const char* pszTimestamp = "China to socially blacklist Bitcoin miners in Inner Mongolia region. COINTELEGRAPH, 2021/05/26";
    const CScript genesisOutputScript = CScript() << ParseHex("04cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda03241a96752373dd49edef35f384368993d65afab7214bb870bd95be32606c477b7c") << OP_CHECKSIG;
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
    (0, uint256S("00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"))
    (10484, uint256S("7c0fa755fbc5f25a1e9974b96cf5412f0c8d910af6a201e80ba4be544ec55b4f"))
    (20969, uint256S("8bc984508e84c47ad16951a5250cc19bc51397620082c8193c597ba1dc34ebb2"))
    (31454, uint256S("eb902250b54bb45fbbb6933cc7ddfd9cf89d7525fcfd11d433340b095339ecaa"))
    (41939, uint256S("94627c9229cf39e45de76254b3f34dbfa05732f97aed8d094b25a1b842546e66"))
    (52424, uint256S("960cb0d21504a71cf95351bb3be6b5ad4dad90d4c33c2185eb2d1cbb93b66130"))
    (62909, uint256S("0ea011164f9a01f20ce4771e4bce1a0fa95c245770ba6032c2b48a6e05a133f1"))
    (73394, uint256S("0fd2013e5ae5d99f3841d453521d0b86dc4aa9e9c4dc8b6aa7e7def57f47c029"))
    (83879, uint256S("61aee01b9d7b68cd67bcc1c8d432d0d8746c21a8a807a08bf1c88e9f2d0a531b"))
    (94364, uint256S("0b9e763ff6248aa278f74b74d91e7c82e6a67ec31887f6e81d9862231c8f1c4c"))
    (104849, uint256S("a18712b22deb6d77205db2a29cec28172f38c85c586d20131d3ae34d2ad30966"))
    (115334, uint256S("c162d13694ca3b6133478604b1b266dae15de988fb3505ccc53bd3d97fd8192d"))
    (125819, uint256S("122ddb79fa62f94c70d4e6829923a2e3d9a994ff021e8fbeef09875d537296ef"))
    (136304, uint256S("1b19d31aaccfda3ac0406771e43364e669131444d851b5af26765a905d65b1fe"))
    (146789, uint256S("4fb9f44c0ee96b02c6c949bee7ea02c9069daebbe42ca0ef852538ea3b475026"))
    (157274, uint256S("7c4bdc8bb9898c2f16ec28fd2c9897efdf04416eea223d870287f9920b2da833"))
    (167759, uint256S("b1b134b3ed1e6a5af7b8eb31ff6522a74324e885c415d8f082248fd6cf38e8e1"))
    (178244, uint256S("44419552e9e3515abcf91969e01da92eb9aebe4ccf6e69ded3d5f0935c4705aa"))
    (188729, uint256S("67620301390e2bd4bc783a2155f5d8dc4a24ab3d510c3069ee0273cf5d4aa072"))
    (199214, uint256S("53bba13584c03b48778a00d0b0a267c5c13190a99ad4f16c5bd0fd19559574f7"))
    (209699, uint256S("d8be9c0e54a004c586e450a4249f5f476c772be831b1a4597e8b662f824d1aa6"))
    (220184, uint256S("c45559a6e9c24aacf494e564be4fc2bc21c6cd43d858e587e44269e8e5176ead"))
    (230669, uint256S("b0c199ab107d0f0b7cd343b83e537112dcdc37c5e8fb2a207c72b080e02cc78a"))
    (241154, uint256S("3bc240206b4d114f59ff89fa88f1e66b83cc7a4e7d3ac23ecdf2d4d4e16aaa4f"))
    (251639, uint256S("ba8311d6ee84243763341e93dabed560edb8a35470773ab36f84019a4cc2e207"))
    (262124, uint256S("e842a334493e7d152e70fe6f7fbab0d3bec39ffe5d4c38d1c764110a7042f59d"))
    (272609, uint256S("cc6d7b1ac0b089fae648cc4f71bdee7ff14599a7154e87d03abb245fd20d91c8"))
    (283094, uint256S("bdb52db4c2cb63657aba50708e10acdd0ffda38b602555c393caf7e90688a761"))
    (293579, uint256S("477011e8c926f3c785f3c5d3b7ff2ad5b6e28a0ddb960062d0e69d4afeb794bd"))
    (304064, uint256S("660c6f03164c1d1199a455373c9ef61d897f6c1c8f1f76e3faf5c40d1f98005a"))
    (314549, uint256S("c7477b32f1998f223d6534062b9ad28008b9299dde5248b99c79824a404856dd"))
    (325034, uint256S("b3daf93d4e397676e35f820442ced3aeef6756a5373a05b09eb095d4d250e755"))
    (335519, uint256S("23a29492218dacb6cb6e93961c1185beab295abd0df036c701ca7ed3d305bf7f"))
    (346004, uint256S("762070c9b600cde7aab14f1d333109ea1d6831f1ae9bd947454a1d8f61a55c64"))
    (356489, uint256S("58a1248cc4830de73bc444dc1f8fcd40461a665198ee9072b98710b051e5ea73"))
    (366974, uint256S("c779f748cea83908a4aa97abd9eef1dd504f5ae443b0955bb55b775f2aabb853"))
    (377459, uint256S("9e9fddd23b25aa0d0874a47e618b41396d84a8564d9d303f7290adbb18d0e179"))
    (387944, uint256S("4a6713850bc4a7ad18f496aaf84258d95a176e1ae625c0cc64d16125888dbf69"))
    (398429, uint256S("1b2043994c46cdd2c82a25d64718aab2316cb37ba0d8e0146447d0f7c7be4e2e"))
    (408914, uint256S("4e9bc2688c62196f4cbe2e513f43717fa63f49aaf445c1f8004a9494a27908ea"))
    (419399, uint256S("7b0275d7d055e5a72e76889e40a5a0402b8b162ac6704879e62010ea6d7e2784"))
    (429884, uint256S("1632bdb5843ccfcd58021858611c5c134f70f085d5321c4a8860dae447639ba0"))
    (440369, uint256S("7195ce3502c424b2cb8fe3a0adccf6d14d95c5faba7381e10a858012ba69d86c"))
    (450854, uint256S("8f7c62e53bc46d60ebb8890543238e9ef3d2987724c135a656f0758d5945ab4f"))
    (461339, uint256S("f37fd262f116b3e95b0a717494aad4a4668a74fe3deb055b423848e9a5df1c24"))
    (471824, uint256S("a28752898728d46b3b9f19f6f32160da05cfc8597930c026b952284bb78000be"))
    (482309, uint256S("b1fe64985634fc043946cbbe7bfe2a25abb833dc28af5007e8aff468623ededb"))
    (492794, uint256S("8683e1f62038e054990cd5c316b7a475a4e54190f014f3cc8311f38e6cb29cc7"))
    (503279, uint256S("03fd001bd9f7e3ad1d3d4c63b2151b6b2db68924340a6d75fd4d83327f5f9eae"))
    (513764, uint256S("a49301a3065c55501b2e4e140f16a93a5bca42f17d18fa00487c90885af28f56"))
    (524249, uint256S("597799351781db42f7d3b74059c212154d4477b7d59697b46e04007a69509d27"))
    (534734, uint256S("1eb11fcc276f33cd60a55871aadbf0adf247d6339cef1665169e1f153f93b6b7"))
    (545219, uint256S("3a68e06228b584c4e616c95e02e2cfc150abe9db7eb4875ad666e5c1d69dfb7c"))
    (555704, uint256S("8f42354d7800c4d4cc9032a2e8bc16114026acc3eb31148657930097351c64fc"))
    (566189, uint256S("a4e05a7926e6862e6c6b9418ecf03e27ad632cbf2e4a58cec761906a3bd0e201"))
    (576674, uint256S("3956a44616aa9e560430111ba7a08d8bb9d9b88bbb83b45eccee46fce1bb9353"))
    (587159, uint256S("5a768620f6e3fa48567c3efe9827bc21be9f8925a0f908bcc6d0674a062f4631"))
    (597644, uint256S("e69624d960fba758d8a7954838cb6857e64ba8a55c613af4ab65c6b1798ae5c5"))
    (608129, uint256S("f8d9a4cf0b05c161a822d79c5d3c315f130c4af9b851b308ea37aea935ea7dbf"))
    (618614, uint256S("70f7e7dc5b923e39b2f1ac001d71c8791936d8f01d75aca9295d839836729a1f"))
    (629099, uint256S("2daefd4b9e6bedf2eb277b4cd0151b54efe0c84cd8153c8b9cdb2479f115a465"))
    (639584, uint256S("79047bdf6c12000ea8ab3f4095d4fa3d28d0e9ed011b66a64e1d01fea531ae24"))
    (650069, uint256S("183298826a9f9c86bbc730a60aa445f3fe65c2ce7aebd79dbcaa5133251050bd"))
    (660554, uint256S("653193bde7a4ae35e8c561eb55f0a90f677234dc9f05634df08605162fabbdee"))
    (671039, uint256S("77ffc9f53be16c9850f66ae4a4c575c6c1f5ab20e78c7a3528e677d6a01eac6f"))
    (681524, uint256S("9a67e402a74b8388ed8d4ea131153ce61af02c5a8d511e975a1bc6a5ca5aa304"))
    (692009, uint256S("07080833c86319f2d92bfbddb59eeff6016c459bf084c7a51f6b914fcd0fe998"))
    (702494, uint256S("0682e597d5f8a2997907a10cd5df411723bd6e316dad158c4a2c0a6c639befc3"))
    (712979, uint256S("c965887cf3a205dfdbec04afd2adeb030f469d4b2eb92475db6f1840f436c699"))
    (723464, uint256S("34c90e8cfab9e3aca5266cc23752875e34f285eac105713dba2608ae72828469"))
    (733949, uint256S("51a8f6c372baddfa8da68566f741e8eab13b870219b92589ff4ddc296ae89a88"))
    (744434, uint256S("6e6b0fc799a79732ab88f057aeaed841210dd3e4d32ab594e1b46bbac39e68fc"))
    (754919, uint256S("8d8f4cc9542d5f908b09a9630df0418773d95d844335700e3cddd620e9581666"))
    (765404, uint256S("d5795448383a33672a3bbdc3b080ff3f870e45716a5621164f25273c859181f3"))
    (775889, uint256S("c33301c0cf41c686893d06f5cba9b2b8584b20c8021c24d357a8d221322067ea"))
    (786374, uint256S("44d5e346434312b9dbb1768fa37f1132b04caf67bddd360e5bfb3798e4485d33"))
    (796859, uint256S("d648df0a70213e886a048ef6f0b5e1a3052b2464d162e1cff1eac00de435806d"))
    (807344, uint256S("4ae4fbf3e472f438394a3e4a2d9f2fe7e871312b7dd0e57ca585ff1570d56ef8"))
    (817829, uint256S("33d5cb3862bf69a00ecc41ef46ee1ef9528587e44680592808235fd665c4f84c"))
    (828314, uint256S("68e01c13b38ed99d9f689d9968e410f5ddd253bb70a79e7ae3e1f9b960f5ed60"))
    (838799, uint256S("a13a133108f77e7154f85297f30f9c32b54b26e62afb0754c3169d3e0a381268"))
    (849284, uint256S("dd0e795b6056bb3a8944dc91c07753ed2f09e770f3cc1708607d9b00a4a1a8c6"))
    (859769, uint256S("8420ad1816540d74f985477d8bb7a7cf704c67fb3814f20b4b4aeba98a968bff"))
    (870254, uint256S("b099c65f4c154f934abe9c7875561b767f9432b1ed735337482455e42a26e295"))
    (880739, uint256S("5e729354e2b70d8b8e4171b2768dbb277eab653c878f2fbb49ec1c18ddde5c06"))
    (891224, uint256S("46761d07731a39080e14fe8e066d039903d8161352dbfb1de8143735576159b3"))
    (901709, uint256S("6f38a5036803a42e402ac3156a694681375123affad039c6482e33f6b8436dc1"))
    (912194, uint256S("c3b02c61ed5d0387f5c99299cd07b7081b2b7093008e46b6a78dcb5f4f0d5db1"))
    (922679, uint256S("0354d2050fb759e3e61b4c92c257a6ba81ae2cc85892ff8b3dcb558764040b41"))
    (933164, uint256S("fea85fa78440695b7f4d904700e73bd6cdc072b191eb11a1dbe2a7e03ec4eff7"))
    (943649, uint256S("012a67e7926877ea3764c332d719c05c0b84e19520537095221cd6b4b58f2533"))
    (954134, uint256S("145867b64cf2f719a2d7e329824d17da124e6fcb299c8d190a6d951ed8dcdcae"))
    (964619, uint256S("e5ed67d6d69062223a28ca49da3b93623b5b5565aed673c4e4cc804a2c20dc10"))
    (975104, uint256S("dbe1e75880197b38cb6a7aa5093e388a7fc3424a7f17e0505ab2532f850492ba"))
    (985589, uint256S("4ae79fd8a120cedb74c15766eec3e4301ad867a78c3dcc824722a3930bece052"))
    (996074, uint256S("0c33d6291941e6e32a34aa4874751c3b4f129ea5bf2908195c8af55092847850"))
    (1006559, uint256S("4b65810f43acdae54c136373b020987c487f2cc7cd9708697882a11a975865f0"))
    (1017044, uint256S("fb24bb83286c8212e61bde9f33a6761026baf1d9e75c841b1913e4eda2fc07d1"))
    (1027529, uint256S("ada263cced7d81a1e1d0b976da0055b9b7e45ff7379bbe63e669670346260e42"))
    (1038014, uint256S("6eb0b20810d6114240a610d972bfdd2c8d176f59839bd199edb09a55f19ba620"))
    (1048499, uint256S("b2db2084b7e196ba63a60150836b4cd307c956d8c5fdca801fc166fcca3db6be"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686521865, // * UNIX timestamp of last checkpoint block
    2270668,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2832        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1622058209, 1716299, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"));
        assert(genesis.hashMerkleRoot == uint256S("0xb81fed5916d638ae849e84e71bb0a920fa6858a0b83cbd596e6ef13c458c84b1"));

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
        consensus.strSporkPubKey = "02cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda0324";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "sXXXXXXXXXXXXXXXXXXXXXXXXXXXVpr7nX", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 80000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("59ea521b46edf374093a44c5e8bf88fe3db211aa9fe63dad1c065692047f6db8");
	    consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6ca0d4ee6fd87d7deb8a3f31eb57dc52588aad8c75766f6449135182f1b472b0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0f2a78cae02903adaee9b7e43a91b86725980e9ef3bb49303a722a48bf9a32f6");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("a70f1ced0cda9854854bda729aa9c93e5867fd583158f033fb16b50daa258a71");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3142c02979abdf5e8e8f6d0f5d68e04caee93fe720d401a806e5e074e50ed5c6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("be026155f0d3fce0b28ba5e0153555b34fe850beb0244803e27c64dd895a8938");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf6;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xec;
        pchMessageStart[3] = 0x78;
        nDefaultPort = PORT_MAINNET;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptosaga.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 142);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4B).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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
        nDefaultPort = PORT_TESTNET;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptosaga.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptosaga addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptosaga script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptosaga BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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
        nDefaultPort = PORT_REGTEST;

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

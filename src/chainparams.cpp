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
    const char* pszTimestamp = "Is Bitcoin a Good Investment: Analyst Predicts High Institutional Demand Post Covid-19";
    const CScript genesisOutputScript = CScript() << ParseHex("04b3fa9f648a6b1f477db94dc72db5df018b5539f081fa32258d6c7ba47a6b47b48187909c1fa62b2087d9e17e115fbfb20b042ff7c9c34f35c5d17f76c458e7f4") << OP_CHECKSIG;
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
    (0, uint256S("000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"))
    (10303, uint256S("461cbbef6b9abe53eaa8866865fa9f1efd198223794c406b48df86498819587a"))
    (20607, uint256S("3340cefc8717f79398b4e51864ff8ba1536db1a97e6d8aa5d62e69c8abc8aa08"))
    (30911, uint256S("60df0cee91c35ea2f42adfa3090385db3f2629b787b735788927429334ff853d"))
    (41215, uint256S("0e7e70de739fc2612f513e5f48b7a0728f71e28da321d3053ac08463b05dafcf"))
    (51519, uint256S("41fb00e1a63d928f478add0323877ed97289a37a5e74e653902ef45a4f8284aa"))
    (61823, uint256S("2085472d7a6bacce42a3cc8ab7c1a9379368a41a1c448fda8400a266616b94ba"))
    (72127, uint256S("c08f0e03cccdb3dd71e23fc11d32ce0e71a8e6c5e3a6e8ae1e4c5e6b92a8a528"))
    (82431, uint256S("25cb05c528cae297aa91f010a45d57961b1103fb2c8c27f2561139567dac9b45"))
    (92735, uint256S("d5b1ceab87241ec4a95fbf6703172ddcb1a1296e9c5de01e8c8c756a65754535"))
    (103039, uint256S("214254cbf58f3567629ecd2a15d7f864a4a0849a041a10e45bbb8c15850bf4ab"))
    (113343, uint256S("d86a8aa4ea55727d272ff83721f9525738fd03f1d8e2453129691704ad648ab2"))
    (123647, uint256S("ac3315e51082251c780592a741bdebca186f87a7c23f17f5711a6daac7095414"))
    (133951, uint256S("cae1a8c1bcd2be2e1ae5284c655a00c140dfaa1c57290e05f264b4e5c40f517a"))
    (144255, uint256S("4449895dadc0541040f0d64a54346ae6c6ac8c7cdf282132e13da29849932240"))
    (154559, uint256S("30596c7ab9498bb2c220012e22d6fee02ed385be8828173f7d3ebfaf2ff4a468"))
    (164863, uint256S("80d1ac61f91d0c3eecc7e45ffeaea3238c164b3876b978da99bfa790763df790"))
    (175167, uint256S("389d5aa940c13608ae52205eef589ff857d7fdddf965c26862456818041e9d01"))
    (185471, uint256S("fa396fafc75bba187021e35aad45db8a7ab571d07c2269a8ed7608cc79962091"))
    (195775, uint256S("225dec81259e1fd030f07ea977dc1df20566e40fe2c20550c086beced024e11e"))
    (206079, uint256S("3803c79b6e9f17c36fdeb48753b0f93de20b3adc761445e9747184ee603138ba"))
    (216383, uint256S("e9d05b2d577e0b221069762d2a305d98b6d7234a36a9095a9e84e3cb58ea89a9"))
    (226687, uint256S("11410a477dad686e36f66ed61a831094c28d0b7bb61b6c9e49f4077c5200d086"))
    (236991, uint256S("9b398e4a1faa62bed1ab9b87bbfaf7b950f82859cdca1caf3d48d8af28a94ec7"))
    (247295, uint256S("f71d81647c26d8797977c796a537d409d3b9bdcec7da92ce846a0ec6d85dcee5"))
    (257599, uint256S("abeabe25cc89957cfe2f8d43d766a53660dcb3208eccc046cdd99cafa3bffe9b"))
    (267903, uint256S("b098a99f63440bbf61473100ad9f202facb788362ec7980cb147f4de3806b450"))
    (278207, uint256S("a2aeaf8afdb88efe406900beff7b6a26837692f312867013ed6ba95ce114c94a"))
    (288511, uint256S("33dce675646c8ef87d57e953459ef48ba86b0b892c740b89ad3ef979bcc5fa94"))
    (298815, uint256S("9180924d26fc1ffadfaa8cbe12474cb30cca7c60305d93d736418e660549de09"))
    (309119, uint256S("d8cd26292b83b04a19107b5f432b5149d397f1691798ed525a6b63cf858f1a16"))
    (319423, uint256S("1e88ef0881307a386d83566e2dcdffd51c774f145839d5e8c4785053a2d2c866"))
    (329727, uint256S("1b59d2673b27a74856cd3a861e8ba47cac3f03a344178da7255213c64950407b"))
    (340031, uint256S("73bd65d08b777ded07d819e9d71437574dc7648b253895baae98abbd6c09135a"))
    (350335, uint256S("0c6f8740321a92a88afa4448fffcb5ee924db5e336d7e69b7e95453b19bc56ba"))
    (360639, uint256S("eac4017bfee4d8f8eb725e4b0965b9051dce9e52ec8d300b5118634f197933ce"))
    (370943, uint256S("c274d057c3565fb6a0bfb79eb1ba2aba69ef4973b9ec2b57f2ea1c758d718525"))
    (381247, uint256S("bbf99da1dbf593de294a744072016ed82c2f184435b1cc3957e8bcfbe7d7023a"))
    (391551, uint256S("fbd2cd893f9b7a930434159c177c816a6eff2a27535e27029a1deb1e1b72b60a"))
    (401855, uint256S("fcf96b2299ea199659abab092c501d749ce928d9296119d55eb055047cde7822"))
    (412159, uint256S("c28d93810839d202a1c71d7150a2638605d8ebd049543d6f9e1e4ae91df7923a"))
    (422463, uint256S("71b75f0a9a19a899fad644d553263c27a0c06a400ce1bddfb67cdada09af1d20"))
    (432767, uint256S("8f2114531f14be1bc975aa7968c776ceeb0f9cff68457bc14046e3815c906dfe"))
    (443071, uint256S("f56b7928673e74729b09cf5c33464102755a8ffa770c9df38d26bc8d49adccd7"))
    (453375, uint256S("867d6731a1aae755531d0de940fe4d3c384b6720835079efe4bb7aa23db22456"))
    (463679, uint256S("7faa0f7604216338cb3fe379d074d7fb4cdf6b6a41a73390d9601774297ba224"))
    (473983, uint256S("37ea3092775cd9c713764d12e7da644f84407eda920c0df5fc6f17808b4135b4"))
    (484287, uint256S("6683a860b3ef2beb2aaf40de0d4b0d0696e7271b3a7fccc0f3286ad4953e4cb6"))
    (494591, uint256S("deb2dc771c5bb690fa145c8623f40b9c1c25be1892e3860ee3e9c008460f7096"))
    (504895, uint256S("b2148ceb934952d23502e2f9d0dfd911777df200a0ad52bfdb4202dc64fba461"))
    (515199, uint256S("686d9776e1680384a406f178a766ef073c5eb828f4357014d465b748e26a83d2"))
    (525503, uint256S("fac4133bf877a2b20fa8b58ec66a93c60141c7079fc019fe0c24a07df7ebcf1c"))
    (535807, uint256S("888de566b7e093014b8be121684eb745a56513e7bcc23f2afad70974a44c6f39"))
    (546111, uint256S("26f40c07f73666c4044d12b82cdd1028897a156eb55cbd885c8f28447de79e97"))
    (556415, uint256S("6b9d760f9fd88d170315eb02623f334e148d5f2e71865e2239b85491e59c05b9"))
    (566719, uint256S("b618d3f25bb0f0e31aa8d7feb9ec8ae70f91c337dbd8be39e5e6b11c71ec11bf"))
    (577023, uint256S("bcd9829410fce70fbe0d35675b97551e9531f6312a00e5147894ffae7f63900a"))
    (587327, uint256S("6b51cd74bfe0a9fe994e16a766f7770c7bc6fb8b74a1a2e7fdc37bd64f96bf7c"))
    (597631, uint256S("1dc38c900daf6d72a41696bcf1a36be8567e5f19c1fda456f1c1ac332db9827e"))
    (607935, uint256S("afbfb55fa50cd44b11f7c8a1385c49c9cea3326758303bed58d0a67d391cceb7"))
    (618239, uint256S("50e36ec0d908262e3f1fdab6db5309107fcf9c5916ed429ddc72863b64b58975"))
    (628543, uint256S("fd0b5475fabe30f7512b61c75d810ad5504d601f2adceffc8542838a10122746"))
    (638847, uint256S("c7a220b2e3b6c635f84411e937fe9348080f0fecf6b64cecaf73ac2c4140fe57"))
    (649151, uint256S("8b521758aeb84550dc1eb7e58b0081e552f5e49fd2c9c03e273becdfb4870d7f"))
    (659455, uint256S("9c79764bcfbc16176ff3b9c75331c2567e57b76de8fb0480d693c0e673bd0640"))
    (669759, uint256S("4301447bdf42e3a32ba9f4808c79ed99e22bdac91a0bb6d45b9521af8cb1fa96"))
    (680063, uint256S("a7a1769dfbeb197d9c84d0f3702470352ba7eb99b15649732b75ca451925aea0"))
    (690367, uint256S("bac3ef720b240a1352bd5afa3dc5ff7d4423dfc17b6a8252051cf32d845125a5"))
    (700671, uint256S("466a6e98747d71d630bfd74daeee7d03e0fbf981b8261e5e1da66393df54e5e2"))
    (710975, uint256S("c8d27cb49fb8d8ee0533ea8c89babcb1f32b71ce208ae618eb3054fe2e9dd7a0"))
    (721279, uint256S("01a1611b9bf8d852f1b6f0bd0a6d7ba341545ed409d645fb1044d00bb3ced1da"))
    (731583, uint256S("d8a8eb3139286903624bfdcecbde5937bbd5bbe81390efb9a6a4a7baeade7ecf"))
    (741887, uint256S("f03c7ae3d02dc0b2249b2414c6a980f4d2f7295b60f19e7aa1e7d6d8c8b00bf0"))
    (752191, uint256S("30ea9e230fe587ed6d7f9553efec9fe4b8b1ca971f2c46bd476a1255d77d373a"))
    (762495, uint256S("3c2b6a540b69aa6b01d7d94b9cda7860902ccc1a1067563f05545ac4fbc6f0c1"))
    (772799, uint256S("f4f305937545db38dd88869db53e2d0908aa026781e1428207a1cb5337eccb43"))
    (783103, uint256S("f29666db0adf5ebf6e1c057e1341557a58701c7c13352f4df6f92d9404b7f1c6"))
    (793407, uint256S("663481ecd6154391322c0ca5a8cd45573d73ad9b708f5bb71eac194a6d22edad"))
    (803711, uint256S("fe9266424a5be4cf284a6db1848ed9ae532b8b8237e08d46c3245dcb7a4370db"))
    (814015, uint256S("ca75838b5fed097567275d9d7d66fa6a1aeead6e64ce6956c8988e96366e3160"))
    (824319, uint256S("011c7ef45dbeafce4aa37b024c28b0e2de9ac258dfb17c7da3489646025c980f"))
    (834623, uint256S("45fd574b8c8e5d147d2ff2740278c4781f4141f37937673663030fd309fd4134"))
    (844927, uint256S("6accb13a4956c1e530c46fbb80bc2b7a00f06c1b0b7491b542e1677b81599854"))
    (855231, uint256S("6ef4c3be1d9deb041fcca3690854be1ba2146e584201f4ccb8520db5f47a26c9"))
    (865535, uint256S("66c89e053ec060e1bce6ba71c119e5a2d95b999f17be037dc97acc491d01738f"))
    (875839, uint256S("6335c7df5837e5f0b19ba0f113647bb643a7d9dc3a50bc97674fd7d008d5f827"))
    (886143, uint256S("59957921913d562d319a27262e840b61e8e11badea430110baf7608d8345b408"))
    (896447, uint256S("0d54aa3f35ba4632fd5f26b995ca29b368a769aff4525fbf418bfa754cb726f5"))
    (906751, uint256S("590cc47b30216b52f543576630b41390e27871aacb20fa8281a374d978891a25"))
    (917055, uint256S("f706a6e78e21e87b2e8dca946f5e30d342aad48adac49da8f0f9cceb20654279"))
    (927359, uint256S("78b3b5b8f3273e092e823a023f64531116794920686ae586084b7924037240ab"))
    (937663, uint256S("a54a9ba4ff973ac0874711294d9d89f71d7ef1627d148ac5ddaa6e4d9a1fd44f"))
    (947967, uint256S("269e04eeda3c2a7d0ff10390d676e12ea6baf9213a444aad2aba29e07ea4e5e9"))
    (958271, uint256S("8178608dacb05c9ed0e55a6b7087bf57163d77cdd7fb6bc06c7834cfd1b973d9"))
    (968575, uint256S("db408dcd37e055706df4c920b9624c845818eb8fb30e2642b548d0eaca6da640"))
    (978879, uint256S("d5714f1fd6bf8ecb07cdbf1f1f3dff7cc443743b9740fa844f3d241501f7ef8b"))
    (989183, uint256S("79a1b3b46543a6fcc3fa94dce8e3fb82719eed32d560a8606f9fb3c62eecf037"))
    (999487, uint256S("fdb71d5322c3defacce0a092ca5120df2f2655c56f7dfae468614bb1589be53d"))
    (1009791, uint256S("0efca6c6aeade6257fc62015e07bfa2409c72c51a668c7e17e52a9e64940728e"))
    (1020095, uint256S("15c0610fa8ec492b932ed7670ff28f4ea8e1b8f4c85ff04969c44808a3b1831f"))
    (1030399, uint256S("6c7ad59622df578978e072edb5983ccbdd011a0aba345f2facbf5eba51624ab7"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707398760, // * UNIX timestamp of last checkpoint block
    2272040,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2822        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1587772800,
    0,
    2880};

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

        genesis = CreateGenesisBlock(1587772800, 548987, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"));
        assert(genesis.hashMerkleRoot == uint256S("0x24c4359abe6d653e1a86916a0326cfe84cf959fdc9cc60659d3c5901b3181df0"));

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
        consensus.strSporkPubKey = "038da032fea63c7f54c820e600ce4f568a63a013570a76770ff71401871ce7c748";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "MbURNXXXXXXXXXXXXXXXXXXXXXXXTCG195", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1101;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1301;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1401;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1501;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1601;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1701;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("2e320a2062fec37665c7b1c33442a1aeedc887fef37a2ba208df8d136330448f");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("818dac1349e48c56c9beda5ef0015908a17ee35545febba405c5827496e981d1");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("d7777b62abf541e637ea76f2bfce77c3a878354174223bdb43d3776a7e567f31");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("00ed73543b2a555a7154421143399250e6044c93380caa9a8a722a28ad4da5d1");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("a297d00abf468b3eee50f0f80a347029691e9cd46f2a0a1f69bff8e1a099975a");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5165a4bd37eacd57e7c61e5a3c7264fe0a50787fb30b2e97cfde7258f7a74a28");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("594bbd3655b3a2d00f16820b8637ccfaa43c83100d7cac97886ff6350fd75030");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0b38649f5de753f137830a3c38a3785c0fd5f33439bd306240771861b8a0a34c");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x6c;
        pchMessageStart[1] = 0x79;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0x78;
        nDefaultPort = 22487;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed5",  "seed5.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed6",  "seed6.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed7",  "seed7.mobic.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.mobic.net"));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 51);
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x51).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
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
        nDefaultPort = 32487;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.__decenomy.net__", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet mobic addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet mobic script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet mobic BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
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
        nDefaultPort = 42487;

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

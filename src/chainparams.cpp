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
    const char* pszTimestamp = "Uniswap flips Bitcoin on daily revenue... and it’s more impressive than you think, 12/05/2021, COINTELEGRAPH";
    const CScript genesisOutputScript = CScript() << ParseHex("04f8e575ae6a7fcf97b4cb8b213a74b550ccbdb4cabff3d0bfe9ec15f5b863be758acb3aead94933428425dd5e934dced26f022c0b33682b4ebf5fdce242bbe0f6") << OP_CHECKSIG;
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
    (0, uint256S("000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"))
    (14079, uint256S("95d87737d0cad570a1b275ddd94b84f4224215b8e52f7f540269f22eb0823d29"))
    (28159, uint256S("f3d30a078beb08d338b66cc59f100ed1bd8e640adfab641e1c0fd1fe7411ac02"))
    (42239, uint256S("a5aeb3c5f011d079e2bb265ebe7552e599ebb4f0dd90ce7c132503eed280cd62"))
    (56319, uint256S("354917e0c14e5216660eca9a1cb99df8fe52ebd7ecbb5554524ed64ca0ec2e42"))
    (70399, uint256S("8894e4cc6a9ab6264fb80fb0401ac68d77748278dd2c515482f687d902dfe638"))
    (84479, uint256S("4bda0f562fb979abcb844fb9cb3e1f7d89966abd8f8e5863cb9ea1bb1f8261ea"))
    (98559, uint256S("df652b9bc204a2a19862a96983f551fc98f68dfaa31ae3e7172403e08b3035cf"))
    (112639, uint256S("b6661cb1526acf8be163e24fd1eea9771a2469efbc1e4bc69ee42c853a2ef1c2"))
    (126719, uint256S("e3adc071c360f30ff3127fa003c7cc8a31a02eb2863a57ac09eef11230523dfb"))
    (140799, uint256S("5e8da2234fc06163d34ad2090d8b8ffaf038f6863ed2a0cda4ab10fe1f6e0803"))
    (154879, uint256S("776c927f761eec99490bcf4647b5a382976ee9338fb7c98e023dda73f78e8cd2"))
    (168959, uint256S("47e8418c60e5373d106a8b0381da6538b63e231ba7f44a72d09e92c547cf8e4a"))
    (183039, uint256S("8ee2f7fb144ef4490d2f6f7ead2cf833abaa46de4213ae847d92e776ea4083e3"))
    (197119, uint256S("b25caea2cc2b5554f9f0d382b0ae271f047173c6ba682860750a6770d18df4f2"))
    (211199, uint256S("bcb5478e8a3490ce3b54d62e392b7545640658588d3a0a8ff04ec8e36be9c348"))
    (225279, uint256S("c0b80c7a744e3dd6304ced107931bf4a631c93d37566782c577e78103ab7cdbe"))
    (239359, uint256S("a7a739709eceeaf14d15b5af0f9651db54e35278205fd1c32610f69dd9d5ddb3"))
    (253439, uint256S("d0f97f7b52d17e1f3459c9f9514e22b86a3e4479c9b11430405d33d166d540b4"))
    (267519, uint256S("b57e8e25826984ca382149ad3b075b11630173f0c4c0087715dda6d8b1e31c84"))
    (281599, uint256S("85cf80cf9fc07180e3277fa750d01b6f4e1071289e4b98377a0b93a3be09e589"))
    (295679, uint256S("7b7af96120a6c9a9c6ab114f15878f8ea29b940d37b76fd0fa50cf8d46bf0fde"))
    (309759, uint256S("aac70a353ca67f132ead1e22aab6bc9eaacf1061053c1961956018b060508969"))
    (323839, uint256S("03e65e2952208a7ce9c00e5bf15c007c14ba453be4257cb7788ef223dbc9f886"))
    (337919, uint256S("57e544979acf7960e8154edd34e856a493533ae4723c8a54b4617c64589edd60"))
    (351999, uint256S("a8375384db54342941e8038e459d84f4d834a6f490ae86750c2cf86d3ca01914"))
    (366079, uint256S("a0a9fba4dd4dda459f1affb8044ed662dd246db70de21382761d7c5eee6c37d1"))
    (380159, uint256S("0f75f934dbf1576b54edaf01fdfcd4d2cf0f201e20462517f650ddcb4ab1b7ae"))
    (394239, uint256S("b18a5d39b0b8d2851401029299d1921c316ceef0d89b99ecf1a9bf5b23e2224e"))
    (408319, uint256S("a70c65b2af18aada62a65dd04e1fc6c0662b83b5473792c2358c2ef2ee7b61da"))
    (422399, uint256S("7d57f44dd190444fd62d2ad30841cbdb3d9be370c0946ab74cc42e7f5aa82ff1"))
    (436479, uint256S("fc9d57d318ea06e106e4c6f658c91a8cc244c0860d392e635b6ab7897ed06b9c"))
    (450559, uint256S("2a32c4e2a1461c4f99994b4bb81416e9db756d9bd18dd6bc293472cd2f77eb48"))
    (464639, uint256S("ae4a4a4e464157215a6920405ae64a646cff0036dd7a34eef60fe1337bc4696e"))
    (478719, uint256S("311451367988e08b2d0a9a1c0c7eea56d69eba199e4f92f35141fada01776ef8"))
    (492799, uint256S("0cc5239e45fcc1723553b3f082f28aa4ea6026a46ed0b43c346d91ab1a941346"))
    (506879, uint256S("4825489694e37a4a11416aa6f11c27fa839da3114e7d4c8660f483b5baf76cfe"))
    (520959, uint256S("7c4381ceff446d6cf36811dcc1354eb972cc4f21e2294943b42fd02a26e2d243"))
    (535039, uint256S("4a1e735fdf1688111d3a312394173a5d6e39cb4dc3922fc058b0114afa2b238a"))
    (549119, uint256S("f4557cf3d45cdf9afa6294a60e17a3487089f8004b9d79deb3d208a7d7123047"))
    (563199, uint256S("18d90ea2584c1e49c429eb1e919963228e1e44ea3fd88eb1b61033c6ddc424e6"))
    (577279, uint256S("c514255642eb4a9c1ee5189f893df3199504b405146acb111e4fe420316ca098"))
    (591359, uint256S("edab04b1b9b5be0bc16f79be74d2ef4d52db3bb86ca9af438dd14e6b8b7361d4"))
    (605439, uint256S("5598d116b28abfdb7c2bda3c66a5ccdaf24f0b5fce355d45e2b6a337430b27fa"))
    (619519, uint256S("3fecd2ccc70840f64a87d46b170626cd945041c16f14dd6aff547ab7a91869b9"))
    (633599, uint256S("aab7ba7e1e4ffac45a20b96f0d6794ac6dceabaaf6e1a2501f04a12972622683"))
    (647679, uint256S("e71312a12e8f19b71b289690240b88f6da8002d3361945f739075a505eb3ebd8"))
    (661759, uint256S("39e53ba54832a84423f243a49924b2d16195f4e048fca86f569cb605f2253fc6"))
    (675839, uint256S("42e6388618d3a748aecdf47b95d1cfc46a34047ce1ffe0b4a1588616b4c438ec"))
    (689919, uint256S("e925be11f8b99fee746f1a0a6c239b68bf67d722e6bf23b8c3ce250020d658f7"))
    (703999, uint256S("5572d8e3070eea6fd68664a6b0570f6fdc2dafbf91154ec21c65c6d410cdb9c8"))
    (718079, uint256S("5e8ada6fa2cdd736d5e6032555e0b2dee09381931f3d02d10ac36140b3d3fe0c"))
    (732159, uint256S("8239eaca51d0ccba2f758c260c3cfbda8bbe240f0eff9a727aa5134eb8fc9e02"))
    (746239, uint256S("54eb973310cfbf926ab6014cf6911ae6c1b7416af365c6ec55a8a6b27d087ca8"))
    (760319, uint256S("2e5ba71b7bb0c263616f727d8649bb77af88ee58334d8ba00acf4d7a183d4771"))
    (774399, uint256S("177cd42330c0c60f456dce4c29b5ee054f3c7cda697d57555a31620cfa0f9ec2"))
    (788479, uint256S("a68d1f12abaff72dd448efb1e063b45eeecf1eccdd716b27c167637286fa895b"))
    (802559, uint256S("7e5c71f4a55a11274d117e6d6b59d250e387c3023375c5558d2e7f0a8ed3c9b5"))
    (816639, uint256S("f10877e4f1968564f79a8e3fe29a089479ea324d45ece3e243fc24bc3409aa97"))
    (830719, uint256S("5d740698793e95c43a0b373156a89004bb49a428aefaec7d7070765064b825e2"))
    (844799, uint256S("885e86a1023ce6a90184611ee4dffb23c390f2ac6ec44f116a18c58e3388afa1"))
    (858879, uint256S("c238c9b8a42cd7d6180643a53f637be6af630316a6c44565dd9db55f0f96c1cb"))
    (872959, uint256S("2f166932068719e17d509a8a92024625a4adb04bc1503c6393c63ab52e057abc"))
    (887039, uint256S("863a2094bef111fa095e29539cc54110750ddcf17824fe0d5100aaa76c2f17a7"))
    (901119, uint256S("91b5c5dfb9e013645c5be533d897d729c103076e035c20c26b1329308d077af5"))
    (915199, uint256S("d0bf4336d157f0f1b1c3b4c3d2b45b50b832a6ad0fda059af976cdac2d2df928"))
    (929279, uint256S("bb7289fb473f6811b9cee198a6b90a7b617a454e6bc050bbdd72c405cc3dc324"))
    (943359, uint256S("ed9ec868e237dee705e6fd3a95ccadf2a96130f7b3a31e8139e5828350de5450"))
    (957439, uint256S("7561b7adcb64f6fd6e7c0ad8e618ab19b159dd3606f66e9c4a926c969123e007"))
    (971519, uint256S("a53647e304eceb116a2d62d8d7ab9e07ef934fc0e797fdff3e18ec2c36573de2"))
    (985599, uint256S("dc43e5ec493ec5d52792ff99e29935b2c81f0caafc80504bd99e478e76047221"))
    (999679, uint256S("56e0f9c59a4f34d42f277ebbbac37bba087f63e123d6b749d3f50f00403a55da"))
    (1013759, uint256S("c6a7aece17542667f935f41a5522323ba9795d8f60510c69fd68bd0bc8c9bb77"))
    (1027839, uint256S("a1d5f8176b0c122d2a6f3d1cbb60894d729991b649cd48b02098877b4d9135d7"))
    (1041919, uint256S("e7ae4fcc375bbfc37da284e3af452c84e1f246e91ecb51a44e435248defbc061"))
    (1055999, uint256S("d2aa47c4b34d500fde859e51d9b9898666b0bf5f72b52dabb060206461a082b9"))
    (1070079, uint256S("0835e3e88c5abf522dbd6d6dc6ff5ef62d8235ba942d31a9ead73b1e6e0b31f7"))
    (1084159, uint256S("fb5283ce65a058bb50a673ca7515a4846f255dcdc13052dbea74a2e46bfdd263"))
    (1098239, uint256S("26c5ab2e53b413074172fc328ff90f760acd91d7dcea2a2e8c0abe6e229e4983"))
    (1112319, uint256S("66833b9a4979d6ae746d800fc23417adfe0f9f30150fc2fe492ba72b1d437834"))
    (1126399, uint256S("8e900cb1b23d7fd94ba26f3bc0d28eadbfc0d449d090311e7c7b94d9d33c1bbd"))
    (1140479, uint256S("e479a0990c14864039cbf86a728c796ea687f4194f17315b43be3593a6c43986"))
    (1154559, uint256S("82ab7d0d78affe1caa4fd445a94b9f0ac0d006a0b4ecbc7ebcda93a4be3f703a"))
    (1168639, uint256S("5146e66d765463a3974b028b51de0800182f42a4bbd95f8b63e98d5daea234bd"))
    (1182719, uint256S("3d595ff761849f190e489858b36e50aa86f6e51693b99d67fdfb3ad0541c94ee"))
    (1196799, uint256S("d7fdb24cd4b32230fbc022f41a41950f95a2d91ae751d3d18822a26aae7bab87"))
    (1210879, uint256S("def339861369746b9a65c71cfbc486ae32713cb0e7ec308d863104db4264d30a"))
    (1224959, uint256S("0913d93ffbc91dd5fa775c3c7026107f1b434f7f626a66278814d02d4ea61642"))
    (1239039, uint256S("746d000b43a043a27cff8c3eba587d9023adc9e9f220550a5357cd96677f9469"))
    (1253119, uint256S("df505ce85e4450cc2a61bab045cdfedc92d570ca64421b62e12ee26b14c1ee12"))
    (1267199, uint256S("0e4b8b606cfddee85bd9a0127d8789ebc3e347f244831b7badfedec225d51116"))
    (1281279, uint256S("51ded4c452abe33d57c31a6ffce2689104885abb3386f2478e8eec5b12e57f12"))
    (1295359, uint256S("91c525f366a12cf56e287c30f3a315a6348680068ee7f9ac886c48e5ee7bd547"))
    (1309439, uint256S("ed9a5fd473f56e4bd53140aef174bd11e8924c3630a0c53d20c25773de3974ae"))
    (1323519, uint256S("0237551e7d137c2f3fc41b70b8020dc015422af6c0829b389b9c3a279772142d"))
    (1337599, uint256S("8cd204e1cdde27d0f2b4bd3cd86d3e2388f81527ec601a29b631d9808dfb2b5e"))
    (1351679, uint256S("d41f63ae0e60844531b415f363e728148b377f70795128cb5d057231b915104f"))
    (1365759, uint256S("95f6dd629610375524847afe6fe427875ed5638c169b1e5be75984aa4f9daaa1"))
    (1379839, uint256S("b3b2eb657d39b4ff79625b8a9d75efda8aa01038df92571c7075f2d68089c1d7"))
    (1393919, uint256S("68c122d0221d83470d86285074eada2b47ad8c13ad8f48e333ab051aa37eca87"))
    (1407999, uint256S("dc55310aec9e1550706df6beb17574d6303b85dfcbbf3bd426907dfb1a3d5e64"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1707348015, // * UNIX timestamp of last checkpoint block
    3194983,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2816        // * estimated number of transactions per day after checkpoint
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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1620820532;

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

        genesis = CreateGenesisBlock(1620820532, 580458, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000004c7da0d7f51dfedea7925831315afb00a41ac2fd1cba3ea54e034efd369"));
        assert(genesis.hashMerkleRoot == uint256S("0xa5567533e1f5261c38b1b68fcb552f692558d820b338222777893e616bbff4d2"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 30 * 60; // 30 min.
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03edf6c42c34d7d7b43103b1d3360e7024f48aacc2ee14a05248b7656bf4280bab";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "PXXXXXXXXXXXXXXXXXXXXXXXXXXXVtkn93", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 110000;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 110000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("50b97b398887b8173870b04a31a2bf1e5b9c06e6e6a10e0b89ef6fd00e8403e8");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("dbc44077315a094a2b7fdb75c1841aaa4fe95ca26452d376c55a37e37cde343e");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("eaa3c0abdd0fd1bef1adc5fd7e5219023b0a15d2713abe1a2974198989992227");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("c31b091596c132cc1a7ed4a87d39600f42203b50f82be210cf06038b48427cc4");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7e94341430a8419e2bd432bd5822a1839545fb35eddd73da1708c01888d6e22b");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("eb883c9b495b398ea70340e6af8c9352622fc3b7bc2d462fff77c132b1d92d4f");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("eb883c9b495b398ea70340e6af8c9352622fc3b7bc2d462fff77c132b1d92d4f");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xcb;
        pchMessageStart[1] = 0x9c;
        pchMessageStart[2] = 0x87;
        pchMessageStart[3] = 0x7d;
        nDefaultPort = 36779;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 117);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 118);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x2D)(0x02)(0x31)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x25)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x48).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 999999999 * COIN;
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
        nDefaultPort = 46779;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.peony.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.peony.net"));
	    vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.peony.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet peony addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet peony script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet peony BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet peony BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // peony starting difficulty is 1 / 2^12
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
        nDefaultPort = 56779;

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

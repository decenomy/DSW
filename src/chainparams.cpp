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
    (9921, uint256S("6dcf2739e106e6f9aad038777a6381b1c8a21c403aeccad653211cfc949c971c"))
    (19843, uint256S("ef0f8af86f61c97bc20ebb72686fb9cfc7fd950d395dd02aaafc26e2c539feb6"))
    (29765, uint256S("7202c1e0eb2c23d0bf5c4fbb2e73a6592371e29f5b586abf34661cd31ab6fd6f"))
    (39687, uint256S("924bb9e2a7ad938dcc5e85d087249ceadbedeee7d53f866a5a165386b8028e6f"))
    (49609, uint256S("2eebe1495d1d872a1394bd2039918edbe4aecd7b31c8ae8c13c4de3d18660944"))
    (59531, uint256S("a2a79c8f03a266fad575c2ebeb38ddec76ca16dd9947040fedd0b9eecca25779"))
    (69453, uint256S("1889e5949d1dbe48c8ca37e7b34d9465177ea61701bdab2a9169bcc6985a0725"))
    (79375, uint256S("fafe366a2ce867cfc281c16a8968b28a915097a88069d9a32e2ff9f8a77b61d1"))
    (89297, uint256S("6ddaa5df66723d493edccae5c76baa50413c9e1ea31ec2134edcde45858006d3"))
    (99219, uint256S("2902348181cf6253de81cbe7c41d746b2c9e550edcba9b133d39da8c770e4035"))
    (109141, uint256S("a0f20e9013e463fcf30cbc3dcc034967c61d8940dece2745fb1938f94b29a00c"))
    (119063, uint256S("5d479b2cf6fdafebbf5f734361dccb25024eff08df7d483126fb3c73e0e13804"))
    (128985, uint256S("6cccda4d3bf729d20ede5553bc9817c6da0db357c9966b4da21e423f4a4bbb7a"))
    (138907, uint256S("049aaef7ad672ac8f3a5c6b136a372680902bff6ab7a48307cb3d2164760023f"))
    (148829, uint256S("2b8d9f763cde1d7a3fd94757efdcb7bce812f804b2a2714bcc976969def2f079"))
    (158751, uint256S("608005fdda797521b4ba228018868702d7ad7e34520967c97d3a284a32eff155"))
    (168673, uint256S("46a048fd4f82063f7f9fe34c6f8f1391c298c693ccdd21f814a5b79b8beb972d"))
    (178595, uint256S("87600fb46ebd7281ad8fb445e39e7f9d0b72380c51ee8942a055b4231cf1bc73"))
    (188517, uint256S("ce820b7e24c5cdc4ddf4cea9e6c8fbaaf94b15bca5a1af86810c5e19f3a405cb"))
    (198439, uint256S("b792c31c5007878d698639aa47da778206b76dc97c686e18ce02a925ba2778e6"))
    (208361, uint256S("23812ac796f8082a8ad2b10eb2554e36407dfd7f581290d08de7a899f0e9a27a"))
    (218283, uint256S("9dad1c24b4779b6fd57c50095575c554bdd0751a3e39dc92614f594a88411087"))
    (228205, uint256S("be8bb4ffb82bd862d78be5f7fab1c60c7f66aa3b7dd91140efedc74fbbc86ca8"))
    (238127, uint256S("910254e76821a17755653c2e433478357fe6e1aa8b891bcc45586ca0a2b98155"))
    (248049, uint256S("3f8d22dba93de5ba311d8675efae6feac9fd090f3174c613a94b1bd13a75ec3b"))
    (257971, uint256S("3d8c5c071f01304569dbb5dd34d692455798b2d290dbdca395982e18b1401570"))
    (267893, uint256S("d22fed5eb0edb80f08124ebaab8f54bb410601a854baef7998c8631f8eee47dc"))
    (277815, uint256S("e2c08ac40162db32b93c3d53964436d3c003f24ca7d3218dcf0b1a59eae534dc"))
    (287737, uint256S("aa39e485a624725ba6f1a794983e8d1eba0014655c670c8afa98928e8d7f9c57"))
    (297659, uint256S("0d97b0913b867c5ab09896fa2a96f5dda3871649ddbfe5e074d9cf4547999566"))
    (307581, uint256S("c71447f2ad4860c84fd4d07f228399060cc0aa8b7db4aa2bc971c150d8e97849"))
    (317503, uint256S("c297997ff1ec5c279ad0e4bec9e29a0fa45108298c528eaa667a113980a32172"))
    (327425, uint256S("0c25df4db6f8b3b87ae2e53bcc2594d62d204026bb6f43ed068d0009f8c9fb0a"))
    (337347, uint256S("172266a1b54625848f712b347c2adaa97402180dd9d1337215426786cc5106e9"))
    (347269, uint256S("34ab88ae67994516d75b7063c8c37b775bba76a82938c52597275718f470a690"))
    (357191, uint256S("4bb2618dc1a02263654bc4feecf3e617bd8b374a72a6ad1b030b472ab60e6e65"))
    (367113, uint256S("045bb54bb59361e5f92236939f4d943e9651cde47877a824dd5c4995e236a48d"))
    (377035, uint256S("9609220a4fa211b6b95467756408f7fddae8e84d7580b5bba45060cbc3c1d8c9"))
    (386957, uint256S("7765461676c465241e40b28b997a5603831ee5962801d010a5b99c69cff8a19e"))
    (396879, uint256S("0dcb719e42f916ecf22152bc4c253c844ade9e0b04f8074bd501eb422f3139e9"))
    (406801, uint256S("19eba5f6baa8aff22af0b37587ebc9e6050b6df7f3f618625b71daa378494bb2"))
    (416723, uint256S("2fa720d3edd2d216bc971734c335ded01fc2705ae79ef2736cce58e84efc75c0"))
    (426645, uint256S("50eee850a4d36d3cd5e66f2c6cec17916f67d4e57e2e9b9fbead90c1a5465c4f"))
    (436567, uint256S("5161f538f595a3302b64c43065cd92e30d122a7b234a14c0ba850f8dedc27444"))
    (446489, uint256S("cf2bd1055e13b12d2bf30f9c851f33db90b75d3a2d1b5a01f78b075246ca3972"))
    (456411, uint256S("acd8764070c5b05e109c9ef7f1ffbaae643d38df8be682b530a5baff2fd8701f"))
    (466333, uint256S("94187a723c79631cdfd0007623f341831137cf411bb2acfe35ef7c58cbc1583f"))
    (476255, uint256S("9469960b6b778259a13690826457be16b4a82789746f2ad33e2ca70e32b99e2f"))
    (486177, uint256S("40a4c4aea0c0a93a746b52bdaa24b6ff268e2fa36d620110d04ab8c19d1f0bd1"))
    (496099, uint256S("e8ceb120cb71c2cbd2d806ae95634ebb4c4e125650f0fbcf0c111fdc81eb9bcb"))
    (506021, uint256S("fea3ce8397402f7f4c81558b2b3e14b552d72bdc29501c7f6f7358f0a963e6ae"))
    (515943, uint256S("982bb23a25c2e5447c661d04d25e494a35823b68883a78e5936bfdd33fbabaca"))
    (525865, uint256S("8407c20b33d850ccd086b6b96c891ff8a7f24785031f119942fb8d5160880b51"))
    (535787, uint256S("ea9ae06d8cd83c550b6f7a10863db84ff0db1d07fe1ef522bfb6560d86874320"))
    (545709, uint256S("8bae45a37a8efd1fc5ff26ec4ba3427f84a00bb60f5c3856a23bbabd6157c024"))
    (555631, uint256S("f0e44b63bdeb11cc57d59c31a89951a78d06411ea463c21eed78c0fa39050bf2"))
    (565553, uint256S("40caaa306001b8b80dddc6131743235c8aee7755c03e37b1783fb39e9663c70a"))
    (575475, uint256S("8c3a17d14f0f025b3b27ad1e23e4e9c10da35f0660f800e83235627ff47215a1"))
    (585397, uint256S("d2e105845c20d4d2a67c61799f2b3b0c2a18682d8a8f880b96f1cc526a875253"))
    (595319, uint256S("1ce7c5dd9c6c9e1d49c575b72edadd94d882d76bd351af666de7217afb0f318c"))
    (605241, uint256S("210a49a3dc5e036a4e7c81871279e73fee816e585e0284f7f996845a64d39be1"))
    (615163, uint256S("764619d5d5c22d4a2b53ff5c55d88a80c6266802a9e20d352261e7437a3ca315"))
    (625085, uint256S("0a8e06052a5fc2881dabfe1f489a8cb2c64b30394323c25ba5e9cb584fc8a587"))
    (635007, uint256S("fdac9bb89212a69f73e1e790421b292485895e2abeb391104caa7b9f6b6adb40"))
    (644929, uint256S("db6d0321d5c157de4436081f9305a8da3e214036343cc9babd535980f4220593"))
    (654851, uint256S("acc02238f6009f1a17267a1e5e5ee52dac28bce9ff3e4cdadaabf259276d2d8c"))
    (664773, uint256S("24355dfad664c6582b151afe32c6ab20068f903cb466ff0d7d87c1773b2676e6"))
    (674695, uint256S("fbae489e9383fb6064b9493e7282d0a151886c780b1de314f18aef5dd028fb57"))
    (684617, uint256S("f944670d264d1a6af4b2e10b3bd07e987bf6351b6fde613b4aff62214f73f714"))
    (694539, uint256S("62d2fe00f306570c4fc1c68454003c790cc0f20f4479a03088bd96b73261aac6"))
    (704461, uint256S("3bb607b856b05ee166e4d77f2289e7b6d892a414ca307ed9e38f29226577d21e"))
    (714383, uint256S("d237a2a720c5da497e746bb6eab907a0f9fb25b43ccedc19e159f8c842a17e07"))
    (724305, uint256S("1fb081945b0c4cb5a5053eb6636615f08041eb8911c5de28cd921d97d3af08b6"))
    (734227, uint256S("5edfcfa0622219e7357fa3c00b700cc8e4f33e6881977c419e1022dff8343983"))
    (744149, uint256S("4b554db3df7178907e64fe32e96449c0a616344cc73b3dbff19b61b0bd2b9487"))
    (754071, uint256S("1f3deb5df6ca8e2b9c9df92004c5be3afab70bc5da0ab754be604b22c83dcd74"))
    (763993, uint256S("224009c6f93907b49c09d6898ff72e7ecddf5581f85bd7bc505e574c5b4b0f85"))
    (773915, uint256S("5aa058c5feaa47a3cbd85779c5389e20a054ee22db6f7f9b86dd310a3f043ddc"))
    (783837, uint256S("a602280bc6ee330e9008843c86a26dc09d076c6769d6152380049490b812d52c"))
    (793759, uint256S("a7ffa4ee79607be806394673adb12e9206ad9b949539d46dad2b9a32612a9a04"))
    (803681, uint256S("fb9bdcb9854c1c815bca93c6ba3ab85c5a7af5b0d1e32ae1083fdb0210f594c4"))
    (813603, uint256S("ed668f37ffe8f235313f9b7d4a4086cc1db6a559baf492d0b79f18c6f71704ed"))
    (823525, uint256S("dababae233e64dfd2bafa28cee02e989370919ef85918e18d901adda626517ca"))
    (833447, uint256S("4774614154309d290af58aaba5f4147473bb7c828d164c20efe0a15181c3b16f"))
    (843369, uint256S("0596e21545d9faf86aeca711102f76885d2dba17de17556922715037c88a5bb3"))
    (853291, uint256S("d36a5691316e8043b5c9cf74dbae2f132708373bcb41a85d01020c757c3de55c"))
    (863213, uint256S("5fc668c28a3bb4896c86bcd4b0f1b59c516ecc0cc0bbe7ee1ff38d76e31cd2d5"))
    (873135, uint256S("a262500b285762e01f93222a0549a6ed61fcebb140471d94c1af9129c27386a4"))
    (883057, uint256S("63a1282ad8229faeb787d0f8dbe6010197f8a9b059a6877b6ee9ee1dbbddd00f"))
    (892979, uint256S("d714f7d0d170bbfa24052b8f8f8a340f9e3c398c90747f155fc74f31c43042d8"))
    (902901, uint256S("7f27de3560dba56a8446a4dda3785e8cfbe479eb665aad562e381f182b5cd27f"))
    (912823, uint256S("45a15ccff73b3288d3332392a4b91c6007f1c53b33d9bfda5ed3c5699582ba70"))
    (922745, uint256S("8019619172696a11a6ffdcc8b73c767454492e23ce467e219e09db9e06a5a261"))
    (932667, uint256S("7936e326089c56c7a1777f68d5eb400eacae625ab792aa1aed3474838fc1b0ca"))
    (942589, uint256S("7274574541a47fbd4e4da3784b635d92397a6ce6fbb91b5c46be08afcd0a4411"))
    (952511, uint256S("6012c90a669b0a1863642b8c4c83d4251b3aa75f96165478e5f9879240e9431c"))
    (962433, uint256S("16181776fba6fdf638796c321149f6d1062523ccdd9a63021b048ebd4d33bd13"))
    (972355, uint256S("ae4d8d15ca905e6fdd1b7812927ba27a98c2596fc0d502a8a1db3cfe514b3733"))
    (982277, uint256S("50da6b37f4df1cb383794a894df4dc3e2c5a4d1c1ff51822f74080917b3a0925"))
    (992199, uint256S("f04b5d61d129b33b09ac59e26cc418000ebff119a1ec99f2780af7e9823eec28"))

;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683555150, // * UNIX timestamp of last checkpoint block
    2229383,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2834        // * estimated number of transactions per day after checkpoint
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

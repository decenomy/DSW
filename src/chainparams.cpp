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
    (19723, uint256S("f6915c64ee410d8d3622e21da25b13da6a04c0ce4591a5e5f99691affb4ed3ba"))
    (39447, uint256S("135e5d4fc0c1da04ef3abefebe72f8e51e8a0d99c7a27103674558b1218ec851"))
    (59171, uint256S("4e18a44144a8009d50b7e4342bbbed50af5eb0e7e3ec0598c67f498bd08619c9"))
    (78895, uint256S("9f1b70fa7dd439fa91cc6e7b233646d5c71a9115861430310254029be9aaff80"))
    (98619, uint256S("ab7b7b41788730d64104c6a1215418622a21277427ef746c6d08595d17fd2dfa"))
    (118343, uint256S("f67266106f08760f1d4049d216723747a060b12d9b7963970fbd08cc9c127300"))
    (138067, uint256S("49d49d0cc170c1b89cbc023741fe252442b2416df770dfe74bbe1a2fab30e1b8"))
    (157791, uint256S("4ac158548a2626685e689095b4ea836ea2e685b85610edddb610938b42cef603"))
    (177515, uint256S("d672195dd6e3edcd119394c3fb2033a65c04c0eff9c9e7be82555318acf9da41"))
    (197239, uint256S("168c7a8e234fb12970780ee29962f1c421a1f80ebee820e4bc22a58708f052ab"))
    (216963, uint256S("41a5f10eb153bc54de86dc17558c093efb472204cb04202473441654f9a2c6aa"))
    (236687, uint256S("6f39c10dbd66e5f74aecd9c99bddf1a1d2e0323137d673560fe4fd0e7a2759f5"))
    (256411, uint256S("4eb43545f911d33776e5e832de2109dbef8f0205e5d0d0dadb5ec8955514ae70"))
    (276135, uint256S("a6e5ce0cda6d3bbd848cc7141283e5918008a49ec70714ad50784e20a340df53"))
    (295859, uint256S("d2aacf3d7db8d85d59e863f35b16fc6f033d39dc0bc6fda86870c3bb4e867898"))
    (315583, uint256S("c30b4f6ecebe3c632fe4d58e781cf7b09fbb9522bb3069ce02580dc97b6435ed"))
    (335307, uint256S("9023a23482bfc0debd6827a2158740af1872b670fe367f5a5118163b79b8f09a"))
    (355031, uint256S("fc5b99a5291b864e100831bbb11719ab4dec97c81e5b89b98af4945434ec15d9"))
    (374755, uint256S("892f8f691b0453ab2f744ab0dab6b84cd14f128aaf600007fb0d54a73377a2c9"))
    (394479, uint256S("d61d63e6496da3fdd32fcf7d925e572b114f1aa02e224a4f3a11ee79dfecddb5"))
    (414203, uint256S("cab07bafa1953023fcfbc240d949ceffeac2bfbc03b582c79dfc620ec6373123"))
    (433927, uint256S("fa9f85689447cadc300808a2922ec614f7f74f6ca3e3b205bef36cc1baa537c5"))
    (453651, uint256S("342e11971889995a3d7d777767ad07c12a6bc35d6f10a8540c22156605987ded"))
    (473375, uint256S("1e45e44ff8050ac2c2c951b568e133c14b00d581f93f8ae9dca9fd2d15c50d95"))
    (493099, uint256S("c166086c4363ffd9ee4dac5376928613158d9db83af62297d504482cf90bc3e8"))
    (512823, uint256S("51eb1b6f1004e39da8fd812deaf9078da49eb9b221f3dea5922a960730bc33db"))
    (532547, uint256S("98ac22541e2b5db66b0eaf85eace72b9805133c16bd3e7bba2274729e5bfb536"))
    (552271, uint256S("d44044a77f3b318949564aaa707d1a15b7bd94cbebf090105219e9dcd22ac02e"))
    (571995, uint256S("d2eb9f6cdf0503ac1a86a2d8312ae68a9190857881823b4e6a214c8b4c25e9bc"))
    (591719, uint256S("82ebd54d5135e67f253d7167c66a58f770c705cfcc3c7db1148e2897bdb18bb1"))
    (611443, uint256S("2951f19f3433365b0073559d84f17a390305278d1877f2b9d2ad5e3644dbcad2"))
    (631167, uint256S("5f6ceb1efd086b1675fdf9452c2db8c224dc20a591de3a676e89b38ccc320ef5"))
    (650891, uint256S("c4e7a2e752421f7e35aa346d4311e905f1f0e8137373acd830b6c3450e0fbbf6"))
    (670615, uint256S("e1ca0bf47a75f611444efa706f929c094a56315e2e0c9f6404c93e3969d07d41"))
    (690339, uint256S("88d3f1b73f4a3760a3617312c476eb0c4fdf6cd1ecd0ec8d2767cf0850d78dcd"))
    (710063, uint256S("ce366028eee0fbd82ae1c517944625535220a12de418a09bd59ada05f1534c4b"))
    (729787, uint256S("d185e41f71abdb1cddc8d27d753d472dd0f80f1cd78b74347b396be0d8c7cf9f"))
    (749511, uint256S("7ae0d357379b78fa6478d4e4d1859f72c3862e80276106edd61632f9fecc813b"))
    (769235, uint256S("10c5b1d1aafbf098f659e4597dd2689539b83f84e0a9e41bd6718eaf4acc3b1f"))
    (788959, uint256S("364bce88b84b43fbf066eade1f62fc0d781c552d32b8859e99447bee3dbd6b79"))
    (808683, uint256S("3c9136ad71e2549299aca2315f1b0f7828a2c763f3bd0f2f71e5fa940d46b5d3"))
    (828407, uint256S("f098b73a3fafcdcecb5aa3b8ad7cd89a4c5bdfd4c1d4eb68ff8ff6decd70e855"))
    (848131, uint256S("e4e205751c8fcc8c7cf467c1102fdb80833dbb8b04013eaaac6c0f583a656ae0"))
    (867855, uint256S("e9925599b1c55cf879e202074db34c404128989f05fcd9cda4d9ef9d29b8883c"))
    (887579, uint256S("812ec8e7f64f6f1379ffc86078891ba7df85a0f45826250ea500846a5e136b31"))
    (907303, uint256S("84d9f3351c8ff985a66138f67d975b6e0f9a13f2a3306f455c32e046c6cf5746"))
    (927027, uint256S("e7f3e20c6caa886cf2543eb60794f939931f66a3464f7048b7eadd7fbd653ce8"))
    (946751, uint256S("da76a3e8efc1805fa0ec6438bf08bc622a3d13d6b79c58c55280099b4156cc19"))
    (966475, uint256S("b6cc22763dbf59ca1155cab8ba61d9748e391fa642ddfe3d8b69b1e75af847eb"))
    (986199, uint256S("a19d098d818cf1f48aedae70e0b7d03a218804bde464f24329329ccf825d6a9a"))
    (1005923, uint256S("bd1c53f1e618cf72276cd8749c61f4fe73c31e7608ef7c7c813d985b6fa7de62"))
    (1025647, uint256S("bef287c9d7aa6253bbcd5ba0198381bddc941f32ca324f4c3de79e55fc075d5f"))
    (1045371, uint256S("2364fa819b50f9707c74c38374bb209923593e87aa9e4457bbfbc85c8e5c92d7"))
    (1065095, uint256S("18184260eeb850abebbba092acc6d2d00de052312854c4ee1c407ea4c7ab2fa6"))
    (1084819, uint256S("08c8fd3f2dbeeae580a94fe78448fa94a9d4d0f519172e48a61e2bdc6e05896c"))
    (1104543, uint256S("f88eccd9c2b455d6352a738e1f9180a5eec9bbdf5bf83b95166a1c1144b6589e"))
    (1124267, uint256S("f5277279ee1f55c36d92d99bdaf05e8814810349481436443f83d5ab25ec9952"))
    (1143991, uint256S("7a02ed8656d8680a3ab113a20cf9cfe0faf3c2579e6a64284cd8146075359186"))
    (1163715, uint256S("80e492392892bc1c0d2c9ecaf71daf4378f442368f74d63f091276e4c7c32dae"))
    (1183439, uint256S("4b594b9bbd150dc010efb1e2b9205cb56ce70c0e2bf07188d5babb5b6d839e82"))
    (1203163, uint256S("d0ff58b9264c732f0206df8f8ffe6fb33aca3636f537a10b5fefa8f0675c74b8"))
    (1222887, uint256S("b25b10a9b2ebc3a1947f91b8b7d70c9a95c6b3bf940177ae5a307efcfafae04d"))
    (1242611, uint256S("b2004509ae8c4a43865bd342a3b219e7ef08d110ded40a5587f28b192090da7d"))
    (1262335, uint256S("81a033274d22f14aa2113492f5d29c070f999c2c882e5dab6c6f81349f55d9c1"))
    (1282059, uint256S("732230637f98eda3a4481b632e718d4c94ddde6c99438e9cd38f5accc7ca5f00"))
    (1301783, uint256S("e041199ca2b2cb6f9801a641ffe376d60a39e075b2b6df0a93998399b140544a"))
    (1321507, uint256S("6ecbc876819fb194c9da49b3d0f0905e325755e3e675a28fca59e72ce9387c7f"))
    (1341231, uint256S("ca9fc54f168bbb0cdaff361d459e0c11d7f655f1ba7f39f95d2d62a5a857b687"))
    (1360955, uint256S("62fb8d64fa193f93878b53b0b47379769f623b9ee158075014bd57213a744003"))
    (1380679, uint256S("f8578e7be5ce3b064459053f7747e430ecca698499ac6f01a2c0069bdd07b5b9"))
    (1400403, uint256S("dbffd1a2d54d56824d0fb907b346851852e74f9f66af3189de4dac1dcc44cbf2"))
    (1420127, uint256S("92a534aa1a97d0ec990b30c808d93d4233daf9f9a7bc6a22db0710fc933726fc"))
    (1439851, uint256S("868d47fff752838963e76a0e940a38e0571031a26db07b1da2e46918d02ce49f"))
    (1459575, uint256S("42e5062b64829eb251c200be93d6140ab9541b898cac60556e9e6d5352b91b11"))
    (1479299, uint256S("815a6d619062410bb6c8281b0d4b296b961a8aa3ce0298dd1a46e22a0f93ad8d"))
    (1499023, uint256S("d7c3b66c1d2fa769c51c3c6fd31b4ed380659c062f830e520e9716615a2990ae"))
    (1518747, uint256S("45c94c31afb5355f7d54ec3b8c1fb3682a28704fed97c7a09d97ea9c29ace61c"))
    (1538471, uint256S("6e5c709713b9be507c1c99f45430076572d0c4b3747e70b7cbfde9d9b208b1f4"))
    (1558195, uint256S("6898a4985a3b17da78036414e78772a28e154c32946a49cfccf5021b8cd702d1"))
    (1577919, uint256S("3cceea50db5117a3e529d5b4ae10bd2d9b2be17a6ff8b302f68cc34fe476798e"))
    (1597643, uint256S("def54511ceae42b353836ee0ff53fae6ee3dfa35ec0991b405fceb4c70f318ac"))
    (1617367, uint256S("050ad34aacde9d72fbf54d2ac08f0ddd3b4d948feb37586d4dfec0f53bbac428"))
    (1637091, uint256S("5f6411fe63a30a0443a62521bbc1652bd71906e45af8150e012809e5ea231796"))
    (1656815, uint256S("db9a25d11b2840815906e73cf61763a6d7c7e6a50080a6f8c57c5182e2cb597c"))
    (1676539, uint256S("73bf6d457a9e1ead19ac70b5a3b2d9a61510fd730b1d195ea806c2868db4a161"))
    (1696263, uint256S("1f910f90643db2a8844b504a7e37a5f10a2ce7545aef2689434120da1699ad61"))
    (1715987, uint256S("ec87def48c1d15dc950b7f5414328ed3aff471d8bad598b03708395dfacd40a2"))
    (1735711, uint256S("af73c2ab6d1caf3b1b622c284cd9fd67a6959baae12530c3fbe951750de8bdad"))
    (1755435, uint256S("207ebafa94ba66ff8dffd57ece2fa186706cad4d732e6f779677e388f658c018"))
    (1775159, uint256S("47cc57cf7fff4e0541f2b8c99c725a15e691c99b45666ba62a0068046d7bc515"))
    (1794883, uint256S("b41c2ad50da3f80c38c96afeb87fbd5ba853f7570eb701b6570c9fab6e8e02d0"))
    (1814607, uint256S("e1e2e5370c4bd5d0cdda790a54c65d2cf7f013d08b95933040512a0ca429fa79"))
    (1834331, uint256S("a6ca8d1687d22ab00960c14bcd5f2fab11f91b213e319b9243129f05fe0214eb"))
    (1854055, uint256S("7732d1402afb4cdc74d901de96288e0954362358f7bf4ab24e46178158d517ba"))
    (1873779, uint256S("8b37f19ef4d6c6cb03735fe5eb185c7397b689eadc68e2f4989dedfe7241f2c5"))
    (1893503, uint256S("0777ca3aafd8c59e5c8b69a0f5055accc5b96be57a9a9fbe98958c06eb0b9ff2"))
    (1913227, uint256S("1f38343641b59680f43e29eff85835715e3cc4d8d93b157adb336a51ac1581b1"))
    (1932951, uint256S("842f42cba21cf5f25bca22523f398c6d9727cca370f42ed822fbe3c37ff7a9b2"))
    (1952675, uint256S("e5d122889e95ff2c276f25ae8991b55e868746954b84aab280ca19f346d625b7"))
    (1972401, uint256S("4855beeb5bd114f906b1457354b0e970b4a0b5e2cb6a29114e8d149d54428289"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683458265, // * UNIX timestamp of last checkpoint block
    4602745,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2816        // * estimated number of transactions per day after checkpoint
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

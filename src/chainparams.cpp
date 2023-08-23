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
    const char* pszTimestamp = "Sometimes you hit the jackpot and sometimes the jackpot hits you";
    const CScript genesisOutputScript = CScript() << ParseHex("0478505c5bc438e08c0c8de26a661bc5a4453378d0b149fbf17cb3e1499b1d3e552fe5faaa253673c5349b461bd964a2ee860c114e9d2b9fdb0328f37ed356ed54") << OP_CHECKSIG;
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
    (0, uint256S("00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"))
    (13092, uint256S("f229f2b08558fda694c91279856b1b5643755e247e014a922604bdb46da89a15"))
    (26185, uint256S("24206f3812e6bfb5d8ca954e2ff50efacaeab555ca9c4da05417d09969f0c99a"))
    (39278, uint256S("8b48ce7873a25df2d867b60ef8ef63fc4f75886b9a21ef3e4ca5990f7c43c5d0"))
    (52371, uint256S("594c5631a63f66ba4261c3639ef49b42757ddc818c8e1813f26829da08cf6002"))
    (65464, uint256S("d0f9a4f3d164eaf449e6fbeb807d98bbfed9324b1b6302f5a10fb215b05475a5"))
    (78557, uint256S("6c1ff3a64bcc0ac890d788a9f97ed2e5df7215786e00cf89435c2449e007cc2b"))
    (91650, uint256S("6d8b3bd819b791006bfde3dfbb444153be8e69ce5eca7e8512f68a2cd4f86da8"))
    (104743, uint256S("b391ef9da064111b8ac97b1cd782eedeedc1be1a541d69e7e2aff1798bf61a7c"))
    (117836, uint256S("4ce9c436a18502d4b47865bb8c0ac46c9452fef2a9f1c1005de9e1d3985c3317"))
    (130929, uint256S("7bed3b766b52af94e7a60f5720c6489a7a2c57f8e37330d1657f14c8edae2a66"))
    (144022, uint256S("af6a1efd838b3cd57fc3e16a07ad3af7e1607940516a374a89227955523c49a9"))
    (157115, uint256S("df2e6f8f75219a15ff343e6a09d5fb116409346b6e0d95ebde39bb43910ae7fb"))
    (170208, uint256S("91220643459370ec66ada5a6d3780574a98a9fdb08554b9547dae2972d2b534a"))
    (183301, uint256S("138b51d2d7873b05d0d1101c51b48b6c197437896c5a775336f2bdae52a23e03"))
    (196394, uint256S("7f5f55e91a08c2095a03b0af74486e6673a5ebe660063ddedba2671e542edea9"))
    (209487, uint256S("073180d5ca52023fef1e7f85401c0910d83ea95fd843ca95ded5b7e4893cb605"))
    (222580, uint256S("7697b9920ac0b923daf493bd5757cb4d4f58a47cbd7a00f16c98556f6dbd7cad"))
    (235673, uint256S("b3a80a84c39ff81e960978d86c8ad7a3d29bf35f3ed2fe25956e40237937c124"))
    (248766, uint256S("97c4e658feba1669d262c7d3e515167c9b0eb2feb9272ec99b3117c1a1eacdcc"))
    (261859, uint256S("5ed512a3035d2bde0047b4215d149dad6e325db0a71592b806594575420ad5fa"))
    (274952, uint256S("83e505794bb78d7ce0e3422d8bd11926b6b1dd97abc683e69e0ee16c8708b69b"))
    (288045, uint256S("87ba1fa25ce3819a278481a8958bc3ac5a8a45d80a1e7aec47d0e195dce5658d"))
    (301138, uint256S("cf5b6692de51067c63bfb567c7ca5419ad52ed2c8fe888d968375a85cd95f355"))
    (314231, uint256S("cb051905310dc489f5dcccdddb61415add4c9369a5925bf6680fcf5423e7e0e7"))
    (327324, uint256S("65e3f814fe03d7f935402b42ca7598ba198d265377b6094fc1868823c6f966b3"))
    (340417, uint256S("e873023f5b41288d2a5ed0f0920c80186b40c99c18f6c8d19039629631c99be3"))
    (353510, uint256S("637188ec371ba8fba55a77c705d0c7cb54f9dfcdebd5675f02c313a60fc0b0bf"))
    (366603, uint256S("269d10f0abfebda1d80992ecb97a5475ccec8c4912c23099588cef1f37707ae5"))
    (379696, uint256S("baf85f5015e48f723459774463d9d0fbf73ade6d6d374489889e328c4e706423"))
    (392789, uint256S("2581d21ef827f1409fea9de1f31f567546d19808be60cc51301e04cd7d90b729"))
    (405882, uint256S("5ebbd996ff8703131a70e39ddbe2df1c5feb09f7e310fa65b1c7ac48f3c4a6ca"))
    (418975, uint256S("25b654a03f7b7ae613223d3942319dd76f834ec05e86a7a44ef1d5c2956a982e"))
    (432068, uint256S("5e0fb9f9f18b5f32f850567770b9a22e22f5543e8dd88e4c610ba6aec06f7762"))
    (445161, uint256S("393828ab4fead3c636283bb54adf1656d67a90cd4823d75a2d9ed336cc18b518"))
    (458254, uint256S("ea95d2b3ab6036fae5bf33cdb432b5fd827d8cf92994e2e479dca3a890898a52"))
    (471347, uint256S("014944b7bde57f0e37bb9f8fc528840a056ace3d31e9b363e86f179e46d711f3"))
    (484440, uint256S("5a17d9be29d5005ca0dc3c8b7df9a804c38f1837b117726c49caedec581a5506"))
    (497533, uint256S("aaabb36c1070a0408471eedbba1f1256e1d210d60ffd5342d8becf79b3ae6fa4"))
    (510626, uint256S("1eddccb62fae5dc0f7b8aaa44e3a682a0dbcd7569cee09df5c5a96f04f291a59"))
    (523719, uint256S("c1aa81ae4de040b647572f8f955ae811baeb02ecac7b2f24469843abf16a7a45"))
    (536812, uint256S("fcf4d5042844db7714f11651b8ec58a0f0fb9e776aed6129a37756bdac3f9c15"))
    (549905, uint256S("5d30fb30e2e434a3b70a45e7acfac449602d8f906f169aaf4b65f88aff168e64"))
    (562998, uint256S("e1850ab3680b08f5de0f2f2b9a4120b702074611e7753996c83eb1cd25886e6d"))
    (576091, uint256S("9fb3d78cd898b881448b21d40a004a4353e39a524b95a297e7e5191f8674b6fa"))
    (589184, uint256S("62b886b33c66e947c094bb878ee46a59f1847733ad7c8a7f18c29df79d3a33d1"))
    (602277, uint256S("022185e1a19f140a1712df4d21899bbcb6f6a055b9b03e6230d25a2158820c84"))
    (615370, uint256S("21e5337e91744777c85b0ab5092a5d4d5828fae15fd43a5ae22aeb7ed3417728"))
    (628463, uint256S("899d8d7454424f588762c539bd7620b832072d28f6da15f896d7387b7a6ed6e3"))
    (641556, uint256S("99071374227a1277fc52c7c107c220dc714d5fc656369a81d60aaefca803f794"))
    (654649, uint256S("b9f1251357838472c2c66f409c26a352b0a5d45ab137542fd2f39937944e109b"))
    (667742, uint256S("dbaccf4250392c712e1540f5407247cc8b0831ab7fa8da8d92ef027dc8361ef6"))
    (680835, uint256S("7b8210acd227d84de4825e44395b9ede1c7bbaa5ecade2a27b10403d4f7f3fed"))
    (693928, uint256S("be17ea8c2d88cc188b42117ad9f1762be33cb3a5e3bffdd036d285bc3d75d0ef"))
    (707021, uint256S("60801da2a078dbfbbb7b84a5473f1fd4ee9fece53ccd8ae699bec271393233f4"))
    (720114, uint256S("f3dcbba3447848565466e74c22889c5fc24dc1b59ab6fd7e37a60d51504ae485"))
    (733207, uint256S("ea5361e725fd61171561e2732b0db036bb598d9950f42d3bef9da64f2b7e17fd"))
    (746300, uint256S("588cf8afd49f0b04eeb4b22aa71513e42cd806333193f98485e95a3c22d07fe9"))
    (759393, uint256S("3b06b394c45cb4e69df0f76391d04943dd4431c59f06cf2b538cb5f7138208f2"))
    (772486, uint256S("771356297d68234bdcfb0f156a2a298b76ece1045d79e85272d5ce75c2547374"))
    (785579, uint256S("529dd00575ed16dd21b1bf4f7784e3a1c7a9f2ec3e304bfdd21f27d04a8e34fc"))
    (798672, uint256S("e0939f0aa5776e674b568d9349530d937250bdaa54e758e8f37be5b3329d4c74"))
    (811765, uint256S("1c585d684fff56d8724a216b280e534dd2fcef28f02de9662c662fe393c22e6d"))
    (824858, uint256S("faaa21d456d9bd418319b0971490b24e573d27c44029044265a03123b785abd2"))
    (837951, uint256S("ba1d013b633d6101aaa715c2a6248436b9a8bf50bc692b7bd47ada8c39d0390d"))
    (851044, uint256S("3a7063ec76ead203011236f1208dd1af85ec192915be645f096f93b265b20a52"))
    (864137, uint256S("68de7cde2551aede7f0c6775080994fa3507b1bd2e8f14ac92c4bf01ff0e0d01"))
    (877230, uint256S("4ee6c5a7078ba9851c1a49b69dac04e399081c908b31931ade2e53ef7f53dc54"))
    (890323, uint256S("e7640bda8863be8f58a777e41932396ee0a1651a6fd8fbad3a0b915695c0e47c"))
    (903416, uint256S("c7ce572a0757264331d2b69d7f78f957671f3ebf710993852cc7341dadcb4df7"))
    (916509, uint256S("5938ce8ff1acb22bd3b4db070a87b7f833c19708342391bd9704ddae32507b2e"))
    (929602, uint256S("c3dfb06a63ed2a051b2f9b7d2707391d230c8569f2c83e5aca939edce7f72c88"))
    (942695, uint256S("51fe45c18982b5290b60d31779f13005d4648a87cce77c3a71feffa15c3b5c03"))
    (955788, uint256S("433417d9dd72c458cb27fcb7d7008aec477c23674c3e1ea9a7ce16e46aab2a7a"))
    (968881, uint256S("b014bb4795d21d86ee500d5fbbf03984d2da900a3ebe94be058cd63e1737c035"))
    (981974, uint256S("0a1120665c1bf9931c9cfcab1cde57afe25ef976ed35c827ada432b8387da3a4"))
    (995067, uint256S("809fb84cc4184682bddeeeddfed7d71f173875830ab039c389280d97ce810c4f"))
    (1008160, uint256S("0e405d9086b43b72b3840e21ee41b9d60105d5cfd90e204778ac6d58f9041b23"))
    (1021253, uint256S("9aef4fc6e57581db40b73cd36dabda837338d120a145f471c7ca0cb3f362802e"))
    (1034346, uint256S("d8122084f8a6027662104caebf7ec3fc658776e00c246ee64aef1660517bb1b1"))
    (1047439, uint256S("2ff0d29b0ef91a3d0ccc1dd3cdd7a66d6c8caf08e025d7de3b96102888a1bc6c"))
    (1060532, uint256S("4d68f884984fe7b207579310e707262a4bf61db83cb4849996a6e9a3bbc35ad5"))
    (1073625, uint256S("93563a13423a30549ffe3a4fe81dd90f1fe23712dc9252a9a4b7ad1b71a07fbd"))
    (1086718, uint256S("b826947411e705dbc44a578a331972327b33ae10b1b70458a719aff912c10d3d"))
    (1099811, uint256S("8656f176c069a17614cf6cb1f7a0c93c31aab113d66a1839e516da9a8f52d740"))
    (1112904, uint256S("a8dfe6784bf4180b06619b64c0af98fb948ae534ce6135d198bf4a6c3e4685d4"))
    (1125997, uint256S("d00bba6602a97be9547df86699fcca6246753d8733595d393705ffe4c40be85d"))
    (1139090, uint256S("91854b09281e068e2ef5631bc4e74e021e719296bb36c434e3b4fd84f94faa43"))
    (1152183, uint256S("f7eb627db0b7c4c4c9b696631f3cdd15fdfc150dcf42bfab6cc7140e47707af3"))
    (1165276, uint256S("d9e1ac23265f81839b0dc076cb89bed41150c329426380d8d507867a422e5cd6"))
    (1178369, uint256S("7e5097784aae567459fa21c2b5c1d0eb88822aeb70128b00d0be74688f7a90d5"))
    (1191462, uint256S("e8ad58a6feffa50e9d0acd63cd37d5e7bb2156956a7828e87df7f7aacafeda1b"))
    (1204555, uint256S("2a49f5a01ec0819828c262a341f5ddd78d4ed072116a3f77f19e17a935ff3864"))
    (1217648, uint256S("d9b4fb5964ec822021083197c7804b8d6b0c7088d55fbbfe5c7d567a12991942"))
    (1230741, uint256S("5ce4defbd2dc4f3d19667699f993a03878790b0f562e78d6125a40fc17a27754"))
    (1243834, uint256S("b50b3c5885520c959919c0477206ef028e4de665e520b33e32dfcc81041dd8b6"))
    (1256927, uint256S("e69d4d7abddf27c6f68ce0020c6f5f403b498ac82c9436e5a9f8871a00667a9f"))
    (1270020, uint256S("83ea945eca317e033bf0cad2e9b471e2c1e25c6ea911928b8ac291d3d7fc5af7"))
    (1283113, uint256S("0e15112e07be475597172c5b7fdbc1744845b831f28d7503750ae90758554dc9"))
    (1296206, uint256S("3042b406122ae08f3e80190552fae9c025ff5ec48fab035d14dd11cb21871041"))
    (1309299, uint256S("06efe8eb13b77d87bfe8e1f85f2035bbffc53c1a4c9fa68cb1e9e59c6d6a13e3"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692821760, // * UNIX timestamp of last checkpoint block
    2943279,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2814        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1612360301, 882189, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000366a6d89ece72f3481f4c81e813f17c4512d2cce519c9d869d8eaebf71d"));
        assert(genesis.hashMerkleRoot == uint256S("0xad9cdf0829529533d9ebcda4f6981195860fdc01c7f6d3f14b847695835fc872"));

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

        consensus.nMintHeight = 550001;
        consensus.nMintValue = 34000000 * COIN;
        consensus.sMintAddress = "7BicbhE37YhQwmCMmG6qeQkK4USPzV29Dy";

        consensus.nMintHeight2 = 947500;
        consensus.nMintValue2 = 23000000 * COIN;
        consensus.sMintAddress2 = "7FTJn1XZXi7ods8S3fELd4T4YMXVn3remk";

        // spork keys
        consensus.strSporkPubKey = "0371d4e47e0ab43865206e9df7c065d6c68471b154bab3815d99f8380d46c7015f";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "7XXXXXXXXXXXXXXXXXXXXXXXXXXXaqpZch", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 235001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1bfd90165e662b99293bbe05a321377d0dc2f2bcf36d52e5abed63c4b006ec6b");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("690164ed39d09a8c62a03f1a17d9e14630094cf8e4a5015f58ad4361af3b7eee");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c17d7ad9fdc95b64409efd6c52054c8d547e72f0e3b5059c7148cbf345057768");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("8f53cb83a9d6dc495410377428e2c85cd80367456d55a82d64bbec5b0960286b");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("7a8aa7d86ebf47008da5b39ba6eb07c380a6638a85d1a632de326a4f5238cc36");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("cb863ebd9d14c47dd733cd9a90b47e79a7ab82250a60fa6009eeaabf89778abb");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("b99924befe2810ac0a613e3c8b43c3d423b870ca3710cd81ab5f8f95ee316d40");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc8;
        pchMessageStart[1] = 0x7b;
        pchMessageStart[2] = 0x86;
        pchMessageStart[3] = 0x77;
        nDefaultPort = 17771;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.777coin.win"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.777coin.win"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.777coin.win"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 15); // 7
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 43);  // J
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x73).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x41).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
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
        nDefaultPort = 27771;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed.fuzzbawls.pw", true));
        vSeeds.push_back(CDNSSeedData("fuzzbawls.pw", "pivx-testnet.seed2.fuzzbawls.pw", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet jackpot addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet jackpot script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet jackpot BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet jackpot BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // jackpot starting difficulty is 1 / 2^12
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
        nDefaultPort = 37771;

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

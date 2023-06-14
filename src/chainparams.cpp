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
    const char* pszTimestamp = "13/Sep/2019 The EskaCoin Launched, It is fantastic!";
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
    (0, uint256S("0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"))
    (19101, uint256S("dc706cb9d96491893aa101abf131f8473302f1288da8010c5c9addba28897d39"))
    (38203, uint256S("e0d2ba0c834009d6658ce573131c838bbaa550f9897181daf2dd5fa19a1ea66c"))
    (57305, uint256S("ede20e4e58eb4cd42929b2bacd98f882e2f3afac4f2d4f958513ac4e49aa87d9"))
    (76407, uint256S("f45109b7f4e774732036acb16feb3ead63eee6aa8e18863e7a03c0b3c95be9e0"))
    (95509, uint256S("bc781493cded8b30b30b0fc7f43abe304f254b5d26ea35790a751494609445dd"))
    (114611, uint256S("345f6015d6ac0e9aed4a83791c0a7b57eeea515ac51002a7c9311f63877644e3"))
    (133713, uint256S("51acc15b9ddbab574b2d4dd9183a2e4dbacbacf36f6e9ae83a4c53c70c6b8847"))
    (152815, uint256S("06af4239b0518e6ca59e805ee50d7c21e47a950e41b13585a3e126e69d10cb54"))
    (171917, uint256S("ad45ad845f390a3bd327f7d1be43733d7727f6551aaaf87bc8f4dfd8c1080832"))
    (191019, uint256S("db07480f399f90184d554c4a26852a392ccbae802ea2eaeee9bfd8fa8835b8c3"))
    (210121, uint256S("68d0d9d9136bee39618ac66321c99310516192a970629877c9c67ea5d721ee41"))
    (229223, uint256S("8910b0c07882fc1a4557e836176019b5789d0e05d95d95a52a418cf5e00fbbae"))
    (248325, uint256S("f7cb0d43fa1f79d9cc0c520acb287a23617b3cd69cb697927784fd8e391b2dcb"))
    (267427, uint256S("03863e2081cc65c03aab28a036c7c1ff5665a25b57226b64e2f41cce9f881c65"))
    (286529, uint256S("2ddde0d1eafd3cc8d2fc7bde43464c079b1ca760c1495c013d093659910a8026"))
    (305631, uint256S("9e214860d45df9d004ada75608cd9d9dc545b3109c76979c673e8b63cbce7e33"))
    (324733, uint256S("e642ff9a483bd32cfbfb8e1c489832c768549ed8ca95f92008b539f55e389254"))
    (343835, uint256S("4ed965bf2f82c321e3fbb7c6f83820a3685cbacc59cfe216349e057d366c5681"))
    (362937, uint256S("36876aa41e96107057e6523d7b0ff5aead2ddf1ff578ecc57a7ca4962907cd53"))
    (382039, uint256S("0188a1261f010eb7048091c63455bb8b1ef4c20314547ca14020a7b299adc067"))
    (401141, uint256S("99bd778174379841eb2aed80f1f39949e564581204986a4dcf0a182135fb7440"))
    (420243, uint256S("5dffe2c15d823576e02b30a82e9713e877f247b2b843878585382520e35011eb"))
    (439345, uint256S("164cd66795fb3631abeb845411f1ca10f94b393a51101b443885353dad7a8344"))
    (458447, uint256S("e7b53a0c2b46bdf549ad12166f6796c35ccd384bb0884d46ec077fe6f599e361"))
    (477549, uint256S("aeeeda3f2d8a4ca9763e5ef7605ae718f5fde547c80bc8ff5b120684dc75ef7e"))
    (496651, uint256S("af2e901f5348b48c7a96a119c10f84af7e69739a1129da0acde398416b163db3"))
    (515753, uint256S("c79b7dcd85c63b7116070becef9ec8f425316752b21c97a8b8c42e88236455f8"))
    (534855, uint256S("7e603602f46f7b731dab2fa32c6665211049ce05b3cf7b52d614c51bec956526"))
    (553957, uint256S("2678cdb56e0fc8721c1773e4553ac280ec2c61cc13349dff4745feaae005818b"))
    (573059, uint256S("d6db07eacaef8fea0813bf52d677f88c0e334f89430b7824a15ff09a37a17ac9"))
    (592161, uint256S("02a78ec0a4f61ed551e90d3498ca06633645162a132ae3c1d4fde279977f7b86"))
    (611263, uint256S("c8fd061b7ae5362e356cb4e6ad1d69c1458bcb15716e039dcda2c6918604db71"))
    (630365, uint256S("4e2406e4458c62af8dba1623759e1099742513393f6949a6616b1e6950dce23c"))
    (649467, uint256S("61b0f25464bca7336d6d4fa32067afa52fdac5db22268f435326da3ed84bed5c"))
    (668569, uint256S("ac1e56498bf7652c3682572223f9cb814f4f74edc81cc734854ad98a293134d5"))
    (687671, uint256S("c949115e23eb1ae2039f5c31bf5b96c50c7cda4d32d9bc355679b57dd474684b"))
    (706773, uint256S("4e243d6405cb8df3d37eba656777033a28464fb4b72f5b88469a69e15ef1e048"))
    (725875, uint256S("dfb56d976e070d2e704bce074a24695d84e391d71dc982368085893d5a861481"))
    (744977, uint256S("dfc857ecbf4e08113b9d8add1ff4b799a029db65ef5380d28e86281d16d9bff4"))
    (764079, uint256S("5b34c33cbbb5d7c1ad5b96712abac5a512de9d004b259b87417a41067cfca0c4"))
    (783181, uint256S("d5af13a96eeea23c1673a5901ec6f7d9890564164f64907bdbff6b08946fb3ca"))
    (802283, uint256S("e395b80407ed2fc92dddd9634761fd782199ed9e0aa83ac02fad26fa0ca351cf"))
    (821385, uint256S("372a5d1ecfefbb58390f7c222cad00bdb383955337cc4a518f153da1ec6ed9fc"))
    (840487, uint256S("66752410d741535fca007ddd596a56d0ac3143e0eca58926a16c5309ca867526"))
    (859589, uint256S("fd7056991cf9c8a3e93424d413a6bf7dd57d8534b8ab4344a0ddb2fb8e58d887"))
    (878691, uint256S("a6380b4ce0c954c68aeb1d45c73cfec8d571fd9f2c0dd0b44b2263a97a593111"))
    (897793, uint256S("630916a19ef62ae2974e487fbad97a3998c2bc80da10689e9aee8caf160b9c6e"))
    (916895, uint256S("277261993f11889ba6bfce8575c1f5c027dcb32c8bf7e111530b8847e569172d"))
    (935997, uint256S("66808f099a27f5823281ca6472248a2d91cd411e94e238a9d1d2eef12e7b95f6"))
    (955099, uint256S("33178191592f0300a9f5c9d47d6af2f88ca32c775f86a9bbaf9bb5e629212e03"))
    (974201, uint256S("fb61f2152ddaf604c0fe0c179359330297ec5db05f36150f51e4ef3304aa8a38"))
    (993303, uint256S("3f605c2f3382d59d3cda157128fc91792b08b08fd0c040970eac8d4bdff8a91d"))
    (1012405, uint256S("bc20ee4593c7363ae116b71be1300a1e6050e250e2d485c517acf5e6770eb4a2"))
    (1031507, uint256S("86056a01fac833af0740c703f0efd726e745b343fa8731f2f74b1367ae2d93ff"))
    (1050609, uint256S("566f68c6a906e71e0dad87c289eefb04f9b3d1ef07eeb4e4bab1a8f5a991ec75"))
    (1069711, uint256S("80871927671dda45a3b96fccf3c0ee25d857365158abe031d42a01a48c61af34"))
    (1088813, uint256S("0c530e6d329711c3a6075c8c86fb75d3cbdf9815795b317e770b7494c15aa812"))
    (1107915, uint256S("ac621ce8194ba689f7491ef79a86b1e5e5d73b0a8db623f2cd405192e3818076"))
    (1127017, uint256S("be4580f8739926fe768a25d7b802b9668d03f532ead9f10469c161b0ef025f2c"))
    (1146119, uint256S("0528aaa502320c21bf72a0c350bbf5d1c56a8724b502e0c5fd2834664f3a39a2"))
    (1165221, uint256S("fe290fd93fea2539772f75ffd77f1df7672cad95e3ed6b2eae38a04852431f6c"))
    (1184323, uint256S("14caf42e80aace3476018d8ed00a5065ef7195e6f4e0fa2f86ead67ad177e208"))
    (1203425, uint256S("9bf6521ea53c894f33cd92c1938177b8df104a68ee0bb9223fef6d1cdf93a839"))
    (1222527, uint256S("72dc4c61e6b5bd02d632e053f462d0bcd05de69d09b73c02991e8f33dffde8b6"))
    (1241629, uint256S("13f26a4f9a37b1cb202e7f34cab0f7044c0e516020e0915a1b6008d372295142"))
    (1260731, uint256S("ecf4f6e6c1772c5b4d370616971cec46c37189774da170e0c2b4b1d8229cfdce"))
    (1279833, uint256S("dbed16867ba024e10d1b71ba4d42c68c8aea0d58e10f05bc52485a0af95e491c"))
    (1298935, uint256S("d2438626ba97aa23c1004a964939a379bddc768a61082de09c8ef02f00bdb930"))
    (1318037, uint256S("f6de7dd26e793dd1d67a1926a5037d179b075abfcf39e87afd56acef4fbe7045"))
    (1337139, uint256S("8a8595232677368a363639a3b00d55a4bb8597cbcfeecf1400b094173fe751cc"))
    (1356241, uint256S("2abfe8a6151a9cd0d328fa3e1d5daf13485e7efec33f369aeb4937fe62ab55f0"))
    (1375343, uint256S("60a3774bd916f4cc4cbb118def9849c8cf1b51cec87fd9b572116aef0e20e24e"))
    (1394445, uint256S("13a0bf3405a5b21bf30b9b9cb8bfc185fc70429076216e7a99ccb287e97de543"))
    (1413547, uint256S("9ff273c8b9fa5888b0026dcff8f774c8db4125f5bf553f6475b1c3f78664584e"))
    (1432649, uint256S("acf1808ac89cafef0df80d8c33f46337af6f6b0ea16e0fd0676b0677cdefa843"))
    (1451751, uint256S("f568bf04d432df20a4f4cb20fb3215c3ed865e4bbaea06a05c329881f1962394"))
    (1470853, uint256S("d615b986f35aa6c23239affea022ed3645a78cd39d7e112b0acedfc68a4c28f1"))
    (1489955, uint256S("8cfeac2c6f059a499390f83959d2419c1ba032b75332b41d53e8e56f5c3c0677"))
    (1509057, uint256S("4a7b18952a0c67e3afa3737704621153c8264cfad5508eeba4de00fdd28b9eed"))
    (1528159, uint256S("a089aa7811f7a9de1e5904e594350308dc056d415f9837b0b413ae9627e12a6a"))
    (1547261, uint256S("522e38957b513fc0d603751e625878f08d4c931bf155c5aeea27393db5043fc6"))
    (1566363, uint256S("32ee2ef22ebe2b0004eb6594b8b57e6d920e8590f3be96639bc2e43154a5f826"))
    (1585465, uint256S("8875be9de92fa681d77d748f2b32769477706c4c4f034b14a8d4dbe0c90809ee"))
    (1604567, uint256S("127daafe57d88276b816fec150b095408d13558cf657238c68cc7bca6110cd97"))
    (1623669, uint256S("b42cfcaa77250bda88b0452a1656b7f3ad8ce91bded117c1489a2e24852703cd"))
    (1642771, uint256S("4c8882e503656583f9c7cb31000e0b5b5fb942fa458350e2c934baf05bfcd4f4"))
    (1661873, uint256S("f212a18a6330fb1ed3492125d2b5402a16e068c01708e893c0b176f936ff70b0"))
    (1680975, uint256S("4fd5df7b685286ba09b78ae9332025c1b22df784a9f554d413afbaaef06429b3"))
    (1700077, uint256S("daeb9c8b54df59da629885b087acf2e62767c2168f880fe215279a77b4b4934e"))
    (1719179, uint256S("7be6e6a77a3f04bc80828e7c639b9cb9131cd7034fc2c747ffe0323bef0df712"))
    (1738281, uint256S("11145a564c4e2efae2bc561218584d307836c6174f23259bfd004e8dcf6148ac"))
    (1757383, uint256S("7ff7d58fa620ed4987ba9140c6624a897fb5f088c21c8f2ca2716ce5f6b4aae3"))
    (1776485, uint256S("fc65e9fccc1e3378636197fee0793784d8b7521d37788519cbffebbffe4e73c3"))
    (1795587, uint256S("2794d9872d44f8d92a804ad690383ac7e40a17c3c47b0bd43749319d01d7bb99"))
    (1814689, uint256S("43aa84995a51a936875be83f90a5527a9bbd811cc87b26ec272805fa063b2267"))
    (1833791, uint256S("93f01eb1ca693c8f71648caaeb4c973ac46430a7206ab4b699d023724d018fa2"))
    (1852893, uint256S("398bc484883bd468f298795b41040919d4442a61e0ccefbb15eee31a76484ae7"))
    (1871995, uint256S("bf1535589b801fc5fb07e4d5d2d18347b636a10d2b13cf16ce3771aa9238536f"))
    (1891097, uint256S("53508a9b0a036ba6468b32c4d599ea5bb81ad35863cdaec4dcd0095fa1b5556c"))
    (1910199, uint256S("96d3feb1bf0a4d8356313af3d00e697cf0815b18afee0e01baac505c4c3c8eb2"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686699360, // * UNIX timestamp of last checkpoint block
    4477697,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2828        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1568452814, 7414, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"));
        assert(genesis.hashMerkleRoot == uint256S("0x036399fee1c5e4dcfa9c8c4f2458899d6de3a1ba0df04e77b7ac10bd09847b12"));

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
        consensus.strSporkPubKey = "02aeefc7f24b3919ff05a7d2661aefba6c37ca77c263a20e8516dea630fa74e9bb";
        consensus.strSporkPubKeyOld = "043B44A0D5F6BFA822208E19096A6F71A144EA1034A5ABB99E458DF1463CF98E72FEA9E5C5038EF7716765D248DAA709A23746606AF41CAC59DC071E89624C9FA2";
        consensus.nTime_EnforceNewSporkKey = 1626393600;
        consensus.nTime_RejectOldSporkKey = 1626480000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "EbURNXXXXXXXXXXXXXXXXXXXXXXXYdqMFj", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 252;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 930001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 300;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 930101;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 930201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 930301;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 930401;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("00000d59619662288595b3e38ab67f243e60fa47be9b8bc49ee36d835cf1d2b1");
        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("4f223b064bf7ec695c08bb41701ac4e59cea14169e86a2c5f802c8c6c29508f5");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0a10b03f191d41ea4d7c8f2170b2b5a57a193b77270e83185c60d0ab98ea82ec");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("6124f4600579296b9dd3973c13b6a24ff84aa0fd06e66b35356cb229eab8a6d1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("aa274bbdbea34da289250e73078a5912e6edf6e93977bd8474be1527993ca09a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("537221a9b3179f9d95c4d84c6c28321fe7cc1d4a1cf2329e1dde87643ed39187");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("dc97bc8e643eaddf4b0b0726abf437f39ffc7df5eaa646957bf7b03bf817c5dc");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x1a;
        nDefaultPort = 14215;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed1", "seed1.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed5", "seed5.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed6", "seed6.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed7", "seed7.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed8", "seed8.eskacoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13); // 6
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 145);  // 2
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4D).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14216;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.eskacoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet eskacoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet eskacoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet eskacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14217;

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

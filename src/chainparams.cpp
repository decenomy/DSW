// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

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
    const char* pszTimestamp = "Soverain's blockchain #init";
    const CScript genesisOutputScript = CScript() << ParseHex("04dbc25a9a48add73d7f65d1ff4ae6a1fc80d2089fcdc78dc8e5088c6d27df962f393a07cad6fc632f6b891f5c81f970bf282679c39e581f856d6a94c9f814cc68") << OP_CHECKSIG;
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
    (0, uint256S("000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"))
    (29487, uint256S("cf895160d36e3ecc2bf5c244d2e495fa7d631a78b460370fce9786f46597d4be"))
    (58975, uint256S("9690b93e09345bedd0f9025f6dccf903f5cdac491d180f4a14419213333f35f6"))
    (88463, uint256S("2a598acb48b4407fe13fcc8918a84214b15bd171c80fa2d5c3b7046c44260245"))
    (117951, uint256S("30e8f1ec0946f68ae17383a0eef47b41b025f56cff555323b202017486e6f0db"))
    (147439, uint256S("3a660fcfdbccac4cf3cf4e3983461c16818cf0e1206589615fa3e787a4cafb39"))
    (176927, uint256S("115ee7b7d9ad80fb0f9257a1f24894734cc5020faf79a73461531136271ee9a7"))
    (206415, uint256S("51b3d170b669a55f01cedf3cdd876627b154056b359dee4992b54ac85aada3d6"))
    (235903, uint256S("d53b494b43270c7f825a31d9ca676e69db79eaf9674416cf27bb3f294aa7aa43"))
    (265391, uint256S("bfd04d2bdf882f75fb4a0a3233aef42278ea38b7a46c8cb5be715886dc9dda94"))
    (294879, uint256S("012ef665405475f9eb801cb594ff6e96705fe559135adfd10f90dab93be178d5"))
    (324367, uint256S("b6653347e9e93f1dde9cb004dd91683be1a33d096ae79a489db4933befebb8a3"))
    (353855, uint256S("947460de052992f06b0c79cc73b132dbb08bd9b4d80f2a124ac157a4bc0575f8"))
    (383343, uint256S("1ecc177464e78e0284a29f5b1604c6c0593e5be3e9e28b988591abc60da705f2"))
    (412831, uint256S("173d981f0d886a7e4e5e163356f752cfc94bea0c2166aec2840b4923f6a86944"))
    (442319, uint256S("e25058d17ea76d2e3f302d5acaef1bb173a2825be5ccbc66c2d14b913f9fe913"))
    (471807, uint256S("9df6e124f350b94c849310946e5108b6ba41edb732d2f684acca10295d6f601f"))
    (501295, uint256S("95eddb98ae10eeeb1da85f382c9c6a6762da64121155f508954aba7850eadacc"))
    (530783, uint256S("a1eac95be69f758c04bdd748986f63c07404b348d41c441fbe90c6de108e7bcb"))
    (560271, uint256S("76eeb26db28ec0ae6177b8e15f4737d386aa5a2d30c0e819f8010f89988e2d60"))
    (589759, uint256S("22ce55a7ac82fa5674a17bfce575a003d0c8a1746a78b3b7c04f6ca204da9ea9"))
    (619247, uint256S("c0a874541a0381efcccdd0a991b8e61cf053a5c9ffee5912911c6b9be7b3bcca"))
    (648735, uint256S("503f5247af14287a94a5f48a649857194bdd30c1db52391f065eb08263a9d908"))
    (678223, uint256S("c4e85feef22bab550d6b204203cb26f4900bd1c656010ecfdba02bfa2a9b585c"))
    (707711, uint256S("7a308d711a852b7cb5b3633713a58f6c0e609ca1e60093c563f091b591153913"))
    (737199, uint256S("2b82a03d7012b8688193c3e5f16245e247d50bb22ee3178ed09d2f8bda957c03"))
    (766687, uint256S("685f6956deab6ecc273d51f0785810e98238d6c516a45a088441c840c830813b"))
    (796175, uint256S("6366bfae7429d66093ff6fed3818ce29eabc1b80d5305b32ebba4a359d393d0e"))
    (825663, uint256S("a6126af207fc4610d70b6cf6f5b40ea9e0369f1c3d865c30957a1e7828d8ee7f"))
    (855151, uint256S("12668d30288e0f9b0aa25b4f1d10a59caa1e401fe1e3248d7dc27d24500885e8"))
    (884639, uint256S("0abc453bb7f0fcd28b86d4d8402c21b4cda3a4b6a1d0416df852ca727b4e9b9d"))
    (914127, uint256S("348bda656151951ec45656eb7c4cbbead198f27f816e29d36bf569ea19075176"))
    (943615, uint256S("20bdeb3e2b6b843807c7db531dd02c5d77b2a5ed4971ded92d26a3ea4474787c"))
    (973103, uint256S("860976ebaf3a3e2af06e51fb6e6cb73433a9f7fc84fcaef23da4e7d8b466ba84"))
    (1002591, uint256S("7c74ea196c715629545d5db6960d8baa5b5886c8fe61d427febc4c3f4f30c49a"))
    (1032079, uint256S("aa8f5a6e4405b982bf2a55bc18ae99e93e312d43832580b1b39a7f8c6493bbee"))
    (1061567, uint256S("f68c1344ab353af67a312a38056a48cd98b026855f13085ea49dee8f0aecb631"))
    (1091055, uint256S("bb0e65d08fa14e9000c8b5159dc12a0c428a5dbc3f89ea2713a0101e4ef76000"))
    (1120543, uint256S("074a3857663bc9ac4005a995e0092013b56e9c9e7cb47a0cfee6149b5fe80c20"))
    (1150031, uint256S("887532caae5b39c90e6171b69c606ac6726af9cbefb9733fe2b44ca2a097182d"))
    (1179519, uint256S("589fdfba527812c9b786f45af64d4599f966b5b4892e49822961d127d5c735b6"))
    (1209007, uint256S("7f53bb2a46a574b1739aaff698b2d8535af5aafd69416040945b346dc0930ccf"))
    (1238495, uint256S("5527ea30f5386f4e82b08dccf39490c43feb040b39acf433d116e945c72201c9"))
    (1267983, uint256S("ec7a709f734e6114e1c79b3e5d49b3367abb4d0d38582d2ce47041152d19ee96"))
    (1297471, uint256S("1ee9fb5002cc31c22de1b77ea8a8733b587041c6a15564573a0dc92e33881510"))
    (1326959, uint256S("65a5c8461b7ffb260eda5e4ed9c111c811a80f0e467a233516fc1401a8e435fc"))
    (1356447, uint256S("1281b9e4446c9e9602b88b423ed76e41de5aed00c0d310170b0480d7d1b4e55e"))
    (1385935, uint256S("7f7a0e1ef32aa152cf6914ded11f408c4a0dba3665c4cd46942b22bf2ffe3c5d"))
    (1415423, uint256S("4d8abf158986a82d8aa443a6126a3bf977780d2b08fa65ba7b72d0faaad4462a"))
    (1444911, uint256S("2f3ca6e17b4c9b17a56b1c5e089ee18c49c6dc07bc0430fc58d8431605ec167b"))
    (1474399, uint256S("4ecca934c41feeae1dae8624099337d10d4c1604d56e9377b44da6aa433e8fde"))
    (1503887, uint256S("c5f3ba4a3d4170322beb03c5ebf3b1a11c006a4df3baf0c645f8cea308976c07"))
    (1533375, uint256S("477a31edb16abe6dbfd103f005ac3618e6adaee545c227ef24713493ec12f3e7"))
    (1562863, uint256S("d656b6c19973937491bf3fbb2fc442243a80a59fed9f6906b66d3bc1f93fb0b9"))
    (1592351, uint256S("2d804fc7714883dbbd142324f6079006bd4df18ffefbab15dbfa93d62a84dafb"))
    (1621839, uint256S("adcf8bca0f696d6c18b46833ff55c56109c0d6b5b5e59c36f92f72b0035a86ce"))
    (1651327, uint256S("9a546b2fa80f68b08b4c7d3907df2fe92c2dfc0a699ebc84314fd8b968b8f7bc"))
    (1680815, uint256S("883bf3b417a6331e46a65183e4d98b08c88a69a3c82897bd7c60e3a1e1b151a5"))
    (1710303, uint256S("c472d7e4af0795c9af64dda2b4d52747f05d8e97a784e4f00c27c2ff653143e8"))
    (1739791, uint256S("6c5a5a193a6ad91b395666d1a4d4679ad35bef00b7c34fa26566ef807c07c8f8"))
    (1769279, uint256S("13bc41c09fa740c37238fec8bb920955e529a36172f648ddd822e3f8d2ab70fe"))
    (1798767, uint256S("1868bc9f58019a87c3372ba460ff076a05ee0c0daa3c60efa6be036633877317"))
    (1828255, uint256S("d2e23819eaef8470303268f0c2332b931d4e214768e73c85e4de13023229593d"))
    (1857743, uint256S("7637d7c18c562d1d769407fbbd86590a0509ba8f26d2bb23bbc59e5e20335aaf"))
    (1887231, uint256S("7d340507b85f998a85298d2349259781c757382ca5f9ad99fc4a33a1b9d170d8"))
    (1916719, uint256S("973642675252f257100f205e8212bf2661e41e4560dcecc463bfafe83ffe3a15"))
    (1946207, uint256S("04685ca40869999f7374cae4b82eadc4ee22d6ab1963c9c20906332feafaabeb"))
    (1975695, uint256S("00db711704c33554b3bdcc9087482f112defb2c754c56e9fa6cbb3cbafcd0d1e"))
    (2005183, uint256S("87d76eda32842adf45484cb6815e81c58f2609d872c35374c2f041d580ce1961"))
    (2034671, uint256S("98b1f434a39b40847ae127b6cdddcabd7a7c037a1d672862c64cbb0e1558867d"))
    (2064159, uint256S("2ddef4efbad9f8404808127273fa8b2a06e7b51d044e9cb4bc977117ed1b2a39"))
    (2093647, uint256S("887410b3dd747ffaa2fd123ec35e2c9b52e36643a9e2ace0a7a6f91493df2d37"))
    (2123135, uint256S("8bbe5fbbb30e12bf4a550e2df5699e332f61ba4f7694f11f94909e9366fc50b7"))
    (2152623, uint256S("b68a56a226600b6b9033e6e47598b8604927f87f0491909d245cb0f8bf5c426d"))
    (2182111, uint256S("82645c06606e1979c1b689212cafbb9b34b8f54f06a1527a60eafd54b64f4eca"))
    (2211599, uint256S("12e81de34a68e8e1e2b15489b0c756edb200b4ab6f63ca21e69cd5bcb0ca5519"))
    (2241087, uint256S("85ca0925bcb78d63772d456cb59fbf6f412a6e75b1bb9c00b0889b15ede313d0"))
    (2270575, uint256S("9bf598d9be91d230a0fad2ed185766634cc5ffff5a3f8cae8cdd6a6ee0a18957"))
    (2300063, uint256S("7f02800dbf36c672e16bbfd127a6dec2acee127b4fc9d9f6727ee6754be72376"))
    (2329551, uint256S("e675f98b59ee7cca2e59258384c3455480984b432243752616360d66c040a0ea"))
    (2359039, uint256S("9f79526fc8cbe624c4947430625cddae23f30c6eb34ebe9a7e250c703f3d1bd9"))
    (2388527, uint256S("d2188df1123a93992d11bc543ca9b1bbeebeeab33ca5a40c872f1ab12b3fd762"))
    (2418015, uint256S("f401ef0405457113c3673c1bf08ff29867e08cf21ed90891e081eb7cc666608d"))
    (2447503, uint256S("0b85520365646603f84ec833d4611777067fb868862bcab9d316893955fbe548"))
    (2476991, uint256S("029fcc893f88d2b172f6c3d494ddde535e0620c7d6ef7b48d645ebb685ddc49e"))
    (2506479, uint256S("76fadec0be8aa23dbfcf6ef1f91eb5519323cc1e2b9036279df74d2950731321"))
    (2535967, uint256S("fe8ca49b0f38f39858e384d4f562dc35a1b7b179b6e6eebbdc04ced89870a7e4"))
    (2565455, uint256S("6c3a44eac766c05e5bbd190e638da408ec9bdbe3476b12eff8209d21dd3aa57a"))
    (2594943, uint256S("021254d442d4f4f7329279443c8db2ca04d9b7865cf5b5fb3afac360d661a97f"))
    (2624431, uint256S("3a3bc3dd3ce89e1172740769d851cc2e26b7ecf236515107cf12d4de0324a02b"))
    (2653919, uint256S("ac1ce05d798c379d78dd82e4786f0e2d58e96b228104ba852ef39ebfe9645f68"))
    (2683407, uint256S("64a14a776cdaa922db527802bb0b85cdb1180e69d672a17dbbcff020445c5bf6"))
    (2712895, uint256S("d5122726c6e26c63cb715da5d060eb9a3b488596984b6cf2062a1214677a9ce9"))
    (2742383, uint256S("d29782720b0d948d480448fc236aeb3d200e4933d14c6fcc6d0851117804610e"))
    (2771871, uint256S("fdb6e576b60015d5f1a13f7c7cae2dd45c12f3fe57f9ae7667a9caf76e53e27e"))
    (2801359, uint256S("957c3e40d54a1953ab2d2887a44d5f3f78a71f2b1db6a5c69e9fd03ea61e17ab"))
    (2830847, uint256S("c18979746937b5209afed2a7c158a1922918e17059215fc8cc0f158c2da2e831"))
    (2860335, uint256S("53644a78528a231399a7a4cce31a7d410bc74fc7afa9e5815eaedbc60985399d"))
    (2889823, uint256S("3077e7c69fd13470cf9abc46966e84f8a8425b179d8f4530ba84ee544656dda3"))
    (2919311, uint256S("b075c256e1122ad6af56ae6cc3eacdd37e69f66b677c1c4a332c0166067f6123"))
    (2948799, uint256S("4f867fa67386649f29424ffe8a10a4e87d12edf9214eb83dc85e48cbaf3c2eaa"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683216255, // * UNIX timestamp of last checkpoint block
    7628672,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2820        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1563924366, 694507, 0x1e0fffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x79b352ef6aa3a1994a4c3d711e2d460385b53cce065611049a9a3c55e49b53e1"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 120;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 3 * 60 * 60; // 3h
        consensus.nStakeMinDepth = 120;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 20 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 30;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03061929edbb05141eef4ce4c9fc5c944c0ee67aaebcca5defaced677769bcc871";
        consensus.strSporkPubKeyOld = "04c90538206b7c4921e1e96e93e83dcc39f4351b997fc57934f5beddf916563497b99a315a772b626e072c9a903209c85172cec7052a54739dc392e27cda0d581f";
        consensus.nTime_EnforceNewSporkKey = 1625615999;
        consensus.nTime_RejectOldSporkKey = 1625788799;

        // burn addresses
        consensus.mBurnAddresses = {
           { "SXXXXXXXXXXXXXXXXXXXXXXXXXXXXFdBi4", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 2024001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("7aeb48ba5038096a31dba0b0a274236297eaab809ef24fe48d58eec821ebbffa");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("24975d012582291480d6604d469acd18b09acd87068f9f1a8309338c708dcda9");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("ea1031ff14a7c59c7df9291d347cbf1c72bb1a9b4aafbf3c215314a14aaeaae7");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("cbf48bacc3e1c8d843fe43be3baf7732c7ac4282f57e171980a2b50d18fb141f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("99552707f5e6815ac9c4bdf764817c21cd72dd095f44a1268c373bec8cb1648a");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("a538111ace7e59b635beac76a113d3a99592215f5063fae161a67bc1176e137d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x45;
        nDefaultPort = 18976;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.suvcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63); 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4C).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 10;
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
        consensus.nTargetSpacingV2 = 60;
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
        nDefaultPort = 18980;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.suvcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet suvereno addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet suvereno script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet suvereno BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nCoinbaseMaturityV2 = 80;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTargetSpacingV2 = 60;
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight          
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight       
            = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 18984;

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

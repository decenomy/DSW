// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
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
    (20215, uint256S("3c35fecd487b7232b2def4921527f8e8178a466f66a47a81542f5753cb344cb5"))
    (40431, uint256S("2366a3721e50923e2bc1421403a4876d15fd7098234709e329e24f8fb7588165"))
    (60647, uint256S("afcf07aab34c1b1ab770f8677a833f84b3a71096b40a7eed218341c860a17a08"))
    (80863, uint256S("7804d916d1fd28779995a4683abeab876c9d0c5280e7a02d0cb5119d3224fb76"))
    (101079, uint256S("5daf8423a8cd78fbddca7bc2e276ba5c96be360038c412d78539f25089ba0e2b"))
    (121295, uint256S("4c7c86a53d1d226fdf028e263bee6effaa86f90e5114f406567ac2e1e51c45e8"))
    (141511, uint256S("f2629dc5b2513068ebfaf7d9d2e38d709ab02abaaa260e91ef7f0db5d40bf3f9"))
    (161727, uint256S("8428f520210353748735ac6cea3f46f98f286c9a83fb6299c2ebc7e202526090"))
    (181943, uint256S("fadd4feb97b7d60847f2bb04e3fbdad2249e180691ed5fd1c79328d6a11af54d"))
    (202159, uint256S("6376e6ecd41661c35c9b1e3bd45cf984f6c333b5e49602bc24e88b5cedc676bb"))
    (222375, uint256S("e4dbf3fced5a90d684b8bae4c0fafa3f147e18f250d95c47d4cccbc760203906"))
    (242591, uint256S("298faa241d09261918e7e62761881bce0e8b5fa102089f97a810b676f25bd830"))
    (262807, uint256S("a21fcd519e6c3797da3d3f12024b9ded0d1be0e3b0320eab75a16d8fbb014141"))
    (283023, uint256S("6892053586283e25f7423dd925bfeb6bf7882f64c40ea5e376232fbaf237a121"))
    (303239, uint256S("51cf7797b7704f89ab6da0bd8bd6f6355ba8f1bd01d0f4f4893320305c9102f0"))
    (323455, uint256S("cb541975368f8c2ed758d186e4d54634cbf5c2fcc2b37682161aa82af5c76429"))
    (343671, uint256S("5e12c2878b3c5f24310ed71ca579da3c397d1dac66e9c691f23f6124735779c5"))
    (363887, uint256S("75fb093a5e2879e66db7d23693b55140ff14741814d69dd5a01f64fcb1c1b8c6"))
    (384103, uint256S("fbb50b680c354abb25ab3122cff47d1552bb0e58694fff7d0a741855d7460a2e"))
    (404319, uint256S("b6e78eb1019f265b9de3e9a8268181ea75f79d177dac32f33706a4366f00b66d"))
    (424535, uint256S("d623924eda4be99a9612d52daae1dd8c9ec6dc2070d2d7a73145b70a7e3fc976"))
    (444751, uint256S("e9c7a9a1b2b49e8cd8a5c5d548f56b506a6c9bee8d8f424826f55b8384d57380"))
    (464967, uint256S("09d4763e450c705471f4ea531e4adcbbc9b896c075802fa5d36e874b0b721bab"))
    (485183, uint256S("42369bb663ae7239d9b0576a47d4e86c26b4811b3e72ff76640b394808801cf0"))
    (505399, uint256S("dcf83b79294a0f4ea10fe1553aaf1cfaefc1adfbdb246ad967a60518ab06c49a"))
    (525615, uint256S("2ff044f581a4c79d03e446025dbcdc8b4fb3d4abc41c41acf59b0065d0e3df95"))
    (545831, uint256S("a9dbc5dff4833d76ba4822622a6af011703703b1310be218bb2dd394e7f45d29"))
    (566047, uint256S("165beb522f4a07c2b70837f6144f9966de6d2eba9af6cad110ab7f98586b4e13"))
    (586263, uint256S("cd3a02b9ffa3f80365074fca47587314a02e116f4b64328c4e6f57c8c5350544"))
    (606479, uint256S("42aff20f96aac7c579205de244a51c2eb239931ec5575135a21d5fa489d559de"))
    (626695, uint256S("5293fb5981cbea4892b67c614858257b111c56c51183f7c6da158b62d6a5c251"))
    (646911, uint256S("3a80847b6ba37948d82191f61ccffd031334bfde74dd5c420ef3d577e8c7af63"))
    (667127, uint256S("7ba9737336de5e7d25625064a72f023fae592893651d76498418b3dacdedab38"))
    (687343, uint256S("58327da12a8ba2741ee3f318dcad05d29382625ca731f158cf22bf3dfe0f1fe5"))
    (707559, uint256S("3c64df9ddddc4940fd5df33f64b00104358432f4938c86a710b608e628beac1f"))
    (727775, uint256S("8d903beed9ce6f262ba62d991eeabcd8e0ac12790fd13d88e072151142d122b0"))
    (747991, uint256S("1434ffb4121dc7c3af35ced5c363dbe923f371943cd4176c23532b602a20882d"))
    (768207, uint256S("037e95fa7094a1c8f30fe64c3ac37e4feb6ca8a87fd607ef48583584858d5a1b"))
    (788423, uint256S("129b556113d5b911bce5f70e065144fc0379f81552225b02cf0749aaf7b383b6"))
    (808639, uint256S("45afefd14ee1d14d35a3f70ff7310224df5bc89b44dbdcc75ebb1a2b8b677365"))
    (828855, uint256S("827bbe122b85e1b02c79d4e7b3d8e1717bfeaeed17e0e9d2d2b2ab2890f34805"))
    (849071, uint256S("a8a04b06bea6cba750fb8895faab9e7bbf0abacff8dd7b49a35576c112e5dbd3"))
    (869287, uint256S("67ee56b04006a52b0ea5b8ee662f02b9996acafae0e0413b241a5e2909e749ab"))
    (889503, uint256S("566c252fdebf1b672b3a0a46d2ca1f5c773ff14b1fd8a9a25b6ebd9c2ad7a914"))
    (909719, uint256S("703458030524b0cbdaab7a9c489c77ef3e409a3df23291863716ef8d0ee5df9a"))
    (929935, uint256S("d62276b9be4ba3c7481ef10d165773b1f6e89b0e513869a8e5f0d09a0010d974"))
    (950151, uint256S("cd6910c6b86186308f2da90c9a632e6bd45d630c4f1e9362db71ca7c34e89a7b"))
    (970367, uint256S("e5992962e0367893caa86541ce2deec17cf01c869eeaf190a57cd96df589fcb4"))
    (990583, uint256S("ab8c42a6750678f4a69440ca62c5175ae6b03bba2d6267c9f4892d1f5c32a9a1"))
    (1010799, uint256S("15de230d54260eafe3e0c36c1ff0530b255b2bf63203996f7c4eb92d98cd3882"))
    (1031015, uint256S("cf256291a1c53d7996a02b6e4e8e2f86452590257ed1747f3efee6fd549f1008"))
    (1051231, uint256S("82583b24e598ff36f813f0d0dd4786dcbcc0ebb64c97b791b4b04a56e4abb0e0"))
    (1071447, uint256S("5dcadb1b7a68166dd9224489cafe6c88f2dff4b7ad142783cc13adf79af7f708"))
    (1091663, uint256S("8bec32ddeb38c6772edb87c32977a0fcab49cb2241ddc6d8933227f2f6e9a759"))
    (1111879, uint256S("c945900f5b8390176205fd5db4d50e612fe48edd1eef430f2b6d9da13c7c927f"))
    (1132095, uint256S("58fc65c5f2efa980827dfe4ab3c3e900ec178fb53cc36ab241a327f56b8e2bb5"))
    (1152311, uint256S("83079f105450e609f2b6d3f42a53e92f2ec0b64e4527b0f684ca45a8453bfedc"))
    (1172527, uint256S("0f140fb7d42de54d1565805db1efe0ef470c4e547ae48112fb316e4f3b7a6967"))
    (1192743, uint256S("6b821fb3a8f348a1a34ae386a6b65f35bd6489a01bc94959a3ad41324916f91b"))
    (1212959, uint256S("828e9186ffb4d04ca9349823a3a8359f339ce414e21e4b48ec5c0639085993d5"))
    (1233175, uint256S("d7300b26501ae8a6281ee47e2f4200b45b20f1c61d1bad0822ecca1e1f077056"))
    (1253391, uint256S("3563b846effa6173fd1cff5f9c68c859054b81ac1b62c3101936aa21eebdeec5"))
    (1273607, uint256S("377cc40c78e3d3e278910f25dbf867bd0e91dc436cdf57235fbffc0926328fc4"))
    (1293823, uint256S("1419c99a328268b5eb1355a2523f4f0b173f1295d39cfa9c80fd4393733e0c07"))
    (1314039, uint256S("ae2ae0ef0013c4b8c6aab1c0085024985af6e327947042e767bb2a9679feb7dd"))
    (1334255, uint256S("2673e36a76c2c7afd854f1cb44c78af50a92b9f5270991060cd98ba729bbe7d5"))
    (1354471, uint256S("c0134bcd88b350c2c4b9ef10f9088cceb591e6f1898e498352dc0704b1ed4d44"))
    (1374687, uint256S("74e5afa84e850eca857567df1d73882dc4c246c7af19fb69adad8a9ec4fc1fcc"))
    (1394903, uint256S("639d6833e0df382c9e7ca5cf1ff682cdf2aafe4175c34e17fe81710f3ff8ea04"))
    (1415119, uint256S("6c98515ba6a0c3573bc84cbda99622073f1a2f52d8eb538a91b785deeafafe98"))
    (1435335, uint256S("1d9569fd625ab7fa14d100de2dc46f82b0330f9ca9774b1f38eb7733b8b31fac"))
    (1455551, uint256S("47c4dbb198b090d139f555ec92c3022684c1869cd8d1e96bcb41673ab5a341fc"))
    (1475767, uint256S("5f792c436d19044ccadb5c9fe2f107e176fa8f07db8378e7ae7c61c9695cb4f0"))
    (1495983, uint256S("85033ac1deab063a02097b4f316b8ae5a7647d2e41f1b674e90f6814f226b448"))
    (1516199, uint256S("623fb2bf355b0e4d810ae0dcd4ebb7b8b9452ddef07aab0f008f110b88ae0017"))
    (1536415, uint256S("bc8dd9d09a49e50029a9b95fb8e13aea752ca1324d0b8d54b3fb4e5812e4868b"))
    (1556631, uint256S("8346e47a2845dc68278e5255666b122feb762f2160614d2e80b2593cdea344f4"))
    (1576847, uint256S("9ddbb4525af0594950a53a652a33c373d602f1c4ec7a39b1dcb0a108d831bbcf"))
    (1597063, uint256S("a02e1958cb1ea32d17ca50b7739b5691b4e741f35d3a9f826643e77f94cb42d8"))
    (1617279, uint256S("a3686a2dcc49aebe1c1e10548ba59f09db34f8fdc4c1684d370da58b2fa29493"))
    (1637495, uint256S("2538de38fbde5964a071e6a147dfa7e4db1ed7e2bf8074162141c9f4fd056027"))
    (1657587, uint256S("593c8c14a70e8c2e8f0d1ca56ef7d60f8e869d9eb19bfdc71ad044e3412a53a6"))
    (1677803, uint256S("932cfcddccb6c8e35914da897383c38d6cecfcfc16e8260f3086009c621d1eb0"))
    (1698019, uint256S("81894dfd622bf87d2b84e10830797cbe39ebf79e0b5291aca1167c9de480f769"))
    (1718235, uint256S("9cf3e48afcd2172b8cd06d4ebd603290f856c4d7e1f9a0db75babbe364c684f9"))
    (1738451, uint256S("66ff3d98a3729d510d191fb6391f187fa4b2e5b013348433a9915f9999b13e1d"))
    (1758667, uint256S("8bd78e85c1a29a02333916fbc570a3d18f7641926246822c053b394bed84f328"))
    (1778883, uint256S("c3f3fae2016788e5b0d57cd11eaa8e4b229c686332a7ee2ae0e786c75d57f983"))
    (1799099, uint256S("892559b7764378e892ac3e74209d4ad3ba982493eb0eef1d0f428fdbfb64e053"))
    (1819315, uint256S("edd56f1b4d1f867296c14da8eeecdae86c6f75de5eeab32782ab4375b6c2ba00"))
    (1839001, uint256S("98d0c72cd78652be187802400a81c3610c132a245bd81c737b76444220241215"))
    (1858429, uint256S("565846f5705f1ebb4d51940b8ad3a285ce33046606f978e05a9bb486cf8e6f9c"))
    (1878195, uint256S("0e88d7a9ee7916b8108bcc4b8638598a8fc2211e5723d986c6e3510c3ff32bc8"))
    (1897807, uint256S("a12c7cbb4131475fd4ba615957216758ba94ad59346249ef9c2c005cf67dc86d"))
    (1917669, uint256S("c535cb24f88503a4ced6f574b69e0f5fafb26421b29138478bc1ad268b04d6b2"))
    (1937507, uint256S("26ac68e35c46018eb25bf0c46d73ce4497471bdc56a46dc86b29ffc1a6bdd5a7"))
    (1957413, uint256S("50a251b0af721f812ca391aa986422aa0e76d466b0829cc72313da62ddb34c5c"))
    (1977245, uint256S("79dd3407be748d3056af872dabdf43cfde1befacf7181ea7456dbeac4454d321"))
    (1996855, uint256S("031700b24ac924316101e3413a2a39a79f4329a3c38f75a2436e56f2473352a2"))
    (2016493, uint256S("20e1d293de11d8de97baf26165e02bcce25b05b655f2dd5fcd94af302c38fb3d"))
    (2016549, uint256S("bb22805959b7bba80598129af90bec3d102cbfd1061ae4b9a9dafd0a63faad81"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1625843550, // * UNIX timestamp of last checkpoint block
    5607389,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    5760        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 120;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
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

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint    = DISABLED;
        consensus.height_last_ZC_WrappedSerials     = DISABLED;
        consensus.height_start_InvalidUTXOsCheck    = DISABLED;
        consensus.height_start_ZC_InvalidSerials    = DISABLED;
        consensus.height_start_ZC_SerialRangeCheck  = DISABLED;
        consensus.height_ZC_RecalcAccumulators      = DISABLED;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1563924366; //07/23/2019 @ 11:26pm (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = 1002;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 2024001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("7aeb48ba5038096a31dba0b0a274236297eaab809ef24fe48d58eec821ebbffa");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                     = uint256S("3c15ae0fbf2b422bae354856c557fdeae8a1cfe8c1dae24dc5a3eb6e89fc801a");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("24975d012582291480d6604d469acd18b09acd87068f9f1a8309338c708dcda9");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("ea1031ff14a7c59c7df9291d347cbf1c72bb1a9b4aafbf3c215314a14aaeaae7");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("cbf48bacc3e1c8d843fe43be3baf7732c7ac4282f57e171980a2b50d18fb141f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("99552707f5e6815ac9c4bdf764817c21cd72dd095f44a1268c373bec8cb1648a");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 10;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint    = 999999999;
        consensus.height_last_ZC_WrappedSerials     = 999999999;
        consensus.height_start_InvalidUTXOsCheck    = 999999999;
        consensus.height_start_ZC_InvalidSerials    = 999999999;
        consensus.height_start_ZC_SerialRangeCheck  = 999999999;
        consensus.height_ZC_RecalcAccumulators      = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart = 1501776000;
        consensus.ZC_WrappedSerialsSupply = 0;   // WrappedSerials only on main net

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                    = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock               = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock           = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock                = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock            = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock  = uint256S("0x0");

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
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nCoinbaseMaturityV2 = 80;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 4;        // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
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

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint = 310;     // no checkpoints on regtest
        consensus.height_last_ZC_WrappedSerials = -1;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials = 999999999;
        consensus.height_start_ZC_SerialRangeCheck = 300;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 10;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 10;
        consensus.ZC_TimeStart = 0;                 // not implemented on regtest
        consensus.ZC_WrappedSerialsSupply = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            
            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         
            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     
            = 400;
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

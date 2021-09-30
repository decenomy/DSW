// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021 The DECENOMY Core Developers
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
    const char* pszTimestamp = "Bitcoin On-Chain Data Suggests Miners Expect Halving to Pump BTC Price";
    const CScript genesisOutputScript = CScript() << ParseHex("045cc0738b254d30b688352a0866ce76f5c07d1770bd07460049a327f00c1921705f130ce64d28e83c24c7fc1b0b63958ab9b883131dcdb4dca5655e1e17350a6c") << OP_CHECKSIG;
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
    (0, uint256S("00000e7b446b97413bfec60b4d733b3765dcc2bbbb63fd655e507390e4c4632c"))
    (6906, uint256S("e7fdc076870799639a60f788bdd4ba5df9454813c4457487b2f91ecda3da18d2"))
    (13813, uint256S("dd1cadbab3d16522f8ee83a8fbadb5fa8be8db502648ad55961d472de2e0b394"))
    (20720, uint256S("b15fd20d5399d7d4c7ba82de06b81546324d3cc1583f636a9dbdb18569710e38"))
    (27627, uint256S("713da91491190c858186bbd9de5f713d764479f926dba356bda9808145fcf8b5"))
    (34534, uint256S("63d0c8e461bd270c0d773d912cf160920e4764464a6217f8bbb9936819e5e4eb"))
    (41441, uint256S("c42a5508d58668c4f309b1122196c78664d73eac032f2387e579840936580122"))
    (48348, uint256S("cf566247a7d03ce0278eca09a68e3f53b9c9fd75c0715d4120b0946c8cd17369"))
    (55255, uint256S("14bd0cd6c5a205060eb8de316ab101c3b38b53df7ba6727e0f7b182c64f7d5ae"))
    (62162, uint256S("568d759b64fa534646ecfcaa525cfddc7f0c699b115305c464b8cbd86edb6cf7"))
    (69069, uint256S("b6a7a8e456b05b586cac827dd39fd996ce75dad5077855a6fd58bc4443254b26"))
    (75976, uint256S("441e8adc49da603f71f1c3fa08293aa19f616c9074760d1d39887f59c1d9c274"))
    (82883, uint256S("30c4bbb9191d4222d4b47f7ce2a814e602ef7428e842c6b5ecf7669a07edc36c"))
    (89790, uint256S("a4dc1ff683c22c6da95cb296ab34e02ef913dfb2e74a0e54e66d33b79c36046e"))
    (96697, uint256S("d02ea34b64055480ba57931acaed9191e8b23f02e6a6e1e0ce7f3c5959bffff0"))
    (103604, uint256S("9e07b5029ee354efe0d25ce2065f37eb9c2dd4fe1815b3f3b42e13284be81950"))
    (110511, uint256S("9bbb76bf8bd7489886bd3db719f4fdc8f5e8ca12c4bd472c9ca9086511e56b41"))
    (117418, uint256S("908dc7e6fd983aca25f1589042d559eac69498cfd1bf2a382d2a22946fae3807"))
    (124325, uint256S("e4d914e25ce323330522ddf095e9bafe5f7d44db359b0aa2c1ba8c7069cf13ee"))
    (131232, uint256S("2dc6804d095538628cf874a815a3b8b04726dcd581be06a152ffd5272ff1b352"))
    (138139, uint256S("aa02e90432bb67884ab73c9ea69989a7a1c34aec58f42aed0b15417d2363f0d5"))
    (145046, uint256S("f8ee0148524c3af62a49c88fa790cba5f595a3e02d39e0e70e7b5aa4cbdfe511"))
    (151953, uint256S("e2a00b377535b882d57bc60c68563905de96519622ed021cedf5f64e132a9715"))
    (158860, uint256S("fed0c391317cecf2c2f979a5b05f14dc6e20c25e2bdc20b736a2c941ed6d65c7"))
    (165767, uint256S("e9109874af9e0556ecd2b774e6d49ba7b6529f3d9a2e88df4695e93185a95ffe"))
    (172674, uint256S("25d4e10f0c0507a2fcc59a29e8395bbd648121e5f09f249c5a9db8106f0a6870"))
    (179581, uint256S("c0b72d962dbd7845a986a92da43008b96675632a6a2b7e80ee38e9b99ee32129"))
    (186488, uint256S("d5d5a6a92146cf4482e89ecd5f8f76122d6f7bfe9e833bb3c3779a3379f8ff71"))
    (193395, uint256S("079b4110f24edec38494e4a68caf23b5c534bb28b1337a62669ba619e2954e6c"))
    (200302, uint256S("c3fb36b366cda7bc3afac284ff2ab9eb97c51dc4c8ba7d2168c9e8a2d2bbb84c"))
    (207209, uint256S("0309c2f406a9d2e2b02f5113b15e67254979b49a27d0ebed9375f868bc446880"))
    (214116, uint256S("b83bd7b1fe79578c6f70572913d68c40017d72460725d75ad4fdb07dd1115732"))
    (221023, uint256S("4ad50b89a02957bc035661b55f5a636f9f6e78658d18e33a232ebe752adca1f6"))
    (227930, uint256S("051a7df62aeafa57d4cd6618a3b47bfaa5f159826edc5da4818ec9b53e3425bd"))
    (234837, uint256S("17dc07168b3af61c524fad23fbc87aaabb809c004ce57abc6bbac00cd7d49881"))
    (241744, uint256S("ea68a6436dd05e27a7a28975191aad11aad0756bdefc6180c8e6675a33441f4a"))
    (248651, uint256S("d05ac68ffca5af1be581fd01dfa20ca58e27900df3b2b122453cbc00b8bd232e"))
    (255558, uint256S("0a3b3cfa197455bc4f0dc213b667e4a4703083de1328797bdfb13e670df11bc0"))
    (262465, uint256S("4850bd579cd9fc17c3572e77618ee6e19acc31a06dd289914a2c097ae0013de4"))
    (269372, uint256S("5140ee9bae7cf7d3dfc7bbf7cf182ae66ddc4bbd5fd06b9e01901bf787474a4e"))
    (276279, uint256S("6a0064061bf209f2f27222ecdc3249656a0fcce7db40298ae061343a650078ad"))
    (283186, uint256S("83204099d7ee72dc2598cd04440f2916452a1bc8785e54a1dd937824301ace5d"))
    (290093, uint256S("d519c66d6e38e017b95ba0c6dae4d76fe75f5e7fb78f2c4a697a08b3f40dcdfc"))
    (297000, uint256S("1e10af698a36bcdea1785dd45e0a0f6bd7d93dfd41ec5c82312129afb5243b8d"))
    (303907, uint256S("01b4547c4e9ec06f7b8d37bc9218069bd27e7789e31b9e88dc4af504dcd8acf7"))
    (310814, uint256S("a34ee7d375928372655324066bf1c4300eb127d6f4d5e490f17c57608fd4b801"))
    (317721, uint256S("b646718db0ece8cb75dc8c683d4b65abcb8250e491a6739eb8251471c950e45c"))
    (324628, uint256S("3ece1259afed9302eba66dcc48642c29c7ec2778618dadde392abd8eb991f939"))
    (331535, uint256S("c3e9fbd1562187d0ca8df9c5773211883c83c376632ba375d64dc48daa768116"))
    (338442, uint256S("28ae578225741c5817f70e86edd80df3ee645c04cb88310af8088ff4bd307b0b"))
    (345349, uint256S("3d7c836b415d2ed16e903ae179553c5ae5c749168209a0cd46750c4ed6d0718c"))
    (352256, uint256S("a3084cfd8affea063fc00e4a309dcc944bf9846d74a6c377b56b8eb208dd22bc"))
    (359163, uint256S("87e0dec9280481a96b7964e68dc75f1505f93342c25d0ac54dc36c92dc0d3abe"))
    (366070, uint256S("4a5bac0c58ad78954b9b0a0fc06180a4ecdef0f909acee8aefc0e4d0d73afa83"))
    (372977, uint256S("258ef01720255b9778a510972cab350f24ef8c3e5248083bc013b36378b5f2e5"))
    (379884, uint256S("63474f6dafb7421738dbb5cb0ebc380507df958200860f12585535dafeacd676"))
    (386791, uint256S("8463867dec3d4363e1453f545221cb03d3688c917db161d02da67f1fa5a2c28d"))
    (393698, uint256S("1daebf9b38d3e2b3c3745d36d7537c1c8795a12e4622f96a92d5542dc30765b3"))
    (400605, uint256S("a313f03eb86dabe5a3872686d9bdbfb50441943a2b98475165b92ec0089f028a"))
    (407512, uint256S("5afad9d82d8f25fe4f989c89e5e7821913a2b11d2d43cce5bf6039effc4cf549"))
    (414419, uint256S("8b81c88e189210b84e486a17d520f27a30e1b46f30cc5740bd401bd13e2e58b6"))
    (421326, uint256S("edc066372979262210da4a9504c059067213dc5415db28121e18f7376dd9a31d"))
    (428233, uint256S("64ede4e044fca70794c5de817d2d7f3b0889c9552501f87778894cb08b51fa09"))
    (435140, uint256S("55e28677c760c2f542093b3312c872cbdfc8e5e9645da0b3beef00053e194be7"))
    (442047, uint256S("2753c04a65272d64c00117b3feeb6b897995ecce4dbca04719fbfb7eaed6cfbb"))
    (448954, uint256S("a56128162b1db60fe9594f7b692666714eb60ca423522fdf511baf8234ce783a"))
    (455861, uint256S("0f3cf649390cf5c8b739cf43b39c04f157559e38e7f80e470a18680028e813e0"))
    (462768, uint256S("d76cca4b3c3a5ac5b542b8877d9cfbdbf58fb77f1620de8084d25591787cb260"))
    (469675, uint256S("fbce7f3487a70c1539071dffae2a1855c378ec73b7e01087a97f3016e7d3e344"))
    (476582, uint256S("3accf76b6a3aaa7f1c6a14d0544d7e9e63a83ceb41c4581f7c47feb85dcd8253"))
    (483489, uint256S("ca2c8997f6abb0be3a4be0e045a6e1e13c55ded37eeb8a3f773ae5742bc38444"))
    (490396, uint256S("cfc1516812eaf3c65f1abab182753f8eb1b2b52cc080d56cffab19c197ca29a8"))
    (497303, uint256S("03e8fd3e1f02b11ee4c9d89ea3cf1835226faf7cf2c9bf2246d831c49e8aa30f"))
    (504210, uint256S("041c5a6409bf7b4fb06c6cd389101a0f939535df730e215fc2512be7a458f4a8"))
    (511117, uint256S("5a37f7ff02a3f776125cf48acb90b81d54eab52142322d51c1417df4c3887765"))
    (518024, uint256S("01255da4ee3e32aa3b223f1592c5aa9eedb2ce8c83bb87f30bc3e6a87f232e10"))
    (524931, uint256S("efe06b666a6e84218cf2218327c882868278a7608e84b56ebfa60d034ee77f76"))
    (531838, uint256S("cb86dca573786f7292e16729f9a6237006178acc872f0fec2f8c85c0a6601591"))
    (538745, uint256S("0f2b543ab7a72e3199ba41d3f3c43c69031843a489ad5faed61af4cd37fad92e"))
    (545652, uint256S("78e818f0ccc2313dc44b027d02390bcdd7ec74d7ae5cb69591c29154e40cddfe"))
    (552559, uint256S("d3481e0939f51d2296dd24e87c6a330313673819c4774fe36fb04bce9baac49b"))
    (559466, uint256S("9f9e03875dcbd7883b3f538fe1804047c28a22c11fdc44e2aaa39e0586a27f81"))
    (566373, uint256S("5bcb510b377ca8361114f56c72eaa2e054ac10ef8742d657d214f7fd40125229"))
    (573280, uint256S("84f6b0a69217ecc6978525f9bfdb0f44cd1b87ecdda0e4e42988a8130d75f788"))
    (580187, uint256S("e3c19ca13040fefce32153df18b463850a9b3797c749d548abbc8e9dba3f84c2"))
    (587094, uint256S("31874ff0cbb942ecb2ae0abc2cb18191b2b2a09e8d9f828248fbf7ffbd4ed2c8"))
    (594001, uint256S("215e2028c2852cf608017272aefc2f568f96014eb920895c70e2f495e746652b"))
    (600908, uint256S("3f2cdae9d58f72c17de4d239ab3c11c17cc23771fb2c83e619cde1b9c3691dc7"))
    (607815, uint256S("9dc516f1dd886b6ef48d21847bf665444f3aa3b86735107d48427c050b4651f7"))
    (614722, uint256S("cd3fedf0b84b5db32dbca5e31fd9ff809694e4a1b37deb284f78ae03c0d93ea4"))
    (621629, uint256S("c9aa4579b699fb2d8a9ba1d3b4dafa9c36a7848c3ed87e365262ca31320e3346"))
    (628536, uint256S("b5819651078072f4825a56f9cc1d1f162b9f19c5abca099e90b983acc40af5c2"))
    (635443, uint256S("fc7568772f42535bdbf8e7bcb15d6c75937c0b873ff791faa3c221927579a6aa"))
    (642350, uint256S("0828e012a9ac815347ac58c91e6acd145376587fa6a449cb648bac962f99faef"))
    (649257, uint256S("f205dc9aabbbb677aec725a788762d08a1001063063318c75e854b95685db7a2"))
    (656164, uint256S("9605b5e0757045606173967d7104512eb2f7c344f634a262fdcd5871a5861d80"))
    (663071, uint256S("af90a9734b3e08ac2e1c0784ae886ea22fc1fbf3313fc4599ba77291fe5d4f8a"))
    (669978, uint256S("e3e66199ecfeb8fee0d1b84dc1f0adf1cf28e4c54319f268c9fd2b6b41a1b10b"))
    (676885, uint256S("fb1a7a54cacc225930391806880cadd7ea1451b58b1445f668d2454dec1363a8"))
    (683792, uint256S("76ffc42fa2d83ff7c6e533a6596249ea0de72c37ed3a1ce369b2a19514e3f954"))
    (690701, uint256S("8a7d5effbbd0e14662abb12f2ed47e8eb16e73216496ccb41c73c9fedfd67597"))
    (690709, uint256S("614e2efad78714126ed98159816950231b13913b57a161d396e5555d53fc2ab5"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1632852892, // * UNIX timestamp of last checkpoint block
    1397461,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2960        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1590602436, 8798527, 0x1e0ffff0, 4, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e7b446b97413bfec60b4d733b3765dcc2bbbb63fd655e507390e4c4632c"));
        assert(genesis.hashMerkleRoot == uint256S("0xd5815c170eb44b9b7aaf67a76cba9da647ec1ade573c585c665a627a71b5405e"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 30 * 24 * 60;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 500000000 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03cb8b6b4f2fd42dda4a9fa037fc8e2bbabf70f626bc03b523d45e0dd13534cd8f";
        consensus.strSporkPubKeyOld = "046DDBE578C1DFDFEE9EBC4C89F2709B92D1D5DD0E0D99D87B84AF8E8DEB3AF370DF7EC30569FB1FD72624B4F3EDC5409EEC0D0A1F7D5B845304FCDCA9FCE157C4";
        consensus.nTime_EnforceNewSporkKey = 1633478400; // Wed Oct 06 2021 00:00:00 GMT+0000
        consensus.nTime_RejectOldSporkKey = 1633651200; // Fri Oct 08 2021 00:00:00 GMT+0000

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
        consensus.ZC_TimeStart = 1893456000;        // 01/01/2030 @ 12:00am (UTC)
        consensus.ZC_WrappedSerialsSupply = 0; //4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 700001;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 700101;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1000;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 700201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 700301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 201;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 700401;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("1203611a86942fdece0314ba7b360110c7d8f1a604c063a61f15c52a6681de19");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock              = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("2ebda866432d7e5f709cd47c33adc21d24a4bb064704962414de7c06913aaf5f");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("1203611a86942fdece0314ba7b360110c7d8f1a604c063a61f15c52a6681de19");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x20;
        pchMessageStart[3] = 0x19;
        nDefaultPort = 32112;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.owocoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.owocoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.owocoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115); // o
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 112); // n
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 92);  // e
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // oneworld starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
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
        nDefaultPort = 51474;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.owocoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet oneworld addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet oneworld script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet oneworld BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet oneworld BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet oneworld BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // oneworld starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 300;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 300;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 400;
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
        nDefaultPort = 51476;

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

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
    const char* pszTimestamp = "Another 50% daily gain for Dogecoin confirms 'alt season' as Bitcoin slumps, 05/05/2021, COINTELEGRAPH";
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
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (1076, uint256S("72775778a9a330103b6bf3fa8fb1a9d0e41ea0472e0fbbe4b1db03a8b44827a4"))
    (2153, uint256S("8204ae2b62bcfeacdf04689effe1b3615a0626c3fcf91f9766441432ce61e5f1"))
    (3230, uint256S("f4523911d52ea1dfbf64dcf7e21963de2be143462ab5c982aed62b6491c98420"))
    (4307, uint256S("3e7814963a99ee967e3a1f7bc6a99436922a8efd26aa6b99bb4c59833c4c8486"))
    (5384, uint256S("b25d3f5d9632b20c823688bf0e74cac41002f17745a4b3cf4915660ec1164a63"))
    (6461, uint256S("f0ee3d28b99a486fd21c74ae29f9fd42d65a56ce32a453084a2bee2be35e3c8a"))
    (7538, uint256S("e2c14c8208082297edeceb41ecd011d2ecdc99edd42678d97d255764edd666bc"))
    (8615, uint256S("4ff4d5cb461a55b8192df970c66ca2f9a3a268b964d4df9184862b09e5301464"))
    (9692, uint256S("5322129f1f30226cdf75b6f7eec758d15309cb927ee9a449e7c2f1b3be911fb3"))
    (10769, uint256S("f0f108fb2c93305e443a5747c87482af500c7f94a46820234e2d54d919dbaa8b"))
    (11846, uint256S("dda26c4a9844140dfcc29b7120b3f18c9ac3cb9e73f321b9ababeee4068edadc"))
    (12923, uint256S("9d313070d628c7ff90ffc805e66e15208c7bbe6980fee3ac3f94a3d939c5401f"))
    (14000, uint256S("25355974cd1a11b9065749121fa0a5eadfcc34332a253ec1f7e0998a6a39783d"))
    (15077, uint256S("f4138ef2d540ac2c2b055c4227ae8ec6f9c3652475ab1d705e9ea2f42fc39afd"))
    (16154, uint256S("12ce1ea94e8042f52f6926d967934738b29146203f26dffb44a7449391dddbab"))
    (17231, uint256S("b6239c3acb166f88368849c8d92e3ec1aa2d252e7b0024f1ad5e18d8ddff8d6f"))
    (18308, uint256S("14a91b7b740566963d6ebb25c5c4742e53689f6f0a019890d684054d655ff868"))
    (19385, uint256S("865775ea9b799889a59c6fcc78281daed43018701f26bd5044b1f0968e443b19"))
    (20462, uint256S("f2eca5d2f731178be0fbc397932dd78eb619ede8926b64065a8276ae62687cea"))
    (21539, uint256S("f10dca1c5151577b1410b759fea64309b823b21f194a8fc4b71b1c519ab01ae9"))
    (22616, uint256S("2570861cf38b3cb934f8e47500a3c8036e54f21cf138dbc2aa31afa2fb2a165a"))
    (23693, uint256S("a11a7354bc0d258f82aa7d121539cffee870911d528afc5af2d11cb0ad3bfbe5"))
    (24770, uint256S("d89546976a7bb97bcd2decc171f1ef7d790e9c1147ecf4deb547b9eb36aca3ac"))
    (25847, uint256S("3528396f9eb39fc49e4985674ebf01fe925f57692b97d0d04197b8501d4c5607"))
    (26924, uint256S("b6cd05ae762c59cb81794b9c53e6a832012507a82000456e4c6d3265420d9a08"))
    (28001, uint256S("91939162217fc9e5002a4cc1c46ff8680d2bb5f5ab5c45d534fc2ab2977f4f4e"))
    (29078, uint256S("86238c17af94920deb737af2bef593422563b2b6287f69d157b91da1fd043c33"))
    (30155, uint256S("e83f8b659daf711d879cbcb57af12ceb863c975b98a07b704b05d4c502197c97"))
    (31232, uint256S("993bb4eb5675e4e905b730675b5c1e3c42adb46c5972d29651f5eaaf6810e979"))
    (32309, uint256S("1d4e994bff9dd3db500c658d478e2aee90f7da997c8a5c3d587636c4a216a8a4"))
    (33386, uint256S("305ba9e183f8a03a5eed492b0f35b777f47c191d5b5a8cbb481954bcc3334ad6"))
    (34463, uint256S("485a71437e8a9b09c4da25cf85ab7c9a767d071fdeb19b4ddf32598179ef064d"))
    (35540, uint256S("5bd8ddf200acaf177e07b6ef8b94318133530e05e66770709a278abe17618f71"))
    (36617, uint256S("78a7b48c5291c6c6b792f6da7a272ab9fde19888843d409ead9b0eeb3457f1ba"))
    (37694, uint256S("3023ec82e778d43d2a4f90aa52c6ce5acebe9beec9cc69ce811ec66d22b508b0"))
    (38771, uint256S("bec6adb8ed8cd138f0c475921dac61370ac49db0cec75ff0e71a4133a50ba861"))
    (39848, uint256S("d845ce8299e328fa971dad40ab9582f860cfdc39269b564fc3c06d2fcd5c0252"))
    (40925, uint256S("3c423dce16be42165eb64b1a4c23b25247ae62adcbc88ceb1e92928ff911b58e"))
    (42002, uint256S("61de5e32c60a3b95c1e31aa68cfe63a9d41129a3760d58cbf4c28c4fb8b9c4e5"))
    (43079, uint256S("16e1c950a065a53679d942f4ab3e3a72c4ff53270f359896bd042e62df29bc9e"))
    (44156, uint256S("7a3138776c1c7bd2e47143e8dfd2203f3ac386280af22ed540c5aa223749163d"))
    (45233, uint256S("9376a50fa454d050d10489f6a9adc5349c150676d93e3048e45ab1a648b66529"))
    (46310, uint256S("5fabcf0f13c63ad16aa439ae31c59a5f2664f08a5e1f524301434df10c436e2c"))
    (47387, uint256S("7d94c286f133234118038c0edb1b98adf7ff27fedc19ad37c6cb49e483f3db17"))
    (48464, uint256S("0eae3adbc059f9208b92cb89be42e02ed8f4e64518c0789862ccb59f59690968"))
    (49541, uint256S("ad0f9e3400b7c1d3458ccab2108bf28c4a134f8b09032be440fcbeb26a581a25"))
    (50618, uint256S("564e1b2fbc3718c887fae1f9d7bdf61946027378ce730b706f6ab6aa53794025"))
    (51695, uint256S("d9632a62244951a1f03584f6f1da884f46e708ce2b27de48c40124ec7fe1afd9"))
    (52772, uint256S("2f42c97d52ce3175a9d5d83fa7e2bb77bb40a8e97cca08fe89bf9c4adf743bd8"))
    (53849, uint256S("f000f59167a65b84a40a7f6202f7da1bee52976f79e919579005587eca935f05"))
    (54926, uint256S("445b4672c8cc154fa39495b8d824eded6f7b6fe5361f4d514614671b93bbbf74"))
    (56003, uint256S("f0d9248ee1ebb78f2d2075c8a9095c7c1829b04ebb000aca8441f1754d7c1118"))
    (57080, uint256S("6b52135124112b89099aac5f07657fcdabdf7ae927aa7c7fbc364101ad1145e5"))
    (58157, uint256S("8c1a484764f520ea5dff83842507740d98de3c137f037947d008298f0fb4ad4d"))
    (59234, uint256S("2bf3ec2f733491d67511ef5494be62eb8720ff7e95177bf1bf59ebb59da5367e"))
    (60311, uint256S("c019752b8692dd8d40ec7c6e73c0442602595566293af8084802082aa765b44f"))
    (61388, uint256S("8a45dd163a7810f583892a08c5ea73d101f0a5a45709552f970fea8acf54c92c"))
    (62465, uint256S("359fd6c61a0c3e1d10e79e2db050cf4d4ca4f16f4ce8f238c538190cb0430bd0"))
    (63542, uint256S("a3632a1308dcf00577bdd5021969028381c9c9454741ea0bae6abfe82e79f9fe"))
    (64619, uint256S("af035562bdee481d7b6201ea9f260d1f7f1888f05adf0259bb5c73c44cb95960"))
    (65696, uint256S("8fb720e262f199f09cd6db00de28348e6d3efbbf1f58ff31356aaa6cd1933ea0"))
    (66773, uint256S("da6fedb3723067a34086d396c597d7fd2e54665d2753061a61711fdc140f99eb"))
    (67850, uint256S("37ddafa8fa1e0805588110695167f07cb1a651edcff396a97847e2ea4fbb2357"))
    (68927, uint256S("25a9bbfd2570eb12834b53741624f6c246e05ef2db83f5cecef42b10f9e7b47c"))
    (70004, uint256S("030869f2834f774aea0bc01d5984afb8688a97a04dc2a94524e861b7d7e51344"))
    (71081, uint256S("6de47364f7ca518f8b9f011a96cb222be2760d7cad444f77df85d6cb122f8062"))
    (72158, uint256S("3241ffa156d6de7682a3b79c81ac3ebe4abd6a6c8bee262668ccefe353a9c5bd"))
    (73235, uint256S("662c258640a2016b98a17c4f7c130ff95a93ffa2106c00d30aeded40b805362d"))
    (74312, uint256S("797e643166e8de37544fed0ee69b6ed05b6fef71abd518818c637e36e1e66d18"))
    (75389, uint256S("c14b10ffe8baf810c3e039d2498d6ab7131556be01bf734bb08f89591d2c7c38"))
    (76466, uint256S("9f91134b27f1abb3d274060033e10fa19ca23f0109e8ed3691702b3de1b6e4d0"))
    (77543, uint256S("88391dff2331a3821372e1496b903265c8b59b58850b87bc4e848f8b61715ccb"))
    (78620, uint256S("a21c10860139a6195e761b3d8754952cc9320fcb5b63574965957f99a5e02e01"))
    (79697, uint256S("08186662d9243754d411af44dba22c13e4a925c83a674c33bc492a8937e13025"))
    (80774, uint256S("934a4b262d2e2cab7c0fd8a4fce2f41c2bebdf2cdd0122f3485eb9fa6bf7f2ca"))
    (81851, uint256S("55d4b976dd0c681d1b37c7c3a02f6de0ea27627e68d912eb6f900eecf568a349"))
    (82928, uint256S("11a48ab3d7cd5bac094a79202af1b4493d391b7fd27123eb1e630f65c064f245"))
    (84005, uint256S("08f0e23751df990c72f5d4f4edda919156827c86cf7f8cf484d2faa483af603d"))
    (85082, uint256S("fd3f36effbfde9eb44fff4e6078f8af484feff85e7005eab352087bc76983496"))
    (86159, uint256S("5b8ae7f4e5c6af24cac95ea983d443b20f92c1da329b3f963e028cd2acd2fe4d"))
    (87236, uint256S("bb9ca85cad692146d90f82731ac3ad01d386cac6a704b5b1383ed82232ad7ac2"))
    (88313, uint256S("59279f7df25dbc0d41c9b08e324fb72f97ae6f88a36d7e9efe23032ee142657c"))
    (89390, uint256S("f5ef0dc3bc7d6a46e5fb1fb647424acaaaae98b8a97ab0446367b216034f5afd"))
    (90467, uint256S("e244de4eb28037bd4ddcfe6d473c3390ddf5f2c8b91de6572574175ec73516da"))
    (91544, uint256S("3ef49a8a14f02ac5b87080066a0ef0b69ad29783800cb4d48e34f06c5af9d695"))
    (92621, uint256S("a7bd25d8ced79a47b9b264b86def827c0c475b74c71e0edaec381d4eededfe26"))
    (93698, uint256S("cc21c3cbec1f5bd38e7bab9b6ab89dfc8c02c60bd0e357bd87151ba9897058cf"))
    (94775, uint256S("09b1c682e224c706c8abda8ae11b460191420425bc4c1aeec11b26c16f48711d"))
    (95852, uint256S("22fae313ab5dd93a1755fb1bafb73463a0137168295d233e7d781c790911a71e"))
    (96929, uint256S("77691ae31f7afcca8b557b38e48b559469d30f4de410187c06985b7cdbd08945"))
    (98006, uint256S("22f2c9d977c3a0d75407a3c7357ed56603263d938583984b71f8117dff073566"))
    (99083, uint256S("cf223dd294f1dc09be3ca49ad1557cab028d976e6466f36687791bb4f61df942"))
    (100160, uint256S("be0c2fd6d0abe14179d54d293be72e07e033089075e3282a764048c498ef6c81"))
    (101237, uint256S("988f740d24aea66cf0a8d182157637c126fc6c2f9fd54d2202ed9073d780cebc"))
    (102314, uint256S("717e37c2bded7ff23353ac466e7fe4124d737ff4ae8d0ec44ec09f8d71292b7e"))
    (103391, uint256S("5290042b86c08f5ee354bba5e5fb8a9884bbb75357ccd6e701a776cc6e55b8f3"))
    (104468, uint256S("6bbc3505e9e502bf47b169feaad54658b617bcef68c1510e3dbf05a9b60f2f68"))
    (105545, uint256S("19be54684ce123a6791bafa05a4837e49b086c5401569ba0672c2a27bdf4830b"))
    (106622, uint256S("d76ad8a3af23e9fa7fc7cf956c53de69bf79343b3ae3179f5c5d2b66281e407b"))
    (107699, uint256S("94ce478d390963ca2d66f7a4c24faeff0178cbe367c753b40fd50db47f8bd97e")); 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1626853170, // * UNIX timestamp of last checkpoint block
    221854,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    3076        // * estimated number of transactions per day after checkpoint
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

        // uint32_t nGenesisTime = 1620224091; // Wed May 05 2021 14:14:51 GMT+0000
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

        genesis = CreateGenesisBlock(1620224091, 1077816, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"));
        assert(genesis.hashMerkleRoot == uint256S("0x5322195c37996cc752786ab95a76b328f2f8e03d3a9b5ffb465173613d4f97ab"));

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
        consensus.nMaxMoneyOut = 50000000 * COIN;
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
        consensus.strSporkPubKey = "0273914d51723890516e319ecf24d71749da673c76606941290a0db4842389d693";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 115000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("f4f586f27b0af2d9307015d45b7ff3ba72821ce54bf45110c0e034bda22a98cf");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c33e160f767be68f93c57e2c5af5d77e7d1c83bb82a345f6f2d4ea968a3f5d95");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("70ce131e9bc06cca48bcf8bd0f0f8efff93fe6e34ce9caaaad984c66616f7245");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("b13b0ac7e05c537438198d3e181c2e9796d0fbe9139e2ab3f33352fadd25dd35");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3e2e44e642974c48c9c2e1b6efd5fbb88b253decc6878a9ee64e7242abd5ed5c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 36552;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x49).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet beacon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet beacon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet beacon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
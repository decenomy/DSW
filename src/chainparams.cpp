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
    (8763, uint256S("e68039711e6a9006af4d8643ef6d78ecfa743d9057d64fa181240363461b2adf"))
    (17527, uint256S("6870a19e2138d4cf3b1304a3ca1f2f415aa93812fac77c70f8c2f20c92de58d7"))
    (26291, uint256S("3ce1a69c4d9e849d36f27b10104a45e5588f4877de85a5e94191a28d3fb54341"))
    (35055, uint256S("0e710645750de54fab98a15366dcd3e6e83ff3195a44948aa2262dc6c2ce2db1"))
    (43819, uint256S("857ba8d5264c6a071779f6da371046ee759247c313bdcb6c43384dad4aface12"))
    (52583, uint256S("b595e7a5a3a42d56bc831f361aece5b65ee09bebf6ef9a28b52288542ced52c5"))
    (61347, uint256S("fcb75165ad6086dc250cc1f293812367f0abff2f294794eb20c291135d932f03"))
    (70111, uint256S("fcc8dc3a0680752dae391d02e0bdd4388b74b962a4d40690916340d08de50464"))
    (78875, uint256S("cffc35998bd467104a7bd7070c8391a479118f71d8c67153b1a7bb614b31d4b2"))
    (87639, uint256S("30a88b0f0f7f2daf3145aa124c9a98cfa0850161b99926493dd59eb3839c818d"))
    (96403, uint256S("ce614e4b067778a803361a92fb9724a1e21ac20f0e6b6a51c6cc3de1f80472e9"))
    (105167, uint256S("0cd06df68c395ad87f5cdf3f610a11e966c9a12fe469997e111c175452c4d70b"))
    (113931, uint256S("df009d886b852813bd48265a0be868fb1233c6faf12f86744a1ab610565dc764"))
    (122695, uint256S("efe0da9cfa5595f9a010d0b117e2f1b757fd74b2b52ed8bb1a50274381f08eb9"))
    (131459, uint256S("47ab0e5859b94a327db81793d25a3a9c0800d7886cc1c641a363c77c688e14f3"))
    (140223, uint256S("b4bb2aff8478c29987657a1eb5628beeb75aa73a90f47517cf32ac83c5db0986"))
    (148987, uint256S("457f19ffe7886915b3d40494699ab07d21d3edc11394b6646e1433337997c392"))
    (157751, uint256S("4b94fb44740741ea223031050504d8db7587bb8a799453f853dbdff2e51f9623"))
    (166515, uint256S("13d3ab000f8d07ca1318cff7d8199c6c95ded384dd7303cabb9c5630d94edb4b"))
    (175279, uint256S("69b3c0c3bab04e0d4ab72cd2d6fc0434a9b5b7a79c12791e7c0887eb564a2f25"))
    (184043, uint256S("4baf30392fa8dc8d87bc6847ea52c307b9525363fcf689889f6472aac20e43c1"))
    (192807, uint256S("daf895be4a46e873b6589d812a298cae88469538e9b906dbe52ac5e095497cb4"))
    (201571, uint256S("8475fa8a036f1ebefec5eba2c17fec01983519039d48f2039ecc59b7ebdddd09"))
    (210335, uint256S("93a41d42c7de82e4b669fd19b118d4ffb246a5b6b3192a37f23921840fa1fd20"))
    (219099, uint256S("e131f8867fab8224048c2dd94030500f7c39461c79d1fa43deab5f14f8e0642b"))
    (227863, uint256S("5fec2504df880ca59b71383dfea5dd9790932ee8d06010bfa6860041c69e7f15"))
    (236627, uint256S("bc057a38e1461b590b695d512acced2631d862514211e24ce474c19bb2578936"))
    (245391, uint256S("5ce2698243baae69a1b2e0f0aceb2e49a052f0076cf873da87ac2f697d8b1d0c"))
    (254155, uint256S("7c90c8bca961c17a6b8a83e65eeea29159f3055a19c7cb99fe25d83d57ff436c"))
    (262919, uint256S("fc58fb574a33bff0a980f4e21e7bf8a8703e036de9443588e729ce420e53598c"))
    (271683, uint256S("c8eb31882fe48d40745b18885b881a2a79d69a21cc77861f2e3f644307d2d473"))
    (280447, uint256S("af932b19cf556158a969a5e742e4afac98c5fcee9d14ac094e113778f7fc3d0a"))
    (289211, uint256S("152c5cfd70865e70673422faaaae0ed1922fc8c0f408359b8b197658213dab2b"))
    (297975, uint256S("d216ed70886d2b710c44413e295f4090b3845a97283f023d378f98344dbbbbfb"))
    (306739, uint256S("f307e791390126f078da2b267caf1880a8625e66857d25fc8fe1b3b1c32c6fc2"))
    (315503, uint256S("d975ccf6bd801022864d3e6232293d38ab4e1a37c72ffc27667a092e583e93c6"))
    (324267, uint256S("1cfbddbea2cfa33d01926c9424fcccb302121b6c3677abdb791555ef9066d99c"))
    (333031, uint256S("f8bd2106427c166b3007df7a4a27b406b5f39a72f3b292a8be8897e8e1f7190d"))
    (341795, uint256S("075b066c12d553b371e935bd46dded5d5d71b61982692a5eb0d1dc51d3435375"))
    (350559, uint256S("ae384ab4bd9dc0e096cfba0da6e33bd69bde171578dbb14b3d91226bce3bf924"))
    (359323, uint256S("f3aaf29b83e1f583ee234af201d81584adcb3d025e534fb6ff2333c492c69e76"))
    (368087, uint256S("4046bbc9640b66d5c1c7c0546890600005549a5147ce2e0777831ae1acf0729d"))
    (376851, uint256S("9e889abaa6a52d284afa44988ecbd385fd9a3db42b102c228433097b082c4324"))
    (385615, uint256S("f0ac36e6c941a4ec99f28901835889243f9becf254537fbb4a68581c4b52775a"))
    (394379, uint256S("207ec41677b39878a62aa05f6f24f84aa6c846cef3f36c130be8c9e13cb7abd0"))
    (403143, uint256S("2e57549ff1645129f3e521296e49c3b70d2ddb0954c9bb6336ea489ee07e9774"))
    (411907, uint256S("0844aa712725e4fd412aaea53502000656067c4e0fa984da801a4c79ef100858"))
    (420671, uint256S("6f53ca24e1690158b4a8ed1127ec03c5986f15fa5a6dab087c2e55fa7204499d"))
    (429435, uint256S("5df0d6bb8ada300d3f18c75e502d695ba9d428552b20d9f8b05e42215579b1bf"))
    (438199, uint256S("f96d70e23d7df19f4509a6dfb9a2771cb7122d30a0d596bfbb2d3fbccfd8f10f"))
    (446963, uint256S("f51385040a851e789a5b42d7b2241dd7c98d891f82dd3844c7aef8c8ebac8b89"))
    (455727, uint256S("539c48b7ab3ef946947919cd5e8659a99b1ffd14a56c6ef220b1e9cf2872c643"))
    (464491, uint256S("b9e1d0d8df5fd50222aa8f7b82903d0abff4bdca31b432894a72b0839b2f71bb"))
    (473255, uint256S("986eec9df2fca7e4c57b897fa499c5ae6bf27bda461f30c95cdf5d1fe50d8ef7"))
    (482019, uint256S("5d082fa7433886050be8152f92e569a84aa11c38140a49a2de19b138a81ca5fc"))
    (490783, uint256S("58ffc491e42a8819e024e041e0470fbd1715078a59c8e208a56a053c397b40c4"))
    (499547, uint256S("ff5641fcbf221208e25ba9c959cf27f2a4105bd1281a41b2829f5a5e66e3902f"))
    (508311, uint256S("8fb499749984d9a5f6c1d361557fd8e21e139e80b31a863d77d0259295c0a395"))
    (517075, uint256S("1684870f706adedc080ffb63f873328784b60f03db9187bae356e08456446f26"))
    (525839, uint256S("c35e9d6320729cbcfef5254eca85bc24ab6f73cfab0a8549adfe65efc06efee3"))
    (534603, uint256S("8eb08b89b89da8bd0c9debf03dcf20ab3b02e40c53b133ce09ca51497bd49692"))
    (543367, uint256S("79afe3db194b2ecb8fc050d2f0758ed10ff021fbfde6b8075f2cfd2dd2a15198"))
    (552131, uint256S("0d8319782559b3db0f9eccc407c10175d86626f7443c1e424e28851e8323a9bf"))
    (560895, uint256S("427a10aa20e9296a16161d198cbd88b8d60952fb2eed8c2267d0442329564e5d"))
    (569659, uint256S("afcd6a12cf66082646a6ac7928c7a7d6deb04455fe38fced70d0efca95dbe27a"))
    (578423, uint256S("b4ac61433870ea61dd45d9889104a6ddc483d27a784567797f6f7e3c50eee9c4"))
    (587187, uint256S("c5f126f9d8706bc9de4d63177fb11c80501db64c793bfc58a28a0a8a192aa525"))
    (595951, uint256S("c0fe209328d441f7ef5561b16ee19f5c78888223b0b280af9017086bfe82c317"))
    (604715, uint256S("11972f6ba0a4abc5efb48845216c36ddd29e0ec82fc830df780a960dedb08709"))
    (613479, uint256S("56c0d9fafe2b4568e4c2229ce0f375e2ba1a9fd576d960bd36ba896fff762c4e"))
    (622243, uint256S("416cff84847ed0e5714d06cee7a9ef34eaccad6b79b63a1f9d29aee6c7f2a04e"))
    (631007, uint256S("cc5bc508be62b891fdc1e016acdc75864e32e24b3ca3d137842533b11f0617e5"))
    (639771, uint256S("fdaac87c69a6705dac07b165f58e5002ce1f1ce5ef5e8bc520db90371ed49dc8"))
    (648535, uint256S("57a5a19ffc69f868e2b15fe054f2b4fc9f09f5ceee076c5c11c920b74c8c2c1f"))
    (657299, uint256S("cce2d4ebdd9e9b4fb881b682d01d14b6b295e540322433920824e89c16b1ab38"))
    (666063, uint256S("c939b6ad600d9370ee96b1967eb1009daff86a8e0ed4317dc71300b8c60c71d7"))
    (674827, uint256S("f62bb936a39c7d8d49b9a277f2d994101a1be8125afb0a6b38f1ca06fb30a66a"))
    (683591, uint256S("a800a4b64bf2ce157fc7e06fb13db696c9ca629add998c9fd34e33839e3df209"))
    (692355, uint256S("49c4c45436a50a7a9f246708164f5acd112f629e9ac1dbdfda299e8233e2ee6f"))
    (701119, uint256S("a233f888e2e551f31bc4101c888a12c17d09b95e84dfd11f92d3dc50accd1a19"))
    (709883, uint256S("569064322fe91b4cdd1cad95a5e77da43c32b8c066bd31855b17c5ae750c5b66"))
    (718647, uint256S("f10ae8ebaf6d6e88a29dae8ef8c97dbf7f805b69cbb78e5533e32619983fffda"))
    (727411, uint256S("baf4a3a15c4abe60c14f5bd6313ab1d211fb123cea9047ad9f11b3c260df20cb"))
    (736175, uint256S("2cb867960f40f37ae005573e040048762d3c38a30968eb92fd1343408f492ecd"))
    (744939, uint256S("151da75f2feed35b887f9ffce69123f52566852da1fb34d3a4f2e944336bd90c"))
    (753703, uint256S("215b3dc32fd1816ff0985d91bcb7e89e692ebfcf69a415f43e1f715c1b690a57"))
    (762467, uint256S("6fc8357769d8337c3a74def3e93e20c9d43d4d3ed53d7ea91d40962d6a2a3779"))
    (771231, uint256S("cf637ccde455ce0c12a9b573f2cb23bdf011f8eb634585d6815390b3e5e58a40"))
    (779995, uint256S("9cb2a1050635d03ca1dbc9add6b14abe28e211d78186ee7310054db9272dee25"))
    (788759, uint256S("2158d11a80522f13cfd17f51a4596acdca83c47a1eb4c9ea5304265b2d38d093"))
    (797523, uint256S("e356ff5e3c16e67a8f6193422203d5aa3a2db5a865270b57775c87cdff35d59e"))
    (806287, uint256S("1876482980aeb80900784e001c275987ec747d41e6643647bc11fe9907c9a847"))
    (815051, uint256S("bffef801f9e4fe46767f34180118a734afeacddd717f9a905a3ac10c6e6ec66c"))
    (823815, uint256S("df97ed91e56404e22adab5da44d85dbf2fb514a0b7c80e1eb9ad9ce875253d5a"))
    (832579, uint256S("0f99ff4446364461391cd70bc2e1bf8b5a310517b61f69098accedcb6bad2655"))
    (841343, uint256S("cc9c4d8fba0ce9e82c856c374819f1225a2962afc79f257cd2b2c7c182f0a8e8"))
    (850107, uint256S("c2574575cc8da28e92a01cd827bd487b31298f7a07fd141b49fb3ea616866dab"))
    (858871, uint256S("78e94beee692a6f0b16fd4462f977746d3a6ca3f7a1f90178f327bc0106d6cbb"))
    (867635, uint256S("449ec62307fbcc1f46d3f922ad2e69917330da70d4ddaac8c9ef37906bd18ad6"))
    (876399, uint256S("05bccf6ac7a95cbb7e40d2c24060520cc127c226952fd1bab5f3acaeef47fdd8"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1643980470, // * UNIX timestamp of last checkpoint block
    1779299,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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
        consensus.nMaxMoneyOut = 9999999999 * COIN;
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

        // burn addresses
        consensus.mBurnAddresses = {
           { "oXXXXXXXXXXXXXXXXXXXXXXXXXXXWc6ERN", 0 }
        };

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
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("5544242267804779f8cc5ef586f1c8a288e82b90fcc0ea346813d0a98b9ef397");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("af29c9c7aee6596f45dcec12d4d6fecf11d83338b6188c0b41bfd400c5a67f2a");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock              = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("2ebda866432d7e5f709cd47c33adc21d24a4bb064704962414de7c06913aaf5f");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("965d52a02ea15fd1e609993710eda72f110b7250bd7f64870767fddb4d9b30ec");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("9cd8671955df99b2127b70b9e663e6ff75bf29db9bb64b182c024b0be8b0be66");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("1203611a86942fdece0314ba7b360110c7d8f1a604c063a61f15c52a6681de19");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("00499a1b5db6df069b9b6f89aba4041de7dbadd32c68ebb28d516a3efdb8f52d");

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

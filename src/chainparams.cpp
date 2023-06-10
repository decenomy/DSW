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
    (10662, uint256S("dbafede4f08c89c1c30cec17baf84059296fa4dec5a74e7b6333c75c6cd6a295"))
    (21325, uint256S("dce10b6a8907ba82f252922f0ce86a3c80057ade5624b32b926a10a94f5bbbb6"))
    (31988, uint256S("105ff85bfe61650e1e4f3739e3469467f8774a23098907b64816d051a103d5f4"))
    (42651, uint256S("cd638b261c5452e6ca65783f49f20851a14389ae48410530893b6c8c5eb467cd"))
    (53314, uint256S("6cf080194df0a04c7ad024311fc48f091ca84c2e08aafeb1aa5dcec7b0e53873"))
    (63977, uint256S("03d2c533bdf02a1b5cdfc3264bd73bfe7462394d4722dc33a127f0a4c4e8acbc"))
    (74640, uint256S("5a91fe36e97bc2e6896aa09aacb5a88c438c2847f4574a0da7217dca7ced671a"))
    (85303, uint256S("37c463bf1b79ec959be5de646b6bc8d9e613c46ddc8e5f8350460eeee6a6c440"))
    (95966, uint256S("d9072c35f2903e9a9c8597429424af4f5af57aeca225770fd71ff91d7b8e4fa2"))
    (106629, uint256S("8264331e02ecc2d78d6ea8055c042c52ae02b8a1c8bf0c1b6fabc735e15e2ed7"))
    (117292, uint256S("fec3c0f42f6a53679f0b2bc9ee77f0736c24b2cf1d1caa9451cfb058766c1f9a"))
    (127955, uint256S("cfbeb695f675e63502f722260ff736620ae520d85a554267569246ca33020bb7"))
    (138618, uint256S("97cae17094f8350e9c472816f90825a2253523996ea9686ce6ea4bf697b867c5"))
    (149281, uint256S("95122509110f16029543ad7842b41a442880ca463ef804ad1497fb7a3f225818"))
    (159944, uint256S("8aedaf0492f18a88096987e3c88853682d7ae3825cdfe145af05ff1f99a54879"))
    (170607, uint256S("d3cd68649b1430e758f349a85241c7e4652aab15e2003b27be7c849c7d66089b"))
    (181270, uint256S("03d2086fd720d85f5b4eff243dca4d5edc287b93a58eb8fc9887ea0e4fa68853"))
    (191933, uint256S("a979d0e911d3e8fe63c74b33001af4f15920abb543e24ddf7384dd708279b32b"))
    (202596, uint256S("50d93c93847634810b880fafece3824e10c558727b12da8d36b80efd9f50b2bd"))
    (213259, uint256S("f4b4e6fac6b1c07a007108b9db35bfbb0fd34f90a30f019f15d3b86f2b7e9810"))
    (223922, uint256S("fed22516fe5c74667bf8ecfeaa359f6b87e70af68584170c1b37e11d7315602d"))
    (234585, uint256S("06e3af1bd35cf4a767ceedcf53a71234cc319950ec7cebf8c5795abeb57e1643"))
    (245248, uint256S("7804408fa79a283f3035609c0ccf5df349df9716883aabe1ef718da107fe9e9f"))
    (255911, uint256S("f58002b9de54a900358944c5843358c26f29828777c74bde84cf9b03145114db"))
    (266574, uint256S("077c1e5be9f213b309985cdb6ff9bf143e57a08274f7dd9668db48f5c0ab1b26"))
    (277237, uint256S("f760a396ae9213b509c75f5cc1dab06b3cdf55cea39fdccc98e4113b7f71019c"))
    (287900, uint256S("2d59dad5d879f5a03448bfa1f97efe5020510cb62006c828e6610f1886b284e2"))
    (298563, uint256S("d44de0cf1b37be25301af738aef7f7c838ced6e0f0be9469d5a990b31e860fb7"))
    (309226, uint256S("f72ceeeaeccae3e78268ccb107e376d8afa14beae3a82bdf11ea6c610f0d6c0f"))
    (319889, uint256S("f75b6a8d92d1c0e436be317dbd40dfb67a238497bba779876447cd1dec3a1242"))
    (330552, uint256S("2a8bf359046c470e7c22e4dc499ea339f10db6aa1dc949617614b5a4d34b2c88"))
    (341215, uint256S("8291c18e871f2a884b8e8f9812c6f457bd5d2a9760c04191b03f4c07a0f8ded4"))
    (351878, uint256S("2297dd309cdc0d9a030c83a20306e68f532122fb8dc5e7ea16328b6fdfdbfa9e"))
    (362541, uint256S("4cb67d393e485f2e676a1b2edcaafc5077d8c73fad971fb5d2ccb75f9c12d993"))
    (373204, uint256S("2d0e5b083a822f873215f1aaccfd0bf29ad85534d3bdb7090d1f5283743a3e31"))
    (383867, uint256S("63fa64c09a42c7042ea7514b93af1a876d6f59472e78c3fca0ff0682b0a73eed"))
    (394530, uint256S("86bd4e1d722127c9ab82f9569497283d675ef9f37fc17f2f0b76d8c26ac661b8"))
    (405193, uint256S("0621b0e79e58074645f94d74598a612f11843097bd3a91cea3d25c178c3a1105"))
    (415856, uint256S("f68d22cdbc882784d62bccef475c3bb890298406c8b6d5ec070bb2e30179038b"))
    (426519, uint256S("357e2a511a36471cff77965f068ad6da4daea5805c4b78c0a21395a67b6cdc87"))
    (437182, uint256S("e00d269c2c8f73878a18c0de862629af8b74654b39be7aee253398fc68c31614"))
    (447845, uint256S("c878f3564f8f65a7b533f274ab57db471612517e962fe5a204117bfaced83493"))
    (458508, uint256S("edb19fe2a7d9b0696098a61661152b7fa085b571d5996c3e10fcb54878c2489d"))
    (469171, uint256S("f44be15f5a687e455e87882e9771d87cace4c8e376ea3569974892737866f3af"))
    (479834, uint256S("07448af18aa504e51976ee498bb9ef0b811bba3846ff65888999916c2c8035da"))
    (490497, uint256S("9816891a534ac943b8bb9e1bc95e6d9f2dd6753eb41522e4b5189c156aeca9c1"))
    (501160, uint256S("8105f04d9260ea4918a483a3c514684c10f1b5d6dca86d51be86b67408905759"))
    (511823, uint256S("032aeecaa054e760e291bfaa3367b71045b7f638744c58ce5461c84293ea85c0"))
    (522486, uint256S("488bb4aac9cab007061abe76667a3b5e7af44cd04e89095e4f6c9df31795c104"))
    (533149, uint256S("c4821a8db47555947737c4e29f9df9de3e8885a6613aba39730ffe697d286063"))
    (543812, uint256S("7e59d2192d211e87d825b4c2a17cf278c8a8ab844d618354cd751a40d1c763ca"))
    (554475, uint256S("72f6ee291a888880115e1f24cad70aad11510f44ef32f5f077f03689190c9b75"))
    (565138, uint256S("5c9304bfe4de21e6ffcf93bd976bfeba23af70a2b2b35a17254cb9a85e032bc8"))
    (575801, uint256S("346664be165952e00239e9b86f020e558a13203c8a01055907b4cfb028790237"))
    (586464, uint256S("bcbeee34a5848e41e94025d3b698c024b5a6aa8874bfbd8af4393103cb6fc403"))
    (597127, uint256S("b0310fa425e02463b2dbcbee12eb956bc342938e2d808d2c7e35fa4da0981d8a"))
    (607790, uint256S("6841101334656a70c4eb7f1b2a88b9c38633106bd17c9abd02ed789e37f95214"))
    (618453, uint256S("7624d8c5a206257816363047ff0054d4c4959284029d6d9c552719366056abb6"))
    (629116, uint256S("b700855409aecc92bc38e9c4e030c7ffefbf9e4e86b1deda795f6f3d24e5e08c"))
    (639779, uint256S("4df102ec1f2214f159452e8e7ab6004004d7804d7af95ff814a477d0b4499d17"))
    (650442, uint256S("9056262c3230714177ab61dc9fd1b89e05155377ff7ddddf469a1c9e28c23207"))
    (661105, uint256S("307f8e3a049cd8a0cf0bb5d2c0047dfa50653e840e12e147fafd826a53a0b68a"))
    (671768, uint256S("87da2f3b0a9825a9b326554d649e39a18eeeb1f3e6728b5bf187f7d1f22cffbd"))
    (682431, uint256S("acaeeeaa4369c846d638f13dd7347f701560400605383fc1b257be54e9bc80e0"))
    (693094, uint256S("859d523729a1385f1658ca726b31fef56ae5a9f9683ce0bcce6b4e996b084264"))
    (703757, uint256S("56857915cd3271c181bcc180b7b2914f04c8a6810c7b9f05bec3f438aa1fba4b"))
    (714420, uint256S("e4310c86008b77bea0a7bcf7970c3ad76004ecf14db6cfef05078865c8aeb224"))
    (725083, uint256S("57bb93c419635041ea52509a5a9c70dc3ce66988da332bc0082e135e8b9ca635"))
    (735746, uint256S("e8de5365eec62c67ac7d69b5710ed2990a951c39a7538f8270dd331aaad26308"))
    (746409, uint256S("4b6d59ad9cc4f275bf91c2d405ffc77689978939bda6738dca6222d3c37d87b0"))
    (757072, uint256S("c0cdf24b766d031a454a682c9705eebf36041d0710b65866c0526187b2f38916"))
    (767735, uint256S("995b6f7e9e3f2fd5f419026c120b321f9174a0ae9cd09f60a88f1b5a6beddc6e"))
    (778398, uint256S("f7788d220a83c5e3e23bae284922343102bd31aa5ad3dede12ce4b0bdb9d0e1e"))
    (789061, uint256S("880999bd2e5bcd2e702977066a4e117b3ee04b75e085d8b2e9534a1424473e23"))
    (799724, uint256S("02d1ca7990b347fbfbaff8740f87e89518d25b0fe9a768aaf51249f660e1c2ae"))
    (810387, uint256S("6757b97926e64acb56185df01cefb20ef078de6c36b543fb871e94adcba7e37e"))
    (821050, uint256S("6a9f9de772fbbfc96ff8469cc8b5d9824a4b6805b2a93656c1a6d2bd15ac4f96"))
    (831713, uint256S("8614a31984acb72eb1046e96922301ba7f2a61292936ef119acd711d48c859d7"))
    (842376, uint256S("30bfc08d1f8e6fb4c34a826224f001f4245cb8a38eda8ad5a2820292eaf58386"))
    (853039, uint256S("3280e7da7765a35647d454038a190325ab5d3f5de8468ded21b9bb8b795cb57c"))
    (863702, uint256S("3dd150dc565bf6d758f0035fa9178d37dc062a28a81251133bb56db001b98caf"))
    (874365, uint256S("cf7b76f03d07f02430ccd105a9cf9f50ed25d441f319d939d65a6a8def429939"))
    (885028, uint256S("1aca07088b2e952b683d99d53bb29b5e3cc05931cf9bd4832cfc8d2f604854cd"))
    (895691, uint256S("2fb34be99d98e51bb4439ee9b4307a97fabb5b1edc2be53b506c091687242440"))
    (906354, uint256S("93088d64fdc5ac829976f5ca3bc29bc6d916655e34e6937bf94d4f81ec303961"))
    (917017, uint256S("c763f975a58ece6366231a3a7acdec71ea44419b91181c593e6df32925b14ba3"))
    (927680, uint256S("9eca3818a6be55bccbd3593b6e9b15b3cb65758974c707bdc7a54066182deb03"))
    (938343, uint256S("2aed7b229f7032377eb281912c28ee417e033422e0742115b947287cb46e7a6a"))
    (949006, uint256S("b2263a336271590025de4715ed94f6baa8323e275a0173046f5c54a1682a2eb8"))
    (959669, uint256S("82933e14bc66f7a9d00a109d9ca7d99a4f34259c81005388a92dbbdeccd50a28"))
    (970332, uint256S("4a24d1e5acedfef5a17eddce012daee58cac939007e619bc4a85a439461284dd"))
    (980995, uint256S("02f27e7bbad6edb3d8fe8d6c8e17cdca13998269d8286760655b491e2a703fbe"))
    (991658, uint256S("1cbfd57799514d8b35aa743319d89929bbbe0061899908a4731e6b9d6a4ec4d0"))
    (1002321, uint256S("370d589a24d0a682c8459d33d7af42865b96d8030bc340683efb09d0fdb047ae"))
    (1012984, uint256S("4c392cb9292f8660e6396f357465ca7f0b559da62985e6fd25e3d18c3b5df4fe"))
    (1023647, uint256S("942789572cc5c29ebe8b1197f4023ca828b1cd2aa87ec6e12c7293ea64d08355"))
    (1034310, uint256S("6ef01f58de1a3321c167bf2b852e8e81cd5f5087c6797444065749625fc4b611"))
    (1044973, uint256S("e4c4415a9c44110228a472b2df926d272eeedd68ba55930fbb85726fadb308ac"))
    (1055636, uint256S("da585bc7606d230bdf2bcf19e7610948b4ef6d1866923953c17743737473a5de"))
    (1066299, uint256S("a46ffcc2634cc81f68b0622c853312cf28abd58c811149301043b1ebf8ecc1d1"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686360825, // * UNIX timestamp of last checkpoint block
    2482209,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2842        // * estimated number of transactions per day after checkpoint
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

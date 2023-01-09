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
    (3671, uint256S("034ba66bd27cb6973999af575315e594496d4fe8ed485e550f55d12cd121214b"))
    (7343, uint256S("749af841c6d589eae6f8e001d559dd1a570ab3ac52fba19908d98ddc9007694d"))
    (11015, uint256S("f88ad25d96187b94c16adfd62b0caf1aca5c541007747c2f1be778cf1f562400"))
    (14687, uint256S("259de869f24f94b19c38e28d8a98b1932ce452228bfc3e201ee543b48d068580"))
    (18359, uint256S("f7c1e128114e9c13a9e26ccdb07f76d1acdf0f50ab2e319be266b1fed5c4a493"))
    (22031, uint256S("af16c9f88a9e7c3700f8777b8af3b6fe2f72fb478eda9147a6b40b8f5654da3d"))
    (25703, uint256S("185212c410bff9370f6ef6fee78c7d4b001885dcf6f5e0045923d203a5ae4e6d"))
    (29375, uint256S("3d80f55386327096aadbf1ac617b4e2dde4c94bcda7ec14bf3b5d3fcb8c53f7f"))
    (33047, uint256S("a399fef31112c350cd2051a937464c36ca63044e6ddfe0d00cfb3872ca462cae"))
    (36719, uint256S("59f12102ac2935c3cc125e7817a0736b5421a1c2b479635750b854410e607821"))
    (40391, uint256S("5aa8dac830d57724230a07cd158990c4ffce07fd612524efc3dd71ef22f3fafd"))
    (44063, uint256S("13fe4d298e4ca0fd80df059f85bc4c8ad9d2f91e668a95b76c0f0ce112a7ef21"))
    (47735, uint256S("d2d8a715fb9a18b4063c8b199c83de79bbe7cf4951f11ce498a446dea0cc86af"))
    (51407, uint256S("886daa7912351996e2f31091bdd62e8789366c8a2bf4a8f71712d138a6a69177"))
    (55079, uint256S("1470c60c52710f6850f086765c466e7faf805f2e90bd2c1684caf2d441cb03fa"))
    (58751, uint256S("21274a188b4a580aacc0e1b9de6d5493cd379fa1258d564512b2211ef9045cb7"))
    (62423, uint256S("185063d9ab1a3f0ee77a03bf1fc721daacb8d50775f04be4672ad4c238946931"))
    (66095, uint256S("8705d60555b1edc63cd028d361745be7ad4b2ec4755b4b8a14b38a272e2bd068"))
    (69767, uint256S("4f046d295e535b7d6e3c229f3f7c1dd2f4c897b9277f9dacac588b99233e3ef5"))
    (73439, uint256S("54aee8f6412f6eb9650edc757d9b10a5408caeee57231601e7364ebac5406a2a"))
    (77111, uint256S("cd554d46e80adaca19cf7f804611d1e40ead42187bb4cd4889381fdd2fe31b36"))
    (80783, uint256S("274914e7c85db40a49657bf8620edf7dfcda4f8cd4e0a312902f0112e60ac690"))
    (84455, uint256S("a052afb87e55eb7261d191177ea1f4ea3d1d9ee2ddea0976dd1b513905ced895"))
    (88127, uint256S("fce0b15abbd89dea15336e3712303a5afa0b2ee1649b43b108d3075c56e8e412"))
    (91799, uint256S("91497ff0ee9294160f243f2dab302b1cd9cc8796fab813411c9b8c3657bda2f3"))
    (95471, uint256S("0ecc8671cacfa6e36740f3e0f91b05c34c977df3071b91d8a1aebd914bc70156"))
    (99143, uint256S("a73cb8eabfde043c97ae469c5dec0eedbe1e098a042ffbb5ef11584df1405653"))
    (102815, uint256S("b98331cdac58be86c6d5535b504772e91d43894607da9ac0b3ef53dca7f11fe7"))
    (106487, uint256S("335fe50e65790464eeee84584e05b688c15f668741fa03f6b12dedc523aa5bad"))
    (110159, uint256S("e4ba15e1328380c3f3b256801448ed98eff32f01c72c7bd6db817dd02e7cb3ae"))
    (113831, uint256S("5fefa89de1b84af8d9aac6936bb6ce0a0cfa3097840fbd27c9e3a8b030393221"))
    (117503, uint256S("9e6ef1b208e12f11474636ce1fd64a4aafcfd606508ede8b6c3cd92196d03c31"))
    (121175, uint256S("ef5242bb75df8ee8598357cfc039b71b05cf6b081c1d1e2dca4284dbb5b0d15f"))
    (124847, uint256S("4d498a4df0f4ec95aa24058e86e79e8ac14ccd6c1f40b6d88c97a20648688a3a"))
    (128519, uint256S("5fe36bda8ce9f8038ef435da32735ce24e9e19ebf0daf6d68c0b8c767429c733"))
    (132191, uint256S("6691fc99b75e042ecfae5873a8c9f926ed0aeb81a0b281744bb7ca5009232893"))
    (135863, uint256S("64e24c68b51834490ce06814c0f9bdd0e68786b7f3d4c948d0ee32de697b67f6"))
    (139535, uint256S("bc5466738f91b835c949eb376e52e9b54b7ea567fe5c9060fb4372176124090e"))
    (143207, uint256S("a2d823dc8750c246d9ec361c3d66e16844df3f2bbafaaf604bea4c77d0dab238"))
    (146879, uint256S("7a05c4bf4e189a3268a5ad15edd0424bfab18e1cd0b1bb550ae30f22cca2bd2d"))
    (150551, uint256S("62616308fa6e8e4bde04cd6d12f2f9dd90a16abc39f1d4957fb93c1f3ff46726"))
    (154223, uint256S("13d87fdf8e9d2ae081e897d4a339bafabb24c772ba37d121dc940eb47ffa0182"))
    (157895, uint256S("1c9b0164b5cd2fb018f8d61ce50d33b8d43895e68aa3ec7d831a9587d61927a3"))
    (161567, uint256S("f172dc813912fcc62aee67aa952af09de67e90633ed54fc4805387cfed5f696b"))
    (165239, uint256S("d4cf0ea328383147c61e4c1d41fa64e585f44097e914430e1dc77a748714dde2"))
    (168911, uint256S("d77192a69930538c3461fdd86c12bf74b077e3427365e5759727a62058f25ff5"))
    (172583, uint256S("8198c95d90e93d7e058ebf7fd1761faec7b34bbbafcc1352d146dbe563c6ac1b"))
    (176255, uint256S("4e739c902fe9f265d55322e971417c38e6706099b88409a89f38503b32900447"))
    (179927, uint256S("51277d8d75e5808a90c20f13ae086928f92c82cc9af31bde93294d8144015a43"))
    (183599, uint256S("9ea4c7d3fc1ddfbbb2bd62844348c575bf3f336faf7af09dc6346a068ec90f17"))
    (187271, uint256S("b2e960914eab8a71c395403dd11110d07bdbcb59c96aa7a877aca9ed79ccc4b6"))
    (190943, uint256S("ba4d0dd3c113d097b46208d843861211a827eaa803d54be93f0270257a430fc3"))
    (194615, uint256S("78494bd80add96a61a81be61e1a548ae58ae28d3a13c93f0612752893cbd5bce"))
    (198287, uint256S("d6d534058f857495041b9af9a80345e31cf2a11fbe613a4ee495bca0f2b24daa"))
    (201959, uint256S("4b8346ef9d4dbc23f332dac8f41790c3b40780219515583d70f3ad6059dd70c1"))
    (205631, uint256S("a8c01a3da9cda75c3c0ff93119189ca5733d9abf6113fadf7fe9e1dac9d76907"))
    (209303, uint256S("b5807d5ffa7697fb05d58faab92a3b196e81cbb8f6b64f62140267b3c5d1777d"))
    (212975, uint256S("b5c8b0e314619a8b65c2b5fba4993239e9cf5763fc78528fd0451d573b8b3056"))
    (216647, uint256S("ab85621e58587ac25ff75214e38d05faec059dbbe80e92f16d67b53060fe4bef"))
    (220319, uint256S("363b876ca91f78ca5e3afe28b393732f78d3adb344746f735780f7e04b6e166a"))
    (223991, uint256S("14e87f64fc14522fd21063f62aa64976b61bb276051614a1e8c41510d716215f"))
    (227663, uint256S("e2afae7de4e7265557c4f827e760b1658d5f9192eafc5081fc582a5b4750b77e"))
    (231335, uint256S("f956200b4460b978f2350d01d58f37646808cb86302541ad5bbe7b137386d42d"))
    (235007, uint256S("4848cc855f95f13aed552ee514fb7fc8c8a74ac8557d1ba91e1a72852830382c"))
    (238679, uint256S("8bbeb1e061c127e54ea1f4f342c38fc2b26607fce17b5856a0215a2fbe0bb11c"))
    (242351, uint256S("4e90578163838c2a135ce1fd6ccf3e272a788def7165dc1c677c3c9798813148"))
    (246023, uint256S("dc8c7755becc79b779427883127434478e29e02f07eae068eab923213ac41264"))
    (249695, uint256S("b27ec501e8570d9ada9c6fe4061adc9ed19da4ed1cf562f03bee8ae0ae366e9f"))
    (253367, uint256S("7c2234cd8b59fe576741891b0e8fd178ef1fd7c5892f3cc2ba0677464c145e65"))
    (257039, uint256S("01860696619d43e3af8142584d1ee12a2b850d9754a567eb26d65120b46fbe93"))
    (260711, uint256S("4b02d34f6bcf93d8207917dbbf1d18de9720762bb09ace413be1cf2757b3e52b"))
    (264383, uint256S("f2a3a628ad7975ffbd5da0ceb33b7f2b09cfe8a6938ee957a7ebcb8a8fce9c97"))
    (268055, uint256S("13b72abde110854e406bc62ff34a290d352ef0fc4c43e2f824c77180200d7bab"))
    (271727, uint256S("607e1ce481d5af4a3af29d50d45dbdee9ca1eab5f97f9bdd862a6d495210b398"))
    (275399, uint256S("9f8ee1f28e014ab0721629dcbbbc6202b51b4f89dece4ea4f9c8d0b3bacc4728"))
    (279071, uint256S("481d77f221f5610c11a207369a17bac539d749ce46239f76758ba957bbd42b78"))
    (282743, uint256S("5b370e12e276dda16a39c14502990b58ecf6b6c8e8f50b9d596b33413cf19eaf"))
    (286415, uint256S("4e97fc6aaaff83e5586ae03ca21b24ad749d7556d6d320191f056c4d7be49036"))
    (290087, uint256S("4426b82ad0747db06fea01eff1c7386404d51869f49f6810df2dd236ebfbd903"))
    (293759, uint256S("e2911641756ac732e1d8fda67fd4f813d0a5d87691bbe645ff4c6599e5908c4d"))
    (297431, uint256S("b4d12c690c107f0c6de92ea0bdd59499a7946251e9fae83d703aa2bb1714233e"))
    (301103, uint256S("cd22a76aa0f539eeb7502481e12109b7f2403d84acda41caab3c907d6ec98391"))
    (304775, uint256S("614bdd71325a611b5d11e3db3b03f646b240064015fc5f6e2ef4025b6c2fd319"))
    (308460, uint256S("07a7f360fe4d5ff5021a6139e1451cd895084c53e3404ac4edf5b8ffc1b0b85f"))
    (312132, uint256S("772c6f3addf7021031966dd6216e4ff55bab106ba0c296668f01a788c543906f"))
    (315806, uint256S("600fcf8ec4794cbd741db0b68eb6ba6745c13f86c502f32c879f07b42afb86fa"))
    (319478, uint256S("99bc4fa29b9087ccf2744f15aa297e7364c6bf5f2948fc3a420c8a9df502ffed"))
    (323150, uint256S("6beaa592ddb0968ee0d5bfde21ad8b11195f1b3961cd07e102fb830eae595bed"))
    (326822, uint256S("f27e9c80a5d106cef9d6a5c8750c3501bbca8b672c178939343b288125526cd2"))
    (330494, uint256S("90277d49e315dc8ff7772633b59ed2c80bf35e1429331942c3e28d6030b7ce37"))
    (334166, uint256S("7548edcded0ff94d9c8377f0c109ffbb08fe3227bd7dbff4ecff37e82ef715a0"))
    (337838, uint256S("dc9b8d22985aea58965b394d0ced8e15b4d2f0bca76073c6009f7fbe1de2ef1e"))
    (341510, uint256S("5296dddc81a917e4ed685a5b1d378949b394a4aa77e1a5baaebcc392844a09dd"))
    (345182, uint256S("de9325745ce487ef07488d2ebade622e2c650a73d10a18d4d751203341c5b0ea"))
    (348854, uint256S("33b9b349a9aeda9ccf19b0ed1193a7d79d53707362b594233c0e7060b33dee39"))
    (352526, uint256S("84958a1fabc1974920d6abee62a579b66aff5cb35908717b869de403f993b3d2"))
    (356198, uint256S("5b0d63c65a5a532626e44e37a8b0c1efcfd6d9aa37eb47b1a5829720e392f76a"))
    (359870, uint256S("ffa2049eddd5f6a13203dca1b6963031a3de9d35327e2e61c928fe6fdf0c9ed1"))
    (363542, uint256S("48aae59c79663ffb0b85692de53516bc03b35d67f075639f20d0976fed2ad97e"))
    (367214, uint256S("408328859dea6fb3b32b46f77d70b0cfcf3fc9e032acf36eae0621eda52911bd"))
    (853058, uint256S("78fdf6b5062c7c692e391d9189f5edaeed3fa111a28d8d4469a5311cfd0598f0"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1673259495, // * UNIX timestamp of last checkpoint block
    2031646,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2824        // * estimated number of transactions per day after checkpoint
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
        consensus.nStakeMinAge = 60 * 60; // 1h
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

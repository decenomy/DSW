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
    (10665, uint256S("229930294f29fdb3b2e472a6b022f992913933dac70f45d639412a724237ba87"))
    (21331, uint256S("c655e3c3c8590789b2d5e76ce1929f56dd2d52f928097c527aedbf61862efa05"))
    (31997, uint256S("8321fb9c34cfc55ede9190aecd0686adc1314596ee11cb1d39dd60c37bc279ca"))
    (42663, uint256S("3632914f5fcf040e2fa552c9d0f9e7f0af8a6f9d19d69933d0596be4f9a57492"))
    (53329, uint256S("905edad23f17bfdceaa4c93159627dc7135c74e0acb2501b113d2b86d29169c4"))
    (63995, uint256S("8a8674d154e66d906b0a554208f6c5a19285bf8077e216fdb2fe6aadf09eac14"))
    (74661, uint256S("0fa3e84fdd07320da9e3f2af515ad470ed63dd39f0ee54ae6f47bd327d152bce"))
    (85327, uint256S("c49e0d1a117baf995f6e6fc87a1389aa2c42c73dd1678e607f304f6ad6217642"))
    (95993, uint256S("2efc62308a73e89ad4ad04d6c844740a6d2f7988e0bbdc5f702efc82b7a4c3db"))
    (106659, uint256S("0cd26a482a4a6906977dadb9237bada8376f0307cf759c12c401b3b4329a324b"))
    (117325, uint256S("3deae1531160e609d13b3b85a8f8f0a4537bcc49748393f0b2462d4895a192a1"))
    (127991, uint256S("e8b805241f4197b59e2990b53e67d2c9eee1d8eae93a1caa7fa27f118182cdda"))
    (138657, uint256S("8cd41a2c434b6f7feb680288fa6c5d87d43dab594c4b5dde653b50bbd8fc9475"))
    (149323, uint256S("18ade578d32b12a745118d8f6ae0666531f0ba43d8827d172771b59a7b6f49e5"))
    (159989, uint256S("aaad1ae9147ad2a5a516a00bca61aa5ac10c5d69e2eb41a03a5e63e789246343"))
    (170655, uint256S("1dda388b0fec280983e7e6446896e5bd527caa98fc56058f1c8e1c86eae81e35"))
    (181321, uint256S("9919791af518f6de5c81fcde1251c46de8dccafe054f1221d9451060cf63e02c"))
    (191987, uint256S("13dd788cd28d2cbc0cea95fa9aac5a1d38b1d378eeba61ad2541a06b014b8f63"))
    (202653, uint256S("afd3547e45df5d706231ed1643ea183ba3a56128d36c5eb4057f1a8a2108b3ce"))
    (213319, uint256S("cfa817928dfaaac28aeda93680745ac19d8bb5301f0a78a4dda4f467c2bf6c50"))
    (223985, uint256S("9f7176e7fb799586bf00e1cce71b2965d8b867c29e50c358a63a6d70cf66b9d5"))
    (234651, uint256S("1608f47527e722c07f125e6ce19b215a79fce41f5e50ce562dfe0432366584b2"))
    (245317, uint256S("3cbf4abf6306def5093fab7b0885fd686ca5a9db252c41398dcbfdcf3048e103"))
    (255983, uint256S("7173d2f44eff10e60595593fb01f0fd6e1c9efe179cbc9539ecfde2f2280c4fe"))
    (266649, uint256S("ee7c6be69ec56184531f1e97452d67933a2ed55ce5e64d81d0a1f5eaf9495d4b"))
    (277315, uint256S("82ce1b84cd1cffa868a421e5a16915ff2036888e48ac3d9c97eaf4eab0ad386f"))
    (287981, uint256S("f26140f7fdcf7408ebff1efb025879100c89f93073d6d248a931d9b1f61493bf"))
    (298647, uint256S("dad9baf34a23ed4d65ddee477a54c30c9030959daae2bde5af7c8ff156cdb1fc"))
    (309313, uint256S("a4c29f9a1b962a6b1e70ea8e2af770f94a97bf95df61a5d3c1b124119d8e1d3d"))
    (319979, uint256S("8517cd11ac84b5266dcb08f46867d0e64a7cdb243c28956899aa547f05ea4664"))
    (330645, uint256S("91253d1e61c4b4c3ff0ab779589578513c489c661848bd1a0d95be1c56bdc844"))
    (341311, uint256S("9fc50b31ba9e2c4358db3b13996756da66d32295f885f06c660117247d9947b0"))
    (351977, uint256S("5e00117c89e874c681ec0e6cf137ecabb5594491df1ba46bd7af32921e0257b0"))
    (362643, uint256S("39c1e679a1f207f270ada3faadd6590feaca770387c7a45b22457561daa77de7"))
    (373309, uint256S("97e249585a57fa14e70a8b644e21c2b3ba586eaba94363aa07ba5fe780850956"))
    (383975, uint256S("ca51187687239e0a41c8ab03e01b904f23f760b73eb44e2bb139705abf1c26f9"))
    (394641, uint256S("ac8a03339088699a18557c8f653f97415c6a15f2183dc22870ce803ed43228e6"))
    (405307, uint256S("dc8535ef477a3eae55f36062eda24d11f07e3f1d58723d4dcfd3a6235e480936"))
    (415973, uint256S("867d939fb9da486718d2d19583a37503c697c12eb87e7d3d1d5e715e1dc4cb8d"))
    (426639, uint256S("ddeca0c42452d6224f45be7c17ed6338de30320fe9d389faa14aef7880a48ef7"))
    (437305, uint256S("36e577791d21c0efef6e2e0e8574f0c74c27b7c25419b8e26de7ac881a975d74"))
    (447971, uint256S("6c172946adca7038851904c4e8fbae28e760ef8283e317afeb5deae8d73f9c38"))
    (458637, uint256S("5381ea9b006a2af3d46c375e94e944abdb16085ae5b30a8215c497ca073f6abd"))
    (469303, uint256S("f4352308187506847d37cde9f2e1ae457a4d7965f06bcb6bddca84b67c963383"))
    (479969, uint256S("a37bf7d83ac2226b498d5fbbf88f09741ee50724956ed068cf020350c75d3b40"))
    (490635, uint256S("8459e3734534275e77844910bbdc0f52f73dd486113feb7cff5e069892c54c0b"))
    (501301, uint256S("288f1422b9150fbb7e4a1bf1d6fa2917ab91c2e07d9b62d9f9381786380594fc"))
    (511967, uint256S("eab1d3276e66b696883451074aa785c1f592f8c11010e39c9ead71924aa4a76f"))
    (522633, uint256S("d752b0780df10cde0741d7d9f9dbe1221100e9ea131b0aca1e5cc78e531aa256"))
    (533299, uint256S("21f45a6d4e610b02370628c0a92cff4797391fb5c3bc446845abbc37f7c3b87e"))
    (543965, uint256S("d869a3732dc71f2b277fad098bd2465fd9ea7a79fda1ac2324764659335350da"))
    (554631, uint256S("860f35bc737c0998e7d56ad94a6d0e4c624ee18f5e9f24ae7c2643516eab56c9"))
    (565297, uint256S("509592a2dff1b4a510034cf534910fa63ed8e4e9f1c3639c6e6dc79b9cd2ab70"))
    (575963, uint256S("111b3d1fbe1f531a85400bbb7fe7b801f6c5f2668cb4557c7bcc1f4780bacb72"))
    (586629, uint256S("555449d7bd3b7b4077ea165b48c2f0651c7c76841e0ec12f50b635f1372d5cfd"))
    (597295, uint256S("ce489b455552f6f3f22c52a3e8484c694003fa7acfe31d450b4916c3b43dffc2"))
    (607961, uint256S("f0839629ee9d81da95a50f980da9b524d128f75c01b006ac068ef0b828d1e004"))
    (618627, uint256S("ea6bfc16a39c96fac1dde0aa19fb2e708eba8d1af2ff9a61e1bdacd853102cb7"))
    (629293, uint256S("482decfcafd813724efcb68baf0e1b82c544c006f9d03a10ebe1a01df54d7caf"))
    (639959, uint256S("4379c21c7260d68ace5db5e075e50e3abab9271ce9e4f555bbb1a43dd75d0cbe"))
    (650625, uint256S("7d9222b3abec525c49dcc0b9c77126b95982e65de51a55a79fe498a35794daef"))
    (661291, uint256S("24e641c7ffdbc4be3d5aace44da3e9a0371ffa43b92bcb2033845cbe41505f4a"))
    (671957, uint256S("4bf92f9858ce1dc8a1709d4cee098f536989563c73582b576f555d6360267395"))
    (682623, uint256S("913b46b6d39d3c883f955bf920cc228ea18463c5b90521643c278625e05c389d"))
    (693289, uint256S("d539f43d5bdc1a3401528caf01834192a8129cf8d4e5336ad9388dc555207649"))
    (703955, uint256S("28ef19ad091d54ddc41e719ca7964e0406c5cdb899d6b025a6f69c44e85e8d68"))
    (714621, uint256S("d29628e52c1c58cabfcc636f90a652e3da79d0588d95839cf2423454b88c2539"))
    (725287, uint256S("5bb488bde4725bee8ff6140d892b0fc1b699327e83daead0e150de05934fd400"))
    (735953, uint256S("538da0bc9830f1fcca3b2a2970bae8a36b1be165f68924236f99d82f1d73fd79"))
    (746619, uint256S("1a1e97e860e8d392b30a1b55a1f6046c104f7d67be2c4afa7788bf9e6728a8d0"))
    (757285, uint256S("15d0dd37eed9c7c69174b4df7dff6b2e83c6050ef075b4f21370702da54649a7"))
    (767951, uint256S("300817baf30766cbfad2f4a15a4739ed08f687fb1ab9e85ad3a93f0f7fd93d54"))
    (778617, uint256S("a12798e1611f236d79e3d4481c27ad64705bcb2c5e8821af4ceafb463a26b7ff"))
    (789283, uint256S("f431a7d9c04a7bc57aa9d149988df750bd0d5c3a16a0ba739b8f4e53c087ddc5"))
    (799949, uint256S("7a31c3fa89f925857798ec27956986670db7f7c65c8f010215f4572dbe2aea20"))
    (810615, uint256S("905ba241b53712b92b304b8c18f7cc946ead8423282f8809b40d2f996193ea5f"))
    (821281, uint256S("f36a8b407ef903658402013787a2a17be409ea8985afd5660585354de245b1b3"))
    (831947, uint256S("a15c5e2ada9e283b260be0b17365ee3bedcfab4eb7f7d521f499a004452e8940"))
    (842613, uint256S("e119e34e4af27290d2cfffb78639557aacaf31c0cd88855bff79b527a0669d40"))
    (853279, uint256S("407f88f394f831a4e01b6f61e9a44b084752f826c7b74a22276858aef6cc82a8"))
    (863945, uint256S("4286ac3929b96792bf54e36561e052926b5d89efe7807651b57fedc5af53699d"))
    (874611, uint256S("70df12cfe87d1648f4e6142515c2a18eda622cfdbc07d9bdb0a5d39df6cfc8d7"))
    (885277, uint256S("98387e522db02fdc746d2c49c9cc88dc8e875b7e217c1893f700b8ecc95ee42a"))
    (895943, uint256S("9eeb9f275f4a47def095246fc13f52768e2dc5f9e966bcea716346f9cd4e821a"))
    (906609, uint256S("445dca71f9f4f2602903c38aed9243eef356602bdd9a9ecb17db47a27bb8e3ee"))
    (917275, uint256S("870c7547b0a162f8491c821cab96d4eb92fe5a65202fee2af7de8d90d1e0aa41"))
    (927941, uint256S("4428a9edeed3ae3de0c2354daea0e2b8813d9dbfb5a3a23f5071661ec51690c1"))
    (938607, uint256S("217076d2ec768e40bb0bc2efe3ccfa64750549f3b7d28ecaf2a6c90048630d22"))
    (949273, uint256S("ac2c90519f9be66a26f6e331a1c0387e3ee4d0f170360983d0a9b0cf57f8aff6"))
    (959939, uint256S("dae0d55cc0553c24040185d004cf2a6a5f3ae221b5f43be18d5bd4a0408e99bf"))
    (970605, uint256S("517bc88de4bf54120e3f51cc840c3cfc526e7f694e32bf8886802a90d43c7c80"))
    (981271, uint256S("04c327f1a1b5fd61b4108d104a877c3ecfe9e83f95f05ccda7a173db49d1ff28"))
    (991937, uint256S("54e1effc480a7c7531397c36ed323d2122adb61e9522aa6598bc5c4dbe381959"))
    (1002603, uint256S("17d8f4bab57c7027fadf14e1fabf2f03c7b141641abc6e4f034bcb81b9821998"))
    (1013269, uint256S("1159466386eae2cd6d811dfff007aaa1aa47e1ae570a7686520f5c105377d946"))
    (1023935, uint256S("1bbf3b919702ce5c732db5ac45d0ef99728d9ab57844618eff6c86ad0b83b9ec"))
    (1034601, uint256S("6a15825c01b44f3f95ade73f7f97e6e415731ccd553980dc516f9a4f77c0ebde"))
    (1045267, uint256S("d458fa19ce11e0d57c8badfb2857432294e3636bcda19071f57aaa7ac1fece75"))
    (1055933, uint256S("321b4636579d2ec60c13b1055007994f70750340658d472303579eda318214c1"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1627098420, // * UNIX timestamp of last checkpoint block
    2655009,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2844        // * estimated number of transactions per day after checkpoint
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
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN;
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
        consensus.strSporkPubKey = "0391eb99d1d94bf8bbc66b39ba11c95814a2bcbcc1cf6c567c8bd58b8710b192f4";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 1599033600;
        consensus.nTime_RejectOldSporkKey = 1599030000;

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint = 1686240;
        consensus.height_last_ZC_WrappedSerials = 1686229;
        consensus.height_start_InvalidUTXOsCheck = 902850;
        consensus.height_start_ZC_InvalidSerials = 891737;
        consensus.height_start_ZC_SerialRangeCheck = 895400;
        consensus.height_ZC_RecalcAccumulators = 908000;

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
        consensus.ZC_TimeStart = 1808214600;        // October 17, 2017 4:30:00 AM
        consensus.ZC_WrappedSerialsSupply = 4131563 * COIN;   // zerocoin supply at height_last_ZC_WrappedSerials

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 501;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight                     = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight                  = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 874500;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
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
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // Ultra Clear starting difficulty is 1 / 2^12
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
        consensus.strSporkPubKeyOld = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        consensus.nTime_EnforceNewSporkKey = 1566860400;
        consensus.nTime_RejectOldSporkKey = 1569538800;

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
        nDefaultPort = 51230;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.ucrcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet ultraclear addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet ultraclear_ script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Ultra Clear BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Ultra Clear BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Ultra Clear BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // Ultra Clear starting difficulty is 1 / 2^12
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

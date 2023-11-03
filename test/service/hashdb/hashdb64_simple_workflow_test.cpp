#include <unistd.h>
#include "hashdb64_simple_workflow_test.hpp"
#include "zklog.hpp"
#include "zkresult.hpp"
#include "hashdb_factory.hpp"
#include "utils.hpp"
#include "hashdb_singleton.hpp"
#include "timer.hpp"
#include "check_tree_test.hpp"
#include "time_metric.hpp"

uint64_t HashDB64SimpleWorkflowTest (const Config& config)
{
    TimerStart(HASHDB64_SIMPLE_WORKFLOW_TEST);

    TimeMetricStorage timeMetricStorage;
    struct timeval t;

    zklog.info("HashDB64WorkflowTest() started");
    Goldilocks fr;
    PoseidonGoldilocks poseidon;
    //uint64_t tx = 0;
    zkresult zkr;
    Persistence persistence = PERSISTENCE_DATABASE;
    HashDBInterface* pHashDB = HashDBClientFactory::createHashDBClient(fr, config);
    zkassertpermanent(pHashDB != NULL);
    uint64_t flushId, storedFlushId;
    

    const uint64_t numberOfBatches = 1;
    const uint64_t numberOfTxsPerBatch = 10;
    const uint64_t numberOfSetsPerTx = 1;

    zklog.info("HashDB64WorkflowTest() numberOfBatches=" + to_string(numberOfBatches) + " numberOfTxsPerBatch=" + to_string(numberOfTxsPerBatch) + " numberOfSetsPerTx=" + to_string(numberOfSetsPerTx));

    SmtSetResult setResult;
    SmtGetResult getResult;

    Goldilocks::Element key[4]={0,0,0,0};
    Goldilocks::Element root[4]={0,0,0,0};
    Goldilocks::Element newRoot[4]={0,0,0,0};
    Goldilocks::Element keyfea[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    mpz_class value = 0;
    mpz_class valueGet = 0;
    mpz_class keyScalar = 0;
    vector<KeyValue> allKeyValues;
    Goldilocks::Element consolidatedStateRoot[4]={0,0,0,0};

    
    pHashDB->getLatestStateRoot(root);
    std::cout<<"LatestStateRoot: "<<fea2string(fr, root)<<std::endl;
    for (uint64_t batch=0; batch<numberOfBatches; batch++)
    {
        zklog.info("STARTING BATCH=" + to_string(batch));

        // Start batch
        string batchUUID = getUUID();
        vector<KeyValue> keyValues;

        // Set TXs
        for (uint64_t tx=0; tx<numberOfTxsPerBatch; tx++)
        {
            for (uint64_t set=0; set<numberOfSetsPerTx; set++)
            {
                keyScalar++;
                keyfea[0] = fr.fromU64(keyScalar.get_ui());
                poseidon.hash(key, keyfea);
                //scalar2key(fr, keyScalar, key);
                value++;
                
                zkr = pHashDB->set(batchUUID, tx, root, key, value, persistence, newRoot, &setResult, NULL);
                zklog.info("SET zkr=" + zkresult2string(zkr) + " root=" + fea2string(fr, root) + " key=" + fea2string(fr, key) + " value=" + value.get_str() + " newRoot=" + fea2string(fr, newRoot));
                zkassertpermanent(zkr==ZKR_SUCCESS);
                zkassertpermanent(!fr.isZero(newRoot[0]) || !fr.isZero(newRoot[1]) || !fr.isZero(newRoot[2]) || !fr.isZero(newRoot[3]));

                zkr = pHashDB->get(batchUUID, newRoot, key, valueGet, &getResult, NULL);
                zklog.info("GET zkr=" + zkresult2string(zkr) + " root=" + fea2string(fr, root) + " key=" + fea2string(fr, key) + " value=" + value.get_str());
                zkassertpermanent(zkr==ZKR_SUCCESS);
                zkassertpermanent(valueGet==getResult.value);
                zkassertpermanent(valueGet==value);

                
                // Advance in the state root chain
                for (uint64_t i=0; i<4; i++) root[i] = setResult.newRoot[i];

                // Take note of the key we used
                KeyValue keyValue;
                for (uint64_t i=0; i<4; i++) keyValue.key[i] = key[i];
                keyValue.value = value;
                keyValues.emplace_back(keyValue);
                
            }
            pHashDB->semiFlush(batchUUID, fea2string(fr, root), persistence);
        }
        // Purge
        zkr = pHashDB->purge(batchUUID, root, persistence);
        zkassertpermanent(zkr==ZKR_SUCCESS);
        zklog.info("PURGE zkr=" + zkresult2string(zkr) + " root=" + fea2string(fr, root));


        for (uint64_t i=0; i<allKeyValues.size(); i++)
        {
            //zklog.info("allKeyValues[" + to_string(i) + "].key=" + fea2string(fr, allKeyValues[i].key) + " .value=" + allKeyValues[i].value.get_str(10));
            mpz_class auxValue;
            gettimeofday(&t, NULL);
            zkr = pHashDB->get(batchUUID, root, allKeyValues[i].key, auxValue, &getResult, NULL);
            timeMetricStorage.add("get", TimeDiff(t));
            zkassertpermanent(zkr==ZKR_SUCCESS);
            zkassertpermanent(auxValue==allKeyValues[i].value);
        }
        allKeyValues.insert(allKeyValues.end(), keyValues.begin(), keyValues.end());
        

        // Consolidate state root every 5 batches, at batches 4, 9, 14, 19...
        Goldilocks::Element batchNewStateRoot[4];
        
        zkr = pHashDB->consolidateState(root, persistence, consolidatedStateRoot, flushId, storedFlushId);
        zkassertpermanent(zkr==ZKR_SUCCESS);
        zklog.info("CONSOLIDATE zkr=" + zkresult2string(zkr) + " virtualRoot=" + fea2string(fr, root) + " consolidatedRoot=" + fea2string(fr, consolidatedStateRoot) + " flushId=" + to_string(flushId) + " storedFlushId=" + to_string(storedFlushId));

        // New state root
        for (uint64_t i=0; i<4; i++) batchNewStateRoot[i] = consolidatedStateRoot[i];
        for (uint64_t i=0; i<4; i++) root[i] = consolidatedStateRoot[i];

        // Wait for data to be sent
        while (true)
        {
            uint64_t storedFlushId, storingFlushId, lastFlushId, pendingToFlushNodes, pendingToFlushProgram, storingNodes, storingProgram;
            string proverId;
            zkr = pHashDB->getFlushStatus(storedFlushId, storingFlushId, lastFlushId, pendingToFlushNodes, pendingToFlushProgram, storingNodes, storingProgram, proverId);
            zkassertpermanent(zkr==ZKR_SUCCESS);
            zklog.info("GET FLUSH STATUS storedFlushId=" + to_string(storedFlushId));
            if (storedFlushId >= flushId)
            {
                break;
            }
            sleep(1);
        }
        zklog.info("FLUSHED");

       #if 0

        // Call ReadTree with the new state root to get the hashes of the initial values of all read or written keys
        vector<HashValueGL> hashValues;
        vector<KeyValue> auxKeyValues = allKeyValues;
        for (uint64_t i=0; i<auxKeyValues.size(); i++)
        {
            auxKeyValues[i].value = 0;
        }

        CheckTreeTest(config);

        gettimeofday(&t, NULL);
        zkr = pHashDB->readTree(batchNewStateRoot, auxKeyValues, hashValues);
        timeMetricStorage.add("readTree", TimeDiff(t));
        zkassertpermanent(zkr==ZKR_SUCCESS);
        zklog.info("READ TREE batchNewStateRoot=" + fea2string(fr, batchNewStateRoot) + " keyValues.size=" + to_string(auxKeyValues.size()) + " hashValues.size=" + to_string(hashValues.size()));

        zkassertpermanent(auxKeyValues.size() == allKeyValues.size());
        for (uint64_t i=0; i<auxKeyValues.size(); i++)
        {
            //zklog.info("auxKeyValues[" + to_string(i) + "].key=" + fea2string(fr, auxKeyValues[i].key) + " .value=" + auxKeyValues[i].value.get_str(10));
            //zklog.info("allKeyValues[i].key=" + fea2string(fr, allKeyValues[i].key) + " .value=" + allKeyValues[i].value.get_str(10));
            if (auxKeyValues[i].value != allKeyValues[i].value)
            {
                zklog.error("HashDB64WorkflowTest() found value=" + auxKeyValues[i].value.get_str() + " != expected value=" + allKeyValues[i].value.get_str());
                return 1;
            }
            else
            {
                //zklog.error("Found value=" + auxKeyValues[i].value.get_str() + " == expected value=" + allKeyValues[i].value.get_str());
            }
            zkassertpermanent( fr.equal(auxKeyValues[i].key[0], allKeyValues[i].key[0]) &&
                                fr.equal(auxKeyValues[i].key[1], allKeyValues[i].key[1]) &&
                                fr.equal(auxKeyValues[i].key[2], allKeyValues[i].key[2]) &&
                                fr.equal(auxKeyValues[i].key[3], allKeyValues[i].key[3]) );
        }
        #endif        
    
    }

    TimerStopAndLog(HASHDB64_SIMPLE_WORKFLOW_TEST);
    Goldilocks::Element rootCons[4]={0,0,0,0};
    pHashDB->getLatestStateRoot(rootCons);
    std::cout<<"LatestStateRoot after: "<<fea2string(fr, rootCons)<<" - "<<fea2string(fr, consolidatedStateRoot)<<std::endl;
    return 0;
}
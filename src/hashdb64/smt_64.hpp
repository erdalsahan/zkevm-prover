#ifndef SMT_64_HPP
#define SMT_64_HPP

#include <vector>
#include <map>
#include <gmpxx.h>

#include "poseidon_goldilocks.hpp"
#include "goldilocks_base_field.hpp"
#include "compare_fe.hpp"
#include "database_64.hpp"
#include "database_map.hpp"
#include "zkresult.hpp"
#include "persistence.hpp"
#include "smt_set_result.hpp"
#include "smt_get_result.hpp"

using namespace std;

/*

A Tree (state) is made of a set of TreeChunks:

      /\
     /__\
        /\
       /__\
          /\
         /__\
        /\ 
       /__\

When we call SMT.get(root, key, value):
    - we want to read [key, value]
    - we call db.read(treeChunk.hash, treeChunk.data) starting from the root until we reach the [key, value] leaf node

When we call SMT.set(oldStateRoot, key, newValue, newStateRoot)
    - we want to write a new leaf node [key, newValue] and get the resulting newStateRoot
    - we calculate the new position of [key, newValue], creating new chunks if needed
    - we recalculate the hashes of all the modified and new chunks
    - we call db.write(treeChunk.hash, treeChunk.data) of all the modified and new chunks

Every time we call SMT.set(), we are potentially creating a new Tree = SUM(TreeChunks)
Every new Tree is a newer version of the state
Many Trees (states) coexist in the same Forest (state history)
Every executor.processBatch() can potentially create several new Trees (states)
The Forest takes note of the latest Tree hash to keep track of the current state:

     SR1      SR2      SR3      SR4
     /\       /\       /\       /\
    /__\     /__\     /__\     /__\
                /\       /\       /\
               /__\     /__\     /__\
                           /\       /\
                          /__\     /__\
                                  /\ 
                                 /__\

*/

class SmtContext64
{
public:
    Database64 &db;
    bool bUseStateManager;
    const string &batchUUID;
    uint64_t tx;
    const Persistence persistence;
    SmtContext64(Database64 &db, bool bUseStateManager, const string &batchUUID, uint64_t tx, const Persistence persistence) :
        db(db),
        bUseStateManager(bUseStateManager),
        batchUUID(batchUUID),
        tx(tx),
        persistence(persistence) {};
};

// SMT class
class Smt64
{
private:
    Goldilocks  &fr;
    PoseidonGoldilocks poseidon;
    Goldilocks::Element capacityZero[4];
    Goldilocks::Element capacityOne[4];
public:
    Smt64(Goldilocks &fr) : fr(fr)
    {
        capacityZero[0] = fr.zero();
        capacityZero[1] = fr.zero();
        capacityZero[2] = fr.zero();
        capacityZero[3] = fr.zero();
        capacityOne[0] = fr.one();
        capacityOne[1] = fr.zero();
        capacityOne[2] = fr.zero();
        capacityOne[3] = fr.zero();
    }
    zkresult set(const string &batchUUID, uint64_t tx, Database64 &db, const Goldilocks::Element (&oldRoot)[4], const Goldilocks::Element (&key)[4], const mpz_class &value, const Persistence persistence, SmtSetResult &result, DatabaseMap *dbReadLog = NULL);
    zkresult get(const string &batchUUID, Database64 &db, const Goldilocks::Element (&root)[4], const Goldilocks::Element (&key)[4], SmtGetResult &result, DatabaseMap *dbReadLog = NULL);
    zkresult hashSave(const SmtContext64 &ctx, const Goldilocks::Element (&v)[12], Goldilocks::Element (&hash)[4]);

    // Consolidate value and capacity
    zkresult hashSave(const SmtContext64 &ctx, const Goldilocks::Element (&a)[8], const Goldilocks::Element (&c)[4], Goldilocks::Element (&hash)[4])
    {
        // Calculate the poseidon hash of the vector of field elements: v = a | c
        Goldilocks::Element v[12];
        for (uint64_t i=0; i<8; i++) v[i] = a[i];
        for (uint64_t i=0; i<4; i++) v[8+i] = c[i];
        return hashSave(ctx, v, hash);
    }
    
    // Use capacity zero for intermediate nodes and value hashes
    zkresult hashSaveZero(const SmtContext64 &ctx, const Goldilocks::Element (&a)[8], Goldilocks::Element (&hash)[4])
    {
        return hashSave(ctx, a, capacityZero, hash);
    }
    
    // Use capacity one for leaf nodes
    zkresult hashSaveOne(const SmtContext64 &ctx, const Goldilocks::Element (&a)[8], Goldilocks::Element (&hash)[4])
    {
        return hashSave(ctx, a, capacityOne, hash);
    }

    zkresult updateStateRoot(Database64 &db, const Goldilocks::Element (&stateRoot)[4]);
    int64_t getUniqueSibling(vector<Goldilocks::Element> &a);
};

#endif
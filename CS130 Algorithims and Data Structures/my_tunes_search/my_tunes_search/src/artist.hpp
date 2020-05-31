#include <string>
#include <set>
using namespace std;

struct ARTIST {
    std::string name;
    std::set<std::string> songs;
};

enum STATUS { EMPTY_SINCE_START, EMPTY_AFTER_REMOVAL, OCCUPIED };
struct BUCKET {
    ARTIST *art;
    STATUS st;
};
typedef BUCKET *HASHTABLE_OA;

static std::hash<std::string> HashFunc1;
unsigned long HashFunc2(std::string input_str);

/* Function: NextBucket
 * ---
 * Two hash functions (HashFunc1 and HashFunc2 that take a string as a
 * parameter and return an unsigned long) are provided for you to use.
 * These hash functions will be used to calculate the BUCKET to check
 * in the functions below (Insert, Remove, and Search) using double
 * hashing as described in lecture and your zyBook.. You should use the
 * hash value of the ARTIST*’s name returned by HashFunc1 and HashFunc2
 * as the parameter values passed to the NextBucket function for hash val1
 * and hash val2, respectively.
 */
unsigned long NextBucket(unsigned long hash_val1, unsigned long hash_val2, int i, int table_size);

/* Function: Initialize
 * ---
 * This function takes two parameters: table and table size. This function will
 * initialize the HASHTABLE & table so that each BUCKET* in the table has memory
 * allocated for it. The ARTIST* art of each BUCKET should be initialized to
 * a NULL pointer. The STATUS st of each BUCKET should be initialized to
 * EMPTY SINCE START.

 */
void Initialize(HASHTABLE_OA *&table, int table_size);

/* Function: Clear
 * ---
 * This function takes two parameters: table and table size.
 * This function will delete the memory allocated for each BUCKET* in
 * the table. If the ARTIST* art of the BUCKET is not NULL, the
 * memory for art should be deleted as well.
 */
void Clear(HASHTABLE_OA *&table, int table_size);

/* Function: Insert
 * ---
 * This function takes three parameters: a HASHTABLE OA*& table, an
 * int& table size, and an ARTIST* art. When this function is executed
 * art is inserted into table at the first non-OCCUPIED bucket encountered
 * using the double hashing algorithm. The key to hash for inserting art
 * should be the name of art. If an ARTIST* already exists in the table,
 * art should replace the ARTIST* currently stored in table. When inserting
 * an ARTIST* into the hash table, the STATUS of the BUCKET in which it is
 * entered should be updated to be be OCCUPIED and the function will return
 * true.
 */
bool Insert(HASHTABLE_OA *&table, int &table_size, ARTIST*);

/* Function: Search
 * ---
 * This function takes three parameters: a HASHTABLE OA*& table, an
 * int table size, and a std::string key. This function will search
 * table for an ARTIST* stored in table which has a name equal to key.
 * The function will use the double hashing technique to search the table
 * for an ARTIST* with a name equal to key until one of 3 conditions are met:
 *
 * 1) An ARTIST* with name equal to key is found. The function should return
 * the matching ARTIST* in this case.
 *
 * 2) A BUCKET is reached in the search which has an st value of
 * EMPTY_SINCE_START. The function should return NULL in this case.
 *
 * 3) All BUCKET s have been checked without finding an ARTIST* having
 * name equal to key. The function should return NULL in this case.
 */
ARTIST* Search(HASHTABLE_OA *table, int table_size, std::string key);

/* Function: Remove
 * ---
 * This function takes three parameters: a HASHTABLE OA* & table, an int
 * table size, and a std::string key. This function will search table
 * for an ARTIST* stored in table which has a name equal to key. The
 * function will use double hashing to search the table for an ARTIST*
 * with a name equal to key until one of 3 conditions are met:
 *
 * 1) An ARTIST* with name equal to key is found. In this case, the memory
 * for the ARTIST* is deleted, the ARTIST* art data member of the BUCKET
 * is set to NULL and the BUCKET ’s st data member is set to EMPTY_AFTER_REMOVAL.
 * The function should return true in this case.
 *
 * 2) A BUCKET is reached in the search which has an st value of
 * EMPTY_SINCE_START. The function should return false in this case.
 *
 * 3) All BUCKET s have been checked without finding an ARTIST* having
 * name equal to key. The function should return false in this case.
 */
bool Remove(HASHTABLE_OA *&table, int table_size, std::string key);

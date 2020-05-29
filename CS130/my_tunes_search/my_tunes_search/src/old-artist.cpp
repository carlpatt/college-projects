#include "artist.hpp"
#include <iostream>

unsigned long HashFunc2(std::string input_str){
    unsigned long hash = 5381;
    int c;
    const char *chr_str = input_str.c_str();

    while ((c = *chr_str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */


    return hash;
}

unsigned long NextBucket(unsigned long hash_val1, unsigned long hash_val2, int i, int table_size) {
    return ((hash_val1 + i * hash_val2) % table_size);
}

void Initialize(HASHTABLE_OA *&table, int table_size) {
    for (int i = 0; i <= table_size; i++) {
        table[i] = new BUCKET;
        table[i]->art = NULL;
        table[i]->st = EMPTY_SINCE_START;
    } 
}

void Clear(HASHTABLE_OA *&table, int table_size) {
    for (int i = 0; i <= table_size; i++) {
        delete table[i]->art;
        delete table[i]; 
    }
}

bool Insert(HASHTABLE_OA *&table, int &table_size, ARTIST* art) {
    unsigned long hash_val1 = HashFunc1(art->name);
    unsigned long hash_val2 = HashFunc2(art->name);

    int bucket, buckets_checked, i = 0;
    bucket = NextBucket(hash_val1, hash_val2, i, table_size);  

    while (buckets_checked < table_size) {
        if (table[bucket]->st != OCCUPIED) {
            table[bucket]->art = art;
            table[bucket]->st = OCCUPIED;
            return true;
        }
        if (table[bucket]->art->name == art->name) {
            table[bucket]->art = art;
            table[bucket]->st = OCCUPIED;
            return true;
        }
        bucket = NextBucket(hash_val1, hash_val2, i++, table_size);  
        buckets_checked++;
    }
    return false;
}

ARTIST* Search(HASHTABLE_OA *table, int table_size, std::string key) {
    unsigned long hash_val1 = HashFunc1(key); 
    unsigned long hash_val2 = HashFunc1(key); 

    int bucket, buckets_checked, i = 0; 
    bucket = NextBucket(hash_val1, hash_val2, i, table_size);  

    while(buckets_checked < table_size) {	
        if(table[bucket]->art->name == key) {
            return table[bucket]->art;
        }
        if(table[bucket]->st == EMPTY_SINCE_START) {
            return NULL;
        }
    }
    bucket = NextBucket(hash_val1, hash_val2, i++, table_size);  
    buckets_checked++;
    return NULL; 
}

bool Remove(HASHTABLE_OA *&table, int table_size, std::string key) {
    unsigned long hash_val1 = HashFunc1(key); 
    unsigned long hash_val2 = HashFunc1(key); 

    int bucket, buckets_checked, i = 0;
    bucket = NextBucket(hash_val1, hash_val2, i, table_size); 

    while (buckets_checked < table_size) {
        if (table[bucket]->art->name == key) {
            delete table[bucket]->art;
            table[bucket]->art = NULL;
            table[bucket]->st = EMPTY_AFTER_REMOVAL;
            return true;
        }
        if (table[bucket]->st == EMPTY_SINCE_START) {
            return false;
        }
        bucket = NextBucket(hash_val1, hash_val2, i++, table_size);  
        buckets_checked++;
    }
    return false; 
}

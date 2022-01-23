#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "hash.h"


// its to check if lines exist or not so bool should be fine ... ig.


// salt, last -> result in the same slot !
int hash(char *key, int lineNo) {
    uint32_t slot = 0;

    for (uint8_t i = 0; i < strlen(key); i++) {
        slot += key[i] - (lineNo + i) / key[i]; // but division does not have great performance !
    }

    slot = slot * strlen(key) * lineNo;
    // printf("%s %d", key, slot% TABLESIZE);
    return slot % TABLESIZE;
}

bool hash_insert(Hashtable hash_table, char *key, int lineNo) {
    // printf("%s <%d>\n", key, lineNo);
    int slot = hash(key, lineNo);
    if (hash_table[slot] != false) return false; // collision ! slot is occupied.
    return (hash_table[slot] = true);
};

bool hash_lookup(Hashtable hash_table, char *key, int lineNo) {
    // printf("%s <%d>\n", key, lineNo);
    int slot = hash(key, lineNo);
    return hash_table[slot];
    // if (hash_table[slot] != 0) return false; // collision !
    // return (hash_table[slot] = true);
}

void print_hash(Hashtable hash_table, uint8_t limit, bool true_only) {
    printf("Slots:\titems:\n");
    // printf("limit: <%d>\n", limit); // NULL means 0;
    limit = (limit == 0 || limit > TABLESIZE) ? TABLESIZE : limit;
    for (uint8_t i = 0; i < limit; ++i)
    {
        if (true_only)
        {
            if (hash_table[i] == true)
                printf("%d\t %d\n", i, hash_table[i]);
        }
        else {
            printf("%d\t %d\n", i, hash_table[i]);
        }
    }
}

// I wonder which one would be better....
// bool hash_delete(char *key, int lineNo) {
//     int slot = hash(key, lineNo);
//     if (hash_table[slot] == false) return false; // collision ! slot is occupied.
//     hash_table[slot] = false;
//     return true;
// }

void hash_delete(Hashtable hash_table, char *key, int lineNo) {
    int slot = hash(key, lineNo);
    hash_table[slot] = false;
}

// A good hash function: https://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html

/*
hash tables work well when the hash function satisfies the simple uniform hashing assumption 
-- that the hash function should look random. If it is to look random, this means that any 
change to a key, even a small one, should change the bucket index in an apparently random way.
if we imagine writing the bucket index as a binary number, a small change to the key should
randomly flip the bits in the bucket index. This is called information diffusion. 
For example, a one-bit change to the key should cause every bit in the index to flip with 1/2 probability.
*/


// uint64_t* matches should contain the slot numbers of the matching lines
uint64_t ht_compare(Hashtable ht1, Hashtable ht2, uint64_t* matches)
{
    // print_hash(ht1, 0, true);
    // print_hash(ht2, 0, true);

    uint64_t matches_i = 0;

    for (uint64_t i = 0; i < TABLESIZE; ++i)
    {
        if (ht1[i] == true && ht2[i] == true)
        {
            matches[matches_i++] = i;
        }
    }

    return matches_i;
}

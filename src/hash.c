#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define tablesize 100


// salt, last -> result in the same slot !
int hash(char *key) {
    uint32_t slot = 0;

    for (uint8_t i = 0; i < strlen(key); i++) {
        slot += key[i];
    }

    slot = slot * strlen(key);

    return slot % tablesize;
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
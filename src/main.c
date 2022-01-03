#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hash.h"

int main() {
    // char* key = "name";
    // int slot = hash(key, 1);
    // printf("slot: %d\n", slot);

    // key = "salt";
    // slot = hash(key, 2);
    // printf("slot: %d\n", slot);

    // key = "last";
    // slot = hash(key, 3);
    // printf("slot: %d\n", slot);

    bool hash_table[TABLESIZE] = {12};
    init_hash_table(&hash_table);

    hash_insert("nice ck", 10);
    bool exists = hash_lookup("nice ck", 10);
    printf("exists <%d>\n", exists);

    hash_insert("nice ck", 10);
    exists = hash_lookup("niadse ck", 10);
    printf("exists <%d>\n", exists);

    print_hash(0);

    return 0;
}
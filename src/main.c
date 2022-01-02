#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hash.h"

int main() {
    char* key = "name";
    int slot = hash(key);
    printf("slot: %d\n", slot);

    key = "salt";
    slot = hash(key);
    printf("slot: %d\n", slot);

    key = "last";
    slot = hash(key);
    printf("slot: %d\n", slot);
    return 0;
}
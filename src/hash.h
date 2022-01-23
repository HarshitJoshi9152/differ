#pragma once

#include <stdbool.h>

// should TABLESIZE be determined dynamically according to the no of lines in the files !? 
#define TABLESIZE 1000

// typedef bool * Hashtable;

typedef bool Hashtable[TABLESIZE]; // this is BAD abstraction

// typedef struct Hashtable { bool ht_array[TABLESIZE]; } Hashtable;

int hash(char *key, int lineNo);
void print_hash(Hashtable hash_table, uint8_t limit, bool true_only);
bool hash_lookup(Hashtable hash_table, char *key, int lineNo);
bool hash_insert(Hashtable hash_table, char *key, int lineNo);
void hash_delete(Hashtable hash_table, char *key, int lineNo);
uint64_t ht_compare(Hashtable ht1, Hashtable ht2, uint64_t* matches);

#pragma once

#include <stdbool.h>

// should TABLESIZE be determined dynamically according to the no of lines in the files !? 
#define TABLESIZE 100

typedef bool Hashtable[TABLESIZE]; // this is BAD abstraction

int hash(char *key, int lineNo);
void print_hash(Hashtable hash_table, uint8_t limit, bool true_only);
bool hash_lookup(Hashtable hash_table, char *key, int lineNo);
bool hash_insert(Hashtable hash_table, char *key, int lineNo);
void hash_delete(Hashtable hash_table, char *key, int lineNo);

#pragma once

#include <stdbool.h>

// should TABLESIZE be determined dynamically according to the no of lines in the files !? 
#define TABLESIZE 100

int hash(char *key, int lineNo);
void init_hash_table();
void print_hash(uint8_t limit, bool true_only);
bool hash_lookup(char *key, int lineNo);
bool hash_insert(char *key, int lineNo);
void hash_delete(char *key, int lineNo);

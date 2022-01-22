#pragma once

#include "hash.h"

#define DEF_LINE_SIZE 100
typedef struct linkedLines {
    char *data;
    struct linkedLines *nextLine;
} LinkedLines;

char *readFile(const char* filename);
LinkedLines splitByLines(const char *str, uint64_t *linesCount);
void printlines(LinkedLines* line);
void freeLinkedLines(LinkedLines* line);
void insertLinkedLinesIntoHashTable(Hashtable ht, LinkedLines *ll, uint32_t *linesSlots);
void printLinesSelectively(LinkedLines *line, uint32_t *slots, bool matching);

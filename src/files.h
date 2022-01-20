#pragma once

#define DEF_LINE_SIZE 100
typedef struct linkedLines {
    char *data;
    struct linkedLines *nextLine;
} LinkedLines;

char *readFile(const char* filename);
LinkedLines splitByLines(const char *str, uint64_t *linesCount);
void printlines(LinkedLines* line);
void freeLinkedLines(LinkedLines* line);
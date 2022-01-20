#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "files.h"
#include "hash.h"
//  returns a calloc allocated buffer which contains the contents of the file read as characters.
//  make sure to call free after this !
char *readFile(const char* filename)
{
    FILE *f1 = fopen(filename, "r");

    if (f1 == NULL) {
        errno = 1;
        fprintf(stderr, "Input File Inaccessible.\n");
        exit(1);
    }

    // finding the size of file to allocate the memory.
    fseek(f1, 0, SEEK_END);
    uint64_t size = ftell(f1);
    rewind(f1);

    char *data = calloc(size, 1);
    if (data == NULL) {
        errno = 1;
        fclose(f1);
        fprintf(stderr, "Failed to allocate memory for file contents.\n");
        exit(1);
    }

    fread(data, /*sizeof(char)*/ 1, size, f1);

    fclose(f1);
    return data;
}

LinkedLines splitByLines(const char *str, uint64_t *linesCount)
{
    uint64_t len = strlen(str);
    size_t lC = 0;
    size_t charCount = 0;

    int buffer_size = DEF_LINE_SIZE;
    char *buffer = calloc(buffer_size, 1);
    // NULL pointer check
    if (buffer == NULL) {
        errno = 1;
        fprintf(stderr, "Failed to allocate memory for line %ld.\n", lC + 1);
        // todo: we should free memory before exiting.
        exit(1);
    }
    LinkedLines first = {.data = buffer, .nextLine = NULL};

    LinkedLines *line = &first;

    for (size_t i = 0; i < len; ++i)
    {
        char c = str[i];
        // checking if our allocated buffer has overflowed its capacity. for the current line.
        if (charCount > buffer_size) {
            // we need to realloc it !
            buffer_size += buffer_size;
            line->data = realloc(line->data, buffer_size);
            // NULL pointer check
            if (line->data == NULL) {
                errno = 1;
                fprintf(stderr, "Failed to allocate memory for line %ld.\n", lC + 1);
                // todo: we should free memory before exiting.
                exit(1);
            }
        }
        // adding char to data.
        line->data[charCount++] = c;
        // moving to next line.
        if (c == '\n')
        {
            // adding NULL character at end of string;
            line->data[charCount++] = '\x00';
            // reseting variables;
            lC++;
            charCount = 0;
            buffer_size = DEF_LINE_SIZE; // the next line may not need such a large buffer;
            // moving to next line;
            buffer = calloc(buffer_size, 1);
            // NULL pointer check
            if (buffer == NULL) {
                errno = 1;
                fprintf(stderr, "Failed to allocate memory for line %ld.\n", lC + 1);
                // todo: we should free memory before exiting.
                exit(1);
            }

            LinkedLines *next = calloc(sizeof(LinkedLines), 1);
            next->data =buffer;

            line->nextLine = next;
            line = next;
        }
    }

    *linesCount = lC;

    return first;
}

void printlines(LinkedLines* line)
{
    LinkedLines *tempLine = line;
    while(tempLine) {
        printf("%s", tempLine->data);
        // printf("<tempLine->data %p>\n", tempLine->data);
        // printf("<tempLine %p>\n", tempLine);
        // printf("<stlen %ld>\n", strlen(tempLine->data));

        // if (tempLine->nextLine == NULL) break;
        tempLine = tempLine->nextLine;
    }
}

void freeLinkedLines(LinkedLines* line)
{
    LinkedLines *tempLine = line;
    while(tempLine) {
        LinkedLines *nextLine = tempLine->nextLine;

        free(tempLine->data);
        free(tempLine);

        tempLine = nextLine;
    }
}

// would the pointer get mutated ?, can i do int* arrya = {1,6,2,34,5}; arrya[1] = 4; ??
void insertLinkedLinesIntoHashTable(Hashtable *ht, LinkedLines *ll, uint32_t *linesSlots)
{   
    while(ll) {
        char* line = ll->data;
        uint64_t linesCount = 1; // startign with 0 will result in bad hash function output value.

        uint32_t slot = hash(line, linesCount);
        bool inserted = hash_insert(ht, line, linesCount);

        if (inserted == false) {
            fprintf(stderr, "COllision ! @ %d %s\n line: %s <%ld>\n", __LINE__, __FILE__, line, linesCount);
            exit(1);
        }

        linesSlots[linesCount - 1] = slot;
        linesCount++;
        ll = ll->nextLine;
    }
    
}
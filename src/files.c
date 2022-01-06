#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "files.h"
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
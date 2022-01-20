#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include "hash.h"
#include "files.h"

// const char* program_name = "differ";


// if the user has not provided the arg the str will point to NULL;

int main(int argc, char *argv[]) {

    // https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
    // we could use https://github.com/cofyc/argparse or https://github.com/tsoding/flag.h too !
    // man getopt : get_option; optin: optionindex (next to be parsed); optarg: holds the actual value *char
    // $ cheat c getopt
    // int rt = getopt(argc, argv, "f::");
    // // :: means optional argument and : means required arg
    // // : captures both -fname and -f name BUT :: doesn't capture -f name1

    // printf("rt <%c>\n", rt);
    // if (rt != -1 && optarg != NULL) printf("%s\n", optarg);

    const char* program = *argv++;
    assert(program != NULL);
    const char* file_path1 = *argv++;
    if (file_path1 == NULL)
    {
        fprintf(stderr, "USAGE: %s <filepath1> <filepath2>\n", program);
        fprintf(stderr, "ERROR: file_path1 not provided\n");
        exit(1);
    }
    const char* file_path2 = *argv++;
    if (file_path2 == NULL)
    {
        fprintf(stderr, "USAGE: %s <filepath1> <filepath2>\n", program);
        fprintf(stderr, "ERROR: file_path2 not provided\n");
        exit(1);
    }

    // // to be taken in from the argv
    // const char* demoFilename1 = "../test/file1.txt";
    // const char* demoFilename2 = "../test/file2.txt";

    // reading files !
    char *f1 = readFile(file_path1);
    char *f2 = readFile(file_path2);


    // spliting file contents by lines.
    uint64_t f1_linesCount = 0;
    LinkedLines f_split_by_lines_1 = splitByLines(f1, f1_linesCount);
    uint64_t f2_linesCount = 0;
    LinkedLines f_split_by_lines_2 = splitByLines(f2, f2_linesCount);

    // freeing files in memory
    free(f1);
    free(f2);

    // printlines(&f_split_by_lines_1);
    // printlines(&f_split_by_lines_2);

    Hashtable hash_table = {0};
    uint64_t tableItemsCount = 0;

    // recording lines' unique existence from file 1 into hash_table.
    LinkedLines *tempLine = &f_split_by_lines_1;
    uint64_t linesCount = 1;
    uint32_t *linesSlots = calloc(f1_linesCount, sizeof(uint32_t)) // to store the slotNo of the lines (line no is index and val is slotNo for that line)

    while(tempLine) {
        char* line = tempLine->data;

        // int slot = hash(line);
        bool inserted = hash_insert(&hash_table, line, linesCount);
        if (inserted == false) {
            fprintf(stderr, "COllision ! @ %d %s\n line: %s <%ld>\n", __LINE__, __FILE__, line, linesCount);
            exit(1);
        }

        linesCount++;
        tableItemsCount++;

        tempLine = tempLine->nextLine;
    }
    
    // check if file2 contains the same lines too !
    tempLine = &f_split_by_lines_2;
    linesCount = 1;
    uint64_t file2_mismatches = 0;
    while(tempLine) {
        char* line = tempLine->data;

        // int slot = hash(line);
        bool found = hash_lookup(&hash_table, line, linesCount);
        if (found == true) {
            tableItemsCount--;
        } else {
            file2_mismatches++;
        }

        linesCount++;

        tempLine = tempLine->nextLine;
    }

    // print_hash(0, true);

    // we need to output this like a table !
    printf("total mismatches : %ld \n", tableItemsCount + file2_mismatches);
    printf("mismatched in %s : %ld \n", file_path1, tableItemsCount);
    printf("mismatches in %s : %ld \n", file_path2, file2_mismatches);

    freeLinkedLines(f_split_by_lines_1.nextLine); // f_split_by_lines_1 is allocated on the stack !
    freeLinkedLines(f_split_by_lines_2.nextLine);

    return 0;
}

/* TODO

1. bad code change it to make both files hash_tables and compare the hash_tables to find differences
2. somehow add reporting which lines are different (line and lineNo) and identify diff content on same line nos.

*/
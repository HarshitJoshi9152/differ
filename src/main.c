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
    bool f1_new_line_ending = f1[strlen(f1) - 1] == '\n'; // checking if last char is new line or not.
    
    char *f2 = readFile(file_path2);
    bool f2_new_line_ending = f1[strlen(f1) - 1] == '\n'; // checking if last char is new line or not.


    // spliting file contents by lines.
    uint64_t f1_linesCount = 0;
    LinkedLines f_split_by_lines_1 = splitByLines(f1, &f1_linesCount);
    uint64_t f2_linesCount = 0;
    LinkedLines f_split_by_lines_2 = splitByLines(f2, &f2_linesCount);

    // freeing files in memory
    free(f1);
    free(f2);

    // printlines(&f_split_by_lines_1);
    // printlines(&f_split_by_lines_2);

    // make hash_table 1.
    Hashtable f1_hash_table = {0};
    // the next line is dangerous
    uint32_t *f1_linesSlots = calloc(f1_linesCount, sizeof(uint32_t)); // to store the slotNo of the lines (line no is index and val is slotNo for that line)

    insertLinkedLinesIntoHashTable(f1_hash_table, &f_split_by_lines_1, f1_linesSlots);

    // make hash_table 2.
    Hashtable f2_hash_table = {0};
    // the next line is dangerous
    uint32_t *f2_linesSlots = calloc(f2_linesCount, sizeof(uint32_t)); // to store the slotNo of the lines (line no is index and val is slotNo for that line)

    insertLinkedLinesIntoHashTable(f2_hash_table, &f_split_by_lines_2, f2_linesSlots);
    
    // compare and take the sets approach
    // ALTHOUGH we can probably just compare the $linesSlots at this point lol
    /*
    uint64_t greater_line_ln = (f1_linesCount > f2_linesCount) ? f1_linesCount : f2_linesCount;
    uint64_t *matching_ln = calloc(greater_line_ln, sizeof(uint64_t));
    uint64_t matching_len = ht_compare(f1_hash_table, f2_hash_table, greater_line_ln, matching_ln);
    */

    uint64_t max_matching_len = (f1_linesCount > f2_linesCount) ? f1_linesCount : f2_linesCount;
    uint64_t *matching_slots = calloc(max_matching_len, sizeof(uint64_t));
    uint64_t matching_len = ht_compare(f1_hash_table, f2_hash_table, matching_slots);

    // we have the slots so potentially we have lines_nos of the lines that match and dont match !
    // for (int i = 0; i < matching_len; i++)
    // {
    //     uint64_t match_slot = matching_slots[i];
    //     printf("%ld ", match_slot);
    // }

    // comparing the matching_slots to both files's lineSlots to group matching and non matching lines.

    // filtering the lines that are matching
    for (int lineNo = 0; lineNo < f1_linesCount; ++lineNo)
    {
        uint32_t *line_slot = f1_linesSlots + lineNo;
        for (int ii = 0; ii < matching_len; ++ii)
        {
            uint32_t slot = matching_slots[ii];
            // printf("> %d\t%d\t %d\n", *line_slot, slot, *line_slot == slot );
            /*
            WTH : this is something new that i learnt !
            > 5     5        0
            > 5     18       0
            > 64    5        0
            > 64    18       0
            > 18    5        0
            > 18    18       0
            > 80    5        0
            > 80    18       0
            > 50    5        0
            > 50    18       0
            > 92    5        0
            > 92    18       0
            COZ I HAD 
                    uint64_t *line_slot = f1_linesSlots + lineNo;
            warning: initialization of ‘uint64_t *’ {aka ‘long unsigned int *’} from incompatible pointer type ‘uint32_t *’ {aka ‘unsigned int *’}
            */
            if (*line_slot == slot) // slot should not be zero.
            {
                // set this to 0. having a slot of 0 does not count.
                *line_slot = 0;
                break;
            }
        }
    }
    // after this the indexes (lineNos) left with non zero values will be the ones that were different

    // filtering the lines that are matching
    for (int lineNo = 0; lineNo < f2_linesCount; ++lineNo)
    {
        uint32_t *line_slot = f2_linesSlots + lineNo;
        for (int ii = 0; ii < matching_len; ++ii)
        {
            uint32_t slot = matching_slots[ii];
            if (*line_slot == slot && *line_slot != 0) // slot should not be zero.
            {
                // set this to 0. having a slot of 0 does not count.
                *line_slot = 0;
                break;
            }
        }
    }
    // after this the indexes (lineNos) left with non zero values will be the ones that were different


    // we need to output this like a table !
    printf("total matches : %ld \n", matching_len);
    // printf("total mismatches : %ld \n", f1_linesCount + 2 + f2_linesCount - (matching_len * 2));
    printf("lines not matching in %s : %ld\n", file_path1, f1_linesCount - matching_len);
    printf("lines not matching in %s : %ld\n", file_path2, f2_linesCount - matching_len);
    printf("\n");
    
    printf("Matching lines :\n");
    printLinesSelectively(&f_split_by_lines_1, f1_linesSlots, true);
    if (f1_new_line_ending == false) printf("\n");
    
    printf("\nnon matching lines %s:\n", file_path1);
    printLinesSelectively(&f_split_by_lines_1, f1_linesSlots, false);
    if (f1_new_line_ending == false) printf("\n");
    
    printf("\nnon matching lines %s:\n", file_path2);
    printLinesSelectively(&f_split_by_lines_2, f2_linesSlots, false);
    if (f2_new_line_ending == false) printf("\n");

    // memory allocataion should be avoided.
    free(f1_linesSlots);
    free(f2_linesSlots);
    free(matching_slots);
    free(f_split_by_lines_1.data);
    free(f_split_by_lines_2.data);
    freeLinkedLines(f_split_by_lines_1.nextLine); // f_split_by_lines_1 is allocated on the stack !
    freeLinkedLines(f_split_by_lines_2.nextLine);

    return 0;
}

/* TODO

1. improve the hash function, too frequent collisions.

*/
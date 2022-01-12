#include <stdio.h>
#include <stdint.h>
#include <string.h>
// #include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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
    }
    const char* file_path2 = *argv++;
    if (file_path2 == NULL)
    {
        fprintf(stderr, "USAGE: %s <filepath1> <filepath2>\n", program);
        fprintf(stderr, "ERROR: file_path2 not provided\n");
    }

    // to be taken in from the argv
    const char* demoFilename1 = "../test/file1.txt";
    const char* demoFilename2 = "../test/file2.txt";

    // reading files !
    char *f1 = readFile(demoFilename1);
    char *f2 = readFile(demoFilename2);

    // printf(f1);
    // printf(f2);

    // char * ff1 = f1;
    // char * ff2 = f2;
    // free(f1);
    // free(f2);

    // spliting file contents by lines.
    LinkedLines f_split_by_lines_1 = splitByLines(f1);
    // printf("<%s>\n\n", f_split_by_lines_1.data);
    // printf("<%p>\n\n", f_split_by_lines_1.nextLine);

    LinkedLines f_split_by_lines_2 = splitByLines(f2);

    printlines(&f_split_by_lines_1);
    printlines(&f_split_by_lines_2);

    freeLinkedLines(f_split_by_lines_1.nextLine);
    freeLinkedLines(f_split_by_lines_2.nextLine);

    // printlines(&f_split_by_lines_1);
    // printlines(&f_split_by_lines_2);


    // bool hash_table[TABLESIZE] = {12};
    // init_hash_table(&hash_table);

    // hash_insert("nice ck", 10);
    // bool exists = hash_lookup("nice ck", 10);
    // printf("exists <%d>\n", exists);

    // hash_insert("nice ck", 10);
    // exists = hash_lookup("niadse ck", 10);
    // printf("exists <%d>\n", exists);

    // print_hash(0);

    return 0;
}
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "hash.h"
#include "files.h"

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

    // to be taken in from the argv
    const char* demoFilename1 = "../test/file1.txt";
    const char* demoFilename2 = "../test/file2.txt";

    char* f1 = readFile(demoFilename1);
    char* f2 = readFile(demoFilename2);

    printf(f1);
    printf(f2);

    free(f1);
    free(f2);

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

CC=gcc
CFLAGS=-Wall -g
build_dir=../build

# all signifance !
# https://stackoverflow.com/a/2515000/9596267
all: differ

# differ: $(build_dir)/*.o
differ: $(build_dir)/main.o $(build_dir)/hash.o  $(build_dir)/files.o
	$(CC) $(CFLAGS) $(build_dir)/*.o -o $(build_dir)/differ
# previously was $(CC) $(CFLAGS) $(build_dir)/main.o $(build_dir)/hash.o -o $(build_dir)/differ

# this is avoid typing this section for all the .c files we want to compile
# but this compiles them in the current dir, we want to do so in the build/ dir
$(build_dir)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
# $(CC) $(CFLAGS) -c -o $(build_dir)/$@ $<

# $@ and $< https://unix.stackexchange.com/a/116553/497721
# i used `$(CC) $(CFLAGS) -c $^` before
clean:
	rm $(build_dir)/*.o $(build_dir)/differ

# pre processing [Pre processor] 
# 	$ gcc -E
# 	expands the macros, includes the headers, etc
# C to assembly (.c to .S) [compiler]
#	$ gcc -S
# [Assembler]
# 	$ gcc -c
# binary executable code in object files (.o)
# [Linker] linking
# links all the compiled => a.out


# so that just the changed pieces need to be recompiled
# the ones that stay smae can be linked to the newly 
# compiled object file

# Compiling C programs with Multiple Files
# https://www.youtube.com/watch?v=2YfM-HxQd_8


# main.c	-> main code
# sub.c		-> helper functions
# sub.h		-> only declarations for sub.c
# 
# compiling:
# $ clang -c main.c
# $ clang -c sub.c
# $ clang main.o sub.o
# 
# so now if we change a function in sub.c file we only have o
# recompile the sub.c file and relink sub.o ! which is faster !
# 
# benefits of this approach: more organised, errors are easier to associate with files in which they occur






# CC=gcc
# CFLAGS=-Wall -g

# # all meaning !
# # https://stackoverflow.com/a/2515000/9596267
# all: differ

# differ: main.o hash.o
# 	$(CC) $(CFLAGS) main.o hash.o -o differ

# # this is avoid typing this section for all the .c files we want to compile
# # but this compiles them in the current dir, we want to do so in the build/ dir
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $^

# # $@ and $< https://unix.stackexchange.com/a/116553/497721
# clean:
# 	rm *.o differ

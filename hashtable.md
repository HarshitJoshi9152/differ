# hashtables


Common implementations of hash tables

1. hashing with chaining
2. linear probing


A ChainedHashTable data structure uses hashing with chaining to store data as an array, `t`,
of lists. An integer, `n`, keeps track of the total number of items in all lists

I found something cool : https://www.cs.dartmouth.edu/doug/diff.pdf

properties of a good hash function !
    diff input diff output
    same input same output | consistency
    avoid collision
    information diffusion

toread:
    https://stackoverflow.com/questions/12671383/benefits-of-header-only-libraries
    https://stackoverflow.com/questions/132241/hidden-features-of-c
    likely unlikely to speed up CPU instruction pipelines !
        https://en.wikipedia.org/wiki/Branch_predictor
### TESING FILE FOR INDEXER ###

The indexer was tested using various inputs as described below. Additionally, valgrind was used on indexer and indextest to check for memory leaks, invalid frees, and the usage of freed pointers. It passed all tests as expected.

Additionally, the output of indexer was tested with indextest and indextest.sh to validate the usage of the datastructures. It was tested by executing the following three commands in order.

./indexer data2 infile
./indextest infile outfile
./index.sh infile outfile

The test was successful.

# Tests for indexer #

- proper usage ./indexer pageDir outfile
produces outfile in /tse/data exits with code 0

- No additional arguments ./indexer
Produces an error message with exit code 2

- Less than 2 additional arguments ./indexer pageDir
Produces an error message with exit code 2

- More than 2 additional arguments ./indexer pageDir outfile random
Produces an error message with exit code 2

- Given directory does not exist.
Produces an error message with exit code 1

- Given directory does not contain .crawler
Produces an error message with exit code 1

- Given directory does not contain .crawler
Produces an error message with exit code 1

- Write protected output file.
Produces an error message with exit code 1

# Tests for indexertest #

- proper usage ./indextest infile outfile
 produced outfile in /tse/data/ with exit code 0

- incorrent number of arguments ./indextest infile 
 produced error with exit code 2

- read protected input file.
Produces an error message with exit code 1

- Write protected output file.
Produces an error message with exit code 1
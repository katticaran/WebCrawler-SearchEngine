
### TESING FILE FOR QUERIER ###

Note: For the purpose of testing logic, a directory called simpletest has been included in the tse/data/ along with its corresponding index file called simpletestindex. This is the example given in the CS50 page for the querier and contains the following.


    query              | D1           | D2           | D3           |
    -------------------+--------------+--------------+--------------+
    *matches*          | 0 cat, 7 dog | 2 cat, 3 emu | 2 cat, 4 dog |
    cat and dog        | score = 0    | score = 0    | score = 2*   |
    cat or  dog        | score = 7*   | score = 2    | score = 6    |
    cat and dog or emu | score = 0    | score = 3*   | score = 2    |

where * indicates the highest rank for each query.


The querier was tested using various inputs as described below. Additionally, valgrind was used on querier to check for memory leaks, invalid frees, and the usage of freed pointers. It passed all tests except the memory leak test. A very small memory leak occurs when multiple or-sequence queries are given. Leak: A few blocks of 16bytes.
All the tests below were tested using the data2.gzp file provided in the course materials. i.e the very very large directory.


# Tests for querier #

- proper usage: ./querier data2 data2index
dartmouth and college or greek life and computers or helicopters
Result: Produces the scores, DOCID's and URL's in descending order of score.

- No additional arguments: ./querier
Result: Produces an error message with exit code 2

# Arguments Tests #
- Less than 2 additional arguments: ./querier data2
Result: Produces an error message with exit code 2

- More than 2 additional arguments ./querier data2 data2index random
Result: Produces an error message with exit code 2

- Given directory does not exist.
Result: Produces an error message with exit code 1

- Given directory does not contain .crawler
Result: Produces an error message with exit code 1

- read protected input file.
Result: Produces an error message with exit code 1

# Validation Tests #

All tests below have been started with the command:
> $ ./querier data2 data2index

The following tests have to do with query validation:

- Query starts with or.
Result: Produces an error message, cleans and accepts new query

- Query starts with and
Result: Produces an error message, cleans and accepts new query

- Query has consecutive or/and
Result: Produces an error message, cleans and accepts new query

- Query ends with or
Result: Produces an error message, cleans and accepts new query

- Query ends with and
Result: Produces an error message, cleans and accepts new query

- Query has non-alphabet non-whitespace character
Result: Produces an error message, cleans and accepts new query

- Query: datrmouth college
Result: Produces a the list of pages in order.

- Query: DARTMOUTH college
Result: Produces a the the list of pages in order ( as above).

- Query: DARTMOUTH and college
Result: Produces a the the list of pages in order ( as above).

- Query: DaRtMouTh AnD CollEGe
Result: Produces a the the list of pages in order ( as above).

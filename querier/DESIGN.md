**Requirements Spec**

The TSE querier is a standalone program that reads the index file produced by the TSE indexer, and answers search queries submitted via stdin.

The querier **shall**:

1.  execute from a command line with usage syntax

    *   `./querier pageDirectory indexFilename`
    *   where `pageDirectory` is a directory produced by the crawler, and
    *   where `indexFilename` is an index file produced by the indexer.
2.  load the index from `indexFilename` into an internal data structure.

3.  read search queries from stdin, one per line, until EOF.

    1.  clean and parse each query according to the _syntax_ described below.
    2.  print the 'clean' query for user to see.
    3.  use the index to identify the set of documents that _satisfy_ the query, as described below.
    4.  if no documents satisfy the query, print `No documents match.`
    5.  otherwise, rank the resulting set of documents according to its _score_, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the `pageDirectory`.)

The querier **shall** validate its command-line arguments:

*   `pageDirectory` is a directory produced by the crawler, and
*   `indexFilename` is the name of a readable file.

The querier _may_ assume that the input directory and files follow the designated formats.

*   `pageDirectory` has files named 1, 2, 3, ..., without gaps.
*   The content of document files in `pageDirectory` follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
*   The content of the file named by `indexFilename` follows our [Index file format](http://www.cs.dartmouth.edu/%7Ecs50/Labs/Lab5/#index-file-format); thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

**Design Spec:**

The querier is required to accept user input and search through the index and answer queries, to design the querier, we can divide and conquer these three separate parts.

**Part 1:** User Input

*Accepting the user input.*
Apart from the command line arguments, the user is free to give in any sequence of characters as a query. However, according to the requirement spec, we have to accpet only alphabets to form strings. To do this, we can iteratively get each character, check if it meets the requirements, and then add it to a buffer. Once the user has terminated using a newline or EOF, we can be sure that the buffer contains the users query.

*Validating user Input*
To validate that the user has met the requirements for the query, we need to run some checks on the given buffer. This can be done once the buffer is ready to be used (when newline or EOF is received). These 

**Part 2:** The Index.

In order to answer queries, our querier needs access to an indexfile that contains information regarding the occurances of words in documents. Due to the fact that there can be a very large number of words, a hashtable is ideal for this purpose, as it not only reduces lookup time to O(1) (given enough hashwidth) but also due to the fact that new entries can be added easily. We can accept the indexfile and parse and insert its contents into an inverted index hashtable. Later on, when a query is made, we can refer to this inverted index to answer the queries.

**Part 3:** The Query

The main challenge in the querier is to search through the index and decide which files are relevant. To do this we refer to the Requirement Spec that gives us an idea of what the user is expected to input. The user, is allowed to input a query that is a string of alphabets and blankspaces (which is ignored). The words 'or' and 'and' are used to allow us to identify the required files. i.e words that are part of an and-sequence are required to all be present in a file if the file in order to match that file with that and-sequence. In short, the score of a particular text is the intersection of counts of each word in the and-sequence. On the other hand, the file score of an or-sequence is the union of the counts of each document with respect to each or-sequence.

In order to meet this requirement, we will need to distinguish between an and-sequence and an or-sequence. However, since the and binds more tightly than the or, we can create groupds wherein each or-sequence is part of a new group. Within each group, we can change the count of each docID to the lowest value of the lowest word-count for that document for words in that and-sequence. The implementation section will make this more clear using pseudocode.

Once we have processed the queries, all that is left to be done is to sort and print out the results. After sorting, each url is found by reading the first line of that particular file.


**Implementation Spec:**

**Data Structures:**
Hashtable: used for creating an inverted index
counters: used to keep track of the number of occurances of each word.
array of structs(1): used to sort the results once we get the data.
array of structs(2): used to keep track of the or-sequence groups.

Pseudocode:
1. Accept command line arguments
2. Validate arguments
3. load index into hashtable
4. accept user input
5. validate user input
6. parse user input
7. check if parsed input meets requirements.
8. get results
9. print

The get-results can be further broken down:
1. get word if none remain goto 8
2. if word is 'and' ignore and get next word
3. if word is 'or' create a new group
4. if word is a regular word, find the occurances of the word in the index
5. add that counter structure to the current group
6. if the DOCID already exists in the current group, then set the count to the lower of the two. (i.e intersection)
7. go to 1
8. Search for identical documents in each group.
9. Add the count to reflect the sum of the counts in each group (ie Union)
10. Delete redundant nodes since we have already added their counts.
11. Add nodes to an array structure for easy sorting.
12. sort array.
13. Print result.

**Testing Spec:**

In order to ensure a robust querier, it needs to be tested with various inputs. See TESTING.md for more information
Some of the tests required are: 

**Argument Tests**
Check if the user has given the right arguments and meets the requirements.
**Validation Test**
Validate the user query with the requirement specs
**Logic Test**
Tests to ensure that the program is scoring the files accurately.
**Accuracy Test**
Check that the final output is accurate.

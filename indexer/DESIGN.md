### Indexer Requirements Spec

Source: Professor Charles C. Palmer's website for COSC50
Link: http://www.cs.dartmouth.edu/~cs50/Labs/Lab5/

The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

The indexer **shall**:

1.  execute from a command line with usage syntax
    *   `./indexer pageDirectory indexFilename`
    *   where `pageDirectory` is a directory produced by the crawler, and
    *   where `indexFilename` is the name of a file into which the index should be written.
2.  read documents from the `pageDirectory`, each of which has a unique document ID,
    *   wherein the document `id` starts at 1 and increments for each new document,
    *   and the filename is of form `pageDirectory/id`,
    *   and the first line of the file is the URL,
    *   and the second line of the file is the depth,
    *   and the rest of the file is the page content.
3.  build an inverted-index data structure mapping from _words_ to _(documentID, count) pairs_, wherein each _count_ represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and `NormalizeWord` before indexing.
4.  create a file `indexFilename` and write the index to that file, in the format described below.

The indexer **shall** validate its command-line arguments:

*   `pageDirectory` is a directory produced by the crawler (see below), and
*   `indexFilename` is the name of a writeable file.

The indexer _may_ assume that

*   `pageDirectory` has files named 1, 2, 3, ..., without gaps.
*   The content of files in `pageDirectory` follow the format as defined in the crawler specs; thus your code (to create a `WebPage` by reading a file) need not have extensive error checking.

The index tester **shall**:

1.  execute from a command line with usage syntax
    *   `./indextest oldIndexFilename newIndexFilename`
    *   where `oldIndexFilename` is the name of a file produced by the indexer, and
    *   where `newIndexFilename` is the name of a file into which the index should be written.
2.  load the index from the `oldIndexFilename` into an inverted-index data structure.
3.  create a file `newIndexFilename` and write the index to that file, in the format described below.

It need not validate its command-line arguments other than to ensure that it receives precisely two arguments; it may simply try to open the `oldIndexFilename` for reading and, later, try to open the `newIndexFilename` for writing. You may use `indextest.sh` (provided) to verify that the output is identical to (or equivalent to) the input.

The index tester _may_ assume that

*   The content of the index file follows the format specified below; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.

### Index file format

The indexer writes the inverted index to a file, and the querier reads the inverted index from a file; the file must be in the following format.

*   one line per word, one word per line
*   each line provides the word and one or more (docID, count) pairs, in the format
    *   `word docID count [docID count]...`
*   where _word_ is a string of lower-case letters,
*   where _docID_ is a positive non-zero integer,
*   where _count_ is a positive non-zero integer,
*   where the word and integers are separated by spaces.

### Design Spec ###

The TSE is divided into three parts: Crawler, indexer and querier. Due to the functionality of each, it the three can be divided into their own components thereby enabling modularity of each system. The crawler produces a directory that contains the page found by crawling. The inderxer inturn, can accept this directory index the words found in each file within the directory. The querier can then use this index to answer queries by the user. 

To enable this modularity, the design for the indexer requires that it accept a directroy, and produce a file. It needs to verify that the directory it recieves is the output of the crawler, to do this, it can check for a particular file produced by the crawler. Using this directory, it can create an index (see Implementation spec) and produce an output file that can be easily parsed and used by the crawler. 

### Implementation spec ###

The indexer makes use of the following datastructures
* Hashtable
* counter (linked list)

The indexer reads each file from the given directory (crawler output). It then finds each word that is greater than 3 characters and normalizes it. Using this normalized word as a key, it adds the word to the hashtable along with the docID. If the word already exists in the hashtable, it increments the counter for that particular docID. If it is not found in the hashtable, it creates an entry for the word along with a counter. It then increments the value of the coutner for that docID. It iterates through all the words in the file and all the files in the Directory. In short, it produces a hashtable which uses the word as a key. Each word contains a counter that contains the docID,count information. It then iterates through each slot in the hashtable and prints out every docId,count pair along with the word.

>Pseudocode
1. get Directory
2. get file from Directory
3. no more files? goto 10 else continue
4. get word
5. no-more words? goto 8 else contine
6. select/normalize word
7. insert into hashtable
8. increment counter for that DocID counter for that word
9. goto 4
10. goto 2
11. iterate through every node in hashtable and print.
12. end


### Testing Spec ###

Once implemented, the indexer needs to be tested in accordance to the requirements spec. Apart from the regular tests such as verification of file and directory, the indexer needs to perform two additional tests.
> 1) It needs to test that the input it receives is the output of crawler.
to do this, i have implemented the crawler to write a .crawler file inside the directory. The indexer then for this file in the directory provided to it. If the file is found, then we can be sure that the file was the output of crawler (assuming the absence of malicious intent)

> 2) It needs to ensure that no data is lost from the time of accepting input to the exporting of output. To ensure this, I have created a indextest that accepts the output of the indexer, organizes it into an equivalent datastructure, and prints the contents of the datastructure in the same fashion as that of indexer. I can then compare these two files. If the two files are equivaled, I can be sure that no data was lost within the datastructure. However, if the two files are not equivalent, it means that some data was lost within the data structure. This test will allow me to ensure the accuracy of my indexer. 
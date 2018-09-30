# TESTING

## Crawler

The crawler was tested with various inputs (mentioned below). All of which compiled and executed successfully. Additionally, it was tested for memory leaks and invalid frees using *valgrind*. It passed all these tests without a flaw.

> **Tests**
>
> **Proper Usage:** ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/ pageDir 1
>Received Success code. 7 files were created within specified directory.
>
> **No additional arguments:** ./crawler
>Received Error code 2.
>
> **Less than 4 arguments:**  ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/ pageDir
>Received Error code 2
>
> **Non-internal Webpage**  ./crawler www.google.com pageDir 1
>Received Error code 1
>
> **Write protected Directory**  http://old-www.cs.dartmouth.edu/~cs50/data/tse/ pageDir 1
>Received Error code 1
>
> **Depth out of bounds**  http://old-www.cs.dartmouth.edu/~cs50/data/tse/ pageDir 12
>Received Error code 1

## Data Structures (list, hashtable, bag, counters)

All the data structures were tested by creating many instances of each data structure and adding elements to them, and removing those elements. The program was then tested with *valgrind* for memory leaks. All tests passed.
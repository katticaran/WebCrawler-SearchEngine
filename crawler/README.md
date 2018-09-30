# Tiny Search Engine
Joel Katticaran
11-Feb-2017

## Crawler
### Directory Structure
```
tse
│── README.md
│── TESTING.md
│── web.c
│── web.h
└───lib
│   └─── bag
│   │   │── bag.c
│   │   │── bag.h
│   │   │── bagtest.c
│   │   └─── Makefile 
│   └─── counters
│   │   │── counters.c
│   │   │── counters.h
│   │   │── counterstest.c
│   │   └─── Makefile 
│   └─── memory
│   │   │── memory.c
│   │   │── memory.h
│   │   └─── Makefile 
│   └───hashtable
│   │   │── hashtable.c
│   │   │── hashtable.h
│   │   │── hashtest.c
│   │   │──  jhash.c
│   │   │── jhash.h
│   │   └─── Makefile 
│   └───list
│       │── list.c
│       │── list.h
│       │── test_list.c
│       └─── Makefile 
│   
└─── Makefile 
 
```

### Useful Information about Crawler.
=====================================

**Compilation:** run Makefile whithin parent directory using 'make'

**Purpose:** This program downloads 'internal' webpages upto
a specified depth and saves the pages in a specified path.

**Parameters:** *./crawler [seedUrl] [pageDirectory] [searchDepth]*

     [seedUrl]       : A seed url. Needs to be 'internal' to produce
                       useful results.
     [pageDirectory] : A directory that the program can write to. If this 
                       directory does not exist at runtime, the program will 
                       create it.
     [searchDepth]   : The depth at which the program will retrieve pages.
                       At depth 0, the program will retrieve only the  seedUrl 
                       page(if valid).


**Produces:** Creates the given directory (if it does not already exist)
and creates the files in that directory. The files in the directory
are named x.txt where x is a positive integer.


>**Exit Codes**	
>0: Successful Run.	
>1: Failed Run.		
>2: Invalid usage of program.	


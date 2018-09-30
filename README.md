# Tiny Search Engine
Joel Katticaran
25-Feb-2017

### Useful Information about TSE.
=====================================

**About:** The Tiny Search Engine is divided into three components. *crawler*, *indexer*, and *querier*. As of Feb 25th 2017, the crawler and indexer and querier have been implemented.

**Compilation:** The components of the TSE can be compiled through the *Makefile* in the tse directory. *make* will make all the components and *make clean* will clean all the components that were created by *make*.

>**IMPORTANT NOTE:**
>The arguments of crawler, indexer and querier are relative to tse/data/ i.e if you ask crawler to store the output in *pageDir* , it will store it in */tse/data/pageDir* . Similarly for indexer, if you  run *./indexer pageDir outfile* , the indexer will look for a directory called *pageDir* in */tse/data/* and will produce a file called *outfile* in the directory */tse/data/*

**Execution:** The components of the TSE can be executed by running the appropriate commands from within the directory of that component.For example, to run the querier
> $ ./querier pageDir indexFile

The README file in each directory contians useful information on how to run that particular program.

### Directory Structure
```
tse
│── README.md
│── data
│   └─── README.md
│── crawler
│   │── bag.c
│   │── README.md
│   │── TESTING.md
│   └─── Makefile 
│── indexer
│   │── indexer.c   
│   │── index.sh
│   │── indextest.c
│   │── DESIGN.md
│   │── TESTING.md
│   │── README
│   └─── Makefile 
│── querier
│   │── querier.c
│   │── DESIGN.md
│   │── TESTING.md
│   │── README
│   └─── Makefile 
│── common
│   │── file.c
│   │── file.h
│   │── web.c
│   │── web.h   
│   │── index.c
│   │── index.h
│   │── webpage.c
│   └─── webpage.h
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
│   └───hashtableIndex
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
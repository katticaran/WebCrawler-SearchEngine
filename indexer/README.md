### README FILE FOR INDEXER, INDEXTEST AND INDEX.SH ###
## This fle contains useful information for execution ##

>IMPORTANT NOTE
>All arguments for indexer, indextest and index.sh are relative to the directory */tse/data* i.e if indexer is provided a directory *pageDir* as an argument, it will search */tse/data/* for a directory called *pageDir*

>Execution pipeline from start to finish to produce output and validate:
>./indexer data2 outfile
>./indextest outfile outTest
>./index.sh outfile outTest

>(See each section below for additional/specific information.)

**Compilation:** indexer, indextest and index.sh can be compiled using the makefile in the /tse/ directory or the /tse/indexer/ directory. 

## indexer ##
*Purpose*: Accepts the output of crawler (see specs) and creates an inverted index that maps each word to (docID,count) pair where count is the number of occurances of word in docID.

Additional Info about my indexer: My indexer is a little more flexibile than required and does not require the contents of the input directory to be consecutive integers. I enabled my indexer to validate the folder by searching for .crawler if it finds this, it can be sure that the output was by crawler. Therefore the input files can have any names.

*Parameters*: ./indexer [pageDir] [outfile]
where [pageDir] is a directory in /tse/data
where [pageDir] is a directory that meets the requirements (see Design.md)
where [pageDir] is the output of crawler and contains the .crawler file.
where [output] is a writeable file in /tse/data/ if [output] does not already exist, indexer will create it.

*Usage*: ./indexer dir out
(if /tse/data/dir/ exists, the output is stored in /tse/data/out)

## indextest ##
*Purpose*: Accepts the output of indexer (see specs) and creates a similar inverted index file. The new inverted index file can be compared to the input file. if both are equivaled, then it validates the success of indexer.

*Parameters*: ./indextes [infile] [outfile]
where [infile] is a readable file in /tse/data/
where [infile] is the output of crawler and meets its output specs.
where [outfile] is a writeable file in /tse/data/ if [output] does not already exist, indexer will create it.

## indextest ##
*Purpose*: Accepts the output of indexer (see specs) and creates a similar inverted index file. The new inverted index file can be compared to the input file. if both are equivaled, then it validates the success of indexer.

*Parameters*: ./indextes [infile] [outfile]
where [infile] is a readable file in /tse/data/
where [infile] is the output of crawler and meets its output specs.
where [outfile] is a writeable file in /tse/data/ if [output] does not already exist, indexer will create it.

*Usage*: ./indextest infile file
(if /tse/data/infile exists, the output is stored in /tse/data/outfile)

## index.sh ##
*Purpose*: Compares the output of indexer and indextest to check for equality. If the two are equivalend, it returs a success code. If the two are not equal, it returns exit code 1 and prints the difference between the two.

*Parameters*: ./index.sh [file1] [file2]
where [file1] and [file2] are the outputs of index and indextest (in no specific order)
where [file1] and [file2] are readable files in /tse/data/

*Usage*: ./index.sh file1 file2
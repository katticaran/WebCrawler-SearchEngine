# README 
This is the readme file for the querier and contains useful information about execution, running and features.

>IMPORTANT NOTE All arguments for querier are relative to the directory /tse/data/ i.e if querier is provided a directory pageDir as an argument, it will search /tse/data/ for a directory called pageDir

This is the readme file for the querier and contains useful information about execution, running and features.

**Purpose:** The querier is a program that uses an index provided by the indexer and a directory provided by the crawler to answer queries regarding the occurance of words in the files within the given directory.

Additional Info about my indexer: I have added a feature wherein if you want a particular word to be valued more than others, repeatedly adding that word to the query will allow the querier to give that particular word more imporatnce. For eg.
If you are searching for "dartmouth or college", but you want "dartmouth" to have more importance, you can search "dartmouth or dartmouth or college". 

**Parameters:** ./querier [pageDir] [indexfile] 
where [pageDir] is a directory in /tse/data 
where [pageDir] is the output of crawler and contains the .crawler file. 
where [indexfile] is a readable file in /tse/data/
where [indexfile] is the output of indexer

>Exit Codes:
0: Successful run
1: Invalid argument
2: Improper usage
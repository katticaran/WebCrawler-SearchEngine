/*
Crawler by JOEL KATTICARAN.
Date: 11-Feb-2017

Compilation: run Makefile using 'make'

Purpose: This program downloads 'internal' webpages upto
a specified depth and saves the pages in a specified path.

Parameters: ./crawler [seedUrl] [pageDirectory] [searchDepth]
            [seedUrl] :       A seed url. Needs to be 'internal' to produce
                              useful results.
            [pageDirectory] : A directory that the program can write to. If 
                              this directory does not exist at runtime, the 
                              program will create it.
            [searchDepth] :   The depth at which the program will retrieve pages.
                              At depth 0, the program will retrieve only the 
                              seedUrl page (if valid).


Produces: Creates the given directory (if it does not already exist)
and creates the files in that directory. The files in the directory
are named x.txt where x is a positive integer.

Exit Codes
0: Successful Run
1: Failed Run
2: Invalid usage of program.
 */

/*
Things to improve in the future:
1) Try adding a better UI.
2) Figure out if we really need a 1 second delay between fetches.
       -This is the biggest bottleneck
3) Test the jhash function to see the spread of the hash. Maybe some optimizat
ions can be made there.
4) Find an optimal hashtable size to inputsize ratio.? How would I do this?
5) The storeData function is ugly. Fix it.
 */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "../lib/bag/bag.h"
#include "../lib/list/list.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include "../common/web.h"
#include <sys/stat.h>
#include <sys/types.h>

/*
Writes the contents of the argument data into the file location/filenumber.txt.
Ensures that the first line is the url and the second line is the depth
 */
int storeData (int filenumber, char *data, char* location, int depth, char* url);

/*Checks the user Input to ensure that it meets the requirements of the
  crawler.checks that all inputs are in appropriate format.
  Retruns the maxDepth value tests if seed url is Internal.
*/
int checkInput(int argc, char* argv[]);

int main(int argc, char* argv[])
{

  //apart from checkingInput, the function checkInput also returns the
  //max search depth.
  int maxDepth = checkInput(argc, argv); 

  int counter = 1;
  char* url = argv[1];
  char* location = argv[2];

  char folderName[150];
  folderName[0]='\0';
  strcat(folderName,"../data/");
  strcat(folderName,location);

  //some variables used for the stopwatch to optimize waiting time.
  clock_t startTime = clock();
  clock_t diffTime;
  int sleepTime;

  //creating the data structures.
  bag_t* bag = bag_new();
  hashtable_t* hashtable = hashtable_new(10000);
  char pageUrl[2001];

  //inserting the seed url into bag.
  bag_insert(bag, (char*)url, 0);
  
  //taking out the element from the bag
  bagNode_t* node = bag_extract(bag);
  strcpy(pageUrl, (char*)node->data);
  int currentDepth = node->depth;
  free(node);
  
  while (1){

    //if hashtable_find returns NULL, it means that the entry is not already
    //existing.
    if (hashtable_find(hashtable, pageUrl) == NULL){
      WebPage* page = calloc(1, sizeof(WebPage));
      page->url = pageUrl;

      //check if a wait is required before page fetch. sleep if required.
      diffTime = clock() - startTime;
      int msec = diffTime * 1000 / CLOCKS_PER_SEC;
      if (msec/1000 < 1){
	sleepTime =(1000-msec%1000)*1000;
	usleep(sleepTime);
      }
      
      //restarting the timer.
      startTime = clock();

      //fetching the webpage
      if(GetWebPage(page)) {
	storeData (counter, page->html, folderName, currentDepth, pageUrl);
	hashtable_insert(hashtable, pageUrl, (void*)pageUrl);
	counter++;

	//getting the urls from within the page just fetched.
	int pos = 0;
	char* result;
	char* base_url = pageUrl;
	while ((pos = GetNextURL(page->html, pos, base_url, &result)) > 0) {
	  if(IsInternalURL(result)){
	    //inserting these URL's into the bag
	    bag_insert(bag, (char*)result, currentDepth+1);
	  }//if
	  free(result);
	}//if
	free(page->html);
	free(page);
      }//if
    }//if
    
    //getting the next element out of the bag
    bagNode_t* node = bag_extract(bag);
    if (node == NULL){
      break;
    }
    strcpy(pageUrl, (char*)node->data);
    currentDepth = node->depth;
    free (node);

    /* since the datastructure of the bag is a queue,
    any element i that is behind an element j in
    the queue will always have depth greater or
    equal to the depth of j. (Since i was inserted into
    the queue after j.) Hence, if this condition is met, I have extracted
    all valid urls for the required depth.
    */
    if (currentDepth > maxDepth)
      break;
    
  }//while
  
  strcat(folderName,"/.crawler");
  FILE *file = fopen (folderName, "wb");
  //check if given pageDirectory is write-protected.
  if (file == NULL){
    printf("Error! The given pageDirectory is write-protected.\n");
    exit (1);
  }
  fclose(file);
  //freeing memory used by the datastructures.
  hashtable_delete(hashtable);
  bag_delete(bag);

  return 0;
}//main
  

/*
checkInput checks all the arguments received to ensure
that they meet the requirements. Additionally, it returns
the maximum depth to the calling function.
 */
int checkInput(int argc, char* argv[]){
  if (argc !=4 ){
    printf("Error. Invalid Number of arguments\n");
    exit (2);
  }
  if (IsInternalURL(argv[1])==false){
    printf("Error. The seed URL is not internal\n");
    exit(1);
  }
  int depth = strtol(argv[3], NULL, 10);
  if (depth < 0 || depth > 10){
    printf("Error. Depth is out of bounds.\n");
    exit(1);
  }
  return depth;
}

/*
storeData is the function that is used to create the txt files.
It concatenates the data that is required to name the file and then writes
it appropriately to the file.
 */
int storeData (int filenumber, char *data, char* location, int depth, char* url) {
  int returnVal = 1;
  char filename[200];
  filename[0]='\0';
  char fileVal[20];
  


  //this converts an integer to a char* which
  //i will later use to name my file.
  snprintf(fileVal, 20,"%d",filenumber);

  strcat(filename,"../data/");   
  strcat(filename,location);
  strcat(filename,"/");
  strcat(filename,fileVal);
  strcat(filename,".txt");


  //making the appropriate directory with permissions
  mkdir(location, S_IRWXU | S_IRWXG | S_IRWXO);


  
  //opening the file
 FILE *file = fopen (filename, "wb");
 //check if given pageDirectory is write-protected.
    if (file == NULL){
      printf("Error! The given pageDirectory is write-protected.\n");
      exit (1);
    }
    //printing out the url and depth
 fprintf(file, "%s\n%d\n", url,depth);
 // fclose (file);

 //printing out the contents of the webpage.
 //  file = fopen (filename, "r+");
  if (file != NULL) {
    if (fputs (data, file) != EOF) {
      returnVal = 0;
    }
    fclose (file);
  }
  return returnVal;
}

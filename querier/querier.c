/*
querier by JOEL KATTICARAN.
Date: 25-Feb-2017

Compilation: run Makefile using 'make'

Purpose: This program downloads 'internal' webpages upto
a specified depth and saves the pages in a specified path.

Purpose: The querier is a program that uses an index provided by the indexer
 and a directory provided by the crawler to answer queries regarding the 
occurance of words in the files within the given directory.

Parameters: ./querier [pageDir] [indexfile] 
where [pageDir] is a directory in /tse/data 
where [pageDir] is the output of crawler and contains the .crawler file. 
where [indexfile] is a readable file in /tse/data/
where [indexfile] is the output of indexer


Exit Codes
0: Successful Run.
1: Invalid argument.
2: Invalid usage of program.
 */

#define MAXNO 10000
#define QUERYMAX 5000
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "../common/file.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtableIndex/hashtable.h"
#include "../common/intoTable.h"

char inputDirectory[500];

//Accepts user input which it parses according to requirement.
void getQuery(hashtable_t* hashTable);

//sorts array in decreasing order using the quicksort algorithm.
void quickSort(countersNode_t* array[], int left, int right);

//organizes and prints the results.
void publishResults(counters_t** countersArray, int max);

//accepts query from getQuery and then parses the data in the string.
void executeQuery(char* query, hashtable_t* hashTable);

//frees allocated memory for the hashTable.
void cleanup(hashtable_t* hashTable);

//frees memory allocated for the array.
void cleanupArray(counters_t* array[]);

//Validates command line arguments.
void check_args(int argc, char* argv[]);

int main(int argc, char* argv[]){

  check_args(argc, argv);

  //creating a hashtable
  hashtable_t* hashTable =  hashtable_new(MAXNO);

  //modifying directory to search in ../data/
  inputDirectory[0] = '\0';
  strcat(inputDirectory,"../data/");
  strncat(inputDirectory,argv[1], 100);

  char* file = argv[2];

  //creating the inverted index from the index file.
  index_toHash(file, hashTable);

  //accept user input for query.
  getQuery(hashTable);

  //free allocated hashtable memory.
  cleanup(hashTable);

  return 0;

}

void getQuery(hashtable_t* hashTable){
  char query[QUERYMAX+1];
  char c = getchar();
  int count = 0;
    
  while ( c != EOF){
    while ((count < QUERYMAX) && (c != '\n') && (c != EOF) ){
    
      if (c >= 'A' && c <= 'Z'){
	c = tolower(c);
      }
    
      if ((c >= 'a' && c <= 'z') || ( c == ' ') ||( c == '\t')) {
	query[count] = c;
	count++;
	c = getchar(); 
      }
      else {
	printf("Invalid character %c. Starting new query...\n",c);
	c = ';';
	break;
      }
    
    }
    
    if (c == ';'){
      count = 0;
      while ((c = getchar()) != '\n' && c != EOF) { }
      c = getchar();
      continue;
    }
  
    if (count >= QUERYMAX){
      printf("Query limit exceeded. Taking next query.\n");
      count = 0;
      while ((c = getchar()) != '\n' && c != EOF) { }
      c = getchar();
      continue;
    }
  
    query[count] = '\0';
    //executing the required query.
    executeQuery(query,  hashTable);

    if (c == EOF){
      return;
    }

    if (c== '\n'){
      count = 0;
      c = getchar();
    }
  
  }
    
}


  
void cleanup(hashtable_t* hashTable){
   int i;
   for (i=0; i<hashTable->size; i++){
     hashEntry_t* current = hashTable->tableAddr[i];
     while(current != NULL){
       counters_delete((counters_t*)current->data);;
       current = current->next;    
     }
   }
   hashtable_delete(hashTable);
}

void executeQuery(char* query, hashtable_t* hashTable){
 char *word;

 //checks if query starts with and/or.
 word = strtok (query," \t");
 if (word != NULL){
   if ((strcmp(word,"and") == 0) || (strcmp(word,"or") == 0)){
     printf("Query cannot start with and/or. Starting new query..\n");
     return;
   }
 }

 //creating array to hold each group in the query
 //a new group is created when an 'or' is found
 counters_t* countersArray[QUERYMAX];
 int m;
 for (m=0;m<QUERYMAX;m++){
   countersArray[m] = NULL;
 }

 //character to store last parsed word. to ensure
 //the absence of consecutive and/or.
 char previous[500];
 previous[0] = '\0';
 
 int group = 0;
 int newgroup = 1;
 int skipwords = 0;
 counters_t* counterWord;
 countersNode_t* myNode;
 countersNode_t* temp;
 countersNode_t* hashNode;
 
 while (word != NULL)
   {
     if ( (strcmp(previous,"and") == 0) || (strcmp(previous,"or") == 0) ){
	 if ((strcmp(word,"and") == 0) || (strcmp(word,"or") == 0)){
	   printf("Query cannot have adjacent and/or. Starting new query..\n");
	   cleanupArray(countersArray);
	   return;
	 }
       }
     //if 'or' create new group
     if (strcmp(word,"or") == 0){
       group++;
       newgroup = 1;
       skipwords = 0;
       countersArray[group] = counters_new();
       strcpy(previous,word);
       word = strtok (NULL, " \t");
       continue;
     }
     
     if (strcmp(word,"and") == 0){
       strcpy(previous,word);
       word = strtok (NULL, " \t");
       continue;
	 }
       
     if (newgroup == 1){
       counterWord = (counters_t*)hashtable_find(hashTable, word);
       if (counterWord == NULL){
	 skipwords = 1;
	 //OPTIMIZATION:
	 //if a word in an and-sequence wasnt found, then the score for that
	 //sequence is 0. (since it is the intersection). Therefore, I can
	 //ignore every other word in the and-sequence.
       }
       else if (counterWord != NULL){
	 countersArray[group] = counters_new();
	 countersNode_t* node = counterWord->head;
	 while (node != NULL){
	   counters_set (countersArray[group], node->key, node->count);
	   node = node->behind;
	     }
       }
       //setting the newgroup flag to 0 after creating a new group.
       newgroup = 0;
       strcpy(previous,word);
       word = strtok (NULL, " \t");
       continue;
     }

     if (skipwords == 0){
       counterWord = (counters_t*) hashtable_find(hashTable, word);
       if (counterWord == NULL){
	 //OPTIMIZATION:
	 //if a word in an and-sequence wasnt found, then the score for that
	 //sequence is 0. (since it is the intersection). Therefore, I can
	 //ignore every other word in the and-sequence.
	 counters_delete(countersArray[group]);
	 countersArray[group] = NULL;
	 skipwords = 1;
       }
       else if (counterWord != NULL){
	 //if the word is found, then add it to the group.
	 myNode = countersArray[group]->head;
	 while (myNode != NULL){
	   hashNode = counterWord->head;
	   if (myNode->count == 0){
	     myNode = myNode->behind;
	     continue;
	   }
	   
	   while (hashNode != NULL){
	     //if it's count it has a lower count, due to the fact
	     //that and-sequence requires the intersection of counts,
	     //we store the lowest count.
	     if (strcmp (myNode->key,hashNode->key) == 0){
	       if (hashNode->count < myNode->count){
		 myNode->count = hashNode->count;
	       }
	       break;
	     }
	     hashNode = hashNode->behind;
	   }
	   if (hashNode == NULL){
	   temp = myNode;
	   myNode = temp->behind;
	   delete_node(countersArray[group], temp);
	   } else {
	     myNode = myNode->behind;
	   }
	 }
       }
     }

    
     // printf ("%s\n",word);
     strcpy(previous,word);
     word = strtok (NULL, " \t");
   }

 //ensure that it doesn't end with and/or.
 if ( (strcmp(previous,"and") == 0) || (strcmp(previous,"or") == 0) ){
   printf("Query cannot end with and/or. Starting new query..\n");
   cleanupArray(countersArray);
   return;
 }

 //organize and print results
  publishResults(countersArray, group);

  //free allocated memory.
  cleanupArray(countersArray);
}


void publishResults(counters_t** countersArray, int max){
  int i,j;
  int maxcount;
  int number = 0;
  counters_t* container = counters_new();
  countersNode_t* node1;
  countersNode_t* node2;

  //compare elements across groups. Since each group represents
  //a different or-sequence, the required score is the union of
  //the counts. So we add the counts.
  for (i=0;i<=max;i++){
    maxcount = 0;
    if (countersArray[i] == NULL){
      continue;
    } else {
      node1 = countersArray[i]->head;
    }
    while(node1 != NULL){
      maxcount = node1->count;
      for (j=i+1;j<=max;j++){
	if (countersArray[j] == NULL){
	  continue;
	} else {
	  node2 = countersArray[j]->head;
	}
	while (node2 != NULL){
	  if (strcmp(node1->key, node2->key) == 0){
	    maxcount = maxcount+node2->count;
	    delete_node(countersArray[j], node2);
	    break;
	  }
	  node2 = node2->behind;
	}
      }
      counters_set(container, node1->key, maxcount);
      number++;
      node1 = node1->behind;
    }
  }

  //enter all the counternodes into an array for sorting.
  countersNode_t* array[number];
  i = 0;
  if (container != NULL){
   node1 = container->head;
   while(node1 != NULL){
     array[i] = node1;
     node1 = node1->behind;
     i++;
   }
  }
  else {
    printf("No Documents Match.\n");
    counters_delete(container);
    return;
  }

  //sorting the array.
  quickSort(array, 0, i-1);

  //if there are no elements in the array, report appropriate message
  if (i<1){
        printf("No Documents Match.\n");
  }
  else{
  FILE* currentFile;

  //print every score, ID and url
  for (j = 0; j<i; j++){

    //char to open the file.
    char filename[500];
    filename[0] = '\0';
    strcat(filename,inputDirectory);
    strcat(filename,"/");
    strcat(filename,array[j]->key);
      
    currentFile = fopen(filename, "r");
    if (currentFile == NULL)
      {
	fprintf(stderr, "Error : Failed to open entry file\n");
	exit(1);
      }
    //get the required url line
    char* url = readline(currentFile);
    fclose(currentFile);

    //print the scores ID's and urls
    printf("Score: %d DOCID: %s :%s \n", array[j]->count, array[j]->key,url);
    
    if (url != NULL)
      free (url);
  }}

  //free allocated memory
   counters_delete(container);
}


//swap two elements of an array
  void swap(countersNode_t* array[], int pos1, int pos2) {
  countersNode_t* temp = array[pos1];
  array[pos1] = array[pos2];
  array[pos2] = temp;
}

int partition(countersNode_t* array[], int left, int right, countersNode_t* pivot) {
   int leftval = left - 1;
   int rightval = right;

   while(true) {
     while (count_greaterthan(array[++leftval], pivot)){
       }
		
     while (rightval > 0 && count_lessthan(array[--rightval],pivot))
       {
       }

       if(leftval >= rightval) {
	   break;
	 } else {
         swap(array, leftval, rightval);
      }
   }
	
   swap(array, leftval,right);
   return leftval;
}

//recursively sorts the array.
void quickSort(countersNode_t* array[], int left, int right) {
   if(right - left <= 0) {
      return;
   } else {
      countersNode_t* pivot = array[right];
      int partitionPoint = partition(array, left, right, pivot);
      quickSort(array, left,partitionPoint-1);
      quickSort(array, partitionPoint+1,right);
   }
}

//frees allocated memory
void cleanupArray(counters_t* array[]){
  int i=0;
  while (i<QUERYMAX){
    if (array[i] != NULL){
      counters_delete(array[i]);
      array[i] = NULL;
    }
    i++;
  }
}

//validates user input.
void check_args(int argc, char* argv[]){
  if (argc !=3 ){
    printf("Error. Invalid Number of arguments\n");
    exit (2);
  }
  DIR* fileDirectory;
  FILE* outfile;
  FILE* crawlerfile;

  char filename[200];
  filename[0] = '\0';
  strcat(filename,"../data/");
  strncat(filename,argv[1], 100);
    
  if ((fileDirectory = opendir (filename)) == NULL) 
    {
      fprintf(stderr, "Error: Failed to open input directory '%s'\n",
	      filename);
      exit(1);
    }
  closedir(fileDirectory);


  strcat(filename,"/");
  strcat(filename,".crawler");
  
  crawlerfile = fopen(filename, "r");
  if (crawlerfile == NULL){
    {
      fprintf(stderr, "Error: '.crawler' file was not found in ../data/'%s'\n",
	      argv[1]);
      exit(1);
    }
  }
  fclose(crawlerfile);

  char outfilename[200];
  outfilename[0]='\0';
  strcat(outfilename,"../data/");
  strncat(outfilename,argv[2], 100);
  
  outfile = fopen(outfilename, "r");
  if (outfile == NULL)
    {
      fprintf(stderr, "Error: Unable to read file '%s' \n", outfilename);
      exit(1);
    }
  fclose(outfile);
  
}

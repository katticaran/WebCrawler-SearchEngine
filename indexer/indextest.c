/* 
 * indextest - load an index, and save it, to test those functions
 *
 * 
 * Name, Summer 2016
 */
#define MAXNO 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/file.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtableIndex/hashtable.h"

//prints the hashtable
void printOut(hashtable_t* hashTable, FILE* outfile);

//frees allocated memory
void cleanup(hashtable_t* hashTable);

//validates arguments
void check_args(int argc, char* argv[]);

int main(int argc, char* argv[]){

   check_args(argc, argv);

   //setting approriate input and output files to look in /tse/data/
   char inputFileName[200];
   inputFileName[0]='\0';
   strcat(inputFileName,"../data/");
   strncat(inputFileName,argv[1],100);
  
   char outputFileName[200];
   outputFileName[0]='\0';
   strcat(outputFileName,"../data/");
   strncat(outputFileName,argv[2],100);

  hashtable_t* hashTable = hashtable_new(MAXNO);
   
  FILE* inFile = fopen(inputFileName, "r");
  FILE* outFile = fopen(outputFileName, "w");

  char* pch;
  char word[200];
  char file[200];
  char count[200];
  counters_t* counter;
  
  //gets line
  char* line = readline(inFile);
  //parses line
  while (line != NULL){
    pch = strtok (line," :[]");
    if (pch != NULL){
      word[0] = '\0';
      strcpy(word,pch);
      // printf ("WORD:%s\n",word);
      // void* counterWord = hashtable_find(hashTable, word);
       counter = counters_new();
    }
    //adds the docID,count to the hastable with key word
    while (pch != NULL)
      {
	// printf ("%s..\n",pch);
	pch = strtok (NULL, " ,:[]");
	if (pch != NULL){
	  strcpy(file,pch);
	  //  printf ("FILE:%s ",file);
	}
	pch = strtok (NULL, " ,:[]");
	if (pch != NULL){
	  strcpy(count,pch);
	  //  printf ("COUNT:%d\n",atoi(count));
	}
	counters_set(counter, file, atoi(count));
      }
    hashtable_insert(hashTable, word, counter);
    
    if (line != NULL)
      free(line);
	
    line = readline(inFile);
  }
  //printing contents
  printOut(hashTable, outFile);

  //close appropriate files
  fclose(inFile);
  fclose(outFile);

  //free memory
  cleanup(hashTable);
  return 0;
    
}

void printOut(hashtable_t* hashTable, FILE* outfile){

  int i;
  for (i=0; i<hashTable->size; i++){
    hashEntry_t* current = hashTable->tableAddr[i];
    while(current != NULL){
      fprintf(outfile,"%s ",current->key);
      counters_printAll((counters_t*)current->data, outfile);
      fprintf(outfile,"\n ");
      current = current->next;    
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

void check_args(int argc, char* argv[]){
  if (argc !=3 ){
    printf("Error. Invalid Number of arguments\n");
    exit (2);
  }

  char infilename[200];
  infilename[0]='\0';
  strcat(infilename,"../data/");
  strncat(infilename,argv[1],100);

  FILE* infile = fopen(infilename, "r");
  if (infile == NULL)
    {
      fprintf(stderr, "Error: Unable to read file '%s' \n", infilename);
      exit(1);
    }
  fclose(infile);
  
  char outfilename[200];
  outfilename[0]='\0';
  strcat(outfilename,"../data/");
  strncat(outfilename,argv[2],100);

  FILE* outfile = fopen(outfilename, "w");
  if (outfile == NULL)
    {
      fprintf(stderr, "Error: Unable to write to file '%s' \n", outfilename);
      exit(1);
    }
  fclose(outfile);
  
}

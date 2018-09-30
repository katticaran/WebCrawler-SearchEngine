/* 
 * indexer - a simple web indexer
 *
 * Joel J. Katticaran
 */


#define MAXNO 10000

#include "../lib/counters/counters.h"
#include "../lib/hashtableIndex/hashtable.h"
#include "../common/word.h"
#include "../common/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

void printOut(hashtable_t* hashTable, FILE* outfile);

void cleanup(hashtable_t* hashTable);

void check_args(int argc, char* argv[]);

int main(int argc, char* argv[])
{
  DIR* fileDirectory;
  FILE* outfile;
  struct dirent* loadFile;
  FILE* currentFile;
  
  // char* outputFileName;
  // char* inputDirectory;

 check_args(argc, argv);
 
 char inputDirectory[200];
 inputDirectory[0] = '\0';
 strcat(inputDirectory,"../data/");
 strncat(inputDirectory,argv[1], 100);

 char outputFileName[200];
 outputFileName[0]='\0';
 strcat(outputFileName,"../data/");
 strncat(outputFileName,argv[2], 100);
  
 //inputDirectory = argv[1];
 // outputFileName = argv[2];
  
  hashtable_t* hashTable = hashtable_new(MAXNO);

  /*open the given directory and file. */
  fileDirectory = opendir (inputDirectory);
  outfile = fopen(outputFileName, "w");
 
  while ((loadFile = readdir(fileDirectory))) 
    {
      if (!strcmp (loadFile->d_name, "."))
	continue;
      if (!strcmp (loadFile->d_name, ".."))    
	continue;
      if (!strcmp (loadFile->d_name, ".crawler"))    
	continue;
      /* Open directory entry file for common operation */
      /* TODO : change permissions to meet your need! */

      //uncomment following line to see all files being read.
      // printf("%s\n",loadFile->d_name);
      
      char filename[200];
      filename[0] = '\0';
      strcat(filename,inputDirectory);
      strcat(filename,"/");
      strcat(filename,loadFile->d_name);
      
      currentFile = fopen(filename, "r");
      if (currentFile == NULL)
        {
	  fprintf(stderr, "Error : Failed to open entry file\n");
	  exit(1);
        }

      //Use the following lines to get the url of the page
      //   char* pageName = readline(entry_file);

      //Use the following line to get the depth of the page.
      //   char* pageDepth = readline(entry_file);

      //reading the file
      char* pageData = readfile(currentFile);   
      char* word;
      
      int pos = 0;
	
      while((pos = GetNextWord(pageData, pos, &word))>0)
	{
	  if (strlen(word)<3){
	    free(word);
	    continue;
	  }

	  NormalizeWord (word);
	   
	  // uncomment the following line to print the url of each page
	  //	  printf("%s %s\n",word, pageName);

	  //check if the word exists in the hashtable
	  void* counterWord = hashtable_find(hashTable, word);
	  if (counterWord == NULL){	    
	    //word does not exist in the hashtable.
	    //so create a counter for it and add it to the hashtable
	    counters_t* counter = counters_new();
	    counters_add(counter, loadFile->d_name);
	    hashtable_insert(hashTable, word, (void*)counter);
	  }
	  else {
	    //the word already exists in the hashtable
	    // which means that counterWord is a counter_t*.
	    counters_add((counters_t*)counterWord, loadFile->d_name);
	  }
	  free(word);
	}
      
      free(pageData);
      /* When you finish with the file, close it */
      fclose(currentFile);
    }

  //print the hashtable to file
  printOut(hashTable, outfile);
  
  //close the file.
  fclose(outfile);
  
  //close the Directory
  closedir(fileDirectory);

  //free allocated memory.
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
  
  outfile = fopen(outfilename, "w");
  if (outfile == NULL)
    {
      fprintf(stderr, "Error: Unable to write to file '%s' \n", outfilename);
      exit(1);
    }
  fclose(outfile);
  
}

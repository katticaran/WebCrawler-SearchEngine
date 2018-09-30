#define MAXNO 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/file.h"
#include "../lib/counters/counters.h"
#include "../lib/hashtableIndex/hashtable.h"

//validates arguments

hashtable_t* index_toHash(char* fileIn, hashtable_t* hashTable){

   //setting approriate input and output files to look in /tse/data/
   char inputFileName[200];
   inputFileName[0]='\0';
   strcat(inputFileName,"../data/");
   strncat(inputFileName,fileIn,100);

   
   FILE* inFile = fopen(inputFileName, "r");

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

    fclose(inFile);

return (hashTable);
}

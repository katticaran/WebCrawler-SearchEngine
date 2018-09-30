#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "counters.h"

//create a new empty data structure.
counters_t *counters_new(){
  counters_t *theCounters = (counters_t*)malloc(sizeof(counters_t));
  if (theCounters == NULL){
    perror("Error");
    exit(1);
  }
  
  theCounters->head = NULL;
  theCounters->tail = NULL;
  return theCounters;
}

//return the current value of the counter for key, or 0 if key is not found.
unsigned int counters_get(counters_t *ctrs, char* key){
  countersNode_t* current = ctrs->head;
  while(current != NULL){
    if (strcmp(current->key, key)==0){
      return current->count;
    }
    current = current->behind;
  }
  return 0;
}

//if key exists, increment its counter; otherwise add key and
//set its counter to 1.
void counters_add(counters_t *ctrs, char* key){
  countersNode_t* current = ctrs->head;
  while(current != NULL){
    if (strcmp(current->key,key) == 0){
      current->count = current->count + 1;
      return;
    }
    current = current->behind;
  }
  countersNode_t* counter = (countersNode_t*)malloc(sizeof(countersNode_t));
  if (counter == NULL){
    perror("Error");
    exit(1);
  }
  // counter->key = key;
  strcpy(counter->key,key);
  counter->count = 1;
  counter->ahead = ctrs->tail;
  counter->behind = NULL;
  
   if (ctrs->tail != NULL)
    ctrs->tail->behind = counter;
  else
    ctrs->head = counter;
 
  ctrs->tail = counter;
}
 
//delete the whole data structure and its contents.
bool counters_delete(counters_t *ctrs){
  if ( ctrs == NULL ){
    fprintf(stdout,"Error: The argument passed to counters_delete is Null.\n");
    return false;
  }
  
  countersNode_t *current;
  while( ctrs->tail != NULL ){
    current = ctrs->tail;
    ctrs->tail = current->ahead;
    free(current);
  }
  free(ctrs);
  return true;
}

void counters_printAll(counters_t* ctrs, FILE* outfile){
  countersNode_t* current = ctrs->head;
  while(current != NULL){
    fprintf(outfile,"[%s,%d]",current->key,current->count);
    current = current->behind;
  }
}

bool counters_set(counters_t* ctrs, char* key, unsigned int count){
countersNode_t* current = ctrs->head;
 while(current != NULL){
   if (strcmp(current->key,key) == 0){
     current->count = count;
     return true;
   }
   current = current->behind;
}
   countersNode_t* counter = (countersNode_t*)malloc(sizeof(countersNode_t));
   if (counter == NULL){
     perror("Error");
     exit(1);
   }
   strcpy(counter->key,key);
   counter->count = count;
   counter->ahead = ctrs->tail;
   counter->behind = NULL;
  
   if (ctrs->tail != NULL)
     ctrs->tail->behind = counter;
   else
     ctrs->head = counter;
 
   ctrs->tail = counter;
   return true;
}

void delete_node(counters_t* ctrs, countersNode_t* node){
  if (node != NULL){
    if ((node->ahead == NULL) && (node->behind == NULL)){
      ctrs->head = NULL;
      ctrs->tail = NULL;
      free(node);
      return;
    }
      
    if (node->ahead == NULL){
      ctrs->head = node->behind;
      node->behind->ahead = NULL;
      free (node);
      return;
    }
      
    if (node->behind == NULL){
      ctrs->tail = node->ahead;
      node->ahead->behind = NULL; 
      free (node);
      return;
    }

    else {
      node->ahead->behind = node->behind;
      node->behind->ahead = node->ahead;
      free(node);
      return;
    }
  }
}

bool count_lessthan(countersNode_t* node1, countersNode_t* node2){
  if ((node1 == NULL) || (node2 == NULL)){
    printf("Somethign went wrong...\n");
    exit (1);
  }
  if (node1->count < node2->count)
    return true;
  else return false;
}

bool count_greaterthan(countersNode_t* node1, countersNode_t* node2){
  if ((node1 == NULL) || (node2 == NULL)){
    printf("Somethign went wrong...\n");
    exit (1);
  }
  if (node1->count > node2->count)
    return true;
  else return false;
}

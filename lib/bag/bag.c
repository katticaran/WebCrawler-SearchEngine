#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
/*
Creates a new bag. Initializes all fields and returns the bag
 */
bag_t *bag_new(){
  bag_t* theBag = (bag_t*)malloc(sizeof(bag_t));
  if (theBag == NULL){
    perror("Error");
    exit(1);
  }
  theBag->head = NULL;
  theBag->tail = NULL;
  return theBag;
}

/*
Pops an element of the bag. Returns that element. (bagNode_t).
Returns NULL if empty.
 */
bagNode_t *bag_extract(bag_t *bag){
  if (bag == NULL){
    fprintf(stdout, "Error: bag points to NULL.\n");
    exit(1);
  }
  if (bag->head == NULL){
    return NULL;
  }
  bagNode_t* temp = bag->head;
  if (bag->head == bag->tail){
    bag->head = NULL;
    bag->tail = NULL;
  }else{
    bag->head = temp->behind;
  }
  return(temp);
   
}

/*
Inserts an element to the bag.
 */
void bag_insert(bag_t *bag, char *data, int depth){
  if (bag == NULL){
    fprintf(stdout, "Error: bag points to NULL.\n");
    exit(1);
  }
    
  bagNode_t* item = (bagNode_t*)malloc(sizeof(bagNode_t));
   if (item == NULL){
    perror("Error");
    exit(1);
   }
   item->depth = depth;
   // item->data = data;
   strcpy(item->data, data);
   item->ahead = bag->tail;
   item->behind = NULL;
   if (bag->tail != NULL)
     bag->tail->behind = item;
   else
     bag->head = item;
 
   bag->tail = item;

  
 }
   
/*
Deletes the bagNodes and the bag, freeing all allocated memory.
 */
bool bag_delete(bag_t *bag){
  if ( bag == NULL )
    return false;
  bagNode_t *current = bag->head;
  while (current != NULL){
    // if (current->data != NULL)
    //  free(current->data);
    bag->head = current->behind;
    free(current);
      if (bag->head == NULL)
	break;
    current = bag->head;
      }
  free (bag);
  return true;
    }
  

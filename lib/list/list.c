#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list_t *list_new(){
  list_t *theList = (list_t*)malloc(sizeof(list_t));
  theList->head = NULL;
  theList->tail = NULL;
  return theList;
}

void *list_find(list_t *list, char *key){
  listNode_t* next = list->head;
  while(next != NULL){
    if (strcmp(next->key, key) == 0){
      return next->data;
    }
    next = next->next;
  }
  return NULL;
}

bool list_insert(list_t *list, char *key, void *data){
  if ( list_find(list, key) == NULL ){
  listNode_t* newNode = (listNode_t*)malloc(sizeof(listNode_t));
  if (newNode == NULL){
    perror("Error ");
    exit(1);
      }
  newNode->key = key;
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = list->tail;
  if ( list->head == NULL ){
    list->head = newNode;
  }
  if ( list->tail != NULL ){
    list->tail->next = newNode;
  }
  list->tail = newNode;
  return true;
  }
  return false;
}

bool list_delete(list_t *list){
  if ( list == NULL )
    return false;
  listNode_t *current;
  while( list->tail != NULL ){
    current = list->tail;
    list->tail = current->prev;
    free(current);
  }
  free(list);
  return true;
}

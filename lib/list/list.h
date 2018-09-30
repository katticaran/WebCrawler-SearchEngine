#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef struct listNode{
  char* key;
  char* data;
  struct listNode* next;
  struct listNode* prev;
}listNode_t;

typedef struct list{
  struct listNode* head;
  struct listNode* tail;
}list_t;

//creates a new list data Structure.
list_t *list_new();

//finds an element within the list and returns the data if found.
//returns NULL if not found.
void *list_find(list_t *list, char *key);

//Inserts a new element into the list by creating a node, and copying
//the pointers key and data into their respective fields within the node.
bool list_insert(list_t *list, char *key, void *data);

//deletes the list and frees all allocated memory.
bool list_delete(list_t *list);

#endif



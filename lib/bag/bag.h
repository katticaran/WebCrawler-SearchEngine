/*
Joel Katticaran
Feb-11-2016

Bag using a queue data structure.
 */
#ifndef LIST_H
#define LIST_H

//Note: The bag uses a queue data structure.

#include <stdbool.h>

typedef struct bagNode{
  char data [2001];
  int depth;
  struct bagNode* ahead;
  struct bagNode* behind;
}bagNode_t;

typedef struct bag{
  struct bagNode* head;
  struct bagNode* tail;
}bag_t;

/*Creates a new bag_t. Initializes all fields to NULL*/
bag_t *bag_new();

/*pops the first element off the bag (queue datastructure). 
Returns the element*/
bagNode_t *bag_extract(bag_t *bag);

/*inserts an element into the tail of the bag (queue datastructure). */
void bag_insert(bag_t *bag, char *data, int depth);

/*delets the bag and bagNodes thereby freeing allocated memory*/
bool bag_delete(bag_t *list);

#endif



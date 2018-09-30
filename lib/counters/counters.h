#ifndef COUNTERS_H
#define COUNTERS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct countersNode{
  char key[2001];
  unsigned int count;
  struct countersNode* ahead;
  struct countersNode* behind;
}countersNode_t;

typedef struct counters{
  struct countersNode* head;
  struct countersNode* tail;
}counters_t;

//Creates a new counter data structure.
counters_t *counters_new();

//adds a key to the counter. if key exists, increment its counter; otherwise add
//key and set its counter to 1.
void counters_add(counters_t *ctrs, char* key);

//return the current value of the counter for key, or 0 if key is not found.
unsigned int counters_get(counters_t *ctrs, char* key);

//delete the whole data structure and its contents.
bool counters_delete(counters_t *ctrs);

//prints every [key,count] pair in the given counter to outfile.
void counters_printAll(counters_t* ctrs, FILE* outfile);

//creates a node if it does not already exist and sets the count
bool counters_set(counters_t* ctrs, char* key, unsigned int count);

//deletes a node.
void delete_node(counters_t* ctrs, countersNode_t* node);

//compares to nodes. returns true if count of arg1 is less than arg2
bool count_lessthan(countersNode_t* node1, countersNode_t* node2);

//compares to nodes. returns true if count of arg1 is greater than arg2
bool count_greaterthan(countersNode_t* node1, countersNode_t* node2);

#endif



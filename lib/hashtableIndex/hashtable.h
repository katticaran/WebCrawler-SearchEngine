#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct hashEntry{
  char key[200];
  void* data;
  struct hashEntry* next;
  }hashEntry_t;

typedef struct hashtable{
  hashEntry_t** tableAddr;
  unsigned long size;
}hashtable_t;

//Creates a new hashtable Data Structure.
hashtable_t *hashtable_new(const int num_slots);

//finds an element within the hashtable. Returns the key if found.
//else returns NULL
void *hashtable_find(hashtable_t *ht, char *key);

//Inserts a new element into the hashtable. Creates a node and copies
//the pointer key and data into their respective fields within the node.
bool hashtable_insert(hashtable_t *ht, char *key, void *data);

//Deletes the hashtable and frees all the memeory that it allocates.
bool hashtable_delete(hashtable_t *ht);

bool hashtable_print(hashtable_t *ht);

#endif

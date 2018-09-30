#include <stdio.h>
#include "list.h"

int main(){
  char* key1 = "KKEEYY";
  char* value1 = "VVAALLUUEE";
  list_t* list = list_new();
  list_insert(list, "lol", "hahaha");
  list_insert(list, "cat", "4");
  list_insert(list, "dog", "4");
  list_insert(list, key1, value1);
  list_insert(list, "whale", "0");
  list_insert(list, "goat", "4");
  list_insert(list, "human", "2");
  list_insert(list, "eagle", "2");
  char* answer = (char*)list_find(list, "human");
  printf("The value is: %s\n",answer);
  answer = (char*)list_find(list, key1);
  printf("The value is: %s\n",answer);
  list_delete(list);
}

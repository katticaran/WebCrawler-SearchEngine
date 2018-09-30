#include <stdio.h>
#include <stdlib.h>
#include "bag.h"

int main(){
  int i;
  bag_t* bag = bag_new();
  char name[20];
  char* answer;
  for (i=0 ; i<100; i++){
   snprintf(name, 20,"Testing");
   bag_insert(bag, (void*)name, i);
  }
  for (i=0 ; i<100; i++){
   bag_insert(bag, (void*)"works!", i);
  }

  for (i=0; i< 200; i++){
    bagNode_t* node = (bagNode_t*)bag_extract(bag);
    answer = node->data;
    printf("Answer: %s %d\n",answer, i);
  free(node);
  }
  
  bag_delete(bag);
  return 0;
}

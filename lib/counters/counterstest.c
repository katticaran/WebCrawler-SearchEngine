#include <stdio.h>
#include "counters.h"

int main(){
  counters_t* counter = counters_new();
  char* word1 = "Hello!";
  int i,j;
  for(i=0;i<100;i++){
    counters_add(counter, word1);
  }
  char* word2 = "Testing";
  
  for(i=0;i<700;i++){
    counters_add(counter, word2);
  }
  j = counters_get(counter, word1);
  printf("Word: %s  Count: %d \n",word1,j);
  j = counters_get(counter, word2);
  printf("Word: %s  Count: %d \n",word2,j);
  j = counters_get(counter, "DoesnotExist");
  printf("Word: %s  Count: %d \n","DoesnotExist",j);
  counters_set(counter, "DoesnotExist", 250);
  j = counters_get(counter, "DoesnotExist");
  printf("Word: %s  Count: %d \n","DoesnotExist",j);
  counters_set(counter, "DoesnotExist", 999);
  j = counters_get(counter, "DoesnotExist");
  printf("Word: %s  Count: %d \n","DoesnotExist",j);
  counters_delete(counter);
  
    
}

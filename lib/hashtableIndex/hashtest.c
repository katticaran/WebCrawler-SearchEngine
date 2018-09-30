#include <stdio.h>
#include "hashtable.h"

int main(){
  char* val1 = "Testing";
  char* val2 = "This";
  char* data1 = "result";
  hashtable_t* ht = hashtable_new(10000);
   hashtable_insert(ht, val1, data1);
   val1 = "new";
   data1 = "newAnswer";
   hashtable_insert(ht, val1, data1);
   
   
  char* ans = hashtable_find(ht, "Testing");
  printf("Answer: %s\n",ans);
  hashtable_delete(ht);
  return 0;
}

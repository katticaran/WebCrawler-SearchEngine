#include <stdio.h>
#include "hashtable.h"

int main(){
  char* val1 = "Testing";
  char* val2 = "This";
  char* data1 = "result";
  hashtable_t* ht = hashtable_new(10000);
   hashtable_insert(ht, val1, data1);
  data1 = "pleaseNo!";
   hashtable_insert(ht, val1, data1);
  hashtable_insert(ht, val2, data1);
  hashtable_insert(ht, "lol2", "haha2");
  hashtable_insert(ht, "lol3", "haha3");
  hashtable_insert(ht, "lol4", "haha4");
  hashtable_insert(ht, "lol5", "haha5");
  hashtable_insert(ht, "lol6", "haha6");
  char* ans = hashtable_find(ht, val2);
  printf("Answer: %s\n",ans);
  hashtable_delete(ht);
  return 0;
}

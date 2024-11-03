#include "dllist.h"
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
   DLList* lst = malloc(sizeof(DLList));

   /* Initializing the list */
   initList(lst);

    /* Inserting 50 key value pairs. The key values range from 0 to 49 and the values range from 0 to 98 */
   for(int i=0;i < 50;i++) {
     char k[10];
     sprintf(k, "%d", i);
     char v[10];
     sprintf(v, "%d", i*2);
     insertSortedList(lst, k,v);
   }

   /* Printing the list */
   printListForward(lst);
      
   /* Destroying the list */
   destroyList(lst);

   free(lst);
   
   return 0;
}


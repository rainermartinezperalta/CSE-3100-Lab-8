#ifndef __DLLIST_H
#define __DLLIST_H

#include <stdlib.h>

/* Structure of a node in the doubly linked list */
typedef struct DLNode {
  struct DLNode* next;
  struct DLNode* prv;
  char* key;
  char* value;
} DLNode;

/* Structure of a doubly linked list */
typedef struct DLList {
   DLNode* head;
   DLNode* tail;
} DLList;

void initList(DLList* list);
void destroyList(DLList* list);
char* getValue(DLList* list, char* key);
int insertSortedList(DLList* list, char* key, char* val);
int removeFromList(DLList* list, char* key);
void printListForward(DLList* list);

#endif

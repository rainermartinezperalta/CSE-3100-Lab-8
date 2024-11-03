#ifndef __HASHMAP_H
#define __HASHMAP_H

#include <pthread.h>
#include "dllist.h"

typedef struct Bucket {
  DLList* list;			// a doubly linked list
  pthread_mutex_t lock;		// mutex for the list
} Bucket;

typedef struct HashMap {
  unsigned int numBuckets;	// total number of buckets
  unsigned int numItems;	// total items in a hash map
  Bucket* buckets;		// array of buckets
  pthread_mutex_t tableLock;	// mutex for hash map
} HashMap;

void initHashMap(HashMap* hm, unsigned int nb);
void destroyHashMap(HashMap* hm);
void insertHashMap(HashMap* hm, char* key, char* value);
char* retrieveValue(HashMap* hm, char* key);
void deleteEntry(HashMap* hm, char* key);

#endif

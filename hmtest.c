#include "hashMap.h"
#include<stdio.h>

/* Structure to hold the key value pairs that need to be added from the hash map */
typedef struct AddPairsThreadArgs{
  HashMap* hm;
  char** keys;
  char** values;
  unsigned int numPairs;
} AddPairsThreadArgs;

/* Structure to hold the key value pairs that need to be removed from the hash map */
typedef struct RemoveKeysThreadArgs{
  HashMap* hm;
  char** keys;
  unsigned int numKeys;
} RemoveKeysThreadArgs;

/* Add the key value pairs in the hash map */
void* addPairs(void* arg)
{
  AddPairsThreadArgs* ta = (AddPairsThreadArgs*) arg;
  for(unsigned int i = 0; i < ta->numPairs; i++){
    insertHashMap(ta->hm, ta->keys[i], ta->values[i]);    
    printf("Added key-value pair: (%s, %s)\n", ta->keys[i], ta->values[i]);
  }
  return NULL;
}

/* Remove the key value pairs from the hash map */
void* removeKeys(void* arg)
{
  RemoveKeysThreadArgs* ta = (RemoveKeysThreadArgs*) arg;
  for(unsigned int i = 0; i < ta->numKeys; i++){
    printf("Removing key-value pair: (%s, %s)\n", ta->keys[i], retrieveValue(ta->hm, ta->keys[i]));
    deleteEntry(ta->hm, ta->keys[i]);
  }
  return NULL;
}

int main(){
  
  /* List of key value pairs to be inserted in the hash map */
  char* keys[10] = {"kriti", "hello", "hola", "terrence", "one", "two", "three", "four", "five", "six"};
  char* values[10] = {"bhargava", "bye", "adios", "bell", "a", "b", "c", "d", "e", "f"};
  
  /* Declare an instance of a hash map and initialize it with 3 buckets */
  HashMap hm;
  initHashMap(&hm, 3);

  /* Declare 2 threads. Thread 1 is used to insert the first 5 key value pairs in the hash map. Thread 2 is used to insert the next 5 values in the hash map */
  pthread_t threadOne;
  AddPairsThreadArgs one;
  one.hm = &hm;
  one.keys = keys;
  one.values = values;
  one.numPairs = 5;

  pthread_t threadTwo;
  AddPairsThreadArgs two;
  two.hm = &hm;
  two.keys = keys + 5;
  two.values = values + 5;
  two.numPairs = 5;

  /* Create the threads. Each thread calls the function addPairs*/
  pthread_create(&threadOne, NULL, addPairs, &one);
  pthread_create(&threadTwo, NULL, addPairs, &two);

  /* Wait for the threads to complete their task */
  pthread_join(threadOne, NULL);
  pthread_join(threadTwo, NULL);

  /* Create two threads to remove values from the hash map. The first thread removes the first 5 values and the second thread removes the next 5 values */
  RemoveKeysThreadArgs oneRemove;
  oneRemove.hm = &hm;
  oneRemove.keys = keys;
  oneRemove.numKeys = 5;

  RemoveKeysThreadArgs twoRemove;
  twoRemove.hm = &hm;
  twoRemove.keys = keys + 5;
  twoRemove.numKeys = 5;
  
  pthread_create(&threadOne, NULL, removeKeys, &oneRemove);
  pthread_create(&threadTwo, NULL, removeKeys, &twoRemove);
  
  /* Join the threads once they are done executing */
  pthread_join(threadOne, NULL);
  pthread_join(threadTwo, NULL);

  /* Destroy the hash map */
  destroyHashMap(&hm);
  
  return 0;
}

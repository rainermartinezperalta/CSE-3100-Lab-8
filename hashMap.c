#include "hashMap.h"
#include "dllist.h"
#include <string.h>
#include <pthread.h>

/* Computes the hash value corresponding to the key */
unsigned long long hash(char* key) {
  const int p = 31;
  const int m = 1e9 + 9;
  unsigned long long hash_value = 0;
  long long p_pow = 1;
  for (int i = 0; i < strlen(key); i++) {
    char c = key[i];
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
    p_pow = (p_pow * p) % m;
  }
  return hash_value;
}

void initHashMap(HashMap* hm, unsigned int nb) {
  hm->numBuckets = nb;
  hm->numItems = 0;
  hm->buckets = (Bucket*) malloc(nb * sizeof(Bucket));

  for (unsigned int i = 0; i < nb; i++) {
    hm->buckets[i].list = (DLList*) malloc(sizeof(DLList));
    initList(hm->buckets[i].list);
    pthread_mutex_init(&(hm->buckets[i].lock), NULL);
  }
  pthread_mutex_init(&(hm->tableLock), NULL);
}

void destroyHashMap(HashMap* hm) {
  for (unsigned int i = 0; i < hm->numBuckets; i++) {
    destroyList(hm->buckets[i].list);
    free(hm->buckets[i].list);
    pthread_mutex_destroy(&(hm->buckets[i].lock));
  }
  free(hm->buckets);
  pthread_mutex_destroy(&(hm->tableLock));
  hm->numBuckets = 0;
  hm->numItems = 0;
}

void insertHashMap(HashMap* hm, char* key, char* value) {
  unsigned int h = hash(key) % hm->numBuckets;
  pthread_mutex_lock(&(hm->buckets[h].lock));

  if (insertSortedList(hm->buckets[h].list, key, value)) {
    pthread_mutex_lock(&(hm->tableLock));
    hm->numItems++;
    pthread_mutex_unlock(&(hm->tableLock));
  }

  pthread_mutex_unlock(&(hm->buckets[h].lock));
}

char* retrieveValue(HashMap* hm, char* key) {
  unsigned int h = hash(key) % hm->numBuckets;
  pthread_mutex_lock(&(hm->buckets[h].lock));
  char* value = getValue(hm->buckets[h].list, key);
  pthread_mutex_unlock(&(hm->buckets[h].lock));
  return value;
}

void deleteEntry(HashMap* hm, char* key) {
  unsigned int h = hash(key) % hm->numBuckets;
  pthread_mutex_lock(&(hm->buckets[h].lock));

  if (removeFromList(hm->buckets[h].list, key)) {
    pthread_mutex_lock(&(hm->tableLock));
    hm->numItems--;
    pthread_mutex_unlock(&(hm->tableLock));
  }

  pthread_mutex_unlock(&(hm->buckets[h].lock));
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

// Write your functions here

 void init_cache(HashTable *table) {
     for (int i = 0 ; i < HASH_BUCKETS; i++){
         table->buckets[i]= NULL;
     }
 }
 char **lookup_cache(HashTable *table, const char *key) {
     unsigned int index = hash(key);
     
     CacheEntry *trav = table->buckets[index];
     while (trav != NULL){
         if (strcmp(trav->key, key)==0){
             return trav->results;
         }
         trav=trav->next;
     }
     return NULL;
 }
 bool insert_cache(HashTable *table, const char *key) {
     if (lookup_cache(table,key)!=NULL) // key exists
     {
         return true;
     }\
     if (simulate_database_fetch(key) == NULL){
         return false; // no search result
     }
     unsigned int index = hash(key);
     // key is new proceed with insertion
     CacheEntry *new = malloc(sizeof(CacheEntry));
     if (new == NULL)return false;
     new->key = strdup(key);
     new->results = simulate_database_fetch(key);

     new->next= table->buckets[index];
     table->buckets[index]= new;
     return true;
 }
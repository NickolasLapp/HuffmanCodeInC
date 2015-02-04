#include<stdlib.h>
#include<stdio.h>
#include "hashMap.h"
#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)
#define STD_MAP_SIZE 256
hashMap_t * newHashMap() {
   hashMap_t * newMap = malloc(sizeof(hashMap_t));
   newMap->bucket = calloc(1, STD_MAP_SIZE * sizeof(hashNode_t));
   newMap->sizeArray = calloc(1, STD_MAP_SIZE * sizeof(int));
   return newMap;
}

hashNode_t * newHashNode(unsigned char key, int value) {
   hashNode_t * newNode = malloc(sizeof(hashNode_t));
   newNode->key = key;
   newNode->value = value;
   return newNode;
}

unsigned char basicHash(unsigned char key) {
   return (key + STD_MAP_SIZE) % STD_MAP_SIZE;
}

void put(unsigned char key, int value, hashMap_t * map) {
   int hash = basicHash(key);
   map->bucket[hash] = newHashNode(key, value);
} 

void print(hashMap_t * map) {
   int i;
   for(i = 0; i < STD_MAP_SIZE; i++) {
      hashNode_t * current = map->bucket[i];
      if(current) 
         printf("Key: %c\tValue: %d\n", current->key, current->value); 
   }
}
void printBinary(hashMap_t * map) {
   int i;
   for(i = 0; i < STD_MAP_SIZE; i++) {
      hashNode_t * current = map->bucket[i];
      if(current) 
         printf("Key: %c\tValue: "BYTETOBINARYPATTERN"\t#bits: %d\n", current->key,BYTETOBINARY(current->value), map->sizeArray[i]);
   }
}
int get(unsigned char key, hashMap_t * map) {
   hashNode_t * found = map->bucket[basicHash(key)];
   if(found)
      return found->value;
   return -1; //not found
}


void setCodeSize(unsigned char key, int size, hashMap_t * map) {
   map->sizeArray[basicHash(key)] = size;
}

int getCodeSize(unsigned char key, hashMap_t * map) {
   return map->sizeArray[basicHash(key)];
}

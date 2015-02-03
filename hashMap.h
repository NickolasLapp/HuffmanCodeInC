#ifndef HASH_MAP_H
#define HASH_MAP_H

typedef struct hashNode
{
   unsigned char key;
   int value;
} hashNode_t;

typedef struct hashMap
{
   hashNode_t ** bucket;
} hashMap_t;


hashNode_t * newHashNode(unsigned char key, int value);
hashMap_t * newHashMap();
unsigned char basicHash(unsigned char key);
void put(unsigned char key, int value, hashMap_t * map);
void print(hashMap_t * map);
int get(unsigned char key, hashMap_t * map);
#endif

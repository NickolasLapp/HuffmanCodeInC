#ifndef MIN_HEAP_H
#define MIN_HEAP_H
#define STD_MAP_SIZE 256
#include "huffmanNode.h"
#include "hashMap.h"

typedef struct minHeap {
   huffmanNode_t ** nodes; 
   int index;
} minHeap_t;   

void printAndDeleteMinHeap(minHeap_t * queue);
huffmanNode_t * removeNode(minHeap_t * queue);
minHeap_t * fillHeapWithFrequencyTable(hashMap_t * frequencyTable);
#endif

#include "minHeap.h"
#include "hashMap.h"
#include "huffmanNode.h"
#include <stdlib.h>
#include <stdio.h>

static minHeap_t * newMinHeap() {
   minHeap_t * newHeap = malloc(sizeof(minHeap_t));
   newHeap->nodes = malloc(STD_MAP_SIZE * sizeof(huffmanNode_t));
   newHeap->index = 0; 
   return newHeap;
}

static void insertNode(minHeap_t * queue, huffmanNode_t * toInsert) {
   int index = queue->index++;
   queue->nodes[index] = toInsert;

   while(index > 0 && queue->nodes[(index - 1) / 2]->frequency > toInsert->frequency)
   {
      queue->nodes[index] = queue->nodes[(index - 1) / 2];
      index = (index - 1) / 2;
      queue->nodes[index] = toInsert;
   }
}

void printAndDeleteMinHeap(minHeap_t * queue)
{
   huffmanNode_t * popped;
   while(popped = removeNode(queue))
      printf("Removed Key: %c\tWith Frequency: %d", popped->key, popped->frequency);
}

huffmanNode_t * removeNode(minHeap_t * queue) {
   huffmanNode_t * toReturn = queue->nodes[0];
   if(!toReturn)
      return NULL; 
   queue->nodes[0] = queue->nodes[queue->index--];
   int start = 0;
   huffmanNode_t * tempNode;

 
   while(start * 2 + 1 <= queue->index && (queue->nodes[start]->frequency >  queue->nodes[start * 2 +1]->frequency || 
               queue->nodes[start]->frequency > queue->nodes[start * 2 + 2]->frequency))
   {  
      if(queue->nodes[start * 2 + 1]->frequency < queue->nodes[start*2+2]->frequency) { //use *2 + 1
         tempNode = queue->nodes[start*2+1];
         queue->nodes[start*2+1] = queue->nodes[start];
         queue->nodes[start] = tempNode; 
         start = start * 2 + 1; 
      }
      else {
         tempNode = queue->nodes[start*2+2];
         queue->nodes[start*2+2] = queue->nodes[start];
         queue->nodes[start] = tempNode;
         start = start * 2 + 2; 
      } 
   }
   return toReturn;
}

minHeap_t * fillHeapWithFrequencyTable(hashMap_t * frequencyTable) {
   minHeap_t * priorityQueue; 

   hashNode_t * current;
   huffmanNode_t * treeNode;
   int numProcessed = 0;

   priorityQueue = newMinHeap();
 
   do { 
      current = frequencyTable->bucket[numProcessed++];
      if(current) {
         treeNode = newNodeFromData(current->key, current->value); 
         insertNode(priorityQueue, treeNode);
      }
   } while (numProcessed < STD_MAP_SIZE); 

   return priorityQueue;
}


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

void insertNode(minHeap_t * queue, huffmanNode_t * toInsert) {
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
   while((queue->index >= 1) && (popped = removeNode(queue)))
      printf("Removed Key: %c\tWith Frequency: %d\n", popped->key, popped->frequency);
}

huffmanNode_t * removeNode(minHeap_t * queue) {
   huffmanNode_t * toReturn = newNodeFromData(queue->nodes[0]->key, queue->nodes[0]->frequency);
   queue->index--; 
   queue->nodes[0] = queue->nodes[queue->index];
   
   queue->nodes[queue->index] = NULL; //this will cause meory leaks. Address later
   
   int currentNodeI = 0;
   huffmanNode_t * tempNode;
    
   while(((queue->index>currentNodeI*2+1)&&(queue->nodes[currentNodeI]->frequency>queue->nodes[currentNodeI*2+1]->frequency)) || 
         ((queue->index>currentNodeI*2+2)&&(queue->nodes[currentNodeI]->frequency>queue->nodes[currentNodeI*2+2]->frequency)))
   {
      if(currentNodeI*2+2 < queue->index) { //both defined, so safe to use either  
         if(queue->nodes[currentNodeI*2+1]->frequency < queue->nodes[currentNodeI*2+2]->frequency) { //use *2 + 1
            tempNode = queue->nodes[currentNodeI*2+1];
            queue->nodes[currentNodeI*2+1] = queue->nodes[currentNodeI];
            queue->nodes[currentNodeI] = tempNode; 
            currentNodeI = currentNodeI * 2 + 1; 
         }
         else {
            tempNode = queue->nodes[currentNodeI*2+2];
            queue->nodes[currentNodeI*2+2] = queue->nodes[currentNodeI];
            queue->nodes[currentNodeI] = tempNode;
            currentNodeI = currentNodeI * 2 + 2; 
         }
      }
      else { //only the second defined, must be the closer child 
         tempNode = queue->nodes[currentNodeI*2+1];
         queue->nodes[currentNodeI*2+1] = queue->nodes[currentNodeI];
         queue->nodes[currentNodeI] = tempNode; 
         currentNodeI = currentNodeI * 2 + 1; 
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


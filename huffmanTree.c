#include "huffmanNode.h"
#include "hashMap.h"
#include "huffmanTree.h"
#include "minHeap.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 65536
#define MAX(a, b) a > b ? a : b


int main(int argc, char ** argv)
{
   FILE * inputFile;
   hashMap_t * frequencyTable, * codeLookupTable;
   minHeap_t * priorityQueue;
   huffmanNode_t * huffmanTree;


   inputFile = fopen("testFile.txt", "r");
   frequencyTable = newHashMap();
   populateFrequencyTable(inputFile, frequencyTable);
   print(frequencyTable); 
  
   codeLookupTable = newHashMap();
   priorityQueue = fillHeapWithFrequencyTable(frequencyTable);
 
   huffmanTree = generateHuffmanTree(priorityQueue);  
 
   fclose(inputFile);  
   return 1;
}

void populateFrequencyTable(FILE * inputFile, hashMap_t * frequencyTable) {
   unsigned char buffer[BUFFER_SIZE] = {};
   int charsRead, i;
   
   do {
      charsRead = fread(buffer, sizeof(char), BUFFER_SIZE, inputFile);
      for(i = 0; i < charsRead; i++)
      {
         int previousFrequency = get(buffer[i], frequencyTable);
         put(buffer[i], MAX(previousFrequency + 1, 1), frequencyTable);
      } 
   } while(charsRead > 0);
}

huffmanNode_t * generateHuffmanTree(minHeap_t * priorityQueue) {
   while(priorityQueue->index > 1) 
      insertNode(priorityQueue, newNodeFromChildren(removeNode(priorityQueue), removeNode(priorityQueue)));
   return removeNode(priorityQueue);
} 

void populateCodingTable(hashMap_t * codingTable, huffmanNode_t * huffmanTree) {
   huffmanNode_t * current = huffmanTree;
//   if(!current.left)
          
}      

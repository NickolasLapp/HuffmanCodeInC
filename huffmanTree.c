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
//   printAndDeleteMinHeap(priorityQueue);
 
   huffmanTree = generateHuffmanTree(priorityQueue);  
   populateCodingTable(codeLookupTable, huffmanTree, 0, 0);

   printBinary(codeLookupTable); 
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
   huffmanNode_t * tempNode;
   while(priorityQueue->index > 1)
   { 
      tempNode = newNodeFromChildren(removeNode(priorityQueue), removeNode(priorityQueue));
      insertNode(priorityQueue, tempNode);
   }
   return removeNode(priorityQueue);
} 

void populateCodingTable(hashMap_t * codingTable, huffmanNode_t * node, int code, int size) {
   if(node->left == 0) {
      put(node->key, code, codingTable); 
      setCodeSize(node->key, size, codingTable);   
   }
   else {
      populateCodingTable(codingTable, node->left, code<<1, size+1);
      populateCodingTable(codingTable, node->right, (code<<1) | 1, size+1);
   }
}      

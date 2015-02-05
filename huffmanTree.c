#include "huffmanNode.h"
#include "hashMap.h"
#include "huffmanTree.h"
#include "minHeap.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 65536
#define MAX(a, b) a > b ? a : b

static void encodeFile(FILE * inputFile,FILE * outputCodedFile, hashMap_t * codeLookupTable);  
static unsigned int setZeroethBit(unsigned int writeTo, int writeFrom, char whichBit); 

int main(int argc, char ** argv)
{
   FILE * inputFile, * outputCodedFile;
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
   
   rewind(inputFile); 

   outputCodedFile = fopen("outputCodedFile", "w");
   encodeFile(inputFile, outputCodedFile, codeLookupTable);  
   
   fclose(inputFile);  
   fclose(outputCodedFile);
   return 1;
}

void populateFrequencyTable(FILE * inputFile, hashMap_t * frequencyTable) {
   unsigned char buffer[BUFFER_SIZE] = {};
   int charsRead, i;
   
   do {
      charsRead = fread(buffer, sizeof(char), BUFFER_SIZE, inputFile);
      for(i = 0; i < charsRead; i++) {
         int previousFrequency = get(buffer[i], frequencyTable);
         put(buffer[i], MAX(previousFrequency + 1, 1), frequencyTable);
      } 
   } while(charsRead > 0);
}

huffmanNode_t * generateHuffmanTree(minHeap_t * priorityQueue) {
   huffmanNode_t * tempNode;
   while(priorityQueue->index > 1) {
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


static void encodeFile(FILE * inputFile,FILE * outputCodedFile, hashMap_t * codeLookupTable) {
   unsigned char buffer[BUFFER_SIZE] = {};
   int charsRead, i, j;
   
   do {
      char numBitsPut = 0; 
      charsRead = fread(buffer, sizeof(char), BUFFER_SIZE, inputFile);
      for(i = 0; i < charsRead; i++) {
         unsigned int toWrite = 0;
         hashNode_t * current = getHashNode(buffer[i], codeLookupTable);   
         int numBits = getCodeSize(current->key, codeLookupTable); 
         int code  = current->value;
         for(j = 0; j < numBits; j++) {
            if(numBitsPut == sizeof(toWrite) * 8-1) {
               fprintf(outputCodedFile, "%c", toWrite);
               toWrite = 0;
            }
            toWrite = setZeroethBit(toWrite<<1, code, j);
            numBitsPut++; 
         }
      }
   } while(charsRead > 0);
}

static unsigned int setZeroethBit(unsigned int writeTo, int writeFrom, char whichBit) {
   unsigned int toSet = ((writeFrom & (1<<whichBit)) != 0);
   if(!toSet)
      return writeTo;
   else
      return writeTo | (1<<whichBit);
}

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


   inputFile = fopen("testFile.txt", "r");
   frequencyTable = newHashMap();
   populateFrequencyTable(inputFile, frequencyTable);
   print(frequencyTable); 
  
   codeLookupTable = newHashMap();
   priorityQueue = fillHeapWithFrequencyTable(frequencyTable);
   printAndDeleteMinHeap(priorityQueue);   
   
 
   fclose(inputFile);  
   return 1;
}

void populateFrequencyTable(FILE * inputFile, hashMap_t * frequencyTable) {
   char buffer[BUFFER_SIZE] = {};
   int charsRead, i;
   
   do {
      charsRead = fread(buffer, sizeof(char), BUFFER_SIZE, inputFile);
      for(i = 0; i < charsRead; i++)
      {
         int previousFrequency = get(buffer[i], frequencyTable);
         put((int)buffer[i], MAX(previousFrequency + 1, 1), frequencyTable);
      } 
   } while(charsRead > 0);
}


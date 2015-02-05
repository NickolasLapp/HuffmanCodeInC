#include "huffmanNode.h"
#include <stdlib.h>
#define BUFFER_SIZE 65536

huffmanNode_t * newNodeFromData(unsigned char key, int frequency) {
   huffmanNode_t * newNode = malloc(sizeof(huffmanNode_t));
   newNode->frequency = frequency; 
   newNode->key = key; 
   newNode->left = newNode->right = NULL;
   return newNode;    
}

huffmanNode_t * newNodeFromChildren(huffmanNode_t * leftChild, huffmanNode_t * rightChild) {
   huffmanNode_t * newNode = malloc(sizeof(huffmanNode_t));
   newNode->frequency = leftChild->frequency + rightChild->frequency;
   newNode->left = leftChild;
   newNode->right = rightChild;
   newNode->key = 0; 
   return newNode;    
}

void printFileFromCodedFile(FILE * outputCodedFile, huffmanNode_t *  huffmanTree) {
   char buffer[BUFFER_SIZE] = {};
   int charsRead, bufferIndex;
   huffmanNode_t * current = huffmanTree;
   do {
      charsRead = fread(buffer, sizeof(char), BUFFER_SIZE, outputCodedFile);

      for(bufferIndex = 0; bufferIndex < charsRead; bufferIndex++) {
         char read = buffer[bufferIndex], bit;
         for( bit = sizeof(read) * 8 - 1; bit >= 0; bit--) {
            if(current->left == NULL) {
               printf("%c", current->key);
               current = huffmanTree;
               bit++;
            }
            else if(read & (1 << bit))
              current = current->right;
            else
               current = current->left;
          }
      }
   } while (charsRead > 0);  
}

#include "huffmanNode.h"
#include <stdlib.h>

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
   return newNode;    
}


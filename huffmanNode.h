#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H
#include <stdio.h>
typedef struct node
{
   struct node * left;
   struct node * right;
   int frequency; 
   unsigned char key;
   int keySize;
} huffmanNode_t;

huffmanNode_t * newNodeFromChildren(huffmanNode_t * leftChild, huffmanNode_t * rightChild); 
huffmanNode_t * newNodeFromData(unsigned char key, int frequency);
void setSize(huffmanNode_t * node, int size);
void printFileFromCodedFile(FILE * outputCodedFile, huffmanNode_t *  huffmanTree);
#endif

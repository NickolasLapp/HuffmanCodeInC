#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

typedef struct node
{
   struct node * left;
   struct node * right;
   int frequency; 
   unsigned char key;
} huffmanNode_t;

huffmanNode_t * newNodeFromChildren(huffmanNode_t * leftChild, huffmanNode_t * rightChild); 
huffmanNode_t * newNodeFromData(unsigned char key, int frequency);
#endif

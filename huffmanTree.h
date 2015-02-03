#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include "huffmanNode.h"
#include "minHeap.h"

void populateFrequencyTable();
huffmanNode_t * generateHuffmanTree(minHeap_t * priorityQueue);  

#endif

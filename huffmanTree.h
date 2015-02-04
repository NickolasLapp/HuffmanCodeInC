#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include "huffmanNode.h"
#include "minHeap.h"

void populateFrequencyTable();
huffmanNode_t * generateHuffmanTree(minHeap_t * priorityQueue);
void populateCodingTable(hashMap_t * codingTable, huffmanNode_t * node, int code, int size);
#endif

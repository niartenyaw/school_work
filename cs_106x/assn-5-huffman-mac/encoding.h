/**
 * File: encoding.h
 * ----------------
 * Defines the Encoding class to manage all aspects of the
 * Huffman compression and decompression algorithms.
 */

#ifndef _encoding_
#define _encoding_

#include "bstream.h"
#include "pqueue.h"
#include "map.h"

class Encoding {
public:
    Encoding();
    ~Encoding();

    void compress(ibstream& infile, obstream& outfile);
    void decompress(ibstream& infile, obstream& outfile);

private:
    struct node {
        int elem = 300;
        int numUses;
        node *left;
        node *right;
    };
    PQueue<node *> queue; // Queue of all 
    node *finalRoot;
    Map<int,int> frequencies;
    string *array;
    
    void deleteTree(node *root);
    void countFrequencies(ibstream& infile);
    void createTree();
    void printQueue();
    void printTree(node *curr);
    void createArray();
    void followTree(node * curr, string bitPattern);
    void printArray();
    void writeFile(ibstream& infile, obstream& outfile);
    
    void readArray(ibstream& infile);
    void writeDecomp(ibstream& infile, obstream& outfile);
};

#endif

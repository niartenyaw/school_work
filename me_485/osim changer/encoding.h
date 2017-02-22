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
    
    void findMuscle(string line, ibstream& infile, obstream& outfile, bool& changing);
};

#endif

/** * File: encoding.cpp * ------------------ * Place your Encoding class implementation here. */#include "encoding.h"#include "strlib.h"#include <iostream>using namespace std;const int kASCII_NUMBERS = 256;const string SENTINEL = ":";const int NEW_LINE_ASCII = 10;Encoding::Encoding(){    array = new string[kASCII_NUMBERS + 1];    for(int i = 0; i < kASCII_NUMBERS; i++){        array[i] = "2";    }}Encoding::~Encoding(){    deleteTree(finalRoot);}void Encoding::compress(ibstream& infile, obstream& outfile){    countFrequencies(infile);    createTree();    //printTree(finalRoot);    createArray();    //printArray();    infile.rewind();    writeFile(infile, outfile);}void Encoding::decompress(ibstream& infile, obstream& outfile){    readArray(infile);    writeDecomp(infile, outfile);}void Encoding::deleteTree(node *root){    if(left == NULL) return;    deleteTree(root->left);    deleteTree(root->right);    delete root;}void Encoding::countFrequencies(ibstream& infile){    string line;    getline(infile, line);    while(true){        for(int i = 0; i < line.length(); i++){            int ascii = (int)line[i];            if(frequencies.containsKey(ascii)){                frequencies[ascii]++;            }            else{                frequencies[ascii] = 1;            }        }        getline(infile, line);        if(infile.fail()) break;        frequencies[NEW_LINE_ASCII]++;    }    frequencies[kASCII_NUMBERS] = 1;}void Encoding::printQueue(){    int size = queue.size();    for(int i = 0; i < size; i++){        node *curr = queue.extractMin();        cout << curr->elem << " " << curr->numUses << endl;    }}void Encoding::printTree(node * curr){    if(curr == NULL) return;    printTree(curr->left);    printTree(curr->right);    cout << curr->elem << " " << curr->numUses << endl;}void Encoding::createTree(){    for(int i = 0; i < kASCII_NUMBERS + 1; i++){ // Adds all single nodes to the PQueue        // +1 for the terminal         if(frequencies.containsKey(i)){            node *add = new node;            add->elem = i;            add->numUses = frequencies[i];            add->left = NULL;            add->right = NULL;            queue.enqueue(add, add->numUses);        }    }    //printQueue();    while(queue.size() > 1){ // Combines the two smallest frequency node trees together until there is only one left        node *curr = new node;        curr->left = queue.extractMin();        curr->right = queue.extractMin();        curr->numUses = curr->left->numUses + curr->right->numUses;        queue.enqueue(curr, curr->numUses);    }    finalRoot = queue.extractMin(); // There is only one left in the queue.}void Encoding::createArray(){    followTree(finalRoot, "");}void Encoding::followTree(node * curr, string bitPattern){    if(curr == NULL) return;    if(curr->elem != 300){        array[curr->elem] = bitPattern;        return;    }    else{        followTree(curr->left, bitPattern + "0");        followTree(curr->right, bitPattern + "1");    }}void Encoding::printArray(){    for(int i = 0; i < kASCII_NUMBERS + 1; i++){        cout << i << " " << array[i] << endl;    }}void Encoding::writeFile(ibstream& infile, obstream& outfile){    //obstream ofile;    //string filename = "bits.txt";    //ofile.open(filename.c_str());        for(int i = 0; i < kASCII_NUMBERS + 1; i++){        if(array[i] != "2"){            outfile << array[i] << "-" << i << ":";        }    }    outfile << SENTINEL;        char ch;    while(infile.get(ch)){        int ascii = (int) ch;        string asciiS = array[ascii];        for(int i = 0; i < asciiS.length(); i++){            //ofile << asciiS[i];            string bitS = asciiS.substr(i,1);            int bit = stringToInteger(bitS);            outfile.writebit(bit);        }    }    string asciiS = array[kASCII_NUMBERS];    for(int i = 0; i < asciiS.length(); i++){        //ofile << asciiS[i];        string bitS = asciiS.substr(i,1);        int bit = stringToInteger(bitS);        outfile.writebit(bit);    }}void Encoding::readArray(ibstream& infile){    char ch;    infile.get(ch);    while(true){        string binary = "";        string ascii = "";        while(isdigit(ch)){            binary += ch;            infile.get(ch);        }        infile.get(ch);        while(isdigit(ch)){            ascii += ch;            ch = infile.get();        }        int asciiInt = stringToInteger(ascii);        array[asciiInt] = binary;        infile.get(ch);        if(!isdigit(ch)) break;    }}void Encoding::writeDecomp(ibstream& infile, obstream& outfile){    string bitString = "";    while(true){        int bit = infile.readbit();        if(infile.fail()) break;        bitString += integerToString(bit);        if(bitString == array[kASCII_NUMBERS]) break;        for(int i = 0; i < kASCII_NUMBERS; i++){            if(array[i] == bitString){                char ch = i;                outfile.put(ch);                bitString = "";                break;            }        }    }}
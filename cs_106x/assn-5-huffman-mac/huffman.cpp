/**
 * File: huffman.cpp 
 * -------------------
 * Huffman main module.  Build it!
 */

#include <iostream>
#include "console.h"
#include "bstream.h"
#include "encoding.h"
using namespace std;

static string lower(string response);
static void compress();
static void decompress();

int main() {
    
    cout << "Welcome to my version of the compression program!" << endl;
    cout << endl;
    cout << "This program uses Huffman encoding to compress and decompress any file." << endl;
    cout << "Compressing a file will substantially reduce most file sizes with the" << endl;
    cout << "ability to faithfully reproduce the original file." << endl;
    cout << endl;
    
    while (true){
        while (true){
            cout << "Would you like to compress or decompress another file? ";
            string response;
            getline(cin, response);
            if(lower(response) == "no") return 0;
            else if(lower(response) == "yes") break;
            else cout << "Please enter yes or no." << endl;
        }
        while (true){
            cout << "Are we compressing a file? ";
            string response;
            getline(cin, response);
            if(lower(response) == "no") {
                decompress();
                break;
            }
            else if(lower(response) == "yes") {
                compress();
                break;
            }
            else cout << "Please enter yes or no." << endl;
        }
    }
    return 0;
}

static string lower(string response){
    string returner = "";
    for(int i = 0; i < response.length(); i++){
        returner += tolower(response[i]);
    }
    return returner;
}

static void compress(){
    ibstream infile;
    string filename;
    while(true){
        cout << "File to compress: ";
        getline(cin, filename);
        cout << endl;
        infile.open(filename.c_str());
        if(!infile.fail()) break;
        cout << "That is not a proper file name." << endl;
    }
    
    obstream outfile;
    string newFile;
    cout << "Enter the new file name: ";
    getline(cin, newFile);
    cout << endl;
    outfile.open(newFile.c_str());
    
    Encoding *encoder = new Encoding();
    encoder->compress(infile, outfile);
    
    double original = infile.size();
    double compressed = outfile.size();
    int ratio = compressed * 100 / original;
    
    cout << "The new file is " << ratio << "% the size of the original." << endl;
    cout << endl;
}

static void decompress(){
    ibstream infile;
    string filename;
    while(true){
        cout << "File to decompress: ";
        getline(cin, filename);
        cout << endl;
        infile.open(filename.c_str());
        if(!infile.fail()) break;
        cout << "That is not a proper file name." << endl;
    }
    
    string newFile;
    cout << "Enter the new file name: ";
    getline(cin, newFile);
    cout << endl;
    obstream outfile;
    outfile.open(newFile.c_str());
    
    Encoding *encoder = new Encoding();
    encoder->decompress(infile, outfile);
    
}


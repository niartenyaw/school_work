/**
 * File: huffman.cpp
 * -------------------
 * This one works with osim files!!
 */

#include <iostream>
#include "console.h"
#include "encoding.h"
using namespace std;

static string lower(string response);
static void change();

int main() {
    
    cout << "Welcome to my version of the muscle program!" << endl;
    cout << endl;
    cout << "This program replaces Thelen muscles with default Millard muscles file." << endl;
    cout << endl;
    
    change();
    return 0;
}

static string lower(string response){
    string returner = "";
    for(int i = 0; i < response.length(); i++){
        returner += tolower(response[i]);
    }
    return returner;
}

static void change(){
    ibstream infile;
    string filename;
    while(true){
        cout << "File to change: ";
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
    
    cout << "The new file has been completed." << endl;
    cout << endl;
}


/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "vector.h"
#include "map.h"
#include "random.h"


static string getFileName();
static bool isValidGrammarFilename(string filename);
static string getNormalizedFilename(string filename);
static void readFile(ifstream & infile, Map< string, Vector<string> > & grammar);
static void startSentence(Map< string, Vector<string> > & grammar);
static void completeSentence(Map< string, Vector<string> > & grammar, string & sentence);
static bool containsNonTerminal(string sentence);


int main() {
    while (true) {
        string filename = getFileName();
        if (filename.empty()) break;
        
        ifstream infile(getNormalizedFilename(filename).c_str());
        Map< string, Vector<string> > grammar;
        readFile(infile, grammar);
        
        startSentence(grammar);
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}


static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        if (filename.empty() || isValidGrammarFilename(filename)) return filename;
        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}


static bool isValidGrammarFilename(string filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}


static const string kGrammarsDirectory = "grammars/";
static const string kGrammarFileExtension = ".g";
static string getNormalizedFilename(string filename) {
    string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}


static void readFile(ifstream & infile, Map< string, Vector<string> > & grammar){
    while(true){
        string nonTerminal, optionNumber, current;
        getline(infile, nonTerminal);
        
        if(infile.fail()) break;
        
        getline(infile, optionNumber);
        Vector<string> options;
        for(int i = 0; i < stringToInteger(optionNumber); i++){
            getline(infile, current);
            options.add(current);
        }
        getline(infile, current); // Gets rid of the empty line after each grouping.
        grammar.put(nonTerminal, options);
    }
}


static const string startString = "<start>";
static void startSentence(Map< string, Vector<string> > & grammar){
    Vector<string> starter = grammar.get(startString);
    string sentence = starter.get(randomInteger(0, starter.size() - 1));
    
    while(containsNonTerminal(sentence)){
        completeSentence(grammar, sentence);
    }
    cout << sentence << endl << endl;
    return;
}


static void completeSentence(Map< string, Vector<string> > & grammar, string & sentence){
    int nonTermStartIndex = sentence.find('<');
    int nonTermStopIndex = sentence.find('>');
    
    string nonTerminal = sentence.substr(nonTermStartIndex, nonTermStopIndex - nonTermStartIndex + 1); // + 1 makes sure to capture the '>' at the end
    Vector<string> replacers = grammar.get(nonTerminal);
    int replaceNumber;
    if(replacers.size() == 1){
        replaceNumber = 0;
    } else {
        replaceNumber = randomInteger(0, replacers.size() - 1);
    }
    sentence.replace(nonTermStartIndex, nonTermStopIndex - nonTermStartIndex + 1, replacers.get(replaceNumber));
}


static bool containsNonTerminal(string sentence){
    for(int i = 0; i < sentence.length(); i++){
        if(sentence[i] == '<') return true;
    }
    return false;
}






/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
#include "queue.h"
#include "lexicon.h"

static void playWordLadder();
static void generateLadder(Lexicon& english, string start, string end);
static string getWord(Lexicon& english, string prompt);
static void printLadder(Vector<string> ladder);
static bool oneLetterAway(string last, string word);

int main() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}


static const string kEnglishLanguageDatafile = "EnglishWords.dat";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        if(start == end){
            cout << "Those are the same words." << endl;
            playWordLadder();
            return;
        }
        else{
            generateLadder(english, start, end);
        }
    }
}


static string getWord(Lexicon& english, string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}


static void generateLadder(Lexicon& english, string start, string end) {
    Queue< Vector<string> > ladders;
    Vector<string> ladder;
    Lexicon usedWords;
    
    ladder.add(start);
    ladders.enqueue(ladder);
    while(!ladders.isEmpty()) {
        Vector<string> current = ladders.dequeue();
        
        string last = current.get(current.size() - 1);
        foreach (string word in english){
            if(!usedWords.contains(word) && oneLetterAway(last, word)){
                if(word == end){
                    current.add(word);
                    printLadder(current);
                    return;
                }
                else{
                    Vector<string> newList = current;
                    cout << newList.size() << " " << word << endl;
                    newList.add(word);
                    ladders.enqueue(newList);
                    usedWords.add(word);
                }
            }
        }
    }
}


static bool oneLetterAway(string last, string word) {
    if(last.length() != word.length()) return false;
    
    int lettersAway = 0;
    for(int i = 0; i < last.length(); i++){
        if(last[i] != word[i]){
            lettersAway++;
        }
    }
    if(lettersAway == 1){
        return true;
    } else{
        return false;
    }
}


static void printLadder(Vector<string> ladder){
    cout << "Your word ladder is: " ;
    cout << ladder[0];
    for(int i = 1; i < ladder.size(); i++){
        cout << " " << ladder[i];
    }
    cout << endl << endl;
}




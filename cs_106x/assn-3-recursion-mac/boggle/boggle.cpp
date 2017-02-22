/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 */


#include <iostream>  // for cout, endl

#include <ctype.h>
#include "simpio.h"
#include "gwindow.h"
#include "gboggle.h"
#include "grid.h"
#include "random.h"
#include "lexicon.h"
#include "queue.h"

using namespace std;


const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;
const int kShortestWordLength = 4;

const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

struct coord{
    int row;
    int col;
};

static bool responseIsAffirmative(const string& prompt);
static void welcome();
static void giveInstructions();
static int getDimensions();
static void createBoard(GWindow& window, Grid<char>& board, int nDimensions);
static void userPlaysBoggle(GWindow& gw, Grid<char>& board, Lexicon& english);
static void getUserWords(GWindow& window, Grid<char>& board, Lexicon& english);
static bool checkForWord(Grid<char>& board, string current, int i, int j, Stack<coord>& path);
static void showWord(Stack<coord>& path);
static void changeToUpperCase(string& answer);
static void computerOwnsUser(GWindow& window, Grid<char>& board, Lexicon& english);
static void findAllWords(GWindow& window, Grid<char>& board, Lexicon& english,
                         Set<string>& usedWords, int i, int j, string word, Queue<coord> path);


int main() {
    GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
    initGBoggle(gw);
    Lexicon english("EnglishWords.dat");
    welcome();
    if (responseIsAffirmative("Do you need instructions? ")) {
       giveInstructions();
    }
    
    int nDimensions = getDimensions();
    Grid<char> board;
    createBoard(gw, board, nDimensions);
    userPlaysBoggle(gw, board, english);
    computerOwnsUser(gw, board, english);
    return 0;
}


static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}


static bool responseIsAffirmative(const string& prompt) {
    while (true) {
        string answer = getLine(prompt);
        if (!answer.empty()) {
            switch (toupper(answer[0])) {
                case 'Y': return true;
                case 'N': return false;
            }
        }
        cout << "Please answer yes or no." << endl;
    }
}


static void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit <return> when you're ready...";
    getLine();
}


static int getDimensions() {
    while(true){
        cout << endl;
        cout << "The dimensions of the board must be between 3x3 and 5x5.";
        cout << "Please enter the size of the board: ";
        int dimension = getInteger();
        if(dimension >= 3 && dimension <= 5){
            return dimension;
        }
        cout << endl;
    }
}


static void createBoard(GWindow& window, Grid<char>& board, int nDimensions){
    board.resize(nDimensions, nDimensions);
    drawBoard(nDimensions, nDimensions);
    Vector<string> scrambled;
    for(int i = 0; i < 25; i++){
        scrambled.add(kBigBoggleCubes[i]);
    }
    for(int j = 0; j < scrambled.size(); j++){
        string temp = scrambled[j];
        int random = randomInteger(0,scrambled.size() - 1);
        scrambled[j] = scrambled[random];
        scrambled[random] = temp;
    }
    
    for(int i = 0; i < nDimensions; i++){
        for(int j = 0; j < nDimensions; j++){
            string cubeSides = scrambled.get(0);
            int randomSide = randomInteger(0,5);
            board[i][j] = cubeSides[randomSide];
            labelCube(i, j, cubeSides[randomSide]);
            scrambled.remove(0);
        }
    }
}


static void userPlaysBoggle(GWindow& window, Grid<char>& board, Lexicon& english) {
    cout << "Enter all of the english words you can find." << endl;
    cout << "Press <enter> when you are done looking for words and it will be the computer's turn." << endl;
    
    getUserWords(window, board, english);
}


static void getUserWords(GWindow& window, Grid<char>& board, Lexicon& english){
    Set<string> usedWords;
    while(true){
        Stack<coord> path;
        string answer = getLine();
        if(answer.empty()) break; // Checks for the empty string to stop inputing words.
        changeToUpperCase(answer);
        if(answer.length() >= kShortestWordLength){
            if(english.contains(answer)){ // Checks to make sure it is an english word.
                bool firstLetterFound = false;
                // Allows all the possible starting points to be checked while being able to quit it at any time.
                for(int i = 0; i < board.numRows(); i++){
                    for(int j = 0; j < board.numCols(); j++){
                        if(board[i][j] == answer[0]){ // Checks for a spot to start looking for the word.
                            firstLetterFound = true;
                            if(!usedWords.contains(answer)){ // Checks if the word has already been used.
                                usedWords.add(answer);
                                if(checkForWord(board, answer.substr(1), i, j, path)){ // Checks that spot for the user's word.
                                    // Breaks out of the for loops so no repeats are found if they are possible.
                                    recordWordForPlayer(answer, HUMAN);
                                    coord adder = {i, j};
                                    path.push(adder);
                                    i = board.numRows();
                                    j = board.numCols();
                                }
                                else{
                                    cout << "That word is not on this board." << endl;
                                }
                            }
                            else{
                                cout << "You have already used that word." << endl;
                            }
                        }
                    }
                }
                if(!firstLetterFound){
                    cout << "That word is not on this board." << endl;
                }
            }
            else{
                cout << "That is not a valid english word. Try another." << endl;
            }
        }
        else{
            cout << "That word is not long enough to score." << endl;
        }
        //if(!path.isEmpty()){
            showWord(path);
        //}
    }
}


static void showWord(Stack<coord>& path){
    while(!path.isEmpty()){
        coord nextCoord = path.pop();
        highlightCube(nextCoord.row, nextCoord.col, true);
        highlightCube(nextCoord.row, nextCoord.col, false);
    }
}

static void showWord(Queue<coord>& path){
    while(!path.isEmpty()){
        coord nextCoord = path.dequeue();
        highlightCube(nextCoord.row, nextCoord.col, true);
        highlightCube(nextCoord.row, nextCoord.col, false);
    }
}


static void changeToUpperCase(string& answer){
    string upperCase;
    for(int i = 0; i < answer.length(); i++){
        upperCase += toupper(answer[i]);
    }
    answer = upperCase;
}


static bool checkForWord(Grid<char>& board, string current, int i, int j, Stack<coord>& path){
    if(current.empty()){
        return true;
    }
    char nextChar = current[0];
    for(int k = -1; k <= 1; k++){
        for(int m = -1; m <= 1; m++){
            if(board.inBounds(i+k, j+m)){
                if(board[i + k][j + m] == nextChar){
                    if(checkForWord(board, current.substr(1), i + k, j + m, path)){
                        coord newCoord = {i+k, j+m};
                        path.push(newCoord);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


static void computerOwnsUser(GWindow& window, Grid<char>& board, Lexicon& english){
    Set<string> usedWords;
    for(int i = 0; i < board.numRows(); i++){
        for(int j = 0; j < board.numCols(); j++){
            string newWord = "" + board[i][j];
            Queue<coord> path;
            coord newCoord = {i, j};
            path.enqueue(newCoord);
            findAllWords(window, board, english, usedWords, i, j, newWord, path);
        }
    }
}


static void findAllWords(GWindow& window, Grid<char>& board, Lexicon& english,
                         Set<string>& usedWords, int i, int j, string word, Queue<coord> path){
    if(word.length() >= kShortestWordLength){
        if(english.contains(word)){
            if(!usedWords.contains(word)){
                usedWords.add(word);
                recordWordForPlayer(word, COMPUTER);
                showWord(path);
            }
        }
    }
    if(english.containsPrefix(word)){
        for(int k = -1; k <= 1; k++){
            for(int m = -1; m <= 1; m++){
                bool center = (k == 0) && (m == 0);
                if(board.inBounds(i+k, j+m) && !center){
                    coord newCoord = {i+k, j+m};
                    path.enqueue(newCoord);
                    findAllWords(window, board, english, usedWords, i+k, j+m, word + board[i+k][j+m], path);
                }
            }
        }
    }
    else{
        return;
    }
}




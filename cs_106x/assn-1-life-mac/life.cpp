/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>  // for cout
#include <fstream>
#include <string>
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "simpio.h"  // for getLine
#include "random.h"  // to choose the random colonies
#include "grid.h"
#include "gevents.h"

#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay


// Function Prototypes
static void waitForEnter(string message);
static void welcome();
static void choosePattern(LifeDisplay & display, Grid<int> & displayGrid);
static int chooseSpeed();
static void createGrid(Grid<int> & displayGrid);
static void createGrid(ifstream & infile, LifeDisplay & display, Grid<int> & displayGrid);
static void placeFileCells(Grid<int> & displayGrid, ifstream & infile);
static void checkForSpeedError(int speed);
static void runSimulation(LifeDisplay & display, Grid<int> & displayGrid, int speedChoice);
static void advanceDisplay(LifeDisplay & display, Grid<int> & displayGrid, int speedChoice);
static void determinePauseTime(int speedChoice);
static bool replay();
static bool yes(string response);

static void evaluateLife(Grid<int> & displayGrid, Grid<int> & newGeneration, int row, int col);
static void updateGeneration(LifeDisplay & display, Grid<int> & displayGrid, Grid<int> & newGeneration);
static bool stablePattern(Grid<int> & displayGrid, Grid<int> & newGeneration);
static void checkSurroundings(Grid<int> & displayGrid, int & surroundingCells, int row, int col);



// Constants for the program.
const int N_STANDARD_ROWS = 40;
const int N_STANDARD_COLS = 70;
const int ENTER_BUTTON = 4;


int main() {
    while(true){
        LifeDisplay display;
        display.setTitle("Game of Life");
        display.setDimensions(N_STANDARD_ROWS, N_STANDARD_COLS);
        welcome();
        
        Grid<int> displayGrid(N_STANDARD_ROWS, N_STANDARD_COLS);
        choosePattern(display, displayGrid);
        updateGeneration(display, displayGrid, displayGrid); // This call updates the display. displayGrid is
            // passed twice because this function requires two Grids and sets the first equal to the second.
            // This allows nothing to actually be changed.
        
        runSimulation(display, displayGrid, chooseSpeed());
        if(!replay()){
            break;
        }
    }
    return 0;
}


/*
 * The welcome method explains the rules to the player and waits for [enter] to continue.
 */
static void welcome() {
	cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
	cout << "Cells live and die by the following rules:" << endl << endl;
	cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
	cout << "\tLocations with 2 neighbors remain stable" << endl;
	cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
	cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
	cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    waitForEnter("Hit [enter] to continue....   ");
}


/*
 * This method lets the program continue when [enter] is pushed.
 */
static void waitForEnter(string message) {
    cout << message;
    (void) getLine();
}


/*
 * This method allows the user to press enter with no prompts (between generations)
 */
static void waitForEnter(){
    (void) getLine();
}


/*
 * This method lets the user choose whether they want to import a file 
 * for the colonies or let the computer do it at random.
 * It takes in the display so it can be passed to the correct method and then altered.
 */
static void choosePattern(LifeDisplay & display, Grid<int> & displayGrid){
    while(true){
        string filename;
        cout << "You can either open a file or create the colonies at random." << endl;
        cout << "Please enter a file name or press [enter] for a random one: ";
        
        if(cin.get() == '\n'){
            createGrid(displayGrid);
            return;
        } else{
            cin.unget();
        }
        
        getline(cin, filename);
        ifstream infile;
        filename = "files/" + filename;
        infile.open(filename.c_str());
        
        if(!infile.fail()){
            createGrid(infile, display, displayGrid);
            return;
        }
        
        cout << "That is not a correct file name. Please try again." << endl;
        cout << endl;
    }
}


/*
 * This method allows the user to choose the speed at which the sequence will run.
 */
static int chooseSpeed(){
    int speed = -1;
    while(speed < 1 || speed > 4){
        cout << endl;
        cout << "Choose the desired speed for the process:" << endl;
        cout << "1. Ludicrous speed! Not ludicrous speed!" << endl;
        cout << "2. I wanna go fast!" << endl;
        cout << "3. Not too fast please!" << endl;
        cout << "4. Press enter to advance through each stage." << endl;
        
        speed = getInteger("-");
        cout << endl;
        checkForSpeedError(speed);
    }
    return speed;
}


/*
 * This method checks the user's speed choice
 */
static void checkForSpeedError(int speed){
    if(speed < 1 || speed > 4){
        cout << "That is not a valid speed." << endl;
        cout << "Please try again." << endl;
    }
}


/*
 * This method interprets a file specified by the user and alters the display accordingly.
 * It takes in the display so it can alter it and takes in the ifstream so 
 * the file can be interpreted.
 */
static void createGrid(ifstream & infile, LifeDisplay & display, Grid<int> & displayGrid){
    string currentLine;
    int nRows, nCols;
    while(true){ // This while loop disregards the comments at the top of each file
        getline(infile, currentLine);
        if(currentLine.at(0) != '#'){
            nRows = stringToInteger(currentLine); // The first line that is not a comment is always the number of rows in the display
            break;
        }
    }
    
    getline(infile, currentLine);
    nCols = stringToInteger(currentLine);
    
    displayGrid.resize(nRows, nCols);
    display.setDimensions(nRows, nCols);
    
    placeFileCells(displayGrid, infile);
}


/*
 * This method creates the colonies at random.
 */
static void createGrid(Grid<int> & displayGrid){
    for(int row = 0; row < N_STANDARD_ROWS; row++){
        for(int col = 0; col < N_STANDARD_COLS; col++){
            int age = 0;
            if(randomChance(0.5)){
                age = randomInteger(1,kMaxAge);
            }
            displayGrid.set(row, col, age);
        }
    }
}


/*
 * This method uses a text file to put the cells into the display at the specified positions.
 */
static void placeFileCells(Grid<int> & displayGrid, ifstream & infile){
    string currentLine;
    for(int i = 0; i < displayGrid.numRows(); i++){
        getline(infile, currentLine);
        for(int j = 0; j < displayGrid.numCols(); j++){
            if(currentLine.at(j) == 'X'){
                displayGrid.set(i , j, 1);
            } else{
                displayGrid.set(i, j, 0);
            }
        }
    }
}

/*
 * This method constantly checks for mouse clicks to end the current pattern while it updates the display.
 */
void runSimulation(LifeDisplay & display, Grid<int> & displayGrid, int speedChoice) {
    while (true) {
        GMouseEvent me;
        if (getNextEvent(me)) {
            if (me.getEventType() == MOUSE_CLICKED) return;
        } else {
            advanceDisplay(display, displayGrid, speedChoice);
        }
    }
}


/*
 * This method advances the display one frame.
 */
static void advanceDisplay(LifeDisplay & display, Grid<int> & displayGrid, int speedChoice){
    determinePauseTime(speedChoice);
    Grid<int> newGeneration;
    newGeneration.resize(displayGrid.numRows(), displayGrid.numCols()); // This makes sure the entire Grid is cleared.
    
    for(int row = 0; row < displayGrid.numRows(); row++) {
        for(int col = 0; col < displayGrid.numCols(); col++) {
            evaluateLife(displayGrid, newGeneration, row, col);
        }
    }
    
    if(stablePattern(displayGrid, newGeneration)){
        return;
    }
    updateGeneration(display, displayGrid, newGeneration);
}


/*
 * This method changes the user's speed choice into an actual pause time.
 */
static void determinePauseTime(int speedChoice){
    switch(speedChoice){
        case 1: pause(50);
            break;
        case 2: pause(500);
            break;
        case 3: pause(1000);
            break;
        case 4: waitForEnter();
            break;
    }
    return;
}


/*
 * This function prompts the user to use another pattern after the user has stopped the cycle or it has become stable.
 */
static bool replay(){
    string response;
    cout << "Would you like to try another pattern? (Yes or No) ";
    cin >> response;
    waitForEnter(); // This makes sure the enter is not registered as an answer to the question of the new pattern.
    return yes(response);
}


/*
 * This function determines if the first letter in the response is a 'Y' or 'y'. If not, it assumes the user wants to quit.
 */
static bool yes(string response){
    if(response.at(0) == 'y' || response.at(0) == 'Y'){
        return true;
    }
    return false;
}


/*
 * This function takes a row and column and checks the Grid to see how many cells are around it and whether
 * it should be alive for the next generation.
 */
static void evaluateLife(Grid<int> & displayGrid, Grid<int> & newGeneration, int row, int col) {
    int surroundingCells = 0;
    checkSurroundings(displayGrid, surroundingCells, row, col);
    
    switch(surroundingCells){
        case 2:
            if(displayGrid[row][col] > 0){
                newGeneration[row][col] = displayGrid[row][col] + 1; // This if statement adds a year to all cells that have
                                                                     // two neighbors and are currently alive.
            }
            break;
        case 3:
            newGeneration[row][col] = displayGrid[row][col] + 1; // This command will adds a new cell that should be created
                                                                 // or adds one to the age if it is already alive.
            break;
        default:
            newGeneration[row][col] = 0;
            break;
    }
    return;
}


/*
 * This function checks the eight positions around a cell position to count how many live cells surround it.
 */
static void checkSurroundings(Grid<int> & displayGrid, int & surroundingCells, int row, int col){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(displayGrid.inBounds(row + i, col + j)){
                if(displayGrid[row + i][col + j] > 0){
                    surroundingCells++;
                }
            }
        }
    }
    if(displayGrid[row][col] > 0){
        surroundingCells--;
    }
    return;
}


/*
 * This function copies the newGeneration into the current display Grid and then updates the graphics.
 */
static void updateGeneration(LifeDisplay & display, Grid<int> & displayGrid, Grid<int> & newGeneration){
    for(int row = 0; row < newGeneration.numRows(); row++){
        for(int col = 0; col < newGeneration.numCols(); col++){
            display.drawCellAt(row, col, newGeneration[row][col]); // Draws the cells at each position
            displayGrid[row][col] = newGeneration[row][col]; // Sets the displayGrid equal to
                                                             // newGeneration to get ready for the next iteration.
        }
    }
    return;
}


/*
 * This method checks the two Grids to see if a stable state has been reached. A stable state is when
 * there are no changes from one generation to the next.
 */
static bool stablePattern(Grid<int> & displayGrid, Grid<int> & newGeneration){
    for(int row = 0; row < displayGrid.numRows(); row++) {
        for(int col = 0; col < displayGrid.numCols(); col++) {
            if(displayGrid[row][col] != newGeneration[row][col]){
                return false;
            }
        }
    }
    return true;
}



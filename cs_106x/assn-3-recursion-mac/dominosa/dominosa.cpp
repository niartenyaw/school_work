/**
 * File: dominosa.cpp
 * ------------------
 * This animates the brute-force discovery of a solution
 * to a 2 x n dominosa board.
 */

#include <iostream>
#include <cmath>
using namespace std;

#include "simpio.h"
#include "grid.h"
#include "random.h"
#include "dominosa-graphics.h"
#include "set.h"
#include "vector.h"


static void welcome();
static int getIntegerInRange(string prompt, int low, int high);
static void populateBoard(Grid<int>& board, int low, int high);
static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board);
static bool checkPairings(DominosaDisplay& display, Grid<int>& board, Vector< Set<int> >& groups, coord xy);
static bool hasBeenUsed(Vector< Set<int> >& groups, Set<int> check);
static bool tryHorizontal(DominosaDisplay& display, Grid<int>& board, Vector< Set<int> >& groups, coord xy);


int main() {
	DominosaDisplay display;
	welcome();
	while (true) {
		int numColumns = getIntegerInRange("How many columns? [0 to exit]: ", 9, 25);
		if (numColumns == 0) break;
		Grid<int> board(2, numColumns);
		populateBoard(board, 1, ceil(2 * sqrt(numColumns)));
		display.drawBoard(board);
		if (canSolveBoard(display, board)) {
			cout << "The board can be solved, and one such solution is drawn above." << endl;
		} else {
			cout << "This board you see can't be solved." << endl;
		}
	}
	
	cout << "Okay, thanks for watching, and come back soon." << endl;
    cout << "Click the mouse anywhere in the window to exit." << endl;
	return 0;
}


static void welcome() {
	cout << "Here we'll illustrate the use of recursive backtracking to" << endl;
	cout << "discover a solution to various 2 x n Dominosa boards.  In some" << endl;
	cout << "cases there won't be any solutions, and in the cases where there are" << endl;
	cout << "multiple solutions, we'll just find one of them." << endl;
	cout << endl;
}


static int getIntegerInRange(string prompt, int low, int high) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0 || (response >= low && response <= high)) return response;
		cout << "Sorry, but I can't use that number." << endl;
	}
}


static void populateBoard(Grid<int>& board, int low, int high) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			board[row][col] = randomInteger(low, high);
		}
	}
}

/*
 * This is the wrapper function that starts the recursive call to checkPairings
 */
static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board) {
    Vector< Set<int> > groups;
    coord xy1 = {0, 0};
    if(checkPairings(display, board, groups, xy1)){
        return true;
    }
	return false;
}

/*
 * This is the recursive function. It determines if a vertical pair is possible. If not, it tries two horizontal pairs.
 */
static bool checkPairings(DominosaDisplay& display, Grid<int>& board, Vector< Set<int> >& groups, coord xy){
    if(xy.col > board.numCols() - 1){
        return true; // This means all numbers have been successfully added to groups.
    }
    
    Set<int> check;
    check.add(board.get(xy.row, xy.col));
    check.add(board.get(xy.row + 1, xy.col));
    coord two = {xy.row+1, xy.col};
    display.provisonallyPair(xy, two);
    if(!hasBeenUsed(groups, check)){ // Checks if next vertical set can be used
        groups.add(check);
        coord newXY = {xy.row, xy.col + 1};
        if(checkPairings(display, board, groups, newXY)){ // This calls for the next vertical pair in line to be analyzed
            display.certifyPairing(xy, two);
            return true;
        }
        else{ // This is invoked when the next vertical bar is not possible
            display.vetoProvisionalPairing(xy, two);
            display.eraseProvisionalPairing(xy, two);
            groups.remove(groups.size() - 1);
            if(tryHorizontal(display, board, groups, xy)){ // This checks for a horizontal bar in place of the vertical
                return true;
            }
        }
    }
    else{ // This is invoked when the vertical pair has been used. It automatically looks for two horizontal pairs.
        display.vetoProvisionalPairing(xy, two);
        display.eraseProvisionalPairing(xy, two);
        if(xy.col + 1 > board.numCols() - 1){ // This returns false when there is not enough room for a horizontal pairing
            return false;
        }
        else{ // This is invoked when there is room for horizontal pairing
            if(tryHorizontal(display, board, groups, xy)){
                return true;
            }
        }
    }
    return false;
}

/*
 * This function determines if the pair of numbers has already been used.
 */
static bool hasBeenUsed(Vector< Set<int> >& groups, Set<int> check){
    for(int i = 0; i < groups.size(); i++){
        if(groups[i] == check){
            return true;
        }
    }
    return false;
}

/*
 * This function looks for two horizontal pairs
 */
static bool tryHorizontal(DominosaDisplay& display, Grid<int>& board, Vector< Set<int> >& groups, coord xy){
    Set<int> horzOne;
    coord oneXY = {xy.row, xy.col + 1};
    horzOne.add(board.get(xy.row, xy.col));
    horzOne.add(board.get(oneXY.row, oneXY.col));
    
    coord twoXY1 = {xy.row + 1, xy.col};
    coord twoXY2 = {xy.row + 1, xy.col + 1};
    Set<int> horzTwo;
    horzTwo.add(board.get(twoXY1.row, twoXY1.col));
    horzTwo.add(board.get(twoXY2.row, twoXY2.col));
    
    display.provisonallyPair(xy, oneXY);
    display.provisonallyPair(twoXY1, twoXY2);
    if(!hasBeenUsed(groups, horzOne) && !hasBeenUsed(groups, horzTwo)){ // This makes sure the pairs have not been used already
        groups.add(horzOne);
        groups.add(horzTwo);
        coord newXY = {xy.row, xy.col + 2};
        if(checkPairings(display, board, groups, newXY)){ // This makes the call back to checkPairings to try a vertical pair next
            display.certifyPairing(xy, oneXY);
            display.certifyPairing(twoXY1, twoXY2);
            return true;
        }
        else{ // This is invoked if the call to checkPairings does not have a solution.
            display.vetoProvisionalPairing(xy, oneXY);
            display.vetoProvisionalPairing(twoXY1, twoXY2);
            display.eraseProvisionalPairing(xy, oneXY);
            display.eraseProvisionalPairing(twoXY1, twoXY2);
            
            groups.remove(groups.size() - 1);
            groups.remove(groups.size() - 1);
        }
    }
    else{ // This is invoked when one of the pairs has already been used.
        display.vetoProvisionalPairing(xy, oneXY);
        display.vetoProvisionalPairing(twoXY1, twoXY2);
        
        display.eraseProvisionalPairing(xy, oneXY);
        display.eraseProvisionalPairing(twoXY1, twoXY2);
        return false;
    }
    return false;
}
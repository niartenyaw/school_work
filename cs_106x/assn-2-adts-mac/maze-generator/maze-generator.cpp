/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "maze-graphics.h"
#include "gwindow.h"
#include "maze-types.h"
#include "random.h"
#include "grid.h"
#include "queue.h"
#include "set.h"
#include "vector.h"


static int getMazeDimension(string prompt, int minDimension = 7, int maxDimension = 50);
static void drawAllWalls(MazeGeneratorView & maze, int dimension);
static void removeRandomWalls(MazeGeneratorView & maze, int dimension);
static wall pickRandomWall(int dimension, Set<wall> & checked);
static bool sameSet(Vector< Set<cell> > & sets, wall toCheck);
static void secondCell(cell & one, cell & two, wall & random, int direction);
static bool alreadyChecked(wall random, Set<wall> & checked);
static bool replay();


int main()  {
	MazeGeneratorView maze;
    while (true) {
		int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ");
		if (dimension == 0) break;
        maze.setDimension(dimension);
        maze.drawBorder();
        drawAllWalls(maze, dimension);
        removeRandomWalls(maze, dimension);
        if(!replay()){
            break;
        }
	}
	return 0;
}

/*
 * This function gets the n*n dimensions of the maze.
 */
static int getMazeDimension(string prompt, int minDimension, int maxDimension) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
		cout << "Please enter a number between "
        << minDimension << " and "
        << maxDimension << ", inclusive." << endl;
	}
}

/*
 * This function draws all the walls in the starting maze so random walls can later be removed.
 */
static void drawAllWalls(MazeGeneratorView & maze, int dimension){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension - 1; j++){
            cell one, two;
            one.row = i;
            one.col = j;
            two.row = i;
            two.col = j + 1;
            wall drawn;
            drawn.one = one;
            drawn.two = two;
            maze.drawWall(drawn);
        }
    }
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension - 1; j++){
            cell one, two;
            one.row = j;
            one.col = i;
            two.row = j + 1;
            two.col = i;
            wall drawn;
            drawn.one = one;
            drawn.two = two;
            maze.drawWall(drawn);
        }
    }
}

/*
 * This function adds each cell to its own set and then randomly removes walls until all cells are
 * contained in the same set.
 */
static void removeRandomWalls(MazeGeneratorView & maze, int dimension){
    Vector< Set<cell> > sets;
    
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            cell one = {i, j};
            Set<cell> first;
            first += one;
            sets.add(first);
        }
    }
    
    Set<wall> checked;
    
    while(sets.size() > 1){
        wall toCheck = pickRandomWall(dimension, checked);
        if(!sameSet(sets, toCheck)){ // randomChance(0.5) && 
            maze.removeWall(toCheck);
        }
    }
}

/*
 * This function picks a random cell and then a random cell next to it. If the wall between them has not
 * been checked already than it returns it.
 */
static wall pickRandomWall(int dimension, Set<wall> & checked){
    wall random;
    while(true){
        cell one = {randomInteger(0, dimension - 1), randomInteger(0, dimension - 1)};
        cell two = {-1, -1};
        
        while(two.row < 0 || two.row > dimension - 1 || two.col < 0 || two.col > dimension - 1){
            int direction = randomInteger(0,3);
            secondCell(one, two, random, direction);
        }
        
        if(!alreadyChecked(random, checked)){
            checked.add(random);
            return random;
        }
    }
}

/*
 * This function chooses which cell around the random cell will complete the wall. The ordering of the cells
 * into the wall is: wall.one is either to the left or above wall.two. This allows the alreadyChecked() function
 * to search for the correct wall.
 */
static const int SOUTH = 0;
static const int NORTH = 1;
static const int EAST = 2;
static const int WEST = 3;
static void secondCell(cell & one, cell & two, wall & random, int direction){
    switch(direction){
        case SOUTH:
            two.row = one.row + 1;
            two.col = one.col;
            random.one = one;
            random.two = two;
            break;
        case NORTH:
            two.row = one.row - 1;
            two.col = one.col;
            random.one = two;
            random.two = one;
            break;
        case EAST:
            two.row = one.row;
            two.col = one.col + 1;
            random.one = one;
            random.two = two;
            break;
        case WEST:
            two.row = one.row;
            two.col = one.col - 1;
            random.one = two;
            random.two = one;
            break;
    }
}

/*
 * This function makes sure that the two cells being considered for the wall removal are not in the same set
 * which makes sure no loops are created.
 */
static bool sameSet(Vector< Set<cell> > & sets, wall toCheck){
    Set<cell> current;
    int one = -1;
    int two = -1;
    
    for(int i = 0; i < sets.size(); i++){
        current = sets.get(i);
        for(int j = 0; j < current.size(); j++){
        }
        if(current.contains(toCheck.one)){
            one = i;
        }
        if(current.contains(toCheck.two)){
            two = i;
        }
        if(current.contains(toCheck.one) && current.contains(toCheck.two)){
            return true;
        }
    }
    if(one >= 0 && two >= 0){
        sets[one] += sets[two];
        sets.remove(two);
    }
    if(one >= 0 && two < 0){
        sets[one].add(toCheck.two);
    }
    if(one < 0 && two >= 0){
        sets[two].add(toCheck.one);
    }
    return false;
}

/*
 * This method makes sure the wall being questioned for removal has not already been checked.
 */
static bool alreadyChecked(wall random, Set<wall> & checked){
    if(checked.contains(random)) return true;
    return false;
}

/*
 * This function asks the user after a maze is created if they would like to make another.
 */
static bool replay(){
    while(true){
        string response;
        cout << "Would you like to try another maze? ";
        cin >> response;
        (void) getLine();
        if(response == "yes" || response == "Yes"){
            return true;
        }
        else if(response == "no" || response == "No"){
            return false;
        }
        else{
            cout << "That is not a valid response" << endl;
        }
    }
}


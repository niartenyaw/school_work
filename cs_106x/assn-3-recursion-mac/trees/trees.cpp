/**
 * File: trees.cpp
 * ---------------
 * Draws a recursive tree as specified in the Assignment 3 handout.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" // required of all CS106 C++ programs
#include "gwindow.h" // for GWindow class and its setTitle, setColor, and drawPolarLine methods
#include "gtypes.h"  // for GPoint class
#include "random.h"  // for randomChance function
#include "math.h"

const static double kWindowWidth = 600;
const static double kWindowHeight = 600;
const static string kWindowTitle = "Recursive Trees";
const static double kTrunkLength  = kWindowHeight/4;
const static double kShrinkFactor = 0.70;
const static int kBranchAngleSeparation = 15;
const static int kTrunkStartAngle = 90;
const static string kLeafColor = "#2e8b57";
const static string kTrunkColor = "#8b7765";
const static double kBranchProbability = 1.0;


static void drawTree(GWindow& window, int order);
static void drawFractalTree(GWindow& window, GPoint point, double theta, int order, double length);


const static int kHighestOrder = 5;
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setWindowTitle(kWindowTitle);
    cout << "Repeatedly click the mouse in the graphics window to draw " << endl;
    cout << "recursive trees of higher and higher order." << endl;
    for (int order = 0; order <= kHighestOrder; order++) {
        waitForClick();
        window.clear();
        drawTree(window, order);
    }
    
    cout << endl;
    cout << "All trees through order " << kHighestOrder << " have been drawn." << endl;
    cout << "Click the mouse anywhere in the graphics window to quit." << endl;
    waitForClick();
    return 0;
}


static void drawTree(GWindow& window, int order) {
    GPoint trunkBase(window.getWidth()/2, window.getHeight());
    window.setColor(kTrunkColor);
    GPoint point = window.drawPolarLine(trunkBase, kTrunkLength, kTrunkStartAngle);
    double length = kTrunkLength;
    drawFractalTree(window, point, kTrunkStartAngle, order, length);
}


static void drawFractalTree(GWindow& window, GPoint point, double theta, int order, double length){
    if(order <= 0) return;
    
    window.setColor(order < 2 ? kLeafColor : kTrunkColor);
    
    length *= kShrinkFactor;
    
    GPoint p1 = window.drawPolarLine(point, length, theta - kBranchAngleSeparation * 3);
    drawFractalTree(window, p1, theta - kBranchAngleSeparation * 3, order - 1, length);
    
    GPoint p2 = window.drawPolarLine(point, length, theta - kBranchAngleSeparation * 2);
    drawFractalTree(window, p2, theta - kBranchAngleSeparation * 2, order - 1, length);
    
    GPoint p3 = window.drawPolarLine(point, length, theta - kBranchAngleSeparation);
    drawFractalTree(window, p3, theta - kBranchAngleSeparation, order - 1, length);
    
    GPoint p4 = window.drawPolarLine(point, length, theta);
    drawFractalTree(window, p4, theta, order - 1, length);
    
    GPoint p5 = window.drawPolarLine(point, length, theta + kBranchAngleSeparation);
    drawFractalTree(window, p5, theta + kBranchAngleSeparation, order - 1, length);
    
    GPoint p6 = window.drawPolarLine(point, length, theta + kBranchAngleSeparation * 2);
    drawFractalTree(window, p6, theta + kBranchAngleSeparation * 2, order - 1, length);
    
    GPoint p7 = window.drawPolarLine(point, length, theta + kBranchAngleSeparation * 3);
    drawFractalTree(window, p7, theta + kBranchAngleSeparation * 3, order - 1, length);
    
}




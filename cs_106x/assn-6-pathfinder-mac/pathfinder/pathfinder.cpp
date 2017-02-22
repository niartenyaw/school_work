/**
 * File: pathfinder.cpp
 * --------------------
 * This is the primary file where you'll place most of your code.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "pathfinder-graph.h"
#include "pathfinder-graphics.h"
#include "error.h"
#include "gwindow.h"
#include "map.h"
#include "pqueue.h"
#include "point.h"
#include "tokenscanner.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "path.h"
using namespace std;

struct All{
    SimpleGraph graph;
    GWindow gw;
    //Map<GPoint, Node *> points;
    Node *start;
    string filename;
};

const int kDARK = 0;
const int kDIM = 1;


static void giveInstructions();
static void quitAction(All& all);
static void getMap(All& all);
static void readInFile(ifstream& infile, All& all);
static void displayMap(SimpleGraph& graph, int i);
static void dijkstra(All& all);
static void kruskal(All& all);
static bool checkSets(Vector< Set<Node*> >& sets, Arc *arc);
static void clearAction(All& all);


/**
 * Function: main
 * --------------
 * Defines the entry point for the entire application.
 */
int main() {
    GWindow gw(kWindowWidth, kWindowHeight + kControlStripHeight);
    initPathfinderGraphics(gw);
    giveInstructions();
    All all;
    
    SimpleGraph graph;
    addButton("Map", getMap, all);
    addButton("Dijkstra", dijkstra, all);
    addButton("Kruskal", kruskal, all);
    addButton("Clear", clearAction, all);
    addButton("Quit", quitAction, all);
    pathfinderEventLoop();
    return 0;
}

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Describes the Pathfinder assignment on the console.  This text has
 * been retained in its original form to preserve the assignment history.
 */
static void giveInstructions() {
    cout << "This masterful piece of work is a graph extravaganza!" << endl;
    cout << "The main attractions include a lovely visual presentation" << endl;
    cout << "of the graph along with an implementation of Dijkstra's" << endl;
    cout << "shortest path algorithm and Kruskal's computation of" << endl;
    cout << "a minimal spanning tree.  Enjoy!" << endl << endl;
}

/**
 * Function: quitAction
 * Usage: quitAction(g);
 * ---------------------
 * Called when the user clicks the Quit button in the control strip.
 */
static void quitAction(All& all) {
    foreach(Node *node in all.graph.nodes) delete node;
    foreach(Arc *arc in all.graph.arcs) delete arc;
    exitGraphics();
}

static void getMap(All& all){
    // Deletes all current nodes and arcs before the new file is read in.
    foreach(Node *node in all.graph.nodes) delete node;
    foreach(Arc *arc in all.graph.arcs) delete arc;
    all.gw.clear();
    
    cout << "Please enter the name of the map you would like to use: ";
    string filename;
    ifstream infile;
    while(true){
        getline(cin, filename);
        filename = "data-files/" + filename + ".txt";
        infile.open(filename.c_str());
        if(!infile.fail()) break;
        cout << "That is not a valid map. Please try another. ";
    }
    
    readInFile(infile, all);
    displayMap(all.graph, kDARK);
}

static void readInFile(ifstream& infile, All& all){
    string line;
    getline(infile, line);
    all.filename = line;
    drawPathfinderMap(line);
    getline(infile, line); // Line that says "NODES"
    while(true){ // Adds all Nodes to the SimpleMap
        getline(infile, line);
        if(line == "ARCS") break;
        
        Node *node = new Node;
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        node->name = scanner.nextToken(); //First token is always the name.
        
        int x = stringToInteger(scanner.nextToken()); // Second token is the X coord.
        int y = stringToInteger(scanner.nextToken()); // Third token is the Y coord.
        GPoint pt(x, y);
        node->loc = pt;
        
        all.graph.nodes.add(node);
        all.graph.nodeMap[node->name] = node;
        all.start = node; // The start node will be the last node entered. Just makes sure it is assigned to something.
    }
    while(true){ //Adds all Arcs to SimpleMap and arcs to each node
        getline(infile, line);
        if(infile.fail()) break;
        
        TokenScanner scanner(line);
        scanner.ignoreWhitespace();
        
        string first = scanner.nextToken(); // First token is the first node name
        Node *node1 = all.graph.nodeMap.get(first);
        string second = scanner.nextToken(); // Next token in the second node name
        Node *node2 = all.graph.nodeMap.get(second);
        
        double cost = (double) stringToInteger(scanner.nextToken()); // Next token is the cost of the arc
        
        Arc *arc = new Arc;
        arc->cost = cost;
        Arc *arc2 = new Arc;
        arc2->cost = cost;
        
        //For node1->node2
        arc->start = node1;
        arc->finish = node2;
        all.graph.arcs.add(arc);
        node1->arcs.add(arc);
        
        //For node2->node1
        arc2->start = node2;
        arc2->finish = node1;
        all.graph.arcs.add(arc2);
        node2->arcs.add(arc2);
    }
}

static void displayMap(SimpleGraph& graph, int i){
    if(i == kDARK){
        foreach(Arc *arc in graph.arcs){
            drawPathfinderArc(arc->start->loc, arc->finish->loc, kArcColor);
        }
        foreach(Node *node in graph.nodes){
            drawPathfinderNode(node->loc, kNodeColor, node->name);
        }
    }
    if(i == kDIM){
        foreach(Arc *arc in graph.arcs){
            drawPathfinderArc(arc->start->loc, arc->finish->loc, kDimColor);
        }
        foreach(Node *node in graph.nodes){
            drawPathfinderNode(node->loc, kDimColor, node->name);
        }
    }
    
}

static void dijkstra(All& all){
    all.gw.clear();
    drawPathfinderMap(all.filename);
    displayMap(all.graph, kDARK);
    
    // Couldn't figure out the clicking so I did it by text.
    cout << "Please type where you want to start. ";
    string beginning;
    getline(cin, beginning);
    while(!all.graph.nodeMap.containsKey(beginning)){
        cout << "That is not a valid start position on this map." << endl;
        cout << "Please try another: ";
        getline(cin, beginning);
    }
    
    cout << "Now type your destination.";
    string end;
    getline(cin, end);
    while(!all.graph.nodeMap.containsKey(end)){
        cout << "That is not a valid destination on this map." << endl;
        cout << "Please try another: ";
        getline(cin, end);
    }
    
    Node *start = all.graph.nodeMap.get(beginning);
    Node *finish = all.graph.nodeMap.get(end);
    
    Path path;
    PriorityQueue<Path> queue;
    Set<string> discovered;
    while(start != finish){
        if(!discovered.contains(start->name)){
            discovered.add(start->name);
            for(Arc *arc : start->arcs){
                if(!discovered.contains(arc->finish->name)){
                    Path path1 = path;
                    path1.addArc(arc);
                    queue.enqueue(path1, path1.getCost());
                }
            }
        }
        if(queue.isEmpty()){
            cout << "That is not a possible route." << endl;
            return;
        }
        path = queue.dequeue();
        start = path.getLastNode();
    }
    cout << path.toString() << endl;
    all.gw.clear();
    drawPathfinderMap(all.filename);
    displayMap(all.graph, kDIM);
    Vector<Arc *> arcs = path.getArcs();
    foreach(Arc *arc in arcs){
        drawPathfinderNode(arc->start->loc, kHighlightColor);
        drawPathfinderArc(arc->start->loc, arc->finish->loc, kHighlightColor);
        drawPathfinderNode(arc->finish->loc, kHighlightColor);
    }
}

static void kruskal(All & all){
    Vector< Set<Node *> > sets;
    PriorityQueue<Arc *> queue;
    Set<Arc *> solution;
    // Adds each Node * to its own Set.
    foreach(Node *node in all.graph.nodes){
        Set<Node *> nodes;
        nodes.add(node);
        sets.add(nodes);
    }
    
    foreach(Arc *arc in all.graph.arcs){ // Lets arcs come out smallest to largest
        queue.enqueue(arc, arc->cost);
    }
    
    while(sets.size() > 1){
        Arc *curr = queue.dequeue();
        if(checkSets(sets, curr)){
            solution += curr;
        }
    }
    
    Set<Node *> final = sets.get(0);
    all.gw.clear();
    drawPathfinderMap(all.filename);
    foreach(Arc *arc in solution){
        drawPathfinderArc(arc->start->loc, arc->finish->loc, kHighlightColor);
        drawPathfinderNode(arc->start->loc, kHighlightColor, arc->start->name);
        drawPathfinderNode(arc->finish->loc, kHighlightColor, arc->finish->name);
    }
}

static bool checkSets(Vector< Set<Node*> >& sets, Arc *arc){
    Set<Node *> curr;
    int one = -1;
    int two = -1;
    
    for(int i = 0; i < sets.size(); i++){
        curr = sets.get(i);
        if(curr.contains(arc->start)){
            one = i;
        }
        if(curr.contains(arc->finish)){
            two = i;
        }
        if(curr.contains(arc->start) && curr.contains(arc->finish)){
            return false;
        }
    }
    
    if(one == two) return false;
    
    sets[one] += sets[two];
    sets.remove(two);
    return true;
}

static void clearAction(All& all){
    all.gw.clear();
    all.graph.nodeMap.clear();
    foreach(Node *node in all.graph.nodes) delete node;
    foreach(Arc *arc in all.graph.arcs) delete arc;
}

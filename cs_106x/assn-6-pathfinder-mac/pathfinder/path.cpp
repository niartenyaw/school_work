/**
 * File: path.cpp
 * --------------
 * This file implements the Path class.
 */

#include "path.h"
using namespace std;

Path::Path(){
    cost = 0;
}

Path::~Path(){}

string Path::toString(){
    string returner = "";
    returner +=arcs[0]->start->name;
    for(int i = 0; i < arcs.size(); i++){
        returner += " -> " + arcs[i]->finish->name;
    }
    return returner;
}

void Path::addArc(Arc *arc){
    arcs.add(arc);
    cost += arc->cost;
}

Node * Path::getLastNode(){
    Arc *arc = arcs[arcs.size() - 1];
    return arc->finish;
}
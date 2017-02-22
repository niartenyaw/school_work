/*
 * File: path.h
 * ------------
 * This file is the interface for a Path class, which consists of a
 * sequence of arcs.
 */

#ifndef _path_h
#define _path_h

#include "vector.h"
#include "graphtypes.h"


class Path{
public:
    Path();
    ~Path();
    double getCost(){return cost;}
    std::string toString();
    void addArc(Arc *arc);
    Node * getLastNode();
    int numArcs(){return arcs.size();}
    Vector<Arc *> getArcs(){return arcs;}
    
private:
    Vector<Arc *> arcs;
    double cost;
};

#endif

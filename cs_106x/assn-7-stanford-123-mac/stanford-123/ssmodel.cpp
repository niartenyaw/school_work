/**
 * File: ssmodel.cpp
 * ------------------
 * This file will contain the implementation of the SSModel class (once you
 * have finished it!
 */
 
#include "ssmodel.h"
#include "exp.h"
#include "parser.h"

SSModel::SSModel(int nRows, int nCols, SSView *view, SimpleGraph *graph) {
    this->nRows = nRows;
    this->nCols = nCols;
    this->view = view;
    this->graph = graph;
}

SSModel::~SSModel() {
    foreach(Node * node in graph->nodes){
        delete node;
    }
    foreach(Arc *arc in graph->arcs){
        delete arc;
    }
    delete graph;
    delete view;
}

bool SSModel::nameIsValid(string& cellname) {
    cellname = toUpperCase(cellname);
    char col = cellname[0];
    int difference = (int) toupper(col) - 'A';
    if(difference >= nCols || difference < 0) return false;
    int row = stringToInteger(cellname.substr(1));
    if(row > nRows) return false;
    return true;
}

void SSModel::setCellFromScanner(const string& cellname, TokenScanner& scanner) {
    Node *node;
    Node *temp = new Node; // To store previously contained info in case a problem occurs
    bool newNode = false;
    if(graph->nodeMap.containsKey(cellname)){
        node = graph->nodeMap.get(cellname);
        
        temp->name = node->name;
        temp->affected = node->affected;
        temp->exp = node->exp;
    }
    else{
        node = new Node;
        newNode = true;
        graph->nodes.add(node);
    }
    
    node->name = cellname;
    Expression *exp = parseExp(scanner, graph, node);
    if(exp->getType() == NULLEXP){ // Makes sure the equation is valid
        cout << "That is not a valid equation." << endl;
        cout << "One or more cell names have not been created yet." << endl;
        delete temp;
        if(newNode){
            delete node;
        }
        return;
    }
    node->exp = exp;
    node->value = exp->eval(context);
    context.setValue(node->name, node->value);
    
    graph->nodeMap[cellname] = node;
    bool display = true;
    foreach(Arc *arc in node->affected){
        if(!noLoops(arc->dependent, node)){
            display = false;
        }
    }
    if(display){
        displayNode(node);
    }
    else{
        cout << "That will make a loop and is not allowed." << endl;
    }
}

bool SSModel::noLoops(Node *n, Node *original){
    if(n == original) return false;
    bool display = true;
    foreach(Arc *arc in n->affected){
        if(!noLoops(arc->dependent, original)){
            display = false;
        }
    }
    if(display){
        displayNode(n);
    }
    return display;
}

void SSModel::displayNode(Node *node){
    Expression *exp = node->exp;
    if(exp->getType() == DOUBLE){
        double num = node->exp->eval(context);
        node->value = num;
        context.setValue(node->name, node->exp->eval(context));
        view->displayCell(node->name, realToString(num));
    }
    if(exp->getType() == COMPOUND){
        double num = node->exp->eval(context);
        node->value = num;
        context.setValue(node->name, node->exp->eval(context));
        view->displayCell(node->name, realToString(num));
    }
    if(exp->getType() == IDENTIFIER){
        double num = node->exp->eval(context);
        node->value = num;
        context.setValue(node->name, node->exp->eval(context));
        view->displayCell(node->name, realToString(num));
    }
    if(exp->getType() == TEXTSTRING){
        view->displayCell(node->name, node->exp->toString());
    }
    if(exp->getType() == RANGE){
        double num = node->exp->eval(context);
        node->value = num;
        context.setValue(node->name, node->exp->eval(context));
        view->displayCell(node->name, realToString(num));
    }
}


void SSModel::printCellInformation(const string& cellname) const {
    Node *node = graph->nodeMap.get(cellname);
    cout << cellname << ": " << node->exp->toString() << endl;
}

void SSModel::writeToStream(ostream& outfile) const {
    foreach(Node *node in graph->nodes){
        outfile << node->name << " = " << node->exp->toString() << endl;
    }
}

void SSModel::readFromStream(istream& infile) {
    while(true){
        string line;
        getline(infile, line);
        if(infile.fail() || line == "") return;
        TokenScanner scanner;
        scanner.ignoreWhitespace();
        scanner.scanNumbers();
        scanner.scanStrings();
        
        scanner.setInput(line);
        string cellname = scanner.nextToken();
        cout << scanner.nextToken() << endl;
        setCellFromScanner(cellname, scanner);
    }
}



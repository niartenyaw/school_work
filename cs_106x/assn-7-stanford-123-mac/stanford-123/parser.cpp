/*
 * File: parser.cpp
 * ----------------
 * This file implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

static Expression *readE(TokenScanner& scanner, SimpleGraph *graph, Node *node, int prec = 0);
static Expression *readT(TokenScanner& scanner, SimpleGraph *graph, Node *node);
static int precedence(const std::string& token);
bool isFunction(string possible);

/**
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner& scanner, SimpleGraph *graph, Node *node) {
   Expression *exp = readE(scanner, graph, node);
   if (scanner.hasMoreTokens()) {
      error("Unexpected token \"" + scanner.nextToken() + "\"");
   }
   return exp;
}

/**
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * The implementation of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each level, the parser reads operators and subexpressions
 * until it finds an operator whose precedence is greater than the prevailing
 * one.  When a higher-precedence operator is found, readE calls itself
 * recursively to read that subexpression as a unit.
 */

Expression *readE(TokenScanner& scanner, SimpleGraph *graph, Node *node, int prec) {
   Expression *exp = readT(scanner, graph, node);
   string token;
   while (true) {
      token = scanner.nextToken();
      int tprec = precedence(token);
      if (tprec <= prec) break;
      Expression *rhs = readE(scanner, graph, node, tprec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/**
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */
Expression *readT(TokenScanner& scanner, SimpleGraph *graph, Node *node) {
    string token = scanner.nextToken();
    token = toUpperCase(token);
    if(token == node->name) return new NullExp();
    TokenType type = scanner.getTokenType(token);
    if (type == WORD){
        if(isFunction(token)){
            scanner.nextToken();
            string startCell = scanner.nextToken();
            scanner.nextToken();
            string endCell = scanner.nextToken();
            scanner.nextToken();
            return new RangeExp(token, startCell, endCell);
        }
        if(graph->nodeMap.containsKey(token)){
            Node *n = graph->nodeMap.get(token);
            Arc *arc = new Arc;
            arc->dependee = n;
            arc->dependent = node;
            n->affected.add(arc);
            return new IdentifierExp(token);
        }
        return new NullExp();
    }
   if (type == NUMBER) return new DoubleExp(stringToReal(token));
   if (type == STRING) return new TextStringExp(token.substr(1, token.length() - 2));
   if (token != "(") error("Unexpected token \"" + token + "\"");
   Expression *exp = readE(scanner, graph, node, 0);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses");
   }
   return exp;
}

bool isFunction(string possible){
    possible = toUpperCase(possible);
    if(possible == "MEAN" || possible == "MIN" || possible == "MAX" || possible == "SUM" || possible == "PRODUCT" || possible == "AVERAGE" || possible == "MEDIAN" || possible == "STDDEV"){
        return true;
    }
    return false;
}

/**
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */
int precedence(const string& token) {
   if (token == "+" || token == "-") return 1;
   if (token == "*" || token == "/") return 2;
   return 0;
}

/**
 * File: exp.cpp
 * -------------
 * This file implements the exp.h interface.
 */

#include <string>
#include "exp.h"
#include "strlib.h"
#include "error.h"
#include "ssutil.h"
using namespace std;

/**
 * Implementation notes: Expression
 * --------------------------------
 * The Expression class itself implements only those methods that
 * are not designated as pure virtual.
 */

Expression::Expression() {
   /* Empty */
}

Expression::~Expression() {
   /* Empty */
}

/**
 * Implementation notes: DoubleExp
 * -------------------------------
 * The ConstantExp subclass represents a numeric constant.  The eval
 * method simply returns that value.
 */

DoubleExp::DoubleExp(double value) {
   this->value = value;
}

double DoubleExp::eval(EvaluationContext& context) const {
   return value;
}

string DoubleExp::toString() const {
   return realToString(value);
}

ExpressionType DoubleExp::getType() const {
   return DOUBLE;
}

double DoubleExp::getDoubleValue() const {
   return value;
}

/**
 * Implementation notes: TextStringExp
 * -----------------------------------
 * The IdentifierExp subclass represents a text string constant.  The
 * implementation of eval simply returns 0.0.
 */

TextStringExp::TextStringExp(const string& str) {
    this->str = str;
}

double TextStringExp::eval(EvaluationContext& context) const {
    return 0.0;
}

string TextStringExp::toString() const {
    return str;
}

ExpressionType TextStringExp::getType() const {
    return TEXTSTRING;
}

string TextStringExp::getTextStringValue() const {
    return '"' + str + '"';
}

/**
 * Implementation notes: IdentifierExp
 * -----------------------------------
 * The IdentifierExp subclass represents a variable name.  The
 * implementation of eval looks up that name in the evaluation context.
 */

IdentifierExp::IdentifierExp(const string& name) {
   this->name = name;
}

double IdentifierExp::eval(EvaluationContext& context) const {
   if (!context.isDefined(name)) error(name + " is undefined");
   return context.getValue(name);
}

string IdentifierExp::toString() const {
   return name;
}

ExpressionType IdentifierExp::getType() const {
   return IDENTIFIER;
}

string IdentifierExp::getIdentifierName() const {
   return name;
}

/**
 * Implementation notes: CompoundExp
 * ---------------------------------
 * The implementation of eval for CompoundExp evaluates the left and right
 * subexpressions recursively and then applies the operator.  Assignment is
 * treated as a special case because it does not evaluate the left operand.
 */

CompoundExp::CompoundExp(const string& op, const Expression *lhs, const Expression *rhs) {
   this->op = op;
   this->lhs = lhs;
   this->rhs = rhs;
}

CompoundExp::~CompoundExp() {
   delete lhs;
   delete rhs;
}

double CompoundExp::eval(EvaluationContext & context) const {
   double right = rhs->eval(context);
   double left = lhs->eval(context);
   if (op == "+") return left + right;
   if (op == "-") return left - right;  
   if (op == "*") return left * right;
   if (op == "/") return left / right; // divide by 0.0 gives ±INF
    
   error("Illegal operator in expression.");
   return 0.0;
}

string CompoundExp::toString() const {
   return '(' + lhs->toString() + ' ' + op + ' ' + rhs->toString() + ')';
}

ExpressionType CompoundExp::getType() const {
   return COMPOUND;
}

string CompoundExp::getOperator() const {
   return op;
}

const Expression *CompoundExp::getLHS() const {
   return lhs;
}

const Expression *CompoundExp::getRHS() const {
   return rhs;
}

// Return methods for NullExp.
NullExp::NullExp(){}
NullExp::~NullExp(){}
double NullExp::eval(EvaluationContext& context) const {
    return 0.0;
}
string NullExp::toString() const {
    return "";
}
ExpressionType NullExp::getType() const {
    return NULLEXP;
}

RangeExp::RangeExp(string operation, string startCell, string endCell){
    this->operation = operation;
    stringToLocation(startCell, cells.startCell);
    stringToLocation(endCell, cells.stopCell);
}
RangeExp::~RangeExp(){
    
}
double RangeExp::eval(EvaluationContext& context) const{
    Vector<double> values = getValues(context);
    if(operation == "MEAN") return average(values);
    if(operation == "AVERAGE") return average(values);
    if(operation == "SUM") return sum(values);
    if(operation == "PRODUCT") return product(values);
    if(operation == "MAX") return max(values);
    if(operation == "MIN") return min(values);
    if(operation == "MEDIAN") return median(values);
    if(operation == "STDDEV") return stdev(values);
    return 0.0;
}

string RangeExp::toString() const{
    string ret = operation + "(" + locationToString(cells.startCell) + ":" + locationToString(cells.stopCell) + ")";
    return ret;
}

ExpressionType RangeExp::getType() const{
    return RANGE;
}

Vector<double> RangeExp::getValues(EvaluationContext& context) const{
    Vector<double> values;
    char curr = locationToString(cells.startCell)[0];
    char last = locationToString(cells.stopCell)[0];
    int currRow = stringToInteger(locationToString(cells.startCell).substr(1));
    int temp = currRow;
    int lastRow = stringToInteger(locationToString(cells.stopCell).substr(1));
    if(curr > last || currRow > lastRow){
        cout << "Invalid range." << endl;
        return values;
    }
    while(curr <= last){
        while(currRow <= lastRow){
            string currCell = curr + integerToString(currRow);
            if(context.isDefined(currCell)){
                values.add(context.getValue(currCell));
            }
            currRow ++;
        }
        curr++;
        currRow = temp;
    }
    return values;
}




/**
 * Implementation notes: EvaluationContext
 * ---------------------------------------
 * The methods in the EvaluationContext class simply call the appropriate
 * method on the map used to represent the symbol table.
 */

void EvaluationContext::setValue(const string& var, double value) {
   symbolTable.put(var, value);
}

double EvaluationContext::getValue(const string& var) const {
   return symbolTable.get(var);
}

bool EvaluationContext::isDefined(const string& var) const {
   return symbolTable.containsKey(var);
}

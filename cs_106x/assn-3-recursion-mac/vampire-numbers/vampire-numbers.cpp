/**
 * File: vampire-numbers.cpp
 * -------------------------
 * Provides a program that repeatedly prompts the user for positive
 * numbers with an even number of digits and informs them
 * whether the number is a Vampire number or not.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" 
#include "simpio.h" // for getInteger
#include "strlib.h" // for stringToInteger, integerToString
#include "stack.h"


static int getPossibleVampireNumber();
static bool isVampireNumber(int number, int& first, int& second);
static bool makePossibleNumbers(string remainingNumbers, int number, Stack<char>& firstNumber, Stack<char>& secondNumber, string firstTemp, string secondTemp);
static void assignNumbers(Stack<char>& firstNumber, Stack<char>& secondNumber, int& first, int& second);


int main() {
    cout << "Here's a program that tells you whether or not a "
         << "number you enter is Vampire." << endl << endl;
    while (true) {
        int number = getPossibleVampireNumber();
        if (number == 0) break;
        int first = 0;
        int second = 0;
        if (isVampireNumber(number, first, second)) {
            cout << "Woo! " << number << " is a Vampire number, and "
                 << first << " and " << second << " are its fangs." << endl << endl;
        } else {
            cout << "Nope! The number " << number << " isn't Vampire." << endl << endl;
        }
    }
    cout << endl;
    cout << "All done!" << endl;
    return 0;
}


static int getPossibleVampireNumber() {
    while (true) {
        int response = getInteger("Enter a positive integer [or 0 to quit]: ");
        if (response >= 0) return response;
        cout << "Ah, sorry.  I need a nonnegative response.  Try again... " << endl;
    }
}

/*
 * This is the wrapper function that makes the call to makePossibleNumbers for recursion.
 */
static bool isVampireNumber(int number, int& first, int& second) {
    string remainingNumbers = integerToString(number);
    string firstTemp = "0";
    string secondTemp = "0";
    
    Stack<char> firstNumber;
    Stack<char> secondNumber;
    
    if(makePossibleNumbers(remainingNumbers, number, firstNumber, secondNumber, firstTemp, secondTemp)){
        assignNumbers(firstNumber, secondNumber, first, second);
        return true;
    }
    return false;
}

/*
 * This function uses recursion to find all possible rearrangements of the number and sees if their product is equal to the number
 */
static bool makePossibleNumbers(string remainingNumbers, int number, Stack<char>& firstNumber, Stack<char>& secondNumber, string firstTemp, string secondTemp){
    if(remainingNumbers.length() == 0){ // Checks for all the numbers to be placed
        int one = stringToInteger(firstTemp);
        int two = stringToInteger(secondTemp);
        
        return one * two == number;
    }
    
    string num = integerToString(number);
    int numberLength = num.length();
    
    for(int i = 0; i < remainingNumbers.length(); i++){ // loop over all possible numbers each time the next number is to be added
        char character = remainingNumbers[i];
        string newFirst = firstTemp + character;
        string newSecond = secondTemp + character;
        
        string newRemaining = remainingNumbers;
        newRemaining.erase(i,1);
        
        if(firstTemp.length() <= numberLength / 2 && makePossibleNumbers(newRemaining, number, firstNumber, secondNumber, newFirst, secondTemp)){ // Makes sure the length is not more than the number length / 2
            firstNumber.push(character);
            return true;
        }
        else if(secondTemp.length() <= numberLength / 2 && makePossibleNumbers(newRemaining, number, firstNumber, secondNumber, firstTemp, newSecond)){
            secondNumber.push(character);
            return true;
        }
    }
    return false;
}

/*
 * This function takes the two stacks and assigns first and second to their contents.
 */
static void assignNumbers(Stack<char>& firstNumber, Stack<char>& secondNumber, int& first, int& second){
    string one = "";
    string two = "";
    while(!firstNumber.isEmpty()){
        one += firstNumber.pop();
    }
    while(!secondNumber.isEmpty()){
        two += secondNumber.pop();
    }
    first = stringToInteger(one);
    second = stringToInteger(two);
}


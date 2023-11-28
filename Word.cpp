#include "Word.h"
#include <iostream>
#include <iomanip> 

using namespace std;

// Define default constructor
Word::Word() {
    cout << "Default Word constructor called\n";
    this->answer = "undefined";
}

// Define parameterized constructor
Word::Word(string answer) {
    cout << "Default Word constructor called\n";
    this->answer = answer;
}
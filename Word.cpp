#include "Word.h"
#include <iostream>
#include <iomanip> 

using namespace std;

// Define default constructor
Word::Word() {
    cout << "???Default Word constructor called????\n";
    this->answer = "undefined";
}

// Define parameterized constructor
Word::Word(string answer) {
    this->answer = answer;
}

Word::LetterMap map[3] = {
    {"incorrect", '-'}, // grey char(250)
    {"partial",   '+'}, // yellow char(176)
    {"correct",   '#'}  // green char(178)
};

void Word::RequestGuess() {
    cout << "Your guess: ";
    cin >> newGuess;

    ProcessGuess(newGuess);
}

void Word::ProcessGuess(string newGuess) {
    string newGuessLayout, newGuessMap;

    for (int i = 0; i < newGuess.size(); i++) {
        newGuessLayout += toupper(newGuess.at(i));

        int checker = 0;
        for (int j = 0; j < answer.size(); j++) {
            if ((tolower(newGuess.at(i)) == answer.at(j)) && (i == j)) {
                checker = 2;
                continue;
            }
            else if ((tolower(newGuess.at(i)) == answer.at(j)) && (i != j)) {
                checker = 1;
            }
        }
        newGuessMap += map[checker].mapValue;
    }


    // Add the guess to the vector
    // guessList.push_back({newGuess, newGuessLayout, newGuessMap});

    cout << "guessLayout: \t" << newGuessLayout << "\nguessMap: \t" << newGuessMap;

}
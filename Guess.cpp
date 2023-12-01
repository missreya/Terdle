#include "Guess.h"
#include <vector>
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <algorithm>

using namespace std;

Guess::LetterMap map[3] = {
    {"incorrect", '_'}, // grey char(250)
    {"partial",   '+'}, // yellow char(176)
    {"correct",   '#'}  // green char(178)
};

string Guess::RequestGuess(const vector<string> &legalWords) {
    string newGuess;
    cout << "Your guess: ";
    cin >> newGuess;
    bool validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());

    // Validate that the guess is 5 letters long and is a valid word
    while((!validWord)) {
        cout << "Guess must be a valid 5 letter word. Please re-enter guess.\n";
        cin >> newGuess;
        validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());
    }

    return newGuess;
}

Wordle::guessMap Guess::ProcessGuess(string newGuess, const string answer) {
    string newGuessMap;
    vector<char> usedLetters;

    // Convert the guess into all lower-case characters
    for (int i = 0; i < newGuess.size(); i++) {
        newGuess.at(i) = tolower(newGuess.at(i));
    }
    
    // Check if the guess is a perfect match to the answer
    if(strcmp(newGuess.c_str(), answer.c_str())==0) {
        newGuessMap = "#####";
    }
    // Otherwise, compare every letter to develop the guess-map 
    else {
        for (int i = 0; i < newGuess.size(); i++) {
            int checker = 0;
            for (int j = 0; j < answer.size(); j++) {
                if ((tolower(newGuess.at(i)) == answer.at(j)) && (i == j)) {
                    checker = 2;
                    usedLetters.push_back(newGuess.at(i));
                    continue;
                }
                else {
                    if ((tolower(newGuess.at(i)) == answer.at(j)) ) {
                        checker = 1;
                    }
                }
            }
            newGuessMap += map[checker].mapValue;
        }
    }

    // Return the guess with its processed accuracy mapping
    return {newGuess, newGuessMap};

}
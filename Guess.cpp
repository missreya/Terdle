#include "Guess.h"
#include <vector>
#include <iostream>
#include <iomanip> 
#include <cstring>

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

    while (newGuess.size() != 5) {
        cout << "Guess must be 5 letters long. Please re-enter guess.\n";
        cin >> newGuess;
    }

    // Splitting the vector into halves for more efficient looping 
    // int lowerIt = lower_bound(legalWords.begin(), legalWords.end(), key);
    // int upperIt = upper_bound(legalWords.begin(), legalWords.end(), key);

    // for (auto it = lowerIt; it != upperIt; ++it)

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
        cout << "perfect match!\n";
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

    // cout << "newGuess: \t" << newGuess << "\nguessMap: \t" << newGuessMap;

    // Return the guess with its processed accuracy mapping
    return {newGuess, newGuessMap};

}
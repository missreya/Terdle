#include <iostream>
#include <string>

#include "Wordle.h"
#include "Guess.h"

using namespace std;

void Wordle::ClearScreen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void Wordle::StartScreen() {
    // ClearScreen();
    cout << " - - - T-E-R-D-L-E - - - \n";

    for (int i = 0; i < 6; i++) {
        cout << "-----\n";
    }
}

void Wordle::Play(const string solution, const vector<string>& legalList) {
    
    Guess myGuess;

    // Request a guess from the user if there are there are 5 or less guesses so far
    while ((guessList.size() <=5)) {
        string userGuess = myGuess.RequestGuess(legalList);   

        guessList.push_back(myGuess.ProcessGuess(userGuess, solution));

        PrintGuesses();

        if (guessList.back().guessMap == "#####") {
            cout << "VICTORY!!!\n";
            return;
        }
    }
    cout << "Saad :( \n";
    return;
}

void Wordle::PrintGuesses() {
    ClearScreen();

    cout << " - - - T-E-R-D-L-E - - - \n";

    for (int i = 0; i < guessList.size(); i++) {
        cout << guessList.at(i).guessWord << "\t" << guessList.at(i).guessMap << endl;
    }

    for (int i = 0; i < 6 - guessList.size(); i++) {
        cout << "-----\n";
    }

}

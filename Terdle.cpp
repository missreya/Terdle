#include <iostream>
#include <string>

#include "Terdle.h"
#include "Guess.h"

using namespace std;

void Terdle::ClearScreen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void Terdle::StartScreen() {
    // ClearScreen();
    cout << " - - - T-E-R-D-L-E - - - \n";

    for (int i = 0; i < 6; i++) {
        cout << "-----\n";
    }
}

void Terdle::Play(const string solution, const vector<string>& legalList) {
    this->solution = solution;
    Guess myGuess;
    PrintGuesses();

    // Request a guess from the user if there are there are 5 or less guesses so far
    while ((guessList.size() <=5)) {
        string userGuess = myGuess.RequestGuess(legalList);   
        guessList.push_back(myGuess.ProcessGuess(userGuess, solution));

        PrintGuesses();

        if (guessList.back().guessMap == "#####") {
            cout << "\n* * * * * * * * * * * *\n";
            cout << "* *     VICTORY     * *";
            cout << "\n* * * * * * * * * * * *\n";
            return;
        }
    }
    cout << "\n* * * * * * * * * * * *\n";
    cout << "Sorry, better luck next time!\n";
    cout << "\n* * * * * * * * * * * *\n";
    return;
}

void Terdle::PrintGuesses() {
    // ClearScreen();
    cout << solution << "\t is the answer\n";

    cout << " - - - T-E-R-D-L-E - - - \n";

    for (int i = 0; i < guessList.size(); i++) {
        cout << guessList.at(i).guessWord << "\t" << guessList.at(i).guessMap << endl;
    }

    for (int i = 0; i < 6 - guessList.size(); i++) {
        cout << "-----\n";
    }

}

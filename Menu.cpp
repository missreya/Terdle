#include <iostream>
#include <string>

#include "Menu.h"
#include "Word.h"

using namespace std;

void Menu::ClearScreen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void Menu::PrintMenu() {
    ClearScreen();
    cout << "Welcome to T-E-R-D-L-E, the Wordle game played on a Terminal!\n";
    // cout << "\tDAILY PUZZLE: enter s\n";
    // cout << "\tENDLESS MODE: enter e\n";
    cout << "\tStart: enter s\n";
    cout << "\tQuit: enter q\n";
}

void Menu::PrintEmptyGuess() {
    cout << ".....\n";
}

void Menu::PrintGuess(string guess) {
    string printLine;
    for (int i = 0; i < 6; i++) {
        if (i == 5) {
            printLine += toupper(guess.at(i));
        }
        else {
            printLine += toupper(guess.at(i)) + " ";
        }
    }
}

void Menu::Start(string solution) {
    // ClearScreen();

    cout << " - - - T-E-R-D-L-E - - - \n";

    for (int i = 0; i < 6; i++) {
        PrintEmptyGuess();
    }

    Word guess(solution);
    guess.RequestGuess();   
}
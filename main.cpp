#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

#include "Wordle.h"
#include "Guess.h"
using namespace std;

//Declare Functions
vector<string> loadWordList(string fileName);
void PrintMainMenu();
string SelectAnswer(vector<string> &solutionList);
void PrintPlayAgainMenu();
void menuRequest(vector<string> &solutionList, const vector<string> &legalList);

// Begin main()
int main() {

    // Load the solution word list - if failure, terminate program
    vector<string> solutionList = loadWordList("wordle-solutions.txt");
    vector<string> legalList = loadWordList("legal-words.txt");

    // cout << "solutionList size is: " << solutionList.size() << endl;
    // cout << "guessList size is: " << legalList.size() << endl;

    // Print menu and request user input if they would like to start a game
    PrintMainMenu();
    menuRequest(solutionList, legalList);

    return 0;

} //end main

// Generates vector of potential word solutions from input file
vector<string> loadWordList(string fileName) {
    vector<string> wordVect;
    ifstream file;
    int index = 0;

    try {
        file.open(fileName); //open file for reading (not for writing)

        if (!file.is_open()) {
            throw fileName;
        }

        while (file) {
        string word;
        file >> word;
        wordVect.push_back(word);
    }
    }
    catch (string fileName) {
        cout << "ERROR: Could not open " << fileName << " - please ensure this file is in the directory.\nEXITING...";
        exit(0);
    }
    
    return wordVect;
}

void PrintMainMenu() {
    // // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    // std::cout << "\x1B[2J\x1B[H";

    cout << "Welcome to T-E-R-D-L-E, the Wordle game played on a Terminal!\n";
    cout << "\tStart: enter s or start\n";
    cout << "\tQuit: enter q or quit\n";
}

void PrintPlayAgainMenu() {
    cout << "Would you like to play again?\n";
    cout << "\tStart: enter s or start\n";
    cout << "\tQuit: enter q or quit\n";
}

// Chooses the new word - passes by ref for memory efficiency of vectors
string SelectAnswer(vector<string>& solutionList) {
    string newAnswer;
    srand(time(0));
    rand(); //discarding the first rand because this first num is less random (due to the time)
    int maxRange = solutionList.size() - 1;
    int newIndex = rand() % maxRange;
    newAnswer = solutionList.at(newIndex);

    // Removing this word from solution list so that it cannot be chosen in subsequent games this session
    solutionList.erase(solutionList.begin() + newIndex);

    return newAnswer;
}

void menuRequest(vector<string> &solutionList, const vector<string> &legalList) {
    // Get user input on if they would like to start a game
    string userMenuSelection;
    cin >> userMenuSelection;

    if (tolower(userMenuSelection.at(0)) == 's') {
        // Begin Game
        string newAnswer = SelectAnswer(solutionList);
        Wordle myGame;
        myGame.Play(newAnswer, legalList);

        // Check if user would like to play again
        PrintPlayAgainMenu();
        menuRequest(solutionList, legalList);

    }
    else if (tolower(userMenuSelection.at(0)) == 'q') {
        cout << "Thanks for playing!\n";
        return;
    }
}
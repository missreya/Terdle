#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

#include "Wordle.h"
#include "Guess.h"
using namespace std;

//Declare Functions
void PrintMainMenu();
vector<string> loadWordList(string fileName);
string selectAnswer(vector<string> &wordVect, vector<string> &usedWords);

// Begin main()
int main() {

    // Load the solution word list - if failure, terminate program
    vector<string> usedWords;
    vector<string> solutionList = loadWordList("wordle-solutions.txt");
    vector<string> legalList = loadWordList("legal-words.txt");

    if ((solutionList.at(0) == "ERROR") || (legalList.at(0) == "ERROR")) {
        cout << "EXITING...";
        return 1;
    }

    // cout << "solutionList size is: " << solutionList.size() << endl;
    // cout << "guessList size is: " << legalList.size() << endl;

    // Print menu
    PrintMainMenu();

    // Get user input on if they would like to start a game
    string userMenuSelection;
    cin >> userMenuSelection;

    if (tolower(userMenuSelection.at(0)) == 's') {
        // Begin Game
        string newAnswer = selectAnswer(solutionList, usedWords);
        Wordle myGame;
        myGame.Play(newAnswer, legalList);
    }
    else if (tolower(userMenuSelection.at(0)) == 'q') {
        cout << "Thanks for playing!\n";
        return 2;
    }

    return 0;

} //end main

// Generates vector of potential word solutions from input file
vector<string> loadWordList(string fileName) {
    vector<string> wordVect;
    ifstream file;
    int index = 0;

    file.open(fileName); //open file for reading (not for writing)

    if (!file.is_open()) {
        cout << "ERROR: Could not open " << fileName << " - please ensure this file is in the directory.\n";
        wordVect.push_back("ERROR");
        return wordVect;
    }

    while (file) {
        string word;
        file >> word;
        wordVect.push_back(word);
    }

    // cout << "Finished loading " << fileName << endl;
    
    return wordVect;
}

void PrintMainMenu() {
    // // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    // std::cout << "\x1B[2J\x1B[H";

    cout << "Welcome to T-E-R-D-L-E, the Wordle game played on a Terminal!\n";
    cout << "\tStart: enter s or start\n";
    cout << "\tQuit: enter q or quit\n";
}

// Chooses the new word - passes by ref for memory efficiency of vectors
string selectAnswer(vector<string>& solutionList, vector<string>& usedWords) {
    string newAnswer;
    srand(time(0));
    rand(); //discarding the first rand because this first num is less random (due to the time)
    int maxRange = solutionList.size() - 1;
    int newIndex = rand() % maxRange;
    newAnswer = solutionList.at(newIndex);

    // Add this word to the used word vector list
    usedWords.push_back(newAnswer);

    cout << "newIndex: " << newIndex << " New word: " << newAnswer << endl;

    return newAnswer;
}
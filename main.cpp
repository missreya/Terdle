#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

#include "Word.h"
#include "Menu.h"
using namespace std;

//Declare Functions
vector<string> loadWordList(string fileName);
string selectAnswer(vector<string> &wordVect, vector<string> &usedWords);

// Begin main()
int main() {

    // Load the solution word list - if failure, terminate program
    vector<string> usedWords;
    vector<string> solutionList = loadWordList("wordle-solutions.txt");
    vector<string> guessList = loadWordList("legal-words.txt");

    if ((solutionList.at(0) == "ERROR") || (guessList.at(0) == "ERROR")) {
        cout << "EXITING...";
        return 1;
    }

    cout << "solutionList size is: " << solutionList.size() << endl;
    cout << "guessList size is: " << guessList.size() << endl;

    // Print menu
    Menu mainMenu;
    mainMenu.PrintMenu();

    string userMenuSelection;
    cin >> userMenuSelection;

    if (userMenuSelection == "s") {
        string newAnswer = selectAnswer(solutionList, usedWords);
        mainMenu.Start(newAnswer);
    }
    else if (userMenuSelection == "q") {
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
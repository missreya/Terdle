#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

#include "Terdle.h"
#include "Guess.h"
using namespace std;

//Declare Functions
vector<string> loadWordList(string fileName);
void PrintMainMenu();
string SelectAnswer(vector<string> &solutionList);
void PrintPlayAgainMenu();
void menuRequest(vector<string> &solutionList, const vector<string> &legalList);

// Input/Output: None | Process: Load the solution vector and legal guess vectors, print the main menu to request user input, then call menuRequest will will process the user input
int main() {
    // Load the solution word list - if failure, terminate program
    vector<string> solutionList = loadWordList("wordle-solutions.txt");
    vector<string> legalList = loadWordList("legal-words.txt");

    // Print menu and request user input if they would like to start a game
    PrintMainMenu();
    menuRequest(solutionList, legalList);

    return 0;

} //end main

// Input: Name of the file (hardcoded in file) | Process: Generates vector of words from input file | Output: Returns vector of words
vector<string> loadWordList(string fileName) {
    vector<string> wordVect;
    ifstream file;
    int index = 0;

    // Exception if file is unable to be opened to generate word vector
    try {
        file.open(fileName); //open file for reading (not for writing)

        if (!file.is_open()) {
            throw fileName; // file was unable to be opened
        }

        while (file) {
            string word;
            file >> word;
            wordVect.push_back(word);
        }
    }
    // If exception is caught, program will terminate
    catch (string fileName) {
        cout << "ERROR: Could not open " << fileName << " - please ensure this file is in the directory.\nEXITING...";
        exit(0);
    }
    
    return wordVect;
} // end loadWordList

//Input: None | Process: Clears the terminal screen, then prints out the main manu | Output: Prints out main manu with options, no return
void PrintMainMenu() {
    // Clears the screen - CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    // Only works on Windows CMD or Powershell, not on JGrasp's terminal... sorry!
    std::cout << "\x1B[2J\x1B[H";

    cout << "Welcome to T-E-R-D-L-E, the Wordle game played on a Terminal!\n";
    cout << "\tStart: enter s or start\n";
    cout << "\tQuit: enter q or quit\n";
} //end PrintMainMenu

//Input: None | Process: After game is played once, asks if user wants to play again | Output: Prints out menu with options, no return
void PrintPlayAgainMenu() {
    cout << "Would you like to play again?\n";
    cout << "\tStart: enter s or start\n";
    cout << "\tQuit: enter q or quit\n";
} // end PrintPlayAgainMenu

// Input: Pass by Reference vector of possible solution words (PBR is for memory efficiency as vector is ~2300 words)
// Process: Using time as rand seed, pick a new solution. Remove this solution from the list so if user plays again, solution won't be picked again.
// Output: Returns the new solution word
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
} // end SelectAnswer

// Input: User inputs a letter to either start or quit 
// Process: If start - instantiate Terdle object and call Terdle::Play which starts the game. 
//          If quit - return to main() which will terminate the program. 
//          If unknown input - re-call this function.
// Output: Prints statement respective to user choice. No return.  
void menuRequest(vector<string> &solutionList, const vector<string> &legalList) {
    // Get user input on if they would like to start a game
    string userMenuSelection;
    cin >> userMenuSelection;

    if (tolower(userMenuSelection.at(0)) == 's') {
        // Begin Game
        string newAnswer = SelectAnswer(solutionList);
        
        // FOR TESTING PURPOSES - you can manually set the answer here. 
        // newAnswer = "liege";

        Terdle myGame;
        myGame.Play(newAnswer, legalList);

        // Check if user would like to play again
        PrintPlayAgainMenu();
        menuRequest(solutionList, legalList);
    } 
    // User requests to quit - this returns to main() then terminates program
    else if (tolower(userMenuSelection.at(0)) == 'q') {
        cout << "Thanks for playing!\n";
        return;
    } 
    //User input was not s or q... reprompt menu
    else {
        PrintMainMenu();
        cout << "Please input either s or q\n";
        menuRequest(solutionList, legalList);
    }
} // end menuRequest
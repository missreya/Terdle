#include "Word.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include <time.h>
using namespace std;

//Declare Functions
vector<string> loadWordList();
string selectAnswer(vector<string> &wordVect, vector<string> &usedWords);
void printMenu();

// Begin main()
int main() {

    // Load the word list - if failure, terminate program
    vector<string> usedWords;
    vector<string> wordList = loadWordList();

    if (wordList.at(0) == "ERROR") {
        cout << "EXITING...";
        return 1;
    }

    // cout << "Wordlist size is: " << wordList.size() << endl;

    string myAnswer = selectAnswer(wordList, usedWords);

    return 0;
} //end main







// Generates vector of 5 letter words from input file
vector<string> loadWordList() {
    vector<string> wordVect;
    ifstream file;
    int index = 0;

    // cout << "Opening file wordle-list.txt\n";
    file.open("wordle-list.txt"); //open file for reading (not for writing)

    if (!file.is_open()) {
        cout << "ERROR: Could not open file wordle-list.txt - please ensure this file is in the directory.\n";
        wordVect.push_back("ERROR");
        return wordVect;
    }

    while (file) {
        string word;
        file >> word;
        wordVect.push_back(word);
    }
    
    return wordVect;
}

// Chooses the new word - passes by ref for memory efficiency of vectors
string selectAnswer(vector<string>& wordList, vector<string>& usedWords) {
    string newAnswer;
    srand(time(0));
    rand(); //discarding the first rand because this first num is less random (due to the time)
    int maxRange = wordList.size() - 1;
    int newIndex = rand() % maxRange;
    newAnswer = wordList.at(newIndex);

    // Add this word to the used word vector list
    usedWords.push_back(newAnswer);

    cout << "newIndex: " << newIndex << " New word: " << newAnswer << endl;

    return newAnswer;
}
#ifndef WORDLEH
#define WORDLEH

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Wordle {
    public:
        void Play(const string solution, const vector<string>& legalList);
        struct guessMap {
            string guessWord; // the guessed word in all caps
            string guessMap;  // the accuracy of the guessed word using symbols
        };

    private:
        void PrintGuesses();
        void ClearScreen();
        void StartScreen();
        string solution;
        vector<guessMap> guessList; // all of the guessed words for this game
};

#endif
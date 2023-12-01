#ifndef WORDLEH
#define WORDLEH

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Wordle {
    public:
        void Play(const string solution, const vector<string>& legalList);
        void ClearScreen();
        void StartScreen();

        struct guessMap {
            string guessWord; // the guessed word in all caps
            string guessMap;  // the accuracy of the guessed word using symbols
        };

        vector<guessMap> guessList; // all of the guessed words for this game

    private:
        void PrintGuesses();
        // void PrintGuess(string guess);
};

#endif
#ifndef TERDLEH
#define TERDLEH

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Terdle {
    public:
        void Play(const string solution, const vector<string>& legalList);

        struct guessMap {
            string guessWord;   // the guessed word in all caps
            string guessMap;    // the accuracy of the guessed word using symbols
        }; //end guessMap struct

    private:
        void ClearScreen();
        void PrintGuesses();
        string solution; // the solution for the game
        vector<guessMap> guessList; // all of the guessed words for this game
}; //end Terdle class

#endif
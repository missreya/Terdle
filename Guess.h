#ifndef GUESSH
#define GUESSH

#include <string>
#include <vector>
#include "Wordle.h"
using namespace std;

class Guess {
    public:
        string RequestGuess(const vector<string> &legalWords);
        Wordle::guessMap ProcessGuess(string guess, const string answer);

        struct LetterMap {
            string mapKey;
            char mapValue;
        };
    
    private:
        string convertToLowerCase(string word);
};

#endif
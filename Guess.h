#ifndef GUESSH
#define GUESSH

#include <string>
#include <vector>
#include "Terdle.h"
using namespace std;

class Guess {
    public:
        string RequestGuess(const vector<string> &legalWords);
        Terdle::guessMap ProcessGuess(string guess, const string answer);

        struct LetterMap {
            string mapKey;
            char mapValue;
        }; //end LetterMap struct
    
    private:
        string convertToLowerCase(string word);
        vector<int> findDupCharLocation(string word, char letter);
}; //end Guess class

#endif
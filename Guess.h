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
        }; //RY- end LetterMap struct
    
    private:
        string convertToLowerCase(string word);
        vector<int> findDupCharLocation(string word, char letter);
}; //RY- end Guess class

#endif
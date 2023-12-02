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
        };

        struct usedLetters {
            vector<char> letter; // the letter already used
            vector<int> indexGuess; // the index of the guess that had matched
            vector<int> indexAnswer; // index of answer that letter matched to
            vector<int> map; // the accuracy of the match
        };
    
    private:
        string convertToLowerCase(string word);
        void addToUsedLetters(usedLetters& used, char letter, int guessIndex, int answerIndex, int checker);
        vector<int> findDupCharLocation(string word, char letter);
};

#endif
#ifndef WORDH
#define WORDH

#include <string>
#include <vector>
using namespace std;

class Word {
    public:
        string answer;
        string newGuess;

        Word();
        Word(string answer);
        void RequestGuess();
        void ProcessGuess(string guess);

        struct LetterMap {
            string mapKey;
            char mapValue;
        };

        struct guessMap {
            string guess;
            string guessLayout;
            string guessMap;
        };
        
        vector<guessMap> guessList;
};

#endif
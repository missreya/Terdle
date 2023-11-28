#ifndef WORDH
#define WORDH

#include <string>
#include <vector>
using namespace std;

class Word {
    public:
        string answer;
        string guess;
        void PrintResult() const;
        Word();
        Word(string answer);

    // private:
        struct LetterMap {
            string mapKey;
            char mapValue;
        };

        LetterMap map[3] = {
            {"incorrect",   '-'},
            {"partial",     'x'},
            {"correct",    'O'}
        };
};

#endif
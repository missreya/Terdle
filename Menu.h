#ifndef MENUH
#define MENUH

#include <string>
#include <iostream>
using namespace std;

class Menu {
    public:
        void ClearScreen();
        void PrintMenu();
        void Start(string solution);

    private:
        void PrintEmptyGuess();
        void PrintGuess(string guess);
};

#endif
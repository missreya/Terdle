#include <iostream>
#include <string>

#include "Terdle.h"
#include "Guess.h"

using namespace std;

//RY- Input: None | Process: Uses ASCII to manually "clear" the screen | Output: Screen is cleared, no return
void Terdle::ClearScreen() {
    //RY- CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
} //RY- end ClearScreen

//RY- Input: None | Process: Prints TERDLE header border and the guesses so far with the guess map | Output: Prints game screen with guesses, no return
void Terdle::PrintGuesses() {
    //RY- Clear the screen everytime so that the guesses look like they populate the empty guesses
    //RY- Only works on Windows CMD or Powershell, not on JGrasp's terminal... sorry!
    // ClearScreen();

    //RY- FOR TESTING PURPOSES - you can display the answer here with every guess
    // cout << solution << "\t is the answer\n";

    cout << " - - - T-E-R-D-L-E - - - \n";

    //RY- Print the guessed word and its gues map
    for (int i = 0; i < guessList.size(); i++) {
        cout << guessList.at(i).guessWord << "\t" << guessList.at(i).guessMap << endl;
    } //RY- end for

    //RY- For the remaining guesses, print empty guesses
    for (int i = 0; i < 6 - guessList.size(); i++) {
        cout << "-----\n";
    } //RY- end for
} //RY- end PrintGuesses

//RY- Input: None | Process: Uses ASCII to manually "clear" the screen | Output: Screen is cleared, no return
void Terdle::Play(const string solution, const vector<string>& legalList) {
    //RY- Set variables and instantiate Guess object. 
    this->solution = solution;
    Guess *myGuess = new Guess;

    //RY- Print out the current guesses
    PrintGuesses();

    //RY- Request a guess from the user if there are there are 5 or less guesses so far
    while ((guessList.size() <=5)) {
        string userGuess = myGuess->RequestGuess(legalList);   
        guessList.push_back(myGuess->ProcessGuess(userGuess, solution));

        //RY- Print out the current guesses
        PrintGuesses();

        //RY- If the guessMap shows the guess was correct, print victory screen, then return to main::menuRequest
        if (guessList.back().guessMap == "#####") {
            cout << "\n* * * * * * * * * * * *\n";
            cout << "* *     VICTORY     * *";
            cout << "\n* * * * * * * * * * * *\n";
            return;
        } //RY- end if
    } //RY- end while 

    //RY- All 6 guesses were used before correct answer was solved - print loss screen. Exits normally to main::menuRequest
    cout << "\n* * * * * * * * * * * * * * *\n";
    cout << "Sorry, better luck next time!\n";
    cout << "The answer was " << solution;
    cout << "\n* * * * * * * * * * * * * * *\n";

    //RY- Deallocate myGuess after guess is complete
    delete myGuess;    

} //RY- end Play

#include "Guess.h"
#include <vector>
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <algorithm>

using namespace std;

//RY- Use the LetterMap struct to define map - this contains the equivalent mapping for letter accuracy
Guess::LetterMap map[3] = {
    {"grey",   '_'},  // no letter match
    {"yellow", '+'},  // match letter but incorrect index 
    {"green",  '#'}   // match letter and correct index
}; //RY- end map definition for guessMap

//RY- Input: Guessed word received from user input previously | Process: Converts the word to all lower-case | Output: No print - returns the lowercase word
string Guess::convertToLowerCase(string word) {
    for (int i = 0; i < word.size(); i++) {
        word.at(i) = tolower(word.at(i));
    } //RY- end for
    return word;
} //RY- end convertToLowerCase

//RY- Input: Pass by Reference the legal word list (the words allowed to be guessed) - PBR because legal word list is almost 15,000 words
//RY- Process: Converts the guessed word to all lower case 
//RY-          Validate if the guessed word is in the legal word list 
//RY-          If not, reprompt user to enter a valid input
//RY- Output: No print - returns the guessed word
string Guess::RequestGuess(const vector<string> &legalWords) {
    string newGuess;

    //RY- Prompt user for their guess
    cout << "Your guess: ";
    cin >> newGuess;

    //RY- Convert the guess into all lower-case characters because legal words are all in lower case
    newGuess = convertToLowerCase(newGuess);

    //RY- Validate if the guessed word is in the legal word list
    bool validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());

    //RY- If the guess is not a valid word, re-prompt user for a new valid guess
    while((!validWord)) {
        cout << "Guess must be a valid 5 letter word. Please re-enter guess.\n";
        cin >> newGuess;
        newGuess = convertToLowerCase(newGuess);
        validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());
    } //RY- end while

    return newGuess;
} //RY- end RequestGuess

//RY- *** THIS IS A VERY LARGE FUNCTION. I've labeled the sections with the equivalent psuedocode part - i.e. (2) and (2-A) below in function. 
// Input: The user's input guess and the game's answer.
// Process: This analyzes each letter of the guess to develop the guessMap, which is the accuracy of the guess. This is done in 3 main parts. 
//  (1) Checks if the guess == answer. If so, return with the fully correct guessmap
//  (2) If not a fully correct answer, begin loop through guess's letters
//        (2-A) If this letter is a duplicate (appears multiple times in the guess or answer):
//                Mark the guessMap position with a duplicate marker '?'. 
//        (2-B) If this letter is not a duplicate, check if the letter exists in the answer:
//                Populate guessMap. If yes and same index = "green". If yes and different index = "yellow". Otherwise, "grey". 
//  (3) Process Duplicates- If the guessMap contains duplicate letter markers '?':
//        (3-A) Populate the matchVect for each guess's letter index with the respective guessMap accuracy. 
//        (3-B) If there are more guessed letters than solution letters for that letter:
//                Change yellow marked letters to grey, starting from end of word until number of yellow+green letters equals to number of letters for solution
//  (4) Return the completed {newGuess, newGuessMap} back to the Terdle::Play function so that game may continue
// Output: Returns the newGuess and newGuessMap struct
Terdle::guessMap Guess::ProcessGuess(string newGuess, const string answer) {
    string newGuessMap;
    bool dupCheck = false;
    
    //RY- (1) Check if the guess is a perfect match to the answer
    if(strcmp(newGuess.c_str(), answer.c_str())==0) {
        newGuessMap = "#####";

        //RY- Return to exit immediately
        return {newGuess, newGuessMap};
    } //RY-end if
    //RY- (2) Otherwise, compare every letter to develop the guess-map 
    else {
        for (int i = 0; i < newGuess.size(); i++) {
            int accuracy = 0; // start with no match
            vector<int> answerDupes = findDupCharLocation(answer, newGuess.at(i)); // vector containing all indexes of this letter in the answer
            vector<int> guessDupes = findDupCharLocation(newGuess, newGuess.at(i)); // vector containing all indexes of this letter in the guess

            //RY- (2-A) If the letter has any duplicates in the answer or the guess, mark map as a duplicate to solve later
            if (((answerDupes.size() != 1) || (guessDupes.size()) != 1)) {
                newGuessMap += '?';
                continue; // move onto next letter
            } //RY- end if
            //RY- (2-B) Since letter does not have duplicates, we can simply check if the letter matches in solution
            else {
                //RY- Loop through the answer's letters
                for (int j = 0; j < answer.size(); j++) {
                    //RY- if matched letter and index, mark as (green) 
                    if ((newGuess.at(i) == answer.at(j)) && (i == j)) {
                        accuracy = 2; //green
                    } //RY- end if
                    //RY- if match letter but not index (yellow)
                    else if ((newGuess.at(i) == answer.at(j)) && (i != j)) {
                        accuracy = 1; //yellow
                    } //RY- end else if
                    //RY- if it reaches end of this for loop, accuracy stays as 0 for grey
                } //RY- end for           
            } //RY- end else 
            //RY- Add the map accuracy to the guess map
            newGuessMap += map[accuracy].mapValue;
        } //RY- end for loop
    } //RY- end else

    //RY- (3) Process Duplicates- Check for '?' duplicate markers in the guessMap - if so, process these duplicate letters
    for (int i = 0; i < newGuessMap.size(); i++) {
        if (newGuessMap.at(i) == '?') {
            vector<int> answerDupes = findDupCharLocation(answer, newGuess.at(i)); // vector containing all indexes of this letter in the answer
            vector<int> guessDupes = findDupCharLocation(newGuess, newGuess.at(i)); // vector containing all indexes of this letter in the guess
            vector<char> matchVect; //vector that will eventually hold all of the equivalent guessMap for the guessDupes letter indexes

            //RY- (3-A) Check every guessDupes.index value to see if it matches that of the answerDupes
                //RY- Populate matchVect with the guessmap equaivalent for each guess letter dup
                //RY- ex. answer = liege (2 Es) and guess = eerie (3 Es)
                //RY- answerDupes = {2, 4} and guessDupes = {0, 1, 4}
                //RY- then matchVect = {+, +, #}
            for (int j = 0; j < guessDupes.size(); j++) {
                //RY- if the guess's index is in the answer's index, then accuracy is green. 
                if ((find(answerDupes.begin(), answerDupes.end(), guessDupes.at(j) ) != answerDupes.end())) {
                    matchVect.push_back(map[2].mapValue);
                } //RY- end if
                //RY- since guess's index is not in the answer's index, accuracy is yellow
                else {
                    matchVect.push_back(map[1].mapValue);
                } //RY- end else
            } //RY- end else

            //RY- (3-B) If guess dups is larger than answer dups, then convert excess guess yellow(s) to grey starting from the back
                //RY- ex. answer = liege (2 Es) and guess = eerie (3 Es)
                //RY- answerDupes = {2, 4} and guessDupes = {0, 1, 4}
                //RY- then matchVect = {+, +, #} ------> matchVect = {+, _, #}
            if (guessDupes.size() > answerDupes.size()) {
                //RY- Determine number of extra guesses that we need to convert from yellow to grey
                int removeNum = guessDupes.size() - answerDupes.size();
                if (removeNum > 0) {
                    //RY- Loop starting from the end of the map
                    for (int index = matchVect.size() - 1 ; index >= 0; index--) {
                        //RY- If the letter is yellow, change to grey 
                        if (matchVect.at(index) == map[1].mapValue) {
                            matchVect.at(index) = map[0].mapValue;
                            removeNum--;
                        } //RY- end if accuracy if yellow

                        //RY- When we have converted enough excess guesses, break out of loop
                        if (removeNum == 0) {
                            break;
                        } //RY- end if 
                    } //RY- end for
                } //RY- end if removeNum > 0
            } //RY- end if guessDupes size > answerDupes size
            //RY- Insert the matchVect values into the guessMap
            for (int j = 0; j < guessDupes.size(); j++) {
                    newGuessMap.at(guessDupes.at(j)) = matchVect.at(j);
            } //RY- end for loop
        } // end if guessMap.at(i) = '?'
    } //RY- end for loop through guessDupes vect
    
    //RY- (4) Return the guess with its completed accuracy mapping
    return {newGuess, newGuessMap};
} //RY- end ProcessGuess

//RY- Input: Word string and letter char 
//RY- Process: Checks if letter is present in word. If so, add the index of word to a vector. 
//RY- Output: Returns vector of character location indexes. 
vector<int> Guess::findDupCharLocation(string word, char letter) {
    vector<int> charLocations;
    for(int i =0; i < word.size(); i++) {
        if(word[i] == letter) {
            charLocations.push_back(i);
        } //RY- end if
    } //RY- end for
    return charLocations;
} //RY- end findDupCharLocation
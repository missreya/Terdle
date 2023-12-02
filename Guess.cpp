#include "Guess.h"
#include <vector>
#include <iostream>
#include <iomanip> 
#include <cstring>
#include <algorithm>

using namespace std;

Guess::LetterMap map[3] = {
    {"incorrect", '_'}, // grey char(250)
    {"partial",   '+'}, // yellow char(176)
    {"correct",   '#'}  // green char(178)
};

string Guess::convertToLowerCase(string word) {
    // Convert the guess into all lower-case characters
    for (int i = 0; i < word.size(); i++) {
        word.at(i) = tolower(word.at(i));
    }
    return word;
}

string Guess::RequestGuess(const vector<string> &legalWords) {
    string newGuess;
    cout << "Your guess: ";
    cin >> newGuess;
    newGuess = convertToLowerCase(newGuess);
    bool validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());

    // Validate that the guess is a valid word (i.e. in the legal words list)
    while((!validWord)) {
        cout << "Guess must be a valid 5 letter word. Please re-enter guess.\n";
        cin >> newGuess;
        newGuess = convertToLowerCase(newGuess);
        validWord = (find(legalWords.begin(), legalWords.end(), newGuess) != legalWords.end());
    }

    return newGuess;
}

Terdle::guessMap Guess::ProcessGuess(string newGuess, const string answer) {
    string newGuessMap;
    usedLetters used;
    
    // Check if the guess is a perfect match to the answer
    if(strcmp(newGuess.c_str(), answer.c_str())==0) {
        newGuessMap = "#####";
    }
    // Otherwise, compare every letter to develop the guess-map 
    else {
        for (int i = 0; i < newGuess.size(); i++) {
            int checker = 0;
            int duplicateCheck = -1;
            for (int j = 0; j < answer.size(); j++) {
                // if matched letter and index, mark as (green) 
                if ((newGuess.at(i) == answer.at(j)) && (i == j)) {
                    checker = 2;
                    // if letter has not been matched before, add to usedLetters map
                    if (find(used.letter.begin(), used.letter.end(), newGuess.at(i)) == used.letter.end()) {
                        addToUsedLetters(used, newGuess.at(i), i , j, checker);
                    }
                    // else letter has already been matched
                    else {
                        // locate the index of the previously matched letter on the usedLetters index 
                        vector<char>::iterator iter = find(used.letter.begin(), used.letter.end(), newGuess.at(i));
                        int indexUsed = iter - used.letter.begin();
                        
                        // locate the index on the solution that previous match had matched to
                        int indexSolution = used.indexAnswer.at(indexUsed);
                        int indexGuessed = used.indexGuess.at(indexUsed);

                        // if previous matched letter was a match to this same index AND that match was yellow, change previous match to (grey)
                        if ((j == indexSolution) && (newGuessMap.at(indexGuessed) = map[1].mapValue)){
                            // change the guessMap for previous match to be grey 
                            newGuessMap.at(indexGuessed) = map[0].mapValue;
                        }
                    }
                    // Since letter has already been matched at this guess index, skip cycling through the rest of the solution 
                    break;
                }
                // if match letter but not index (yellow)
                else if ((newGuess.at(i) == answer.at(j)) && (i != j)) {
                    checker = 1;
                    // if letter has not been matched before, add this letter to the usedLetters map
                    if (find(used.letter.begin(), used.letter.end(), newGuess.at(i)) == used.letter.end()) {
                        addToUsedLetters(used, newGuess.at(i), i , j, checker);
                    }
                    // else letter has already been matched
                    else {

                        // locate the index of the previously matched letter on the usedLetters index 
                        vector<char>::iterator iter = find(used.letter.begin(), used.letter.end(), newGuess.at(i));
                        int indexUsed = iter - used.letter.begin();

                        // locate the index on the solution that previous match had matched to
                        int indexSolution = used.indexAnswer.at(indexUsed);

                        // if current solution index is higher than the previous matched index, updated userLetters map to it 
                        // that way, double letters in solution are accounted for
                        if (j > indexSolution) {
                            used.indexAnswer.at(indexUsed) = j;
                        }
                        // if previous matched letter was a match to this same index
                        else if (j == indexSolution){
                            // change this letter's to be grey 
                            checker = 0;
                        }
                        // else if this guess index was already a green match, keep as green
                        // else if ((used.map.at(indexUsed == map[2].mapValue)) && i == indexSolution) {
                        //     cout << "turn green\n";
                        //     checker = 2;
                        // }
                    }
                }               
            }
            // Add the map accuracy to the guess map
            newGuessMap += map[checker].mapValue;
        }
    }

    // Return the guess with its processed accuracy mapping
    return {newGuess, newGuessMap};
}

void Guess::addToUsedLetters(usedLetters& used, char letter, int guessIndex, int answerIndex, int checker) {
    used.letter.push_back(letter);
    used.indexGuess.push_back(guessIndex);
    used.indexAnswer.push_back(answerIndex);
    used.map.push_back(checker);
}
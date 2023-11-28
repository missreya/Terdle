# Terdle
Terminal Wordle... aka play Wordle in your terminal :)

# Other Credit
5 Letter Wordle List from dracos (github): https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93

or pre-shuffled https://github.com/tabatkins/wordle-list

List of solutions here: https://github.com/vallleyyy/WordleDictionary

# REMAINING TO-DO
Word::ProcessGuess
- complexity rules with repeated letters in guess
- complexity rules with repeated letters in solution

Word::RequestGuess
- checker that the guess is in the legal word list
- turn cin into a getline 

Menu::Start
- continue to request guesses until game is won OR guesslist is size 6

Menu
- make Menu::PrintGame - properly print out the guess + guessMap with stream
- make a win screen
- make a lose screen
- make a request to play again

Main
- try throw catch exception for the files
- check that the selected solution is not in the usedWords list
# Terdle
- Terminal Wordle... aka play Wordle in your terminal :)

# Credit
- 5 Letter Wordle List: https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93
- List of Previous Worlde Solutions: https://github.com/vallleyyy/WordleDictionary

# How To Play Terdle
- Simply build and run this in your terminal... and let the fun begin!

# Terdle Rules
- They are the same as Wordle rules. You have 6 guesses to figure out the 5 letter word.
- Your guesses must be valid words - these are the same valid words for Wordle.
- A correct letter guessed in the correct spot results in # (aka green in Wordle).
- A correct letter guessed in the wrong spot result in + (aka yellow in Wordle).
- A correct letter that is not in the answer results in _ (aka grey in Wordle).

# Wordle Rules Regarding Duplicate Letters
```
liege    is the answer
 - - - T-E-R-D-L-E - - -
sweed   __#+_               If one dup letter is an incorrect spot, it will be yellow
needy   _+#__               If one dup letter is an incorrect spot, it will be yellow
neeze   __#_#               Additional dups: green matches take priority
eerie   +__+#               Additional dups: lower index yellow takes priority over other yellows, but not over greens
eever   ++___               Additional dups: lower index yellow takes priority over other yellows
```

# Debugging Lines
- Set the answer to a certain word: uncomment main.cpp Line 111
- Display the answer during game: uncomment Terdle.cpp Line 22

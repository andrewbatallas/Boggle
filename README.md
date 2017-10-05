# Boggle Board Solver with Tries

This project contains my implementation of a [Trie](https://en.wikipedia.org/wiki/Trie) using linked lists.

Here, tries are used to win a game of [Boggle](https://en.wikipedia.org/wiki/Boggle) against the computer. The user goes first and tries to find as many words as they can, and then the computer finds the remaining words. The computer's solution(s) to the game are found using recursive backtracking. The program utilises a trie that contains all of the words from the Official Scrabble Players Dictionary (ospd.txt).

## Boggle Board Information

Included in this repo is a sample Boggle Board in a file titled boggle-in.txt, whose contents are:
```
eaii
nrav
tioa
uslr
```
There are 167 possible words that you can find on this board. You can also generate your own boggle board by editing the text file. Make sure that boggle-in.txt and ospd.txt are in the same folder as your source files.

### Gameplay

When you run boggle.cpp, the program will display the board and prompt you to type any words that you see on the board. Enter one word at a time and press enter. If you enter a word that is less than four letters long, then you will see this message:
```
Please enter a word that is at least four characters.
```
If you enter a word that is not part of the OSPD, then you will see this message:
```
Please enter a word that is part of the dictionary.
```
If you enter a word that you already entered, then you will see this message: 
```
Please enter a word that has not already been entered.
```
For any entered word that is both at least four letters long and part of the OSPD, the program will not tell you if the word is actually on the board until you are done guessing. You can tell the computer that you're done playing by typing either "q" or "Q" without quotes. After this, you'll know which of your guesses were actually on the board and you'll see the list of words that you weren't able to find, as well as how many.

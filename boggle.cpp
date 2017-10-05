#include <stdexcept>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Trie.h"

const int DIM = 4; //characters per row or column on Boggle Board
const int MIN_WORD_SIZE = 4; //minimum length of a valid word

void makeAndPrintBoard(std::pair<char,bool> board[DIM][DIM]);

void solver(int m, int n, std::pair<char,bool> board[DIM][DIM], std::string &cur,
            const Trie &dict, const Trie &userAns, Trie &userCorrect, Trie &compCorrect);

void getInput(Trie &userInput, Trie dict);

void printWordsFound(Trie storedWords, bool isPlayer);


int main()
{
    //creates a Trie for the OSPD
    Trie dictionary;
    dictionary.loadFromFile("ospd.txt");

    //create 2D array representing Boggle board
    //first will denote character at a given position on the board
    //second will denote whether a given position on the board has been visited
    std::pair<char,bool> board[DIM][DIM];

    //create and print out Boggle board
    makeAndPrintBoard(board);

    std::cout << "\nGAMEPLAY: " << std::endl;

    Trie userAnswers;
    getInput(userAnswers, dictionary);

    std::cout << "The computer will now search for "
            "any remaining words on the board." << std::endl;

    Trie userCorrectAns;
    Trie compFoundWords;
    std::string cur = "";

    //finds all words in Boggle Board not found by user
    for(size_t m = 0; m < DIM; m++) {
        for (size_t n = 0; n < DIM; n++) {
            solver(m, n, board, cur, dictionary,
                   userAnswers, userCorrectAns, compFoundWords);
        }
    }

    printWordsFound(userCorrectAns, true);
    std::cout << "------------" << std::endl;
    printWordsFound(compFoundWords, false);

    return 0;
}


// makeAndPrintBoard
// pre: board is an empty DIM X DIM array of type std::pair<char,bool>,
//      represents Boggle Board
// post: All positions on the board are assigned their corresponding elements from
//      the boggle-in.txt file. The Boggle board is printed out to the user.
void makeAndPrintBoard(std::pair<char,bool> board[DIM][DIM])
{
    std::ifstream file("boggle-in.txt");
    if (!file) { //error checking
        throw std::invalid_argument("Boggle Board file cannot be opened");
    }

    //store Boggle board into array
    std::string wordVal;
    size_t k = 0;
    std::cout << "The Boggle Board: " << std::endl;
    while(file >> wordVal) {
        for (size_t l = 0; l < DIM; l++) {
            board[k][l].first = wordVal[l];
            board[k][l].second = false;
        }
        std::cout << wordVal << std::endl;
        k++;
    }
}


// solver
// pre: m is the row number and n is the column number on the Boggle board,
//      both using zero-based indexing. board is a DIM X DIM 2D array with all elements
//      assigned (represents Boggle board). cur is the
//      dict is the dictionary of valid words.
//      userAns Trie of the user's guesses of words on the board. userCorrect
//      is the subset of the user's guesses that appear on the board. CompCorrect
//      is the Trie of words on the board not found by the user to be found by
//      the computer.
// post: All words not already found by the user starting with the character located
//      at the (m,n) position(zero-based indexing) are stored in the Trie compCorrect.
//      All words correctly guessed by the user starting with that same character are
//      stored in userCorrect.
void solver(int m, int n, std::pair<char,bool> board[DIM][DIM], std::string &cur,
            const Trie &dict, const Trie &userAns, Trie &userCorrect, Trie &compCorrect)
{
    board[m][n].second = true;
    cur = cur + board[m][n].first;
    if (cur.length() >= MIN_WORD_SIZE && dict.isWord(cur)) {
        if (userAns.isWord(cur)) {
            userCorrect.insert(cur);
        } else if (!compCorrect.isWord(cur)) {
            compCorrect.insert(cur);
        }
    }

    if (dict.isPrefix(cur)) {
        for (int i = std::max(m-1,0); i <= std::min(m+1,DIM-1); i++) {
            for (int j = std::max(n-1,0); j <= std::min(n+1,DIM-1); j++) {
                if (!board[i][j].second) {
                    solver(i, j, board, cur, dict, userAns, userCorrect, compCorrect);
                }
            }
        }
    }
    cur.erase(cur.length() - 1);
    board[m][n].second = false;
}


// getInput
// pre: Trie userInput stores the valid guesses the user types in.
//      Trie dict is the dictionary of possible words.
// post: The user enters guesses of words on the Boggle board. Words that
//      is not at least four characters, not a word in the dictionary,
//      or were already entered by the user.
void getInput(Trie &userInput, Trie dict)
{
    std::cout << "Please enter words that you find on the Board. ";
    std::cout << "Press \'Q\' or \'q \'when you are done." << std::endl;
    std::string ans;
    std::cin >> ans;
    while (ans != "q" && ans != "Q") {
        bool flag = true;
        if (ans.length() < MIN_WORD_SIZE) {
            std::cout << "Please enter a word that "
                    "is at least four characters." << std::endl;
            flag = false;
        }
        if (!dict.isWord(ans)) {
            std::cout << "Please enter a word that "
                    "is part of the dictionary." << std::endl;
            flag = false;
        }
        if (userInput.isWord(ans)) {
            std::cout << "Please enter a word that "
                    "has not already been entered." << std::endl;
            flag = false;
        }

        if (flag) {
            userInput.insert(ans);
        }
        std::cin >> ans;
    }
}


// printWordsFound
// pre: storedWords is a (possibly empty) Trie of words found by either
//      the user of the computer. isPlayer is a boolean indicating if the
//      agent who stored the words is the player (true) or the computer (false).
// post: Prints out how many words found by the agent during game play
//      after a list of those words.
void printWordsFound(Trie storedWords, bool isPlayer)
{
    size_t ct = storedWords.wordCount();
    std::string name;
    if (isPlayer) {
        name = "You";
    } else {
        name = "The computer";
    }
    std::cout << name << " found the following words:\n============" << std::endl;
    storedWords.print();
    std::cout << "============\n" << name << " found " << ct << " word";
    if (ct != 1) {
        std::cout << "s";
    }
    std::cout << "." << std::endl;
}
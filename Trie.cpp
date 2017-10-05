#include "Trie.h"
#include <cstddef>   // make gcc & CLion happy
#include <stdexcept>
#include <fstream>
#include <iostream>


//default ctor
// post: Trie is created and initialized to be empty. Root node is created.
Trie::Trie():myRoot(new TrieNode(' ', false)){}


// Copy Constructor
// pre: parameter object, rhs, exists
// post: Trie is created to be a copy of the parameter Trie
Trie::Trie(const Trie& rhs):myRoot(new TrieNode(*rhs.myRoot)) {}


// Destructor
// pre: The Trie exists
// post: The Trie is destroyed and any dynamic memory is returned to the system
Trie::~Trie()
{
    delete myRoot;
    myRoot = nullptr;
}


// Assignment Operator
// pre: Both Tries exist
// post: This Trie gets assigned a copy of the parameter Trie
const Trie& Trie::operator=(const Trie& rhs)
{
    if(this == &rhs) {
        return *this;
    }
    Trie tmp(rhs);
    std::swap(myRoot, tmp.myRoot);
    return *this;
}


// Insert
// pre: word is a string representing a word
// post: Inserts str into the given Trie
void Trie::insert(const std::string& word)
{
    myRoot->insert(strToLow(word));
}


// loadFromFile
// pre: filename is the name of the file to be read
// post: Insert all words in the specified file into the Trie.
// Throws a std::invalid_argument exception if the specified file cannot be opened.
void Trie::loadFromFile(const std::string& filename)
{
    std::string str;
    std::ifstream file(filename.c_str());
    if (!file) { //error checking
        throw std::invalid_argument("File cannot be opened");
    }

    std::string wordVal;
    while(file >> wordVal) {
        insert(wordVal);
    }
}


// isWord
// pre: word is a string representing a word
// post: Returns true if word is in the Trie, else returns false.
bool Trie::isWord(const std::string& word) const
{
    return myRoot->isWord(strToLow(word));
}


//isPrefix
// pre: pre is a string of a prefix of a word
// post: Returns true if pre is a prefix of a word in the Trie, else returns false.
bool Trie::isPrefix(const std::string& pre) const
{
    if (pre == "") {
        return true;
    }
    return myRoot->isPreFix(strToLow(pre));
}


// print
// post: Prints all of the words stored in the Trie
void Trie::print() const
{
    if (myRoot != nullptr) {
        myRoot->print("");
    }
}


// wordCount
// post: Returns the number of words in the Trie
size_t Trie::wordCount() const
{
    return myRoot->wordCount();
}


// strToLow helper function
// pre: str is a string representing a word
// post: Returns a the same word with all characters in lowercase
std::string Trie::strToLow(const std::string &str) const
{
    std::string strLow = "";
    for(size_t i = 0; i < str.length(); i++) {
        strLow += (char) tolower(str[i]);
    }
    return strLow;
}
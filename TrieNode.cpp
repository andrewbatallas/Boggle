#include <iostream>
#include "TrieNode.h"


// Alternate Constructor
// post: Creates a new TrieNode with item c that may be the end of a word
TrieNode::TrieNode(char c, bool b):item(c), isEnd(b) {
    for(size_t i = 0; i < sizeof(next)/sizeof(*next); i++) {
        next[i] = nullptr;
    }
}


// Copy Constructor
// pre: parameter object rhs exists
// post: Creates a new TrieNode that is a copy of rhs
TrieNode::TrieNode(const TrieNode& rhs):item(rhs.item), isEnd(rhs.isEnd)
{
    for(size_t i = 0; i < sizeof(next)/sizeof(*next); i++) {
        if (rhs.next[i] != nullptr)
        {
            next[i] = new TrieNode(*rhs.next[i]);
        } else {
            next[i] = nullptr;
        }
    }
}


// Destructor
// pre: the TrieNode exists
// post: the TrieNode is destroyed and memory is returned to the system
TrieNode::~TrieNode()
{
    for(size_t i = 0; i < sizeof(next)/sizeof(*next); i++) {
        delete next[i];
    }
}


// Assignment Operator
// pre: both this TrieNode and rhs exist
//post: this TrieNode gets assigned a copy of the parameter TrieNode
const TrieNode& TrieNode::operator=(const TrieNode& rhs)
{
    if(this == &rhs) {
        return *this;
    }
    TrieNode tmp(rhs);
    std::swap(item, tmp.item);
    std::swap(isEnd, tmp.isEnd);
    std::swap(next, tmp.next);
    return *this;
}

// Insert
// pre: str is a string of a word consisting of lowercase letters or the empty string
// post: Inserts str starting with the given TrieNode. Creates new
// TrieNodes as needed and sets the boolean flag on the last node to true.
void TrieNode::insert(const std::string& str)
{
    if(str != "") {
        size_t ind = (size_t) str[0] - 'a';
        bool flag = str.length() == 1;
        if (next[ind] == nullptr) {
            TrieNodePtr newPtr = new TrieNode(str[0], flag);
            next[ind] = newPtr;
        } else {
            next[ind]->item = str[0];
            if (flag) {
                next[ind]->isEnd = flag;
            }
        }
        if (str.length() == 1) {

        } else {
            next[ind]->insert(str.substr(1,str.length()));
        }
    }
}


// isWord
// pre: str is a string of a word consisting of lowercase letters or the empty string
// post: Returns true if str is in the sub-Trie starting at the given TrieNode, else returns false.
bool TrieNode::isWord(const std::string& str) const
{
    if (str.length() == 0) {
        return isEnd;
    }
    size_t ind = (size_t) (str[0] - 'a');
    if(next[ind] != nullptr) {
        return next[ind]->isWord(str.substr(1,str.length()));
    }
    return false;
}


// isPrefix
// pre: str is a string of a word consisting of lowercase letters or the empty string
// post: Returns true if pre is a prefix of a word in the sub-Trie
// starting at the given TrieNode, else returns false.
bool TrieNode::isPreFix(const std::string& str) const
{
    if (str.length() == 0) {
        return wordCount() > 0;
    }
    size_t ind = (size_t) (str[0] - 'a');
    if(next[ind] != nullptr) {
        return next[ind]->isPreFix(str.substr(1,str.length()));
    }
    return false;
}


// print
// pre: str is a string containing the letters of all ancestors of the given TrieNode
// post: Prints all the words in the given TrieNode
void TrieNode::print(const std::string& str) const
{
    if (isEnd) {
        std::cout << str << std::endl;
    }
    for(size_t i = 0; i < sizeof(next)/sizeof(*next); i++) {
        if(next[i] != nullptr) {
            next[i]->print(str + (char)('a' + i));
        }
    }
}


//wordCount
// post: Returns the number of words in the subTrie of the given TrieNode
size_t TrieNode::wordCount() const
{
    size_t total = 0;
    if (isEnd) {
        total++;
    }
    for(size_t i = 0; i < sizeof(next)/sizeof(*next); i++) {
        if(next[i] != nullptr) {
            total += next[i]->wordCount();
        }
    }
    return total;
}
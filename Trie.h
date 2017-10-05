#ifndef TRIE_H
#define TRIE_H
#include<string>
#include <cstddef>   // make gcc & CLion happy

#include "TrieNode.h"

class Trie
{
private:

    TrieNode* myRoot;

    std::string strToLow(const std::string &str) const;

public:

    Trie();

    Trie(const Trie& rhs);

    ~Trie();

    const Trie& operator=(const Trie& rhs);

    void insert(const std::string& word);

    void loadFromFile(const std::string& filename);

    bool isWord(const std::string& word) const;

    bool isPrefix(const std::string& pre) const;

    void print() const;

    size_t wordCount() const;
};

#endif

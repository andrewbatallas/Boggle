#ifndef TRIENODE_H
#define TRIENODE_H
#include<string>


class TrieNode
{
private:

    char item;

    bool isEnd;

    typedef TrieNode* TrieNodePtr;

    TrieNodePtr next[26];

public:

    TrieNode(char c, bool b);

    TrieNode(const TrieNode& rhs);

    ~TrieNode();

    const TrieNode& operator=(const TrieNode& rhs);

    void insert(const std::string& str);

    bool isWord(const std::string& str) const;

    bool isPreFix(const std::string& str) const;

    void print(const std::string& str) const;

    size_t wordCount() const;
};


#endif

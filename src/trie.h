#ifndef EUCL_TRIE
#define EUCL_TRIE

#include <iostream>

//This structure adopted to store strings consisted only of chars 'P', 'C', 'L', 'X', 'Y', 'N'.
#define TRIE_CHAR_SIZE 6

// A class to store a Trie node
class Trie
{
public:
    bool isLeaf;
    Trie* character[TRIE_CHAR_SIZE];
 
    Trie();
 
    void insert(std::string);
    bool deletion(Trie*&, std::string);
    bool search(std::string);
    bool haveChildren(Trie const*);
    size_t keyToPos(char key);
};

#endif /* EUCL_TRIE */

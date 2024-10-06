#include "trie.h"

using namespace std;

Trie::Trie()
{
    this->isLeaf = false;

    for (int i = 0; i < TRIE_CHAR_SIZE; i++)
    {
        this->character[i] = nullptr;
    }
}

// Iterative function to insert a key into a Trie
void Trie::insert(string key)
{
    // start from the root node
    Trie *curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // create a new node if the path doesn't exist
        size_t pos = keyToPos(key[i]);
        
        if (curr->character[pos] == nullptr)
        {
            curr->character[pos] = new Trie();
        }

        // go to the next node
        curr = curr->character[pos];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key)
{
    // return false if Trie is empty
    if (this == nullptr)
    {
        return false;
    }

    Trie *curr = this;
    for (int i = 0; i < key.length(); i++)
    {
        // go to the next node
        curr = curr->character[keyToPos(key[i])];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr)
        {
            return false;
        }
    }

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(Trie const *curr)
{
    for (int i = 0; i < TRIE_CHAR_SIZE; i++)
    {
        if (curr->character[i])
        {
            return true; // child found
        }
    }

    return false;
}

size_t Trie::keyToPos(char key)
{
    switch (key)
    {
    case 'P':
        return 0;
    case 'C':
        return 1;
    case 'L':
        return 2;
    case 'X':
        return 3;
    case 'Y':
        return 4;
    case 'N':
        return 5;
    }
    return -1;
}

// Recursive function to delete a key in the Trie
bool Trie::deletion(Trie *&curr, string key)
{
    // return if Trie is empty
    if (curr == nullptr)
    {
        return false;
    }

    // if the end of the key is not reached
    if (key.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)

        if (curr != nullptr &&
            curr->character[key[0]] != nullptr &&
            deletion(curr->character[key[0]], key.substr(1)) &&
            curr->isLeaf == false)
        {
            if (!haveChildren(curr))
            {
                delete curr;
                curr = nullptr;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr))
        {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else
        {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
        }
    }

    return false;
}
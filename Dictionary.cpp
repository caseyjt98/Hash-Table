


// Dictionary.cpp

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <iostream>
#include <utility>  // for swap
using namespace std;

const int NUM_BUCKETS = 49999;    // large prime number to reduce collisions

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl() {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
private:
    unsigned int myHashFnc(const string &toHash) const;
    list<string> m_words[NUM_BUCKETS];  // an array of linked lists, open hash table
};



void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    if ( ! word.empty())
    {
        int bucket = myHashFnc(word); // get proper bucket number
        // look-up linked list at proper bucket number and insert
        m_words[bucket].push_back(word);
    }
    
}

unsigned int DictionaryImpl::myHashFnc(const string &toHash) const
{
    
    unsigned int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101}; // list of prime numbers
 
    unsigned int hashValue = 1;
    
    for (int i=0;i<toHash.length(); i++)
        hashValue *= primes[toHash[i] - 'a'];       // get hash value by assigning each character a prime number and
    
    unsigned int bucketNum = hashValue % NUM_BUCKETS;    // use modulo to get valid bucket number within bounds of array
    return bucketNum;
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;
    
    removeNonLetters(letters);
    if (letters.empty())
        return;
    
    
    int bucket = myHashFnc(letters); // get proper bucket number
    list<string> currList = m_words[bucket];
    // traverse through linked list of anagrams
    for (list<string>::const_iterator wordp = currList.begin();
            wordp != currList.end(); wordp++)
    {
        string currWord = *wordp;
        if (currWord.length() == letters.length())  // word length of all valid anagrams must be the same
            callback(*wordp);
    }
    
   
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}




//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
 


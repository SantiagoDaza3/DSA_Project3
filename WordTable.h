#pragma once
#include "Word.h"
#include "Hashfunctions.h"
#include <vector>

class WordTable
{
    private://screen.blit();
    std::vector<Word> arr;//array containing every unique word in the dataset
    float load_factor;//if above 0.7, resize array
    int capacity;//sets capacity of the hash table
    int size;//number of elements inside

    public:
    //constructors
    WordTable();
    WordTable(int initial_cap);


    int Hashfunction_MMH3();
    //insertion functions
    void resize_arr();
    void insert(Word jojo, int option);
    void setLoadFactor();
    //traversal function
    Word search(const std::string& text, int option);
};

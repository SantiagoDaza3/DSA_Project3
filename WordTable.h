#pragma once
#include "Word.h"
#include "Hashfunctions.h"
#include <vector>
#include <queue>
#include <sstream>
class WordTable
{
    //private://screen.blit();
    public:
    std::vector<Word> arr;//array containing every unique word in the dataset
    float load_factor;//if above 0.7, resize array
    int capacity;//sets capacity of the hash table
    int size;//number of elements inside
    unsigned int num_of_collisions = 0;

    //public:
    //constructors
    WordTable();
    WordTable(int initial_cap);


    int Hashfunction_MMH3();
    //insertion functions
    void resize_arr(unsigned int option);
    void insert(Word jojo, int option);
    void setLoadFactor();


    //traversal function
    Word search(const std::string& text, int option);

    //queue functions
    struct combinedWord
    {
        Word* kin;
        float score;
        combinedWord(Word& jojo, unsigned int tag)
        {
            kin = &jojo;
            score = jojo.calculate_score(tag);
        }
    };

    struct compareScores
    {
        bool operator()(const combinedWord& lhs, const combinedWord& rhs) const
        {
            return lhs.score < rhs.score;
        }
    };
    //UI functions
    void contribute_to_dataset(std::string& passage, int emotiontag, int option);
    std::vector<float> passage_sentiment_analysis(const std::string& passage, int option);
    std::vector<float> word_analysis(std::string& word, int option);
    std::vector<Word*> emotion_analysis(int emotiontag);
};

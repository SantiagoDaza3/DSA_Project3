#pragma once
#include "Hashfunctions.h"
#include "Word.h"
#include <cmath>
#include <queue>
#include <sstream>
#include <vector>
class WordTable
{
private:                   //screen.blit();
    std::vector<Word> arr; //array containing every unique word in the dataset
    float load_factor;     //if above 0.7, resize array
    int capacity;          //sets capacity of the hash table
    int size;              //number of elements inside
    unsigned int num_of_collisions = 0;

public:
    //constructors
    WordTable();
    WordTable(int initial_cap);

    int Hashfunction_MMH3();
    //insertion functions
    void resize_arr(unsigned int option);
    void insert(Word jojo, int option);
    void setLoadFactor();

    //traversal function
    Word search(const std::string &text, int option);

    //queue functions
    struct combinedWord
    {
        Word *kin;
        float score;
        combinedWord(Word &jojo, unsigned int tag)
        {
            kin = &jojo;
            score = jojo.calculate_score(tag);
        }
    };

    struct compareScores
    {
        bool operator()(const combinedWord &lhs, const combinedWord &rhs) const
        {
            return lhs.score < rhs.score;
        }
    };

    //return functions
    float return_loadfactor() { return load_factor; }
    int return_capacity() { return capacity; }
    unsigned int return_collisions() { return num_of_collisions; }
    int return_size() { return size; }
    //UI functions
    void contribute_to_dataset(
        std::string &passage,
        int emotiontag,
        int option); //allows the user to insert a passage, tag with emotion, and has int option for which hashing function to use
    std::vector<float> passage_sentiment_analysis(
        const std::string &passage,
        int option); //takes a passage from the user's breaks it into words and calculates a score for it word by word and adds it together for all the emotions. The score is based on the number of times that emotion has been called for that word and what percent of the entire words use is for that emotion
    std::vector<float> word_analysis(
        const std::string &word,
        int option); //essentially returns the percentages of a word's emotion frequencies. Philadelphia is in 3 angry tweets, 1 happy tweet, it is 75% angry 25% happy
    std::vector<Word *> emotion_analysis(
        int emotiontag); //returns the top 10 words from any emotion, based on its emotion tag
    float passion_analysis(std::string &passage, int option);
};

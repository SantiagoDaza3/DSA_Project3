#pragma once
#include <string>
struct Word//each tweet's words separated by spaces are added to the dataset
{
    std::string word_name;
    unsigned int emotion_values[6] = {0,0,0,0,0,0};//tracks occurences of the word i.e. "Philadelphia" was used 3 times in an angry tweet and once in a joyous tweet. corresponds to[sadness, joy, love, anger, fear, surprise]
    unsigned int num_of_repeats = 0;//this is essentially how many times the word can be found in the dataset, useful for some calculations
    Word();
    Word(std::string _tweet, int tag);//base constructor, this is what you'll be using when inserting the first time
    void modify_value(int tag);
    float calculate_score(unsigned int emotiontag);
};
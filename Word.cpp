#include "Word.h"
Word::Word()
{
    word_name = "";
};

Word::Word(std::string _tweet, int tag)
{
    word_name = _tweet;
    emotion_values[tag] = 1;
    num_of_repeats += 1;
};

void Word::modify_value(int tag)
{
    emotion_values[tag] += 1;
    num_of_repeats += 1;
};
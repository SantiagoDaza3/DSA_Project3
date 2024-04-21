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
float Word::calculate_score(unsigned int emotiontag)
{
    if (num_of_repeats == 0)
    {
        return 0;
    }
    float fraction = static_cast<float>(emotion_values[emotiontag]) / num_of_repeats;
    return fraction * emotion_values[emotiontag];
};

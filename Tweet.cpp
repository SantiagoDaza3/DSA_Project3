#include "Tweet.h"

Tweet::Tweet()
{
    tweet = "";
    emotion = "";
}
Tweet::Tweet(std::string _tweet, int tag)
{
    tweet = _tweet;
    std::string emotionset[] = {"sadness", "joy", "love", "anger", "fear", "surprise"};
    std::string _emotion = emotionset[tag];
    emotion = _emotion;
}

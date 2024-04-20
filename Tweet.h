#pragma once
#include <string>

struct Tweet//each entry in the dataset has a tweet, and an emotion attached to it
{
    std::string tweet;
    std::string emotion;//pay attention to one thing, in the dataset emotions are tagged using integers from 0-5, you need to match them to their corresponding emotions i.e. tweet tagged with 1 is for joy
    Tweet();
    Tweet(std::string _tweet, int tag);//base constructor, this is what you'll be using

};
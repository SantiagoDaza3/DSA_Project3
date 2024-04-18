#pragma once
#include "Tweet.h"
#include <vector>

class TweetTable
{
    private://screen.blit();
    std::vector<Tweet> arr;
    std::string emotion;
    float load_factor;
    int capacity;
    int size;

    public:
    TweetTable()
    {
        arr.resize(1);
        load_factor = 0;
        capacity = 1;
        size = 0;
    };
    TweetTable(int initial_cap)
    {
        capacity = initial_cap;
        arr.resize(capacity);
        load_factor = 0;
        size = 0;
    };
    int HashFunction1();
    int Hashfunction2();

    void insert(std::string tweet, std::string emotion);

    void setLoadFactor(){load_factor = size/capacity;};
};



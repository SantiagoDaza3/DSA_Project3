
#pragma once
#include "Tweet.h"
#include <vector>
#include <cstdint>

class TweetTable
{
    private://screen.blit();
    std::vector<Tweet> arr;
    std::string emotion;
    float load_factor;
    int capacity;
    int size;

    public:
    TweetTable();
    TweetTable(int initial_cap);
    uint32_t Hashfunction_fnv1a(const std::string& str);
    int Hashfunction_MMH3();
    void resize_arr();
    void insert(Tweet jojo);
    Tweet search(const std::string& text);
    void setLoadFactor();
};



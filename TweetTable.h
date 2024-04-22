
#pragma once
#include "Hashfunctions.h"
#include "Tweet.h"
#include <vector>

class TweetTable
{
private:                    //screen.blit();
    std::vector<Tweet> arr; //contains every Tweet along with its emotion
    float load_factor;      //if above 0.7, resize
    int capacity;           //sets the number of buckets
    int size;               //how many elements in the array

public:
    TweetTable(); //default constructor, should just create a vector with a single empty element
    TweetTable(int initial_cap); //default constructor, sets the vector size to a certain amoutn
    int Hashfunction_MMH3();
    void resize_arr(int option);         //resizes array and rehashes every contained Tweet
    void insert(Tweet jojo, int option); //inserts tweet if it doesn't already exist
    Tweet search(
        const std::string &text,
        int option); //finds the element if it exists, IF THE ELEMENT IS NOT IN THE HASH TABLE, IT WILL RETURN A TWEET WITH
    void setLoadFactor(); //simply sets the value of load_factor, should automatically be called in insert
};

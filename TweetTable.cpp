#include "TweetTable.h"

TweetTable::TweetTable()
{
    arr.resize(1);
    load_factor = 0;
    capacity = 1;
    size = 0;
};
TweetTable::TweetTable(int initial_cap)
{
    capacity = initial_cap;
    arr.resize(capacity);
    load_factor = 0;
    size = 0;
};
void TweetTable::resize_arr(int option)
{
    std::vector<Tweet> temp_arr;
    for (int i = 0; i < capacity; i++) {
        if (arr[i].tweet != "") {
            temp_arr.push_back(arr[i]);
            arr[i] = Tweet();
        }
    }
    capacity *= 2;
    size = 0;
    arr.resize(capacity);
    for (int i = 0; i < temp_arr.size(); i++) {
        insert(temp_arr[i], option);
    }
    setLoadFactor();
}

void TweetTable::setLoadFactor()
{
    load_factor = size / capacity;
};

void TweetTable::insert(Tweet jojo, int option)
{
    std::string text = jojo.tweet;
    uint32_t hash;
    if (option == 1) {
        hash = Hashfunction_fnv1a(text);
    } else {
        hash = Hashfunction_mmh3(text);
    }
    unsigned int index = hash % capacity;
    unsigned int n = 0;
    bool while_condition = true;
    while ((index + n * n) < capacity) {
        unsigned int multiple = n * n;
        Tweet &in_array = arr[index + multiple];
        if (in_array.tweet == "") {
            arr[index] = jojo;
            size += 1;
            break;
        } else {
            if (in_array.tweet != jojo.tweet) {
                n += 1;
            } else if (in_array.tweet == jojo.tweet) {
                break;
            }
        }
    }
    setLoadFactor();
    if (load_factor >= 0.7) {
        resize_arr(option);
    }
};
Tweet TweetTable::search(const std::string &text, int option)
{
    uint32_t hash;
    if (option == 1) {
        hash = Hashfunction_fnv1a(text);
    } else {
        hash = Hashfunction_mmh3(text);
    }
    unsigned int index = hash % capacity;
    int n = 0;
    while ((index + n * n) < capacity) {
        Tweet &in_array = arr[index + n * n];
        if (in_array.tweet == "") {
            n += 1;
        } else {
            if (in_array.tweet == text) {
                return arr[index + n * n];
            } else if (in_array.tweet != text) {
                n += 1;
            }
        }
    }
    return Tweet();
};

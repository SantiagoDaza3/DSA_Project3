#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Tweet.h"

std::vector<Tweet> parse_entry(string file)
{
    std::string filename{file};
    std::ifstream input{filename};

    if (!input.is_open()) {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return; 
    }

    std::vector<std::vector<std::string>> csvRows;

    for (std::string line; std::getline(input, line);) {
        std::istringstream ss(std::move(line));
        std::vector<std::string> row;
        if (!csvRows.empty()) {
            // We expect each row to be as big as the first row
            row.reserve(csvRows.front().size());
        }
        // std::getline can split on other characters, here we use ','
        for (std::string value; std::getline(ss, value, ',');) {
        row.push_back(std::move(value));
        }
        csvRows.push_back(std::move(row));
    }

    std::vector<Tweet> tweets;
    for (int i = 1; i < csvRows.size(); i++) {
        std::string tweet = csvRows[i][1];
        int emotiontag = stoi(csvRows[i][2];
        Tweet obj(tweet, emotiontag);
        tweets.push_back(obj);
    }
    return tweets;
}

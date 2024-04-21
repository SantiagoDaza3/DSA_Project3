#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Tweet.h"
#include "TweetTable.h"
#include "WordTable.h"

TweetTable parse_entry(std::string file_name)
{
    std::string filename{file_name};
    std::ifstream input{filename};
    std::vector<std::vector<std::string>> csvRows;

    
    TweetTable bigboy(2000000);
    if (!input.is_open()) {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return bigboy;
    }

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

    for (int i = 1; i < csvRows.size(); i++) {
        std::string tweet = csvRows[i][1];
        int emotiontag = stoi(csvRows[i][2]);
        Tweet obj(tweet, emotiontag);
        bigboy.insert(obj);
    }
    return bigboy;
}
WordTable parse_entry_words(std::string file_name)
{
    std::string filename{file_name};
    std::ifstream input{filename};
    std::vector<std::vector<std::string>> csvRows;

    
    WordTable bigboy(5000000);
    if (!input.is_open()) {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return bigboy;
    }

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

    for (int i = 1; i < csvRows.size(); i++) {
        std::string tweet = csvRows[i][1];
        int emotiontag = stoi(csvRows[i][2]);

        std::istringstream iss(tweet);
        std::string word;
        while (std::getline(iss, word, ' ')) {
            Word obj(word, emotiontag);
            bigboy.insert(obj);
        }
    }
    return bigboy;
}
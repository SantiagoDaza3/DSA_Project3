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


std::vector<std::vector<std::string>> parsed_rows(std::string file_name)
{
    std::string filename{file_name};
    std::ifstream input{ filename };
    std::vector<std::vector<std::string>> csvRows;

    if (!input.is_open()) {
        std::cerr << "Couldn't read file: " << filename << "\n";
        return csvRows;
    }
    for (std::string line; std::getline(input, line);) {
        std::istringstream ss(std::move(line));
        std::vector<std::string> row;
        if (!csvRows.empty()) {
            row.reserve(csvRows.front().size());
        }
        for (std::string value; std::getline(ss, value, ',');) {
            row.push_back(std::move(value));
        }
        csvRows.push_back(std::move(row));
    }
    return csvRows;
}
TweetTable parse_entry(std::vector<std::vector<std::string>>& parsed_rows, unsigned int capacity, int option)
{    
    TweetTable bigboy(capacity);
    for (int i = 1; i < parsed_rows.size(); i++) {
        std::string tweet = parsed_rows[i][1];
        int emotiontag = stoi(parsed_rows[i][2]);
        Tweet obj(tweet, emotiontag);
        bigboy.insert(obj, option);
    }
    return bigboy;
}
WordTable parse_entry_words(std::vector<std::vector<std::string>>& parsed_rows, unsigned int capacity, int option)
{
    WordTable bigboy(capacity);

    for (int i = 1; i < parsed_rows.size(); i++) {
        std::string tweet = parsed_rows[i][1];
        int emotiontag = stoi(parsed_rows[i][2]);

        std::istringstream iss(tweet);
        std::string word;
        while (std::getline(iss, word, ' ')) {
            Word obj(word, emotiontag);
            bigboy.insert(obj, option);
        }
    }
    return bigboy;
}

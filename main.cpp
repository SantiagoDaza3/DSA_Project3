#include "mainwindow.h"
#include <QApplication>
#include "datasetparsing.h"
#pragma once

int main(int argc, char *argv[])
{
    std::vector<std::vector<std::string>> finisher = parsed_rows("../../text.csv");

    WordTable mmhTable = parse_entry_words(finisher, 200000, 0);

    WordTable FNVTable = parse_entry_words(finisher, 200000, 1);

    /*
        std::vector<std::vector<std::string>> finished = parsed_rows("text.csv");
        //you can put checkpoints before and after this code to track the execution time using chronos or whatever
        //checkpoint 1
        WordTable k = parse_entry_words(finished, 200000, 1);// 1 for fnv hash
        //checkpoint 2
        std::cout << k.return_size() << std::endl;
        std::cout << k.return_loadfactor() << std::endl;
        std::cout << k.return_capacity() << std::endl;
        std::cout << k.return_collisions() << std::endl;
        //checkpoint1

        //WordTable b = parse_entry_words(finished, 200000, 0);// 0 for MMH3 hash
        //std::cout << b.get_collisions() << std::endl;
        //checpoint 2

        finished.clear();//just deallocates the memory after it's not needed

        Word jo = k.search("i", 1);
        std::cout << jo.word_name << std::endl;
        std::cout << "sadness: " << jo.emotion_values[0] << std::endl;
        std::cout << "joy: " << jo.emotion_values[1] << std::endl;
        std::cout << "love: " << jo.emotion_values[2] << std::endl;
        std::cout << "anger: " << jo.emotion_values[3] << std::endl;
        std::cout << "fear: " << jo.emotion_values[4] << std::endl;
        std::cout << "surprise: " << jo.emotion_values[5] << std::endl;
        std::cout << "capacity: " << jo.num_of_repeats << std::endl;

        Word jo2 = k.search("the", 1);
        std::cout << jo2.word_name << std::endl;
        std::cout << "sadness: " << jo2.emotion_values[0] << std::endl;
        std::cout << "joy: " << jo2.emotion_values[1] << std::endl;
        std::cout << "love: " << jo2.emotion_values[2] << std::endl;
        std::cout << "anger: " << jo2.emotion_values[3] << std::endl;
        std::cout << "fear: " << jo2.emotion_values[4] << std::endl;
        std::cout << "surprise: " << jo2.emotion_values[5] << std::endl;
        std::cout << "capacity: " << jo2.num_of_repeats << std::endl;

        Word jo3 = k.search("feel", 1);
        std::cout << jo3.word_name << std::endl;
        std::cout << "sadness: " << jo3.emotion_values[0] << std::endl;
        std::cout << "joy: " << jo3.emotion_values[1] << std::endl;
        std::cout << "love: " << jo3.emotion_values[2] << std::endl;
        std::cout << "anger: " << jo3.emotion_values[3] << std::endl;
        std::cout << "fear: " << jo3.emotion_values[4] << std::endl;
        std::cout << "surprise: " << jo3.emotion_values[5] << std::endl;
        std::cout << "capacity: " << jo3.num_of_repeats << std::endl;

        Word jo4 = k.search("and", 1);
        std::cout << jo4.word_name << std::endl;
        std::cout << "sadness: " << jo4.emotion_values[0] << std::endl;
        std::cout << "joy: " << jo4.emotion_values[1] << std::endl;
        std::cout << "love: " << jo4.emotion_values[2] << std::endl;
        std::cout << "anger: " << jo4.emotion_values[3] << std::endl;
        std::cout << "fear: " << jo4.emotion_values[4] << std::endl;
        std::cout << "surprise: " << jo4.emotion_values[5] << std::endl;
        std::cout << "capacity: " << jo4.num_of_repeats << std::endl;
        std::vector<Word*> jojo = k.emotion_analysis(2);
        for (int i = 0; i < jojo.size(); i++)
        {
            std::cout << jojo[i]->word_name << std::endl;
        }

        //passage sentiment analysis plus passion analysis
        std::string test = "I went to the mall today";
        std::vector<float> mi = k.passage_sentiment_analysis(test, 1);
        std::cout << test << std::endl;
        for (int i = 0; i < 6; i++)
        {
            std::cout << mi[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Passion Analysis" << k.passion_analysis(test, 1) << std::endl;
    */
    QApplication a(argc, argv);
    MainWindow w;
    w.setFNVTable(FNVTable);
    w.setMMHTable(mmhTable);
    w.show();
    return a.exec();
}


#include "WordTable.h"


//default constructors
WordTable::WordTable()
{
    arr.resize(1);
    load_factor = 0;
    capacity = 1;
    size = 0;
};
WordTable::WordTable(int initial_cap)
{
    capacity = initial_cap;
    arr.resize(capacity);
    load_factor = 0;
    size = 0;
};

//insertion functions
void WordTable::resize_arr(unsigned int option)
{
    std::vector<Word> temp_arr;//I create a temporary vector to store all the stored Words and set those indices to an empty default Word Constructor
    for(int i = 0; i < capacity; i++)
    {
        if(arr[i].word_name != "")
        {
            temp_arr.push_back(arr[i]);
            arr[i] = Word();
        }
    }

    //increase capacity by two, set size to 0, and resize the empty array
    capacity *= 2;
    size = 0;
    num_of_collisions = 0;
    arr.resize(capacity);


    for(int i = 0; i < temp_arr.size(); i++)
    {
        insert(temp_arr[i], option);    //rehash and reinsert every value from the temporary vector
    }
}

void WordTable::setLoadFactor()
{
    load_factor = static_cast<float>(size)/capacity;
};

void WordTable::insert(Word jojo, int option)
{
    //set up initial values
    std::string text = jojo.word_name;
    uint32_t hash;//find the hash number
    if (option == 1) {
        hash = Hashfunction_fnv1a(text);
    }else{
        hash = Hashfunction_mmh3(text);
    }
    unsigned int index = hash % capacity;//relate the hash to capacity
    unsigned int n = 0;//will be used for PROBING


    while(arr[(index + n*n)%capacity].word_name != "" && arr[(index + n * n) % capacity].word_name != jojo.word_name)
    {  
        unsigned int multiple = n * n;
        Word& in_array = arr[(index + multiple)%capacity];//if the hash table is empty, each Word in the array is set using the default constructor, it is NOT NULL


        n += 1;               
    }
    if (arr[(index+(n*n))%capacity].word_name == "")//if the word at the index has word name "", that means it hasn't been assigned yet and can be used
    {
        arr[(index+(n*n))%capacity] = jojo;
        size += 1;
        if (n > 0)
        {
            num_of_collisions += 1;
        }
    }
    else if (arr[(index + (n * n))%capacity].word_name == jojo.word_name)//if the word already exists, we need to add it's emotion tag
    {
        //if the word already exists in the hash table, add 1 to whichever emotion its associated with in this current tweet
        for (int i = 0; i < 6; i++)//matrix addition i.e. {0,2,1} + {1,0,0} = {1,2,1}
        {
           arr[(index + (n*n))%capacity].emotion_values[i] += jojo.emotion_values[i];
        }
        arr[(index + (n*n))%capacity].num_of_repeats += 1;
    }    
    setLoadFactor();
    if(load_factor >= 0.7)
    {
        resize_arr(option);
    }
};


//traversal functions
Word WordTable::search(const std::string& text, int option)
{
    uint32_t hash;
    if (option == 1) {
        hash = Hashfunction_fnv1a(text);
    }else{
        hash = Hashfunction_mmh3(text);
    }
    unsigned int index = hash % capacity;
    int n = 0;
    while (arr[(index + n * n) % capacity].word_name != "" && arr[(index + n * n) % capacity].word_name != text)
    {
        unsigned int multiple = n * n;
        Word& in_array = arr[(index + multiple) % capacity];//if the hash table is empty, each Word in the array is set using the default constructor, it is NOT NULL


        n += 1;
    }
    if (arr[(index + (n * n)) % capacity].word_name == "")//if the word at the index has word name "", that means it hasn't been assigned yet and can be used
    {
        return Word();
    }
    else if (arr[(index + (n * n)) % capacity].word_name == text)//if the word already exists, we need to add it's emotion tag
    {
        return arr[(index + (n*n)) % capacity];
    }
    return Word();
};


//UI functions

std::vector<Word*> WordTable::emotion_analysis(int emotiontag)
{
    //find the top 10 most associated words of any emotion using a priority queue
    std::priority_queue<combinedWord, std::vector<combinedWord>, compareScores> pq;//this uses a special struct and bool to add Word Objects and their score and then sort them
    for(Word& a : arr)
    {
        if(a.word_name != "")
        {
            pq.push(combinedWord(a, emotiontag));
        }
    }
    std::vector<Word*> finalarr;//keep in mind this returns a vector of POINTERS, you will need to use ->
    for(int i = 0; i < 10; i++)
    {
        combinedWord jo = pq.top();
        //the below is a list of words that show up in every emotion tag's top 10 because they're used so frequently, i chose to just remove them
        while (jo.kin->word_name == "i" || jo.kin->word_name == "the" || jo.kin->word_name == "to" || jo.kin->word_name == "in" || jo.kin->word_name == "and" || jo.kin->word_name == "feel" || jo.kin->word_name == "and" || jo.kin->word_name == "a" || jo.kin->word_name == "of")
        {
            pq.pop();
            jo = pq.top();
        }
        finalarr.push_back(jo.kin);
        pq.pop();
    }
    return finalarr;
};

std::vector<float> WordTable::word_analysis(std::string& word, int option)
{
    Word searched = search(word, option);
    std::string text = searched.word_name;
    std::vector<float> emotion_percentages;
    for(int i = 0; i < 6; i++)
    {
        emotion_percentages.push_back(static_cast<float>(searched.emotion_values[i]) / searched.num_of_repeats);
    }
    return emotion_percentages;
};

std::vector<float> WordTable::passage_sentiment_analysis(const std::string& passage, int option)
{
    std::istringstream iss(passage);
    std::string word;
    std::vector<float> return_arr = {0, 0, 0, 0, 0, 0};
    while(std::getline(iss, word, ' '))
    {
        Word temp = search(word, option);
        std::vector<float> temp_arr;
        for(int i = 0; i < 6; i++)
        {
            if (temp.word_name == "i" || temp.word_name == "the" || temp.word_name == "to" || temp.word_name == "in" || temp.word_name == "and" || temp.word_name == "feel" || temp.word_name == "and" || temp.word_name == "a" || temp.word_name == "of")
            {
                temp_arr.push_back(0);
            }
            else
            {
                temp_arr.push_back(temp.calculate_score(i));
            }
        }
        for(int i = 0; i < 6; i++)
        {
            return_arr[i] += temp_arr[i];
        }
    }
    return return_arr;
};
void WordTable::contribute_to_dataset(std::string& passage, int emotiontag, int option)
{
    std::istringstream iss(passage);
    std::string word;
    while(std::getline(iss, word, ' '))
    {
        Word obj(word, emotiontag);
        insert(obj, option);
    }
};

float WordTable::passion_analysis(std::string& passage, int option)
{
    std::vector<float> passed = passage_sentiment_analysis(passage, option);
    float sum = 0.0, mean, variance = 0.0, stdDev = 0.0;
    int i = 0;
    for (int i = 0; i < 6; i++)
    {
        sum += passed[i];
    }
    mean = sum / 6;
    for (int i = 0; i < 6; i++)
    {
        stdDev += std::pow(passed[i] - mean, 2);
    }
    return std::sqrt(stdDev/6)/mean;
};

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
void WordTable::resize_arr()
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
    arr.resize(capacity);


    for(int i = 0; i < temp_arr.size(); i++)
    {
        insert(temp_arr[i]);//rehash and reinsert every value from the temporary vector
    }
}

void WordTable::setLoadFactor()
{
    load_factor = size/capacity;
};

void WordTable::insert(Word jojo)
{
    //set up initial values
    std::string text = jojo.word_name;
    uint32_t hash = Hashfunction_fnv1a(text);//find the hash number
    unsigned int index = hash % capacity;//relate the hash to capacity
    unsigned int n = 0;//will be used for PROBING


    while((index + n*n) < capacity)
    {  
        unsigned int multiple = n * n;
        Word& in_array = arr[index + multiple];//if the hash table is empty, each Word in the array is set using the default constructor, it is NOT NULL
        if(in_array.word_name == "")//if the word at the index has word name "", that means it hasn't been assigned yet and can be used
        {
            arr[index] = jojo;
            size += 1;
            break;
        }
        else
        {
            if(in_array.word_name != jojo.word_name)//if the word at the hash index isn't equal to the entered word_name, you will need to probe to the next one
            {
                n += 1;
            }
            else if(in_array.word_name == jojo.word_name)//if the word already exists, we need to add it's emotion tag
            {
                //if the word already exists in the hash table, add 1 to whichever emotion its associated with in this current tweet
                for(int i = 0; i < 6; i++)//matrix addition i.e. {0,2,1} + {1,0,0} = {1,2,1}
                {
                    in_array.emotion_values[i] += jojo.emotion_values[i];
                }
                in_array.num_of_repeats += 1;
                break;
            }
        }
    }
    setLoadFactor();
    if(load_factor >= 0.7)
    {
        resize_arr();
    }
};


//traversal functions
Word WordTable::search(const std::string& text)
{
    uint32_t hash = Hashfunction_fnv1a(text);
    unsigned int index = hash % capacity;
    int n = 0;
    while((index + n*n) < capacity)
    {
        Word& in_array = arr[index + n*n];
        if(in_array.word_name == "")
        {
            n += 1;
        }
        else
        {
            if(in_array.word_name == text)
            {
                return arr[index + n*n];
            }
            else if(in_array.word_name != text)
            {
                n += 1;
            }
        }
    }
    return Word();
};

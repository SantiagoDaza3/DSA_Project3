#include "Hashfunctions.h"

uint32_t Hashfunction_fnv1a(const std::string& str)
{
    uint32_t hash = 2166136261;
    for (char c : str) 
    {
        hash ^= static_cast<uint32_t>(c);
        hash *= 16777619;
    }
    return hash;
};

uint32_t Hashfunction_mmh3(const std::string& str)
{
    uint32_t hash = 0;
    MurmurHash3_x86_32(str.c_str(), str.size(), 0, &hash);
    return hash;
};

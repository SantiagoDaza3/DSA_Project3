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
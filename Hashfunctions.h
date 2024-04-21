#pragma once
#include <cstdint>
#include <string>
#include "MurmurHash3.h"

uint32_t Hashfunction_fnv1a(const std::string& str);
uint32_t Hashfunction_mmh3(const std::string& str);

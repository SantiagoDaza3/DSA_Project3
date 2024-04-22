#pragma once
#include "MurmurHash3.h"
#include <cstdint>
#include <string>

uint32_t Hashfunction_fnv1a(const std::string &str);
uint32_t Hashfunction_mmh3(const std::string &str);

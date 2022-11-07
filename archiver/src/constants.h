#pragma once

#include <string>
#include <unordered_map>

using Encoded = std::unordered_map<int16_t, std::string>;

using CntSymbols = std::unordered_map<int16_t, size_t>;

const size_t BITS = 9;

enum class ExtraSymbols { FILENAME_END = 256, ONE_MORE_FILE = 257, ARCHIVE_END = 258 };
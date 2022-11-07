#pragma once

#include "write_eight_bits.h"

#include <string>
#include <fstream>
#include <string_view>
#include <unordered_map>
#include <vector>

void WriteNumberOfSymbols(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight);

bool Comp(const std::pair<int16_t, std::string_view>& p1, const std::pair<int16_t, std::string_view>& p2);

void WriteSymbols(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight);

void WriteNumberOfLengths(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight);

void WriteSymbol(int16_t symb, std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight);

void WriteFileName(const std::string& file_name, std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight);

void WriteFileData(std::ofstream& fout, const std::string& file, const Encoded& encoded, WriteEightBits& eight);

void WriteEncoded(const std::string& file_name, const std::string& file, std::ofstream& fout, const Encoded& encoded,
                  WriteEightBits& eight, bool not_last_file);
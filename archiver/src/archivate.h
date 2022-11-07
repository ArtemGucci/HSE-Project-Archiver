#pragma once

#include "constants.h"
#include "CommandLineParser.h"
#include "write_eight_bits.h"

#include <fstream>
#include <string>

void CountSymbols(const std::string& file_name, std::ifstream& fin, CntSymbols& ump);

void AddExtraSymbols(CntSymbols& ump);

void Write(const std::string& file, std::ofstream& fout, WriteEightBits& eight, bool not_last_file, size_t& sum_sizes);

void Archivate(const CommandLineParser& parser);
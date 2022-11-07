#pragma once

#include "accumulator.h"
#include "CommandLineParser.h"
#include "node.h"
#include "read_nine_bits.h"

#include <fstream>

size_t ReadNumberOfSymbs(std::ifstream& fin, ReadNineBits& nines, Accumulator& accum);

std::vector<int16_t> ReadSymbs(std::ifstream& fin, ReadNineBits& nines, size_t number_of_symbs, Accumulator& accum);

std::vector<size_t> ReadLengths(std::ifstream& fin, ReadNineBits& nines, size_t number_of_symbs, Accumulator& accum);

Encoded MakeEncoded(const std::vector<int16_t>& symbs, const std::vector<size_t>& lengths);

Node* BuildBor(const Encoded& encoded);

std::string ReadFileName(Node* bor, std::ifstream& fin, Accumulator& accum);

bool WriteInFile(std::ofstream& fout, std::ifstream& fin, Node* bor, Accumulator& accum);

bool DeArchivateNewFile(std::ifstream& fin, Accumulator& accum);

void DeArchivate(const CommandLineParser& parser);
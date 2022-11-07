#include "write_encoded.h"

#include <cstring>
#include <iostream>

void WriteNumberOfSymbols(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight) {
    size_t size = encoded.size();
    for (ssize_t i = BITS - 1; i >= 0; --i) {
        if (eight.AddNewBit((size >> i) & 1)) {
            fout << eight.GetChar();
        }
    }
}

bool Comp(const std::pair<int16_t, std::string_view>& p1, const std::pair<int16_t, std::string_view>& p2) {
    if (p1.second.size() < p2.second.size()) {
        return true;
    }
    if (p1.second.size() > p2.second.size()) {
        return false;
    }
    return p1.first < p2.first;
}

void WriteSymbols(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight) {
    std::vector<std::pair<int16_t, std::string>> pairs;
    for (auto& i : encoded) {
        pairs.push_back({i.first, i.second});
    }
    std::sort(pairs.begin(), pairs.end(), Comp);
    for (auto& pair : pairs) {
        for (ssize_t i = BITS - 1; i >= 0; --i) {
            if (eight.AddNewBit((pair.first >> i) & 1)) {
                fout << eight.GetChar();
            }
        }
    }
}

void WriteNumberOfLengths(std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight) {
    size_t lengths[encoded.size() + 1];
    memset(lengths, 0, sizeof(lengths));
    for (auto& i : encoded) {
        ++lengths[i.second.size()];
    }
    size_t last = encoded.size();
    while (!lengths[last]) {  // Обязательно найдётся ненулевой элемент
        --last;
    }
    for (size_t i = 1; i <= last; ++i) {
        for (ssize_t j = BITS - 1; j >= 0; --j) {
            if (eight.AddNewBit((lengths[i] >> j) & 1)) {
                fout << eight.GetChar();
            }
        }
    }
}

void WriteSymbol(int16_t symb, std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight) {
    const std::string& code = encoded.at(symb);
    for (auto& i : code) {
        if (eight.AddNewBit(i - '0')) {
            fout << eight.GetChar();
        }
    }
}

void WriteFileName(const std::string& file_name, std::ofstream& fout, const Encoded& encoded, WriteEightBits& eight) {

    for (auto& c : file_name) {
        WriteSymbol(static_cast<int16_t>(c), fout, encoded, eight);
    }
    WriteSymbol(static_cast<int16_t>(ExtraSymbols::FILENAME_END), fout, encoded, eight);
}

void WriteFileData(std::ofstream& fout, const std::string& file, const Encoded& encoded, WriteEightBits& eight) {
    std::ifstream fin(file);
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла " << file << std::endl;
        exit(111);
    }
    char c = 0;  // todo char
    while (fin.get(c)) {
        int16_t c_16 = static_cast<int16_t>(c);
        if (c_16 < 0) {
            c_16 += 256;
        }
        WriteSymbol(c_16, fout, encoded, eight);
    }
    fin.close();
}

void WriteEncoded(const std::string& file_name, const std::string& file, std::ofstream& fout, const Encoded& encoded,
                  WriteEightBits& eight, bool not_last_file) {

    try {
        WriteNumberOfSymbols(fout, encoded, eight);
        WriteSymbols(fout, encoded, eight);
        WriteNumberOfLengths(fout, encoded, eight);
        WriteFileName(file_name, fout, encoded, eight);
        WriteFileData(fout, file, encoded, eight);

        if (not_last_file) {
            WriteSymbol(static_cast<int16_t>(ExtraSymbols::ONE_MORE_FILE), fout, encoded, eight);
        } else {
            WriteSymbol(static_cast<int16_t>(ExtraSymbols::ARCHIVE_END), fout, encoded, eight);
            if (!eight.GetBits()) {
                return;
            }
            if (eight.GetBits() != 8) {
                while (!eight.AddNewBit(false)) {
                }
            }
            fout << eight.GetChar();
        }
    } catch (...) {
        std::cout << "Ошибка выполнения программы" << std::endl;
        exit(111);
    }
}
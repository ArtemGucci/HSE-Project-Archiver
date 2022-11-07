#include "dearchivate.h"
#include "bitstring.h"

#include <iostream>

size_t ReadNumberOfSymbs(std::ifstream& fin, ReadNineBits& nines, Accumulator& accum) {
    char c = 0;
    while (fin.get(c)) {
        accum.AddChar(c);
        while (accum.CntBits()) {
            if (nines.AddNewBit(accum.GetBit())) {
                int16_t res = nines.GetSymb();
                return static_cast<size_t>(res);
            }
        }
    }
    std::cout << "Данный файл не подлежит декодированию" << std::endl;
    exit(111);
}

std::vector<int16_t> ReadSymbs(std::ifstream& fin, ReadNineBits& nines, size_t number_of_symbs, Accumulator& accum) {
    std::vector<int16_t> symbs;
    char c = 0;
    for (size_t i = 0; i < number_of_symbs; ++i) {
        int16_t res = -1;
        while (true) {
            while (accum.CntBits()) {
                if (nines.AddNewBit(accum.GetBit())) {
                    res = nines.GetSymb();
                    symbs.push_back(res);
                    break;
                }
            }
            if (res != -1) {
                break;
            }
            if (!fin.eof()) {
                fin.get(c);
                accum.AddChar(c);
            } else {
                std::cout << "Данный файл не подлежит декодированию" << std::endl;
                exit(111);
            }
        }
    }
    if (symbs.size() != number_of_symbs) {
        std::cout << "Данный файл не подлежит декодированию" << std::endl;
        exit(111);
    }
    return symbs;
}

std::vector<size_t> ReadLengths(std::ifstream& fin, ReadNineBits& nines, size_t number_of_symbs, Accumulator& accum) {
    std::vector<size_t> lengths;
    char c = 0;
    while (number_of_symbs) {
        while (true) {
            while (accum.CntBits() and number_of_symbs) {
                if (nines.AddNewBit(accum.GetBit())) {
                    int16_t res = nines.GetSymb();
                    lengths.push_back(static_cast<size_t>(res));
                    number_of_symbs -= lengths.back();
                }
            }
            if (!number_of_symbs) {
                break;
            }
            if (!fin.eof()) {
                fin.get(c);
                accum.AddChar(c);
            } else {
                std::cout << "Данный файл не подлежит декодированию" << std::endl;
                exit(111);
            }
        }
    }
    return lengths;
}

Encoded MakeEncoded(const std::vector<int16_t>& symbs, const std::vector<size_t>& lengths) {
    Encoded encoded;
    size_t i = 0;
    BitString cur;
    size_t last_length = 0;
    for (size_t j = 0; j < lengths.size(); ++j) {
        for (size_t g = 0; g < lengths[j]; ++g) {
            if (cur.Empty()) {
                cur.Assign(j + 1, '0');
                encoded[symbs[i++]] = cur.GetString();
            } else {
                cur = (++cur) << (j - last_length);
                encoded[symbs[i++]] = cur.GetString();
            }
            last_length = j;
        }
    }
    return encoded;
}

Node* BuildBor(const Encoded& encoded) {
    Node* bor = new Node(-1, 0, nullptr, nullptr);
    for (auto& symb : encoded) {
        bor->AddNewBitString(symb.second, symb.first);
    }
    return bor;
}

std::string ReadFileName(Node* bor, std::ifstream& fin, Accumulator& accum) {
    char c = 0;
    Node* cur_node = bor;
    std::string name;
    while (true) {
        while (accum.CntBits() and cur_node->GetSymb() == -1) {
            bool bit = accum.GetBit();
            cur_node = cur_node->Go(bit);
        }
        int16_t symb = cur_node->GetSymb();
        if (symb != -1) {
            cur_node = bor;
            if (symb == static_cast<int16_t>(ExtraSymbols::FILENAME_END)) {
                return name;
            }
            name += static_cast<char>(symb);
        } else {
            if (!fin.eof()) {
                fin.get(c);
                accum.AddChar(c);
            } else {
                std::cout << "Данный файл не подлежит декодированию" << std::endl;
                exit(111);
            }
        }
    }
    return name;
}

bool WriteInFile(std::ofstream& fout, std::ifstream& fin, Node* bor, Accumulator& accum) {
    char c = 0;
    Node* cur_node = bor;
    while (true) {
        while (accum.CntBits() and cur_node->GetSymb() == -1) {
            bool bit = accum.GetBit();
            cur_node = cur_node->Go(bit);
        }
        int16_t symb = cur_node->GetSymb();
        if (symb != -1) {
            cur_node = bor;
            if (symb == static_cast<int16_t>(ExtraSymbols::ONE_MORE_FILE)) {
                return false;
            }
            if (symb == static_cast<int16_t>(ExtraSymbols::ARCHIVE_END)) {
                return true;
            }
            fout << static_cast<char>(symb);
        } else {
            if (!fin.eof()) {
                fin.get(c);
                accum.AddChar(c);
            } else {
                std::cout << "Данный файл не подлежит декодированию" << std::endl;
                exit(111);
            }
        }
    }
    return false;
}

bool DeArchivateNewFile(std::ifstream& fin, Accumulator& accum) {
    ReadNineBits nines;
    size_t number_of_symbs = ReadNumberOfSymbs(fin, nines, accum);
    std::vector<int16_t> symbs = ReadSymbs(fin, nines, number_of_symbs, accum);
    std::vector<size_t> lengths = ReadLengths(fin, nines, number_of_symbs, accum);
    Encoded encoded = MakeEncoded(symbs, lengths);
    Node* bor = BuildBor(encoded);
    std::string file_name = ReadFileName(bor, fin, accum);

    std::ofstream fout(file_name);
    if (!fout.is_open()) {
        std::cout << "Ошибка открытия файла " << file_name << std::endl;
        exit(111);
    }

    std::cout << "Достаём файл " << file_name << std::endl;

    bool is_last_file = WriteInFile(fout, fin, bor, accum);
    fout.close();
    delete bor;
    return is_last_file;
}

void DeArchivate(const CommandLineParser& parser) {
    std::ifstream fin(parser.GetArchiveName());
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла " << parser.GetArchiveName() << std::endl;
        exit(111);
    }
    std::cout << "Деархивация началась" << std::endl;

    Accumulator accum;
    while (!fin.eof()) {
        try {
            if (DeArchivateNewFile(fin, accum)) {
                break;
            }
        } catch (...) {
            std::cout << "Ошибка выполнения программы" << std::endl;
            exit(111);
        }
    }
    fin.close();
    std::cout << "Деархивация завершена" << std::endl;
}
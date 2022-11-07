#include "archivate.h"
#include "haffman.h"
#include "write_encoded.h"

#include <filesystem>
#include <iostream>

void CountSymbols(const std::string& file_name, std::ifstream& fin, CntSymbols& ump) {
    char c = 0;
    while (fin.get(c)) {
        int16_t c_16 = static_cast<int16_t>(c);
        if (c_16 < 0) {
            c_16 += 256;
        }
        ++ump[c_16];
    }
    for (auto& i : file_name) {
        ++ump[static_cast<int16_t>(i)];
    }
}

void AddExtraSymbols(CntSymbols& ump) {
    ++ump[static_cast<int16_t>(ExtraSymbols::FILENAME_END)];
    ++ump[static_cast<int16_t>(ExtraSymbols::ONE_MORE_FILE)];
    ++ump[static_cast<int16_t>(ExtraSymbols::ARCHIVE_END)];
}

void Write(const std::string& file, std::ofstream& fout, WriteEightBits& eight, bool not_last_file, size_t& sum_sizes) {
    std::ifstream fin(file);
    if (!fin.is_open()) {
        std::cout << "Ошибка открытия файла " << file << std::endl;
        exit(111);
    }
    std::string file_name = std::filesystem::path(file).filename();
    sum_sizes += std::filesystem::file_size(file);
    std::cout << "Добавление файла " << file_name << " в архив" << std::endl;
    CntSymbols ump;
    CountSymbols(file_name, fin, ump);
    AddExtraSymbols(ump);
    Encoded encoded = Haffman(ump);
    WriteEncoded(file_name, file, fout, encoded, eight, not_last_file);
    fin.close();
}

std::string MakeRightMeasure(size_t value) {
    std::stringstream ss;
    if (value >= (1 << 30)) {
        ss << std::setprecision(1) << std::fixed << static_cast<double>(value) / (1 << 30) << 'G';
    } else if (value >= (1 << 20)) {
        ss << std::setprecision(1) << std::fixed << static_cast<double>(value) / (1 << 20) << 'M';
    } else if (value >= (1 << 10)) {
        ss << std::setprecision(1) << std::fixed << static_cast<double>(value) / (1 << 10) << 'K';
    } else {
        ss << value << 'B';
    }
    std::string str;
    ss >> str;
    return str;
}

void Archivate(const CommandLineParser& parser) {
    try {
        WriteEightBits eight;
        std::ofstream fout(parser.GetArchiveName());
        if (!fout.is_open()) {
            std::cout << "Ошибка открытия файла " << parser.GetArchiveName() << std::endl;
            exit(111);
        }
        std::cout << "Архивация началась" << std::endl;

        size_t sum_sizes = 0;
        for (size_t i = 0; i < parser.GetNumberOfFiles(); ++i) {
            try {
                Write(parser[i], fout, eight, (i != parser.GetNumberOfFiles() - 1), sum_sizes);
            } catch (...) {
                std::cout << "Ошибка выполнения программы" << std::endl;
                exit(111);
            }
        }
        fout.close();

        size_t archive_size = std::filesystem::file_size(parser.GetArchiveName());

        std::cout << "Архивация завершена" << std::endl;
        std::cout << "Суммарный размер файлов " << MakeRightMeasure(sum_sizes) << std::endl;
        std::cout << "Размер архива " << MakeRightMeasure(archive_size) << std::endl;
        std::cout << "Сжатие " << std::setprecision(1) << std::fixed
                  << static_cast<double>(archive_size) / static_cast<double>(sum_sizes) * 100 << '%' << std::endl;
    } catch (...) {
        std::cout << "Ошибка выполнения программы" << std::endl;
        exit(111);
    }
}
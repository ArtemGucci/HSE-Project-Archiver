#pragma once

#include <vector>
#include <string>

class CommandLineParser {
public:
    CommandLineParser() = default;
    CommandLineParser(int argc, char* argv[]);

    bool Correct() const;
    bool IsArchivate() const;
    bool IsDearchivate() const;

    std::string& operator[](size_t index);
    const std::string& operator[](size_t index) const;

    const std::string& GetArchiveName() const;
    size_t GetNumberOfFiles() const;

protected:
    bool correct_ = true;
    size_t number_of_files_ = 0;
    char flag_ = 0;
    std::string archive_name_;
    std::vector<std::string> files_;
};
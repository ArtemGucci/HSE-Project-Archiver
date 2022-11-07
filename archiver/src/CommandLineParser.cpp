#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int argc, char* argv[]) {
    if (argc == 1) {
        correct_ = false;
        return;
    }
    auto s = std::string_view(argv[1]);
    if (s != "-c" and s != "-d" and s != "-h") {
        correct_ = false;
        return;
    }
    flag_ = s[1];
    if (flag_ == 'h') {
        return;
    }
    if (argc == 2) {
        correct_ = false;
        return;
    }
    archive_name_ = argv[2];
    if (flag_ == 'd') {
        return;
    }
    if (argc == 3) {
        correct_ = false;
        return;
    }
    number_of_files_ = argc - 3;
    files_.resize(number_of_files_);
    for (size_t i = 0; i < number_of_files_; ++i) {
        files_[i] = std::string(argv[i + 3]);
    }
}
bool CommandLineParser::Correct() const {
    return correct_;
}
bool CommandLineParser::IsArchivate() const {
    return flag_ == 'c';
}
bool CommandLineParser::IsDearchivate() const {
    return flag_ == 'd';
}
const std::string& CommandLineParser::GetArchiveName() const {
    return archive_name_;
}
std::string& CommandLineParser::operator[](size_t index) {
    return files_[index];
}
const std::string& CommandLineParser::operator[](size_t index) const {
    return files_[index];
}
size_t CommandLineParser::GetNumberOfFiles() const {
    return number_of_files_;
}

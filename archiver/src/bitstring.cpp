#include "bitstring.h"

BitString::BitString(size_t cnt, char c) {
    str_.assign(cnt, c);
}

BitString& BitString::operator<<(size_t k) {
    for (size_t i = 0; i < k; ++i) {
        str_ += '0';
    }
    return *this;
}

BitString& BitString::operator++() {
    ssize_t ind = static_cast<ssize_t>(GetSize()) - 1;
    while (ind >= 0) {
        if (str_[ind] == '0') {
            str_[ind] = '1';
            for (size_t i = ind + 1; i < GetSize(); ++i) {
                str_[i] = '0';
            }
            break;
        }
        --ind;
    }
    if (ind < 0) {
        for (size_t i = 0; i < GetSize(); ++i) {
            str_[i] = '0';
        }
        str_ = '1' + str_;
    }
    return *this;
}

size_t BitString::GetSize() const {
    return str_.size();
}

bool BitString::Empty() const {
    return !GetSize();
}

void BitString::Assign(size_t cnt, char c) {
    str_.assign(cnt, c);
}
const std::string& BitString::GetString() const {
    return str_;
}
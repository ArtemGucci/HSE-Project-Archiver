#include "write_eight_bits.h"

bool WriteEightBits::AddNewBit(bool bit) {
    capacity_ = (capacity_ << 1) + bit;
    ++cnt_bits_;
    if (cnt_bits_ == 8) {
        return true;
    }
    return false;
}

char WriteEightBits::GetChar() {
    cnt_bits_ = 0;
    char res = static_cast<char>(capacity_);
    capacity_ = 0;
    return res;
}

size_t WriteEightBits::GetBits() const {
    return cnt_bits_;
}
#include "read_nine_bits.h"

bool ReadNineBits::AddNewBit(bool bit) {
    capacity_ = (capacity_ << 1) + bit;
    ++cnt_bits_;
    if (cnt_bits_ == 9) {
        return true;
    }
    return false;
}
int16_t ReadNineBits::GetSymb() {
    cnt_bits_ = 0;
    int16_t res = capacity_;
    capacity_ = 0;
    return res;
}
size_t ReadNineBits::GetBits() const {
    return cnt_bits_;
}
int16_t ReadNineBits::AddNewChar(char k) {
    int16_t res = -1;
    for (ssize_t i = BITS - 1; i >= 0; --i) {
        if (AddNewBit((k >> i) & 1)) {
            res = GetSymb();
        }
    }
    return res;
}

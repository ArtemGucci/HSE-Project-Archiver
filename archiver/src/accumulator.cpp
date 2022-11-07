#include "accumulator.h"

void Accumulator::AddBit(bool bit) {
    bits_ = (bits_ << 1) + bit;
    ++cnt_bits_;
}
void Accumulator::AddChar(char c) {
    for (ssize_t i = BITS - 2; i >= 0; --i) {
        AddBit((c >> i) & 1);
    }
}
size_t Accumulator::CntBits() const {
    return cnt_bits_;
}
bool Accumulator::GetBit() {
    if (!cnt_bits_) {
        return false;
    }
    bool res = bits_ & (1 << (cnt_bits_ - 1));
    bits_ &= (1 << (cnt_bits_ - 1)) - 1;
    --cnt_bits_;
    return res;
}
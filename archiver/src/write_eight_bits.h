#pragma once

#include "constants.h"

class WriteEightBits {
public:
    bool AddNewBit(bool bit);

    char GetChar();

    size_t GetBits() const;

protected:
    int16_t capacity_ = 0;
    size_t cnt_bits_ = 0;
};
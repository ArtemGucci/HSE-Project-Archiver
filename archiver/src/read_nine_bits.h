#pragma once

#include "constants.h"

class ReadNineBits {
public:
    int16_t AddNewChar(char k);

    bool AddNewBit(bool bit);

    int16_t GetSymb();

    size_t GetBits() const;

protected:
    int16_t capacity_ = 0;
    size_t cnt_bits_ = 0;
};
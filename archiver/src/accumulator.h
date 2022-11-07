#pragma once

#include "constants.h"

#include <cstddef>
#include <cstdint>

class Accumulator {

public:
    void AddBit(bool bit);

    void AddChar(char c);

    size_t CntBits() const;

    bool GetBit();

protected:
    int16_t bits_ = 0;
    size_t cnt_bits_ = 0;
};
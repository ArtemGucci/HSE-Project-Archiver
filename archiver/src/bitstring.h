#pragma once

#include <string>

class BitString {
public:
    BitString() = default;
    BitString(const std::string& str) : str_(str) {
    }
    BitString(size_t cnt, char c);

    BitString& operator<<(size_t k);

    BitString& operator++();

    size_t GetSize() const;
    const std::string& GetString() const;

    bool Empty() const;

    void Assign(size_t cnt, char c);

protected:
    std::string str_;
};

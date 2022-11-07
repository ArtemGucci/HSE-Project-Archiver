#pragma once

#include <string>

class Node {
public:
    Node() = default;
    Node(int16_t symb, size_t cnt, Node* left, Node* right);
    ~Node();

    int16_t GetSymb() const;
    size_t GetCnt() const;
    std::pair<Node*, Node*> GetChildren() const;

    void AddNewBitString(const std::string& s, int16_t symb);

    Node* Go(bool bit);

protected:
    size_t cnt_ = 0;
    int16_t symb_ = 0;
    Node *left_ = nullptr, *right_ = nullptr;
};

struct CompareRefs {
    bool operator()(const Node* const a, const Node* const b) const;
};
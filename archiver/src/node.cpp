#include "node.h"

Node::Node(int16_t symb, size_t cnt, Node* left, Node* right) {
    symb_ = symb;
    left_ = left;
    right_ = right;
    cnt_ = cnt;
}

Node::~Node() {
    delete left_;
    delete right_;
}

int16_t Node::GetSymb() const {
    return symb_;
}

size_t Node::GetCnt() const {
    return cnt_;
}

std::pair<Node*, Node*> Node::GetChildren() const {
    return {left_, right_};
}
void Node::AddNewBitString(const std::string& s, int16_t symb) {
    Node* cur = this;
    for (auto& i : s) {
        if (i == '0') {
            if (!cur->left_) {
                cur->left_ = new Node(-1, 0, nullptr, nullptr);
            }
            cur = cur->left_;
        } else {
            if (!cur->right_) {
                cur->right_ = new Node(-1, 0, nullptr, nullptr);
            }
            cur = cur->right_;
        }
    }
    cur->symb_ = symb;
}
Node* Node::Go(bool bit) {
    if (bit and right_) {
        return right_;
    }
    if (!bit and left_) {
        return left_;
    }
    return this;
}

bool CompareRefs::operator()(const Node* const a, const Node* const b) const {
    if (a->GetCnt() > b->GetCnt()) {
        return true;
    }
    if (a->GetCnt() < b->GetCnt()) {
        return false;
    }
    return a->GetSymb() > b->GetSymb();
}

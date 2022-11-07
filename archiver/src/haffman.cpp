#include "haffman.h"

void Dfs(Node* node, std::vector<std::pair<size_t, int16_t>>& pairs, size_t depth) {
    std::pair<Node*, Node*> p = node->GetChildren();
    if (p.first) {
        Dfs(p.first, pairs, depth + 1);
        Dfs(p.second, pairs, depth + 1);
    } else {
        pairs.push_back({depth, node->GetSymb()});
    }
}

Encoded MakeCanonicalCodes(Node* node) {
    std::vector<std::pair<size_t, int16_t>> pairs;
    Dfs(node, pairs);  // обходит dfs-ом бор и добавляет пары (длина кода, символ)
    delete node;
    std::sort(pairs.begin(), pairs.end());
    Encoded encoded;
    BitString cur(pairs[0].first, '0');
    encoded[pairs[0].second] = cur.GetString();
    for (size_t i = 1; i < pairs.size(); ++i) {
        cur = (++cur) << (pairs[i].first - pairs[i - 1].first);
        encoded[pairs[i].second] = cur.GetString();
    }
    return encoded;
}

Encoded Haffman(const CntSymbols& cnt_symbols) {
    std::priority_queue<Node*, std::vector<Node*>, CompareRefs> pq;
    for (auto& symb : cnt_symbols) {
        pq.push(new Node(symb.first, symb.second, nullptr, nullptr));
    }
    while (pq.size() > 1) {
        Node* first = pq.top();
        pq.pop();
        Node* second = pq.top();
        pq.pop();
        Node* parent =
            new Node(std::min(first->GetSymb(), second->GetSymb()), first->GetCnt() + second->GetCnt(), first, second);
        pq.push(parent);
    }
    if (pq.empty()) {
        return {};
    }
    Encoded encoded = MakeCanonicalCodes(pq.top());
    return encoded;
}
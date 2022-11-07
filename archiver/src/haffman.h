#pragma once

#include "bitstring.h"
#include "constants.h"
#include "node.h"

#include <queue>

void Dfs(Node* node, std::vector<std::pair<size_t, int16_t>>& pairs, size_t depth = 0);

Encoded MakeCanonicalCodes(Node* node);

Encoded Haffman(const CntSymbols& cnt_symbols);
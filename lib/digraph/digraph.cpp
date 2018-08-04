//
// Created by 黄嘉华 on 2018/7/29.
//

#include <cstddef>
#include "../../include/internal/digraph.h"

namespace jregex_util {
size_t digraph::vertex() const {
    return V;
}

size_t digraph::edge() const {
    return E;
}

digraph::digraph(size_t v): V(v), E(0), adj(v, Bag()) {
}


digraph::Bag &digraph::adjacent(size_t v) {
    return adj[v];
}

void digraph::inc_weight(const size_t from, const size_t to) {
    for (auto& e : adj[from])
        if (e.index == to)
            e.weight++;
}

void digraph::dec_weight(const size_t from, const size_t to) {
    for (auto& e : adj[from])
        if (e.index == to)
            e.weight--;
}

void digraph::reset_weight() {
    for (auto& b : adj)
        for (node& n : b)
            n.weight = n.backup;
}
} // namespace jregex_util

//
// Created by 黄嘉华 on 2018/7/29.
//

#include "../../include/internal/dfs.h"

namespace jregex_util {
dfs::dfs(digraph &g, size_t src) : is_marked(g.vertex(), false) {
    search(g, src);
}

bool dfs::marked(const size_t v) const {
    return is_marked[v];
}

void dfs::search(digraph &g, const size_t v) {
    is_marked[v] = true;
    digraph::Bag &bag = g.adjacent(v);
    for (digraph::node &w : bag)
        if (!is_marked[w.index]) {
            bool enable = false;
            if (w.weight <= 0)
                enable = true;

            if (w.index < v)
                w.weight++;
            else if (w.index > v)
                w.weight--;

            if (enable)
                search(g, w.index);
        }
}
} // namespace jregex_util


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

dfs::dfs(digraph &g, std::forward_list<size_t> &c) : is_marked(g.vertex(), false) {
    for (size_t s : c)
        if (!is_marked[s])
            search(g, s);
}

void dfs::reset(digraph &g, std::forward_list<size_t> &c) {
    is_marked.resize(g.vertex());
    for (int i = 0; i < is_marked.size(); ++i)
        is_marked[i] = false;
    for (size_t s : c)
        if (!is_marked[s])
            search(g, s);
}
} // namespace jregex_util


//
// Created by 黄嘉华 on 2018/7/29.
//

#ifndef GRAPH_DFS_H
#define GRAPH_DFS_H

#include "digraph.h"

namespace jregex_util {
class dfs {
private:
    std::vector<bool> is_marked;

    void search(digraph &g, const size_t v);

public:
    dfs(digraph &g, size_t src);

    dfs(digraph &g, std::forward_list<size_t> &c) : is_marked(g.vertex(), false) {
        for (size_t s : c)
            if (!is_marked[s])
                search(g, s);
    }

    void reset(digraph &g, std::forward_list<size_t> &c) {
        is_marked.resize(g.vertex());
        for (int i = 0; i < is_marked.size(); ++i)
            is_marked[i] = false;
        for (size_t s : c)
            if (!is_marked[s])
                search(g, s);
    }


    bool marked(const size_t v) const;
};
} // namespace jregex_util


#endif //GRAPH_DFS_H

//
// Created by 黄嘉华 on 2018/7/29.
//

#ifndef GRAPH_DIGRAPH_H
#define GRAPH_DIGRAPH_H


#include <cstddef>
#include <forward_list>
#include <vector>


namespace jregex_util {
class digraph {
public:
    struct node {
        size_t index;
        long long weight;
        const long long backup;
        node(size_t i, long long w): index(i), weight(w), backup(w) {}
        node(size_t i): index(i), weight(0), backup(0) {}
    };
    // type def
    typedef std::forward_list<node> Bag;
private:

    // private field
    const size_t V;
    size_t E;
    std::vector<Bag> adj;

public:
    // constructor
    explicit digraph(size_t v);

    // attributes
    size_t vertex() const;
    size_t edge() const;

    void inc_weight(const size_t from, const size_t to);
    void dec_weight(const size_t from, const size_t to);

    void reset_weight();

    // adj bag
    Bag& adjacent(size_t v);
};
} // namespace jregex_util


#endif //GRAPH_DIGRAPH_H

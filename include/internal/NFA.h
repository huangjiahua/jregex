//
// Created by 黄嘉华 on 2018/7/30.
//

#ifndef JHREGEX_NFA_H
#define JHREGEX_NFA_H


#include <string>
#include <sstream>
#include <stack>
#include <algorithm>
#include "digraph.h"
#include "dfs.h"
#include <limits>


namespace jregex_util {
class NFA {
private:
    std::string re;
    digraph graph;
    size_t states;
    std::vector<size_t> jump;
    std::vector<std::pair<size_t, size_t>> square_ranges;

    size_t parse_set(std::stack<size_t> &sset, const size_t i); // NOLINT
    size_t switch_to_complement(const size_t i, const size_t left_edge); // NOLINT
    void closure_transit(char c, size_t left, size_t right);

    size_t parse_cluster(std::stack<size_t> &ops, const size_t i);// NOLINT
    static inline bool transit_to_next(char c);

    size_t find_range(const std::vector<std::pair<size_t, size_t>> &square_ranges,
                      const size_t v);// NOLINT
    bool in_complement_set(std::pair<size_t, size_t> p);

    std::pair<size_t, size_t> find_set_range(const std::forward_list<size_t> &ranges,
                                             const size_t v);// NOLINT
    bool generally_equal(const size_t v, const char in_txt);// NOLINT
    bool equal_to_char_in_set(const std::pair<size_t, size_t> p, char in_txt);// NOLINT

    std::pair<long long, long long> parse_config(size_t left, size_t right);

    static std::pair<long long, long long> parse_range(std::string str);

    bool is_escape(size_t i);

    bool escape_equal(char c, char e, bool inset = true);


public:
    NFA(const std::string &regexp);// NOLINT
    bool recognize(const std::string &txt);

    std::pair<bool, std::string::size_type>
    search(const std::string &txt, const std::string::size_type start); // NOLINT
};
}



#endif //JHREGEX_NFA_H

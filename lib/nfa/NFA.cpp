//
// Created by 黄嘉华 on 2018/7/31.
//
#include "NFA.h"


namespace jregex_util {
NFA::NFA(const std::string &regexp) : re(regexp), states(regexp.size()),
                                      graph(regexp.size() + 1),
                                      jump(regexp.size(), 1) {
    std::stack<size_t> ops; // for ( ) and |
    std::stack<size_t> sset; // for [ ] and ^
    for (size_t i = 0; i < states; i++) {
        size_t lp = i;


        if (re[i] == '[' ||  // handle specific set
            (!sset.empty() && re[i] != ']' && re[i] != '^')) {
            sset.push(i);
            if (re[i] == '\\') i++;
            continue; // the operator in the set is not related to that outside of the set
        } else if (!sset.empty() && re[i] == '^') {
            i = switch_to_complement(i, sset.top()) - 1; // find '['
            continue;
        } else if (!sset.empty() && re[i] == ']') { // reach the end of the set
            lp = parse_set(sset, i);
        }

        if (re[i] == '\\') {
            jump[i] = 2;
            ++i;
            if (i < states - 1) {
                closure_transit(re[i + 1], lp, i + 1);
            }
            continue;
        }

        if (re[i] == '(' || re[i] == '|') // handle parentheses, ors
            ops.push(i);
        else if (re[i] == ')') {
            lp = parse_cluster(ops, i);
        }


        if (i < states - 1) { // handle closures
            closure_transit(re[i + 1], lp, i + 1);
        }

        if (transit_to_next(re[i]))
            graph.add_edge(i, i + 1);
    }
}

size_t NFA::parse_set(std::stack<size_t> &sset, const size_t i) {
    size_t lp; // the index of '['
    std::stack<size_t> elements;
    while (re[sset.top()] != '[') {
        size_t element = sset.top();
        sset.pop();
        jump[element] = i - element;
        elements.push(element);
    } // reach '['

    lp = sset.top();
    sset.pop();

    while (!elements.empty()) {
        graph.add_edge(lp, elements.top());
        elements.pop();
    }
    return lp;
}

size_t NFA::parse_cluster(std::stack<size_t> &ops, const size_t i) {
    size_t lp;
    std::stack<size_t> sor;
    while (re[ops.top()] == '|') {
        sor.push(ops.top());
        ops.pop();
    }
    if (!sor.empty()) {
        lp = ops.top();
        ops.pop();
        while (!sor.empty()) {
            size_t oor = sor.top();
            sor.pop();
            graph.add_edge(lp, oor + 1);
            graph.add_edge(oor, i);
        }
    } else {
        lp = ops.top();
        ops.pop();
    }
    return lp;
}

size_t NFA::switch_to_complement(const size_t i, const size_t left_edge) {
    graph.add_edge(left_edge, i);
    size_t j = i;
    for (; re[j] != ']'; j++);
    square_ranges.emplace_back(i, j);
    return j;
}

void NFA::closure_transit(char c, size_t left, size_t right) {
    if (c == '*') {
        graph.add_edge(left, right);
        graph.add_edge(right, left, std::numeric_limits<long long>::min());
    } else if (c == '+') {
        graph.add_edge(right, left, std::numeric_limits<long long>::min());
    } else if (c == '?') {
        graph.add_edge(left, right);
    } else if (c == '{') {
        size_t i = right;
        while (re[i] != '}')
            i++;
        std::pair<long long, long long> p = parse_config(right, i);
        graph.add_edge(right, i, p.first - 1);
        graph.add_edge(right, left, -p.second + 2);
        if (p.first == 0)
            graph.add_edge(left, right);
    }
}


bool NFA::transit_to_next(char c) {
    return c == '(' || c == '*' || c == ')' || c == '+' || c == '?' || c == ']'
           || c == '}';
}

bool NFA::recognize(const std::string &txt) {
    std::forward_list<size_t> pc;
    std::forward_list<size_t> ranges;
    dfs search(graph, (size_t) 0);
    bool complement = false; // handle complement

    for (size_t v = 0; v < graph.vertex(); v++)
        if (search.marked(v))
            pc.push_front(v);

    for (size_t i = 0; i < txt.size(); i++) {
        std::forward_list<size_t> match;
        for (size_t v : pc) { // find new reachable states
            if (v < states) {
                std::pair<size_t, size_t> set = find_set_range(ranges, v);
                if (!complement
                    || !in_complement_set(set)) { // not complement mode or not in the set
                    if (generally_equal(v, txt[i]))
                        match.push_front(v + jump[v]);
                } else { // complement mode
                    if (equal_to_char_in_set(set, txt[i]))
                        match.push_front(set.second);
                }
            }
        }
        pc.clear();
        ranges.clear();
        complement = false;

        search.reset(graph, match);
        for (int v = 0; v < graph.vertex(); v++) { // construct new pc
            if (search.marked(v))
                pc.push_front(v);
            if (re[v] == '^') {
                complement = true;
                ranges.push_front(find_range(square_ranges, v));
            }
        }
    }
    graph.reset_weight();
    for (size_t v : pc)
        if (v == states) return true;
    return false;
}

size_t NFA::find_range(const std::vector<std::pair<size_t, size_t>> &square_ranges,
                       const size_t v) {
    auto iter = std::find_if(square_ranges.cbegin(), square_ranges.cend(),
                             [v](std::pair<size_t, size_t> p) {
                                 return p.first == v;
                             });
    return static_cast<size_t>(std::distance(square_ranges.cbegin(), iter));
}

bool NFA::in_complement_set(std::pair<size_t, size_t> p) {
    return !(p.first == 0 && p.second == 0);
}

std::pair<size_t, size_t> NFA::find_set_range(const std::forward_list<size_t> &ranges,
                                              const size_t v) {
    std::pair<size_t, size_t> ret(0, 0);
    for (size_t k : ranges) {
        if (v >= square_ranges[k].first && v < square_ranges[k].second) {
            ret = square_ranges[k];
            break;
        }
    }
    return ret;
}

bool NFA::generally_equal(const size_t v, const char in_txt) {
    if (re[v] == '\\')
        return escape_equal(in_txt, re[v + 1]);
    bool flag = false;
    if (re[v] == in_txt || re[v] == '.')
        flag = true;
    else if (re[v] == '-') {
        bool in_set = false;
        int k = (int) v;
        for (; k >= 0; --k) {
            if (re[k] == ']')
                break;
            if (re[k] == '[')
                in_set = true;
        }

        if (in_set) {
            if (in_txt >= re[v - 1] && in_txt <= re[v + 1])
                flag = true;
        }
    }
    return flag;
}

bool NFA::equal_to_char_in_set(const std::pair<size_t, size_t> set, char in_txt) {
    size_t k = set.first + 1;
    for (; k < set.second; k++) {
        if (generally_equal(k, in_txt)) {
            if (re[k] == '\\') k++;
            break;
        }
        if (re[k] == '\\') k++;
    }
    return k == set.second;
}

std::pair<long long, long long> NFA::parse_config(size_t left, size_t right) {
    return parse_range(re.substr(left, right + 1 - left));
}

std::pair<long long, long long> NFA::parse_range(std::string str) {
    std::replace_if(str.begin(), str.end(), [](char c) {
        return c == '{' || c == '}';
    }, ' ');
    std::string::size_type i = str.find(',');
    if (i == str.size()) {
        long long temp = std::stoll(str);
        return std::pair<long long, long long>(temp, temp); // NOLINT
    } else {
        std::string former = str.substr(0, i);
        std::string latter = str.substr(i + 1);
        long long f = std::stoll(former);
        long long l;
        auto iter = std::find_if(latter.begin(), latter.end(), [](char c) {
            return c != ' ';
        });
        if (iter != latter.end())
            l = std::stoll(latter);
        else
            l = std::numeric_limits<long long>::max();
        return std::pair<long long, long long>(f, l);
    }
}

bool NFA::is_escape(size_t i) {
    if (i == 0)
        return false;
    int j = 0, k = static_cast<int>(i - 1);
    for (; k >= 0 && re[k] == '\\'; k--)
        ++j;
    return j % 2 == 1;
}

bool NFA::escape_equal(char c, char e, bool inset) {
    switch (e) {
        // \d \s and \w
        case 'd':
            return static_cast<bool>(isdigit(c));
        case 'D':
            return !isdigit(c);
        case 's':
            return static_cast<bool>(isspace(c));
        case 'S':
            return !isspace(c);
        case 'w':
            return static_cast<bool>(isalnum(c));
        case 'W':
            return !isalnum(c);

            // \t \r and \n
        case 't':
            return c == '\t';
        case 'r':
            return c == '\r';
        case 'n':
            return c == '\n';

        case '\\':;
        case '*':;
        case '+':;
        case '?':;
        case '{':;
        case '}':;
        case '[':;
        case ']':;
        case '(':;
        case ')':;
        case '|':
            return c == e; // including all the above

        case '^':;
        case '-':
            if (inset) return c == e;
        default:
            return false;
    }
}

std::pair<bool, std::string::size_type>
NFA::search(const std::string &txt, const std::string::size_type start) {
    std::forward_list<size_t> pc;
    std::forward_list<size_t> ranges;
    dfs search(graph, (size_t) 0);
    bool complement = false; // handle complement
    std::pair<bool, std::string::size_type> ret(false, 0);

    for (size_t v = 0; v < graph.vertex(); v++)
        if (search.marked(v))
            pc.push_front(v);

    for (size_t i = start; i < txt.size(); i++) {
        std::forward_list<size_t> match;
        for (size_t v : pc) { // find new reachable states
            if (v < states) {
                std::pair<size_t, size_t> set = find_set_range(ranges, v);
                if (!complement
                    || !in_complement_set(set)) { // not complement mode or not in the set
                    if (generally_equal(v, txt[i]))
                        match.push_front(v + jump[v]);
                } else { // complement mode
                    if (equal_to_char_in_set(set, txt[i]))
                        match.push_front(set.second);
                }
            }
        }
        pc.clear();
        ranges.clear();
        complement = false;
        
        if (match.empty()) {
            break;
        }

        search.reset(graph, match);
        for (int v = 0; v < graph.vertex(); v++) { // construct new pc
            if (search.marked(v))
                pc.push_front(v);
            if (re[v] == '^') {
                complement = true;
                ranges.push_front(find_range(square_ranges, v));
            }
        }
        
        if (search.marked(states)) {
            ret.first = true;
            ret.second = i - start + 1;
        }
    }
    graph.reset_weight();
    return ret;
}
} // namespace jregex_util



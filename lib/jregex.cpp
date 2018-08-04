//
// Created by 黄嘉华 on 2018/8/4.
//

#include "../include/jregex/jregex.h"

namespace jregex {

bool jregex_match(const std::string& txt, jreg& regexp) {
    return regexp.recognize(txt);
}

bool jregex_search(const std::string& txt, jreg& regexp) {
    for (std::string::size_type i = 0; i < txt.size(); i++)
        if (regexp.search(txt, i).first)
            return true;
    return false;
}

result jregex_find(const std::string& txt, jreg& regexp) {
    std::pair<std::string::size_type, std::string::size_type> p;
    for (std::string::size_type i = 0; i < txt.size(); i++)
        if ((p = regexp.search(txt, i)).first)
            return {i, p.second, &txt};
    return {txt.size(), 0, nullptr};
}

void jregex_find(const std::string& txt, results& v, jreg& regexp) {
    std::pair<std::string::size_type, std::string::size_type> p;
    for (std::string::size_type i = 0; i < txt.size(); i++)
        if ((p = regexp.search(txt, i)).first) {
            v.push_back(result(i, p.second, &txt));
            i += p.second - 1;
        }
}

result::result(std::string::size_type p, std::string::size_type l, const std::string *s) :
        pos(p), len(l), ptr(s) {}

std::string result::str() {
    if (ptr == nullptr)
        return std::string();
    else
        return ptr->substr(pos, len);
}

std::string::size_type result::position() { return pos; }

std::string::size_type result::length() { return len; }

bool jreg::recognize(const std::string &txt) { return nfa.recognize(txt); }

std::pair<bool, std::string::size_type> jreg::search(const std::string &txt, 
                                                     std::string::size_type start) {
    return nfa.search(txt, start);
}

jreg::jreg(const std::string &str) : nfa(str) {}
} // namespace jregex


//
// Created by 黄嘉华 on 2018/8/4.
//

#ifndef JREGEX_JREGEX_H
#define JREGEX_JREGEX_H

#include "../internal/NFA.h"
#include <string>

namespace jregex {
// class represent the regular expression
class jreg;
class result;
typedef std::vector<result> results;

// return whether match
bool jregex_match(const std::string& txt, jreg& regexp);

// return whether somewhere in the txt match
bool jregex_search(const std::string& txt, jreg& regexp);

// return the first index where it matches in the txt
result jregex_find(const std::string& txt, jreg& regexp);

// return all the matches
void jregex_find(const std::string& txt, results& v, jreg& regexp);



// implementation of jreg
class jreg {
    friend bool jregex_match(const std::string& txt, jreg& regexp);
    friend bool jregex_search(const std::string& txt, jreg& regexp);
    friend result jregex_find(const std::string& txt, jreg& regexp);
    friend void jregex_find(const std::string& txt, results& v, jreg& regexp);
private:
    jregex_util::NFA nfa;
    bool recognize(const std::string& txt);

    std::pair<bool, std::string::size_type>
    search(const std::string& txt, std::string::size_type start);
public:
    jreg(const std::string& str);
};

class result {
    friend result jregex_find(const std::string& txt, jreg& regexp);
    friend void jregex_find(const std::string& txt, results& v, jreg& regexp);
private:
    std::string::size_type pos;
    std::string::size_type len;
    const std::string* ptr;
    result(std::string::size_type p, std::string::size_type l, const std::string* s);
public:
    std::string str();
    std::string::size_type position();
    std::string::size_type length();
};

} // namespace jregex



#endif //JREGEX_JREGEX_H

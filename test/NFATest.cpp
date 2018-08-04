//
// Created by 黄嘉华 on 2018/7/30.
//

#include "../lib/nfa/NFA.h"
#include <gtest/gtest.h>
#include <algorithm>
using namespace std;
using namespace jregex_util;

template <typename C>
void display(C& c) {
    for (auto i : c)
        cout << i << " ";
    cout << endl;
}

TEST(MatchTest, NFATest) {
    const string regexp = "((A*B|AC)D)";
    NFA nfa(regexp);

    vector<string> TureTests = {
            "ABD", "BD", "AAABD", "ACD"
    };

    vector<string> FalseTests = {
            "", "D", "AD", "AAD", "CD", "hello"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithOneOrMore, NFATest) {
    const string regexp = "((A+B|AC)D)";
    NFA nfa(regexp);

    vector<string> TureTests = {
            "ABD", "AABD", "AAABD", "AAAABD", "ACD"
    };

    vector<string> FalseTests = {
            "", "D", "BD", "AD", "AAD", "CD", "hello"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithZeroOrOne, NFATest) {
    const string regexp = "((A?B|AC)D)";
    NFA nfa(regexp);

    vector<string> TureTests = {
            "ABD", "BD", "ACD"
    };

    vector<string> FalseTests = {
            "", "D", "AABD", "AAABD", "AD", "AAD", "CD", "hello"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithMultiwayOr, NFATest) {
    const string regexp = "(.*AB((C|D|EH)F)*G)";
    NFA nfa(regexp);
    vector<string> TureTests = {
            "ABCFG", "ABDFG", "ABEHFG",
            "ABG",
            "ABCFCFG", "ABDFDFG", "ABEHFEHFG", "ABCFDFEHFG",
            "eABCFCFG", "amABG"
    };

    vector<string> FalseTests = {
            "", "hello",
            "ABCFMFG", "ABMFG",
            "acAdBG"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithSet, NFATest) {
    const string regexp = "C[ABCD]+E";
    NFA nfa(regexp);
    vector<string> TureTests = {
        "CAE", "CBE", "CCE", "CDE",
        "CAAE", "CCCE", "CBDE", "CADE",
        "CABCDE", "CAAAAE", "CAAAAAE"
    };

    vector<string> FalseTests = {
            "", "hello",
            "CE", "CEE", "CFE"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithRange, NFATest) {
    const string regexp = "C[aA-D0-9]+E";
    NFA nfa(regexp);
    vector<string> TureTests = {
            "CAE", "CBE", "CCE", "CDE",
            "CAAE", "CCCE", "CBDE", "CADE",
            "CaE", "C5E",
            "CABCDE", "C0000E", "C00000E"
    };

    vector<string> FalseTests = {
            "", "hello",
            "CE", "CEE", "CFE"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithComplement, NFATest) {
    const string regexp = "C[^A-D]+[0-9]?E";
    NFA nfa(regexp);
    vector<string> TureTests = {
        "CME", "C3E", "CaE",
        "CMOE", "C1KE", "CO5E"
    };

    vector<string> FalseTests = {
            "", "hello",
            "CAE", "CADE",
            "CCE", "CMBE", "cP54E"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithSpecificClosure, NFATest) {
    const string regexp = "A{1,2}B{1}C{2,}D";
    NFA nfa(regexp);
    vector<string> TureTests = {
           "ABCCD", "AABCCD", "AABCCCD", "ABCCCCCCCCCD"
    };

    vector<string> FalseTests = {
            "ABBCCD", "BCCD", "AAABCCD", "AAAABCCD", "AAAAABCCD", "AAAAAABCCD",
            "ABCD"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}


TEST(EmptyRegexpTest, NFATest) {
    const string regexp = "";
    NFA nfa(regexp);
    vector<string> TureTests = {
    };

    vector<string> FalseTests = {
            "he", "hello",
            "CE", "CEE", "CFE"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithEscape1, NFATest) {
    const string regexp = R"(\++\[\s\d\D)";
    NFA nfa(regexp);
    vector<string> TureTests = {
            "+[ 3m", "+++[\t9."
    };

    vector<string> FalseTests = {
            "[ 3m", "+[ 23", "+[ mm"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(MatchTestWithEscape2, NFATest) {
    const string regexp = "[\\-A-Z*]+";
    NFA nfa(regexp);
    vector<string> TureTests = {
            "-", "B", "*", "*-B"
    };

    vector<string> FalseTests = {
            "[ 3m", "+[ 23", "+[ mm"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

TEST(TempTest, NFATest) {
    const string regexp = "A-Z";
    NFA nfa(regexp);
    vector<string> TureTests = {
            "A-Z"
    };

    vector<string> FalseTests = {
            "AAZ", "AAZR"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(nfa.recognize(str)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(nfa.recognize(str)) << str << " supposed to be false!!";
}

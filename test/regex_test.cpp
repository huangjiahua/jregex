//
// Created by 黄嘉华 on 2018/8/4.
//

#include "../include/jregex/jregex.h"
#include <gtest/gtest.h>
using namespace std;
using namespace jregex;

TEST(match_test, jregex_test) {
    const string regexp = "((A*B|AC)D)";
    jreg nfa(regexp);

    vector<string> TureTests = {
            "ABD", "BD", "AAABD", "ACD"
    };

    vector<string> FalseTests = {
            "", "D", "AD", "AAD", "CD", "hello"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(jregex_match(str, nfa)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(jregex_match(str, nfa)) << str << " supposed to be false!!";
}

TEST(search_test, jregex_test) {
    const string regexp = "((A*B|AC)D)";
    jreg nfa(regexp);

    vector<string> TureTests = {
            "ABDKKK", "BDhih", "AAABDdog", "ACDmka",
            "sfkaABDfasl", "fasfBDDKFJ", "dAAABD", "fsaACD"

    };

    vector<string> FalseTests = {
            "", "D", "AD", "AAD", "CD", "hello", "mAAAB"
    };

    for (const string& str : TureTests)
        EXPECT_TRUE(jregex_search(str, nfa)) << str << " supposed to be true!!";

    for (const string& str : FalseTests)
        EXPECT_FALSE(jregex_search(str, nfa)) << str << " supposed to be false!!";
}

TEST(find_test, jregex_test) {
    const string regexp = "((A*B|AC)D)";
    jreg nfa(regexp);

    vector<string> TureTests = {
            "ABDKKK", "BDhih", "mmAAABDdog", "ACDmka",
            "sfkaABDfasl", "fasfBDDKFJ", "dAAABD", "fsaACD"

    };

    vector<string> FalseTests = {
            "", "D", "AD", "AAD", "CD", "hello"
    };

    auto r1 = jregex_find(TureTests[2], nfa);
    EXPECT_EQ(r1.position(), 2);
    EXPECT_EQ(r1.length(), 5);
    EXPECT_EQ(r1.str(), string("AAABD"));

    for (auto& str : FalseTests) {
        auto r = jregex_find(str, nfa);
        EXPECT_EQ(r.position(), str.size());
        EXPECT_EQ(r.length(), 0);
        EXPECT_EQ(r.str(), string(""));
    }
}

TEST(find_all_test, jregex_test) {
    const string regexp = "A[BCD]{1,2}M";
    jreg nfa(regexp);

    vector<string> TureTests = {
            "ABBM", "KABCMABCM", "ADMTK,ADBMCDABM"
    };

    vector<string> FalseTests = {
    };

    results rs1, rs2, rs3;
    jregex_find(TureTests[0], rs1, nfa);
    jregex_find(TureTests[1], rs2, nfa);
    jregex_find(TureTests[2], rs3, nfa);

    EXPECT_EQ(rs1.size(), 1);
    EXPECT_EQ(rs2.size(), 2);
    EXPECT_EQ(rs3.size(), 3);
}



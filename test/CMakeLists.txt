set(NFASRC  ../lib/nfa/NFA.cpp
        ../lib/digraph/digraph.cpp  ../lib/digraph/dfs.cpp)
set(JREGEXSRC  ../lib/jregex.cpp)

add_executable(REGEX_MATCH_TEST regex_test.cpp ${NFASRC} ${JREGEXSRC})
target_link_libraries(REGEX_MATCH_TEST gtest_main pthread)

add_executable(NFA_TEST NFATest.cpp ${NFASRC})
target_link_libraries(NFA_TEST gtest_main pthread)

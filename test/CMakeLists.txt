set(NFASRC ../lib/nfa/NFA.h ../lib/nfa/NFA.cpp ../lib/digraph/digraph.h
        ../lib/digraph/digraph.cpp ../lib/digraph/dfs.h ../lib/digraph/dfs.cpp)
set(JREGEXSRC ../include/jregex/jregex.h ../lib/jregex.cpp)

add_executable(REGEX_MATCH_TEST regex_test.cpp ${NFASRC} ${JREGEXSRC})
target_link_libraries(REGEX_MATCH_TEST gtest_main pthread)
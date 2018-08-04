set(DIGRAPHLIB ../digraph/digraph.h ../digraph/digraph.cpp
        ../digraph/dfs.h ../digraph/dfs.cpp)

add_executable(test1 NFATest.cpp NFA.h NFA.cpp ${DIGRAPHLIB})
target_link_libraries(test1 gtest_main pthread)
cmake_minimum_required(VERSION 3.10)
project(jregex CXX)

set(CMAKE_CXX_STANDARD 11)

#add_subdirectory(./googletest)
add_subdirectory(./test)

set(NFALIBSRC lib/nfa/NFA.cpp lib/digraph/digraph.cpp lib/digraph/dfs.cpp)

add_library(jregex SHARED lib/jregex.cpp ${NFALIBSRC})
set_target_properties(jregex PROPERTIES VERSION 1.0 SOVERSION 0)

add_library(jregex_static STATIC lib/jregex.cpp ${NFALIBSRC})
set_target_properties(jregex_static
        PROPERTIES OUTPUT_NAME "jregex")

include_directories(AFTER ./include)

install(TARGETS jregex jregex_static
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES include/jregex/jregex.h DESTINATION include/jregex)



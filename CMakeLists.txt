cmake_minimum_required(VERSION 2.6)
project(ldistance)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_subdirectory(lib)
add_subdirectory(ut)

enable_testing()
add_test(NAME ldistance_ut COMMAND ldistance_ut -s)

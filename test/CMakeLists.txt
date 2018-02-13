cmake_minimum_required(VERSION 2.8)
project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -std=c++11 -pedantic -Wextra -lgtest_main -lgtest -lpthread -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
include_directories(../include/)

set(SOURCE_FILES commandLineParser_test.cpp ../src/commandLineParser.cpp fileBits_test.cpp ../src/fileBits.cpp
        rates_test.cpp  ../src/rates.cpp
        huffmanTree_test.cpp ../src/huffmanTree.cpp
        huffmanTypes_test.cpp ../src/huffman.cpp huffman_test.cpp)
add_executable(test ${SOURCE_FILES})
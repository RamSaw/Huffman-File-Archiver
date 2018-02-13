cmake_minimum_required(VERSION 2.8)
project(hw_03)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Werror -std=c++11 -Iinclude -pedantic -Wextra")
include_directories(./include/)

set(SOURCE_FILES src/main.cpp src/huffman.cpp include/huffman.h include/huffmanTree.h src/huffmanTree.cpp include/fileBits.h src/fileBits.cpp include/commandLineParser.h src/commandLineParser.cpp src/rates.cpp include/rates.h include/huffmanTypes.h)
add_executable(huffman ${SOURCE_FILES})

//
// Created by mikhail on 22.04.17.
//

#include <gtest/gtest.h>

#include "huffmanTree.h"

/* Test HuffmanTree class */

/* empty input, checks that there is no failure */
TEST(HuffmanTree_test, empty_input_case) {
    std::stringstream in_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree huffman_tree(rates);
    /* Most likely could be realization with 0 or 1 code for none byte */
    ASSERT_FALSE(huffman_tree.byte_exists(std::vector<bool>(1, 0)));
    ASSERT_FALSE(huffman_tree.byte_exists(std::vector<bool>(1, 0)));
}

/* single byte input */
TEST(HuffmanTree_test, single_byte_input_case) {
    std::stringstream in_f("a");
    huffman_size_type correct_coded_str_length = 1;
    Rates rates(compress_mode, in_f);
    HuffmanTree huffman_tree(rates);

    huffman_size_type actual_coded_str_length = 0;
    for (auto byte : in_f.str()) {
        std::vector<bool> code = huffman_tree.get_code(byte);
        ASSERT_TRUE(huffman_tree.byte_exists(code));
        ASSERT_EQ(byte, huffman_tree.get_byte(code));
        actual_coded_str_length += code.size();
    }
    ASSERT_EQ(correct_coded_str_length, actual_coded_str_length);
}

/* one unique byte input */
TEST(HuffmanTree_test, one_unique_byte_input_case) {
    std::stringstream in_f("ddddd");
    huffman_size_type correct_coded_str_length = 5;
    Rates rates(compress_mode, in_f);
    HuffmanTree huffman_tree(rates);

    huffman_size_type actual_coded_str_length = 0;
    for (auto byte : in_f.str()) {
        std::vector<bool> code = huffman_tree.get_code(byte);
        ASSERT_TRUE(huffman_tree.byte_exists(code));
        ASSERT_EQ(byte, huffman_tree.get_byte(code));
        actual_coded_str_length += code.size();
    }
    ASSERT_EQ(correct_coded_str_length, actual_coded_str_length);
}

/* multiple bytes input */
TEST(HuffmanTree_test, multiple_bytes_input_case) {
    std::stringstream in_f("abacabad");
    huffman_size_type correct_coded_str_length = 14;
    Rates rates(compress_mode, in_f);
    HuffmanTree huffman_tree(rates);

    huffman_size_type actual_coded_str_length = 0;
    for (auto byte : in_f.str()) {
        std::vector<bool> code = huffman_tree.get_code(byte);
        ASSERT_TRUE(huffman_tree.byte_exists(code));
        ASSERT_EQ(byte, huffman_tree.get_byte(code));
        actual_coded_str_length += code.size();
    }
    ASSERT_EQ(correct_coded_str_length, actual_coded_str_length);
}

/* multiple bytes input, full coverage test of HuffmanTree() function */
TEST(HuffmanTree_test, full_coverage_input_case) {
    std::stringstream in_f("abcdefxxx");
    huffman_size_type correct_coded_str_length = 24;
    Rates rates(compress_mode, in_f);
    HuffmanTree huffman_tree(rates);

    huffman_size_type actual_coded_str_length = 0;
    for (auto byte : in_f.str()) {
        std::vector<bool> code = huffman_tree.get_code(byte);
        ASSERT_TRUE(huffman_tree.byte_exists(code));
        ASSERT_EQ(byte, huffman_tree.get_byte(code));
        actual_coded_str_length += code.size();
    }
    ASSERT_EQ(correct_coded_str_length, actual_coded_str_length);
}
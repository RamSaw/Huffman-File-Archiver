//
// Created by mikhail on 22.04.17.
//

#include <gtest/gtest.h>

#include "rates.h"

/* Test Rates class */

/* compress mode */
class RatesCompressModeTest : public  ::testing::Test {
protected:
    std::stringstream empty_input;
    Rates rates_empty_input;
    std::unordered_map<char, huffman_size_type> correct_rates_empty_input;

    std::stringstream single_byte_input;
    Rates rates_single_byte_input;
    std::unordered_map<char, huffman_size_type> correct_rates_single_byte_input;

    std::stringstream one_unique_byte_input;
    Rates rates_one_unique_byte_input;
    std::unordered_map<char, huffman_size_type> correct_rates_one_unique_byte_input;

    std::stringstream multiple_bytes_input;
    Rates rates_multiple_bytes_input;
    std::unordered_map<char, huffman_size_type> correct_rates_multiple_bytes_input;

    RatesCompressModeTest() : empty_input(""), rates_empty_input(compress_mode, empty_input),
                              single_byte_input("a"), rates_single_byte_input(compress_mode, single_byte_input),
                              one_unique_byte_input("bbbb"), rates_one_unique_byte_input(compress_mode, one_unique_byte_input),
                              multiple_bytes_input("abacabad"), rates_multiple_bytes_input(compress_mode, multiple_bytes_input) {
        correct_rates_single_byte_input['a'] = 1;

        correct_rates_one_unique_byte_input['b'] = 4;

        correct_rates_multiple_bytes_input['a'] = 4;
        correct_rates_multiple_bytes_input['b'] = 2;
        correct_rates_multiple_bytes_input['c'] = 1;
        correct_rates_multiple_bytes_input['d'] = 1;
    }
};

TEST_F(RatesCompressModeTest, size_method_test) {
    ASSERT_EQ(correct_rates_empty_input.size(), rates_empty_input.size());
    ASSERT_EQ(correct_rates_single_byte_input.size(), rates_single_byte_input.size());
    ASSERT_EQ(correct_rates_one_unique_byte_input.size(), rates_one_unique_byte_input.size());
    ASSERT_EQ(correct_rates_multiple_bytes_input.size(), rates_multiple_bytes_input.size());
}

TEST_F(RatesCompressModeTest, get_count_of_bytes_method_test) {
    ASSERT_EQ(empty_input.str().length(), rates_empty_input.get_count_of_bytes());
    ASSERT_EQ(single_byte_input.str().length(), rates_single_byte_input.get_count_of_bytes());
    ASSERT_EQ(one_unique_byte_input.str().length(), rates_one_unique_byte_input.get_count_of_bytes());
    ASSERT_EQ(multiple_bytes_input.str().length(), rates_multiple_bytes_input.get_count_of_bytes());
}

/* Also test on correct constructor */
TEST_F(RatesCompressModeTest, get_all_rates_method_test) {
    /* empty input */
    for (auto rate : rates_empty_input.get_all_rates()) {
        ASSERT_TRUE(correct_rates_empty_input.find(rate.first) != correct_rates_empty_input.end());
        ASSERT_EQ(correct_rates_empty_input[rate.first], rate.second);
    }

    /* single input */
    for (auto rate : rates_single_byte_input.get_all_rates()) {
        ASSERT_TRUE(correct_rates_single_byte_input.find(rate.first) != correct_rates_single_byte_input.end());
        ASSERT_EQ(correct_rates_single_byte_input[rate.first], rate.second);
    }

    /* one unique byte input */
    for (auto rate : rates_one_unique_byte_input.get_all_rates()) {
        ASSERT_TRUE(correct_rates_one_unique_byte_input.find(rate.first) != correct_rates_one_unique_byte_input.end());
        ASSERT_EQ(correct_rates_one_unique_byte_input[rate.first], rate.second);
    }

    /* multiple bytes input */
    for (auto rate : rates_multiple_bytes_input.get_all_rates()) {
        ASSERT_TRUE(correct_rates_multiple_bytes_input.find(rate.first) != correct_rates_multiple_bytes_input.end());
        ASSERT_EQ(correct_rates_multiple_bytes_input[rate.first], rate.second);
    }
}

TEST_F(RatesCompressModeTest, write_rates_table_method_test_empty_input_case) {
    /* empty input */
    std::stringstream out_f;
    huffman_size_type written_size = 0;
    rates_empty_input.serialize_to(out_f);

    out_f.read(reinterpret_cast<char *>(&written_size), sizeof(written_size));
    ASSERT_EQ(correct_rates_empty_input.size(), written_size);
    /*
     * Not a black box moment: we demand that table is written exactly in this order.
     * Let's assume that it is must-have specification.
     */
    for (auto correct_rate : correct_rates_empty_input) {
        char written_byte = 0;
        huffman_size_type written_rate = 0;
        out_f.read(&written_byte, sizeof(char));
        out_f.read(reinterpret_cast<char *>(&written_rate), sizeof(huffman_size_type));

        ASSERT_EQ(correct_rate.first, written_byte);
        ASSERT_EQ(correct_rate.second, written_rate);
    }
}

TEST_F(RatesCompressModeTest, write_rates_table_method_test_single_byte_input_case) {
    /* single byte input */
    std::stringstream out_f;
    huffman_size_type written_size = 0;
    rates_single_byte_input.serialize_to(out_f);

    out_f.read(reinterpret_cast<char *>(&written_size), sizeof(huffman_size_type));
    ASSERT_EQ(correct_rates_single_byte_input.size(), written_size);
    for (auto correct_rate : correct_rates_single_byte_input) {
        char written_byte = 0;
        huffman_size_type written_rate = 0;
        out_f.read(&written_byte, sizeof(char));
        out_f.read(reinterpret_cast<char *>(&written_rate), sizeof(huffman_size_type));

        ASSERT_EQ(correct_rate.first, written_byte);
        ASSERT_EQ(correct_rate.second, written_rate);
    }
}

TEST_F(RatesCompressModeTest, write_rates_table_method_test_one_unique_byte_input_case) {
    /* one unique byte input */
    std::stringstream out_f;
    huffman_size_type written_size = 0;
    rates_one_unique_byte_input.serialize_to(out_f);

    out_f.read(reinterpret_cast<char *>(&written_size), sizeof(huffman_size_type));
    ASSERT_EQ(correct_rates_one_unique_byte_input.size(), written_size);
    for (auto correct_rate : correct_rates_one_unique_byte_input) {
        char written_byte = 0;
        huffman_size_type written_rate = 0;
        out_f.read(&written_byte, sizeof(char));
        out_f.read(reinterpret_cast<char *>(&written_rate), sizeof(huffman_size_type));

        ASSERT_EQ(correct_rate.first, written_byte);
        ASSERT_EQ(correct_rate.second, written_rate);
    }
}

TEST_F(RatesCompressModeTest, write_rates_table_method_test_multiple_bytes_input_case) {
    /* multiple bytes input */
    std::stringstream out_f;
    huffman_size_type written_size = 0;
    rates_multiple_bytes_input.serialize_to(out_f);

    out_f.read(reinterpret_cast<char *>(&written_size), sizeof(huffman_size_type));
    ASSERT_EQ(correct_rates_multiple_bytes_input.size(), written_size);
    for (auto correct_rate : correct_rates_multiple_bytes_input) {
        char written_byte = 0;
        huffman_size_type written_rate = 0;
        out_f.read(&written_byte, sizeof(char));
        out_f.read(reinterpret_cast<char *>(&written_rate), sizeof(huffman_size_type));

        ASSERT_EQ(correct_rate.first, written_byte);
        ASSERT_EQ(correct_rate.second, written_rate);
    }
}

/* decompress mode */
/*
 * All methods for compress are tested including common methods for both mode,
 * that's why it is left in decompress mode only to test decompress constructor using compress mode
 */
TEST_F(RatesCompressModeTest, decompress_mode_constuctor_test_empty_input_case) {
    /* empty input */
    std::stringstream out_f;
    rates_empty_input.serialize_to(out_f);
    Rates rates_empty_input_decompress(decompress_mode, out_f);

    for (auto rate : rates_empty_input_decompress.get_all_rates()) {
        ASSERT_TRUE(correct_rates_empty_input.find(rate.first) != correct_rates_empty_input.end());
        ASSERT_EQ(correct_rates_empty_input[rate.first], rate.second);
    }
}

TEST_F(RatesCompressModeTest, decompress_mode_constuctor_test_single_byte_input_case) {
    /* single byte input */
    std::stringstream out_f;
    rates_single_byte_input.serialize_to(out_f);
    Rates rates_single_byte_input_decompress(decompress_mode, out_f);

    for (auto rate : rates_single_byte_input_decompress.get_all_rates()) {
        ASSERT_TRUE(correct_rates_single_byte_input.find(rate.first) != correct_rates_single_byte_input.end());
        ASSERT_EQ(correct_rates_single_byte_input[rate.first], rate.second);
    }
}

TEST_F(RatesCompressModeTest, decompress_mode_constuctor_test_one_unique_byte_input_case) {
    /* one unique byte input */
    std::stringstream out_f;
    rates_one_unique_byte_input.serialize_to(out_f);
    Rates rates_one_unique_byte_input_decompress(decompress_mode, out_f);

    for (auto rate : rates_one_unique_byte_input_decompress.get_all_rates()) {
        ASSERT_TRUE(correct_rates_one_unique_byte_input.find(rate.first) != correct_rates_one_unique_byte_input.end());
        ASSERT_EQ(correct_rates_one_unique_byte_input[rate.first], rate.second);
    }
}

TEST_F(RatesCompressModeTest, decompress_mode_constuctor_test_multiple_bytes_input_case) {
    /* multiple bytes input */
    std::stringstream out_f;
    rates_multiple_bytes_input.serialize_to(out_f);
    Rates rates_multiple_bytes_input_decompress(decompress_mode, out_f);

    for (auto rate : rates_multiple_bytes_input_decompress.get_all_rates()) {
        ASSERT_TRUE(correct_rates_multiple_bytes_input.find(rate.first) != correct_rates_multiple_bytes_input.end());
        ASSERT_EQ(correct_rates_multiple_bytes_input[rate.first], rate.second);
    }
}
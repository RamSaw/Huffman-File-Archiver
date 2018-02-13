//
// Created by mikhail on 22.04.17.
//

#include <gtest/gtest.h>

#include "fileBits.h"

/* Test BitWriter class */
TEST(BitWriter_test, empty_input_case) {
    std::stringstream out_f;
    BitWriter bit_writer(out_f);
    bit_writer.flush();

    ASSERT_TRUE(out_f.good());
    ASSERT_EQ("", out_f.str());
}

TEST(BitWriter_test, not_empty_input_divisible_8_case) {
    std::vector<bool> input_bits = {0, 0, 0, 0, 0, 0, 0, 0,
                                    1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 1,
                                    0, 1, 0, 0, 0, 1, 1, 0};
    std::string result_string = {0, -1, 1, -128, 'b'};

    std::stringstream out_f;
    BitWriter bit_writer(out_f);

    for (auto bit : input_bits) {
        bit_writer.write_bit(bit);
    }
    bit_writer.flush();

    ASSERT_TRUE(out_f.good());
    ASSERT_EQ(result_string, out_f.str());
}

TEST(BitWriter_test, not_empty_input_less_1_bit_case) {
    std::vector<bool> input_bits = {1, 0, 1};
    std::string result_string = {5};

    std::stringstream out_f;
    BitWriter bit_writer(out_f);

    for (auto bit : input_bits) {
        bit_writer.write_bit(bit);
    }
    ASSERT_TRUE(out_f.good());
    ASSERT_EQ(out_f.str(), "");

    bit_writer.flush();
    ASSERT_TRUE(out_f.good());
    ASSERT_EQ(result_string, out_f.str());
}

TEST(BitWriter_test, not_empty_input_more_1_bit_case) {
    std::vector<bool> input_bits = {0, 1, 1, 0, 1, 0, 0, 0,
                                    1, 1, 0, 1};
    std::string result_string = {22, 11};

    std::stringstream out_f;
    BitWriter bit_writer(out_f);

    for (auto bit : input_bits) {
        bit_writer.write_bit(bit);
    }
    bit_writer.flush();

    ASSERT_TRUE(out_f.good());
    ASSERT_EQ(result_string, out_f.str());
}

/* Test BitReader class */
TEST(BitReader_test, input_divisible_8_case) {
    std::string in_f_string = {0, -1, 1, -128, 'b'};
    std::stringstream in_f(in_f_string);
    std::vector<bool> output_bits = {0, 0, 0, 0, 0, 0, 0, 0,
                                     1, 1, 1, 1, 1, 1, 1, 1,
                                     1, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 1,
                                     0, 1, 0, 0, 0, 1, 1, 0};
    BitReader bit_reader(in_f);

    for (auto bit : output_bits) {
        bool read_bit = bit_reader.read_bit();
        ASSERT_EQ(bit, read_bit);
        ASSERT_TRUE(in_f.good());
    }
}

TEST(BitReader_test, input_less_1_bit_case) {
    std::string in_f_string = {5};
    std::stringstream in_f(in_f_string);
    std::vector<bool> output_bits = {1, 0, 1};
    BitReader bit_reader(in_f);

    for (auto bit : output_bits) {
        bool read_bit = bit_reader.read_bit();
        ASSERT_EQ(bit, read_bit);
        ASSERT_TRUE(in_f.good());
    }
}

TEST(BitReader_test, input_more_1_bit_case) {
    std::string in_f_string = {22, 11};
    std::stringstream in_f(in_f_string);
    std::vector<bool> output_bits = {0, 1, 1, 0, 1, 0, 0, 0,
                                      1, 1, 0, 1};
    BitReader bit_reader(in_f);

    for (auto bit : output_bits) {
        bool read_bit = bit_reader.read_bit();
        ASSERT_EQ(bit, read_bit);
        ASSERT_TRUE(in_f.good());
    }
}
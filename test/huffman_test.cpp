//
// Created by mikhail on 22.04.17.
//
#include <gtest/gtest.h>

#include "huffman.h"
#include "huffmanTypes.h"

/* empty input */
TEST(encode_huffman_test, empty_input_case) {
    std::stringstream in_f, out_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, out_f, codes_tree);
    ASSERT_EQ("", out_f.str());
}

TEST(decode_huffman_test, empty_input_case) {
    std::stringstream in_f, coded_out_f, decoded_out_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, coded_out_f, codes_tree);

    decode_huffman(coded_out_f, decoded_out_f, codes_tree, rates.get_count_of_bytes());
    ASSERT_EQ(in_f.str(), decoded_out_f.str());
}

TEST(compress_test, empty_input_case) {
    std::stringstream in_f, out_f, correct_out_f;
    huffman_size_type correct_size_of_rates = 0, correct_result_data_size = 0;
    filesize_statistic out_statistic;

    correct_out_f.write(FilePrefix::VALUE.c_str(), FilePrefix::VALUE.length());
    correct_out_f.write(reinterpret_cast<char *>(&correct_size_of_rates), sizeof(huffman_size_type));

    out_statistic = compress(in_f, out_f);

    ASSERT_EQ(correct_out_f.str(), out_f.str());
    ASSERT_EQ(in_f.str().size(), out_statistic.source_data_size);
    ASSERT_EQ(out_f.str().size(), out_statistic.additional_data_size);
    ASSERT_EQ(correct_result_data_size, out_statistic.result_data_size);
}

TEST(decompress_test, empty_input_case) {
    std::stringstream in_f, compressed_out_f, decompressed_out_f;

    filesize_statistic compressed_statistic = compress(in_f, compressed_out_f);
    filesize_statistic decompressed_statistic = decompress(compressed_out_f, decompressed_out_f);

    ASSERT_EQ(in_f.str(), decompressed_out_f.str());
    ASSERT_EQ(decompressed_statistic.source_data_size, compressed_statistic.result_data_size);
    ASSERT_EQ(decompressed_statistic.result_data_size, compressed_statistic.source_data_size);
    ASSERT_EQ(decompressed_statistic.additional_data_size, compressed_statistic.additional_data_size);
}

/* single byte input */
/* White-box tests, needed information about coding */
TEST(encode_huffman_test, single_byte_input_case) {
    std::stringstream in_f("a"), out_f;
    std::string correct_coded_out = {0};
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, out_f, codes_tree);
    ASSERT_EQ(correct_coded_out, out_f.str());
}

TEST(decode_huffman_test, single_byte_input_case) {
    std::stringstream in_f("a"), coded_out_f, decoded_out_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, coded_out_f, codes_tree);

    decode_huffman(coded_out_f, decoded_out_f, codes_tree, rates.get_count_of_bytes());
    ASSERT_EQ(in_f.str(), decoded_out_f.str());
}

TEST(compress_test, single_byte_input_case) {
    std::stringstream in_f("a"), out_f, correct_out_f;
    std::string correct_coded_out = {0};

    std::unordered_map<char, huffman_size_type> correct_rates;
    correct_rates['a'] = 1;

    huffman_size_type correct_size_of_rates = correct_rates.size();

    correct_out_f.write(FilePrefix::VALUE.c_str(), FilePrefix::VALUE.length());
    correct_out_f.write(reinterpret_cast<char *>(&correct_size_of_rates), sizeof(huffman_size_type));
    for (auto correct_rate : correct_rates) {
        correct_out_f.write(&correct_rate.first, sizeof(char));
        correct_out_f.write(reinterpret_cast<char *>(&correct_rate.second), sizeof(huffman_size_type));
    }
    correct_out_f.write(correct_coded_out.c_str(), correct_coded_out.length());

    huffman_size_type correct_result_data_size = 1,
            correct_additional_data_size = FilePrefix::VALUE.size() + sizeof(huffman_size_type)
                                           + correct_rates.size() * (sizeof(char) + sizeof(huffman_size_type));

    filesize_statistic out_statistic = compress(in_f, out_f);

    ASSERT_EQ(correct_out_f.str(), out_f.str());
    ASSERT_EQ(in_f.str().size(), out_statistic.source_data_size);
    ASSERT_EQ(correct_additional_data_size, out_statistic.additional_data_size);
    ASSERT_EQ(correct_result_data_size, out_statistic.result_data_size);
}


TEST(decompress_test, single_byte_input_case) {
    std::stringstream in_f("a"), compressed_out_f, decompressed_out_f;
    filesize_statistic compressed_statistic = compress(in_f, compressed_out_f);
    filesize_statistic decompressed_statistic = decompress(compressed_out_f, decompressed_out_f);

    ASSERT_EQ(in_f.str(), decompressed_out_f.str());
    ASSERT_EQ(decompressed_statistic.source_data_size, compressed_statistic.result_data_size);
    ASSERT_EQ(decompressed_statistic.result_data_size, compressed_statistic.source_data_size);
    ASSERT_EQ(decompressed_statistic.additional_data_size, compressed_statistic.additional_data_size);
}

/* one unique byte input */
/* White-box tests, needed information about coding */
TEST(encode_huffman_test, one_unique_byte_input_case) {
    std::stringstream in_f("ddd"), out_f;
    std::string correct_coded_out = {0};
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, out_f, codes_tree);
    ASSERT_EQ(correct_coded_out, out_f.str());
}

TEST(decode_huffman_test, one_unique_byte_input_case) {
    std::stringstream in_f("ddd"), coded_out_f, decoded_out_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, coded_out_f, codes_tree);

    decode_huffman(coded_out_f, decoded_out_f, codes_tree, rates.get_count_of_bytes());
    ASSERT_EQ(in_f.str(), decoded_out_f.str());
}


TEST(compress_test, one_unique_byte_input_case) {
    std::stringstream in_f("ddd"), out_f, correct_out_f;
    std::string correct_coded_out = {0};


    std::unordered_map<char, huffman_size_type> correct_rates;
    correct_rates['d'] = 3;

    huffman_size_type correct_size_of_rates = correct_rates.size();
    correct_out_f.write(FilePrefix::VALUE.c_str(), FilePrefix::VALUE.length());
    correct_out_f.write(reinterpret_cast<char *>(&correct_size_of_rates), sizeof(huffman_size_type));
    for (auto correct_rate : correct_rates) {
        correct_out_f.write(&correct_rate.first, sizeof(char));
        correct_out_f.write(reinterpret_cast<char *>(&correct_rate.second), sizeof(huffman_size_type));
    }
    correct_out_f.write(correct_coded_out.c_str(), correct_coded_out.length());

    huffman_size_type correct_result_data_size = 1,
            correct_additional_data_size = FilePrefix::VALUE.size() + sizeof(huffman_size_type)
                                           + correct_rates.size() * (sizeof(char) + sizeof(huffman_size_type));

    filesize_statistic out_statistic = compress(in_f, out_f);

    ASSERT_EQ(correct_out_f.str(), out_f.str());
    ASSERT_EQ(in_f.str().size(), out_statistic.source_data_size);
    ASSERT_EQ(correct_additional_data_size, out_statistic.additional_data_size);
    ASSERT_EQ(correct_result_data_size, out_statistic.result_data_size);
}


TEST(decompress_test, one_unique_byte_input_case) {
    std::stringstream in_f("ddd"), compressed_out_f, decompressed_out_f;

    filesize_statistic compressed_statistic = compress(in_f, compressed_out_f);
    filesize_statistic decompressed_statistic = decompress(compressed_out_f, decompressed_out_f);

    ASSERT_EQ(in_f.str(), decompressed_out_f.str());
    ASSERT_EQ(decompressed_statistic.source_data_size, compressed_statistic.result_data_size);
    ASSERT_EQ(decompressed_statistic.result_data_size, compressed_statistic.source_data_size);
    ASSERT_EQ(decompressed_statistic.additional_data_size, compressed_statistic.additional_data_size);
}

/* multiple bytes input */
/* White-box tests, needed information about coding */
TEST(encode_huffman_test, multiple_bytes_input_case) {
    std::stringstream in_f("abacabad"), out_f;
    std::string correct_coded_out = {50, 57}; // a:0, b: 10, d: 111, c: 110; 01001100 10011100 -> 00110010 00111001
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, out_f, codes_tree);
    ASSERT_EQ(correct_coded_out, out_f.str());
}


TEST(decode_huffman_test, multiple_bytes_input_case) {
    std::stringstream in_f("abacabad"), coded_out_f, decoded_out_f;
    Rates rates(compress_mode, in_f);
    HuffmanTree codes_tree(rates);
    encode_huffman(in_f, coded_out_f, codes_tree);

    decode_huffman(coded_out_f, decoded_out_f, codes_tree, rates.get_count_of_bytes());
    ASSERT_EQ(in_f.str(), decoded_out_f.str());
}


TEST(compress_test, multiple_bytes_input_case) {
    std::stringstream in_f("abacabad"), out_f, correct_out_f;
    std::string correct_coded_out = {50, 57}; // a:0, b: 10, d: 111, c: 110; 01001100 10011100 -> 00110010 00111001

    std::unordered_map<char, huffman_size_type> correct_rates;
    correct_rates['a'] = 4;
    correct_rates['b'] = 2;
    correct_rates['c'] = 1;
    correct_rates['d'] = 1;

    huffman_size_type correct_size_of_rates = correct_rates.size();
    correct_out_f.write(FilePrefix::VALUE.c_str(), FilePrefix::VALUE.length());
    correct_out_f.write(reinterpret_cast<char *>(&correct_size_of_rates), sizeof(huffman_size_type));
    for (auto correct_rate : correct_rates) {
        correct_out_f.write(&correct_rate.first, sizeof(char));
        correct_out_f.write(reinterpret_cast<char *>(&correct_rate.second), sizeof(huffman_size_type));
    }
    correct_out_f.write(correct_coded_out.c_str(), correct_coded_out.length());

    huffman_size_type correct_result_data_size = 2,
            correct_additional_data_size = FilePrefix::VALUE.size() + sizeof(huffman_size_type)
                                           + correct_rates.size() * (sizeof(char) + sizeof(huffman_size_type));

    filesize_statistic out_statistic = compress(in_f, out_f);

    ASSERT_EQ(correct_out_f.str(), out_f.str());
    ASSERT_EQ(in_f.str().size(), out_statistic.source_data_size);
    ASSERT_EQ(correct_additional_data_size, out_statistic.additional_data_size);
    ASSERT_EQ(correct_result_data_size, out_statistic.result_data_size);
}


TEST(decompress_test, multiple_bytes_input_case) {
    std::stringstream in_f("abacabad"), compressed_out_f, decompressed_out_f;

    filesize_statistic compressed_statistic = compress(in_f, compressed_out_f);
    filesize_statistic decompressed_statistic = decompress(compressed_out_f, decompressed_out_f);

    ASSERT_EQ(in_f.str(), decompressed_out_f.str());
    ASSERT_EQ(decompressed_statistic.source_data_size, compressed_statistic.result_data_size);
    ASSERT_EQ(decompressed_statistic.result_data_size, compressed_statistic.source_data_size);
    ASSERT_EQ(decompressed_statistic.additional_data_size, compressed_statistic.additional_data_size);
}
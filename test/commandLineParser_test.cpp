//
// Created by mikhail on 21.04.17.
//

#include <gtest/gtest.h>

#include "commandLineParser.h"

TEST(parse_parameters_test, correct_input_1_case) {
    parameters input_params(compress_mode, "input", "output");

    std::vector<std::string> argv_input1 = {"path_unused", "-c", "-f", "input", "-o", "output"};
    parameters result_input1 = parse_parameters(argv_input1);
    /* Check equality */
    ASSERT_EQ(result_input1.mode, input_params.mode);
    ASSERT_EQ(result_input1.in_filename, input_params.in_filename);
    ASSERT_EQ(result_input1.out_filename, input_params.out_filename);
}

TEST(parse_parameters_test, correct_input_2_case) {
    parameters input_params(compress_mode, "input", "output");
    std::vector<std::string> argv_input2 = {"path_unused", "-o", "output", "-f", "input", "-c"};
    parameters result_input2 = parse_parameters(argv_input2);
    /* Check equality */
    ASSERT_EQ(result_input2.mode, input_params.mode);
    ASSERT_EQ(result_input2.in_filename, input_params.in_filename);
    ASSERT_EQ(result_input2.out_filename, input_params.out_filename);
}

TEST(parse_parameters_test, correct_input_3_case) {
    parameters input_params(compress_mode, "input", "output");

    std::vector<std::string> argv_input3 = {"path_unused", "-f", "input", "-c", "-o", "output"};
    parameters result_input3 = parse_parameters(argv_input3);
    /* Check equality */
    ASSERT_EQ(result_input3.mode, input_params.mode);
    ASSERT_EQ(result_input3.in_filename, input_params.in_filename);
    ASSERT_EQ(result_input3.out_filename, input_params.out_filename);
}

TEST(parse_parameters_test, incorrect_input_1_case) {
    bool is_exception = false;

    std::vector<std::string> argv_input1 = {"path_unused", "-c", "-f", "input", "-x", "output"};
    try {
        parse_parameters(argv_input1);
    }
    catch (std::runtime_error &re) {
        is_exception = true;
    }
    ASSERT_TRUE(is_exception);
}

TEST(parse_parameters_test, incorrect_input_2_case) {
    bool is_exception = false;

    std::vector<std::string> argv_input2 = {"path_unused", "-c", "-f", "input", "-o", "output", "extra_field"};
    try {
        parse_parameters(argv_input2);
    }
    catch (std::runtime_error &re) {
        is_exception = true;
    }
    ASSERT_TRUE(is_exception);
}

TEST(parse_parameters_test, incorrect_input_3_case) {
    bool is_exception = false;

    std::vector<std::string> argv_input3 = {"path_unused", "-c", "-f", "input", "-o"};
    try {
        parse_parameters(argv_input3);
    }
    catch (std::runtime_error &re){
        is_exception = true;
    }
    ASSERT_TRUE(is_exception);
}
//
// Created by mikhail on 22.04.17.
//

#include <gtest/gtest.h>

#include "huffmanTypes.h"

/* Test FilePrefix class */
TEST(FilePrefix_test, write_prefix_method_test) {
    std::stringstream out_f;
    FilePrefix::write_prefix(out_f);
    ASSERT_EQ(FilePrefix::VALUE, out_f.str());
}

TEST(FilePrefix_test, has_prefix_method_test) {
    std::stringstream in_f(FilePrefix::VALUE);
    ASSERT_TRUE(FilePrefix::check_prefix(in_f));
}
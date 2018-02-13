//
// Created by mikhail on 21.04.17.
//

#ifndef HW_03_TYPES_H
#define HW_03_TYPES_H

#include <cstddef>
#include <vector>
#include <iostream>

typedef uint64_t huffman_size_type;

enum mode_enum { compress_mode, decompress_mode, no_mode };

struct filesize_statistic {
    huffman_size_type source_data_size;
    huffman_size_type result_data_size;
    huffman_size_type additional_data_size;
};

class FilePrefix {
public:
    /*
     * Prefix to indicate that file was compressed by this program.
     * Value is set in huffman.cpp.
     */
    static const std::string VALUE;

    /*
     * Action: writes prefix to file
     * Contract: object remains in correct state, no changes in object.
     * May throw an exception while writing to file
     */
    static void write_prefix(std::ostream &out_f) {
        out_f.write(VALUE.c_str(), VALUE.length());
    }

    /*
     * Action: writes prefix to file
     * Contract: if prefix exists, return true, object remains in correct state, no changes in object.
     * If no prefix returns false or exception(?) throws if size of prefix cannot be read.
     * May throw an exception while reading from file
     */
    static bool check_prefix(std::istream &in_f) {
        std::vector<char> chars_file_prefix_read(VALUE.size());

        in_f.read(chars_file_prefix_read.data(), chars_file_prefix_read.size());
        std::string file_prefix_read(chars_file_prefix_read.begin(), chars_file_prefix_read.end());

        return file_prefix_read == VALUE;
    }
};

#endif //HW_03_TYPES_H

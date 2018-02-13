//
// Created by mikhail on 13.04.17.
//

/*
 * TODO: fix problem: using ofstream::write breaks endianness
 */

#include <deque>
#include <algorithm>
#include <iostream>

#include "huffman.h"

const std::string FilePrefix::VALUE = "#!HUFFMAN_MP5";

void encode_huffman(std::istream &in_f, std::ostream &out_f, const HuffmanTree &codes_tree) {
    BitWriter bit_writer(out_f);

    in_f.seekg(std::ios_base::beg);
    while (in_f.peek() != std::istream::traits_type::eof()) {
        char byte;

        in_f.read(&byte, sizeof(byte));
        for (const auto& bit : codes_tree.get_code(byte))
            bit_writer.write_bit(bit);
    }
}

void decode_huffman(std::istream &in_f, std::ostream &out_f, const HuffmanTree &codes_tree,
                    huffman_size_type count_of_bytes) {
    BitReader bit_reader(in_f);

    for (huffman_size_type i = 0; i < count_of_bytes; ++i) {
        char byte;
        std::vector<bool> code;

        while (!codes_tree.byte_exists(code)) { /// Too long??
            if (bit_reader.read_bit() == 1)
                code.push_back(1);
            else
                code.push_back(0);
        }
        byte = codes_tree.get_byte(code);
        out_f.write(&byte, sizeof(byte));
    }
}

filesize_statistic compress(std::istream &in_f, std::ostream &out_f) {
    filesize_statistic statistic;
    std::streampos begin, end;

    begin = in_f.tellg();
    Rates rates(compress_mode, in_f);
    in_f.seekg(0, std::ios::end);
    end = in_f.tellg();
    statistic.source_data_size = (huffman_size_type)(end - begin);

    HuffmanTree codes_tree(rates);

    begin = out_f.tellp();
    FilePrefix::write_prefix(out_f);
    rates.serialize_to(out_f);
    end = out_f.tellp();
    statistic.additional_data_size = (huffman_size_type)(end - begin);

    begin = out_f.tellp();
    encode_huffman(in_f, out_f, codes_tree);
    end = out_f.tellp();
    statistic.result_data_size = (huffman_size_type)(end - begin);

    return statistic;
}

filesize_statistic decompress(std::istream &in_f, std::ostream &out_f) {
    filesize_statistic statistic;
    std::streampos begin, end;

    begin = in_f.tellg();
    if (!FilePrefix::check_prefix(in_f))
        throw std::runtime_error("Input file wasn't compressed by this program");

    Rates rates(decompress_mode, in_f);
    end = in_f.tellg();
    statistic.additional_data_size = (huffman_size_type)(end - begin);

    /* Build codes */
    HuffmanTree codes_tree(rates);

    std::streampos begin_in_f, end_in_f;
    std::streampos begin_out_f, end_out_f;

    begin_in_f = in_f.tellg();
    begin_out_f = out_f.tellp();
    decode_huffman(in_f, out_f, codes_tree, rates.get_count_of_bytes());
    ///_in_f.seekg(0, std::ios::end);
    end_out_f = out_f.tellp();
    end_in_f = in_f.tellg();
    statistic.source_data_size = (huffman_size_type)(end_in_f - begin_in_f);
    statistic.result_data_size = (huffman_size_type)(end_out_f - begin_out_f);

    return statistic;
}
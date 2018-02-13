//
// Created by mikhail on 13.04.17.
//

#ifndef HW_03_HUFFMAN_H
#define HW_03_HUFFMAN_H

#include <iostream>
#include <string>
#include <map>

#include "huffmanTree.h"
#include "fileBits.h"
#include "rates.h"

void encode_huffman(std::istream &in_f, std::ostream &out_f, const HuffmanTree &codes_tree);
void decode_huffman(std::istream &in_f, std::ostream &out_f, const HuffmanTree &codes_tree,
                    huffman_size_type count_of_bytes);

filesize_statistic compress(std::istream &in_f, std::ostream &out_f);
filesize_statistic decompress(std::istream &in_f, std::ostream &out_f);

#endif //HW_03_HUFFMAN_H

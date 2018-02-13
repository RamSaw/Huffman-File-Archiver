//
// Created by mikhail on 21.04.17.
//

#include <iostream>

#include "rates.h"

Rates::Rates(mode_enum mode, std::istream &in_f) {
    if (mode == compress_mode) {
        /* Count rates */
        char byte;

        in_f.seekg(std::ios_base::beg);
        while (in_f.peek() != std::istream::traits_type::eof()) {
            in_f.read(&byte, sizeof(byte));
            _rates[byte]++;
        }
    } else {
        /* Read rates table */
        huffman_size_type rates_size;

        in_f.read(reinterpret_cast<char *>(&rates_size), sizeof(rates_size));
        for (huffman_size_type i = 0; i < rates_size; ++i) {
            char byte;
            huffman_size_type rate;

            in_f.read(&byte, sizeof(byte));
            in_f.read(reinterpret_cast<char *>(&rate), sizeof(rate));
            _rates[byte] = rate;
        }
    }
}


void Rates::serialize_to(std::ostream &out_f) const {
    huffman_size_type rate_size = _rates.size();

    out_f.write(reinterpret_cast<char *>(&rate_size), sizeof(rate_size));
    for (const auto& rate : _rates) {
        out_f.write(&rate.first, sizeof(rate.first));
        out_f.write(reinterpret_cast<const char *>(&rate.second), sizeof(rate.second));
    }
}

huffman_size_type Rates::size() const {
    return _rates.size();
}

const std::unordered_map<char, huffman_size_type> &Rates::get_all_rates() const {
    return _rates;
}

huffman_size_type Rates::get_count_of_bytes() const {
    huffman_size_type count_of_bytes = 0;

    for (const auto& rate : _rates)
        count_of_bytes += rate.second; /// Can be realized by writing size of input file into compressed file
    return count_of_bytes;
}


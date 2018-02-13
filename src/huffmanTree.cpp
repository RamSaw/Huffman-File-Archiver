//
// Created by mikhail on 14.04.17.
//

#include <deque>
#include <algorithm>

#include "huffmanTree.h"

HuffmanTree::HuffmanTree(const Rates &rates) {
    /* No characters */
    if (rates.size() == 0)
        return;

    /* Case of 1 character */
    if (rates.size() == 1) {
        for (const auto& rate : rates.get_all_rates())
            _codes[rate.first].push_back(0);
    }
    else {
        std::deque<std::pair<huffman_size_type, char>> rates_deq;
        for (const auto &item : rates.get_all_rates())
            rates_deq.push_back(std::make_pair(item.second, item.first));
        std::sort(rates_deq.begin(), rates_deq.end());

        std::deque<std::pair<huffman_size_type, std::string>> min_sums;

        /* Generating reversed codes */
        for (size_t k = 0; k < rates.size() - 1; k++) {
            /* Counting sum of first 2 elements */
            huffman_size_type rates_sum = 0;
            if (rates_deq.size() > 1)
                rates_sum = rates_deq[0].first + rates_deq[1].first;

            huffman_size_type mins_sum = 0;
            if (min_sums.size() > 1)
                mins_sum = min_sums[0].first + min_sums[1].first;

            huffman_size_type rates_mins_sum = 0;
            if (min_sums.size() > 0 && rates_deq.size() > 0)
                rates_mins_sum = rates_deq[0].first + min_sums[0].first;

            /* Selecting min sum */
            if (rates_sum != 0 &&
                (rates_mins_sum == 0 || rates_sum <= rates_mins_sum) &&
                (mins_sum == 0 || rates_sum <= mins_sum)) {
                std::string conc;

                conc.push_back(rates_deq[0].second);
                conc.push_back(rates_deq[1].second);
                min_sums.push_back(std::make_pair(rates_deq[0].first + rates_deq[1].first, conc));

                _codes[conc[0]].push_back(0);
                _codes[conc[1]].push_back(1);

                rates_deq.pop_front();
                rates_deq.pop_front();
            } else if (rates_mins_sum != 0 &&
                       (rates_sum == 0 || rates_mins_sum <= rates_sum) &&
                       (mins_sum == 0 || rates_mins_sum <= mins_sum)) {
                std::string conc;

                conc.push_back(rates_deq[0].second);
                min_sums.push_back(std::make_pair(rates_deq[0].first + min_sums[0].first, conc + min_sums[0].second));

                _codes[conc[0]].push_back(0);
                for (const auto &c : min_sums[0].second)
                    _codes[c].push_back(1);

                rates_deq.pop_front();
                min_sums.pop_front();
            } else {
                min_sums.push_back(std::make_pair(min_sums[0].first + min_sums[1].first,
                                                  min_sums[0].second + min_sums[1].second));

                for (const auto &c : min_sums[0].second)
                    _codes[c].push_back(0);
                for (const auto &c : min_sums[1].second)
                    _codes[c].push_back(1);

                min_sums.pop_front();
                min_sums.pop_front();
            }
        }
    }

    /* Reverse again to get straight codes */
    for (auto &code : _codes) {
        reverse(code.second.begin(), code.second.end());
        _bytes_by_codes[code.second] = code.first;
    }
}

const std::vector<bool>& HuffmanTree::get_code(char c) const {
    return _codes.at(c);
}

bool HuffmanTree::byte_exists(const std::vector<bool> &code) const {
    return _bytes_by_codes.find(code) != _bytes_by_codes.end();
}

char HuffmanTree::get_byte(const std::vector<bool> &code) const {
    return _bytes_by_codes.at(code);
}
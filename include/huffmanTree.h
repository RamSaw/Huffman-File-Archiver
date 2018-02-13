//
// Created by mikhail on 14.04.17.
//

#ifndef HW_03_HUFFMANTREE_H
#define HW_03_HUFFMANTREE_H

#include <string>
#include <map>
#include <unordered_map>

#include "rates.h"

class HuffmanTree {
private:
    std::unordered_map<char, std::vector<bool>> _codes;
    std::unordered_map<std::vector<bool>, char> _bytes_by_codes; // Unless it would be O(n), finding char by string in _codes

public:
    /*
     * Action: generates codes by rates and swaps codes(value) and bytes(keys) to _bytes_by_codes.
     * Contract: if success then _codes and _bytes_by_codes are initialized correctly and object is in correct state.
     * Unless behaviour is undefined: this could happen because of overflow of type or rates are more than infinite_rate.
     * But infinite_rate defined by max limit of huffman_size_type and for most of files rate won't exceed infinite_rate.
     */
    HuffmanTree(const Rates &rates);

    /*
     * Action: returns code of byte by byte.
     * Contract: if code of byte exists, method will succeed and object remains in correct state.
     * If there is no byte, it throws out_of_range exception.
     */
    const std::vector<bool> & get_code(char c) const;

    /*
     * Action: checks if byte with such code exists.
     * Contract: safe, no exceptions, object remains in correct state.
     */
    bool byte_exists(const std::vector<bool> &code) const;

    /*
     * Action: returns code of byte by byte.
     * Contract: if byte of code exists, method will succeed and object remains in correct state.
     * If there is no code, it throws out_of_range exception.
     */
    char get_byte(const std::vector<bool> &code) const;
};

#endif //HW_03_HUFFMANTREE_H

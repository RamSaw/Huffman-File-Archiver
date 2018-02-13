//
// Created by mikhail on 21.04.17.
//

#ifndef HW_03_RATES_H
#define HW_03_RATES_H


#include <unordered_map>

#include "huffmanTypes.h"

class Rates {
private:
    std::unordered_map<char, huffman_size_type> _rates;

public:
    /*
     * Action: count rates from uncompressed file or read rates table from compressed.
     * Contract: after constructor _rates is initialized by rates of bytes and object is in correct state.
     * If file stream throws exception, no mem leaks occurs, _rates will be destroyed.
     */
    Rates(mode_enum mode, std::istream &in_f);

    /*
     * Action: writes rates table to out_f file.
     * Contract: _rates does not change, object remains in correct state.
     * If file stream throws exception, object destructed, no mem leaks.
     */
    void serialize_to(std::ostream &out_f) const;

    /*
     * Action: returns size of _rates.
     * Contract: Safe, _rates does not change, remains in correct state.
     */
    huffman_size_type size() const;

    /*
     * Action: returns link on _rates.
     * Contract: Safe, _rates does not change(returns const link), remains in correct state.
     * Needed for iterating on rates.
     */
    const std::unordered_map<char, huffman_size_type>& get_all_rates() const;

    /*
     * Action: returns sum of bytes rates.
     * Contract: Safe, _rates does not change, remains in correct state.
     * Needed to understand how many bytes must be decoded.
     */
    huffman_size_type get_count_of_bytes() const;
};


#endif //HW_03_RATES_H

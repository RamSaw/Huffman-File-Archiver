//
// Created by mikhail on 14.04.17.
//

#ifndef HW_03_FILEBITS_H
#define HW_03_FILEBITS_H

#include <iostream>

#include "huffmanTypes.h"

class BitWriter {
private:
    char _byte;
    huffman_size_type _pos;
    std::ostream &_out_f;
public:
    /*
     * Action: initializes reference _out_f, _bytes with 0, _pos with 0.
     * Contract: no exceptions, object will be created in correct state.
     */
    BitWriter(std::ostream &_out_f);

    /*
     * Action: writes one single bit to _out_f.
     * Contract: if no exception, object remains in correct state, _byte and _pos will be changed,
     * Writing can throw an exception.
     */
    void write_bit(bool bit);

    /*
     * Action: writes all bits remained in buffer(_byte).
     * Contract: if no exception, object remains in correct state, _byte and _pos will be changed,
     * Writing can throw an exception.
     */
    void flush();

    /*
     * Action: calls flush().
     * Contract: the same as flush() and if success then object will be destroyed successfully.
     */
    ~BitWriter();
};

class BitReader {
private:
    char _byte;
    huffman_size_type _pos;
    std::istream &_in_f;
public:
    /*
     * Action: initializes reference _in_f, _pos with 8(to initialize _byte in first call of read_bit()).
     * Contract: no exceptions, object will be created in correct state.
     */
    BitReader(std::istream &_in_f);

    /*
     * Action: reads one single bit from _in_f.
     * Contract: if no exception, object remains in correct state, _byte and _pos will be changed,
     * Reading can throw an exception.
     */
    bool read_bit();
};


#endif //HW_03_FILEBITS_H

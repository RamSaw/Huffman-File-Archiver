//
// Created by mikhail on 14.04.17.
//

#include "fileBits.h"

BitWriter::BitWriter(std::ostream &_out_f) : _byte(0), _pos(0), _out_f(_out_f) {}

void BitWriter::write_bit(bool bit) {
    if (_pos == 8)
        flush();
    if (bit == 1) {
        _byte |= (1 << _pos);
    }
    // bit == '0' can be not set, because supported invariant that _byte = 0 after flush
    _pos++;
}

void BitWriter::flush() {
    if (_pos != 0) {
        _out_f.write(&_byte, sizeof(_byte));
        _pos = 0;
        _byte = 0;
    }
}

BitWriter::~BitWriter() {
    flush();
}

BitReader::BitReader(std::istream &_in_f) : _pos(8), _in_f(_in_f) {}

bool BitReader::read_bit() {
    if (_pos == 8) {
        _in_f.read(&_byte, sizeof(_byte));
        _pos = 0;
    }
    return (_byte >> _pos++) & static_cast<char>(1);
}

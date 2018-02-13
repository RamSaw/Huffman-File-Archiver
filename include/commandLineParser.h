//
// Created by mikhail on 20.04.17.
//

#ifndef HW_03_COMMANDLINEPARSER_H
#define HW_03_COMMANDLINEPARSER_H

#include <string>
#include "huffman.h"

struct parameters {
    mode_enum mode;
    std::string in_filename, out_filename;

    parameters(mode_enum mode, const std::string &in_filename, const std::string &out_filename) :
            mode(mode), in_filename(in_filename), out_filename(out_filename) {}
};

parameters parse_parameters(const std::vector<std::string> &input_parameters);

#endif //HW_03_COMMANDLINEPARSER_H

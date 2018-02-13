//
// Created by mikhail on 20.04.17.
//

#include <cstring>
#include <stdexcept>

#include "commandLineParser.h"

parameters parse_parameters(const std::vector<std::string> &input_parameters) {
    std::string in_f, out_f;
    mode_enum mode = no_mode;

    std::size_t i = 1;
    while (i < input_parameters.size()) {
        if ("-c" == input_parameters[i]) {
            mode = compress_mode;
        }
        else if ("-u" == input_parameters[i]) {
            mode = decompress_mode;
        }
        else if ("-o" == input_parameters[i]) {
            if (i + 1 < input_parameters.size())
                out_f = input_parameters[i + 1]; /// ??? strcpy
            else
                throw std::runtime_error("Invalid arguments: output filename is missing");
            i++;
        }
        else if ("-f" == input_parameters[i]) {
            if (i + 1 < input_parameters.size())
                in_f = input_parameters[i + 1];
            else
                throw std::runtime_error("Invalid arguments: input filename is missing");
            i++;
        }
        else {
            throw std::runtime_error("Invalid arguments: unknown key");
        }
        i++;
    }

    if (mode == no_mode) {
        throw std::runtime_error("Invalid arguments: no mode");
    }

    return parameters(mode, in_f, out_f);
}

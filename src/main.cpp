#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "huffman.h"
#include "commandLineParser.h"

int main(int argc, char** argv) {
    try {
        parameters parsed_parameters = parse_parameters(std::vector<std::string>(argv, argv + argc));
        filesize_statistic statistic;

        /* Opening files */
        std::ifstream in_f;
        std::ofstream out_f;

        in_f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        in_f.open(parsed_parameters.in_filename, std::ios::binary);

        out_f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        out_f.open(parsed_parameters.out_filename, std::ios::binary);

        if (parsed_parameters.mode == compress_mode) {
            statistic = compress(in_f, out_f);
        }
        else {
            statistic = decompress(in_f, out_f);
        }

        // Output statistics
        std::cout << statistic.source_data_size << '\n';
        std::cout << statistic.result_data_size << '\n';
        std::cout << statistic.additional_data_size << '\n';
    }
    catch (std::fstream::failure &fstream_error) {
        std::cerr << fstream_error.what() << " Error from reading/writing from/to file\n";
    }
    catch (std::runtime_error &re){
        std::cerr << re.what() << ". Use -c to compress_mode and -u to uncompress,"
                " -f - input file, -o - output file.\n";
    }
    catch (std::exception &except) {
        std::cerr << except.what();
    }
    return 0;
}

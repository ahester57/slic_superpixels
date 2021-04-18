// cla_parse.hpp : Parse given command line arguments.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef CLA_PARSE_H
#define CLA_PARSE_H

#include <iostream>

int parse_arguments(
    int argc,
    const char** argv,
    std::string* input_image_filename,
    std::string* output_image_filename,
    float* scale_image_value,
    bool* blur_output,
    bool* equalize_output
);

#endif

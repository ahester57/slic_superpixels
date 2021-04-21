// cla_parse.hpp : Parse given command line arguments.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef CLA_PARSE_H
#define CLA_PARSE_H

#include <iostream>

int parse_arguments(
    int argc,
    const char** argv,
    std::string* template_image_filename,
    std::string* target_image_filename,
    float* scale_image_value,
    bool* blur_output,
    bool* equalize_output,
    bool* sharpen_output,
    int* region_size,
    float* ruler,
    std::string* algorithm,
    int* connectivity
);

#endif

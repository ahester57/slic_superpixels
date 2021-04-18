// string_helper.hpp : String functions
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include <opencv2/core/core.hpp>


std::vector<std::string> split (std::string s, char delim);

std::string cv_type_to_str(cv::Mat img);

#endif

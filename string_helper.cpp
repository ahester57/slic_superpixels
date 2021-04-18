
// string_helper.cpp : Transformation functions
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include <sstream>

#include "./include/string_helper.hpp"


std::vector<std::string>
split (std::string s, char delim)
{
    // cred: https://stackoverflow.com/a/46931770
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

std::string
cv_type_to_str(cv::Mat img)
{
    int type = img.type();
    uint8_t channels = img.channels();
    // cred: https://stackoverflow.com/a/17820615
    std::string r;
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch ( depth ) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }

    r += "C";
    r += std::to_string(channels);

    return r;
}

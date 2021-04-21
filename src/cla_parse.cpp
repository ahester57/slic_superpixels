// cla_parse.cpp : Parse given command line arguments.
// Austin Hester CS542o nov 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "../include/cla_parse.hpp"


// parse command line arguments
int
parse_arguments(
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
) {
    cv::String keys =
        "{@template_image |      | Template image. Provides theme.}"
        "{@target_image   |      | Target image. Provides structure. Defaults to template image.}"
        // "{grayscale g     |      | Read Input As Grayscale}"
        "{scale sc        |1.f   | Scale input image size using Affine Transform}"
        "{equalize e      |      | Output Image - Equalize}"
        "{blur b          |      | Output Image - Blur}"
        "{sharpen sh      |      | Output Image - Sharpen}"
        "{algorithm a     |SLIC  | Name of SLIC algorithm variant\n\t\t\t - SLIC segments image using a desired region size\n\t\t\t - SLICO optimizes using an adaptive compactness factor\n\t\t\t - MSLIC optimizes using manifold methods giving more context-sensitive superpixels}"
        "{region_size s   |10    | Chooses an average superpixel size measured in pixels}"
        "{ruler r         |10.f  | Chooses the enforcement of superpixel smoothness}"
        "{connectivity c  |25    | The minimum element size in percents that should be absorbed into a bigger superpixel}"
        "{help h          |      | Show Help Message}";

    cv::CommandLineParser parser =  cv::CommandLineParser(argc, argv, keys);

    parser.printMessage();

    if (parser.has("h")) {
        parser.about("About.");
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        return -1;
    }

    try {
        *template_image_filename = (std::string) parser.get<std::string>(0).c_str();
        assert( template_image_filename->size() > 0 );
    } catch (...) {
        std::cerr << "Failed to parse template_image argument!:" << std::endl;
        return -1;
    }

    try {
        *target_image_filename = (std::string) parser.get<std::string>(1).c_str();
        if (target_image_filename->size() == 0) {
            *target_image_filename = (std::string) parser.get<std::string>(0).c_str();
        }
        assert( target_image_filename->size() > 0 );
    } catch (...) {
        std::cerr << "Failed to parse target_image argument!:" << std::endl;
        return -1;
    }

    try {
        *scale_image_value = (float) parser.get<float>("sc");
        assert( *scale_image_value > 0.f && *scale_image_value < 10.f );
    } catch (...) {
        std::cerr << "Failed to parse scale argument!:" << std::endl;
        return -1;
    }

    try {
        *blur_output = parser.has("b");
    } catch (...) {
        std::cerr << "Failed to parse blur argument!:" << std::endl;
        return -1;
    }

    try {
        *equalize_output = parser.has("e");
    } catch (...) {
        std::cerr << "Failed to parse equalize argument!:" << std::endl;
        return -1;
    }

    try {
        *sharpen_output = parser.has("sh");
    } catch (...) {
        std::cerr << "Failed to parse sharpen argument!:" << std::endl;
        return -1;
    }

    try {
        *region_size = parser.get<int>("s");
        assert( *region_size > 0 && *region_size <= 400 );
    } catch (...) {
        std::cerr << "Failed to parse region_size argument!:" << std::endl;
        return -1;
    }

    try {
        *ruler = parser.get<float>("r");
        assert( *ruler >= 0.f && *ruler <= 100.f );
    } catch (...) {
        std::cerr << "Failed to parse ruler argument!:" << std::endl;
        return -1;
    }

    try {
        *algorithm = (std::string) parser.get<std::string>("a").c_str();
        assert( algorithm->size() > 0 );
    } catch (...) {
        std::cerr << "Failed to parse algorithm argument!:" << std::endl;
        return -1;
    }

    try {
        *connectivity = parser.get<int>("c");
        assert( *connectivity >= 0 && *connectivity <= 100 );
    } catch (...) {
        std::cerr << "Failed to parse connectivity argument!:" << std::endl;
        return -1;
    }

    std::cout << std::endl << "Shortcuts:" << std::endl << "\tq\t- quit" << std::endl << std::endl;

    return 1;
}

// cla_parse.cpp : Parse given command line arguments.
// Austin Hester CS542o nov 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "./include/cla_parse.hpp"


// parse command line arguments
int
parse_arguments(
    int argc,
    const char** argv,
    std::string* input_image_filename,
    std::string* output_image_filename,
    float* scale_image_value,
    bool* blur_output,
    bool* equalize_output
) {
    cv::String keys =
        "{@input_image    |<none>| Input Image}"
        "{@output_image   |<none>| Output Image}"
        // "{grayscale g     |      | Read Input As Grayscale}"
        "{scale sc        |1.f   | Scale Input Image Size using Affine Transform}"
        "{equalize e      |      | Equalize Output Image}"
        "{blur b          |      | Blur Output Image}"
        // "{hsv_plane p     |2     | HSV Plane to Use: 0 = H, 1 = S, 2 = V}"
        "{algorithm a     |SLIC  | Name of SLIC algorithm variant\n\t\t\tSLIC segments image using a desired region size\n\t\t\tSLICO optimizes using an adaptive compactness factor\n\t\t\tMSLIC optimizes using manifold methods giving more context-sensitive superpixels}"
        "{size s          |10    | Chooses an average superpixel size measured in pixels}"
        "{ruler r         |10.f  | Chooses the enforcement of superpixel smoothness}"
        "{help h          |      | Show Help Message}";

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("h")) {
        parser.printMessage();
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    try {
        *input_image_filename = (std::string) parser.get<std::string>(0).c_str();
        assert( input_image_filename->size() > 0 );
    } catch (...) {
        std::cerr << "Failed to parse imagefile argument!:" << std::endl;
        return -1;
    }

    try {
        *output_image_filename = (std::string) parser.get<std::string>(1).c_str();
        if (output_image_filename->size() == 0) {
            *output_image_filename = "output_" + *input_image_filename;
        }
    } catch (...) {
        std::cerr << "Failed to parse templatefile argument!:" << std::endl;
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

    // try {
    //     *hsv_plane = (float) parser.get<int>("p");
    //     assert( *hsv_plane >= 0 && *hsv_plane <= 2 );
    // } catch (...) {
    //     std::cerr << "Failed to parse hsv_plane argument!:" << std::endl;
    //     return -1;
    // }

    // try {
    //     *grayscale = parser.has("g");
    //     assert( *grayscale >= 0 && *grayscale <= 2 );
    // } catch (...) {
    //     std::cerr << "Failed to parse grayscale argument!:" << std::endl;
    //     return -1;
    // }

    std::cout << std::endl << "Shortcuts:" << std::endl << "\tq\t- quit" << std::endl << std::endl;

    return 1;
}

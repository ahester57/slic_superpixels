// equalize.cpp : equalizer functions
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./include/equalize.hpp"

#include "./include/hsv_convert.hpp"


// equalize given image
void
equalize_image(cv::Mat* image)
{
    int n_channels = image->channels();
    assert( n_channels == 1 || n_channels == 3 );

    if (n_channels == 1) {
        cv::equalizeHist( *image, *image );
    } else if (n_channels == 3) {
        cv::Mat hsv_image;
        bgr_to_hsv( *image, &hsv_image );
        cv::Mat hsv_planes[3];
        cv::split( hsv_image, hsv_planes );
        cv::equalizeHist( hsv_planes[2], hsv_planes[2] );
        cv::merge( hsv_planes, 3, hsv_image );
        hsv_to_bgr( hsv_image, image );
    }
}

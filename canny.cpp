// canny.cpp : Canny Edge Detections
// Austin Hester CS642o april 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./include/canny.hpp"

#include "./include/hsv_convert.hpp"


// draw contours of canny edge detection
cv::Mat
draw_canny_contours(cv::Mat image)
{
    // blur image
    cv::Mat canny_output;
    cv::GaussianBlur( image, canny_output, cv::Size( 3, 3 ), 0.5f );

    // compute canny edges
    cv::Canny( canny_output, canny_output, 75, 200 );

    // find the contours to draw
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours( canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );

    // draw the contours
    cv::Mat canvas = cv::Mat::zeros( canny_output.size(), CV_8U );
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours( canvas, contours, i, cv::Scalar(255), 1, cv::LINE_8, hierarchy, 0 );
    }

    canny_output.release();
    return canvas;
}

/**
 * plane: 
 * 0 = Hue
 * 1 = Saturation
 * 2 = Vintensity
 * 
**/
cv::Mat
draw_color_canny_contours(cv::Mat image, int hsv_plane)
{
    // Convert to HSV
    cv::Mat hsv_image;
    bgr_to_hsv( image, &hsv_image );

    // Split HSV into parts
    cv::Mat hsv_planes[3];
    cv::split( hsv_image, hsv_planes );

    // canny edge detection, returning contour map
    cv::Mat canny_edges = draw_canny_contours( hsv_planes[hsv_plane] );

    hsv_planes[0].release();
    hsv_planes[1].release();
    hsv_planes[2].release();
    hsv_image.release();
    return canny_edges;
}

// created binary image of regions
cv::Mat
create_binary_image_from_canny_edges(cv::Mat canny_edges, cv::Mat mask)
{
    cv::Mat canny_edges_8U; // aka "borders"
    canny_edges.convertTo( canny_edges_8U, CV_8U, 100 );
    cv::bitwise_not( canny_edges_8U, canny_edges_8U );
    // apply mask to map
    canny_edges_8U.setTo( cv::Scalar(0, 0, 0), ~mask );
    // threshold bordered map output
    cv::threshold( canny_edges_8U, canny_edges_8U, 55, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );
    return canny_edges_8U;
}

// segmentation.cpp : This file contains functions useful for segmentation
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include "./include/segmentation.hpp"

#define DEBUG 0


// find normalized distance transform of binary image
cv::Mat
distance_finder(cv::Mat binary_image)
{
    cv::Mat distance;
    cv::distanceTransform( binary_image, distance, cv::DIST_L2, 3 );
    cv::normalize( distance, distance, 0.f, 1.f, cv::NORM_MINMAX );
    return distance;
}

// Trivial "black background only" background finder
cv::Mat
make_background_mask(cv::Mat image)
{
    //TODO make this better at background detection, not just black backgrounds
    cv::Mat mask;
    cv::inRange( image, cv::Scalar::all(0), cv::Scalar::all(0), mask );
    return ~mask;
}

// find drawable contours from distance transformation
std::vector<std::vector<cv::Point>>
find_distance_contours(cv::Mat distance_transform)
{
    cv::threshold( distance_transform, distance_transform, 0.01f, 1.f, cv::THRESH_BINARY );

    cv::Mat distance_8U;
    distance_transform.convertTo( distance_8U, CV_8U );

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours( distance_8U, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

    distance_8U.release();
    return contours;
}

// draw singular contour
cv::Mat
draw_contour_as_marker(std::vector<std::vector<cv::Point>> contours, cv::Size canvas_size, int marker_value)
{
    cv::Mat marker = cv::Mat::zeros( canvas_size, CV_8U );
    cv::drawContours( marker, contours, marker_value - 1, cv::Scalar( 255 ), -1 );
    return marker;
}

// draw all contours
cv::Mat
draw_contours_as_markers(std::vector<std::vector<cv::Point>> contours, cv::Size canvas_size)
{
    cv::Mat markers = cv::Mat::zeros( canvas_size, CV_32S );
    for (size_t i = 0; i < contours.size(); i++) {
        int ii = static_cast<int>( i );
        cv::drawContours( markers, contours, ii, cv::Scalar( i + 1 ), -1 );
    }

    return markers;
}

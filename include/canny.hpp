// canny.hpp : Canny Edge Detections
// Austin Hester CS642o april 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef CANNY_H
#define CANNY_H

#include <opencv2/core/core.hpp>

cv::Mat draw_canny_contours(cv::Mat image);

cv::Mat draw_color_canny_contours(cv::Mat image, int hsv_plane);

cv::Mat create_binary_image_from_canny_edges(cv::Mat canny_edges, cv::Mat mask);

#endif

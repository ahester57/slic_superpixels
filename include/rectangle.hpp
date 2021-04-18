// rectangle.hpp : cv::Rect functions
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/core/core.hpp>


cv::Rect center_and_double_rect(cv::Rect rect, cv::Size target_size);

std::vector<cv::Rect> draw_bounding_rects(std::vector<std::vector<cv::Point>> contours);

#endif

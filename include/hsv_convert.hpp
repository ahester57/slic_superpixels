// hsv_convert.hpp : Convert color images to and from HSV
// Austin Hester CS542o dec 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef HSV_CONVERT_H
#define HSV_CONVERT_H

#include <opencv2/core/core.hpp>

void bgr_to_hsv(cv::Mat bgr, cv::Mat* hsv);

void hsv_to_bgr(cv::Mat hsv, cv::Mat* bgr);

#endif

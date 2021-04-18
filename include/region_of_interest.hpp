// region_of_interest.hpp : ROI
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef REGION_OF_INTEREST_H
#define REGION_OF_INTEREST_H

#include <opencv2/core/core.hpp>


cv::Mat extract_roi_safe(cv::Mat image, cv::Rect rect);

#endif

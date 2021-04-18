// region_of_interest.cpp : ROI
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./include/region_of_interest.hpp"


// extract ROI ignoring out of bounds
cv::Mat
extract_roi_safe(cv::Mat image, cv::Rect rect)
{
    // adjust contour_bounds to prevent out of bounds errors
    cv::Rect image_rect = cv::Rect( {}, image.size() );
    cv::Rect intersection = image_rect & rect;
    cv::Rect inter_roi = intersection - image_rect.tl();

    // grab the ROI
    return image( inter_roi );
}

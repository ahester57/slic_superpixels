// rectangle.cpp : cv::Rect functions
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "./include/rectangle.hpp"


// double size of rect of and place at center
cv::Rect
center_and_double_rect(cv::Rect rect, cv::Size target_size)
{
    int old_x = rect.x;
    rect.x = target_size.width / 2 - rect.width;
    if (old_x < 0) {
        rect.x += 2 * old_x;
    }
    int old_y = rect.y;
    rect.y = target_size.height / 2 - rect.height;
    if (old_y < 0) {
        rect.y += 2 * old_y;
    }
    //TODO figure this out just padding for now
    rect += cv::Size(
        (old_x < 0) ? rect.width + rect.x :
            (old_x + rect.width > target_size.width) ? 2 * (target_size.width - old_x) - rect.width :
                rect.width,
        (old_y < 0) ? rect.height + rect.y :
            (old_y + rect.height > target_size.height) ? 2 * (target_size.height - old_y) - rect.height :
                rect.height
    );
    return rect;
}

// create auxillary array of bounding rectangles
std::vector<cv::Rect>
draw_bounding_rects(std::vector<std::vector<cv::Point>> contours)
{
    std::vector<cv::Rect> boundaries = std::vector<cv::Rect>( contours.size() );
    for (size_t i = 0; i < contours.size(); i++) {
        int ii = static_cast<int>( i );
        std::vector<cv::Point> contours_poly;
        cv::approxPolyDP( contours[ii], contours_poly, 1, true );
        boundaries[ii] = cv::boundingRect( contours_poly );
        // bump up size of rects just a bit
        boundaries[ii].x -= 5;
        boundaries[ii].y -= 5;
        boundaries[ii] += cv::Size( 10, 10 );
    }

    return boundaries;
}

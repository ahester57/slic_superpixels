// slic_helper.hpp : Helper Functions
// Austin Hester CS542o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef SLIC_HELPER_H
#define SLIC_HELPER_H

#include <opencv2/core/core.hpp>

#include <vector>


typedef struct {
    std::string window_name;
    cv::Mat input_image;
    cv::Mat input_mask;
    cv::Mat region_of_interest;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Rect> boundaries;
    cv::Mat markers;
    cv::Mat marked_up_image;
    int algorithm;
    int region_size;
    float ruler;
    int connectivity;
} SLICData;


void superpixel(SLICData* image_data);

int slic_string_to_int(std::string algorithm_string);

void segment(SLICData* map_data, int hsv_plane = 2);

void select_region(SLICData* map_data, int marker_value);

cv::Mat extract_selected_region(SLICData* map_data, int marker_value);

cv::Mat paint_map_atop_region(SLICData* map_data, int marker_value, cv::Mat drawn_contour);

cv::Mat paint_region_over_map(SLICData* map_data, cv::Rect bounding_rect);

cv::Mat make_border_from_size_and_rect(cv::Mat image, cv::Size target_size, cv::Rect rect);

void draw_in_states(SLICData* map_data);

void draw_in_roi(SLICData* map_data, int marker_value);

#endif

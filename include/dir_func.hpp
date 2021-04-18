// dir_func.hpp : Directory functions
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef DIR_FUNC_H
#define DIR_FUNC_H

#include <opencv2/core/core.hpp>


cv::Mat open_image(std::string file_path, bool grayscale = false);

void open_image_from_text(std::string file_path, cv::Mat* dst);

int create_dir_recursive(std::string dst_file);

int write_img_to_file(cv::Mat image, std::string output_dir, std::string file_name);

template <typename T>
int write_img_to_file_as_text(cv::Mat image, std::string output_dir, std::string file_name);

#endif

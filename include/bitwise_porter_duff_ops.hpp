// bitwise_porter_duff_operators.hpp : porter-duff operators
// Austin Hester CS642o feb 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef BITWISE_PORTER_DUFF_OPS_H
#define BITWISE_PORTER_DUFF_OPS_H

#include <opencv2/core/core.hpp>

// Ir = 0
// Mr = 0
cv::Mat bitwise_clear_i1  (cv::Mat src, cv::Mat mask);

// Ir = I1
// Mr = M1
cv::Mat bitwise_copy_i1   (cv::Mat src, cv::Mat mask);

// Ir = (I1 ∧ M1) ∨ (I2 ∧ M2 ∧ ¬M1)
// Mr = M1 ∨ M2
cv::Mat bitwise_i1_over_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2);

// Ir = I1
// Mr = M1 ∧ M2
cv::Mat bitwise_i1_in_i2  (cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2);

// Ir = I1
// Mr = M1 ∧ ¬M2
cv::Mat bitwise_i1_out_i2 (cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2);

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Mat bitwise_i1_atop_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2);

// Ir = (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2)
// Mr = (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)
cv::Mat bitwise_i1_xor_i2 (cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2);

#endif

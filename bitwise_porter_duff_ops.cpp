// bitwise_porter_duff_ops.cpp : bitwise porter-duff operators on whole image
// Austin Hester CS642o feb 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>

#include "./include/bitwise_porter_duff_ops.hpp"


// Ir = 0
// Mr = 0
cv::Mat
bitwise_clear_i1(cv::Mat src, cv::Mat mask)
{
    cv::Mat Ir;
    cv::bitwise_and(src, src, Ir);
    cv::bitwise_xor(Ir, Ir, Ir, mask);
    return Ir;
}

// Ir = I1
// Mr = M1
cv::Mat
bitwise_copy_i1(cv::Mat src, cv::Mat mask)
{
    cv::Mat Ir;
    cv::bitwise_and(src, src, Ir, mask);
    return Ir;
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ M2 ∧ ¬M1)
// Mr = M1 ∨ M2
cv::Mat
bitwise_i1_over_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    cv::Mat i1, i2, i3;
    cv::bitwise_and(img1, img1, i1, mask1);
    cv::bitwise_and(img2, img2, i2, mask2);
    cv::bitwise_and(i2, i2, i3, ~mask1);
    cv::Mat Mr;
    cv::bitwise_or(mask1, mask2, Mr);
    cv::Mat Ir;
    cv::bitwise_or(i1, i3, Ir, Mr);
    i1.release();
    i2.release();
    i3.release();
    Mr.release();
    return Ir;
}

// Ir = I1
// Mr = M1 ∧ M2
cv::Mat
bitwise_i1_in_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    cv::Mat Mr;
    cv::bitwise_and(mask1, mask2, Mr);
    cv::Mat Ir;
    cv::bitwise_and(img1, img1, Ir, Mr);
    Mr.release();
    return Ir;
}

// Ir = I1
// Mr = M1 ∧ ¬M2
cv::Mat
bitwise_i1_out_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    cv::Mat Mr;
    cv::bitwise_and(mask1, ~mask2, Mr);
    cv::Mat Ir;
    cv::bitwise_and(img1, img1, Ir, Mr);
    Mr.release();
    return Ir;
}

// Ir = (I1 ∧ M1) ∨ (I2 ∧ ¬M2)
// Mr = M2
cv::Mat
bitwise_i1_atop_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    cv::Mat i1, i2;
    cv::bitwise_and(img1, img1, i1, mask1);
    cv::bitwise_and(img2, img2, i2, ~mask2);
    cv::Mat Ir;
    cv::bitwise_or(i1, i2, Ir, mask2);
    i1.release();
    i2.release();
    return Ir;
}

// Ir = (I1 ∧ M1 ∧ ¬M2) ∨ (I2 ∧ ¬M1 ∧ M2)
// Mr = (M1 ∧ ¬M2) ∨ (¬M1 ∧ M2)
cv::Mat
bitwise_i1_xor_i2(cv::Mat img1, cv::Mat img2, cv::Mat mask1, cv::Mat mask2)
{
    cv::Mat i1, i2, i3, i4;
    cv::bitwise_and(img1, img1, i1, mask1);
    cv::bitwise_and(i1, i1, i2, ~mask2);

    cv::bitwise_and(img2, img2, i3, ~mask1);
    cv::bitwise_and(i3, i3, i4, mask2);

    cv::Mat Mr = (mask1 & ~mask2) | (~mask1 & mask2);
    cv::Mat Ir;
    cv::bitwise_or(i2, i4, Ir, Mr);
    i1.release();
    i2.release();
    i3.release();
    i4.release();
    Mr.release();
    return Ir;
}

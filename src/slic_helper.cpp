// slic_helper.cpp : This file contains the helper functions for the main
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ximgproc/slic.hpp>

#include <iostream>
#include <map>

#include "../include/slic_helper.hpp"

#include "../include/affine.hpp"
#include "../include/bitwise_porter_duff_ops.hpp"
#include "../include/canny.hpp"
#include "../include/rectangle.hpp"
#include "../include/region_of_interest.hpp"
#include "../include/segmentation.hpp"

#define DEBUG 1

#if DEBUG
    #include <opencv2/highgui/highgui.hpp>
    #include <ctime>

    #include "../include/dir_func.hpp"
    #include "../include/string_helper.hpp"
#endif


void
superpixel(SLICData* image_data)
{
#if DEBUG
    std::clock_t clock_begin, clock_end;
    clock_begin = std::clock();
#endif

    cv::Ptr<cv::ximgproc::SuperpixelSLIC> superpixels;
    superpixels = cv::ximgproc::createSuperpixelSLIC(
        image_data->input_image,
        image_data->algorithm,
        image_data->region_size,
        image_data->ruler
    );

    // generate the segments
    superpixels.get()->iterate(7);
    // level of connectivity
    superpixels.get()->enforceLabelConnectivity( image_data->connectivity );
    // label contours
    superpixels.get()->getLabelContourMask( image_data->input_mask );
    // labels
    superpixels.get()->getLabels( image_data->markers );
    // num superpixels
    image_data->num_superpixels = superpixels.get()->getNumberOfSuperpixels();
    superpixels.release();

#if DEBUG
    clock_end = std::clock();
    std::printf( "\nSuperpixel Time Elapsed: %f (ms)\n", (float)( clock_end - clock_begin ) / CLOCKS_PER_SEC * 1000 );

    char metadata[50];
    std::sprintf( metadata, "a_%d_s_%d_r_%f_c_%d.png",
        image_data->algorithm,
        image_data->region_size,
        image_data->ruler,
        image_data->connectivity
    );
    std::printf( "%s\n", metadata );

    // normalize markers for output (won't be recoverable, but looks cool)
    cv::Mat markers;
    cv::normalize( image_data->markers, markers, 0, 255, cv::NORM_MINMAX );
    markers.convertTo( markers, CV_8U );

    // save both
    cv::imshow( "SLIC Label Markers", markers );
    write_img_to_file( markers, "./out/slic_markers", metadata );
    write_img_to_file( image_data->markers, "./out/slic_markers_32S", metadata );
    markers.release();

    cv::imshow( "SLIC Label Contours", image_data->input_mask );
    write_img_to_file( image_data->input_mask, "./out/slic_contours", metadata );
    cv::waitKey(0);
#endif
}

// convert given slic_string type to enum int
int
slic_string_to_int(std::string algorithm_string)
{
    std::map<std::string, int> algorithm_string_map = {
        { "SLIC",  cv::ximgproc::SLIC  },
        { "SLICO", cv::ximgproc::SLICO },
        { "MSLIC", cv::ximgproc::MSLIC }
    };
    int algorithm = algorithm_string_map[algorithm_string];
    // assertion to prevent them from typing wrong and getting translation
    assert(algorithm > 99 && algorithm < 103);
    return algorithm;
}


// select a region. called from mouse listener
void
select_region(SLICData* image_data, int marker_value)
{

    // zero-out region of interest
    image_data->marked_up_image = cv::Mat::zeros( image_data->input_image.size(), image_data->input_image.type() );

    // draw original map back on
    draw_on_original( image_data, marker_value );

    // highlight selected region
    // draw_in_roi( image_data, marker_value );

    // get bounding rect
    // cv::Rect bounding_rect = image_data->boundaries[marker_value - 1];

    // extract the ROI
    // cv::Mat region_only = extract_selected_region( image_data, marker_value );

    // double the size
    // region_only = resize_affine( region_only, 2.f );

    // copy the region to image_data
    // region_only.copyTo( image_data->region_of_interest );
    // region_only.release();

    // double size of rect of roi
    // bounding_rect = center_and_double_rect( bounding_rect, image_data->marked_up_image.size() );

}

// paint real map atop the region of interest's mask
cv::Mat
paint_map_atop_region(SLICData* image_data, int marker_value, cv::Mat drawn_contour)
{
    // create single channel mask
    cv::Mat map_mask_8u;
    image_data->input_mask.convertTo( map_mask_8u, CV_8U );

    // create 3 channel contour
    cv::Mat contour_8u3;
    drawn_contour.convertTo( contour_8u3, CV_8UC3 );
    cv::cvtColor( contour_8u3, contour_8u3, cv::COLOR_GRAY2BGR );

    // paint region using porter duff
    cv::Mat painted_region;
    try {
        painted_region = bitwise_i1_atop_i2(
            image_data->input_image,
            contour_8u3,
            map_mask_8u,
            drawn_contour
        );
    } catch (std::string &str) {
        std::cerr << "ERROR : paint_map_atop_region" << std::endl;
        std::cerr << "Error: " << str << std::endl;
    } catch (cv::Exception &e) {
        std::cerr << "ERROR : paint_map_atop_region" << std::endl;
        std::cerr << "Error: " << e.msg << std::endl;
    } catch (std::runtime_error &re) {
        std::cerr << "ERROR : paint_map_atop_region" << std::endl;
        std::cerr << "Error: " << re.what() << std::endl;
    }

    if (painted_region.empty()) {
        image_data->input_image.copyTo( painted_region );
    }

    map_mask_8u.release();
    contour_8u3.release();
    return painted_region;
}

// draw original states back onto marked_up_image
void
draw_on_original(SLICData* image_data, int marker_value)
{
    // create single channel mask
    cv::Mat mask_8u;
    image_data->input_mask.convertTo( mask_8u, CV_8U );

    // fill in states
    for (int i = 0; i < image_data->markers.rows; i++)
    {
        for (int j = 0; j < image_data->markers.cols; j++)
        {
            // skip if not in mask (draw borders)
            if (mask_8u.at<uchar>( i, j ) != (uchar) 0) {
                continue;
            }
            int pixel = image_data->markers.at<int>( i, j );
            if (marker_value > -1 && pixel != marker_value) {
                continue;
            }
            if (pixel >= 0 && pixel <= static_cast<int>(image_data->num_superpixels)) {
                image_data->marked_up_image.at<cv::Vec3b>( i, j ) = image_data->input_image.at<cv::Vec3b>( i, j );
            }
        }
    }
    mask_8u.release();
}

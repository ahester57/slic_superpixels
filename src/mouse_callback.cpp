// mouse_callback.cpp : Mouse Callback Stuff
// Austin Hester CS642o april 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/mouse_callback.hpp"

#include "../include/dir_func.hpp"

#define DEBUG 1

#if DEBUG
    #include <iostream>
#endif


// draw zeros on image
void
mouse_callback_draw_zeros(int event, int x, int y, int d, void* userdata)
{
    SLICData* image_data = (SLICData*) userdata;

    switch (event) {

    // RIGHT MOUSE BUTTON
        case cv::EVENT_RBUTTONUP:
            // zero-out region of interest
            image_data->marked_up_image = cv::Mat::zeros( image_data->input_image.size(), image_data->input_image.type() );

            // draw original map back on
            draw_on_original( image_data );

            // show marked_up_image
            cv::imshow( image_data->window_name, image_data->marked_up_image );
            break;

    // LEFT MOUSE BUTTON
        case cv::EVENT_LBUTTONUP:
            // check bounds (needed if double ROI is larger than input image
            if (x > image_data->markers.size().width || y > image_data->markers.size().height) {
#if DEBUG
                std::cout << "OOB" << std::endl;
#endif
                break;
            }

            // find the marker at that point
            int marker_value = image_data->markers.at<int>( y, x );

#if DEBUG
            std::cout << "Marker Value:\t\t" << marker_value << std::endl;
#endif
            // check marker exists
            if (marker_value < 0 || marker_value > image_data->num_superpixels-1) {
#if DEBUG
                std::cout << "Marker Out of Range." << std::endl;
#endif
                break;
            }

            // extract region_of_interest
            select_region( image_data, marker_value );

            // show region_of_interest in new window
            // cv::imshow( "region_of_interest", image_data->region_of_interest );

            // show marked_up_image
            cv::imshow( image_data->window_name, image_data->marked_up_image );

            // save marked_up_image
            char metadata[50];
            std::sprintf( metadata, "regions/out_a_%d_s_%d_r_%f_c_%d_m_%d.png",
                image_data->algorithm,
                image_data->region_size,
                image_data->ruler,
                image_data->connectivity,
                marker_value
            );
            write_img_to_file(
                image_data->marked_up_image,
                "./out",
                metadata
            );
            break;

    }
}


// assign mouse callbacks
void
init_callback(SLICData* image_data)
{
    cv::setMouseCallback( image_data->window_name, mouse_callback_draw_zeros, image_data );
}

void
init_callback(SLICData* image_data, std::string window_name)
{
    cv::setMouseCallback( window_name, mouse_callback_draw_zeros, image_data );
}

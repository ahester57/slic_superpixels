// map_segment.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS642o apr 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>

#include "../include/affine.hpp"
#include "../include/canny.hpp"
#include "../include/cla_parse.hpp"
#include "../include/dir_func.hpp"
#include "../include/equalize.hpp"
#include "../include/mouse_callback.hpp"
#include "../include/rectangle.hpp"
#include "../include/segmentation.hpp"
#include "../include/slic_helper.hpp"

#define DEBUG 0


const std::string WINDOW_NAME = "SLIC Superpixels";


// event loop
// call in a while loop to only register q or <esc>
int
wait_key()
{
    char key_pressed = cv::waitKey(0) & 255;
    // 'q' or  <escape> quits out
    if (key_pressed == 27 || key_pressed == 'q') {
        return 0;
    }
    return 1;
}

// initialize input data
SLICData
initialize_slic_data(
    std::string input_image_filename,
    float scale_image_value,
    bool pad_input,
    std::string algorithm_string,
    int region_size,
    float ruler
) {
    cv::Mat input_image = open_image( input_image_filename );

    // crop if odd resolution
    input_image = input_image(
        cv::Rect( 0, 0, input_image.cols & -2, input_image.rows & -2 )
    );

    // scale the input size if given 's' flag
    if (scale_image_value != 1.f) {
        input_image = resize_affine( input_image, scale_image_value );
        std::cout << "Scaled Image size is:\t\t" << input_image.cols << "x" << input_image.rows << std::endl;
    }

    // pad the input image if given flag
    if (pad_input) {
        cv::copyMakeBorder( input_image, input_image, 50, 50, 50, 50, cv::BORDER_CONSTANT, cv::Scalar(0) );
        std::cout << "Padded Image size is:\t\t" << input_image.cols << "x" << input_image.rows << std::endl;
    }

#if DEBUG > 1
    cv::imshow( WINDOW_NAME, input_image );
    // 'event loop' for keypresses
    while (wait_key());
#endif

    std::string output_window_name = WINDOW_NAME + " Output Image";

    SLICData image_data;
    image_data.window_name = output_window_name;
    input_image.copyTo( image_data.input_image );

    // create mask, only distance filter on foreground
    //TODO make this better at background detection, not just black backgrounds
    image_data.input_mask = make_background_mask( image_data.input_image );

    // get the algorithm parameters
    image_data.algorithm = slic_string_to_int( algorithm_string );
    image_data.region_size = region_size;
    image_data.ruler = ruler;

    return image_data;
}

// apply segmentation
void
process_slic_data(SLICData* image_data)
{
    // segment the image by intensity
    superpixel( image_data );
}

// apply input filters, show, save, and initialize mouse callback
void
post_processing(
    SLICData* image_data,
    bool blur_output,
    bool equalize_output,
    std::string output_image_filename
) {
    // blur the output if given 'b' flag
    if (blur_output) {
        cv::medianBlur( image_data->marked_up_image, image_data->marked_up_image, 3 );
    }

    // equalize the output if given 'e' flag
    if (equalize_output) {
        equalize_image( &image_data->marked_up_image );
    }

    cv::imshow( image_data->window_name, image_data->marked_up_image );
    write_img_to_file( image_data->marked_up_image, "./out", output_image_filename );

    // initialize the mouse callback
    init_callback( image_data );

}


int
main(int argc, const char** argv)
{
    // CLA variables
    std::string input_image_filename;
    std::string output_image_filename;
    int region_size;
    float ruler;
    std::string algorithm_string;

    // CLA flags
    float scale_image_value;
    bool blur_output;
    bool equalize_output;
    bool pad_input = false;

    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &input_image_filename,
        &output_image_filename,
        &scale_image_value,
        &blur_output,
        &equalize_output,
        &region_size,
        &ruler,
        &algorithm_string
    );
    if (parse_result != 1) return parse_result;


    // open the image with given options
    SLICData image_data = initialize_slic_data(
        input_image_filename,
        scale_image_value,
        pad_input,
        algorithm_string,
        region_size,
        ruler
    );

    // apply segmentation
    process_slic_data( &image_data );

    // post-process slic data
    post_processing(
        &image_data,
        blur_output,
        equalize_output,
        output_image_filename
    );

    // 'event loop' for keypresses
    while (wait_key());

    cv::destroyAllWindows();

    image_data.input_image.release();
    image_data.markers.release();
    image_data.input_mask.release();
    image_data.region_of_interest.release();
    image_data.marked_up_image.release();

    return 0;
}

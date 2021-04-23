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
preprocess_slic(
    std::string input_image_filename,
    float scale_image_value,
    bool pad_input,
    std::string algorithm_string,
    int region_size,
    float ruler,
    int connectivity
) {
    cv::Mat input_image = open_image( input_image_filename );

    // scale the input size if given 's' flag
    if (scale_image_value != 1.f) {
        input_image = resize_affine( input_image, scale_image_value );
    }

    // crop if odd resolution
    input_image = input_image(
        cv::Rect( 0, 0, input_image.cols & -2, input_image.rows & -2 )
    );
    std::cout << "Scaled Image size is:\t\t" << input_image.cols << "x" << input_image.rows << std::endl;

    // pad the input image if given flag
    if (pad_input) {
        cv::copyMakeBorder( input_image, input_image, 50, 50, 50, 50, cv::BORDER_CONSTANT, cv::Scalar(0) );
        std::cout << "Padded Image size is:\t\t" << input_image.cols << "x" << input_image.rows << std::endl;
    }

    // blur
    cv::GaussianBlur( input_image, input_image, cv::Size( 3, 3 ), 0.5f );

    // convert to CieLAB
    cv::cvtColor( input_image, input_image, cv::COLOR_BGR2Lab );

#if DEBUG > 1
    cv::imshow( WINDOW_NAME, input_image );
    // 'event loop' for keypresses
    while (wait_key());
#endif

    std::string output_window_name = WINDOW_NAME + " Output Image";

    // initialize SLICData object
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
    image_data.connectivity = connectivity;
    image_data.num_superpixels = 0;

    return image_data;
}

// apply segmentation
void
process_slic(SLICData* image_data)
{
    // segment the image by intensity
    superpixel( image_data );
    // convert back to RGB
    cv::cvtColor( image_data->input_image, image_data->input_image, cv::COLOR_Lab2BGR );
    // zero-out region of interest
    image_data->marked_up_image = cv::Mat::zeros( image_data->input_image.size(), image_data->input_image.type() );
    // draw original map back on
    draw_on_original( image_data );
}

// apply input filters, show, save, and initialize mouse callback
void
postprocess_slic(
    SLICData* image_data,
    bool blur_output,
    bool equalize_output,
    bool sharpen_output
) {
    // blur the output if given 'b' flag
    if (blur_output) {
        cv::GaussianBlur( image_data->marked_up_image, image_data->marked_up_image, cv::Size( 3, 3 ), 3.5f );
    }

    if (sharpen_output) {
        cv::Mat tmp;
        cv::GaussianBlur( image_data->marked_up_image, tmp, cv::Size( 0, 0 ), 3 );
        cv::addWeighted( image_data->marked_up_image, 1.42, tmp, -0.42, 0, image_data->marked_up_image );
        tmp.release();
    }

    // equalize the output if given 'e' flag
    if (equalize_output) {
        equalize_image( &image_data->marked_up_image );
    }

    char metadata[50];
    std::sprintf( metadata, "a_%d_s_%d_r_%f_c_%d.png",
        image_data->algorithm,
        image_data->region_size,
        image_data->ruler,
        image_data->connectivity
    );
    std::printf( "%s\n", metadata );
    cv::imshow( image_data->window_name, image_data->marked_up_image );
    write_img_to_file( image_data->marked_up_image, "./out/slic_output", metadata );

    // initialize the mouse callback
    init_callback( image_data );
    init_callback( image_data, "SLIC Label Contours");
    init_callback( image_data, "SLIC Label Markers" );
}


int
main(int argc, const char** argv)
{
    // CLA variables
    std::string template_image_filename;
    std::string target_image_filename;
    int region_size = 10;
    float ruler = 10.f;
    std::string algorithm_string = "SLIC";
    int connectivity = 25;

    // CLA flags
    float scale_image_value = 1.f;
    bool blur_output = false;
    bool equalize_output = false;
    bool sharpen_output = false;
    bool pad_input = false;

    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &template_image_filename,
        &target_image_filename,
        &scale_image_value,
        &blur_output,
        &equalize_output,
        &sharpen_output,
        &region_size,
        &ruler,
        &algorithm_string,
        &connectivity
    );
    if (parse_result != 1) return parse_result;


    // open the image with given options
    SLICData source_data = preprocess_slic(
        template_image_filename,
        scale_image_value,
        pad_input,
        algorithm_string,
        region_size,
        ruler,
        connectivity
    );

    // apply segmentation
    process_slic( &source_data );

    // post-process slic data
    postprocess_slic(
        &source_data,
        blur_output,
        equalize_output,
        sharpen_output
    );

    // 'event loop' for keypresses
    while (wait_key());

    cv::destroyAllWindows();

    source_data.input_image.release();
    source_data.markers.release();
    source_data.input_mask.release();
    source_data.region_of_interest.release();
    source_data.marked_up_image.release();

    return 0;
}

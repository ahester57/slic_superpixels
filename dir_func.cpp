// dir_func.hpp : Directory functions
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utils/filesystem.hpp>

#include <fstream>
#include <iostream>

#include "./include/dir_func.hpp"

#include "./include/string_helper.hpp"


cv::Mat
open_image(std::string file_path, bool grayscale)
{
    cv::Mat dst;
    try {
        // attempt to read the image
        if (grayscale) {
            dst = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
        } else {
            dst = cv::imread(file_path);
        }

        assert(!dst.empty());

        std::cout << "Image type is:\t\t\t" << cv_type_to_str( dst ) << std::endl;
        std::cout << "Image size is:\t\t\t" << dst.cols << "x" << dst.rows << std::endl;
    } catch (std::string &str) {
        std::cerr << "Error: " << file_path << ": " << str << std::endl;
    } catch (cv::Exception &e) {
        std::cerr << "Error: " << file_path << ": " << e.msg << std::endl;
    }
    return dst;
}


void
open_image_from_text(std::string file_path, cv::Mat* dst)
{
    try {


        std::ifstream ifi;
        ifi.open(file_path);
        for (int i = 0; i < dst->size().height; i++) {
            for (int j = 0; j < dst->size().width; j++) {
                ifi >> dst->at<float>(i, j);
            }
        }
        ifi.close();

        cv::waitKey(100);

    } catch (std::string &str) {
        std::cerr << "Error: " << str << std::endl;
    } catch (cv::Exception &e) {
        std::cerr << "Error: " << e.msg << std::endl;
    } catch (std::runtime_error &re) {
        std::cerr << "Error: " << re.what() << std::endl;
    }
}


int
create_dir_recursive(std::string dst_file)
{
    std::vector<std::string> split_dst_file = split(dst_file, '/');
    std::string output_so_far = "";
    // for each string between '/'s
    for (std::string this_dir : split_dst_file) {
        if (output_so_far.length() > 0) {
            // if it's not the first one, append with preceding '/'
            output_so_far = output_so_far + '/' + this_dir;
        } else output_so_far = this_dir;
        // if this is the last one, don't create the dir bc this is the filename
        if (output_so_far == dst_file) return 1;
        assert(cv::utils::fs::createDirectory(output_so_far));
    }
    std::cerr << "this should never happen but compiler wants a return here.\n";
    return 1;
}

int
write_img_to_file(cv::Mat image, std::string output_dir, std::string file_name)
{
    try {

        std::string dst_file = output_dir + "/" + file_name;
        assert(create_dir_recursive(dst_file));

        assert(cv::imwrite(dst_file, image));

        cv::waitKey(100);
        std::cout << "Wrote " << dst_file << std::endl;

    } catch (std::string &str) {
        std::cerr << "Error: " << str << std::endl;
        return -1;
    } catch (cv::Exception &e) {
        std::cerr << "Error: " << e.msg << std::endl;
        return -1;
    } catch (std::runtime_error &re) {
        std::cerr << "Error: " << re.what() << std::endl;
    }
    return 1;
}

template <typename T>
int
write_img_to_file_as_text(cv::Mat image, std::string output_dir, std::string file_name)
{
    try {

        std::string dst_file = output_dir + "/" + file_name;
        assert(create_dir_recursive(dst_file));

        std::ofstream of;
        of.open(dst_file);
        for (int i = 0; i < image.size().height; i++) {
            for (int j = 0; j < image.size().width; j++) {
                of << image.at<T>(i, j) << " ";
            }
            if (i < image.size().height - 1) of << std::endl;
        }
        of.close();

        cv::waitKey(100);
        std::cout << "Wrote " << dst_file << std::endl;

    } catch (std::string &str) {
        std::cerr << "Error: " << str << std::endl;
        return -1;
    } catch (cv::Exception &e) {
        std::cerr << "Error: " << e.msg << std::endl;
        return -1;
    } catch (std::runtime_error &re) {
        std::cerr << "Error: " << re.what() << std::endl;
    }
    return 1;
}

template int write_img_to_file_as_text<uint>(cv::Mat image, std::string output_dir, std::string file_name);
template int write_img_to_file_as_text<float>(cv::Mat image, std::string output_dir, std::string file_name);

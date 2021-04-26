# Image Segmentation with SLIC Superpixels
### Austin Hester
### CS 6420 - Computer Vision
### UMSL SP2021, Prof. Sanjiv Bhatia

----
## Purpose

The purpose of this assignment is to segment a given image using the SLIC pixels algorithm.  
You are given a color image and you will apply the OpenCV function createSuperpixelSLIC() to show the picture using superpixels.

----

## Task

SLIC, Simple Linear Iterative Clustering, is a modification of the k-means algorithm. It helps with generating superpixels that
are approximately equal in size.  

You are given a color picture. Process it using the SLIC pixel algorithm to create superpixels. Experiment with different
parameters of the createSuperpixelSLIC function to compute the superpixels.

----

## Example

Algorithm: `MSLIC`  
Region Size: `4`  
Ruler: `40`  
Connectivity: `4`  

Input Image:
![Input Image](images/tiger.jpg)

![Contours Image](out_example/slic_contours/a_102_s_4_r_40.000000_c_4.png)

![Output Image](out_example/slic_output/a_102_s_4_r_40.000000_c_4.png)

----

### Usage

```
Usage: slic.exe [params] template_image target_image

        -a, --algorithm (value:MSLIC)
                Name of SLIC algorithm variant
                         - SLIC segments image using a desired region size
                         - SLICO optimizes using an adaptive compactness factor
                         - MSLIC optimizes using manifold methods giving more context-sensitive superpixels
        -b, --blur (value:true)
                Output Image - Blur
        -c, --connectivity (value:99)
                The minimum element size in percents that should be absorbed into a bigger superpixel
        -e, --equalize (value:true)
                Output Image - Equalize
        -h, --help (value:true)
                Show Help Message
        -r, --ruler (value:10)
                Chooses the enforcement of superpixel smoothness
        --region_size, -s (value:8)
                Chooses an average superpixel size measured in pixels
        --sc, --scale (value:1.6)
                Scale input image size using Affine Transform
        --sh, --sharpen (value:true)
                Output Image - Sharpen

        target_image
                Target image. Provides structure. Defaults to template image.

```
----

https://github.com/ahester57/slic_superpixels

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

#### Usage

```
Usage: slic.exe [params] input_image output_image

        -a, --algorithm (value:SLIC)
                Name of SLIC algorithm variant
                        SLIC segments image using a desired region size
                        SLICO optimizes using an adaptive compactness factor
                        MSLIC optimizes using manifold methods giving more context-sensitive superpixels
        -b, --blur
                Blur Output Image
        -e, --equalize
                Equalize Output Image
        -h, --help (value:true)
                Show Help Message
        -r, --ruler (value:10.f)
                Chooses the enforcement of superpixel smoothness
        -s, --size (value:10)
                Chooses an average superpixel size measured in pixels     
        --sc, --scale (value:1.f)
                Scale Input Image Size using Affine Transform

        input_image (value:<none>)
                Input Image
        output_image (value:<none>)
                Output Image

```
----

https://github.com/ahester57/slic_superpixels

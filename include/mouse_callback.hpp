
// mouse_callback.hpp : Mouse Callback Stuff
// Austin Hester CS642o april 2021
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef MOUSE_CALLBACK_H
#define MOUSE_CALLBACK_H

#include "./slic_helper.hpp"


void mouse_callback_draw_zeros(int event, int x, int y, int d, void* userdata);

void init_callback(SLICData* frequency_mask);

void init_callback(SLICData* image_data, std::string window_name);

#endif

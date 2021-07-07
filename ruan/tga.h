//
// Created by dust on 2021/6/28.
//

#ifndef RUAN_TGA_H
#define RUAN_TGA_H
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "types.h"
#include "platform.h"

typedef struct {
    short width;
    short height;
    byte* data;
} tga_image;

tga_image* tga_new(short width, short height);
void tga_free(tga_image* image);
color32 tga_get_pixel(tga_image* img, vector2i pos);
color32 tga_tex2d(tga_image* img, vector2f pos);
void tga_set_pixel(tga_image *img, vector2i pos, color32 color);
void tga_write(tga_image *img, const char* file_name);
tga_image* tga_load(const char* file_name);

#endif //RUAN_TGA_H

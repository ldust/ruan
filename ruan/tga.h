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

#pragma pack(push, 1)
typedef struct {
    char  id_length;
    char  color_map_type;
    char  data_type_code;
    short int color_map_origin;
    short int color_map_length;
    char  color_map_depth;
    short int x_origin;
    short int y_origin;
    short width;
    short height;
    char  bits_per_pixel;
    char  image_descriptor;
} tga_header;

#pragma pack(pop)

typedef struct {
    short width;
    short height;
    byte* data;
} tga_image;

#define BYTES_PER_PIXEL 4

tga_image* tga_new(short width, short height) {
    tga_image* img = malloc(sizeof(tga_image));
    img->width = width;
    img->height = height;
    size_t sz = width * height * BYTES_PER_PIXEL;
    img->data = malloc(sz);
    memset(img->data, 0, sz);
    return img;
}

void tga_free(tga_image* image) {
    free(image->data);
    free(image);
}

color tga_get_pixel(tga_image* img, vector2i pos) {
    short x = (short)pos.x;
    short y = (short)pos.y;
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        byte* ptr = img->data + (img->width * y + x) * BYTES_PER_PIXEL;
        return (color){*(ptr + 2), *(ptr + 1), *(ptr + 0), *(ptr + 3) };
    } else {
        fprintf (stderr, "error: invalid position (%d,%d).\n", x, y);
        return (color) { 0 };
    }
}

void tga_set_pixel(tga_image *img, vector2i pos, color color) {
    short x = (short)pos.x;
    short y = (short)pos.y;
    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
        byte c[4];
        c[0] = color.b;
        c[1] = color.g;
        c[2] = color.r;
        c[3] = color.a;
        memcpy(img->data + (img->width * y + x) * BYTES_PER_PIXEL, &c, BYTES_PER_PIXEL);
    } else {
        fprintf (stderr, "error: invalid position (%d,%d).\n", x, y);
    }
}

void tga_write(tga_image *img, const char* file_name) {
    FILE* file = app_open_file(file_name, "wb");
    tga_header header;
    memset((void *)&header, 0, sizeof(header));
    header.data_type_code = 2; // Uncompressed, RGB images.
    header.width = img->width;
    header.height = img->height;
    header.bits_per_pixel = BYTES_PER_PIXEL * 8;
    fwrite(&header, sizeof(header), 1, file);
    size_t sz = img->width * img->height * BYTES_PER_PIXEL;
    fwrite(img->data, sz, 1, file);
    fclose(file);
}

tga_image* tga_load(const char* file_name) {
    FILE* file = app_open_file(file_name, "rb");
    if (!file) {
        fprintf (stderr, "error: file open failed '%s'.\n", file_name);
        return 0;
    }
    tga_header header;
    size_t read_sz = fread(&header, sizeof(header), 1, file);
    if (read_sz != 1) {
        fprintf (stderr, "error: file header wrong '%s'.\n", file_name);
        return 0;
    }
    if (header.bits_per_pixel != BYTES_PER_PIXEL * 8 || header.data_type_code != 2) {
        fprintf (stderr, "error: unsupported tga format '%s'.\n", file_name);
        return 0;
    }
    tga_image *img = tga_new(header.width, header.height);
    size_t sz = img->width * img->height * BYTES_PER_PIXEL;
    read_sz = fread(img->data, sz, 1, file);
    fclose(file);
    if (read_sz != 1) {
        fprintf (stderr, "error: file data wrong '%s'.\n", file_name);
        tga_free(img);
        return 0;
    }

    return img;
}

#endif //RUAN_TGA_H

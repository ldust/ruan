//
// Created by dust on 2021/6/29.
//

#ifndef RUAN_PLATFORM_H
#define RUAN_PLATFORM_H
#include "geometry.h"
#include <stdio.h>

typedef struct {
    vector2i win_size;
    void* handle;
    void (*set_pixel) (void*, vector2i, color);
    void (*flush)(void*);
    void (*clear)(void*);
} device;

void app_launch_finished(void);

void app_create_win(vector2i size, device* d);

void app_update(void);

FILE* app_open_file(const char* file_name, const char* mode);

#endif //RUAN_PLATFORM_H

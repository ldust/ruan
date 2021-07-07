//
// Created by dust on 2021/6/28.
//

#ifndef RUAN_RUAN_H
#define RUAN_RUAN_H
#include "types.h"
#include "mesh.h"
#include "platform.h"
#include <math.h>
#include <stdbool.h>
#include "tga.h"

void ruan_clear(device* d);
void ruan_flush(device* d);
void ruan_pixel(device* d, vector2i pos, color32 color);
void ruan_line(device *d, vector2i from, vector2i to, color32 color);
void ruan_triangle(device *d, vector3f* positions, vector2f* uv, vector3f* normals, vector3f light_dir, tga_image* tex);
#endif //RUAN_RUAN_H

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

void ruan_clear(device* d);
void ruan_flush(device* d);
void ruan_pixel(device* d, vector2i pos, color color);
void ruan_line(device *d, vector2i from, vector2i to, color color);
void ruan_triangle(device *d, vector2i* vs, color color);
#endif //RUAN_RUAN_H

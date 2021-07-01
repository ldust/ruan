//
// Created by dust on 2021/6/28.
//

#ifndef RUAN_RUAN_H
#define RUAN_RUAN_H
#include "types.h"
#include <math.h>
#include <stdbool.h>

void ruan_clear(device* d) {
    d->clear(d->handle);
}

void ruan_flush(device* d) {
    d->flush(d->handle);
}

void ruan_pixel(device* d, vector2i pos, color color) {
    d->set_pixel(d->handle, pos, color);
}

void ruan_line(device *d, vector2i from, vector2i to, color color) {
    bool steep = false;
    if (abs(to.x - from.x) < abs((to.y - from.y))) {
        swap(from.x, from.y);
        swap(to.x, to.y);
        steep = true;
    }
    if (from.x > to.x) {
        swap(from, to);
    }
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    float derror = fabsf((float)dy / (float)dx);
    float error = 0;
    int y = from.y;
    int dir = from.y > to.y ? -1 : 1;
    for (int x = from.x; x <= to.x; x++) {
        if (steep) {
            ruan_pixel(d, v2i(y, x), color);
        } else {
            ruan_pixel(d, v2i(x, y), color);
        }
        error += derror;
        if (error > 0.5f) {
            y += dir;
            error -= 1.0f;
        }
    }
}

#endif //RUAN_RUAN_H

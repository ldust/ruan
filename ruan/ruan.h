//
// Created by dust on 2021/6/28.
//

#ifndef RUAN_RUAN_H
#define RUAN_RUAN_H
#include "types.h"
#include <math.h>
#include <stdbool.h>

typedef struct {
    void* device;
    void (*set) (void*, vector2i, color);
} frame_buffer;

void ruan_draw(frame_buffer* fb, vector2i pos, color color) {
    fb->set(fb->device, pos, color);
}

void ruan_line(frame_buffer *fb, vector2i from, vector2i to, color color) {
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
            ruan_draw(fb, v2i(y, x), color);
        } else {
            ruan_draw(fb, v2i(x, y), color);
        }
        error += derror;
        if (error > 0.5f) {
            y += dir;
            error -= 1.0f;
        }
    }
}

#endif //RUAN_RUAN_H

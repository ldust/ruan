//
// Created by dust on 2021/7/2.
//

#include "ruan.h"
#include <stdlib.h>
#include <float.h>

void ruan_clear(device* d) {
    d->clear(d);
}

void ruan_flush(device* d) {
    d->flush(d);
}

void ruan_pixel(device* d, vector2i pos, color32 color) {
    d->set_pixel(d, pos, color);
}

void ruan_line(device *d, vector2i from, vector2i to, color32 color) {
    bool steep = false;
    if (abs(to.x - from.x) < abs(to.y - from.y)) {
        swap(from.x, from.y);
        swap(to.x, to.y);
        steep = true;
    }
    if (from.x > to.x) {
        swap(from, to);
    }
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    int derror = abs(dy) * 2;
    int error = 0;
    int y = from.y;
    int dir = from.y > to.y ? -1 : 1;
    for (int x = from.x; x <= to.x; x++) {
        if (steep) {
            ruan_pixel(d, v2i(y, x), color);
        } else {
            ruan_pixel(d, v2i(x, y), color);
        }
        error += derror;
        if (error > dx) {
            y += dir;
            error -= dx * 2;
        }
    }
}

void ruan_triangle(device *d, vector3f* positions, vector2f* uvs, tga_image* tex, color32 c) {
    int max_x = d->win_size.x - 1;
    int max_y = d->win_size.y - 1;
    vector2i bbox_min = v2i(max_x, max_y);
    vector2i bbox_max = v2i(0, 0);
    for (int i = 0; i < 3; ++i) {
        bbox_min.x = max(0, min(bbox_min.x, positions[i].x));
        bbox_min.y = max(0, min(bbox_min.y, positions[i].y));
        bbox_max.x = min(max_x, max(bbox_max.x, positions[i].x));
        bbox_max.y = min(max_y, max(bbox_max.y, positions[i].y));
    }

    for (int x = bbox_min.x; x <= bbox_max.x; ++x) {
        for (int y = bbox_min.y; y <= bbox_max.y; ++y) {
            vector3f p = v3f(x, y, 0);
            vector3f bc = barycentric(positions, p);
            if (bc.x >= 0 && bc.y >= 0 && bc.z >= 0) {
                int depth_idx = y * d->win_size.x + x;
                float old = d->depth_buffer[depth_idx];
                float now = positions[0].z * bc.x;
                now += positions[1].z * bc.y;
                now += positions[2].z * bc.z;
                if (now >= old) {
                    d->depth_buffer[depth_idx] = now;

                    vector2f uv;
                    uv.x = uvs[0].x * bc.x;
                    uv.x += uvs[1].x * bc.y;
                    uv.x += uvs[2].x * bc.z;

                    uv.y = uvs[0].y * bc.x;
                    uv.y += uvs[1].y * bc.y;
                    uv.y += uvs[2].y * bc.z;

                    color32 tex_c = tga_tex2d(tex, uv);
                    color32 mix = clr32(c.r * tex_c.r / 255, c.g * tex_c.g / 255, c.b * tex_c.b / 255, c.a);
                    ruan_pixel(d, v2i(x, y), mix);
                }
            }
        }
    }
//    ruan_line(d, positions[0], positions[1], c);
//    ruan_line(d, positions[1], positions[2], c);
//    ruan_line(d, positions[2], positions[0], c);
//    ruan_line(d, v2i(bbox_min.x, bbox_min.y), v2i(bbox_min.x, bbox_max.y), clr_blue);
//    ruan_line(d, v2i(bbox_min.x, bbox_min.y), v2i(bbox_max.x, bbox_min.y), clr_blue);
//    ruan_line(d, v2i(bbox_max.x, bbox_min.y), v2i(bbox_max.x, bbox_max.y), clr_blue);
//    ruan_line(d, v2i(bbox_min.x, bbox_max.y), v2i(bbox_max.x, bbox_max.y), clr_blue);
}

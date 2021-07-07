//
// Created by dust on 2021/7/6.
//

#include "geometry.h"
#include <math.h>
#include <float.h>

float v3f_field(vector3f v, int idx) {
    return idx == 0 ? v.x : (idx == 1 ? v.y : v.z);
}

float v2f_field(vector2f v, int idx) {
    return idx == 0 ? v.x : v.y;
}

vector3f v3f_add(vector3f a, vector3f b) {
    return v3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

vector3f v3f_sub(vector3f a, vector3f b) {
    return v3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

vector3f v3f_scale(vector3f v, float scale) {
    return v3f(v.x * scale, v.y * scale, v.z * scale);
}

float v3f_length_sq(vector3f v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

float v3f_length(vector3f v) {
    return sqrtf(v3f_length_sq(v));
}

vector3f v3f_normalize(vector3f v) {
    return v3f_scale(v, 1 / v3f_length(v));
}

float v3f_dot(vector3f a, vector3f b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vector3f v3f_cross(vector3f a, vector3f b) {
    return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

vector3f barycentric(vector3f* vs, vector3f p) {
    vector3f a = vs[0];
    vector3f b = vs[1];
    vector3f c = vs[2];
    vector3f st = v3f_cross(v3f(b.x - a.x, c.x - a.x, a.x - p.x), v3f(b.y - a.y, c.y - a.y, a.y - p.y));
    if (fabsf(st.z) < FLT_EPSILON) {
        return v3f(-1, 1, 1);
    }
    return v3f(1.0 - (st.x + st.y) / st.z, st.x / st.z, st.y / st.z);
}
//
// Created by dust on 2021/7/6.
//

#include "geometry.h"
#include <math.h>
#include <float.h>

float v3f_dot(vector3f a, vector3f b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vector3f v3f_cross(vector3f a, vector3f b) {
    return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

vector3f barycentric(vector2i* vs, vector2i p) {
    vector2i a = vs[0];
    vector2i b = vs[1];
    vector2i c = vs[2];
    vector3f st = v3f_cross(v3f(b.x - a.x, c.x - a.x, a.x - p.x), v3f(b.y - a.y, c.y - a.y, a.y - p.y));
    if (fabsf(st.z) < FLT_EPSILON) {
        return v3f(-1, 1, 1);
    }
    return v3f(1.0 - (st.x + st.y) / st.z, st.y / st.z, st.x / st.z);
}
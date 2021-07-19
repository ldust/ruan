//
// Created by dust on 2021/7/6.
//

#include "geometry.h"
#include <math.h>
#include <float.h>
#include <string.h>

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

vector3f v3f_mul_mat33(vector3f v, matrix33 mat) {
    float x = mat.data[0] * v.x + mat.data[1] * v.y + mat.data[2] * v.z;
    float y = mat.data[3] * v.x + mat.data[4] * v.y + mat.data[5] * v.z;
    float z = mat.data[6] * v.x + mat.data[7] * v.y + mat.data[8] * v.z;
    return v3f(x / z, y / z, z);
}

vector3f v3f_mul_mat44(vector3f v, matrix44 mat) {
    float x = mat.data[ 0] * v.x + mat.data[ 1] * v.y + mat.data[ 2] * v.z + mat.data[ 3];
    float y = mat.data[ 4] * v.x + mat.data[ 5] * v.y + mat.data[ 6] * v.z + mat.data[ 7];
    float z = mat.data[ 8] * v.x + mat.data[ 9] * v.y + mat.data[10] * v.z + mat.data[11];
    float w = mat.data[12] * v.x + mat.data[13] * v.y + mat.data[14] * v.z + mat.data[15];
    return v3f(x / w, y / w, z / w);
}

matrix44 mat44_identity() {
    matrix44 m;
    memset(&m, 0, sizeof(m.data));
    m.data[0] = m.data[5] = m.data[10] = m.data[15] = 1;
    return m;
}

matrix44 mat44_mul_mat44(matrix44 a, matrix44 b) {
    matrix44 r;
    r.data[ 0] = a.data[ 0] * b.data[ 0] + a.data[ 1] * b.data[ 4] + a.data[ 2] * b.data[ 8] + a.data[ 3] * b.data[12];
    r.data[ 1] = a.data[ 0] * b.data[ 1] + a.data[ 1] * b.data[ 5] + a.data[ 2] * b.data[ 9] + a.data[ 3] * b.data[13];
    r.data[ 2] = a.data[ 0] * b.data[ 2] + a.data[ 1] * b.data[ 6] + a.data[ 2] * b.data[10] + a.data[ 3] * b.data[14];
    r.data[ 3] = a.data[ 0] * b.data[ 3] + a.data[ 1] * b.data[ 7] + a.data[ 2] * b.data[11] + a.data[ 3] * b.data[15];

    r.data[ 4] = a.data[ 4] * b.data[ 0] + a.data[ 5] * b.data[ 4] + a.data[ 6] * b.data[ 8] + a.data[ 7] * b.data[12];
    r.data[ 5] = a.data[ 4] * b.data[ 1] + a.data[ 5] * b.data[ 5] + a.data[ 6] * b.data[ 9] + a.data[ 7] * b.data[13];
    r.data[ 6] = a.data[ 4] * b.data[ 2] + a.data[ 5] * b.data[ 6] + a.data[ 6] * b.data[10] + a.data[ 7] * b.data[14];
    r.data[ 7] = a.data[ 4] * b.data[ 3] + a.data[ 5] * b.data[ 7] + a.data[ 6] * b.data[11] + a.data[ 7] * b.data[15];

    r.data[ 8] = a.data[ 8] * b.data[ 0] + a.data[ 9] * b.data[ 4] + a.data[10] * b.data[ 8] + a.data[11] * b.data[12];
    r.data[ 9] = a.data[ 8] * b.data[ 1] + a.data[ 9] * b.data[ 5] + a.data[10] * b.data[ 9] + a.data[11] * b.data[13];
    r.data[10] = a.data[ 8] * b.data[ 2] + a.data[ 9] * b.data[ 6] + a.data[10] * b.data[10] + a.data[11] * b.data[14];
    r.data[11] = a.data[ 8] * b.data[ 3] + a.data[ 9] * b.data[ 7] + a.data[10] * b.data[11] + a.data[11] * b.data[15];

    r.data[12] = a.data[12] * b.data[ 0] + a.data[13] * b.data[ 4] + a.data[14] * b.data[ 8] + a.data[15] * b.data[12];
    r.data[13] = a.data[12] * b.data[ 1] + a.data[13] * b.data[ 5] + a.data[14] * b.data[ 9] + a.data[15] * b.data[13];
    r.data[14] = a.data[12] * b.data[ 2] + a.data[13] * b.data[ 6] + a.data[14] * b.data[10] + a.data[15] * b.data[14];
    r.data[15] = a.data[12] * b.data[ 3] + a.data[13] * b.data[ 7] + a.data[14] * b.data[11] + a.data[15] * b.data[15];
    return r;
}
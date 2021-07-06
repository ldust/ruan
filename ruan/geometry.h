//
// Created by dust on 2021/7/6.
//

#ifndef RUAN_GEOMETRY_H
#define RUAN_GEOMETRY_H

typedef struct {
    int x;
    int y;
} vector2i;

#define v2i(x, y) ((vector2i) { x, y })

typedef struct {
    float x;
    float y;
    float z;
} vector3f;

#define v3f(x, y, z) ((vector3f) { x, y, z })

float v3f_dot(vector3f a, vector3f b);
vector3f v3f_cross(vector3f a, vector3f b);
vector3f barycentric(vector2i* vs, vector2i p);

#endif //RUAN_GEOMETRY_H

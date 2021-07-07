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
float v3f_field(vector3f v, int idx);
vector3f v3f_add(vector3f a, vector3f b);
vector3f v3f_sub(vector3f a, vector3f b);
vector3f v3f_scale(vector3f v, float scale);
vector3f v3f_normalize(vector3f v);
float v3f_length(vector3f v);
float v3f_length_sq(vector3f v);
float v3f_dot(vector3f a, vector3f b);
vector3f v3f_cross(vector3f a, vector3f b);

typedef struct {
    float x;
    float y;
} vector2f;

#define v2f(x, y) ((vector2f) { x, y })
float v2f_field(vector2f v, int idx);

vector3f barycentric(vector3f* vs, vector3f p);



#endif //RUAN_GEOMETRY_H

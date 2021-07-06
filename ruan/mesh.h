//
// Created by dust on 2021/7/2.
//

#ifndef RUAN_MESH_H
#define RUAN_MESH_H

#include "geometry.h"

typedef struct {
    vector3f *vertices;
    int *triangles;
} mesh;

mesh* mesh_new();

void mesh_free(mesh* mesh) ;

#endif //RUAN_MESH_H

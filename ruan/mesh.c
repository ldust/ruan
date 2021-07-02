//
// Created by dust on 2021/7/2.
//

#include "mesh.h"
#include <stdlib.h>
#include "darray.h"

mesh* mesh_new() {
    mesh* m = malloc(sizeof(mesh));
    m->triangles = NULL;
    m->vertices = NULL;
    return m;
}

void mesh_free(mesh* mesh) {
    free(mesh->vertices);
    free(mesh->triangles);
    free(mesh);
}
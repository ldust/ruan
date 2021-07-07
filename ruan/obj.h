//
// Created by dust on 2021/7/1.
//

#ifndef RUAN_OBJ_H
#define RUAN_OBJ_H
#include "types.h"
#include "darray.h"
#include <stdio.h>

#define LINE_SIZE 256

mesh* obj_read(const char* file_name) {
    FILE* file = app_open_file(file_name, "r");
    if (!file) {
        fprintf (stderr, "error: file open failed '%s'.\n", file_name);
        return NULL;
    }
    mesh* m = mesh_new();
    char line[LINE_SIZE];
    vector3f* normals = NULL;
    vector2f* uvs = NULL;
    int* indices = NULL;
    while (1) {
        if (fgets(line, LINE_SIZE, file) == NULL) {
            break;
        } else if (strncmp(line, "v ", 2) == 0) {               /* position */
            vector3f position;
            char* end = line + 2;
            position.x = strtof(end, &end);
            position.y = strtof(end, &end);
            position.z = strtof(end, NULL);
            darray_push(m->vertices, position);
        } else if (strncmp(line, "vn ", 3) == 0) {
            char* end = line + 3;
            vector3f normal;
            normal.x = strtof(end, &end);
            normal.y = strtof(end, &end);
            normal.z = strtof(end, NULL);
            darray_push(normals, normal);
        } else if (strncmp(line, "vt ", 3) == 0) {
            char* end = line + 3;
            vector2f uv;
            uv.x = strtof(end, &end);
            uv.y = strtof(end, NULL);
            darray_push(uvs, uv);
        } else if (strncmp(line, "f ", 2) == 0) {               /* face */
            char* end = line + 1;
            for (int i = 0; i < 9; ++i) {
                darray_push(indices, (int)strtol(end + 1, &end, 10));
            }
        }
    }

    m->uv = darray_hold(m->uv, darray_size(m->vertices), sizeof(vector2f));
    m->normals = darray_hold(m->normals, darray_size(m->vertices), sizeof(vector3f));

    for (int i = 0; i < darray_size(indices); i += 3) {
        int v_idx = indices[i + 0] - 1;
        darray_push(m->triangles, v_idx);
        m->uv[v_idx] = uvs[indices[i + 1] - 1];
        m->normals[v_idx] = normals[indices[i + 2] - 1];
    }
    darray_free(uvs);
    darray_free(normals);
    darray_free(indices);

    fclose(file);
    return m;
}

#endif //RUAN_OBJ_H

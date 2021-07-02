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
    FILE* file = fopen(file_name, "r");
    if (!file) {
        fprintf (stderr, "error: file open failed '%s'.\n", file_name);
        return NULL;
    }
    mesh* m = mesh_new();
    char line[LINE_SIZE];
    while (1) {
        if (fgets(line, LINE_SIZE, file) == NULL) {
            break;
        } else if (strncmp(line, "v ", 2) == 0) {               /* position */
            vector3f position;
            char* end;
            position.x = strtof(line + 2, &end);
            position.y = strtof(end, &end);
            position.z = strtof(end, NULL);
            darray_push(m->vertices, position);
        } else if (strncmp(line, "f ", 2) == 0) {               /* face */
            int indices_buf[9];
            char* end = line + 1;
            for (int i = 0; i < 9; ++i) {
                indices_buf[i] = (int)strtol(end + 1, &end, 10);
            }
            darray_push(m->triangles, indices_buf[0]);
            darray_push(m->triangles, indices_buf[3]);
            darray_push(m->triangles, indices_buf[6]);
        }
    }

    for (int i = 0; i < darray_size(m->triangles); ++i) {
        m->triangles[i]--;
    }

    fclose(file);
    return m;
}

#endif //RUAN_OBJ_H

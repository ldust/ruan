#include <stdio.h>
#include <time.h>
#include "../ruan/tga.h"
#include "../ruan/ruan.h"
#include "../ruan/platform.h"
#include "../ruan/obj.h"
#include "../ruan/darray.h"

device *d = NULL;
mesh *m = NULL;
tga_image* tex = NULL;
vector2i win_size;

matrix44 mat;

void app_launch_finished() {
    srand(time(0));
    d = malloc(sizeof(device));
    app_create_win(v2i(800, 800), d);

    vector2i win_size = d->win_size;

    matrix44 mat_proj = mat44_identity();
    const float cam_z = 5;
    mat_proj.data[14] = 1.0f / -cam_z;

    vector2i origin = v2i(win_size.x / 8, win_size.y / 8);
    vector2i ws = v2i(win_size.x * 3 / 4, win_size.y * 3 / 4);

    matrix44 mat_viewport = mat44_identity();
    float w = (float)ws.x / 2.0f;
    float h = (float)ws.y / 2.0f;
    float scale = w < h ? w : h;
    mat_viewport.data[0] = mat_viewport.data[5] = scale;
    mat_viewport.data[3] = (float)origin.x + w;
    mat_viewport.data[7] = (float)origin.y + h;

    mat = mat44_mul_mat44(mat_viewport, mat_proj);
}

double get_unix_time(void) {
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
    return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}

void draw_wireframe(void);
void mat_test(void);

void app_update(void) {
    ruan_clear(d);
//    mat_test();
    draw_wireframe();

//    vector2i t0[3] = {v2i(10, 70),   v2i(50, 70),  v2i(70, 70)};
//    vector2i t1[3] = {v2i(180, 50),  v2i(150, 1),   v2i(70, 180)};
//    vector2i t2[3] = {v2i(180, 150), v2i(120, 160), v2i(130, 180)};
//
//    ruan_triangle(d,t0, clr_red);
//    ruan_triangle(d,t1, clr_white);
//    ruan_triangle(d,t2, clr_green);
    ruan_flush(d);
}

vector3f light_dir = v3f(-1, -1, -1);
vector3f world_to_screen(vector3f v) {
    int w = win_size.x / 2;
    int h = win_size.y / 2;
    int scale = w < h ? w : h;
    return v3f(v.x * scale + w, v.y * scale + h, v.z);
}

void draw_quad(vector3f v1, vector3f v2, vector3f v3, vector3f v4, color32 color) {
    v1 = world_to_screen(v1);
    v2 = world_to_screen(v2);
    v3 = world_to_screen(v3);
    v4 = world_to_screen(v4);
    ruan_line(d, v2i(v1.x, v1.y), v2i(v2.x, v2.y), color);
    ruan_line(d, v2i(v2.x, v2.y), v2i(v3.x, v3.y), color);
    ruan_line(d, v2i(v3.x, v3.y), v2i(v4.x, v4.y), color);
    ruan_line(d, v2i(v4.x, v4.y), v2i(v1.x, v1.y), color);
}

void mat_test(void) {
    float r = 0.5f;

    matrix33 mat = {{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }};

    vector3f v1 = v3f(-r, -r, 1);
    vector3f v2 = v3f(-r, r, 1);
    vector3f v3 = v3f(r, r, 1);
    vector3f v4 = v3f(r, -r, 1);

    draw_quad(v1, v2, v3, v4, clr32_white);

    v1 = v3f_mul_mat33(v1, mat);
    v2 = v3f_mul_mat33(v2, mat);
    v3 = v3f_mul_mat33(v3, mat);
    v4 = v3f_mul_mat33(v4, mat);

    draw_quad(v1, v2, v3, v4, clr32_red);
}



void draw_wireframe() {
    if (m == NULL) {
        m = obj_read("res/african_head.obj");
    }
    if (tex == NULL) {
        tex = tga_load("res/african_head_diffuse.tga");
    }

    win_size = d->win_size;

    vector3f l_dir = v3f_normalize(light_dir);
    l_dir = v3f_scale(l_dir, -1);

    for (int i = 0; i < darray_size(m->triangles); i += 3) {
        vector3f pos[3];
        vector2f uv[3];
        vector3f normals[3];

        for (int j = 0; j < 3; ++j) {
            int v_idx = m->triangles[i + j];
            pos[j] = m->vertices[v_idx];
            uv[j] = m->uv[v_idx];
            normals[j] = m->normals[v_idx];
        }

        for (int j = 0; j < 3; ++j) {
            pos[j] = v3f_mul_mat44(pos[j], mat);
        }
        ruan_triangle(d, pos, uv, normals, l_dir, tex);
        //ruan_line(d, v2i(pos1.x * scale + w, pos1.y * scale + h), v2i(pos2.x * scale + w, pos2.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos2.x * scale + w, pos2.y * scale + h), v2i(pos3.x * scale + w, pos3.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos3.x * scale + w, pos3.y * scale + h), v2i(pos1.x * scale + w, pos1.y * scale + h), clr_white);
    }
}
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

void app_launch_finished() {
    srand(time(0));
    d = malloc(sizeof(device));
    app_create_win(v2i(800, 800), d);
}

double get_unix_time(void) {
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
    return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}

void draw_wireframe(void);

void app_update(void) {
    ruan_clear(d);
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

vector3f light_dir = v3f(0, 0, -1);
vector2i win_size;
vector3f world_to_screen(vector3f v) {
    int w = win_size.x / 2;
    int h = win_size.y / 2;
    int scale = w < h ? w : h;
    return v3f(v.x * scale + w, v.y * scale + h, v.z);
}

void draw_wireframe() {
    if (m == NULL) {
        m = obj_read("res/african_head.obj");
    }
    if (tex == NULL) {
        tex = tga_load("res/african_head_diffuse.tga");
    }

    win_size = d->win_size;

    for (int i = 0; i < darray_size(m->triangles); i += 3) {
        vector3f pos[3];
        vector2f uv[3];

        for (int j = 0; j < 3; ++j) {
            int v_idx = m->triangles[i + j];
            pos[j] = m->vertices[v_idx];
            uv[j] = m->uv[v_idx];
        }

        vector3f normal = v3f_normalize(v3f_cross(v3f_sub(pos[2], pos[0]), v3f_sub(pos[1], pos[0])));
        float intensity = v3f_dot(normal, v3f_normalize(light_dir));
        if (intensity > 0) {
            for (int j = 0; j < 3; ++j) {
                pos[j] = world_to_screen(pos[j]);
            }
            ruan_triangle(d, pos, uv, tex, clr32(intensity * 255, intensity * 255, intensity * 255, 255));
        }
        //ruan_line(d, v2i(pos1.x * scale + w, pos1.y * scale + h), v2i(pos2.x * scale + w, pos2.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos2.x * scale + w, pos2.y * scale + h), v2i(pos3.x * scale + w, pos3.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos3.x * scale + w, pos3.y * scale + h), v2i(pos1.x * scale + w, pos1.y * scale + h), clr_white);
    }
}
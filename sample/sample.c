#include <stdio.h>
#include <time.h>
#include "../ruan/tga.h"
#include "../ruan/ruan.h"
#include "../ruan/platform.h"
#include "../ruan/obj.h"
#include "../ruan/darray.h"

device *d = NULL;
mesh *m = NULL;

void app_launch_finished() {
    srand(time(0));
    d = malloc(sizeof(device));
    app_create_win(v2i(400, 400), d);
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

void draw_wireframe() {
    if (m == NULL) {
        m = obj_read("res/african_head.obj");
    }
    int w = d->win_size.x / 2;
    int h = d->win_size.y / 2;

    int scale = w < h ? w : h;

    for (int i = 0; i < darray_size(m->triangles); i += 3) {
        vector3f pos1 = m->vertices[m->triangles[i]];
        vector3f pos2 = m->vertices[m->triangles[i + 1]];
        vector3f pos3 = m->vertices[m->triangles[i + 2]];
        vector2i vs[3];
        vs[0] = v2i(pos1.x * scale + w, pos1.y * scale + h);
        vs[1] = v2i(pos2.x * scale + w, pos2.y * scale + h);
        vs[2] = v2i(pos3.x * scale + w, pos3.y * scale + h);

        ruan_triangle(d, vs,clr(rand() % 255, rand() % 255, rand() % 255, 255));
        //ruan_line(d, v2i(pos1.x * scale + w, pos1.y * scale + h), v2i(pos2.x * scale + w, pos2.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos2.x * scale + w, pos2.y * scale + h), v2i(pos3.x * scale + w, pos3.y * scale + h), clr_white);
        //ruan_line(d, v2i(pos3.x * scale + w, pos3.y * scale + h), v2i(pos1.x * scale + w, pos1.y * scale + h), clr_white);
    }
}
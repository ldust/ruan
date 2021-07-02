#include <stdio.h>
#include <time.h>
#include "tga.h"
#include "ruan.h"
#include "platform.h"
#include "obj.h"
#include "darray.h"

device *d;
mesh *m;
void app_launch_finished() {
    srand(time(0));
    d = malloc(sizeof(device));
    app_create_win(v2i(400, 600), d);
    m = obj_read("/Users/dust/Downloads/african_head.obj");
}

double get_unix_time(void) {
    struct timespec tv;
    if (clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;
    return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}

void app_update(void) {
    ruan_clear(d);
    int w = d->win_size.x / 2;
    int h = d->win_size.y / 2;

    int scale = w < h ? w : h;

    for (int i = 0; i < darray_size(m->triangles); i += 3) {
        vector3f pos1 = m->vertices[m->triangles[i]];
        vector3f pos2 = m->vertices[m->triangles[i + 1]];
        vector3f pos3 = m->vertices[m->triangles[i + 2]];
        ruan_line(d, v2i(pos1.x * scale + w, pos1.y * scale + h), v2i(pos2.x * scale + w, pos2.y * scale + h), clr_white);
        ruan_line(d, v2i(pos2.x * scale + w, pos2.y * scale + h), v2i(pos3.x * scale + w, pos3.y * scale + h), clr_white);
        ruan_line(d, v2i(pos3.x * scale + w, pos3.y * scale + h), v2i(pos1.x * scale + w, pos1.y * scale + h), clr_white);
    }
    ruan_flush(d);
}
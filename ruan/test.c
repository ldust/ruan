#include <stdio.h>
#include <time.h>
#include "tga.h"
#include "ruan.h"
#include "platform.h"

device *d;
void app_launch_finished() {
    srand(time(0));
    d = malloc(sizeof(device));
    app_create_win(v2i(1000, 1000), d);
}

void app_update(void) {
    ruan_clear(d);

    ruan_line(d, v2i(0, 0), v2i(1000, 1000), clr_red);

    ruan_flush(d);
}
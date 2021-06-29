#include <stdio.h>
#include "tga.h"
#include "ruan.h"

void set_pixel(void *img, vector2i pos, color c) {
    tga_set_pixel(img, pos, c);
}

int main() {
    tga_image *image = tga_new(100, 100);

    frame_buffer fb;
    fb.device = image;
    fb.set = set_pixel;

    ruan_line(&fb, v2i(0, 0), v2i(99, 10), clr_red);
    tga_write(image, "/Users/dust/Code/ruan/to.tga");
    tga_free(image);

    return 0;
}

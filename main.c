#include <stdio.h>
#include "tga.h"


int main() {
    tga_image *image = tga_read("/Users/dust/Code/ruan/from.tga");
    if (image) {
        for (short i = 0; i < image->width; ++i) {
            for (short j = 0; j < image->height; ++j) {
                color now = tga_get_pixel(image, i, j);
                if (now.r == now.g) {
                    now = clr(255, 0, 0, 255);
                }
                tga_set_pixel(image, i, j, now);
            }
        }
        tga_write(image, "/Users/dust/Code/ruan/to.tga");
        tga_free(image);
    }
    return 0;
}

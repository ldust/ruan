//
// Created by dust on 2021/6/28.
//

#ifndef RUAN_TYPES_H
#define RUAN_TYPES_H

typedef unsigned char byte;

typedef struct {
    byte r;
    byte g;
    byte b;
    byte a;
} color;

typedef struct {
    int x;
    int y;
} vector2i;

#define clr_red ((color){ 255, 0, 0, 255 })
#define clr_green ((color){ 0, 255, 0, 255 })
#define clr_blue ((color){ 0, 0, 255, 255 })
#define clr_white ((color){ 255, 255, 255, 255 })
#define clr_black ((color){ 0, 0, 0, 255 })

#define clr(r, g, b, a) ((color){ r, g, b, a })
#define v2i(x, y) ((vector2i) { x, y })

typedef struct {
    void* handle;
    void (*set_pixel) (void*, vector2i, color);
    void (*flush)(void*);
    void (*clear)(void*);
} device;

#define swap(x,y) do {   \
   typeof(x) _x = x;     \
   typeof(y) _y = y;     \
   (x) = _y;             \
   (y) = _x;             \
 } while(0)

#endif //RUAN_TYPES_H

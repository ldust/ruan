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

#define clr_red ((color){ 255, 0, 0, 255 })
#define clr_green ((color){ 0, 255, 0, 255 })
#define clr_blue ((color){ 0, 0, 255, 255 })
#define clr_white ((color){ 255, 255, 255, 255 })
#define clr_black ((color){ 0, 0, 0, 255 })
#define clr(r, g, b, a) ((color){ r, g, b, a })

#define swap(x,y) do {   \
   typeof(x) _x = x;     \
   typeof(y) _y = y;     \
   (x) = _y;             \
   (y) = _x;             \
 } while(0)

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#endif //RUAN_TYPES_H

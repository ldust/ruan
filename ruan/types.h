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
} color32;

#define clr32_red ((color32){ 255, 0, 0, 255 })
#define clr32_green ((color32){ 0, 255, 0, 255 })
#define clr32_blue ((color32){ 0, 0, 255, 255 })
#define clr32_white ((color32){ 255, 255, 255, 255 })
#define clr32_black ((color32){ 0, 0, 0, 255 })
#define clr32(r, g, b, a) ((color32){ r, g, b, a })

#define swap(x,y) do {   \
   typeof(x) _x = x;     \
   typeof(y) _y = y;     \
   (x) = _y;             \
   (y) = _x;             \
 } while(0)

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#endif //RUAN_TYPES_H

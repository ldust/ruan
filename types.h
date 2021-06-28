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

#define clr(r, g, b, a) ((color){ r, g, b, a })

#endif //RUAN_TYPES_H

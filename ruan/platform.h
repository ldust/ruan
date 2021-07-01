//
// Created by dust on 2021/6/29.
//

#ifndef RUAN_PLATFORM_H
#define RUAN_PLATFORM_H
#include "types.h"

void app_launch_finished(void);

void app_create_win(vector2i size, device* d);

void app_update(void);
#endif //RUAN_PLATFORM_H

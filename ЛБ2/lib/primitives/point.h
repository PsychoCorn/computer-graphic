#ifndef POINT_H
#define POINT_H

#include "../includes.h"

struct Point
{
    int32_t x;
    int32_t y;
};

typedef struct Point point_t;

void point_init(point_t *const self, int32_t x, int32_t y)
{
    self->x = x;
    self->y = y;
}

point_t point_new(int32_t x, int32_t y)
{
    point_t new_point;
    point_init(&new_point, x, y);
    return new_point;
}

#endif
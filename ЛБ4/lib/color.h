#ifndef COLOR_H
#define COLOR_H

#include "includes.h"

struct Color
{
    GLdouble red;
    GLdouble green;
    GLdouble blue;
    GLdouble alpha;
};

typedef struct Color color_t;

void color_init1d(color_t *const self, GLdouble c)
{
    self->red = c;
    self->green = c;
    self->blue = c;
    self->alpha = 1.f;
}

void color_init2d(color_t *const self, GLdouble c, GLdouble a)
{
    self->red = c;
    self->green = c;
    self->blue = c;
    self->alpha = a;
}

void color_init3d(color_t *const self, GLdouble r, GLdouble g, GLdouble b)
{
    self->red = r;
    self->green = g;
    self->blue = b;
    self->alpha = 1.f;
}

void color_init4d(color_t *const self, GLdouble r, GLdouble g, GLdouble b, GLdouble a)
{
    self->red = r;
    self->green = g;
    self->blue = b;
    self->alpha = a;
}

color_t color_new1d(GLdouble c)
{
    color_t new_color;
    color_init1d(&new_color, c);
    return new_color;
}

color_t color_new2d(GLdouble c, GLdouble a)
{
    color_t new_color;
    color_init2d(&new_color, c, a);
    return new_color;
}

color_t color_new3d(GLdouble r, GLdouble g, GLdouble b)
{
    color_t new_color;
    color_init3d(&new_color, r, g, b);
    return new_color;
}

color_t color_new4d(GLdouble r, GLdouble g, GLdouble b, GLdouble a)
{
    color_t new_color;
    color_init4d(&new_color, r, g, b, a);
    return new_color;
}

#endif
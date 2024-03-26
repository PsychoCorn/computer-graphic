#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../color.h"
#include "point.h"

enum RectBasePoint
    {
        CENTER,
        TOP_CENTER,
        BOTTOM_CENTER,
        LEFT_CENTER,
        RIGHT_CENTER,
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT, // default
        BOTTOM_RIGHT,
    };

struct Rectangle
{
    point_t _base; // protected
    point_t _offset; // protected
    color_t color;
    point_t _vertices[4]; // protected
};

typedef struct Rectangle rectangle_t;

static void rectangle_calculate_vertices(rectangle_t *const self, point_t bottom_left)
{
    point_init(self->_vertices, bottom_left.x, bottom_left.y); // bottom left
    point_init(self->_vertices + 1, bottom_left.x + self->_offset.x, bottom_left.y); // bottom right
    point_init(self->_vertices + 2, bottom_left.x + self->_offset.x, bottom_left.y + self->_offset.y); // top right
    point_init(self->_vertices + 3, bottom_left.x, bottom_left.y + self->_offset.y); // top left
}

void rectangle_base_to(rectangle_t *const self, int32_t x, int32_t y, enum RectBasePoint bp)
{
    self->_base.x = x;
    self->_base.y = y;
    switch (bp)
    {
    case CENTER:
        x -= self->_offset.x >> 1;
        y -= self->_offset.y >> 1;
        break;

    case TOP_CENTER:
        x -= self->_offset.x >> 1;
        y -= self->_offset.y;
        break;

    case BOTTOM_CENTER:
        x -= self->_offset.x >> 1;
        break;

    case LEFT_CENTER:
        y -= self->_offset.y >> 1;
        break;

    case RIGHT_CENTER:
        x -= self->_offset.x;
        y -= self->_offset.y >> 1;
        break;

    case TOP_LEFT:
        y -= self->_offset.y;
        break;

    case TOP_RIGHT:
        x -= self->_offset.x;
        y -= self->_offset.y;
        break;

    case BOTTOM_LEFT:
        break;

    case BOTTOM_RIGHT:
        x -= self->_offset.x;
        break;
    }

    rectangle_calculate_vertices(self, point_new(x, y)); // update vertices
}

void rectangle_init(rectangle_t *const self, int32_t x, int32_t y, int32_t w, int32_t h, enum RectBasePoint bp, color_t c)
{
    point_init(&self->_offset, w, h);
    rectangle_base_to(self, x, y, bp);
    self->color = c;
}

rectangle_t rectangle_new(int32_t x, int32_t y, int32_t w, int32_t h, enum RectBasePoint bp, color_t c)
{
    rectangle_t new_rectangle;
    rectangle_init(&new_rectangle, x, y, w, h, bp, c);
    return new_rectangle;
}

void rectangle_draw(const rectangle_t *const self)
{
    glColor4d(self->color.red, self->color.green, self->color.blue, self->color.alpha);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; ++i)
    {
        glVertex2i(self->_vertices[i].x, self->_vertices[i].y);
    }
    glEnd();
}

#endif
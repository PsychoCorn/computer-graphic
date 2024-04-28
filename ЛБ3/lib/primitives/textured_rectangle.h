#ifndef TEXTURED_RECTANGLE_H
#define TEXTURED_RECTANGLE_H

#include "rectangle.h"
#include "texture.h"

struct TexturedRectangle
{
    rectangle_t rect;
    texture_t tex;
};

typedef struct TexturedRectangle textured_rectangle_t;

void textured_rectangle_init(textured_rectangle_t *const self, rectangle_t r, texture_t t)
{
    self->rect = r;
    self->tex = t;
}

textured_rectangle_t textured_rectangle_new(rectangle_t r, texture_t t)
{
    textured_rectangle_t new_textured_rectangle;
    textured_rectangle_init(&new_textured_rectangle, r, t);
    return new_textured_rectangle;
}

void textured_rectangle_draw(const textured_rectangle_t *const self)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, self->tex.texture_id);
    glColor4d(self->rect.color.red, self->rect.color.green, self->rect.color.blue, self->rect.color.alpha);
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f);
    glVertex2i(self->rect._vertices[0].x, self->rect._vertices[0].y);
    glTexCoord2f(1.f, 1.f);
    glVertex2i(self->rect._vertices[1].x, self->rect._vertices[1].y);
    glTexCoord2f(1.f, 0.f);
    glVertex2i(self->rect._vertices[2].x, self->rect._vertices[2].y);
    glTexCoord2f(0.f, 0.f);
    glVertex2i(self->rect._vertices[3].x, self->rect._vertices[3].y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

#endif
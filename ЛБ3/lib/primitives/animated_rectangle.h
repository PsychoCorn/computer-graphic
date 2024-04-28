#ifndef ANIMATED_RECTANGLE_H
#define ANIMATED_RECTANGLE_H

#include "textured_rectangle.h"

struct AnimatedRectangle
{
    textured_rectangle_t sprite_sheet;
    uint8_t frame_number;
    uint8_t frame_counter;
    GLfloat *frame_coords;

};

typedef struct AnimatedRectangle animated_rectangle_t;

void animated_rectangle_init(animated_rectangle_t *const self, textured_rectangle_t sh)
{
    self->sprite_sheet = sh;
    self->frame_counter = 0u;
    self->frame_number = self->sprite_sheet.tex.size.x / self->sprite_sheet.rect._offset.x;
    self->frame_coords = (GLfloat *)malloc((self->frame_number + 1) * sizeof(GLfloat));
    float frame_shift = 1.f / (float)self->frame_number;
    GLfloat frame_coord = 0.f;
    for (int8_t i = 0; i <= self->frame_number; ++i)
    {
        self->frame_coords[i] = frame_coord;
        frame_coord += frame_shift;
    }
}

animated_rectangle_t animated_rectangle_new(textured_rectangle_t sh)
{
    animated_rectangle_t new_animated_rectangle;
    animated_rectangle_init(&new_animated_rectangle, sh);
    return new_animated_rectangle;
}

void animated_rectangle_draw(animated_rectangle_t *const self)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, self->sprite_sheet.tex.texture_id);
    glColor4d(self->sprite_sheet.rect.color.red, self->sprite_sheet.rect.color.green, 
              self->sprite_sheet.rect.color.blue, self->sprite_sheet.rect.color.alpha);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2f(self->frame_coords[self->frame_counter], 1.f);
    glVertex2i(self->sprite_sheet.rect._vertices[0].x, self->sprite_sheet.rect._vertices[0].y);
    glTexCoord2f(self->frame_coords[self->frame_counter + 1], 1.f);
    glVertex2i(self->sprite_sheet.rect._vertices[1].x, self->sprite_sheet.rect._vertices[1].y);
    glTexCoord2f(self->frame_coords[self->frame_counter + 1], 0.f);
    glVertex2i(self->sprite_sheet.rect._vertices[2].x, self->sprite_sheet.rect._vertices[2].y);
    glTexCoord2f(self->frame_coords[self->frame_counter], 0.f);
    glVertex2i(self->sprite_sheet.rect._vertices[3].x, self->sprite_sheet.rect._vertices[3].y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    self->frame_counter = self->frame_counter >= self->frame_number - 1 ? 0u : self->frame_counter + 1;
}

#endif
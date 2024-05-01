#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"

typedef enum
{
    LEFT,
    RIGHT
} Side;

typedef struct
{
    Side side;
    texture_t sprite_sheet;
    uint8_t frame_number;
    uint8_t frame_counter;
    GLfloat *frame_coords;
    float frame_shift;
} animation_t;

void animation_turn_right(animation_t *const self)
{
    if (self->side == RIGHT)
    {
        return;
    }
    GLfloat frame_coord = 0.f;
    for (int8_t i = 0; i <= self->frame_number; ++i)
    {
        self->frame_coords[i] = frame_coord;
        frame_coord += self->frame_shift;
    }
    self->side = RIGHT;
}

void animation_turn_left(animation_t *const self)
{
    if (self->side == LEFT)
    {
        return;
    }
    GLfloat frame_coord = self->frame_shift;
    for (int8_t i = 0; i <= self->frame_number; ++i)
    {
        self->frame_coords[i] = frame_coord;
        frame_coord -= self->frame_shift;
    }
    self->side = LEFT;
}

void animation_init(animation_t *const self, texture_t sprite_sheet, int32_t size_of_frame)
{
    self->sprite_sheet = sprite_sheet;
    self->frame_counter = 0u;
    self->frame_number = self->sprite_sheet.size.x / size_of_frame;
    self->frame_coords = (GLfloat *)malloc((self->frame_number + 1) * sizeof(GLfloat));
    self->frame_shift = 1.f / (float)self->frame_number;
    animation_turn_right(self);
}

animation_t animation_new(texture_t sprite_sheet, int32_t size_of_frame)
{
    animation_t new_animation;
    animation_init(&new_animation, sprite_sheet, size_of_frame);
    return new_animation;
}

#endif
#ifndef CHARACTER_H
#define CHARACTER_H

#include "../primitives/animation.h"
#include "../global_settings.h"
#include "../primitives/rectangle.h"

typedef enum
{
    IDLE,
    WALKING,
    DEATH,
} CharacterState;

typedef struct
{
    bool on_floor;
    animation_t animations[3];
    rectangle_t rect;
    point_t speed;
    CharacterState state;
    Side side;
} character_t;

void character_init(character_t *const self, rectangle_t r, texture_t *sprite_sheets)
{
    self->rect = r;
    self->speed.x = 0;
    // self->speed.y = -gravity;
    self->speed.y = 0;
    self->state = IDLE;
    self->side = RIGHT;
    for (int i = 0; i < 3; ++i)
    {
        animation_init(self->animations + i, sprite_sheets[i], self->rect._offset.x);
    }
    self->on_floor = 0;
}

character_t character_new(rectangle_t r, texture_t *sprite_sheets)
{
    character_t new_character;
    character_init(&new_character, r, sprite_sheets);
    return new_character;
}

void character_walk_right(character_t *const self)
{
    if (self->side != RIGHT)
    {
        self->animations[self->state].frame_counter = 0;
        self->side = RIGHT;
    }
    self->state = WALKING;
    self->speed.x = CHARACTER_SPEED;
}

void character_walk_left(character_t *const self)
{
    if (self->side != LEFT)
    {
        self->animations[self->state].frame_counter = 0;
        self->side = LEFT;
    }
    self->state = WALKING;
    self->speed.x = -CHARACTER_SPEED;
}

void character_jump(character_t *const self)
{
    if (self->on_floor)
    {
        self->speed.y = 70;
    }

}

void character_stop(character_t *const self)
{
    self->animations[self->state].frame_counter = 0;
    self->state = IDLE;
    self->speed.x = 0;
}

void character_move(character_t *const self)
{
    for (int i = 0; i < 4; ++i)
    {
        self->rect._vertices[i].x += self->speed.x;
        self->rect._vertices[i].y += self->speed.y /* - GRAVITY */;
    }
}

void character_draw(character_t *const self)
{
    switch (self->side)
    {
    case LEFT:
        animation_turn_left(self->animations + self->state);
        break;

    case RIGHT:
        animation_turn_right(self->animations + self->state);
        break;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, self->animations[self->state].sprite_sheet.texture_id);
    glColor4d(self->rect.color.red, self->rect.color.green,
              self->rect.color.blue, self->rect.color.alpha);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2f(self->animations[self->state].frame_coords[self->animations[self->state].frame_counter], 1.f);
    glVertex2i(self->rect._vertices[0].x, self->rect._vertices[0].y);
    glTexCoord2f(self->animations[self->state].frame_coords[self->animations[self->state].frame_counter + 1], 1.f);
    glVertex2i(self->rect._vertices[1].x, self->rect._vertices[1].y);
    glTexCoord2f(self->animations[self->state].frame_coords[self->animations[self->state].frame_counter + 1], 0.f);
    glVertex2i(self->rect._vertices[2].x, self->rect._vertices[2].y);
    glTexCoord2f(self->animations[self->state].frame_coords[self->animations[self->state].frame_counter], 0.f);
    glVertex2i(self->rect._vertices[3].x, self->rect._vertices[3].y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    if (self->on_floor)
    {
        self->animations[self->state].frame_counter =
            self->animations[self->state].frame_counter >= self->animations[self->state].frame_number - 1 ?
            0u : self->animations[self->state].frame_counter + 1;
    }
    else
    {
        self->animations[self->state].frame_counter =
            self->animations[self->state].frame_counter >= self->animations[self->state].frame_number - 1 ?
            0u : self->animations[self->state].frame_counter;
        if (self->speed.y > 0)
        {
            self->speed.y -= 20;
        }
    }
}

#endif

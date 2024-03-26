#ifndef CHARACTER_H
#define CHARACTER_H

#include "../primitives/textured_rectangle.h"

struct Character
{
    textured_rectangle_t rect;
    // TODO: make struct animated_rect, change field rect to animated_rect
};

typedef struct Character character_t;

void character_init(character_t *self, textured_rectangle_t r)
{
    self->rect = r;
}

character_t character_new(textured_rectangle_t r)
{
    character_t new_character;
    character_init(&new_character, r);
    return new_character;
}

void character_draw(character_t *self)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, self->rect.tex.texture_id);
    glColor4d(self->rect.rect.color.red, self->rect.rect.color.green, 
              self->rect.rect.color.blue, self->rect.rect.color.alpha);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f);
    glVertex2i(self->rect.rect._vertices[0].x, self->rect.rect._vertices[0].y);
    glTexCoord2f(1.f, 1.f);
    glVertex2i(self->rect.rect._vertices[1].x, self->rect.rect._vertices[1].y);
    glTexCoord2f(1.f, 0.f);
    glVertex2i(self->rect.rect._vertices[2].x, self->rect.rect._vertices[2].y);
    glTexCoord2f(0.f, 0.f);
    glVertex2i(self->rect.rect._vertices[3].x, self->rect.rect._vertices[3].y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

#endif
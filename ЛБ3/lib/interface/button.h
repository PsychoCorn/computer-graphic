#ifndef BUTTON_H
#define BUTTON_H

#include "../primitives/textured_rectangle.h"
#include <string.h>

struct Interface;
typedef struct Interface interface_t;

struct Button
{
    textured_rectangle_t _rect; // private
    void (*on_click)(interface_t *const );
};

typedef struct Button button_t;

void button_init(button_t *const self, textured_rectangle_t r, void (*on_click)(interface_t *const))
{
    self->_rect = r;
    self->on_click = on_click;
}

button_t button_new(textured_rectangle_t r, void (*on_click)(interface_t *const))
{
    button_t new_button;
    button_init(&new_button, r, on_click);
    return new_button;
}

void button_on_click(const button_t *const self, interface_t *const interf)
{
    self->on_click(interf);
}

bool button_is_mouse_over(const button_t *const self, int32_t mouse_x, int32_t mouse_y)
{
    return mouse_x >= self->_rect.rect._vertices[0].x && mouse_x <= self->_rect.rect._vertices[2].x && 
           mouse_y >= self->_rect.rect._vertices[0].y && mouse_y <= self->_rect.rect._vertices[2].y;
}

void button_baseTo(button_t *const self, int32_t x, int32_t y, enum RectBasePoint bp)
{
    rectangle_base_to(&self->_rect.rect, x, y, bp);
}

void button_draw(const button_t *const self)
{
    textured_rectangle_draw(&self->_rect);
}

#endif
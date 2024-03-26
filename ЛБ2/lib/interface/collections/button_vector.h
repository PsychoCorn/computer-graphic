#ifndef BUTTON_VECTOR_H
#define BUTTON_VECTOR_H

#include "../button.h"

#define MAX_NUMBER_OF_BUTTONS 2

struct ButtonVector
{
    button_t arr[MAX_NUMBER_OF_BUTTONS];
    size_t size;
};

typedef struct ButtonVector button_vector_t;

void button_vector_init(button_vector_t *const self)
{
    self->size = 0;
}

button_vector_t button_vector_new()
{
    button_vector_t new_button_vector;
    button_vector_init(&new_button_vector);
    return new_button_vector;
}

void button_vector_push(button_vector_t *const self, button_t new_btn)
{
    if (self->size >= MAX_NUMBER_OF_BUTTONS)
    {
        fprintf(stderr, "Error! The limit has been exceeded");
        exit(1);
    }
    self->arr[self->size++] = new_btn;
}

void button_vector_clear(button_vector_t *const self)
{
    self->size = 0;
}

void button_vector_check_click(const button_vector_t *const self, interface_t *const interf, int32_t mouse_x, 
                               int32_t mouse_y)
{
    for (int32_t i = 0; i < self->size; ++i)
    {
        if (button_is_mouse_over(self->arr + i, mouse_x, mouse_y))
        {
            self->arr[i].on_click(interf);
            return;
        }
    }
}

void button_vector_draw(const button_vector_t *const self)
{
    for (int32_t i = 0; i < self->size; ++i)
    {
        button_draw(self->arr + i);
    }
}

#endif
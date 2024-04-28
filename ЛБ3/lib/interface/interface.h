#ifndef INTERFACE_H
#define INTERFACE_H

#include "collections/button_vector.h"
#include "../winsettings.h"

enum GameState
{
    GAMEPLAY,
    PAUSE,
};

struct Interface
{
    enum GameState _state; // private
    button_vector_t _buttons; // private
    // TODO: аdd other fields when they are thought up :)
};

void interface_add_pause_button(interface_t *);
void interface_add_pause_menu(interface_t *);

void interface_change_state(interface_t *const self, enum GameState new_state)
{
    self->_state = new_state;
    button_vector_clear(&self->_buttons);
    switch (new_state)
    {
    case GAMEPLAY:
        interface_add_pause_button(self);
        break;
    
    case PAUSE:
        interface_add_pause_menu(self);
        break;
    }
}

void interface_init(interface_t *const self)
{
    button_vector_init(&self->_buttons);
    interface_change_state(self, GAMEPLAY);
}

interface_t interface_new()
{
    interface_t new_interface;
    interface_init(&new_interface);
    return new_interface;
}

void pause_btn_on_click(interface_t *const self)
{
    interface_change_state(self, PAUSE);
}

void continue_btn_on_click(interface_t *const self)
{
    interface_change_state(self, GAMEPLAY);
}

void close();

void exit_btn_on_click(interface_t *const self)
{
    close();
}

void interface_add_pause_button(interface_t *const self)
{
    button_t pause_btn = button_new(textured_rectangle_new(rectangle_new(0, WIN_HEIGHT, 50, 50, TOP_LEFT, 
                                    color_new1d(0.5f)), 
                                    texture_new("sprites/interface/pause_button.png")), 
                                    pause_btn_on_click);
    button_vector_push(&self->_buttons, pause_btn);
}

void interface_add_pause_menu(interface_t *const self)
{
    int32_t btn_width = 250, btn_height = 75;
    color_t btn_color = color_new1d(0.5f);
    button_t continue_btn = button_new(textured_rectangle_new(rectangle_new(WIN_WIDTH >> 1, (WIN_HEIGHT >> 1) + 20, 
                                       btn_width, btn_height, BOTTOM_CENTER, btn_color), 
                                       texture_new("sprites/interface/continue_button.png")), 
                                       continue_btn_on_click);
    button_vector_push(&self->_buttons, continue_btn);
    button_t exit_btn = button_new(textured_rectangle_new(rectangle_new(WIN_WIDTH >> 1, (WIN_HEIGHT >> 1) - 20, 
                                   btn_width, btn_height, TOP_CENTER, btn_color), 
                                   texture_new("sprites/interface/exit_button.png")), 
                                   exit_btn_on_click);
    button_vector_push(&self->_buttons, exit_btn);
}

void interface_draw(const interface_t *const self)
{
    button_vector_draw(&self->_buttons);
}

void interface_check_buttons(interface_t *const self, int32_t mouse_x, int32_t mouse_y)
{
    button_vector_check_click(&self->_buttons, self, mouse_x, mouse_y);
}

#endif
#ifndef GAME_H
#define GAME_H

#include "interface/interface.h"
#include "characters/character.h"

struct Game
{
    interface_t interf;
    character_t charac;
};

typedef struct Game game_t;

void game_init(game_t *const self)
{
    interface_init(&self->interf);
    texture_t sprite_sheets[] = {texture_new("sprites/characters/main frog/idle.png"),
                            texture_new("sprites/characters/main frog/walk.png"),
                            texture_new("sprites/characters/main frog/dead.png")};
    character_init(&self->charac,
                   rectangle_new(WIN_WIDTH >> 1, WIN_HEIGHT >> 2, 100, 100, CENTER, color_new2d(1.f, 1.0f)),
                   sprite_sheets);
}

game_t game_new()
{
    game_t new_game;
    game_init(&new_game);
    return new_game;
}

void game_draw(game_t *const self)
{
    if (self->interf._state == GAMEPLAY)
        character_draw(&self->charac);
    interface_draw(&self->interf);
}

#endif
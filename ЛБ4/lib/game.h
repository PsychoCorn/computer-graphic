#ifndef GAME_H
#define GAME_H

#include "interface/interface.h"
#include "characters/character.h"
#include "map/map.h"

struct Game
{
    interface_t interf;
    map_t map;
};

typedef struct Game game_t;

void game_init(game_t *const self)
{
    interface_init(&self->interf);
    map_init(&self->map);
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
    {
        map_draw(&self->map);
        character_draw(&self->map.charac);
    }
    interface_draw(&self->interf);
}

#endif
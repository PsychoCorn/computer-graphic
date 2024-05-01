#ifndef MAP_H
#define MAP_H

#include "../characters/character.h"
#include "../winsettings.h"
#include "../global_settings.h"

typedef struct
{
    const char *map_plan[18];
    textured_rectangle_t *blocks;
    size_t size_of_blocks;
    character_t charac;
} map_t;

void map_init(map_t *const self)
{
    texture_t sprite_sheets[] = {texture_new("sprites/characters/main frog/idle.png"),
                            texture_new("sprites/characters/main frog/walk.png"),
                            texture_new("sprites/characters/main frog/dead.png")};
    character_init(&self->charac,
                   rectangle_new(80, WIN_HEIGHT >> 2, 40, 40, CENTER, color_new2d(1.f, 1.0f)),
                   sprite_sheets);
    for (int i = 0; i < 18; ++i)
    {
        self->map_plan[i] = map[i];
    }
    size_t start = 0, end = 17;
    const char *temp;
    while (start < end)
    {
        temp = self->map_plan[start];
        self->map_plan[start] = self->map_plan[end];
        self->map_plan[end] = temp;
        ++start;
        -- end;
    }

    self->size_of_blocks = 0;
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 33; ++j)
        {
            if (self->map_plan[i][j] == '#')
            {
                ++self->size_of_blocks;
            }
        }
    }
    self->blocks = (textured_rectangle_t *)malloc((self->size_of_blocks) * sizeof(textured_rectangle_t));
    size_t current_index = 0;
    for (int i = 0; i < 18; ++i)
    {
        for (int j = 0; j < 33; ++j)
        {
            if (self->map_plan[i][j] == '#')
            {
                self->blocks[current_index++] = textured_rectangle_new(rectangle_new(
                    j * 40, i * 40, 40, 40, BOTTOM_LEFT, color_new2d(1.f, 1.f)
                ), texture_new("sprites/map/groung.png"));
            }
        }
    }
}

map_t map_new()
{
    map_t new_map;
    map_init(&new_map);
    return new_map;
}

uint8_t border_collision_check(RECT char_pos)
{
    uint8_t collision = 0; // bits: 000000vh; v - vertical; h - horizontal;
    if (char_pos.left >= 0 && char_pos.right <= WIN_WIDTH)
        collision |= 1;
    if (char_pos.bottom >= 0)
        collision |= 2;
    return collision;
}

RECT get_corners(RECT char_pos)
{
    RECT corners;
    int32_t x_on_map_plan = char_pos.left / 40;
    int32_t y_on_map_plan = char_pos.bottom / 40;

    corners.left = (x_on_map_plan - 1 < 0) ? 0 : x_on_map_plan - 1;
    corners.bottom = (y_on_map_plan - 1 < 0) ? 0 : y_on_map_plan - 1;

    corners.right = (x_on_map_plan + 1 >= 33) ? 32 : x_on_map_plan + 1;
    corners.top = (y_on_map_plan + 1 >= 33) ? 32 : y_on_map_plan + 1;

    return corners;
}

uint8_t check_intersection(character_t *const self, RECT new_char_pos, int32_t block_x, int32_t block_y)
{
    RECT block;
    block.left = block_x;
    block.right = block_x + 40;
    block.bottom = block_y;
    block.top = block_y + 40;

    RECT char_pos;
    char_pos.left = self->rect._vertices[0].x;
    char_pos.right = self->rect._vertices[2].x;
    char_pos.bottom = self->rect._vertices[0].y;
    char_pos.top = self->rect._vertices[2].y;

    uint8_t collision = 0;

    bool h_col = (new_char_pos.right <= block.left || new_char_pos.left >= block.right) ||
                 (char_pos.top <= block.bottom || char_pos.bottom >= block.top);
    bool v_col = new_char_pos.top <= block.bottom || new_char_pos.bottom >= block.top ||
                 (char_pos.right <= block.left || char_pos.left >= block.right);

    if (h_col)
        collision |= 1;
    if (v_col)
        collision |= 2;

    return collision;
}

uint8_t collision_check(map_t *const self, RECT char_pos)
{
    RECT corners = get_corners(char_pos);
    uint8_t collision = border_collision_check(char_pos);
    for (int i = corners.bottom; i <= corners.top; ++i)
    {
        for (int j = corners.left; j <= corners.right; ++j)
        {
            if (self->map_plan[i][j] == '#')
            {
                uint8_t intersaction = check_intersection(&self->charac, char_pos, j * 40, i * 40);
                collision &= intersaction;
                if (collision == 0)
                    goto break_label;
            }
        }
    }
    break_label:
    return collision;
}

void map_character_move(map_t *const self)
{
    RECT new_char_pos;
    new_char_pos.left = self->charac.rect._vertices[0].x + self->charac.speed.x;
    new_char_pos.right = self->charac.rect._vertices[2].x + self->charac.speed.x;
    new_char_pos.bottom = self->charac.rect._vertices[0].y + self->charac.speed.y - GRAVITY;
    new_char_pos.top = self->charac.rect._vertices[2].y + self->charac.speed.y - GRAVITY;

    uint8_t collision = collision_check(self, new_char_pos);
    
    if (collision & 0b00000001)
    {
        self->charac.rect._vertices[0].x = new_char_pos.left;
        self->charac.rect._vertices[1].x = new_char_pos.right;
        self->charac.rect._vertices[2].x = new_char_pos.right;
        self->charac.rect._vertices[3].x = new_char_pos.left;
    }
    if (((collision & 0b00000010) >> 1))
    {
        self->charac.rect._vertices[0].y = new_char_pos.bottom;
        self->charac.rect._vertices[1].y = new_char_pos.bottom;
        self->charac.rect._vertices[2].y = new_char_pos.top;
        self->charac.rect._vertices[3].y = new_char_pos.top;
        self->charac.on_floor = 0;
    }
    else
        self->charac.on_floor = 1;
}

void map_draw(map_t *const self)
{
    for (int i = 0; i < self->size_of_blocks; ++i)
    {
        textured_rectangle_draw(self->blocks + i);
    }
    map_character_move(self);
}


#endif
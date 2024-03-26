#ifndef TEXTURE_H
#define TEXTURE_H

#include "point.h"

struct Texture
{
    GLuint texture_id;
    point_t size;
    int32_t channels;
    uint8_t *image;
};

typedef struct Texture texture_t;

void texture_init(texture_t *const self, const char *path)
{
    self->image = stbi_load(path, &self->size.x, &self->size.y, &self->channels, 0);
    if (!self->image)
    {
        fprintf(stderr, "Error! Texture load error!");
        exit(1);
    }
    glGenTextures(1, &self->texture_id);
    glBindTexture(GL_TEXTURE_2D, self->texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->size.x, self->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
                 self->image);
                 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(self->image);
}

texture_t texture_new(const char *path)
{
    texture_t new_texture;
    texture_init(&new_texture, path);
    return new_texture;
}

#endif
#ifndef texture_h
#define texture_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../inc/sdl.h"

typedef struct texture_t
{
	SDL_Texture *texture;
	int w;
	int h;
} texture_t;

void texture_init(texture_t *texture);
void texture_render(texture_t *texture, SDL_Rect *src_rect, SDL_Rect *dst_rect);

void texture_load_from_file(texture_t *texture, const char* path);
SDL_Texture* sdl_load_texture(const char* path);

#endif

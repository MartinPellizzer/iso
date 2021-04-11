#ifndef _map_h
#define _map_h

#include <SDL2/SDL.h>
#include "../inc/util.h"
#include "../inc/iso.h"
#include "../inc/sdl.h"
#include "../inc/grid.h"
#include "../inc/mouse.h"
#include "../inc/texture.h"

typedef struct map_t
{
	texture_t texture;
	vec2_t tile_num;
	vec2_t tile_size;
} map_t;

map_t map;

void map_init(texture_t *texture, vec2_t tile_size, vec2_t tile_num);
void map_get_tile_pos();
void map_render();

#endif

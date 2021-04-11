#ifndef _moving_area_h
#define _moving_area_h

#include <SDL2/SDL.h>
#include "../inc/util.h"
#include "../inc/iso.h"
#include "../inc/sdl.h"
#include "../inc/grid.h"
#include "../inc/player.h"

typedef struct moving_area_t
{
	SDL_Texture *texture;
	vec2_t map_tiles_num;
	vec2_t tile_size;
	SDL_Rect src_rect;
} moving_area_t;


void moving_area_init(moving_area_t *moving_area, SDL_Texture *texture, vec2_t tile_size, vec2_t map_tiles_num);
void moving_area_render(moving_area_t *moving_area, player_t *player);

#endif

#ifndef _cursor_h
#define _cursor_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../inc/util.h"
#include "../inc/mouse.h"
#include "../inc/camera.h"
#include "../inc/iso.h"
#include "../inc/sdl.h"
#include "../inc/player.h"

typedef struct cursor_t
{
	SDL_Texture *texture;
	vec2_t size;
	vec2_t pos;
	vec2_t tiles_num;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
} cursor_t;

cursor_t cursor;

void cursor_init(SDL_Texture *texture, vec2_t pos, vec2_t tiles_num);
void cursor_update();
void cursor_render();

void cursor_move(int x, int y, player_t *player);

#endif

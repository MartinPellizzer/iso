#ifndef player_h
#define player_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../inc/globals.h"
#include "../inc/util.h"
#include "../inc/grid.h"
#include "../inc/sdl.h"
#include "../inc/iso.h"
#include "../inc/llist.h"


typedef struct camera_t camera_t;

vec2_t selected_tile; 

float walk_anim_lenght;
double walk_anim_time;

typedef enum player_state_t
{
	IDLE,
	WALKING
} player_state_t;

typedef struct player_t
{
	int id;
	SDL_Texture *texture;
	player_state_t state;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	vec2_t size;
	vec2_t pos;
	vec2_t pos_from;
	vec2_t pos_to;
	int direction;
	int frame_current;
	int frame_total;
	int frame_timer;
	int animation_speed;

	int mov;
} player_t;

void player_init(player_t *player, SDL_Texture *texture, vec2_t pos, int dir);
void player_update(player_t *player);
void player_render(player_t *player);

void player_update_dst_rect(player_t *player);
void player_move(player_t *player, int x, int y);
void player_get_trans_pos(player_t *player, vec2f_t *trans_pos);
void player_animate(player_t *player);

#endif

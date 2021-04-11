#ifndef camera_h
#define camera_h

#include "../inc/globals.h"
#include "../inc/util.h"
#include "../inc/mouse.h"
#include "../inc/player.h"
#include "../inc/iso.h"

typedef struct player_t player_t;

typedef struct camera_t
{
	vec2_t pos;
	vec2_t pan_origin;
} camera_t;

camera_t camera;

void camera_init();
void camera_update(vec2_t *tile_size);
void camera_center_to_player(player_t *player);

#endif

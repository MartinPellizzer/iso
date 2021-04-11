#ifndef _player_manager_h
#define _player_manager_h

#include "../inc/player.h"
#include "../inc/camera.h"

typedef struct player_manager_t
{
	player_t *players;
	player_t *current_player;
	int num;
} player_manager_t;

player_manager_t player_manager;

void player_manager_init(int num);
void player_manager_update();
void player_manager_render();

#endif

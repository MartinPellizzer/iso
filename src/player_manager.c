#include "../inc/player_manager.h"

void player_manager_init(int num)
{
	player_manager.players = (player_t*)malloc(sizeof(player_t) * num);
	if(player_manager.players == NULL)
		return;
	player_manager.current_player = NULL;
	player_manager.num = num;
}

void player_manager_render()
{
	for(int i = 0; i < player_manager.num; i++)
	{
		if(player_manager.players[i].id >= 0)
		{
			player_render(&player_manager.players[i]);
		}
	}
}

void player_manager_update()
{
	for(int i = 0; i < player_manager.num; i++)
	{
		if(player_manager.players[i].id >= 0)
		{
			player_update(&player_manager.players[i]);
		}
	}
}


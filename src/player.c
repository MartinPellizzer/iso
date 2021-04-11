#include "../inc/player.h"
#include <stdio.h>

void player_init(player_t *player, SDL_Texture *texture, vec2_t pos, int direction)
{
	player->texture = texture;
	player->pos.x = pos.x;
	player->pos.y = pos.y;
	player->size.x = 32;
	player->size.y = 32;
	player->state = 0;
	player->pos_from.x = 0;
	player->pos_from.y = 0;
	player->pos_to.x = 0;
	player->pos_to.y = 0;

	player->frame_timer = 0;
	player->frame_current = 0;
	player->frame_total = 4;
	player->direction = direction;


	selected_tile.x = 0; 
	selected_tile.y = 0; 

	walk_anim_lenght = 0.5;
	walk_anim_time = 0;

	player->src_rect.x = 0;
	player->src_rect.y = 0;
	player->src_rect.w = 32;
	player->src_rect.h = 32;

	player->dst_rect.x = 0;
	player->dst_rect.y = 0;
	player->dst_rect.w = 32 * scale;
	player->dst_rect.h = 32 * scale;

	player->animation_speed = 16;

	player->mov = 3;
}

/*
void player_move(player_t *player, int x, int y)
{
	if(player->state == IDLE)
	{
		if(x == 0 && y == -1) player->direction = 0;
		else if(x == 1 && y == 0) player->direction = 1;
		else if(x == 0 && y == 1) player->direction = 2;
		else if(x == -1 && y == 0) player->direction = 3;

		player->pos_from.x = player->pos.x;
		player->pos_from.y = player->pos.y;

		player->pos_to.x = player->pos.x + x;
		player->pos_to.y = player->pos.y + y;

		player->pos.x = player->pos_to.x;
		player->pos.y = player->pos_to.y;

		player->state = WALKING;
	}
}
*/

void player_move(player_t *player, int x, int y)
{
	if(player->state == IDLE)
	{

		if(path != NULL)
		{
			
			if(path->pos.x == 0 && path->pos.y == -1) player->direction = 0;
			else if(path->pos.x == 1 && path->pos.y == 0) player->direction = 1;
			else if(path->pos.x == 0 && path->pos.y == 1) player->direction = 2;
			else if(path->pos.x == -1 && path->pos.y == 0) player->direction = 3;
			

			player->pos_from.x = player->pos.x;
			player->pos_from.y = player->pos.y;

			player->pos_to.x = player->pos.x + path->pos.x;
			player->pos_to.y = player->pos.y + path->pos.y;

			player->pos.x = player->pos_to.x;
			player->pos.y = player->pos_to.y;

			llist_vec2_delete_first(&path);

			player->state = WALKING;
		}
	}
}

void player_animate(player_t *player)
{
	int frame_w = 128 / player->frame_total;
	int frame_h = 128 / player->frame_total;

	player->frame_timer += frame_delay;
	if (player->frame_timer >= frame_delay * player->animation_speed)
	{
		player->frame_timer = 0;
		player->frame_current += 1;
		player->frame_current %= player->frame_total;
	}

	player->src_rect.x = player->frame_current * frame_w;
	player->src_rect.y = player->direction * frame_h;
}

void player_get_trans_pos(player_t *player, vec2f_t *trans_pos)
{
	float x = player->pos.x;
	float y = player->pos.y;
	
	if(player->state == WALKING)
	{
		walk_anim_time += (float)frame_delay / 1000;

		float t = walk_anim_time * 3;
		if(t >= 1)
		{
			walk_anim_time = 0;
			t = 1;
			player->state = IDLE;
		}

		x = lerp(player->pos_from.x, player->pos_to.x, t); 
		y = lerp(player->pos_from.y, player->pos_to.y, t); 
	}

	trans_pos->x = x;
	trans_pos->y = y;
}

void player_update_dst_rect(player_t *player)
{
	player->dst_rect.x = player->pos.x; 
	player->dst_rect.y = player->pos.y; 
	player->dst_rect.w = player->size.x * scale; 
	player->dst_rect.h = player->size.y * scale; 
}

void player_update(player_t *player)
{
	player_update_dst_rect(player);
	player_animate(player);
}

void player_render(player_t *player)
{
	vec2f_t pos;
	player_get_trans_pos(player, &pos);

	iso_character_to_screen(&pos);

	player->dst_rect.x = pos.x;
	player->dst_rect.y = pos.y - tile_size.y - (tile_size.y / 4);
	SDL_RenderCopy(renderer, player->texture, &player->src_rect, &player->dst_rect);
}

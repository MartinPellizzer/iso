#include "../inc/cursor.h"

void cursor_init(SDL_Texture *texture, vec2_t pos, vec2_t tiles_num)
{
	cursor.texture = texture;
	cursor.size.x = 32;
	cursor.size.y = 16;
	cursor.pos.x = pos.x;
	cursor.pos.y = pos.y;
	cursor.tiles_num.x = tiles_num.x;
	cursor.tiles_num.y = tiles_num.y;
	cursor.src_rect.x = 64;
	cursor.src_rect.y = 0;
	cursor.src_rect.w = 32;
	cursor.src_rect.h = 16; 
	cursor.dst_rect.x = 0;
	cursor.dst_rect.y = 0;
	cursor.dst_rect.w = 32;
	cursor.dst_rect.h = 16;
}

void cursor_update()
{
	vec2_t tmp_pos = cursor.pos;
	
	iso_map_to_screen(&tmp_pos);

	cursor.dst_rect.x = tmp_pos.x;
	cursor.dst_rect.y = tmp_pos.y;
	cursor.dst_rect.w = cursor.size.x * scale;
	cursor.dst_rect.h = cursor.size.y * scale;
}

void cursor_render()
{
	SDL_RenderCopy(renderer, cursor.texture, &cursor.src_rect, &cursor.dst_rect);
}


void cursor_move(int x, int y, player_t *player)
{
	vec2_t tmp_pos = cursor.pos;
	if(abs(tmp_pos.x - player->pos.x + x) + abs(tmp_pos.y - player->pos.y + y) <= player->mov)
	{
		if(cursor.pos.x + x < 16 && cursor.pos.x + x >= 0)
			cursor.pos.x += x;
		if(cursor.pos.y + y < 16 && cursor.pos.y + y >= 0)
			cursor.pos.y += y;
	}
}


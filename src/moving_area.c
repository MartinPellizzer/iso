#include "../inc/moving_area.h"

#include <math.h>

void moving_area_init(moving_area_t *moving_area, SDL_Texture *texture, vec2_t tile_size, vec2_t map_tiles_num)
{
	moving_area->texture = texture;
	moving_area->tile_size.x = tile_size.x;
	moving_area->tile_size.y = tile_size.y;
	moving_area->map_tiles_num.x = map_tiles_num.x;
	moving_area->map_tiles_num.y = map_tiles_num.y;
	moving_area->src_rect.x = 0;
	moving_area->src_rect.y = 0;
	moving_area->src_rect.w = tile_size.x;
	moving_area->src_rect.h = tile_size.x;
}

void moving_area_render(moving_area_t *moving_area, player_t *player)
{
	SDL_Rect dst_rect;
	sdl_set_rect(&dst_rect, 0, 0, tile_size.x, tile_size.y);

	for(int y = 0; y < moving_area->map_tiles_num.y; y++)
		for(int x = 0; x < moving_area->map_tiles_num.x; x++)
		{
			if(abs(y - player->pos.y) + abs(x - player->pos.x) <= player->mov)
			{
				vec2_t pos = {0};
				pos.x = x;
				pos.y = y;

				iso_map_to_screen(&pos);

				dst_rect.x = pos.x;
				dst_rect.y = pos.y;

				SDL_RenderCopy(renderer, moving_area->texture, &moving_area->src_rect, &dst_rect);
			}
		}
}


#include "../inc/map.h"

void map_init(texture_t *texture, vec2_t tile_size, vec2_t tile_num)
{
	map.texture = *texture;
	map.tile_size.x = tile_size.x;
	map.tile_size.y = tile_size.y;
	map.tile_num.x = tile_num.x;
	map.tile_num.y = tile_num.y;
}

void map_get_tile_pos()
{
	vec2_t tmp_pos = {mouse.pos.x - camera.pos.x, mouse.pos.y - camera.pos.y};
	
	iso_mouse_to_map(&tmp_pos);
}

void map_render()
{
	SDL_Rect src_rect, dst_rect;
	sdl_set_rect(&src_rect, 0, 0, map.tile_size.x, map.tile_size.y);
	sdl_set_rect(&dst_rect, 0, 0, tile_size.x, tile_size.y);

	for(int y = 0; y < map.tile_num.y; y++)
		for(int x = 0; x < map.tile_num.x; x++)
		{
			vec2_t pos = {x, y};

			iso_map_to_screen(&pos);


			dst_rect.x = pos.x;
			dst_rect.y = pos.y;

			texture_render(&map.texture, &src_rect, &dst_rect);

		}
}


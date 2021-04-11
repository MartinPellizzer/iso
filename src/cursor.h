#include "../inc/cursor.h"

void render_cursor()
{
	vec2_t pos = {0};
	pos.x = mouse.pos.x - camera.pos.x;
	pos.y = mouse.pos.y - camera.pos.y;
	
	iso_mouse_to_map(&pos);

	SDL_Rect src_rect, dst_rect;
	sdl_set_rect(&src_rect, 32, 0, 32, 32);
	sdl_set_rect(&dst_rect, 32, 0, tile_size.x, tile_size.y);

	iso_map_to_screen(&pos);
	dst_rect.x = pos.x;
	dst_rect.y = pos.y;

	SDL_RenderCopy(renderer, map.texture, &src_rect, &dst_rect);
}


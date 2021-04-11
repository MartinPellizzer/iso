#include "../inc/camera.h"

void camera_init()
{
	camera.pos.x = WINDOW_WIDTH / 2;
	camera.pos.y = 0;
}

void camera_update(vec2_t *tile_size)
{
	if(mouse.wheel.pressed) 
	{
		camera.pos.x = camera.pan_origin.x + ((mouse.wheel.pan.origin.x - mouse.pos.x) * (-1)); 
		camera.pos.y = camera.pan_origin.y + ((mouse.wheel.pan.origin.y - mouse.pos.y) * (-1)); 
	}
	if(mouse.wheel.scrolled)
	{
		mouse.wheel.scrolled = 0;
		if(scale + mouse.wheel.scroll.dir.y > 0)
			scale += mouse.wheel.scroll.dir.y;
		tile_size->x = scale * 32;
		tile_size->y = scale * 16;
	}
}

void camera_center_to_player(player_t *player)
{	
	vec2_t pos = player->pos;

	iso_map_to_screen(&pos);

	camera.pos.x += 400 - pos.x;
	camera.pos.y += 300 - pos.y;
}


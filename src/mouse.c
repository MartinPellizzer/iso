#include "../inc/mouse.h"

void mouse_update()
{
	SDL_GetMouseState(&mouse.pos.x, &mouse.pos.y);
}

void mouse_scroll(int x, int y)
{
	mouse.wheel.scrolled = 1;
	mouse.wheel.scroll.dir.x = x;
	mouse.wheel.scroll.dir.y = y;
}

void mouse_pan_start()
{
	mouse.wheel.pressed = 1;
	mouse.wheel.pan.origin.x = mouse.pos.x;
	mouse.wheel.pan.origin.y = mouse.pos.y;
	camera.pan_origin.x = camera.pos.x;
	camera.pan_origin.y = camera.pos.y;
}


void mouse_pan_end()
{
	mouse.wheel.pressed = 0;
}

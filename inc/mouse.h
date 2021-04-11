#ifndef mouse_h
#define mouse_h

#include <SDL2/SDL.h>
#include "../inc/util.h"
#include "../inc/camera.h"

typedef struct scroll_t
{
	vec2_t dir;
} scroll_t;

typedef struct pan_t
{
	vec2_t origin;
} pan_t;

typedef struct wheel_t
{
	pan_t pan;
	scroll_t scroll;
	int scrolled;
	int pressed;
} wheel_t;

typedef struct mouse_t
{
	vec2_t pos;
	wheel_t wheel;
} mouse_t;

mouse_t mouse;

void mouse_update();

void mouse_scroll(int x, int y);
void mouse_pan_start();
void mouse_pan_end();

#endif

#ifndef globals_h
#define globals_h

#include <SDL2/SDL.h>
#include "../inc/camera.h"
#include "../inc/mouse.h"
#include "../inc/llist.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 

int scale;


int FPS;
int frame_delay;
int frame_start;
int frame_time;

llist_vec2_t *path;


#endif

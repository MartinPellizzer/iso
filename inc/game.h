#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "../inc/globals.h"
#include "../inc/util.h"
#include "../inc/sdl.h"
#include "../inc/texture.h"
#include "../inc/iso.h"
#include "../inc/mouse.h"
#include "../inc/camera.h"

#include "../inc/player.h"
#include "../inc/llist.h"
#include "../inc/map.h"
#include "../inc/astar.h"
#include "../inc/cursor.h"
#include "../inc/moving_area.h"
#include "../inc/player_manager.h"

int is_running;

void init();
void quit();
void handle_inputs();
void update();
void render();

void render_map_iso();
void render_player_iso();

void delay_fps();


#endif

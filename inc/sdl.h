#ifndef sdl_h
#define sdl_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../inc/globals.h"

SDL_Window *window;
SDL_Renderer *renderer;

void sdl_init();
void sdl_quit();

void sdl_set_rect(SDL_Rect *rect, int x, int y, int w, int h);

#endif

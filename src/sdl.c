#include "../inc/sdl.h"

void sdl_init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("SDL init failed!!\n");
		exit(1);
	}

	window = SDL_CreateWindow("Oliark", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if(!window)
	{
		printf("SDL window failed!!\n");
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer)
	{
		printf("SDL renderer failed!!\n");
		exit(1);
	}

	int img_flags = IMG_INIT_PNG;
	if(!(IMG_Init(img_flags) & img_flags))
	{
		printf("SDL image failed!!\n");
		exit(1);
	}
}


void sdl_quit()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void sdl_set_rect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;	
	rect->y = y;	
	rect->w = w;	
	rect->h = h;	
}


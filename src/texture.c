#include "../inc/texture.h"

void texture_init(texture_t *texture)
{
	texture->texture = NULL;
	texture->w = 0;
	texture->h = 0;
}

void texture_render(texture_t *texture, SDL_Rect *src_rect, SDL_Rect *dst_rect)
{
	SDL_RenderCopy(renderer, texture->texture, src_rect, dst_rect);
}

void texture_load_from_file(texture_t *texture, const char* path)
{
	SDL_Surface *tmp_surface = IMG_Load(path);
	if(tmp_surface == NULL) 
	{
		printf("Cant load image!!\n");
		return;
	}

	texture->texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	if(texture->texture == NULL) 
	{
		printf("Cant load image!!\n");
		SDL_FreeSurface(tmp_surface);
		return;
	}

	texture->w = tmp_surface->w;
	texture->h = tmp_surface->h;

	SDL_FreeSurface(tmp_surface);
}

SDL_Texture* sdl_load_texture(const char* path)
{
	SDL_Surface *tmp_surface = IMG_Load(path);
	if(tmp_surface == NULL) 
	{
		printf("Cant load image!!\n");
		return NULL;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
	if(texture == NULL) 
	{
		printf("Cant load image!!\n");
		SDL_FreeSurface(tmp_surface);
		return NULL;
	}

	SDL_FreeSurface(tmp_surface);

	return texture;
}

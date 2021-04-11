#include "../inc/iso.h"


void iso_map_to_screen(vec2_t *pos)
{
	vec2_t tmp_pos = {pos->x, pos->y};

	int mtx[2][2] =
	{
		{0.5 * 32 * scale, -0.5 * 32 * scale},
		{0.25 * 32 * scale, 0.25 * 32 * scale},
	};

	pos->x = (tmp_pos.x * mtx[0][0]) + (tmp_pos.y * mtx[0][1]) - (32 * scale / 2) + (camera.pos.x);
	pos->y = (tmp_pos.x * mtx[1][0]) + (tmp_pos.y * mtx[1][1]) + (camera.pos.y);
}

void iso_character_to_screen(vec2f_t *pos)
{
	vec2f_t tmp_pos = {pos->x, pos->y};

	int mtx[2][2] =
	{
		{0.5 * 32 * scale, -0.5 * 32 * scale},
		{0.25 * 32 * scale, 0.25 * 32 * scale},
	};

	pos->x = (tmp_pos.x * mtx[0][0]) + (tmp_pos.y * mtx[0][1]) - (32 * scale / 2) + (camera.pos.x);
	pos->y = (tmp_pos.x * mtx[1][0]) + (tmp_pos.y * mtx[1][1]) + (camera.pos.y);
}

void iso_mouse_to_map(vec2_t *pos)
{
	vec2_t tmp_pos = {pos->x, pos->y};
	int mtx[2][2] = 
	{
		{0.25 * 32 * scale, 0.5 * 32 * scale},
		{-0.25 * 32 * scale, 0.5 * 32 * scale},
	};
	int determinator = (mtx[1][1] * mtx[0][0]) - (mtx[0][1] * mtx[1][0]);

	pos->x = ((tmp_pos.x * mtx[0][0]) + (tmp_pos.y * mtx[0][1])) / determinator;
	pos->y = ((tmp_pos.x * mtx[1][0]) + (tmp_pos.y * mtx[1][1])) / determinator;
}


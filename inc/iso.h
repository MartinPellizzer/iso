#ifndef iso_h
#define iso_h

#include "../inc/globals.h"
#include "../inc/util.h"
#include "../inc/camera.h"

typedef struct camera_t camera_t;

void iso_map_to_screen(vec2_t *pos);
void iso_character_to_screen(vec2f_t *pos);
void iso_mouse_to_map(vec2_t *pos);

#endif

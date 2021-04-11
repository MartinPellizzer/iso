#ifndef util_h
#define util_h

typedef struct vec2_t
{
	int x;
	int y;
} vec2_t;

typedef struct vec2f_t
{
	float x;
	float y;
} vec2f_t;

float lerp(float a, float b, float f);

#endif

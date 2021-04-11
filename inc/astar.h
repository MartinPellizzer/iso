#ifndef _astar_h
#define _astar_h

#include <stdlib.h>
#include <math.h>
#include "../inc/map.h"

typedef struct node_t
{
	int obstacle;
	int visited;
	float global;
	float local;
	int x;
	int y;
	struct node_t *neighbors[4];
	int neighbors_num;
	struct node_t *parent;
} node_t;

node_t *nodes;
node_t *node_start;
node_t *node_end;

void astar_init(map_t *map);
void solve_astar(map_t *map);
void astar_quit();



typedef struct list_t
{
	struct node_t *node;
	struct list_t *next;
} list_t;

void list_insert(list_t **head, node_t *n);
void list_delete_first(list_t **head);
void list_print(list_t *head);



#endif

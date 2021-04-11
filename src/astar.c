#include "../inc/astar.h"

static void _list_generate_moves(llist_vec2_t *tmp_path);
static float distance(node_t *a, node_t *b);
static float heuristic(node_t *a, node_t *b);

void astar_init(map_t *map)
{
	int current_num;
	nodes = NULL;
	node_start = NULL;
	node_end = NULL;

	// dinamically create a grid of nodes to use for the path-finding
	nodes = (node_t*)malloc(sizeof(node_t) * map->tile_num.x * map->tile_num.y);
	for(int x = 0; x < map->tile_num.x; x++)
		for(int y = 0; y < map->tile_num.x; y++)
		{
			nodes[y * map->tile_num.x + x].x = x;
			nodes[y * map->tile_num.x + x].y = y;
			nodes[y * map->tile_num.x + x].obstacle = 0;
			nodes[y * map->tile_num.x + x].neighbors[0] = NULL;
			nodes[y * map->tile_num.x + x].neighbors[1] = NULL;
			nodes[y * map->tile_num.x + x].neighbors[2] = NULL;
			nodes[y * map->tile_num.x + x].neighbors[3] = NULL;
			nodes[y * map->tile_num.x + x].parent = NULL;
			nodes[y * map->tile_num.x + x].visited = 0;
			nodes[y * map->tile_num.x + x].neighbors_num = 0;

			// link each node with its neighbors
			if(y > 0)
			{
				current_num = nodes[y * map->tile_num.x + x].neighbors_num;
				nodes[y * map->tile_num.x + x].neighbors[current_num] = &nodes[(y - 1) * map->tile_num.x + (x + 0)];
				nodes[y * map->tile_num.x + x].neighbors_num += 1;
			}
			if(y < map->tile_num.y - 1)
			{
				current_num = nodes[y * map->tile_num.x + x].neighbors_num;
				nodes[y * map->tile_num.x + x].neighbors[current_num] = &nodes[(y + 1) * map->tile_num.x + (x + 0)];
				nodes[y * map->tile_num.x + x].neighbors_num += 1;
			}
			if(x > 0)
			{
				current_num = nodes[y * map->tile_num.x + x].neighbors_num;
				nodes[y * map->tile_num.x + x].neighbors[current_num] = &nodes[(y + 0) * map->tile_num.x + (x - 1)];
				nodes[y * map->tile_num.x + x].neighbors_num += 1;
			}
			if(x < map->tile_num.x - 1)
			{
				current_num = nodes[y * map->tile_num.x + x].neighbors_num;
				nodes[y * map->tile_num.x + x].neighbors[current_num] = &nodes[(y + 0) * map->tile_num.x + (x + 1)];
				nodes[y * map->tile_num.x + x].neighbors_num += 1;
			}
		}
}

void solve_astar(map_t *map)
{
	// reset astar nodes
	for(int x = 0; x < map->tile_num.x; x++)
		for(int y = 0; y < map->tile_num.x; y++)
		{
			nodes[y * map->tile_num.x + x].parent = NULL;
			nodes[y * map->tile_num.x + x].visited = 0;
			nodes[y * map->tile_num.x + x].global = 9999;
			nodes[y * map->tile_num.x + x].local = 9999;
		}

	// execute astar
	node_t *node_current = node_start;
	node_start->local = 0.0f;
	node_start->global = heuristic(node_start, node_end);

	list_t *list_not_tested_nodes = NULL;
	list_insert(&list_not_tested_nodes, node_start);

	while(list_not_tested_nodes != NULL && node_current != node_end)
	{
		// TODO sort llist by node.global ascending
		if(list_not_tested_nodes->node->visited == 1)
			list_delete_first(&list_not_tested_nodes);

		if(list_not_tested_nodes == NULL)
			break;

		node_current = list_not_tested_nodes->node;
		node_current->visited = 1;

		int i = 0;
		while(i < node_current->neighbors_num)
		{
			node_t *node_neighbor = node_current->neighbors[i];
			
			if(!node_neighbor->visited && node_neighbor->obstacle == 0)
				list_insert(&list_not_tested_nodes, node_neighbor);

			float possibly_lower_goal = node_current->local + distance(node_current, node_neighbor);

			if(possibly_lower_goal < node_neighbor->local)
			{
				node_neighbor->parent = node_current;
				node_neighbor->local = possibly_lower_goal;
				node_neighbor->global = node_neighbor->local + heuristic(node_neighbor, node_end);
			}
			i++;
		}
	}
	
	// invert list order
	llist_vec2_t *tmp_path = NULL;
	if(node_end != NULL)
	{
		node_t *p = node_end;
		while(p != NULL)
		{
			vec2_t pos = {p->x, p->y};
			llist_vec2_insert(&tmp_path, pos);

			p = p->parent;
		}
	}

	// create a list of movements
	_list_generate_moves(tmp_path);

	while(tmp_path != NULL)
		llist_vec2_delete_first(&tmp_path);

	//llist_vec2_print(tmp_path);
		
}

void _list_generate_moves(llist_vec2_t *tmp_path)
{
	llist_vec2_t *current = tmp_path;
	llist_vec2_t *prev = tmp_path;
	while(current != NULL)
	{
		vec2_t pos;
		pos.x = current->pos.x - prev->pos.x;
		pos.y = current->pos.y - prev->pos.y;
		llist_vec2_insert(&path, pos);
		prev = current;
		current = current->next;
	}
}

void list_insert(list_t **head, node_t *n)
{
	list_t *new_node = (list_t*)malloc(sizeof(list_t));
	new_node->node = n;
	new_node->next = *head;
	*head = new_node;
}

void list_delete_first(list_t **head)
{
	list_t *tmp;
	if(head == NULL || *head == NULL) return;
	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

void list_print(list_t *head)
{
	list_t *tmp = head;
	while(tmp != NULL)
	{
		printf("(%d  %d)", tmp->node->x, tmp->node->y);
		tmp = tmp->next;
	}
	printf("\n");
}

float distance(node_t *a, node_t *b)
{
	return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

float heuristic(node_t *a, node_t *b)
{
	return distance(a, b);
}


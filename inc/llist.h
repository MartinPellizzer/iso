#ifndef llist_h
#define llist_h

#include <stdlib.h>
#include "../inc/util.h"

typedef struct llist_vec2_t
{
	vec2_t pos;
	struct llist_vec2_t *next;
} llist_vec2_t;

void llist_vec2_insert(llist_vec2_t **head, vec2_t pos);
void llist_vec2_delete_first(llist_vec2_t **head);
void llist_vec2_print(llist_vec2_t *head);

#endif

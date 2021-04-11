#include "../inc/llist.h"

#include <stdio.h>

void llist_vec2_insert(llist_vec2_t **head, vec2_t pos)
{
	llist_vec2_t *node = (llist_vec2_t*)malloc(sizeof(llist_vec2_t));
	node->pos.x = pos.x;
	node->pos.y = pos.y;
	node->next = *head;
	*head = node;
}

void llist_vec2_delete_first(llist_vec2_t **head)
{
	llist_vec2_t *tmp;
	if(head == NULL || *head == NULL) return;
	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

void llist_vec2_print(llist_vec2_t *head)
{
	llist_vec2_t *tmp = head;
	while(tmp != NULL)
	{
		printf("(%d  %d)", tmp->pos.x, tmp->pos.y);
		tmp = tmp->next;
	}
	printf("\n");
}




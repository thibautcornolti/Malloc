/*
** EPITECH PROJECT, 2017
** malloc
** File description:
** malloc
*/

#include <unistd.h>

typedef struct metadata_s {
	void *ptr;
	size_t size;
	struct metadata_s *prev;
	struct metadata_s *next;
} metadata_t;

void add_elem_after_elem(metadata_t **first_node, metadata_t *after_elem, metadata_t *elem)
{
	metadata_t *temp = *first_node;

	while (temp && temp != after_elem && temp->next)
		temp = temp->next;
	if (!temp) {
		elem->next = NULL;
		elem->prev = NULL;
		*first_node = elem;
		return ;
	}
	elem->next = temp->next;
	temp->next = elem;
	elem->prev = temp;
	if (elem->next)
		elem->next->prev = elem;
}

void add_elem(metadata_t **first_node, metadata_t *elem)
{
	add_elem_after_elem(first_node, NULL, elem);
}

void del_elem(metadata_t **first_node, metadata_t *elem)
{
	metadata_t *temp = *first_node;

	if (!temp)
		return ;
	while (temp && temp != elem)
		temp = temp->next;
	if (!temp)
		return ;
	if (temp->next)
		temp->next->prev = temp->prev;
	if (temp->prev)
		temp->prev->next = temp->next;
	if (temp == *first_node)
		*first_node = temp->next;
}
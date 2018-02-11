/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <signal.h>
#include "malloc.h"

static void resize_heap()
{
	metadata_t *temp = allocated->last;

	if (temp && !temp->occupied) {
		if (temp->prev) {
			temp->prev->next = NULL;
			allocated->last = temp->prev;
		} else
			allocated = NULL;
		brk(temp);
	}
}

static void merge(metadata_t *p)
{
	for (; p->next && !p->next->occupied;) {
		p->size += HEADER + p->next->size;
		p->next = p->next->next;
		if (p->next)
			p->next->prev = p;
		else
			allocated->last = p;
	}
}

void free(void *ptr)
{
	metadata_t *temp;

	if (!ptr)
		return;
	temp = ptr - HEADER;
	if (temp->ptr != ptr)
		return;
	lock_thread(0);
	temp->occupied = 0;
	for (; temp->prev && !temp->prev->occupied; temp = temp->prev);
	merge(temp);
	resize_heap();
	unlock_thread(0);
}

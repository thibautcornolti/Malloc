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
	unlock_thread(0);
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
	resize_heap();
}

void free(void *ptr)
{
	metadata_t *temp;

	lock_thread(0);
	if (!ptr) {
		unlock_thread(0);
		return;
	}
	temp = ptr - HEADER;
	if (temp->ptr != ptr) {
		unlock_thread(0);
		return;
	}
	temp->occupied = 0;
	merge(temp);
}

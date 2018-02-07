/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

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
	resize_heap();
}

void free(void *ptr)
{
	metadata_t *temp = allocated;

	write(1, "free\n", 5);
	if (!ptr || !temp || ptr < (void *)allocated || ptr > sbrk(0))
		return;
	lock_thread(0);
	for (;temp && (void *)temp + HEADER != ptr; temp = temp->next);
	if (temp) {
		temp->occupied = 0;
		for (; temp->prev && !temp->prev->occupied; temp = temp->prev);
		merge(temp);
	}
	unlock_thread(0);
}
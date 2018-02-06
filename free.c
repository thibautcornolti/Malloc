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

	if (temp && temp->occupied == 0) {
		brk(temp->ptr);
		if (temp->prev) {
			temp->prev->next = NULL;
			allocated->last = temp->prev;
		} else {
			allocated = NULL;
		}
	}
	unlock_thread(0);
}

static void merge()
{
	metadata_t *temp = allocated;
	metadata_t *removed;

	while (temp) {
		if (temp->next && !temp->occupied && !temp->next->occupied) {
			removed = temp->next;
			if (removed->next)
				removed->next->prev = removed->prev;
			else
				allocated->last = removed->prev;
			removed->prev->next = removed->next;
			removed->prev->size += HEADER + removed->size;
			continue;
		}
		temp = temp->next;
	}
	resize_heap();
}

void free(void *ptr)
{
	metadata_t *temp;

	write(2, "free\n", 5);
	lock_thread(0);
	if (!ptr) {
		unlock_thread(0);
		return ;
	}
	temp = ptr - HEADER;
	if (temp->ptr != ptr) {
		unlock_thread(0);
		return ;
	}
	temp->occupied = 0;
	merge();
}

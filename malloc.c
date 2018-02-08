/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <string.h>
#include <stdio.h>
#include "malloc.h"

metadata_t *allocated = NULL;

static void *init_heap(size_t i)
{
	allocated = sbrk(0);
	if (brk((void *) allocated + HEADER + i) == -1) {
		return (NULL);
	}
	allocated->size = i;
	allocated->ptr = (void *) allocated + HEADER;
	allocated->next = NULL;
	allocated->prev = NULL;
	allocated->last = allocated;
	allocated->occupied = 1;
	unlock_thread(0);
	return (allocated->ptr);
}

static void *resize_heap(size_t i)
{
	metadata_t *temp = allocated->last;
	metadata_t *newElem = sbrk(0);

	if (brk((void *) newElem + HEADER + i) == -1) {
		return (NULL);
	}
	newElem->size = i;
	newElem->ptr = (void *) newElem + HEADER;
	newElem->next = NULL;
	newElem->prev = temp;
	newElem->occupied = 1;
	temp->next = newElem;
	allocated->last = newElem;
	unlock_thread(0);
	return (newElem->ptr);
}

static void *realloc_freed(metadata_t *pMetadata)
{
	pMetadata->occupied = 1;
	unlock_thread(0);
	return (pMetadata->ptr);
}

void *malloc(size_t size)
{
	metadata_t *temp = allocated;

	size = ALIGN(size);
	lock_thread(0);
	if (!allocated)
		return (init_heap(size));
	for (; temp; temp = temp->next)
		if (!temp->occupied && temp->size >= size)
			return (realloc_freed(temp));
	return (resize_heap(size));
}

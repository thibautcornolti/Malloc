/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/
#include "malloc.h"

metadata_t *allocated = NULL;

static void *init_heap(size_t i)
{
	if (!i)
		return NULL;
	allocated = sbrk(0);
	if (brk((void *)allocated + HEADER + i) == -1)
		return (NULL);
	allocated->size = i;
	allocated->last = allocated;
	allocated->prev = NULL;
	allocated->next = NULL;
	allocated->occupied = 1;
	return ((void *)allocated + HEADER);
}

static void *resize_heap(size_t i)
{
	metadata_t *newElem = (metadata_t *)sbrk(0);

	if (brk((void *)newElem + HEADER + i) == -1)
		return (NULL);
	newElem->size = i;
	newElem->next = NULL;
	newElem->occupied = 1;
	allocated->last->next = newElem;
	newElem->prev = allocated->last;
	allocated->last = newElem;
	return ((void *)newElem + HEADER);
}

static void *realloc_freed(metadata_t *pMetadata)
{
	pMetadata->occupied = 1;
	return ((void *)pMetadata + HEADER);
}

void *malloc(size_t size)
{
	metadata_t *temp = allocated;
	void *ret = NULL;

	write(1, "malloc\n", 7);
	lock_thread(0);
	size = ALIGN(size);
	for (; temp && size; temp = temp->next)
		if (!temp->occupied && temp->size >= size) {
			ret = realloc_freed(temp);
			break;
		}
	if (!ret)
		ret = ((size && allocated) ? resize_heap(size) :
			init_heap(size));
	unlock_thread(0);
	write(1, ret ? "" : "malloc null\n", ret ? 0 : 12);
	return ret;
}
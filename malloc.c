/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <string.h>
#include "malloc.h"

metadata_t *allocated = NULL;

metadata_t *freed = NULL;

static void *init_heap(size_t i)
{
	if ((allocated = sbrk(i + HEADER)) == (void *)-1)
		return (NULL);
	allocated->size = i;
	allocated->ptr = allocated + HEADER;
	allocated->prev = NULL;
	allocated->next = NULL;
	return (allocated->ptr);
}

static void *resize_heap(size_t i)
{
	metadata_t *temp;
	metadata_t *iter;

	if ((temp = sbrk(i + HEADER)) == (void *)-1)
		return (NULL);
	iter = allocated;
	while (iter->next)
		iter = iter->next;
	iter->next = temp;
	temp->prev = iter;
	temp->next = NULL;
	temp->size = i;
	temp->ptr = temp + HEADER;
	return (temp->ptr);
}

static void *realloc_freed(metadata_t *pMetadata)
{
	metadata_t *temp = allocated;

	pMetadata->next->prev = pMetadata->prev;
	pMetadata->prev->next = pMetadata->next;
	pMetadata->ptr = pMetadata + HEADER;
	while (temp->next && temp->next < pMetadata)
		temp = temp->next;
	if (temp != allocated) {
		pMetadata->next = temp->next;
		pMetadata->prev = temp;
		if (pMetadata->next)
			pMetadata->next->prev = pMetadata;
		temp->next = pMetadata;
	} else {
		pMetadata->next = temp;
		temp->prev = pMetadata;
		pMetadata->prev = NULL;
		allocated = pMetadata;
	}
	return (pMetadata + HEADER);
}

void *malloc(size_t size)
{
	metadata_t *temp = freed;

	if (!allocated)
		return (init_heap(size));
	while (temp) {
		if (temp->size > size)
			return (realloc_freed(temp));
		temp = temp->next;
	}
	return (resize_heap(size));
}
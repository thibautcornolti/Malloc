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
	if (brk(allocated + HEADER + i) == -1) {
		write(2, "mallocnull0\n", 13);
		return (NULL);
	}
	allocated->size = i;
	allocated->ptr = allocated + HEADER;
	allocated->next = NULL;
	allocated->occupied = 1;
	return (allocated->ptr);
}

static void *resize_heap(size_t i)
{
	metadata_t *temp = allocated;
	metadata_t *newElem = sbrk(0);

	for (;temp->next; temp = temp->next);
	if (brk(newElem + HEADER + i) == -1) {
		write(2, "mallocnull1\n", 13);
		return (NULL);
	}
	newElem->next = NULL;
	newElem->size = i;
	newElem->ptr = newElem + HEADER;
	newElem->occupied = 1;
	temp->next = newElem;
	return (newElem->ptr);
}

static void *realloc_freed(metadata_t *pMetadata)
{
	pMetadata->occupied = 1;
	return (pMetadata->ptr);
}

void *malloc(size_t size)
{
	metadata_t *temp = allocated;

	write(2, "malloc\n", 8);
	size = align4(size);
	if (!allocated) {
		write(2, "endmalloc\n", 11);
		return (init_heap(size));
	}
	for (; temp; temp = temp->next) {
		if (!temp->occupied && temp->size >= size) {
			write(2, "endmalloc\n", 11);
			return (realloc_freed(temp));
		}
	}
	write(2, "endmalloc\n", 11);
	return (resize_heap(size));
}

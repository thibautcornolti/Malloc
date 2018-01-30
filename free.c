/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include "malloc.h"

static void release_ptr(metadata_t *);

static void resize_heap(metadata_t *pMetadata)
{
	metadata_t *temp = freed;

	if (pMetadata)
		release_ptr(pMetadata);
	while (temp->next)
		temp = temp->next;
	if (temp + HEADER + temp->size != sbrk(0))
		return;
	while (temp->prev && temp->prev->ptr + temp->prev->size + 1 == temp)
		temp = temp->prev;
	if (temp->prev)
		temp->prev->next = NULL;
	brk(temp);
}

static void merge()
{
	metadata_t *temp = freed;

	while (temp) {
		if (temp->ptr + temp->size + 1 == temp->next) {
			temp->size += HEADER + temp->next->size;
			temp->next = temp->next->next;
			if (temp->next->next)
				temp->next->next->prev = temp;
			continue;
		}
		temp = temp->next;
	}
	resize_heap(NULL);
}

static void release_ptr(metadata_t *pMetadata)
{
	metadata_t *temp = freed;

	if (!freed) {
		freed = pMetadata;
	} else if (freed > pMetadata) {
		pMetadata->next = freed;
		freed->prev = pMetadata;
		freed = pMetadata;
	} else {
		while (freed && temp->next && temp->next < pMetadata)
			temp = temp->next;
		pMetadata->prev = temp;
		pMetadata->next = NULL;
		temp->next = pMetadata;
	}
	merge();
}

void free(void *ptr)
{
	metadata_t *temp = allocated;

	while (ptr && temp && temp->ptr != ptr)
		temp = temp->next;
	if (!temp || !ptr)
		return;
	if (sbrk(0) == ptr + ((metadata_t *)ptr)->size)
		resize_heap(temp);
	else {
		if (temp->prev)
			temp->prev->next = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
		temp->next = NULL;
		temp->prev = NULL;
		release_ptr(temp);
	}
}
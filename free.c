/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include "malloc.h"

static void resize_heap(metadata_s *pMetadata)
{
	metadata_s *temp = freed;

	while (temp->next)
		temp = temp->next;
	while (temp->prev && temp->prev->ptr + temp->prev->size + 1 == temp)
		temp = temp->prev;
	if (temp->prev)
		temp->prev->next = NULL;
	brk(temp);
	heap_size -= (allocated + heap_size) - temp;
}

void merge()
{
	metadata_s *temp = freed;

	while (temp) {
		if (temp->ptr + temp->size  + 1 == temp->next){
			temp->size += HEADER + temp->next->size;
			temp->next = temp->next->next;
			if (temp->next->next)
				temp->next->next->prev = temp;
			continue;
		}
		temp = temp->next;
	}
}

void release_ptr(metadata_s *pMetadata)
{
	metadata_s *temp = freed;

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
	metadata_s *temp = allocated;

	while (ptr && temp && temp->ptr != ptr)
		temp = temp->next;
	if (!temp || !ptr)
		return;
	if (allocated + heap_size == ptr + ((metadata_s *)ptr)->size)
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
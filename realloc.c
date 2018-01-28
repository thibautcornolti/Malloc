/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <string.h>
#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
	metadata_s *temp = allocated;
	metadata_s *newElem;

	if (!ptr && size)
		return (malloc(size));
	while (temp && temp->ptr != ptr)
		temp = temp->next;
	if (temp && !size) {
		free(ptr);
		return NULL;
	} else if (temp) {
		if (temp->size > size)
			return temp->ptr;
		newElem = malloc(size);
		return (memcpy(newElem, ptr, temp->size));
	}
	return NULL;
}
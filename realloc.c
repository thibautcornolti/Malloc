/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <string.h>
#include "malloc.h"

void my_memcpy(void *dest, const void *src, size_t n)
{
	char *cdest = dest;
	const char *csrc = src;

	for (size_t i = 0; i < n; ++i) {
		cdest[i] = csrc[i];
	}
}

void *realloc(void *ptr, size_t size)
{
	metadata_t *temp = NULL;
	metadata_t *newElem;

	if (!ptr && size)
		return (malloc(size));
	temp = (!ptr || ((metadata_t *)(ptr - HEADER))->ptr != ptr) ? NULL :
		ptr - HEADER;
	if (temp && !size) {
		free(ptr);
		return (NULL);
	} else if (temp) {
		if (temp->size > size)
			return (temp->ptr);
		lock_thread(1);
		newElem = malloc(size);
		my_memcpy(newElem, ptr, temp->size);
		free(ptr);
		unlock_thread(1);
		return (newElem);
	}
	return (malloc(size));
}

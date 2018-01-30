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
	metadata_t *temp = allocated;
	metadata_t *newElem;

	write(2, "realloc\n", 9);
	if (!ptr && size)
		return (malloc(size));
	while (temp && temp->ptr != ptr)
		temp = temp->next;
	if (temp && !size) {
		free(ptr);
		return (NULL);
	} else if (temp) {
		if (temp->size > size)
			return (temp->ptr);
		newElem = malloc(size);
		my_memcpy(newElem, ptr, temp->size);
		free(temp);
		return (newElem);
	}
	write(2, "endrealloc\n", 12);
	return (malloc(size));
}

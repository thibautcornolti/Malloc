/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include "malloc.h"

static void my_memcpy(void *dest, const void *src, size_t n)
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
	void *newElem;

	write(1, "realloc\n", 8);
	if ((!ptr && size) || (ptr && !size)) {
		if (ptr)
			free(ptr);
		return (!ptr ? malloc(size) : NULL);
	}
	for (; temp && (void *)temp + HEADER != ptr; temp = temp->next);
	if (temp && temp->size >= size)
		return ((void *)temp + HEADER);
	else if (temp) {
		lock_thread(1);
		newElem = malloc(size);
		my_memcpy(newElem, ptr, temp->size > size ? size : temp->size);
		free(ptr);
		unlock_thread(1);
		return (newElem);
	}
	write(1, "realloc null\n", 13);
	return (NULL);
}

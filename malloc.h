/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#ifndef MALLOC_H
#define MALLOC_H

#include <errno.h>
#include <zconf.h>

#define HEADER sizeof(struct s_memory_chunk)

extern struct metadata_t *allocated;
extern struct metadata_t *freed;
extern size_t heap_size;

typedef struct metadata_t {
	void *ptr;
	size_t size;
	struct metadata_t *prev;
	struct metadata_t *next;
} metadata_s;

void	*malloc(size_t);
void	*realloc(void *, size_t);
void	free(void *);
void	show_alloc_mem(void);

#endif

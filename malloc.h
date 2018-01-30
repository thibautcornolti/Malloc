/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#ifndef MALLOC_H
#define MALLOC_H

#include <errno.h>
#include <unistd.h>

extern struct metadata_s *allocated;

typedef struct metadata_s {
	void *ptr;
	size_t size;
	struct metadata_s *next;
	char occupied;
} metadata_t;

void	*malloc(size_t);
void	*realloc(void *, size_t);
void	*calloc(size_t, size_t);
void	free(void *);
void	show_alloc_mem(void);

#define align4(x) (((((x)-1)>>2)<<2)+4)
#define HEADER sizeof(struct metadata_s)

#endif

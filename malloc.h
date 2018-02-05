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
void	lock_thread(int);
void	unlock_thread(int);
void	show_alloc_mem(void);

#ifndef __X86_64__
#define ALIGNMENT (16)
#else
#define ALIGNMENT (8)
#endif

#define ALIGN(size) (((size) + (ALIGNMENT - 1)) &~ (ALIGNMENT - 1))
#define HEADER (sizeof(struct metadata_s))

#endif

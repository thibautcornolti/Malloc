/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "malloc.h"

void show_alloc_mem(void)
{
	metadata_t *temp = allocated;

	printf("break : %p\n", sbrk(0));
	while (temp) {
		printf("%p - %p : %zu bytes\n", temp->ptr,
			temp->ptr + temp->size, temp->size);
		temp = temp->next;
	}
}
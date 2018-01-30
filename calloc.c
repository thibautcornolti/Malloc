/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include "malloc.h"

void *calloc(size_t nmeb, size_t size){
	return(malloc(nmeb * size));
}
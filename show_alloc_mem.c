/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by rectoria
*/

#include <unistd.h>
#include "malloc.h"

void my_putnbr(long long int nbr)
{
	char tmp;

	if (nbr < 0) {
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr / 10 != 0)
		my_putnbr(nbr / 10);
	tmp = (char)((nbr % 10) + '0');
	write(1, &tmp, 1);
}

int print_address_in_hexa(unsigned long long int ptr)
{
	unsigned long nbr2;
	char nbrc;
	int size = 0;

	if ((ptr / 16) != 0)
		size = print_address_in_hexa(ptr / 16);
	nbr2 = ptr % 16;
	nbrc = (nbr2 >= 10 && nbr2 <= 15) ? (char)(nbr2 + 55) :
		(char)(nbr2 + '0');
	write(1, &nbrc, 1);
	return (size + 1);
}

void show_alloc_mem()
{
	metadata_t *tmp = allocated;
	void *breakPoint = sbrk(0);

	if (!breakPoint)
		return;
	my_putstr("break : ");
	write(1, "0x", 2);
	print_address_in_hexa((unsigned long long int)breakPoint);
	my_putstr("\n");
	for (; tmp; tmp = tmp->next) {
		write(1, "0x", 2);
		print_address_in_hexa((size_t)tmp->ptr);
		my_putstr(" - ");
		write(1, "0x", 2);
		print_address_in_hexa((size_t)((void *)tmp->ptr + tmp->size));
		my_putstr(" : ");
		my_putnbr((long long int)tmp->size);
		if (!tmp->occupied)
			my_putstr(" freed bytes\n");
		else
			my_putstr(" bytes\n");
	}
}
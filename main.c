#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str = malloc(sizeof(char) * 12);

	printf("%x\n", str);
	return 0;
}
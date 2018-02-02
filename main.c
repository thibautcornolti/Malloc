#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;
	int i = 0;
	while(++i){
		if(!(str = malloc(sizeof(char) * i * 100000)))
		write(1, "Fail\n", 5);
	}
}

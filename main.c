#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *str;
	if (str=malloc(200000000)) {
		for (int i = 0 ; i < 200000000 ; ++i)
			str[i] = 'o';
		write(2, "should work\n", 13);
		free(str);
	}
	if (str=malloc(200000000)) {
		for (int i = 0 ; i < 200000000 ; ++i)
			str[i] = 'o';
		write(2, "should work\n", 13);
		free(str);
	}

	sleep(15);
}

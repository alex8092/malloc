#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	char *str;
	long int i;
	size_t	y;

	for (i = 0; i < 200000; ++i)
	{
		str = malloc(20);
		printf("test %p\n", str);
		for (y = 0; y < 20; y++)
			str[y] = 'a';
		str[y] = 0;
	}
	show_alloc_mem();
	return (0);
}

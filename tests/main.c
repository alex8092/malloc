#include "malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	char		*str;
	long int	i;
//	long int	y;

	for (i = 0; i < 20000; ++i)
	{

		str = malloc(5000000000);
		realloc(str, 500000);
//		str = malloc(2000);
//		str = malloc(50000);
//		for (y = 0; y < 200; y++)
//			str[y] = 'a';
//		str[y] = 0;
		free(str);
	}
	show_alloc_mem();
	return (0);
}

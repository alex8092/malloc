#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		*str;
	long int	i;
//	long int	y;

	for (i = 0; i < 20; ++i)
	{

		str = malloc(200);
//		str = malloc(2000);
//		str = malloc(50000);
//		for (y = 0; y < 200; y++)
//			str[y] = 'a';
//		str[y] = 0;
	}
	show_alloc_mem();
	return (0);
}

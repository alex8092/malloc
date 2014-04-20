#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		*str;
	long int	i;
//	long int	y;

	for (i = 0; i < 2000; ++i)
		str = malloc(50);
	show_alloc_mem();
	return (0);
}

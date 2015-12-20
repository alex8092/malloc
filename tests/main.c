#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		*str;
	long int	i;
	long int	y;

	for (i = 0; i < 10; ++i)
	{
		str = malloc(i * 10000);
		if (str)
		{
			for (y = 0; y < 200; ++y)
				str[y] = y % 26 + 65;
			free(str);
		}
	}
	// show_alloc_mem();
	return (0);
}

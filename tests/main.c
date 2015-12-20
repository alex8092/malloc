#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		*str;
	long int	i;
	long int	y;

	for (i = 0; i < 1024; ++i)
	{
		str = malloc(1024);
		if (str)
		{
			for (y = 0; y < 200; ++y)
				str[y] = y % 26 + 65;
			free(str);
		}
	}
	printf("npage: %zu\n", ft_mc_get_instance()->npage);
	// show_alloc_mem();
	return (0);
}

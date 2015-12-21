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
		str = malloc(10);
		if (str)
		{
			for (y = 0; y < 10; ++y)
				str[y] = y % 26 + 65;
			str = realloc(str, 20);
			if (!str)
				printf("fail !\n");
			for (y = 10; y < 20; ++y)
				str[y] = y % 26 + 65;
			printf("str: %s\n", str);
			free(str);
		}
	}
	printf("npage: %zu\n", ft_mc_get_instance()->npage);
	show_alloc_mem();
	return (0);
}

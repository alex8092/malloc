#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char		*str;
	long int	i;
	long int	y;

	for (i = 0; i < 1; ++i)
	{
		str = malloc(3000);
		if (str)
		{
			for (y = 0; y < 10; ++y)
				str[y] = y % 26 + 65;
			str = realloc(str, 0);
			// for (y = 10; y < 20; ++y)
				// str[y] = y % 26 + 65;
			// printf("str: %s\n", str);
			free(str);
		}
	}
	show_alloc_mem();
	// printf("npage: %zu\n", ft_mc_get_instance()->npage);
	return (0);
}

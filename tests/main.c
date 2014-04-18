#include "malloc.h"
#include <stdio.h>

int	main(void)
{
	char *str;
	long int i;


	for (i = 0; i < 20000; ++i)
	{
		str = malloc(20);
		str[20] = 0;
//		sleep(1);
//		printf("test %p\n", str);
		if (i % 2 == 0)
			ft_free(str);
	}
	show_alloc_mem();
	return (0);
}

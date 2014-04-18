#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void	show_alloc_mem(void)
{
	t_mal	*small;
	char	*tmp;

	small = struct_singleton()->small;
	while (small)
	{
		tmp = (char *)small + sizeof(t_mal);
		printf("TINY : %p\n", small);
		while (tmp < ((char*)small + sizeof(t_mal) + SIZE_N))
		{
			if (*tmp == 'i')
				printf("%p - %p : %ld octets\n", (tmp + 1 + sizeof(size_t)), (tmp + 1 + *(size_t*)(tmp + 1) + sizeof(size_t)), *(size_t*)(tmp + 1));
			tmp += 1 + *(size_t*)(tmp + 1) + sizeof(size_t);
		}
		small = small->next;
		printf("---\n\n\n\n\n");
	}
}

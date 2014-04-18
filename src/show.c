#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void	print(t_mal *small, char *type)
{
	char	*tmp;

	while (small)
	{
		tmp = (char *)small + sizeof(t_mal);
		printf("%s : %p\n", type, small);
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

void	show_alloc_mem(void)
{
	print(struct_singleton()->small, "TINY");
	print(struct_singleton()->big, "BIG");
	print(struct_singleton()->other, "OTHER");
}

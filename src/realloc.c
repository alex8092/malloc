#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	*old_size;
	size_t	*next;

	printf("test\n");
	tmp = (char*)ptr;
	old_size = (size_t*)(tmp - sizeof(size_t));
	next =  (size_t*)(tmp + sizeof(size_t) + 1 + *(size_t*)(tmp - sizeof(size_t)));
	if (size >= *(size_t*)(tmp - sizeof(size_t)))
		return (ptr);
	printf("test2\n");
	if (*(tmp + *old_size) == 'd' && *old_size + *next >= size)
	{
		printf("lolol\n");
		*old_size = size;
		*(tmp + size) = 'd';
		*(size_t*)(tmp + size + 1) = (*old_size + *next - size);
	}
	return (ptr);
}

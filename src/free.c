#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		supprim(void *ptr, t_mal **begin, size_t len, size_t size)
{
	char	*tmp;
	char	*tmp2;
	t_mal	*prev;
	t_mal	*cur;

	cur = *begin;
	while (cur)
	{
		if (ptr > (void*)cur && ptr < (void*)((char*)cur + len + 1 + sizeof(size_t)))
			break ;
		prev = cur;
		cur = cur->next;
	}
  	tmp = (char*)cur + sizeof(t_mal);
	while ((tmp + 1 + sizeof(size_t) + *(size_t*)(tmp + 1)) != (char*)ptr)
		tmp += 1 +  sizeof(size_t) + *(size_t*)(tmp + 1);
	cur->dispo += size + 1 + sizeof(size_t);
	if (cur->dispo == len + 1 + sizeof(size_t))
	{
		if (prev)
			prev->next = prev->next->next;
		else
			*begin = cur->next;
		munmap(cur, len + sizeof(t_mal) + 1 + sizeof(size_t));
	}
	else
	{
		tmp2 = (char*)ptr;
		*(tmp2 - sizeof(size_t) - 1) = 'd';
		if (*(tmp2 + size) == 'd')
			*(size_t*)(tmp2 - sizeof(size_t)) += *(size_t*)(tmp2 + size) + 1 + sizeof(size_t);
		if (*tmp == 'd')
			*(size_t*)(tmp + 1) += *(size_t*)(tmp + 1 + sizeof(size_t) + *(size_t*)(tmp + 1) + 1 + sizeof(size_t));

	}
}

void	free(void *ptr)
{
	char	*tmp;
	size_t	len;

	tmp = (char*)ptr;
	len = *(size_t*)(tmp - sizeof(size_t));
	if (len < SIZE_N)
		supprim(ptr, &struct_singleton()->small, SIZE_N, len);
	else if (len < SIZE_M)
		supprim(ptr, &struct_singleton()->big, SIZE_M, len);
	else
		supprim(ptr, &struct_singleton()->other, len, len);
	
}


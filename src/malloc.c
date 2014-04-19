#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	*put_in(size_t size, t_mal *cur, size_t len)
{
	char *tmp;
	t_mal *prev;
	size_t	old;

	prev = NULL;
	while (cur)
	{
		if (cur->dispo < (size + 1 + sizeof(size_t)))
		{
			prev = cur;
			cur = cur->next;
		}
		else
		{
			tmp = (char*)cur + sizeof(t_mal);
			while ((tmp + 1 + sizeof(size_t) + size < (char*)cur + sizeof(t_mal) + 1 +  sizeof(size_t) + len) && ((*tmp == 'i') || (*(size_t*)(tmp + 1) <= (1 + sizeof(size_t) + size))))
				tmp += 1 + sizeof(size_t) + *(size_t*)(tmp + 1);
			if (tmp + 1 + sizeof(size_t) + size >= (char*)cur + sizeof(t_mal) + 1 +  sizeof(size) + len) 
			{
				prev = cur;
				cur = cur->next;
			}
			else
				break;
		}
	}
	if (!cur)
	{
		cur = prev;
		if ((prev = mmap(NULL, sizeof(t_mal) + len + 1 + sizeof(size_t), PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
			exit (1);
		if (!cur)
			cur = prev;
		else
			cur->next = prev;
		tmp = (char*)prev + sizeof(t_mal);
		*tmp = 'd';
		*(size_t*)(tmp + 1) = len - 1 - sizeof(size_t);
		cur = prev;
		cur->dispo = len + 1 + sizeof(size_t);
	}
	*tmp = 'i';
	cur->dispo -= size + 1 + sizeof(size_t);
	old = *(size_t*)(tmp + 1);
	*(size_t*)(tmp + 1) = size;
	if (old - size - 2 * (1 +  sizeof(size_t))  > 0)
	{
		*(tmp + 1 + sizeof(size_t) + size) = 'd';
		*(size_t*)(tmp + 2 + sizeof(size_t) + size) = old - size - 1 - sizeof(size_t);
//		printf("total dispo = [%ld]\n", cur->dispo);
//		printf("old[%ld] - size[%ld] = %ld\n\n", old, size, *(size_t*)(tmp + 2 + sizeof(size_t) + size));
	}
	return (tmp + 1 + sizeof(size_t));
}


void	*malloc(size_t size)
{
	if (size < (SIZE_N / 100))
		return (put_in(size, struct_singleton()->small, SIZE_N));
	else if (size < (SIZE_M / 100))
		return (put_in(size, struct_singleton()->big, SIZE_M));
	else
	{
		if (struct_singleton()->other == NULL)
		{
	if ((struct_singleton()->other =  mmap(NULL, sizeof(t_mal) + 1 + sizeof(size_t) + size, PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
				exit (1);
			struct_singleton()->other->dispo = size;
		}
		return (put_in(size, struct_singleton()->other, size));
	}
}



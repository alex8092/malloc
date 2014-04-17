#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	*put_in(size_t size, t_mal *cur, size_t len)
{
	char	*tmp;
	size_t	old;
	t_mal	*prev;

	prev = NULL;
/*	while (cur->dispo < (size + 1 + sizeof(size_t)) && cur->next)
		cur = cur->next;
	if (cur->dispo >= (size + 1 + sizeof(size_t)))
	{
		tmp = (char*)cur;
		tmp += sizeof(t_mal);
		cur->dispo -= size + sizeof(size_t) + 1;
		while (tmp < ((char*)cur + len + 1 + sizeof(size_t)) && (*tmp == 'i' || *(size_t*)(tmp + 1) < (size + 1 + sizeof(size_t))))
			tmp += *(size_t*)(tmp + 1) + 1 + sizeof(size_t);
		if (tmp >=v ((char*) cur + len + 1 + sizeof(size_t)))
			i++;
	}
	else
		i = 1;*/
	while (cur)
	{
		tmp = (char*)cur + sizeof(t_mal);
		while (tmp < ((char*)cur + len + 1 + sizeof(size_t)) && (*tmp == 'i' || *(size_t*)(tmp + 1) < (size + 1 + sizeof(size_t))))
			tmp += *(size_t*)(tmp + 1) + 1 + sizeof(size_t);
		if (tmp >=  ((char*) cur + len + 1 + sizeof(size_t)))
		{
			prev = cur;
			cur = cur->next;
		}
		else
			break ;
	}
	if (cur == NULL)
	{
		cur = prev;
		if ((cur->next = mmap(NULL, sizeof(t_mal) + len + 1 + sizeof(size_t), PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
			exit (1);
		tmp = (char*)cur->next + sizeof(t_mal);
		*tmp = 'd';
		*(size_t*)(tmp + 1) = len - 1 - sizeof(size_t);
	}
	*tmp = 'i';
	old = *(size_t*)(tmp + 1);
	*(size_t*)(tmp + 1) = size;
	if (((tmp + sizeof(size_t) + 1) + size) < ((char*)cur + sizeof(t_mal) + len + 1))
	{
		*(tmp + size + 1 + sizeof(size_t)) = 'd';
		*((size_t*)(tmp + size + 2 + sizeof(size_t) )) = old - size - 1 - sizeof(size_t);
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
		return (put_in(size, struct_singleton()->other, size));
}



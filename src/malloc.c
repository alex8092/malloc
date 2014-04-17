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

	tmp = (char*)cur;
	tmp += sizeof(t_mal);
	while (cur->dispo < size && cur->next)
		cur = cur->next;
	if (cur->dispo >= size)
	{
		cur->dispo -= size;
		while (*tmp != 'd' && *((size_t*)(tmp + 1)) < size)
			tmp +=  *((size_t*)(tmp + 1)) + 1;
	}
	else
	{
		if ((cur->next =  mmap(NULL, sizeof(t_mal) + len, PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0)) == NULL)
			exit (1);
		tmp = (char*)cur->next + sizeof(t_mal);
	}
	*tmp = 'i';
	old = *((size_t*)(tmp + 1));
	*((size_t*)(tmp + 1)) = size;
	tmp +=  *((size_t*)(tmp + 1)) + 1;
	*tmp    = 'd';
	*((size_t*)(tmp + 1)) = old - size - 1 - sizeof(size_t);
	return (tmp + 1 + sizeof(size_t));
}

void	*malloc(size_t size)
{
	static t_mal *small = NULL;
	static t_mal *big = NULL;
	static t_mal *other = NULL;

	if (small == NULL)
	{
		if ((small = mmap(NULL, sizeof(t_mal) + SIZE_N, PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS, 0, 0)) == NULL)
			exit(1);
		else
			small->dispo = SIZE_N - sizeof(size_t) - 1;
		if ((big =  mmap(NULL, sizeof(t_mal) + SIZE_M, PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS, 0, 0)) == NULL)
			exit (1);
		else
			big->dispo = SIZE_M - sizeof(size_t) - 1;
		if ((other =  mmap(NULL, sizeof(t_mal) + size ,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS, 0, 0)) == NULL)
			exit (1);
		else
			other->dispo = 0;
	}
	if (size < SIZE_N)
		return (put_in(size, small, SIZE_N));
	else if (size < SIZE_M)
		return (put_in(size, big, SIZE_M));
	else
		return (put_in(size, other, size));
}

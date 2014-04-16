#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>

void	*put_small(size_t size, t_mal *small)
{
	while (small->dispo < size && small->next)
		small = small->next;
	if (small->dispo > size)
	{
		small->dispo -= size;
		
	}
	else
	{
		small->next = mmap(NULL, (sizeof(t_mal) * SIZE_N), PROT_READ | PROT_WRITE , MAP_PRIVATE, 0, 0);
	}

	return (NULL);
}

void	*malloc(size_t size)
{
	static t_mal *small;
	static t_mal *big;
	static t_mal *other;

	if (small == NULL)
	{
		if ((small = mmap(small, (sizeof(t_mal) * SIZE_N), PROT_READ | PROT_WRITE , MAP_PRIVATE, 0, 0)) == NULL)
			exit(1);
		else
			small->dispo = SIZE_N;
		if ((big = mmap(small, (sizeof(t_mal) * SIZE_M), PROT_READ | PROT_WRITE, MAP_PRIVATE , 0, 0)) == NULL)
			exit (1);
		else
			big->dispo = SIZE_M;
		if ((other = mmap(small, sizeof(t_mal), PROT_READ | PROT_WRITE, MAP_PRIVATE, 0, 0)) == NULL)
			exit (1);
	}
	if (size < SIZE_N)
		;
	else if (size < SIZE_M)
		;
	else
		;
	return (NULL);
}

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>

t_mal	*init(int size, t_mal ptr)
{
	int	n;
	int	m;
	t_mal *new;

	// new = je sais pas comment alouer sans memoire ahahah
	new->next = NULL;
	if (size < n)
		new->total = n;
	else if (size < m)
		new->total = m;
	else
		new->total = 0;
	new->dispo = new->total - size;
	new->actual = size;
	// allourer le debut ahahha;
	return (new);
}

void	*new_ptr(int size, t_mal *ptr)
{
	if (ptr == NULL)
		;//init struct (size, NULL);
	else
	{
		while (ptr->next && ptr->dispo < size)
			ptr = ptr->next;
		if (size > ptr->dispo)
			;//ptr->next = init struc (size, ptr)
		else
		{
			ptr->dispo -= size;
			ptr->actual += size;

		}
	}
	return ((void *)ptr);
}


void	*malloc(size_t size)
{
	static t_mal *small;
	static t_mal *big;
	static t_mal *other;
	int			n;
	int			m;

	if (size < n)
		new_ptr(size, small);
	else if (size < m)
		new_ptr(size, big);
	else
		new_ptr(size, other);
	return (NULL);
}

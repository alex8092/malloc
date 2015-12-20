#include "malloc.h"
#include <sys/mman.h>
#include <stdio.h>

static void			nonfree_item(t_item *it, size_t size)
{
	t_item			*next;

	next = (t_item *)(it + sizeof(t_item) + size);
	if (size != it->size && it->size - size >= sizeof(t_item))
	{
		next->free = 1;
		if (it->size - size - sizeof(t_item) == 0)
			next->size = 0;
		else
			next->size = it->size - size - sizeof(t_item);
		next->prev = it;
	}
	else if (size != it->size)
		size = it->size;
	it->free = 0;
	it->size = size;
}

void				*ft_mc_range_insert(t_range *range, size_t size)
{
	t_item	*current;

	current = (t_item *)(range + sizeof(t_range));
	while ((void *)current < (void *)(range + range->size + sizeof(t_range)))
	{
		// printf("item free(%d) size(%zu)\n", current->free, current->size);
		if (current->free && current->size >= size)
		{
			nonfree_item(current, size);
			ft_mc_update_free_space(range);
			return (current + sizeof(t_item));
		}
		current = (t_item *)(current + sizeof(t_item) + current->size);
	}
	return (0);
}

t_range				*ft_mc_find_free(t_range *range, size_t size, size_t rsize)
{
	t_range			*last;
	t_range			*newrange;
	t_item			*item;

	last = 0;
	while (range)
	{
		last = range;
		if (range->free >= size)
			return (range);
		range = range->next;
	}
	newrange = mmap(0, rsize, MAP_PROT, MAP_ACCESS, -1, 0);
	if (!newrange)
		return (0);
	newrange->size = rsize - sizeof(t_range);
	newrange->free = newrange->size - sizeof(t_item);
	newrange->next = 0;
	item = (t_item *)(newrange + sizeof(t_range));
	item->size = newrange->free;
	item->free = 1;
	item->prev = 0;
	if (last)
		last->next = newrange;
	return (newrange);
}

t_range				*ft_mc_find_ptr(t_range *range, void *ptr)
{
	t_range			*current;
	void			*ptr2;

	current = range;
	while (current)
	{
		ptr2 = (current + sizeof(t_range));
		// printf("check (%p) with (%p)\n", ptr, ptr2);
		if (ptr >= ptr2 && ptr < ptr2 + current->size)
			return (range);
		current = current->next;
	}
	return (0);
}
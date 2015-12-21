#include "malloc.h"
#include <sys/mman.h>
#include <stdio.h>

static void			nonfree_item(t_item *it, size_t size)
{
	t_item			*next;

	next = (void *)it + sizeof(t_item) + size;
	if (size != it->size && it->size - size >= sizeof(t_item))
	{
		next->free = 1;
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

	current = (void *)range + sizeof(t_range);
	while ((void *)current < (void *)range + range->size + sizeof(t_range))
	{
		if (current->free && current->size >= size)
		{
			nonfree_item(current, size);
			ft_mc_update_free_space(range);
			return ((void *)current + sizeof(t_item));
		}
		current = (void *)current + sizeof(t_item) + current->size;
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
	++ft_mc_get_instance()->npage;
	newrange->size = rsize - sizeof(t_range);
	newrange->free = newrange->size - sizeof(t_item);
	newrange->next = 0;
	item = (void *)newrange + sizeof(t_range);
	item->size = newrange->free;
	item->free = 1;
	item->prev = 0;
	if (last)
		last->next = newrange;
	newrange->prev = last;
	return (newrange);
}

t_range				*ft_mc_find_ptr(t_range *range, void *ptr)
{
	t_range			*current;
	void			*ptr2;

	current = range;
	while (current)
	{
		ptr2 = (void *)current + sizeof(t_range);
		if (ptr >= ptr2 && ptr < ptr2 + current->size)
			return (range);
		current = current->next;
	}
	return (0);
}

t_item				*ft_mc_find_item(t_range *range, void *ptr)
{
	t_item	*current;
	void	*end;

	end = (void *)range + sizeof(t_range) + range->size;
	current = (void *)range + sizeof(t_range);
	while ((void *)current < end)
	{
		if ((void *)current + sizeof(t_item) == ptr)
			return (current);
		current = (void *)current + sizeof(t_item) + current->size;
	}
	return (0);
}
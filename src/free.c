#include "malloc.h"
#include <stdio.h>

void			ft_mc_free_item(t_range *range, t_item *item)
{
	t_item	*next;

	next = (void *)item + sizeof(t_item) + item->size;
	if ((void *)next < (void *)range + sizeof(t_range) + range->size)
	{
		if (next->free)
			item->size += next->size + sizeof(t_item);
		else
			next->prev = item;
	}
	if (item->prev && item->prev->free)
	{
		item->prev->size += item->size + sizeof(t_item);
		next = (void *)item + sizeof(t_item) + item->size;
		if ((void *)next < (void *)range + sizeof(t_range) + range->size)
			next->prev = item->prev;
	}
	else
		item->free = 1;
	ft_mc_update_free_space(range);
}

void			free(void *ptr)
{
	static t_mc		*mc = 0;
	t_range			*range;
	t_item			*it;

	if (!mc)
		mc = ft_mc_get_instance();
	pthread_mutex_lock(&mc->maccess);
	range = ft_mc_find_ptr(mc->tiny, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->small, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->big, ptr);
	if (!range)
	{
		pthread_mutex_unlock(&mc->maccess);
		return ;
	}
	it = ft_mc_find_item(range, ptr);
	if (it)
		ft_mc_free_item(range, it);
	mc->tiny = ft_mc_release_free_range(mc->tiny);
	mc->small = ft_mc_release_free_range(mc->small);
	mc->big = ft_mc_release_free_range(mc->big);
	pthread_mutex_unlock(&mc->maccess);
}
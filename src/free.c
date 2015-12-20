#include "malloc.h"
#include <stdio.h>

void		ft_mc_free_item(t_range *range, t_item *item)
{
	t_item	*next;

	if (item->prev && item->prev->free)
		item->prev->size += item->size + sizeof(t_item);
	else
	{
		item->free = 1;
		next = item;
		while (1)
		{
			next = (t_item *)(next + sizeof(t_item) + next->size);
			if ((void *)next >= (void *)(range + sizeof(t_range) + range->size))
				break ;
			if (next->free)
			{
				item->size += next->size + sizeof(t_item);
				next = (t_item *)(next + sizeof(t_item) + next->size);
			}
			else
			{
				next->prev = item;
				break ;
			}
		}
		
	}
	ft_mc_update_free_space(range);
}
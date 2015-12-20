#include "malloc.h"

void				ft_mc_update_free_space(t_range *range)
{
	t_item			*item;
	size_t			max;

	max = 0;
	item = (void *)range + sizeof(t_range);
	while ((void *)item < (void *)range + range->size + sizeof(t_range))
	{
		if (item->free && item->size > max)
			max = item->size;
		item = (void *)item + sizeof(t_item) + item->size;
	}
	range->free = max;
}
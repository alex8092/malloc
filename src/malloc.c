#include "malloc.h"
#include <sys/mman.h>

static void		ft_calc_sizes(t_mc *mc)
{
	mc->small_alloc = (SMALL_SZMAX + sizeof(t_item)) * 100;
	mc->small_alloc += sizeof(t_range);
	mc->tiny_alloc = (TINY_SZMAX + sizeof(t_item)) * 100;
	mc->tiny_alloc += sizeof(t_range);
	mc->small_alloc += (mc->small_alloc % mc->pgsize);
	mc->tiny_alloc += (mc->tiny_alloc % mc->pgsize);
}

t_mc			*ft_mc_get_instance(void)
{
	static t_mc	instance;
	static int	init = 0;

	if (!init)
	{
		instance.pgsize = getpagesize();
		instance.small = 0;
		instance.tiny = 0;
		instance.big = 0;
		instance.npage = 0;
		ft_calc_sizes(&instance);
		instance.total = 0;
		init = 1;
	}
	return (&instance);
}

void			*malloc(size_t size)
{
	if (!size)
		return (0);
	if (size <= TINY_SZMAX)
		return (ft_mc_alloc_tiny(size));
	else if (size <= SMALL_SZMAX)
		return (ft_mc_alloc_small(size));
	else
		return (ft_mc_alloc_big(size));
}

void			free(void *ptr)
{
	static t_mc		*mc = 0;
	t_range			*range;
	t_item			*it;

	if (!mc)
		mc = ft_mc_get_instance();
	range = ft_mc_find_ptr(mc->tiny, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->small, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->big, ptr);
	if (!range)
		return ;
	it = ft_mc_find_item(range, ptr);
	if (it)
		ft_mc_free_item(range, it);
}

void			*realloc(void *ptr, size_t size)
{
	static t_mc	*mc = 0;
	t_range		*range;
	t_item		*it;

	if (!mc)
		mc = ft_mc_get_instance();
	if (!(range = ft_mc_find_ptr(mc->tiny, ptr)))
		range = ft_mc_find_ptr(mc->small, ptr);
	if (!(range = ft_mc_find_ptr(mc->big, ptr)))
		return (0);
	if (!(it = ft_mc_find_item(range, ptr)))
		return (0);
	(void)size;
	return (it);
}
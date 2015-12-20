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
	if (size < TINY_SZMAX)
		return (ft_mc_alloc_tiny(size));
	else if (size < SMALL_SZMAX)
		return (ft_mc_alloc_small(size));
	else
		return (ft_mc_alloc_big(size));
}

void			free(void *ptr)
{
	static t_mc		*mc = 0;
	t_range			*range;

	if (!mc)
		mc = ft_mc_get_instance();
	range = ft_mc_find_ptr(mc->tiny, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->small, ptr);
	if (!range)
		range = ft_mc_find_ptr(mc->big, ptr);
	if (!range)
		return ;
	ft_mc_free_item(range, (t_item *)(range + sizeof(t_range)));
}
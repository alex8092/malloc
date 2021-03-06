/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 08:53:48 by amerle            #+#    #+#             */
/*   Updated: 2015/12/21 08:53:50 by amerle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*ft_mc_alloc_tiny(size_t size)
{
	static t_mc		*mc = 0;
	t_range			*range;

	if (!mc)
		mc = ft_mc_get_instance();
	range = ft_mc_find_free(mc->tiny, size, mc->tiny_alloc);
	if (!range)
		return (0);
	if (!mc->tiny)
		mc->tiny = range;
	return (ft_mc_range_insert(range, size));
}

void				*ft_mc_alloc_small(size_t size)
{
	static t_mc		*mc = 0;
	t_range			*range;

	if (!mc)
		mc = ft_mc_get_instance();
	range = ft_mc_find_free(mc->small, size, mc->small_alloc);
	if (!range)
		return (0);
	if (!mc->small)
		mc->small = range;
	return (ft_mc_range_insert(range, size));
}

void				*ft_mc_alloc_big(size_t size)
{
	static t_mc		*mc = 0;
	t_range			*range;
	size_t			rsize;

	if (!mc)
		mc = ft_mc_get_instance();
	rsize = size + sizeof(t_range) + sizeof(t_item);
	range = ft_mc_find_free(mc->big, size, rsize);
	if (!range)
		return (0);
	if (!mc->big)
		mc->big = range;
	return (ft_mc_range_insert(range, size));
}

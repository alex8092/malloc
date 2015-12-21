/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 08:54:07 by amerle            #+#    #+#             */
/*   Updated: 2015/12/21 08:54:08 by amerle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

t_range				*ft_mc_release_free_range(t_range *range)
{
	t_range			*first;
	t_range			*next;

	first = range;
	while (range)
	{
		if (range->free + sizeof(t_item) == range->size)
		{
			if (range->prev)
				range->prev->next = range->next;
			if (range->next)
				range->next->prev = range->prev;
			if (!first || first == range)
				first = range->next;
			next = range->next;
			munmap(range, range->size + sizeof(t_range));
		}
		else
			next = range->next;
		range = next;
	}
	return (first);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 08:54:04 by amerle            #+#    #+#             */
/*   Updated: 2015/12/21 08:56:56 by amerle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

static void		*ft_do_realloc_next(t_range *range, t_item *it, size_t size)
{
	t_item		*next;
	t_item		*tmp;
	size_t		prev_size;

	next = (void *)it + it->size + sizeof(t_item);
	if (next->size + sizeof(t_item) == size - it->size && (it->size = size))
	{
		next = (void *)next + next->size + sizeof(t_item);
		if ((void *)next < (void *)range + sizeof(t_range) + range->size)
			next->prev = it;
	}
	else
	{
		prev_size = next->size;
		next = (void *)it + size + sizeof(t_item);
		next->size = prev_size - (size - it->size);
		next->prev = it;
		ft_mc_free_item(range, next);
		tmp = next;
		next = (void *)it + size + sizeof(t_item);
		if ((void *)next < (void *)range + sizeof(t_range) + range->size)
			next->prev = tmp;
		it->size = size;
	}
	return ((void *)it + sizeof(t_item));
}

static void		*ft_alloc_new(t_item *it, size_t size)
{
	char		*ptr;
	char		*ptr2;
	size_t		i;

	ptr = (char *)malloc(size);
	if (!ptr)
		return (ptr);
	ptr2 = (char *)it + sizeof(t_item);
	i = 0;
	while (i < it->size)
	{
		ptr[i] = ptr2[i];
		++i;
	}
	free(ptr2);
	return (ptr);
}

static void		*ft_realloc_next(t_range *range, t_item *it, size_t size)
{
	t_item		*next;

	next = (void *)it + it->size + sizeof(t_item);
	if ((void *)next < (void *)range + sizeof(t_range) + range->size)
	{
		if (next->free && next->size + sizeof(t_item) >= size - it->size)
			return (ft_do_realloc_next(range, it, size));
	}
	return (ft_alloc_new(it, size));
}

void			*ft_mc_realloc(t_range *range, t_item *it, size_t size)
{
	t_item		*tmp;

	if (!size)
	{
		free((void *)it + sizeof(t_item));
		return (0);
	}
	if (size < it->size)
	{
		if (it->size - size >= sizeof(t_item))
		{
			tmp = (void *)it + sizeof(t_item) + size;
			tmp->size = it->size - size - sizeof(t_item);
			tmp->prev = it;
			ft_mc_free_item(range, tmp);
		}
		it->size = size;
		return ((void *)it + sizeof(t_item));
	}
	else
		return (ft_realloc_next(range, it, size));
}

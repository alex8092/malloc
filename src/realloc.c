/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:44 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 18:34:53 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		is_in(void *ptr, t_mal *cur, size_t size)
{
	char	*tmp;
	char	*begin;

	begin = (char*)cur;
	while (cur)
		cur = cur->next;
	tmp = (char*)(cur + size + 1 + SIZE_T);
	if ((char*)ptr >= begin && (char*)ptr <= tmp)
		return (1);
	return (0);
}

int		is_mine(void *ptr)
{
	char	*tmp;
	int		ret;
	t_mal	*cur;

	ret = 0;
	cur = struct_singleton()->small;
	ret += is_in(ptr, cur, SIZE_N);
	if (ret)
		return (1);
	cur = struct_singleton()->big;
	ret += is_in(ptr, cur, SIZE_M);
	if (ret)
		return (1);
	cur = struct_singleton()->other;
	while (cur)
	{
		tmp = (char*)cur + sizeof(t_mal) + 1;
		if ((char*)ptr >= tmp && (char*)ptr <= tmp + *(size_t*)tmp)
			return (1);
		cur = cur->next;
	}
	return (ret);
}

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	*old;
	size_t	*next;
	void	*new;

	if (!is_mine(ptr))
		return (ptr);
	old = (size_t*)((char*)ptr - sizeof(size_t));
	if (size == *old)
		return (ptr);
	next = (size_t*)((char*)ptr + 1 + *(size_t*)((char*)ptr - sizeof(size_t)));
	if ((*((char*)ptr + *old) == 'd' && *old + *next >= size) || size < *old)
	{
		*(size_t*)((char*)ptr + size + 1) = (*old + *next - size);
		*old = size;
		*((char*)ptr + size) = 'd';
	}
	else
	{
		new = ft_malloc(size);
		ft_memcpy(new, ptr, *old);
		ft_free(ptr);
		ptr = new;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:44 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 05:53:39 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	*ft_realloc(void *ptr, size_t size)
{
	char	*tmp;
	size_t	*old_size;
	size_t	*next;
	void	*new;

	tmp = (char*)ptr;
	old_size = (size_t*)(tmp - sizeof(size_t));
	if (size == *old_size)
		return (ptr);
	next = (size_t*)(tmp + 1 + *(size_t*)(tmp - sizeof(size_t)));
	if ((*(tmp + *old_size) == 'd' && *old_size + *next >= size) || size < *old_size)
	{
		*(size_t*)(tmp + size + 1) = (*old_size + *next - size);
		*old_size = size;
		*(tmp + size) = 'd';
	}
	else
	{
		new = malloc(size);
		ft_memcpy(new, ptr, *old_size);
		ft_free(ptr);
		ptr = new;
	}
	return (ptr);
}

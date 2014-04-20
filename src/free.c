/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:31 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 05:53:42 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		supprim(void *ptr, t_mal **begin, size_t len, size_t size)
{
	char	*tmp;
	t_mal	*prev;
	t_mal	*cur;
	size_t	prev_size;

	cur = *begin;
	prev = NULL;
	while (cur)
	{
		if ((char*)ptr >= (char*)cur && (char*)ptr <= (char*)cur + len + 1 + sizeof(size_t) + sizeof(t_mal))
			break ;
		prev = cur;
		cur = cur->next;
	}
	tmp = (char*)cur + sizeof(t_mal);
	if (tmp + 1 + sizeof(size_t) != (char*)ptr)
	{
		while (tmp + 1 + sizeof(size_t) != (char*)ptr)
		{
			prev_size = *(size_t*)(tmp + 1);
			tmp += 1 +  sizeof(size_t) + *(size_t*)(tmp + 1);
		}
	}
	cur->dispo += size + 1 + sizeof(size_t) ;
	if (cur->dispo == len + 1 + sizeof(size_t))
	{
		if (prev)
			prev->next = prev->next->next;
		else
			*begin = cur->next;
		munmap(cur, len + sizeof(t_mal) + 1 + sizeof(size_t));
	}
	else
	{
		*((char*)ptr - sizeof(size_t) - 1) = 'd';
		if (*((char*)ptr + size) == 'd')
			*(size_t*)((char*)ptr - sizeof(size_t)) += *(size_t*)((char*)ptr + size + 1) + 1 + sizeof(size_t);
			if ((char*)cur + sizeof(t_mal)  != (char*)ptr - 1 - sizeof(size_t) && *(char*)(ptr - 2 * (sizeof(size_t) - 1) - prev_size) == 'd')
				*(size_t*)((char*)ptr - 2 * sizeof(size_t) - 1 - prev_size) += *(size_t*)((char*)ptr  - sizeof(size_t)) + sizeof(size_t) + 1;
	}
}

void	ft_free(void *ptr)
{
	char	*tmp;
	size_t	len;

	tmp = (char*)ptr;
	len = *(size_t*)(tmp - sizeof(size_t));
	if (len < (SIZE_N / (100 - 1 - sizeof(size_t))))
		supprim(ptr, &struct_singleton()->small, SIZE_N, len);
	else if (len < (SIZE_M / (100 - 1 - sizeof(size_t))))
		supprim(ptr, &struct_singleton()->big, SIZE_M, len);
	else
		supprim(ptr, &struct_singleton()->other, len, len);
	
}


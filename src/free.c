/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:31 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 18:24:25 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		maj(void *ptr, size_t size, size_t prev, t_mal *cur)
{

	char	*tmp;
	char	*tmp2;

	tmp2 = (char*)cur + sizeof(t_mal);
	tmp = (char*)ptr;
	*(tmp - SIZE_T - 1) = 'd';
	if (*(tmp + size) == 'd')
		PREV_SIZE += *(size_t*)(tmp + size + 1) + 1 + SIZE_T;
	if (tmp2 < tmp - 1 - SIZE_T && *(tmp - 2 * (SIZE_T - 1) - prev) == 'd')
		*(size_t*)(tmp - 2 * SIZE_T - 1 - prev) += PREV_SIZE + SIZE_T + 1;
}

static t_mal	*find_cur(t_mal **begin, void *ptr, t_mal **prev, size_t len)
{
	char	*tmp2;
	char	*tmp;
	t_mal	*cur;

	cur = *begin;
	tmp = (char*)ptr;
	while (cur)
	{
		tmp2 = (char*)cur;
		if (tmp >= tmp2 && tmp <= tmp2 + len + 1 + SIZE_T + sizeof(t_mal))
			break ;
		*prev = cur;
		cur = cur->next;
	}
	return (cur);
}

static void		ft_delete(t_mal **prev, t_mal **begin, t_mal **cur, size_t len)
{
	if (*prev)
		(*prev)->next = (*prev)->next->next;
	else
		*begin = (*cur)->next;
	munmap(*cur, len + sizeof(t_mal) + 1 + SIZE_T);
}

static void		supprim(void *ptr, t_mal **begin, size_t len, size_t size)
{
	char	*tmp;
	t_mal	*prev;
	t_mal	*cur;
	size_t	prev_size;

	prev = NULL;
	cur = find_cur(begin, ptr, &prev, len);
	tmp = (char*)cur + sizeof(t_mal);
	if (tmp + 1 + SIZE_T != (char*)ptr)
	{
		while (tmp + 1 + SIZE_T != (char*)ptr)
		{
			if (*(tmp + 1) == 'd')
				prev_size = TMP_SIZE;
			tmp += 1 + SIZE_T + *(size_t*)(tmp + 1);
		}
	}
	cur->dispo += size + 1 + SIZE_T;
	if (cur->dispo == len + 1 + SIZE_T)
		ft_delete(&prev, begin, &cur, len);
	else
		maj(ptr, size, prev_size, cur);
}

void			free(void *ptr)
{
	char	*tmp;
	size_t	len;

	if (!is_mine(ptr))
		return ;
	tmp = (char*)ptr;
	len = *(size_t*)(tmp - SIZE_T);
	if (len < (SIZE_N / (100 - 1 - SIZE_T)))
		supprim(ptr, &struct_singleton()->small, SIZE_N, len);
	else if (len < (SIZE_M / (100 - 1 - SIZE_T)))
		supprim(ptr, &struct_singleton()->big, SIZE_M, len);
	else
		supprim(ptr, &struct_singleton()->other, len, len);
}

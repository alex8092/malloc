/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:38 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 10:13:43 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		actualisation(t_mal *cur, char *tmp, size_t size)
{
	size_t	old;

	*tmp = 'i';
	cur->dispo -= size + 1 + SIZE_T;
	old = *(size_t*)(tmp + 1);
	*(size_t*)(tmp + 1) = size;
	if (old - size - 2 * (1 + SIZE_T) > 0)
	{
		*(tmp + 1 + SIZE_T + size) = 'd';
		*(size_t*)(tmp + 2 + SIZE_T + size) = old - size - 1 - SIZE_T;
	}
}

static t_mal	*add_zone(t_mal **prev, size_t len, char **tmp)
{
	t_mal	*cur;

	cur = *prev;
	if ((*prev = NEW(len)) == NULL)
		exit (1);
	if (!cur)
		cur = *prev;
	else
		cur->next = *prev;
	*tmp = (char*)*prev + sizeof(t_mal);
	**tmp = 'd';
	*(size_t*)(*tmp + 1) = len - 1 - SIZE_T;
	cur = *prev;
	cur->dispo = len + 1 + SIZE_T;
	return (cur);
}

static char		*ft_find_where(t_mal *cur, size_t len, size_t size)
{
	char	*tmp;

	if (cur->dispo < (size + 1 + SIZE_T))
		return (NULL);
	tmp = (char*)cur + sizeof(t_mal);
	while ((NEXT_PTR < LAST_PTR) && CAN_PUT)
		tmp += 1 + SIZE_T + *(size_t*)(tmp + 1);
	if (NEXT_PTR >= (char*)cur + sizeof(t_mal) + 1 + sizeof(size_t) + len)
		return (NULL);
	else
		return (tmp);
}

static void			*put_in(size_t size, t_mal *cur, size_t len)
{
	char	*tmp;
	t_mal	*prev;

	prev = NULL;
	while (cur)
	{
		if ((tmp = ft_find_where(cur, len, size)) != NULL)
			break ;
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	if (!cur)
		cur = add_zone(&prev, len, &tmp);
	actualisation(cur, tmp, size);
	return (tmp + 1 + SIZE_T);
}

void			*malloc(size_t size)
{
	if (size < (SIZE_N / (100 - 1 - SIZE_T)))
		return (put_in(size, struct_singleton()->small, SIZE_N));
	else if (size < (SIZE_M / (100 - 1 - SIZE_T)))
		return (put_in(size, struct_singleton()->big, SIZE_M));
	else
	{
		if (struct_singleton()->other == NULL)
		{
			if ((struct_singleton()->other = NEW(size)) == NULL)
				exit (1);
			struct_singleton()->other->dispo = size;
		}
		return (put_in(size, struct_singleton()->other, size));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:49 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 14:27:44 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void		print_init(char *type, t_mal *ptr)
{
	ft_putstr(type);
	ft_putstr(" : ");
	ft_putaddr(ptr);
	ft_putchar('\n');
}

size_t		print_current(char *tmp)
{
	size_t		ret;

	ft_putaddr(tmp + 1 + sizeof(size_t));
	ft_putstr(" - ");
	ft_putaddr((tmp + 1 + *(size_t*)(tmp + 1) + sizeof(size_t)));
	ft_putstr(" : ");
	ret = (*(size_t*)(tmp + 1));
	ft_putnbr(ret);
	ft_putstr(" octets\n");
	return (ret);
}

size_t		print(t_mal *cur, char *type, size_t size)
{
	char		*tmp;
	size_t		ret;

	ret = 0;
	while (cur)
	{
		tmp = (char *)cur + sizeof(t_mal);
		print_init(type, cur);
		while (tmp < ((char*)cur + sizeof(t_mal) + size))
		{
			if (*tmp == 'i')
				ret += print_current(tmp);
			tmp += 1 + *(size_t*)(tmp + 1) + sizeof(size_t);
		}
		cur = cur->next;
	}
	return (ret);
}

size_t		print_last(t_mal *cur)
{
	char	*tmp;
	size_t	ret;

	ret = 0;
	if (cur)
		cur = cur->next;
	while (cur)
	{
		tmp = (char*)cur + sizeof(t_mal);
		print_init("LARGE", cur);
		ret += print_current(tmp);
		cur = cur->next;
	}
	return (ret);
}

void		show_alloc_mem(void)
{
	size_t	ret;

	ret = 0;
	ret += print(struct_singleton()->small, "TINY", SIZE_N);
	ret += print(struct_singleton()->big, "SMALL", SIZE_M);
	ret += print_last(struct_singleton()->other);
	ft_putstr("Total : ");
	ft_putnbr(ret);
	ft_putstr(" octets\n");
}

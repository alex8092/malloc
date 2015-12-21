/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 08:54:10 by amerle            #+#    #+#             */
/*   Updated: 2015/12/21 08:54:11 by amerle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			print(const char *before, t_range *range)
{
	t_item			*current;

	ft_putstr(before);
	ft_putstr(" : ");
	ft_putaddr((void *)range + sizeof(t_range));
	ft_putstr("\n");
	current = (void *)range + sizeof(t_range);
	while ((void *)current < (void *)range + sizeof(t_range) + range->size)
	{
		if (!current->free || SHOW_FREE_SPACE)
		{
			ft_putaddr((void *)current + sizeof(t_item));
			ft_putstr(" - ");
			ft_putaddr((void *)current + sizeof(t_item) + current->size);
			ft_putstr(" : ");
			ft_putnbr(current->size);
			ft_putstr(" octets\n");
		}
		current = (void *)current + sizeof(t_item) + current->size;
	}
}

void				show_alloc_mem(void)
{
	static t_mc		*mc = 0;

	if (!mc)
		mc = ft_mc_get_instance();
	if (mc->tiny)
		print("TINY", mc->tiny);
	if (mc->small)
		print("SMALL", mc->small);
	if (mc->big)
		print("LARGE", mc->big);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 05:13:53 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 09:01:25 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void		ft_init_params(t_struct *singleton, size_t size)
{
	char	*tmp;

	tmp = (char*)singleton->small + sizeof(t_mal);
	*tmp = 'd';
	*(size_t*)(tmp + 1) = size - 1 - sizeof(size_t);
	singleton->small->dispo = size - 1 - sizeof(size_t);
}

t_struct		*struct_singleton(void)
{
	static t_struct		*singleton;
	size_t				size;

	if (singleton == NULL)
	{
		singleton = mmap(NULL, sizeof(t_struct), AG, -1, 0);
		if ((singleton->small = NEW(SIZE_N)) == NULL)
			exit(1);
		else
		{
			size = SIZE_N;
			ft_init_params(singleton, size);
		}
		if ((singleton->big = NEW(SIZE_M)) == NULL)
			exit (1);
		else
		{
			size = SIZE_M;
			ft_init_params(singleton, size);
		}
	}
	return (singleton);
}

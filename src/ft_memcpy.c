/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <thrivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:01:31 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 04:55:19 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char			*tmp;
	const char		*tmp2;

	tmp = (char *)s1;
	tmp2 = (const char*)s2;
	while (n > 0)
	{
		*tmp = *tmp2;
		++tmp;
		++tmp2;
		n--;
	}
	return (s1);
}

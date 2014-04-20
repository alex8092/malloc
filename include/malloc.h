/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrivier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 07:57:14 by thrivier          #+#    #+#             */
/*   Updated: 2014/04/20 09:03:05 by thrivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define SIZE_N 40960
# define SIZE_M 409600
# define AG PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANON
# define NEW(x)  mmap(NULL, sizeof(t_mal) + x + sizeof(size_t) + 1, AG, -1, 0)
# define NEXT_PTR tmp + 1 + sizeof(size_t) + size
# define LAST_PTR (char*)cur + sizeof(t_mal) + 1 +  sizeof(size_t) + len
# define TMP_SIZE *(size_t*)(tmp + 1)
# define SIZE_T sizeof(size_t)
# define CAN_PUT ((*tmp == 'i') || ( TMP_SIZE <= (1 + SIZE_T + size)))
# define PREV_SIZE *(size_t*)(tmp - SIZE_T)

typedef	struct s_mal	t_mal;
struct					s_mal
{
	t_mal				*next;
	size_t				dispo;
};

typedef struct s_struct	t_struct;
struct					s_struct
{
	t_mal				*small;
	t_mal				*big;
	t_mal				*other;
};

void					show_alloc_mem(void);
void					ft_free(void *ptr);
void					*ft_realloc(void *ptr, size_t size);
void					*malloc(size_t size);
void					*ft_memcpy(void *s1, const void *s2, size_t n);
void					ft_putaddr(void *ptr);
void					ft_putchar(char c);
int						ft_strlen(char *str);
void					ft_putstr(char *str);
void					ft_putnbr(size_t n);
t_struct				*struct_singleton(void);

#endif

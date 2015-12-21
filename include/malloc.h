#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define TINY_SZMAX		1024
# define SMALL_SZMAX	8192

# define MAP_PROT		PROT_WRITE | PROT_READ
# define MAP_ACCESS		MAP_PRIVATE | MAP_ANON

typedef struct s_item	t_item;
typedef struct s_range	t_range;

struct				s_item
{
	char			free;
	size_t			size;
	t_item			*prev;
};

struct				s_range
{
	size_t			free;
	size_t			size;
	t_range			*next;
	t_range			*prev;
};

typedef struct		s_mc
{
	t_range			*small;
	t_range			*tiny;
	t_range			*big;
	size_t			npage;
	int				pgsize;
	size_t			small_alloc;
	size_t			tiny_alloc;
	size_t			total;
}					t_mc;

/*
** malloc.c
*/
t_mc				*ft_mc_get_instance(void);
void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);

/*
** alloc.c
*/
void				*ft_mc_alloc_tiny(size_t size);
void				*ft_mc_alloc_small(size_t size);
void				*ft_mc_alloc_big(size_t size);

/*
** range.c
*/
t_range				*ft_mc_find_free(t_range *range, size_t size, size_t rsize);
void				*ft_mc_range_insert(t_range *range, size_t size);
t_range				*ft_mc_find_ptr(t_range *range, void *ptr);
t_item				*ft_mc_find_item(t_range *range, void *ptr);

/*
** check.c
*/
void				ft_mc_update_free_space(t_range *range);

/*
** free.c
*/
void				ft_mc_free_item(t_range *range, t_item *item);

/*
** realloc.c
*/
void				*ft_mc_realloc(t_range *range, t_item *it, size_t size);					

#endif
#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define SIZE_N 4060
# define SIZE_M 409600

typedef	struct s_mal t_mal;
struct		s_mal
{
	t_mal		*next;
	size_t		dispo;
};

typedef struct s_struct t_struct;
struct			s_struct
{
	t_mal		*small;
	t_mal		*big;
	t_mal		*other;
};

void		show_alloc_mem(void);
void		ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
void		*malloc(size_t size);
t_struct	*struct_singleton(void);

#endif

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define SIZE_N 40600
# define SIZE_M 40960000

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
void		free(void *ptr);
void		*malloc(size_t size);
t_struct	*struct_singleton(void);

#endif

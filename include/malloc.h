#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define SIZE_N 409600
# define SIZE_M 40960000

typedef	struct s_mal t_mal;
struct		s_mal
{
	t_mal		*next;
	size_t		total;
	size_t		dispo;
	int			actual;
};

void	*malloc(size_t size);

#endif

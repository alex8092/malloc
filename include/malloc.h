#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

typedef	struct s_mal t_mal;
struct		s_mal
{
	t_mal		*prev;
	t_mal		*next;
	size_t		total;
	size_t		dipo;
};

void	*malloc(size_t size);

#endif

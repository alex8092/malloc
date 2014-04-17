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

void	*malloc(size_t size);

#endif


#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_struct	*struct_singleton(void)
{
	static t_struct *singleton;
	char	*tmp;

	if (singleton == NULL)
	{
		singleton = mmap(NULL, sizeof(t_struct), PROT_WRITE|PROT_READ, MAP_PRIVATE|MAP_ANON, -1, 0);
		if ((singleton->small = mmap(NULL, sizeof(t_mal) + SIZE_N + sizeof(size_t) + 1, PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
			exit(1);
		else
		{
			tmp = (char*)singleton->small + sizeof(t_mal);
			*tmp = 'd';
			*(size_t*)(tmp + 1) = SIZE_N - 1 - sizeof(size_t);
			singleton->small->dispo = SIZE_N - 1 - sizeof(size_t);
		}



		if ((singleton->big =  mmap(NULL, sizeof(t_mal) + SIZE_M + 1 + sizeof(size_t), PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
			exit (1);
		else
		{
			tmp = (char*)singleton->big;
			*(tmp + sizeof(t_mal)) = 'd';
			*(size_t*)(tmp + sizeof(t_mal) + 1) = SIZE_M - 1 - sizeof(size_t);
			singleton->big->dispo = SIZE_M - 1 - sizeof(size_t);

		}



		if ((singleton->other =  mmap(NULL, sizeof(t_mal) + 1 + sizeof(size_t), PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_ANON, -1, 0)) == NULL)
			exit (1);
		singleton->other->dispo = 0;
	}

	return (singleton);
}

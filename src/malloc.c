#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"
#include <sys/mman.h>


void	*malloc(size_t size)
{
	size_t		n;
	size_t		m;

	n = 4096;
	m = 40000;
	if (size < n)
		;
	else if (size < m)
		;
	else
		;
	return (NULL);
}

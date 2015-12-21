#include "malloc.h"


void			ft_putaddr(void *ptr)
{
	size_t			adr;
	char			*tab;
	char			ret[9];
	int				i;

	adr = (size_t)ptr;
	tab = "0123456789abcdef";
	i = 8;
	while ((adr / 16) > 0 || i >= 8)
	{
		ret[i] = tab[(adr % 16)];
		adr /= 16;
		i--;
	}
	ret[i] = tab[(adr % 16)];
	write(1, "0x", 2);
	while (i < 9)
		write(1, &ret[i++], 1);
}

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

static int		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

void			ft_putnbr(size_t n)
{
	size_t		i;

	if (n == 0)
		ft_putchar('0');
	i = 1;
	while (i <= n)
		i *= 10;
	while (i != 1)
	{
		ft_putchar((n % i) / (i / 10) + 48);
		i /= 10;
	}
}
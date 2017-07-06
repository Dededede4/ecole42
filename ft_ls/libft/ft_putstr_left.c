#include "libft.h"

void	ft_putstr_left(char const *s, size_t place)
{
	size_t	spaces;

	spaces = place - ft_strlen(s);
	while (*s)
		ft_putchar(*(s++));
	while (place && spaces--)
		ft_putchar(' ');
}
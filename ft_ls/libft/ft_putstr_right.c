#include "libft.h"

void	ft_putstr_right(char const *s, size_t place)
{
	size_t	spaces;

	spaces = place - ft_strlen(s);
	while (place && spaces--)
		ft_putchar(' ');
	while (*s)
		ft_putchar(*(s++));
}

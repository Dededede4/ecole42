#include "ft_printf.h"

size_t	ft_unicodelen(const t_unicode *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

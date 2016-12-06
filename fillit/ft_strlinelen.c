#include "fillit.h"

size_t	ft_strlinelen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (i);
}
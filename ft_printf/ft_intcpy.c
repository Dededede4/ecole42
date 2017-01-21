#include "ft_printf.h"

void	*ft_intcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((int*)dest)[i] = ((int*)src)[i];
		i++;
	}
	return (dest);
}

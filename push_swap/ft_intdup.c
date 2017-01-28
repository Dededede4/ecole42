#include "push_swap.h"

int		*ft_intdup(int nbr)
{
	int *ptr;

	ptr = malloc(sizeof(int));
	if (!ptr)
		return (NULL);
	*(ptr) = nbr;
	return (ptr);
}
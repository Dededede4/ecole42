#include "push_swap.h"

t_list		*ft_arraytolst(char **str, int size)
{
	t_list	*first;
	t_list	*current;
	int 	val;
	int		i;
	int		e;

	e = 0;
	first = NULL;
	while(e < size)
	{
		i = 0;
		if (str[e][i] == '+' || str[e][i] == '-')
			i++;
		while (ft_isdigit(str[e][i]))
			i++;
		if (str[e][i] == '\0' && i > 0 && ft_isdigit(str[e][i - 1]))
		{
			val = ft_atoi(str[e]);
			if (first == NULL)
			{

				first = ft_lstnew(&val, sizeof(int));
				current = first;
			}
			else
			{
				current->next = ft_lstnew(&val, sizeof(int));
				current = current->next;
			}
		}
		else
		{ 	
			ft_putstr_fd("Error\n", 1);
			exit(0);
		}
		e++;
	}
	return (first);
}

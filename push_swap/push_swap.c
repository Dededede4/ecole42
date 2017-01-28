#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_list	*lst;
	if (argc > 0)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);
		ft_printlst(lst);
	}
	return (0);
}
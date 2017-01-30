#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_list	*lst;
	//t_instructs	*selectsort;
	if (argc > 0)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);
		/*selectsort = ft_pushswap_selectsort(lst);
		ft_printlst_str(selectsort);
		ft_printf("\n");*/
		ft_pushswap_bublesort(lst);
	}
	return (0);
}
#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_list	*lst;
	t_instructs	*selectsort;
	t_instructs	*bublesort;

	if (argc > 0)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);
		selectsort = ft_pushswap_selectsort(lst);
		bublesort = ft_pushswap_bublesort(lst);
		if (ft_lstlen(selectsort) > ft_lstlen(bublesort) )
		{
			ft_printf("Le gagnant est le bublesort !\nInstructions : %d\n", ft_lstlen(bublesort));
			//ft_printlst_str(bublesort);
		}
		else
		{
			ft_printf("Le gagnant est le selectsort !\nInstructions : %d\n", ft_lstlen(selectsort));
			//ft_printlst_str(selectsort);
		}
		
	}
	return (0);
}
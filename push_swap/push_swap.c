#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_list	*lst;
	t_instructs	*selectsort;
	t_instructs	*bublesort;
	t_instructs	*quicksort;

	int 		len_selectsort;
	int 		len_bublesort;
	int 		len_quicksort;

	if (argc > 1)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);
		selectsort = ft_pushswap_selectsort(lst);
		bublesort = ft_pushswap_bublesort(lst);
		quicksort = ft_pushswap_quicksort(lst);
		len_selectsort = ft_lstlen(selectsort);
		len_bublesort = ft_lstlen(bublesort);
		len_quicksort = ft_lstlen(quicksort);
		if ( len_bublesort <= len_selectsort && len_bublesort <= len_quicksort )
		{
			ft_printf("Le gagnant est le bublesort !\nInstructions : %d\n", len_bublesort);
			//ft_printlst_str(bublesort);
		}
		else if ( len_selectsort <= len_bublesort && len_selectsort <= len_quicksort )
		{
			ft_printf("Le gagnant est le selectsort !\nInstructions : %d\n", len_selectsort);
			//ft_printlst_str(selectsort);
		}
		else
		{
			ft_printf("Le gagnant est le quicksort !\nInstructions : %d\n", len_quicksort);
		}
		
	}
	return (0);
}
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

/*


int		main(int argc, char **argv)
{
	t_list	*lst;
	t_stacks *stacks;
	char 	instructs[] = {INSTRUCT_PB, INSTRUCT_PB, INSTRUCT_PB, INSTRUCT_PB, INSTRUCT_SA, INSTRUCT_SB, INSTRUCT_SS,
		INSTRUCT_PA, INSTRUCT_RA, INSTRUCT_RB,	INSTRUCT_RRA,
		INSTRUCT_RRB, 0};
	char 	*instructs_str[] = {"INSTRUCT_PB", "INSTRUCT_PB", "INSTRUCT_PB", "INSTRUCT_PB", "INSTRUCT_SA", "INSTRUCT_SB", "INSTRUCT_SS",
		"INSTRUCT_PA", "INSTRUCT_RA", "INSTRUCT_RB", "INSTRUCT_RRA",
		"INSTRUCT_RRB", 0};
	int 	i = 0;
	if (argc > 8)
	{
		lst = ft_arraytolst(argv + 1, argc - 1);

		stacks = malloc(sizeof(t_stacks));
		stacks->stacka = lst;
		stacks->instructs = NULL;
		stacks->stackb = NULL;
		ft_printf("A:");
		ft_printlst(stacks->stacka);
		ft_printf("\nB:");
		ft_printlst(stacks->stackb);
		ft_printf("\n\n");
		while (instructs[i])
		{
			ft_printf("%s\n", instructs_str[i]);
			ft_pushswap_instruct(instructs[i], stacks);
			ft_printf("A:");
			ft_printlst(stacks->stacka);
			ft_printf("\nB:");
			ft_printlst(stacks->stackb);
			ft_printf("\n\n");
			i++;
		}
	}
	return (0);
}*/
#include "push_swap.h"

int 		ft_pushswap_selectsort_findmin(t_vals *vals)
{
	int 	min_val;
	int 	min_pos;
	int 	length;

	if (!vals)
		return (0);
	length = 0;
	min_val = *((int*)vals->content);
	min_pos = 0;
	while (vals)
	{
		if (*((int*)vals->content) < min_val)
		{
			min_val = *((int*)vals->content);
			min_pos = length;
		}
		length++;
		vals = vals->next;
	}
	return (min_pos <= (length / 2) ? min_pos : 0 - (length - min_pos));
}


t_instructs		*ft_pushswap_selectsort(t_vals *vals)
{
	t_stacks *stacks;
	int 	 moves;

	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	while (stacks->stacka)
	{
		moves = ft_pushswap_selectsort_findmin(stacks->stacka);
		while (moves != 0)
		{
			if (moves > 0)
				ft_pushswap_instruct(INSTRUCT_RRA, stacks);
			else
				ft_pushswap_instruct(INSTRUCT_RA, stacks);
			moves += (moves > 0) ? -1 : 1;
		}
		ft_pushswap_instruct(INSTRUCT_PB, stacks);
		// TODO : stop if stack a is sorted
	}
	while (vals)
	{
		ft_pushswap_instruct(INSTRUCT_PA, stacks);
		vals = vals->next;
	}
	return stacks->instructs;
}


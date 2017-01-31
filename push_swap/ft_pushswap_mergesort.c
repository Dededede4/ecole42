/*t_instructs		*ft_pushswap_selectsort(t_vals *vals)
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
}*/
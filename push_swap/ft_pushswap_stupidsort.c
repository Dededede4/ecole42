#include "push_swap.h"

t_instructs		*ft_pushswap_stupidsort(t_vals *vals)
{
	t_stacks *stacks;

	stacks = malloc(sizeof(t_stacks));
	stacks->stacka = ft_lstcpy(vals);
	stacks->stackb = ft_lstcpy(vals);
	ft_pushswap_sa(stacks);
	ft_printlst(stacks->stacka);
	return stacks->instructs;
}
#include "push_swap.h"

void	ft_pushswap_sa(t_stacks *stacks)
{
	t_instructs		*new;

	new = ft_lstnew("sa", 3);
	if (stacks->instructs == NULL)
		stacks->instructs = new;
	else
		ft_lstadd(&stacks->instructs, new);
	ft_swap(stacks->stacka->content, stacks->stackb->content);
}